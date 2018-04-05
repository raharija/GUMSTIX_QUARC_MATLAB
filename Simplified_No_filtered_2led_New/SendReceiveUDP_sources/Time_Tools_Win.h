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
 
#include <windows.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef DEF_TIME_TOOLS
#define DEF_TIME_TOOLS

#ifndef ECHO_PRINTF_TIME
	#define ECHO_PRINTF_TIME
#endif
 #ifndef ECHO_FPRINTF_TIME
	/***** DEFINE FPRINTF_ECHO_TIME OPTION *****/
#endif	

/********** Declaration of data structure and new types **********/
struct TicToc {
	double d_Tinit;
	double d_Tend;
	double d_Tdelta;
	char s_message[100];
};

/************** Declaration of function's protoypes **************/
double ms_time (void);	// give current time in millisecond
double us_time (void);	// give current time in microsecond
double s_time (void); 	// give current time in second
void tic (char *message_in);
double toc (void);
void init_time (void);
void us_wait(int us_wait_time);
void ms_wait(int ms_wait_time);
void s_wait(int s_wait_time);

#endif
