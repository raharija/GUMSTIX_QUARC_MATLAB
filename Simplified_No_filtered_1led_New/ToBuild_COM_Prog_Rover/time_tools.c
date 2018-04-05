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
 
#include "time_tools.h"
 
extern FILE *FID_debug;
 
// REMINDER

/*
struct timeval {
    time_t      tv_sec;     // seconds
    suseconds_t tv_usec;    // microseconds
};

struct timezone {
    int tz_minuteswest;     // minutes west of Greenwich
    int tz_dsttime;         // type of DST correction
};

struct timespec {
	__kernel_time_t tv_sec;		// seconds 
	long            tv_nsec;	// nanoseconds 
};
*/
 
/*************** Declaration of different variable ***************/
extern struct TicToc struc_TicToc[NB_SAMPLE_TIME]; // need to be created in main.c
 
/************ Declaration of functions and their body ************/
double ns_time (void) // give current time with microsecond resolution
{
	static struct timespec tod;
	clock_gettime(CLOCK_MONOTONIC, &tod);
	return ((double)tod.tv_sec * 1000000000.0 + (double)tod.tv_nsec);
}

double us_time (void) // give current time with microsecond resolution
{
	static struct timespec tod;
	clock_gettime(CLOCK_MONOTONIC, &tod);
	return ((double)tod.tv_sec * 1000000000.0 + (double)tod.tv_nsec)/1000;
}

double ms_time (void) // give current time with microsecond resolution
{
	static struct timespec tod;
	clock_gettime(CLOCK_MONOTONIC, &tod);
	return ((double)tod.tv_sec * 1000000000.0 + (double)tod.tv_nsec)/1000000;
}

double s_time (void) // give current time with microsecond resolution
{
	static struct timespec tod;
	clock_gettime(CLOCK_MONOTONIC, &tod);
	return ((double)tod.tv_sec + ((double)tod.tv_nsec)/1000000000.0);
} 
 
void tic (char *message_in, int ThreadNum) // capture an initial time with microseconds resolution
{
	struc_TicToc[ThreadNum].d_Tinit = ns_time()/1000;
	strcpy(struc_TicToc[ThreadNum].s_message, message_in);
	#ifdef ECHO_PRINTF_TIME
		printf("BEGIN Tic(): %s\n", struc_TicToc[ThreadNum].s_message);
		fflush(stdout);
	#endif
	#ifdef ECHO_FPRINTF_TIME
		fprintf(FID_debug, "BEGIN Tic(): %s\n", struc_TicToc[ThreadNum].s_message);
		//fflush(FID_debug);
	#endif
	// printf("temps initial: %f us\n", struc_TicToc.d_Tinit);
}
 
double toc (int ThreadNum) // capture a final time with microseconds resolution
{
	struc_TicToc[ThreadNum].d_Tend = ns_time()/1000;
	struc_TicToc[ThreadNum].d_Tdelta = struc_TicToc[ThreadNum].d_Tend - struc_TicToc[ThreadNum].d_Tinit;
	#ifdef ECHO_PRINTF_TIME
		printf("END Toc(): %s. Elapsed time: %.9f [ms]\n", struc_TicToc[ThreadNum].s_message, (struc_TicToc[ThreadNum].d_Tdelta)/1000.0);
		fflush(stdout);
	#endif
	#ifdef ECHO_FPRINTF_TIME
		fprintf(FID_debug, "END Toc(): %s. Elapsed time: %.9f [ms]\n", struc_TicToc[ThreadNum].s_message, (struc_TicToc[ThreadNum].d_Tdelta)/1000.0);
		//fflush(FID_debug);
	#endif
	
	return(struc_TicToc[ThreadNum].d_Tdelta);
}

void us_wait(int us_wait_time)
{
	double us_init_time = us_time();
	
	while((us_time()-us_init_time)<(double)us_wait_time);
}

void ms_wait(int ms_wait_time)
{
	double us_init_time = us_time();
	
	while((us_time()-us_init_time)<(double)ms_wait_time*1000.0);
}

void s_wait(int s_wait_time)
{
	double us_init_time = us_time();
	
	while((us_time()-us_init_time)<(double)s_wait_time*1000000.0);
}

