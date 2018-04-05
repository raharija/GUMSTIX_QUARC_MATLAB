#include "ThreadLibrary.h"
#include "CpuTools.h"

void DisplayThread(int taskID)
{
	int error;
	int policy;
	struct sched_param schedp;
	char Prefix[13];
	
	sprintf(Prefix, "<THREAD %d>", taskID);
	
	error = pthread_getschedparam(pthread_self(), &policy, &schedp); 
	switch (error)
	{
		case ESRCH:
			printf("<THREAD> No thread with the ID thread could be found!\n");
			break;
		case EINVAL:
			printf("<THREAD> policy is not a recognized policy, or param does not make sense for the policy!\n");
			break;
		case EPERM:
			printf("<THREAD> The caller does not have appropriate privileges to set the specified scheduling policy and parameters!\n");
			break;
	}   
	printf("%s Thread Task #%d description:\n", Prefix, taskID); 
	switch(policy)
	{
		case SCHED_FIFO:
			printf("%s \tPolicy: SCHED_FIFO\n", Prefix); 
			break;
		case SCHED_RR:
			printf("%s \tPolicy: SCHED_RR\n", Prefix); 
			break;
		default:
			printf("%s \tPolicy: SCHED_OTHER\n", Prefix); 
			break;
	} 
	if (policy == SCHED_OTHER)
	{
		printf("%s \tPriority: IGNORED\n\n", Prefix); 
	}
	else
	{
		printf("%s \tPriority: %d\n\n", Prefix, schedp.sched_priority); 
	}	
}

int CreateMyThread(pthread_t *thread, void *(*start_routine) (void *), void *arg, int policy, int priority)
{
	pthread_attr_t attr;			// for thread attribute modifications 
	struct sched_param schedp;	// for thread priority modifications
	int error;
	int success = 1;
	char policyStr[12];

	switch(policy)
	{
		case SCHED_FIFO:
			sprintf(policyStr, "SCHED_FIFO"); 
			break;
		case SCHED_RR:
			sprintf(policyStr, "SCHED_RR"); 
			break;
		default:
			sprintf(policyStr, "SCHED_OTHER"); 
			break;
	} 
   
	// Initialize thread attribute (for next threads)
	error = pthread_attr_init(&attr);
	if (error<0)
	{
		printf("<SCHED> \t Can not initialize attribute for pthread!\n");
		success &= 0;
	}
   
	// assign the scheduler policy in the thread attriubute
	error = pthread_attr_setschedpolicy(&attr, policy);
	if (error == EINVAL)
	{
		printf("<SCHED> \t Invalid value in policy!\n");
		success &= 0;
	}
		
	// assign the priority of the thread in the thread attribute
	if (policy != SCHED_OTHER)
	{
		schedp.sched_priority = priority;
		error = pthread_attr_setschedparam(&attr, &schedp);
		switch (error)
		{
			case EINVAL:
				printf("<SCHED> \t The specified priority (%d) does not make sense for the current scheduling policy %s\n", priority, policyStr);
				success &= 0;
				break;
			case ENOTSUP:
				printf("<SCHED> \t An attempt was made to set the attribute to an unsupported value!\n");
				success &= 0;
				break;
		}
	}
				
	error = pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
	if (error == EINVAL)
	{
		printf("<SCHED> \t Invalid value in inheritsched!\n");
		success &= 0;
	}
   
	// create a thread for task 1 with attribute "attr"
	error = pthread_create(thread, &attr, start_routine, arg);
	switch (error) 
	{
		case EAGAIN:
			printf("<SCHED> \t Insufficient resources to create another thread!\n");
			success &= 0;
			break;
		case EINVAL:
			printf("<SCHED> \t Invalid settings in attr!\n");
			success &= 0;
			break;
		case EPERM:
			printf("<SCHED> \t No permission to set the scheduling policy and parameters specified in attr!\n");
			success &= 0;
			break;
	}
	return(success);
}

void VoidTask(int sig)
{
}

void *DisplayTask(void *threadid) 
{
	int tid, sig;
	tid = (int)threadid;
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
	
	// Block all signal except SIGRTMIN+tid
		// block all signals
	sigfillset(&sigmask);
	pthread_sigmask(SIG_BLOCK, &sigmask, (sigset_t*)0);
		// unblock UnblockedSig
	sigemptyset(&sigmask);
	sigaddset(&sigmask, SigNum);
	pthread_sigmask(SIG_UNBLOCK, &sigmask, (sigset_t*)0);
	
	// redirect SIGRTMIN+tid to terminate
	signal(SigNum, VoidTask);
	
	// display the property of the new thread
	printf("THREAD %d created for Display Task at %.2f [ms]\n", tid, 1000.0);
	DisplayThread(tid);
	
	for(;;)
	{
		sigwait(&sigmask, &sig);
	
		if (sig == SigNum)
		{
			getloadavg(LoadAvg, 3);
			ComputeCPU();
			// plot the CPU load
			printf("| Sim Time: %8.3f [s]| Last second | Last Minute | Last 5 minutes |  Last 15 min  |\n", (float)((SimCurrentTime_us/1000000))/1000.0);
			printf("|   Waiting Processes   |      -      |   %7.3f   |     %7.3f    |    %7.3f    |\n", LoadAvg[0], LoadAvg[1], LoadAvg[2]);
			printf("|    CPU Load [0-100]   |   %7.3f   |   %7.3f   |     %7.3f    |    %7.3f    |\n\n", CpuAvg[3], CpuAvg[0], CpuAvg[1], CpuAvg[2]);
		}

		sched_yield();
	}
}