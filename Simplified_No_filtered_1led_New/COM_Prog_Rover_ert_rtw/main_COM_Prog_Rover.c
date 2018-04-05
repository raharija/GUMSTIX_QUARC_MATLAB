/*
***************************************************************************
*
* Author: Augustin Manecy
*
* Copyright (C) 2011-2014 Augustin Manecy
*
* augustin.manecy@gmail.com
*
***************************************************************************
*
* This file is part of RT-MaG Toolbox.
*
*   RT-MaG Toolbox is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   RT-MaG Toolbox is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with RT-MaG Toolbox.  If not, see <http://www.gnu.org/licenses/>.
*
***************************************************************************
*
* This version of GPL is at https://www.gnu.org/licenses/gpl-3.0.txt
*
***************************************************************************
*/
 
#include <stdio.h>      // for printf/fflush 
#include <stdlib.h>		// for strtod()... 
#include <sys/signal.h>	// for sigalarm
#include <sys/time.h>	// for timer and itimer
#include <pthread.h>	// for thread creation and thread priority management
#include <sched.h>		// for scheduler choice (FIFO or RR for Real-Time Applications)
#include <errno.h>		// to test error value
#include <sys/types.h>	// for classic types (int8_t...)
#include <unistd.h>		// for getpid()	
#include "rtwtypes.h"       	// MathWorks types 
#include "time_tools.h"			// Clock and delay customized tools 
#include "defines_verdex.h"		// specific gumstix defines
#include "ThreadLibrary.h"
#include "CpuTools.h"

#ifdef XENOMAI
	// specific Xenomai's includes
	#include <sys/mman.h> 	// for mlockall
	#include <signal.h>		// for SIGXCPU
	#include <time.h>		// for timespec
	#include <getopt.h>
	#include <execinfo.h>	// for backtrace

	#include <xenomai/rtdm/rtdm.h>
	#include <xenomai/native/task.h>
	#include <xenomai/rtdm/rtserial.h>
	#include <xenomai/rtdk.h>
	#include <xenomai/native/timer.h>
#endif
 
// specific model's includes
/****** Add here your specific models headers *****/
#include "COM_Prog_Rover.h"
	/***** UDP Header *****/
#include "library_udp.h" 			     /* Network udp headers */
	/***** UDP Header -END- *****/
 	
	/***** RS232 Header *****/
#include "library_rs232.h"				 /* Rs232 headers */
	/***** RS232 Header -END- *****/
 
/****** Add here your specific defines *****/
#define MY_SCHED_PRIO 96

/**************** Declaration of global variable *****************/
	// relative to time_tools
struct TicToc struc_TicToc[NB_SAMPLE_TIME];    	// to use tic() and toc() functions of time_tools.h
real_T rT_MyClock_s;			// to simulate a clock in secondes
real_T rT_TimeInit_s;			// to memorize initial time in second
	// debug file and pipe to send command to the system
FILE * FID_debug;				// to debug
FILE* FID_pipe;					// to upgrate process priority to max priority
#ifdef TASK_TIME_LOGGER
	FILE *FID_TimeLogger[NB_SAMPLE_TIME];
#endif
 
	// variables for execution time statistics
long long int FinalTime_us; 		// definition of final time in micro_seconds
struct timespec SimInit;				// to memorize initial simulation time 
unsigned long long int CurrentTimeLoop_us;	// to measure the current time
unsigned long long int SimCurrentTime_us;	// Simulation time in seconds
int StopAsked = 0, NbByteRead = 0, NbByteWrite = 0;
char OverRunStatus[NB_SAMPLE_TIME];
timer_t timerid = NULL;
//struct sigevent sev;;
	
	/*****  MULTI THREAD Global Variables *****/
pthread_t threads[NB_SAMPLE_TIME+1] = {0,0,0};     // an array to memorize thread's identifier (for signals emission)
unsigned long int SampleTimeList[NB_SAMPLE_TIME] = {2000000, 10000000};    // The sample time list in nano-seconds
struct timespec t_start[NB_SAMPLE_TIME];   // The time corresponding to task beginning
float ExecTimeLoop_ms[NB_SAMPLE_TIME]   = {0.0,0.0};   // The execution time of each task
float min_exec_time_ms[NB_SAMPLE_TIME]  = {0.0,0.0};   // The minimum execution time of each task
float max_exec_time_ms[NB_SAMPLE_TIME]  = {0.0,0.0};   // The maximum execution time of each task
float mean_exec_time_ms[NB_SAMPLE_TIME] = {0.0,0.0};   // The mean execution time of each task
float TotalExecTime_avg[NB_SAMPLE_TIME] = {0.0,0.0};   // The mean execution time+wait of each task
unsigned long int nb_ticks[NB_SAMPLE_TIME] = {0,0}; // How many time each task was executed
unsigned int TaskSubFreq[NB_SAMPLE_TIME+1] = {1, 5,500};   // Task frequency with respect to the base rate
int OverRun[NB_SAMPLE_TIME] = {0,0};                // how many overruns occured for each task
	/*****  MULTI THREAD Global Variables -END- *****/
	/***** UDP Global Variables *****/
	// remote peer configuration
struct sockaddr_in receptionRemote_info[NB_RECP_UDP];
struct sockaddr_in emissionRemote_info[NB_EMI_UDP];
	// local configuration
struct sockaddr_in local_info[NB_SOCK_UDP];
	// local sockets
int sk[NB_SOCK_UDP];
const char *interface[NB_SOCK_UDP]={"wlan0"};
unsigned short localPort[NB_SOCK_UDP]={2012};
char localIP[NB_SOCK_UDP][IP_LENGTH]={"000.000.000.000"};
const char *receptionRemoteIP[NB_RECP_UDP]={"192.168.137.3"};
unsigned short receptionRemotePort[NB_RECP_UDP]={2012};
unsigned int receptionUDPblockingTime[NB_RECP_UDP]={100000};
const char *emissionRemoteIP[NB_EMI_UDP]={"192.168.137.3"};
unsigned short emissionRemotePort[NB_EMI_UDP]={2012};
	/***** UDP Global Variables -END- *****/
		
	/***** RS232 Global Variables *****/
int ComPortNum = 0;
int BaudRate = 115200;
	/***** RS232 Global Variables -END- *****/
	
/*************** Function's protoypes declaration ****************/
void rt_OneStep(int sig);									// execute one step of simulink code 
void ArgumentsProcess(int_T argc, const char_T *argv[]);	// check arguments validity and do the needed initializations
void CreateBaseRateTimer(unsigned long int period_in);		// create a thread which will call the base rate task
void terminateProperly(int sig);	// a temination function allowing to free all resources
void ComputeCPU(void);				// to compute the CPU load
int FileGetLine(char *buf, int n, FILE * fd); // to get one line of a file
void lli2timeStr(char timeStr[100], long long int nbSec);
   
/*************** Termination function ****************/
void terminateProperly(int sig)
{
	unsigned int i, threadID_start;
	int error;
	
	// define the first thread that must be deleted as Task_0
	#ifdef XENOMAI
		threadID_start = 0;		// Task_0 is created by pthread_create() so it must be deleted
	#else
		threadID_start = 1;
		// do not rearm the main task
		signal(SIGALRM, SIG_IGN);
		if (timerid!=NULL)
		{
			timer_delete(timerid);
		}
	#endif	
	
	if (sig == 0)
	{
		printf("SIMULATION TERMINATE!!!\n");
		fflush(stdout);
		fprintf(FID_debug, "SIMULATION TERMINATE!!!\n");
	}
	else
	{
		printf("\t GumSim Program Aborted by User!\n\n");
		fflush(stdout);
		fprintf(FID_debug,"\t GumSim Program Aborted by User!\n\n");
	}
	
	pthread_t threadThis = pthread_self();
	
	// terminate immedialtly all the subtask
	for (i=threadID_start;i<NB_SAMPLE_TIME+1;i++)
	{
		if (!pthread_equal(threadThis,threads[i])) {
			error = pthread_cancel(threads[i]);
			if(!error)
			{
				printf ("Terminating Task %d... ", i);
				fflush(stdout);
				error = pthread_join(threads[i], NULL);
				switch(error)
				{
					case 0:
						printf ("Done!\n");
						break;
					case EDEADLK:
						printf("\tERROR: A deadlock was detected; or %d specifies the calling thread\n", (int)threads[i]);
						fflush(stdout);
						break;
					case EINVAL:
						printf("\tERROR: %d is not a joinable thread or Another thread is already waiting to join with this thread\n", (int)threads[i]);
						fflush(stdout);
						break;
					case ESRCH:
						printf("\tERROR: No thread with the ID %d could be found\n", (int)threads[i]);
						fflush(stdout);
						break;
				}
			}
			else
			{
				printf("\tERROR: No thread with the ID %d could be found\n", (int)threads[i]);
				fflush(stdout);
			}	
		}
	}
	// print the statistics of each task
	printf("\t STATISTICS:\n");
	fflush(stdout);
	fprintf(FID_debug,"\t STATISTICS:\n");
	for (i=0;i<NB_SAMPLE_TIME;i++)
	{
		printf("\t\t TASK %d (%.3f [ms])\n", i, (float)SampleTimeList[i]/1000000.0);
		printf("\t\t\t OverRun(s): %d/%lu ticks \n", OverRun[i], nb_ticks[i]); 
		fflush(stdout);
		fprintf(FID_debug,"\t\t\t OverRun(s): %d/%lu ticks \n", OverRun[i], nb_ticks[i]); 
		printf("\t\t\t min execution time: %.6f [ms]\n", min_exec_time_ms[i]);
		fflush(stdout);
		fprintf(FID_debug,"\t\t\t min execution time: %.6f [ms]\n", min_exec_time_ms[i]);
		printf("\t\t\t max execution time: %.6f [ms]\n", max_exec_time_ms[i]);
		fflush(stdout);
		fprintf(FID_debug,"\t\t\t max execution time: %.6f [ms]\n", max_exec_time_ms[i]);
		printf("\t\t\t mean execution time: %.6f [ms]\n", mean_exec_time_ms[i]);
		fflush(stdout);
		fprintf(FID_debug,"\t\t\t mean execution time: %.6f [ms]\n", mean_exec_time_ms[i]);
		printf("\t\t\t TotalExecTime+Wait = %.6f [ms]\n", TotalExecTime_avg[i]/1000.0);
		fflush(stdout);
		fprintf(FID_debug,"\t\t\t TotalExecTime+Wait = %.6f [ms]\n", TotalExecTime_avg[i]/1000.0);
	}
	
	/***** STOP SYNCHRONIZATION PROTOCOL *****/
	/***** STOP SYNCHRONIZATION PROTOCOL -END- *****/
	
	/***** TURN OFF HERE THE UDP *****/
	// close sockets
	for(i=0; i<NB_SOCK_UDP; i++)
	{
		close(sk[i]);
	}
	/***** TURN OFF HERE THE UDP -END- *****/
	
	/***** TURN OFF HERE THE RS232 *****/
	// close RS232
	printf("closing RS232 ports...\n");
	fflush(stdout);
	CloseComPort(ComPortNum);
	printf("DONE!\n");
	fflush(stdout);
	/***** TURN OFF HERE THE RS232 -END- *****/
	
	#ifdef TASK_TIME_LOGGER
		/***** CLOSE HERE THE TIME LOG FILES *****/
		for (i=0;i<NB_SAMPLE_TIME;i++)
		{
			fclose(FID_TimeLogger[i]);
		}
		/***** CLOSE HERE THE TIME LOG FILES -END- *****/
	#endif
	
	// close pipe
	pclose(FID_pipe);
	// close debug file
	fclose(FID_debug);
	
	exit(1);
}

// Function called when SIGXCPU signal is generated (switch of scheduler Xenomai/Linux)
#ifdef XENOMAI
	void SchedSwitchHandler(int sig __attribute__((unused)))
	{
	#if (defined ECHO_PRINTF || defined ECHO_FPRINTF)
		void *bt[32];
		int size, nentries;
		
		/* Dump a backtrace of the frame which caused the switch to
		   secondary mode: */
		size = sizeof(bt) / sizeof(bt[0]);
		nentries = backtrace(bt,size);	
		#ifdef ECHO_PRINTF
			backtrace_symbols_fd(bt,nentries,fileno(stdout));
		#endif
		#ifdef ECHO_FPRINTF
			backtrace_symbols_fd(bt,nentries,fileno(FID_debug));
		#endif
	#endif
	}
#endif
 
/***************** Sub Rate Functions *****************/
void *Task_1(void *threadid) // sample time: Ts = 0.01000 [s]
{
	int tid, sig, dt, i;
	tid = (int)threadid;
	struct timespec t1;
	float ExecTimeLoop_us;
	float TotalExecTime;
	sigset_t sigmask;
	int SigNum = SIGRTMIN+tid;
	
	#ifdef XENOMAI
		/* Ask Xenomai to warn us upon switches to secondary mode. */
		int error = rt_task_set_mode(0, T_WARNSW, NULL);
		switch (error) 
		{
			case -EINVAL:
				printf("ERROR: either setmask or clrmask specifies invalid bits. T_CONFORMING is always invalid in clrmask, or when applied in setmask to kernel-based tasks\n");
				break;
			case -EPERM:
				printf("ERROR: this service was not called from a real-time task context\n");
				break;
		}
	#endif
	
	// block all signals
	sigfillset(&sigmask);
	pthread_sigmask(SIG_BLOCK, &sigmask, (sigset_t*)0);
	// unblock SigNum
	sigemptyset(&sigmask);
	sigaddset(&sigmask, SigNum);
	pthread_sigmask(SIG_UNBLOCK, &sigmask, (sigset_t*)0);
	// redirect SigNum to terminate
	signal(SigNum, VoidTask);
	
	// display the property of the new thread
	printf("<THREAD %d> Successfully created with subrate %.2f [ms]\n", tid, (float)SampleTimeList[tid]/1000000.0);
	DisplayThread(tid);
	
	for(;;)
	{
		sigwait(&sigmask, &sig);
	
		if (sig == SigNum)
		{
			// get the time since the previous loop beginning
			clock_gettime(CLOCK_MONOTONIC, &t1);
			dt = (t1.tv_sec - t_start[tid].tv_sec) * 1000000
				   + (t1.tv_nsec - t_start[tid].tv_nsec)/1000;
			t_start[tid] = t1;
			TotalExecTime = (float)dt;	// time between this loop and the previous loop
			
			// OverRun management
			if (OverRunStatus[tid]==1)
			{
				printf("OVERRUN!!!! Task %d not run, waiting end of previous task...\n", tid);
			}
			else
			{
				OverRunStatus[tid]=1;
					/***** INPUTS ATTRIBUTION *****/
						/***** INPUT FROM RS232 ATTRIBUTION *****/
					#if (defined ECHO_PRINTF_TIME || defined ECHO_FPRINTF_TIME)
						tic("RS232_reception", tid);
					#endif
					NbByteRead = HeaderRead_RS232(ComPortNum, COM_Prog_Rover_U.In_from_Serial2, 6*NB_BYTE_UCHAR8, 174);
					#if (defined ECHO_PRINTF_TIME || defined ECHO_FPRINTF_TIME)
						toc(tid);
					#endif
					#if (defined ECHO_PRINTF || defined ECHO_FPRINTF)
						if (NbByteRead > 0) {
							for (i = 0; i < NbByteRead/NB_BYTE_UCHAR8; i++) {
								#ifdef ECHO_PRINTF
									printf("<RS232> Received[%d] = %u\n", i, COM_Prog_Rover_U.In_from_Serial2[i]);
								#endif
								#ifdef ECHO_FPRINTF
									fprintf(FID_debug, "<RS232> Received[%d] = %u\n", i, COM_Prog_Rover_U.In_from_Serial2[i]);
								#endif
							}
						}
					#endif
					/***** INSERT HERE THE SPECIFIC TASK *****/
					#if (defined ECHO_PRINTF_TIME || defined ECHO_FPRINTF_TIME)
						tic("Step_1", tid);
					#endif
						COM_Prog_Rover_step1();
					#if (defined ECHO_PRINTF_TIME || defined ECHO_FPRINTF_TIME)
						toc(tid);
					#endif
					/***** OUPUTS ATTRIBUTION *****/
						/***** OUTPUT TO RS232 ATTRIBUTION *****/
					#if (defined ECHO_PRINTF_TIME || defined ECHO_FPRINTF_TIME)
						tic("RS232_send", tid);
					#endif
					NbByteWrite = HeaderWrite_RS232(ComPortNum, &COM_Prog_Rover_Y.Out_to_Serial1, 1*NB_BYTE_UINT16, 174);
					#if (defined ECHO_PRINTF_TIME || defined ECHO_FPRINTF_TIME)
						toc(tid);
					#endif
					#if (defined ECHO_PRINTF || defined ECHO_FPRINTF)
						if (NbByteWrite > 0) {
							for (i = 0; i < NbByteWrite/NB_BYTE_UINT16; i++) {
								#ifdef ECHO_PRINTF
									printf("<RS232> Sent[%d] = %d\n", i, COM_Prog_Rover_Y.Out_to_Serial1[i]);
								#endif
								#ifdef ECHO_FPRINTF
									fprintf(FID_debug, "<RS232> Sent[%d] = %d\n", i, COM_Prog_Rover_Y.Out_to_Serial1[i]);
								#endif
							}
						}
					#endif
				OverRunStatus[tid]=0;
			}
			// get the task's execution time
			dt = (t1.tv_sec - t_start[tid].tv_sec) * 1000000
				   + (t1.tv_nsec - t_start[tid].tv_nsec)/1000;
			ExecTimeLoop_us = (float)dt; // memorize the execution time of this loop (add the statistics execution time)
			ExecTimeLoop_ms[tid] = ExecTimeLoop_us/1000.0; 				 // memorize end time for previous loop
			
			#ifdef TASK_TIME_LOGGER
				if(FID_TimeLogger[tid] != -1)
				{
					fprintf(FID_TimeLogger[tid],"%f;%f;%f;%llu\n", TotalExecTime, ExecTimeLoop_us, CpuAvg[3], SimCurrentTime_us/1000);
				}	
			#endif
			
			if (nb_ticks[tid] == 0)
			{
				nb_ticks[tid]++;
				min_exec_time_ms[tid] = ExecTimeLoop_ms[tid];
				max_exec_time_ms[tid] = ExecTimeLoop_ms[tid];
				mean_exec_time_ms[tid] = ExecTimeLoop_ms[tid];
			}
			else
			{
				if (ExecTimeLoop_ms[tid] < min_exec_time_ms[tid])
					min_exec_time_ms[tid] = ExecTimeLoop_ms[tid];
				if (ExecTimeLoop_ms[tid] > max_exec_time_ms[tid])
					max_exec_time_ms[tid] = ExecTimeLoop_ms[tid];
				mean_exec_time_ms[tid] = (mean_exec_time_ms[tid]*nb_ticks[tid] + ExecTimeLoop_ms[tid])/((float)(nb_ticks[tid]+1));
				TotalExecTime_avg[tid] = (TotalExecTime_avg[tid]*nb_ticks[tid] + TotalExecTime)/((float)(nb_ticks[tid]+1));
				nb_ticks[tid]++;
			}
			
			#if (defined(ECHO_PRINTF) || defined(ECHO_PRINTF_TIME))
				printf("TASK %d: Previous Loop execution time: %.3f/%.3f [ms]\n", tid, ExecTimeLoop_ms[tid], (float)SampleTimeList[tid]/1000000.0);
			#endif
			#if (defined(ECHO_FPRINTF) || defined(ECHO_FPRINTF_TIME))
				fprintf(FID_debug, "TASK %d: Previous Loop execution time: %.3f/%.3f [ms]\n", tid, ExecTimeLoop_ms[tid], (float)SampleTimeList[tid]/1000000.0);
			#endif
			
			if (ExecTimeLoop_us>=SampleTimeList[tid]/1000)
			{
				OverRun[tid]++;
				printf("\t\tOVERRUN!!!! Task %d Total Time: %.3f/%.3f [ms]\n", tid, ExecTimeLoop_ms[tid], (float)SampleTimeList[tid]/1000000.0);
				
				#ifdef ECHO_FPRINTF
					fprintf(FID_debug, "TASK %d (%.3f [ms])\n", tid, (float)SampleTimeList[tid]/1000000.0);
					fprintf(FID_debug,"\t statistics:\n");
					fprintf(FID_debug,"\t\tOVERRUN!!!! Task %d Total Time: %.3f/%.3f [ms]\n", tid, ExecTimeLoop_ms[tid], (float)SampleTimeList[tid]/1000000.0);
					fprintf(FID_debug,"\t\t min execution time: %.6f [ms]\n", min_exec_time_ms[tid]);
					fprintf(FID_debug,"\t\t max execution time: %.6f [ms]\n", max_exec_time_ms[tid]);
					fprintf(FID_debug,"\t\t mean execution time: %.6f [ms]\n", mean_exec_time_ms[tid]);
					fprintf(FID_debug,"\t\t TotalExecTime+Wait = %.6f [ms]\n", TotalExecTime_avg[tid]/1000.0);
				#endif
				
				#ifdef ECHO_PRINTF
					printf("---------------------------\n");
				#endif
				#ifdef ECHO_FPRINTF
					fprintf(FID_debug, "---------------------------\n");
				#endif
			}
			sched_yield();
		}
	}
}
 
/***************** Function's body declaration *******************/
#ifdef XENOMAI
	void *Task_0(void *threadid)
#else
	void Task_Rate0(int sig)
#endif	
{
	/***** DECLARATION OF MULTI_TASK FLAGS *****/
	static unsigned int TaskCount[NB_SAMPLE_TIME+1] = {0, 0, 0};
	//struct timeval t1;
	struct timespec t1;
	float ExecTimeLoop_us;
	float TotalExecTime;
	int dt, i, tid = 0;	// thread 0
	
	#ifdef XENOMAI
		struct timespec start, period;
		unsigned long overrun;
		
		DisplayThread(tid);
	
		/* Ask Xenomai to warn us upon switches to secondary mode. */
		int error = rt_task_set_mode(0, T_WARNSW, NULL);
		switch (error) 
		{
			case -EINVAL:
				printf("ERROR: either setmask or clrmask specifies invalid bits. T_CONFORMING is always invalid in clrmask, or when applied in setmask to kernel-based tasks\n");
				break;
			case -EPERM:
				printf("ERROR: this service was not called from a real-time task context\n");
				break;
		}
		
		clock_gettime(CLOCK_MONOTONIC, &start);
		start.tv_sec += 1;
		period.tv_sec = 0;
		period.tv_nsec = SampleTimeList[0];
		
		error = pthread_make_periodic_np(pthread_self(), &start, &period);
		
		for (;;) {
		
			overrun = 0;
			error = pthread_wait_np(&overrun);
			if(overrun)
				rt_printf("Task1: OVERRUN\n");
			if(error)
			{
				rt_printf("Task1: ERROR %d\n", error);
				//exit(EXIT_FAILURE);
			}
	#endif
	
	// get the current time in [us]
	clock_gettime(CLOCK_MONOTONIC, &t1);
	CurrentTimeLoop_us = (long int)(t_start[tid].tv_sec - SimInit.tv_sec) * (long int)1000000
							+ (long int)((t_start[tid].tv_nsec - SimInit.tv_nsec)/1000);
	// get the time since the previous loop beginning
	dt = (t1.tv_sec - t_start[tid].tv_sec) * 1000000
		   + (t1.tv_nsec - t_start[tid].tv_nsec)/1000;
	t_start[tid] = t1;
	TotalExecTime = (float)dt;	// time between this loop and the previous loop
	
	if (dt>2*GUMSTIX_SAMPLE_TIME_US)
	{
		OverRun[tid]++;
		printf("\t\tInterval Timer OVERRUN!!!! Task %d Interval: %.3f/%.3f [ms]\n", 0, TotalExecTime/1000.0, (float)SampleTimeList[tid]/1000000.0);
	}
	
	// get the current simulation time
	SimCurrentTime_us = (unsigned long long int)nb_ticks[tid]*(unsigned long long int)SampleTimeList[tid];
	
	#if (defined ECHO_PRINTF || defined ECHO_FPRINTF)
		#if (defined(ECHO_PRINTF) || defined(ECHO_PRINTF_TIME))
			printf("Current Time: %.3f [ms]\n", (double)(CurrentTimeLoop_us)/1000.0);
		#endif
		#if (defined(ECHO_FPRINTF) || defined(ECHO_FPRINTF_TIME))
			fprintf(FID_debug, "Current Time: %.3f [ms]\n", (double)(CurrentTimeLoop_us)/1000.0);
		#endif
	#endif
	
	/***** SUB-TASK MANAGEMENT *****/
	for (i=1;i<NB_SAMPLE_TIME+1; i++)
	{
		TaskCount[i]++;
		// if task need to be done
		if (TaskCount[i] >= TaskSubFreq[i])
		{
			// Reset task counter
			TaskCount[i] = 0;
			// Ask to the corresponding thread to do the task
			pthread_kill(threads[i], SIGRTMIN+i);
		}
	}
	/***** SUB-TASK MANAGEMENT -END- *****/
	
	/***** INPUTS ATTRIBUTION *****/
		/***** INPUT FROM UDP ATTRIBUTION *****/
	#if (defined ECHO_PRINTF_TIME || defined ECHO_FPRINTF_TIME)
		tic("UDP_reception", tid);
	#endif
	ReadLastnFloat_UDP(sk[0], &receptionRemote_info[0], &COM_Prog_Rover_U.In_from_UDP2, 26);
	#if (defined ECHO_PRINTF_TIME || defined ECHO_FPRINTF_TIME)
		toc(tid);
	#endif
	

	/***** STEP MODEL HERE *****/
	#if (defined ECHO_PRINTF_TIME || defined ECHO_FPRINTF_TIME)
		tic("StepBaseRate", tid);
	#endif
	COM_Prog_Rover_step0();
	#if (defined ECHO_PRINTF_TIME || defined ECHO_FPRINTF_TIME)
		toc(tid);
	#endif

	/***** OUPUTS ATTRIBUTION *****/
		/***** OUTPUT TO UDP ATTRIBUTION *****/
	#if (defined ECHO_PRINTF_TIME || defined ECHO_FPRINTF_TIME)
		tic("UDP_send", tid);
	#endif
	SendnFloat_UDP(sk[0], &emissionRemote_info[0], COM_Prog_Rover_Y.Out_to_UDP1, 20);
	#if (defined ECHO_PRINTF_TIME || defined ECHO_FPRINTF_TIME)
		toc(tid);
	#endif
	
	
	// get the task's execution time
	clock_gettime(CLOCK_MONOTONIC, &t1);
	dt = (t1.tv_sec - t_start[tid].tv_sec) * 1000000
		   + (t1.tv_nsec - t_start[tid].tv_nsec)/1000;
	ExecTimeLoop_us = (float)dt; // memorize the execution time of this loop (add the statistics execution time)
	ExecTimeLoop_ms[tid] = ExecTimeLoop_us/1000.0; 				 // memorize end time for previous loop
	
	#ifdef TASK_TIME_LOGGER
		if(FID_TimeLogger[tid] != -1)
		{
			fprintf(FID_TimeLogger[tid],"%f;%f;%f;%llu\n", TotalExecTime, ExecTimeLoop_us, CpuAvg[3], SimCurrentTime_us/1000);
		}
	#endif
	
	if (nb_ticks[tid] == 0)
	{
		nb_ticks[tid]++;
		min_exec_time_ms[tid] = ExecTimeLoop_ms[tid];
		max_exec_time_ms[tid] = ExecTimeLoop_ms[tid];
		mean_exec_time_ms[tid] = ExecTimeLoop_ms[tid];
	}
	else
	{
		if (ExecTimeLoop_ms[tid] < min_exec_time_ms[tid])
			min_exec_time_ms[tid] = ExecTimeLoop_ms[tid];
		if (ExecTimeLoop_ms[tid] > max_exec_time_ms[tid])
			max_exec_time_ms[tid] = ExecTimeLoop_ms[tid];
		mean_exec_time_ms[tid] = (mean_exec_time_ms[tid]*nb_ticks[tid] + ExecTimeLoop_ms[tid])/((double)(nb_ticks[tid]+1));
		TotalExecTime_avg[tid] = (TotalExecTime_avg[tid]*nb_ticks[tid] + TotalExecTime)/((double)(nb_ticks[tid]+1));
		nb_ticks[tid]++;
	}
	
	#if (defined(ECHO_PRINTF) || defined(ECHO_PRINTF_TIME))
		printf("TASK %d: Previous Loop execution time: %.3f/%.3f [ms]\n", tid, ExecTimeLoop_ms[tid], (float)SampleTimeList[tid]/1000000.0);
		printf("---------------------------\n");
		fflush(stdout);
	#endif
	#if (defined(ECHO_FPRINTF) || defined(ECHO_FPRINTF_TIME))
		fprintf(FID_debug, "TASK %d: Previous Loop execution time: %.3f/%.3f [ms]\n", tid, ExecTimeLoop_ms[tid], (float)SampleTimeList[tid]/1000000.0);
		fprintf(FID_debug, "---------------------------\n");
		//fflush(FID_debug);
	#endif
	
	if (ExecTimeLoop_us>=GUMSTIX_SAMPLE_TIME_US)
	{
		OverRun[tid]++;
		printf("\t\tOVERRUN!!!! Task %d Total Time: %.3f/%.3f [ms]\n", 0, ExecTimeLoop_ms[tid], (float)SampleTimeList[tid]/1000000.0);
		#ifdef ECHO_FPRINTF
			fprintf(FID_debug,"TASK %d (%.3f [ms])\n", 0, (float)SampleTimeList[tid]/1000000.0);
				fprintf(FID_debug,"\t statistics:\n");
				fprintf(FID_debug,"\t\tOVERRUN!!!! Task %d Total Time: %.3f/%.3f [ms]\n", 0, ExecTimeLoop_ms[tid], (float)SampleTimeList[tid]/1000000.0);
				fprintf(FID_debug,"\t\t min execution time: %.6f [ms]\n", min_exec_time_ms[tid]);
				fprintf(FID_debug,"\t\t max execution time: %.6f [ms]\n", max_exec_time_ms[tid]);
				fprintf(FID_debug,"\t\t mean execution time: %.6f [ms]\n", mean_exec_time_ms[tid]);
				fprintf(FID_debug,"\t\t TotalExecTime+Wait = %.6f [ms]\n", TotalExecTime_avg[tid]/1000.0);
		#endif
		
		#ifdef ECHO_PRINTF
			printf("---------------------------\n");
		#endif
		#ifdef ECHO_FPRINTF
			fprintf(FID_debug, "---------------------------\n");
		#endif
	}
	dt = (t_start[0].tv_sec - SimInit.tv_sec) * 1000000
		+ (t_start[0].tv_nsec - SimInit.tv_nsec)/1000;
					   
	if(( dt > FinalTime_us ) || StopAsked != 0)
	{
		terminateProperly(0);
	}
	
	#ifdef XENOMAI
		}	// to close for (;;) {
	#endif
	sched_yield();
}
 
int_T main(int_T argc, const char_T *argv[])
{
	/***** VARIABLES DECLARATIONS *****/
	char commandName[255];
	char get_pid[255];
	int i;
	int WaitCondition = 0;
	struct sigaction IntAction;
	char timeStr[100];
	#ifdef TASK_TIME_LOGGER
		char FileName[50];
	#endif
	
	// Check the arguments, and update configurations if needed
	ArgumentsProcess(argc, argv);
	
	/***** INITIALISATIONS *****/
	
	printf("INITIALISATION...\n");
	
	#ifdef XENOMAI   
		/* no memory-swapping for this programm (needed for Xenomai!) */
		int error = mlockall(MCL_CURRENT | MCL_FUTURE);
		if (error) {
			perror("ERROR : mlockall has failled");
			exit(1);
		}
		
		/* Ask Xenomai to warn us upon switches to secondary mode. */
		error = rt_task_set_mode(0, T_WARNSW, NULL);
		switch (error) 
		{
			case -EINVAL:
				printf("ERROR: either setmask or clrmask specifies invalid bits. T_CONFORMING is always invalid in clrmask, or when applied in setmask to kernel-based tasks\n");
				break;
			case -EPERM:
				printf("ERROR: this service was not called from a real-time task context\n");
				break;
		}
		
		signal(SIGXCPU, SchedSwitchHandler);	// redirect SIGXCPU to SchedSwitchHandler()
	#else
		struct sigaction TimerAction;
		struct sched_param schedp;
		struct itimerspec BaseRateTimer;
	#endif
	
	/***** OPEN FILE *****/	
	FID_debug = fopen("COM_Prog_Rover_debug.debug","w");
	if (FID_debug != NULL)
	{
		printf("\t Debug File successfully created!!!\n");
		fprintf(FID_debug, "\t Debug File successfully created!!!\n");
	}
	else
	{
		printf("\t Debug File creation error!!!\n");
	}
	
	// echo the chosen configuration
	printf("--------------------- CHOSEN CONFIGURATION ---------------------\n\n");
	lli2timeStr(timeStr, FinalTime_us);
	printf("\t Simulation duration:   %s (%.6f [s])\n", timeStr, ((double)FinalTime_us)/1000000.0);
	
	#ifdef TASK_TIME_LOGGER
		for (i=0;i<NB_SAMPLE_TIME;i++)
		{
			sprintf(FileName, "./TimeLogger/TimeLogger_Task%d.csv", i);
			FID_TimeLogger[i] = fopen(FileName, "w");
			fprintf(FID_TimeLogger[i], "Time Log for the Task %d with SampleTime %lu [us]\n\n", i, SampleTimeList[i]);
		}
	#endif
	
	/***** TURN ON HERE THE UDP *****/
	// initialize the emission:
	// 		create the sockaddr_in structure corresponding to the remote peer (IP, PORT)
	for (i=0; i<NB_EMI_UDP; i++)
	{
		initUDPremote(&emissionRemote_info[i], emissionRemoteIP[i], emissionRemotePort[i]);
	}
	// initialize all the local sockets
	for (i=0; i<NB_SOCK_UDP; i++)
	{
		printf("<UDP> Configuring Socket %d of interface '%s':\n", i, interface[i]);
		getAddressOfInterface(interface[i], localIP[i]);	// use ip address of wished interface
		initUDPlocalSocket(&local_info[i], &sk[i], localIP[i], localPort[i]);	
	}
	/***** TURN ON HERE THE UDP -END- *****/
	printf("<RS232> \t COM port number: \t1\n");
	printf("<RS232> \t\t COM device: \t%s\n", comPorts[ComPortNum]);
	printf("<RS232> \t\t BaudRate  : \t%d\n",BaudRate);
	// initialize Serial connection
	initCOMconnection(ComPortNum, BaudRate);
	/***** TURN ON HERE THE RS232 -END- *****/
	
	// initialize the CPU monitoring
	InitCPU();
	
	// redirect SIGINT to terminateProperly()
	IntAction.sa_handler = terminateProperly;
    sigemptyset (&IntAction.sa_mask);
    IntAction.sa_flags = 0;
	
	sigaction(SIGINT, &IntAction, NULL);
	
	// assign highest priority to process
	printf("<SCHED> Assign to the program the highest priority...\n");
	fflush(stdout);
	sprintf(commandName, "pidof %s", argv[0]);
	FID_pipe = popen(commandName,"r");
	fgets(get_pid,255,FID_pipe); 
	sprintf(commandName, "renice -20 %s", get_pid);
	system(commandName);
	system("cpufreq-set -f 1000MHz");
	
	#ifdef TASK_TIME_LOGGER
		sprintf(commandName, "top -n %ld -d 1 -b 1>./TimeLogger/top-output.txt&", (long int)(FinalTime_us/1000000 + 2));
		printf("<CPU> CPU Monitoring activated!\n \t=> Logged in 'top-output.txt'\n");
		system(commandName);
	#endif
	
	sleep(1);
	
    /* Initialize model */
	COM_Prog_Rover_initialize();
    rT_TimeInit_s = s_time();
	
	int success;
	/***** CREATE ALL SUB RATE TASK *****/
	printf("<SCHED> Creation of thread 2\n");
	success = CreateMyThread(&threads[1], Task_1, (void *)1, SCHED_RR, MY_SCHED_PRIO-1); 
	if(success==0)
	{
	printf("<SCHED> Creation of thread 2 FAILED!\n");
		exit(-1);
	}
	printf("<SCHED> Creation of thread 2\n");
	success = CreateMyThread(&threads[2], DisplayTask, (void *)2, SCHED_RR, 1); 
	if(success==0)
	{
	printf("<SCHED> Creation of thread 2 FAILED!\n");
		exit(-1);
	}
	
    /***** SIMULATE MODEL BEHAVIOUR IN REAL TIME *****/
	
	/***** START SYNCHRONIZATION PROTOCOL *****/
	CleanBothRS232(ComPortNum);
		// send a start stream
	SendStartStream_RS232(ComPortNum, "START");
		// wait the first stream and check its validity
	WaitCondition |= WaitStartStream_RS232(ComPortNum, "START", 100);
	
	if (WaitCondition != -1)
	{
		/***** CREATE Task_Rate0 HERE *****/
		
		schedp.sched_priority = MY_SCHED_PRIO;
		sched_setscheduler(0, SCHED_RR, &schedp);
		
		
		TimerAction.sa_handler = &Task_Rate0;
		sigemptyset(&TimerAction.sa_mask);
		TimerAction.sa_flags = 0;
		
		BaseRateTimer.it_value.tv_sec = SampleTimeList[0] / 1000000000;
		BaseRateTimer.it_value.tv_nsec = SampleTimeList[0] % 1000000000;
		BaseRateTimer.it_interval.tv_sec = SampleTimeList[0] / 1000000000;
		BaseRateTimer.it_interval.tv_nsec = SampleTimeList[0] % 1000000000;
		
		timer_create(CLOCK_MONOTONIC, NULL, &timerid);
		sigaction(SIGALRM, &TimerAction, NULL);
		printf("THREAD 0 created for Base Rate %.2f [ms]\n", (float)SampleTimeList[0]/1000000.0);
		DisplayThread(0);
		timer_settime (timerid, 0, &BaseRateTimer, NULL);
		
		printf("SIMULATION BEGIN!!!\n");
		fflush(stdout);
		fprintf(FID_debug, "SIMULATION BEGIN!!!\n");
	
		// RUN SIMULATION
		clock_gettime(CLOCK_MONOTONIC, &SimInit);
		
		for (i=0; i<NB_SAMPLE_TIME; i++)
		{
			t_start[i] = SimInit;
		}
		
		for(;;)
		{
			pause(); // let the Task_Rate0 be executed at each timer expiration (SIGALRM)
		}
	}
	else
	{
		// REPORT ERROR
		printf("<RS232> StartStream_RS232 ERROR!\n\t -> Simulation abort\n");
		fprintf(FID_debug, "<RS232> StartStream_RS232 ERROR!\n\t -> Simulation abort\n");
	}
 
    /***** TERMINATE THE MODEL SIMULATION *****/
	    COM_Prog_Rover_terminate();
    
	terminateProperly(0);
	
    return 0;
}

void lli2timeStr(char timeStr[100], long long int nbSec)
{
	char str[5][4] = {"hrs", "min", "sec", "ms", "us"};
	long long int div[5] = {3600000000, 60000000, 1000000, 1000, 1};
	int i;
	char buf[10];
	
	strcpy(timeStr, "");
	for (i=0; i<5; i++)
	{
		if (i==0)
		{
			sprintf(buf, "%d", (int)(nbSec/div[i]) );
		}
		else
		{
			sprintf(buf, "%d", (int)((nbSec/div[i]) - (nbSec/div[i-1])*(div[i-1]/div[i])) );
		}	
		strcat(timeStr, buf);
		strcat(timeStr, str[i]);
		strcat(timeStr, " ");
	}
}
 
void ArgumentsProcess(int_T argc, const char_T *argv[])
{
	int i = 0;
	
	/********* HELP MENU *********/
	if (argc>=2)
	{
		if (!strcmp(argv[1],"-help")||!strcmp(argv[1],"-h"))
		{
			printf("SYNTAX: %s -opt <opt_value>\n\n",argv[0]);
			printf("Execute in real time the auto-generated program obtained from the MATLAB simulink model with modificatiuons given by 'opt'. ");
			printf("\t Valid 'opt' are:\n");
			printf("\t -h, -help: This Menu\n");
			printf("\t -d <duration_in_seconds>: Duration of the simulation in seconds\n");
			/***** UDP HELP *****/
			printf("\t -if <network_interface>: network interface to use (eth0, wlan0...)\n");
			printf("\t -ip <IP adress of remote UDP host>: Address of the remote host with which udp stream are exchanged. ie: 192.168.1.2\n");
			printf("\t -port <UDP_PORT>: Number of port used for udp protocol (0<UDP_PORT<65535)\n");
			/***** UDP HELP -END- *****/
			/***** RS232 HELP *****/
			printf("\t -com <COM_PORT>: Number of COM Port used to dialog with an other board (0<COM_PORT<2 for the Gumstix Overo or Verdex XL6P)\n");
			printf("\t                  if your application features more than 1 com port, the -com option will modify the first com port\n");
			printf("\t -baud <COM_BAUD_RATE>: Baudrate in baud per second for COM Port <COM_PORT>\n");
			printf("\t                  if your application features more than 1 com port, the -baud option will modify the first com port\n");
			/***** RS232 HELP -END- *****/
			exit(0);
		}
	}
	/*****************************/
	
	while (i<(argc-1))
	{
		i++;
		if(!strcmp(argv[i], "-d" ))
		{
			// check validity of next argument
			i++;
			if (i<=(argc-1))
			{
				FinalTime_us = (long long int)(atof( argv[i] )*(double)1000000.0);
				//printf("duration: %f, %lld\n", atof( argv[i] ), (long long int)(atof( argv[i] )*1000000.0) );
				if (FinalTime_us < 0)
				{
					printf("Invalid duration %f second! Must be greater than 0.0\n", atof( argv[i] ));
					exit(1);
				}
			}	
			else
			{
				printf("Option '-d' have to be followed by a valid duration [s] (ex: 10, 3600, 0.001)!\n");
				exit(1);
			}	
		}
		/***** UDP ARGUMENT *****/
		else if(!strcmp(argv[i], "-if" ))
		{
			// check validity of next argument
			i++;
			if (i<=(argc-1))
			{
				interface[0] = argv[i];
				if ((strcmp(interface[0], "eth0"))&&(strcmp(interface[0], "wlan0")))
				{
					printf("Invalid UDP interface!\n");
					exit(1);
				}
			}	
			else
			{
				printf("Option '-if' have to be followed by a valid UDP interface (ex: wlan0, eth0)!\n");
				exit(1);
			}	
		}
		else if(!strcmp(argv[i], "-ip" ))
		{
			// check validity of next argument
			i++;
			if (i<=(argc-1))
			{
				receptionRemoteIP[0] = argv[i];
				emissionRemoteIP[0] = argv[i];
				if (!isValidIP(receptionRemoteIP[0]))
				{
					printf("Invalid IPv4 address format!\n");
					exit(1);
				}
			}
			else
			{
				printf("Option '-ip' have to be followed by a valid IP address (ex: 192.1683.137.1)!\n");
				exit(1);
			}
		}
		else if(!strcmp(argv[i], "-port" ))
		{
			// check validity of next argument
			i++;
			if (i<=(argc-1))
			{
				receptionRemotePort[0] = (unsigned short) strtoul(argv[i], NULL, 0);
				emissionRemotePort[0] = receptionRemotePort[0];
				if (receptionRemotePort[0] < 1024)	// (port > 65535) always false as port is short
				{
					printf("Invalid UDP port! Have to be 1023<port<65536\n");
					exit(1);
				}
			}
			else
			{
				printf("Option '-port' have to be followed by a valid UDP port (ex: 2012)!\n");
				exit(1);
			}
		}
		/***** UDP ARGUMENT -END- *****/
		/***** RS232 ARGUMENT *****/
		else if(!strcmp(argv[i], "-com" ))
		{
			// check validity of next argument
			i++;
			if (i<=(argc-1))
			{
				/***** Recover ComPort Argument here *****/
				ComPortNum = (int)strtol(argv[i],NULL,10);
				if ((ComPortNum < 0)||(ComPortNum > 2))
				{
					printf("Invalid ComPort! Have to be 0<=ComPort<=2\n");
					exit(1);
				}
			}
			else
			{
				printf("Option '-com' have to be followed by a valid ComPort (ex: 0, 1 or 2)!\n");
				exit(1);
			}
		}
		else if(!strcmp(argv[i], "-baud" ))
		{
			// check validity of next argument
			i++;
			if (i<=(argc-1))
			{
				/***** Recover BaudRate Argument here *****/
				BaudRate = (int)strtol(argv[i],NULL,10);
				switch(BaudRate)
				{
					case      75:
					case     150:
					case     600:
					case    1200:
					case    1800:
					case    2400:
					case    4800:
					case    9600:
					case   19200:
					case   38400:
					case   57600:
					case  115200:
					case  230400:
					case  460800:
					case  921600:
					case 1000000:
					case 1843200:
					case 3000000:
					case 3686400:
						break;
					default :
						printf("\t Invalid baudrate: '%d'.\n\t Must be '75,150,600,1200,1800,2400,4800,9600,19200,38400,57600,115200,230400,460800,921600,1000000,1843200,3000000,3686400.'\n", BaudRate);
						exit(1);
						break;
				}
			}
			else
			{
				printf("Option '-baud' have to be followed by a valid BaudRate (ex: 115200)!\n");
				exit(1);
			}
		}
		/***** RS232 ARGUMENT -END- *****/
	}
}
 
