#ifndef library_thread_h
#define library_thread_h

	#include <stdlib.h>
	#include <unistd.h>
	#include <stdio.h>
	#include <signal.h>
	#include <time.h>
	#include <errno.h>		// to test error value
	#include <pthread.h>	// for thread creation and thread priority management
	
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

	int CreateMyThread(pthread_t *thread, void *(*start_routine) (void *), void *arg, int policy, int priority);
	void VoidTask(int sig);
	void DisplayThread(int taskID);
	void *DisplayTask(void *threadid);
	
	extern unsigned long long int SimCurrentTime_us;	// Simulation time in seconds
	
#endif
