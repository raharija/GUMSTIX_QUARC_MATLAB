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
 
#include "Time_Tools_Win.h"

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
*/
 
/*************** Declaration of different variable ***************/
extern struct TicToc struc_TicToc; // need to be created in main.c
 
/************ Declaration of functions and their body ************/
int gettimeofday( struct timeval *tv, struct timezone *tz )
{
	// here starts the microsecond resolution:
	LARGE_INTEGER tickPerSecond;
	LARGE_INTEGER tick; // a point in time
	ULONGLONG tick_u;
	ULONGLONG tickPerSecond_u;

	//time(&rawtime);
	//tv->tv_sec = (long)rawtime;

	// get the high resolution counter's accuracy
	QueryPerformanceFrequency(&tickPerSecond);
	//printf("tickPerSecond: %d\n", tickPerSecond.QuadPart);
	// what time is it ?
	QueryPerformanceCounter(&tick);
	//printf("tick: %d\n", tick.QuadPart);
	// and here we get the current microsecond! \o/
	tick_u = (ULONGLONG)tick.QuadPart;
	tickPerSecond_u = (ULONGLONG)tickPerSecond.QuadPart;
	// NbSec = tick_u/tickPerSecond_u;
	// NbuSec = tick_u*1000000/tickPerSecond_u-NbSec*1000000;
	// tv->tv_sec = (long)NbSec;
	// tv->tv_usec = (long)NbuSec;
	tv->tv_sec = (long)(tick_u/tickPerSecond_u);
	tv->tv_usec = (long)(tick_u*1000000/tickPerSecond_u-tv->tv_sec*1000000);

	//printf("tv->tv_sec: %d\n", tv->tv_sec);
	//printf("tv->tv_usec: %d\n", tv->tv_usec);
	return 0;
}

double ms_time (void) // give current time with millisecond resolution
{
	static struct timeval tod;
	gettimeofday (&tod, NULL);
	return ((double)tod.tv_sec * 1000.0 + (double)tod.tv_usec / 1000.0);
}
 
double us_time (void) // give current time with microsecond resolution
{
	static struct timeval tod;
	gettimeofday (&tod, NULL);
	return ((double)tod.tv_sec * 1000000.0 + (double)tod.tv_usec);
}
double s_time (void) // give current time with microsecond resolution
{
	static struct timeval tod;
	gettimeofday (&tod, NULL);
	return ((double)tod.tv_sec + ((double)tod.tv_usec)/1000000.0);
}
 
void tic (char *message_in) // capture an initial time with microseconds resolution
{
	struc_TicToc.d_Tinit = us_time();
	strcpy(struc_TicToc.s_message, message_in);
	#ifdef ECHO_PRINTF_TIME
		printf("BEGIN Tic(): %s\n", struc_TicToc.s_message);
	#endif
	#ifdef ECHO_FPRINTF_TIME
		fprintf(FID_debug, "BEGIN Tic(): %s\n", struc_TicToc.s_message);
	#endif
	// printf("temps initial: %f us\n", struc_TicToc.d_Tinit);
}
 
double toc (void) // capture a final time with microseconds resolution
{
	struc_TicToc.d_Tend = us_time();
	struc_TicToc.d_Tdelta = struc_TicToc.d_Tend - struc_TicToc.d_Tinit;
	#ifdef ECHO_PRINTF_TIME
		printf("END Toc(): %s. Elapsed time: %.6f [s]\n", struc_TicToc.s_message, struc_TicToc.d_Tdelta/1000000.0);
	#endif
	#ifdef ECHO_FPRINTF_TIME
		fprintf(FID_debug, "END Toc(): %s. Elapsed time: %.6f [s]\n", struc_TicToc.s_message, struc_TicToc.d_Tdelta/1000000.0);
	#endif
	
	return(struc_TicToc.d_Tdelta);
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
