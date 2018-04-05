#ifndef library_cpu_h
#define library_cpu_h

	#include <string.h>
	#include <stdlib.h>
	#include <unistd.h>
	#include <stdio.h>

	#define CPU_LINE_LENGTH 255
	#define NB_SAMPLE_CPU 901

	void InitCPU(void);
	void ComputeCPU(void);
	int FileGetLine(char *buf, int n, FILE * fd);

	// variable for CPU load monitoring
	extern double LoadAvg[3];
	extern float CpuAvg[4];	// average over 1min, 5min and 15min and last second CPU load
	extern int BusyJiffies[NB_SAMPLE_CPU];		// 900=60*15: 15 min history with a 1Hz refreash rate
	extern int TotalJiffies[NB_SAMPLE_CPU];
	extern int CicularBufferIndex;		

#endif
	