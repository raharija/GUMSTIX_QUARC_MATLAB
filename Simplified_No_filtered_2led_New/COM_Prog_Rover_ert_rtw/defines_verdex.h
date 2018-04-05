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
 
#ifndef VERDEX_DEFINES_h
 
	#define VERDEX_DEFINES_h
	
	#include "time_tools.h"				     /* Clock and delay customized tools */
	
	#ifndef ECHO_PRINTF
		/***** DEFINE PRINTF_ECHO OPTION *****/
	#endif
	#ifndef ECHO_FPRINTF
		/***** DEFINE FPRINTF_ECHO OPTION *****/
	#endif	
	#ifndef ECHO_PRINTF_TIME
		/***** DEFINE PRINTF_ECHO_TIME OPTION *****/
	#endif
	#ifndef ECHO_FPRINTF_TIME
		/***** DEFINE FPRINTF_ECHO_TIME OPTION *****/
	#endif
	#ifndef TASK_TIME_LOGGER
		/***** DEFINE TASK_TIME_LOG OPTION *****/
	#endif
	
	#define MAX(a,b) ((a) > (b) ? (a) : (b)) 
	#define MIN(a,b) ((a) < (b) ? (a) : (b)) 
	
	#define NB_BYTE_CHAR8 	1
	#define NB_BYTE_UCHAR8 	1
	#define NB_BYTE_INT16 	2
	#define NB_BYTE_UINT16 	2
	#define NB_BYTE_INT32 	4
	#define NB_BYTE_UINT32 	4
	#define NB_BYTE_FLOAT 	4
	#define NB_BYTE_DOUBLE 	8
	
	#define CPU_STAT_SAMPLE_TIME_US 1000000
	
	/***** DEFINE RS232 EXCHANGED DATA SIZE *****/
    	// GUMSTIX SIDE:  //(code generated automatically)
	#define NB_COM_PORT 1
	
	/***** DEFINE UDP EXCHANGED DATA SIZE *****/
    	// GUMSTIX SIDE:  //(code generated automatically)
    #define NB_RECP_UDP 1       	// Number of data expected in the port "In_from_UDP" of Gumstix  //(code generated automatically)
    #define NB_EMI_UDP 1     	// Number of data expected in the port "Out_to_UDP" of Gumstix  //(code generated automatically)
    #define NB_SOCK_UDP 1     	// Number of data expected in the port "Out_to_UDP" of Gumstix  //(code generated automatically)
	
	/***** DEFINE SPI EXCHANGED DATA SIZE *****/
	
	/***** DEFINE I2C EXCHANGED DATA SIZE *****/
	
	/***** DEFINE LOG EXCHANGED DATA SIZE *****/
	
	/***** DEFINE THE SAMPLE TIME *****/
    #define GUMSTIX_SAMPLE_TIME_US 2000	// sample time in microseconds  //(code generated automatically)
	#define NB_SAMPLE_TIME 2
	#define NB_SUB_TASK 1
	#define NANOWII_TIMEOUT 100000.00 // 100.00 ms
	#define PREEMPTRT 
	/***** TERMINATE DEFINES *****/
	
#endif
 
