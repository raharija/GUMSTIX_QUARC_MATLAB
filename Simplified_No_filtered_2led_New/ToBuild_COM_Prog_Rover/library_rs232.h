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
 
#ifndef library_rs232_h
#define library_rs232_h
	
	#ifdef __cplusplus
	extern "C" {
	#endif
	
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <errno.h>
	#include <termios.h>
	#include <sys/ioctl.h>
	#include <unistd.h>
	#include <fcntl.h>
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <limits.h>
	#include <linux/serial.h>
	#include <sys/time.h>
	#include "defines_verdex.h"
	#ifdef XENOMAI
		#include <xenomai/rtdm/rtdm.h>
		#include <xenomai/rtdm/rtserial.h>
		#include <xenomai/native/task.h>
	#endif
	
	#define RING_BUF_SIZE 256
	
	struct RingBuffer {
		int EndIndex;
		int BeginIndex;
		int SizeOfBuffer;
		int NbByteInBuffer;
		char Data[RING_BUF_SIZE];
	};
	
	extern char comPorts[22][13];
	
	/********* Ring buffer tools *********/
	void InitRingBuffer(volatile struct RingBuffer *RingBufferPtr);
	void ClearRingBuffer(volatile struct RingBuffer *RingBufferPtr);
	void RemoveToRingBufferBegin(volatile struct RingBuffer *RingBufferPtr, int NbBytes);
	void RemoveToRingBufferEnd(volatile struct RingBuffer *RingBufferPtr, int NbBytes);
	void AddDataToRingBuffer(volatile struct RingBuffer *RingBufferPtr, char* ToFill, int NbBytes);
	void AddToRingBuffer(volatile struct RingBuffer *RingBufferPtr, int NbBytes);
	
	/********* UART configurations operations *********/
	int CleanInputRS232(int ComPortNum);
	int CleanOutputRS232(int ComPortNum);
	int CleanBothRS232(int ComPortNum);
	int OpenComPort(int ComPortNum, int BaudRate);
	void CloseComPort(int ComPortNum);
	int initCOMconnection(int ComPortNum, int BaudRate);
	void EnableIOinterrupt_RS232(int ComPortNum);
	int BytesAvailable(int ComPortNum);
	
	int ReadnChar(int ComPortNum, char *ptr, int nb_to_read);
	int WritenChar(int ComPortNum, char *ptr);
	
	/********* SYNCHRONIZATION PROTOCOLS RS232 *********/
	int SendStartStream_RS232(int ComPortNum, char* StartMessage);
	int WaitStartStream_RS232(int ComPortNum, char* StartMessage, int TimeOut_ms);
	int SendStopStream_RS232(int ComPortNum, char* StopMessage);
	int WaitStopStream_RS232(int ComPortNum, char* StopMessage, int TimeOut_ms);
	
	/***************** RS232 READ/WRITE/WAIT FUNCTIONS ********************/
	int Write_RS232(int ComPortNum, void *ToWrite, int NbByteToWrite);
	int Wait_RS232(int ComPortNum, void *ToWait, int NbByteToWait);
	int Read_RS232(int ComPortNum, void *ToWait, int NbByteToWait);
	int HeaderWrite_RS232(int ComPortNum, void *ToWrite, int NbByteToWrite, unsigned char Header);
	int HeaderRead_RS232(int ComPortNum, void *ToWait, int NbByteToWait, unsigned char Header);
	int HeaderWait_RS232(int ComPortNum, void *ToWait, int NbByteToWait, unsigned char Header, int BlockingTimeOut_us);
	
	#ifdef __cplusplus
	} /* extern "C" */
	#endif
	
#endif


