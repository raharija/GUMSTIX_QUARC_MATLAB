#include "CpuTools.h"

// variable for CPU load monitoring
double LoadAvg[3] = {0.0, 0.0, 0.0};
float CpuAvg[4];	// average over 1min, 5min and 15min and last second CPU load
int BusyJiffies[NB_SAMPLE_CPU] = {0, };		// 900=60*15: 15 min history with a 1Hz refreash rate
int TotalJiffies[NB_SAMPLE_CPU] = {1, };
int CicularBufferIndex = 0;

void InitCPU(void)
{
	int i;
	
	for (i=0; i<NB_SAMPLE_CPU; i++)
	{
		BusyJiffies[i] = 0;
		TotalJiffies[i] = 1;
	}
}

void ComputeCPU(void)
{
	char CpuLine[CPU_LINE_LENGTH+1];
	int NbIntRead = 0;
	int Read, DeltaBusyJiffies, DeltaTotalJiffies;
	static int PreviousBusyJiffies, PreviousTotalJiffies;
	int OldIndex;
	float OldCpuSample, CurrentCpuSample;
	char* ReadString;
	
	FILE* ProcStatFd;

	ProcStatFd = fopen("/proc/stat", "r");
	// compute the CPU load
	FileGetLine(CpuLine, CPU_LINE_LENGTH, ProcStatFd);
	// recover and:
	//		- sum the three first number of the cpu line (Busy Jiffies)
	//      - sum all the number of the cpu line (Total Jiffies)
	ReadString = strtok (CpuLine," "); // the first string is "cpu" and is ignored
	BusyJiffies[CicularBufferIndex] = 0;
	TotalJiffies[CicularBufferIndex] = 0;
	NbIntRead = 0;
	while (ReadString != NULL)
	{
		// recover the new string
		ReadString = strtok (NULL, " ");
		if (ReadString!=NULL)
		{
			// convert it to an int
			Read = (int)strtol(ReadString, NULL, 10);
			NbIntRead++;
			// compute the busy
			if (NbIntRead <= 3)
			{
				BusyJiffies[CicularBufferIndex] += Read;
			}
			TotalJiffies[CicularBufferIndex] += Read;
		}
	}
	// determine the delta between the current jiffies and the previous jiffies
	DeltaBusyJiffies = BusyJiffies[CicularBufferIndex]-PreviousBusyJiffies;
	DeltaTotalJiffies = TotalJiffies[CicularBufferIndex]-PreviousTotalJiffies;
	// Current jiffies becomes previous jiffies
	PreviousBusyJiffies = BusyJiffies[CicularBufferIndex];
	PreviousTotalJiffies = TotalJiffies[CicularBufferIndex];
	// Memories the delta jiffies
	BusyJiffies[CicularBufferIndex] = DeltaBusyJiffies;
	TotalJiffies[CicularBufferIndex] = DeltaTotalJiffies;
	// Update the CpuAvg
	if ((CicularBufferIndex-60)<0)
	{
		OldIndex = (CicularBufferIndex+NB_SAMPLE_CPU-60)%NB_SAMPLE_CPU;
	}
	else
	{
		OldIndex = (CicularBufferIndex-60)%NB_SAMPLE_CPU;
	}
	OldCpuSample = ((float)BusyJiffies[OldIndex]/(float)TotalJiffies[OldIndex])*100.0;
	CurrentCpuSample = ((float)BusyJiffies[CicularBufferIndex]/(float)TotalJiffies[CicularBufferIndex])*100.0;
	CpuAvg[3] = CurrentCpuSample;
	CpuAvg[0] += (CurrentCpuSample - OldCpuSample)/60.0;
	if ((CicularBufferIndex-300)<0)
	{
		OldIndex = (CicularBufferIndex+NB_SAMPLE_CPU-300)%NB_SAMPLE_CPU;
	}
	else
	{
		OldIndex = (CicularBufferIndex-300)%901;
	}
	OldCpuSample = ((float)BusyJiffies[OldIndex]/(float)TotalJiffies[OldIndex])*100.0;
	CpuAvg[1] += (CurrentCpuSample - OldCpuSample)/300.0;
	if ((CicularBufferIndex-900)<0)
	{
		OldIndex = (CicularBufferIndex+NB_SAMPLE_CPU-900)%NB_SAMPLE_CPU;
	}
	else
	{
		OldIndex = (CicularBufferIndex-900)%NB_SAMPLE_CPU;
	}
	OldCpuSample = ((float)BusyJiffies[OldIndex]/(float)TotalJiffies[OldIndex])*100.0;
	OldCpuSample = ((float)BusyJiffies[OldIndex]/(float)TotalJiffies[OldIndex])*100.0;
	CpuAvg[2] += (CurrentCpuSample - OldCpuSample)/900.0;
	
	// update the circular buffer
	CicularBufferIndex++;
	if(CicularBufferIndex==NB_SAMPLE_CPU) 
	{ 
		CicularBufferIndex=0;
	}
	fclose(ProcStatFd);
}

int FileGetLine(char *buf, int n, FILE * fd)
{
    if (!fgets(buf, n, fd))
	{
		return(0);
	}

    while(*buf != '\n')
	{
		buf++;
	}
    *buf = '\0';

    return(1);
}