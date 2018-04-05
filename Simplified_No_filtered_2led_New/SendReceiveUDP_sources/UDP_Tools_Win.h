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
 
#ifndef UDP_TOOLS_WIN_h
#define UDP_TOOLS_WIN_h

	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
    #include <windows.h>
	 
	#include "simstruc.h"
	#include "Time_Tools_Win.h"
	
    #define MAX(a,b) ((a) > (b) ? a : b)
    #define MIN(a,b) ((a) < (b) ? a : b)
        
    //#define QUARC_MODE
        
	#ifndef __bool_true_false_are_defined
	#  define TRUE 1
	#  define FALSE 0
	#  define bool int
	#  define __bool_true_false_are_defined
	#endif
	
	#define MAX_BUF 		1024
	#define RCV_FLAG 		0
	#define ERROR_FOPEN 	0x01
	#define ERROR_WINSOCK 	0x02
	#define ERROR_SOCKET 	0x04
	#define ERROR_BIND 		0x08
	#define INIT_OK 		0
	
	#define ERROR_CLOSESOCKET	0x01
	#define ERROR_WSACLEANUP	0x02
	
	#define NB_BYTE_CHAR8 	1
	#define NB_BYTE_UCHAR8 	1
	#define NB_BYTE_INT16 	2
	#define NB_BYTE_UINT16 	2
	#define NB_BYTE_INT32 	4
	#define NB_BYTE_UINT32 	4
	#define NB_BYTE_FLOAT 	4
	#define NB_BYTE_DOUBLE 	8
	
	#define NB_IP_MAX 254
	
	//DTypeId GetDataToSendType_UDP(SimStruct *S);
	//DTypeId GetDataToReceiveType_UDP(SimStruct *S);
	int GetIPlastNumber(const char IP_address_str[16]);
	
	/********** INITIALIZATION AND TERMINATE FUNCTIONS *********/
	int initUDPconnection(int index, char *ip_remote, char *ip_host, int port);
	int CleanUpSocket(int index);
	void ConnectLogUpdate_SendReceiveUDP(FILE* NameDebug, char* IP_addres_str, int index);
	void CleanUpMdlStartSendReceiveUDP(int index, char* IP_remote_str);
	int ReportInitUDPError(int index);
	void ReportUDPerror(int index);

	/*********** CLASSIC STREAM OPERATION **********/
	int receiveUDPstream(struct sockaddr_in *host_info, SOCKET socket_id, char *buffer, int index);
	int sendUDPstream(SOCKADDR_IN *host_info, char *buffer, SOCKET socket_id, int index);
	int formatUDPstream_in(double *tab, char *buf, int nb_waiting_data, int index);

	/*************** OPIMIZED STREAM OPERATION *************/

	/************ DOUBLE ***********/
	void WaitnDouble_UDP(int SocketIndex, SOCKADDR_IN *src_info, double *DoubleToWait, int NbDoubleToWait);
	void ReadnDouble_UDP(int SocketIndex, SOCKADDR_IN *src_info, double *DoubleToWait, int NbDoubleToWait);
	int ReadLastnDouble_UDP(int SocketIndex, SOCKADDR_IN *src_info, double *DoubleToWait, int NbDoubleToWait);
	int SendnDouble_UDP(int SocketIndex, SOCKADDR_IN *dest_info, double *DoubleToSend, int NbDoubleToSend);

	/************ FLOAT32 ***********/
	void WaitnFloat_UDP(int SocketIndex, SOCKADDR_IN *src_info, float *Float32ToWait, int NbFloat32ToWait);
	void ReadnFloat_UDP(int SocketIndex, SOCKADDR_IN *src_info, float *FloatToWait, int NbFloatToWait);
	int ReadLastnFloat_UDP(int SocketIndex, SOCKADDR_IN *src_info, float *FloatToWait, int NbFloatToWait);
	int SendnFloat_UDP(int SocketIndex, SOCKADDR_IN *dest_info, float *Float32ToSend, int NbFloat32ToSend);

	/************ INT32 ***********/
	void WaitnInt32_UDP(int SocketIndex, SOCKADDR_IN *src_info, int *Int32ToWait, int NbInt32ToWait);
	void ReadnInt32_UDP(int SocketIndex, SOCKADDR_IN *src_info, int *Int32ToWait, int NbInt32ToWait);
	int ReadLastnInt32_UDP(int SocketIndex, SOCKADDR_IN *src_info, int *Int32ToWait, int NbInt32ToWait);
	int SendnInt32_UDP(int SocketIndex, SOCKADDR_IN *dest_info, int *Int32ToSend, int NbInt32ToSend);

	/************ UINT32 ***********/
	void WaitnUInt32_UDP(int SocketIndex, SOCKADDR_IN *src_info, unsigned int *UInt32ToWait, int NbUInt32ToWait);
	void ReadnUInt32_UDP(int SocketIndex, SOCKADDR_IN *src_info, unsigned int *UInt32ToWait, int NbUInt32ToWait);
	int ReadLastnUInt32_UDP(int SocketIndex, SOCKADDR_IN *src_info, unsigned int *UInt32ToWait, int NbUInt32ToWait);
	int SendnUInt32_UDP(int SocketIndex, SOCKADDR_IN *dest_info, unsigned int *UInt32ToSend, int NbUInt32ToSend);

	/************ INT16 ***********/
	void WaitnInt16_UDP(int SocketIndex, SOCKADDR_IN *src_info, short *Int16ToWait, int NbInt16ToWait);
	void ReadnInt16_UDP(int SocketIndex, SOCKADDR_IN *src_info, short *Int16ToWait, int NbInt16ToWait);
	int ReadLastnInt16_UDP(int SocketIndex, SOCKADDR_IN *src_info, short *Int16ToWait, int NbInt16ToWait);
	int SendnInt16_UDP(int SocketIndex, SOCKADDR_IN *dest_info, short *Int16ToSend, int NbInt16ToSend);

	/************ UINT16 ***********/
	void WaitnUInt16_UDP(int SocketIndex, SOCKADDR_IN *src_info, unsigned short *UInt16ToWait, int NbUInt16ToWait);
	void ReadnUInt16_UDP(int SocketIndex, SOCKADDR_IN *src_info, unsigned short *UInt16ToWait, int NbUInt16ToWait);
	int ReadLastnUInt16_UDP(int SocketIndex, SOCKADDR_IN *src_info, unsigned short *UInt16ToWait, int NbUInt16ToWait);
	int SendnUInt16_UDP(int SocketIndex, SOCKADDR_IN *dest_info, unsigned short *UInt16ToSend, int NbUInt16ToSend);

	/************ CHAR8 ***********/
	void WaitnChar8_UDP(int SocketIndex, SOCKADDR_IN *src_info, char *Char8ToWait, int NbChar8ToWait);
	void ReadnChar8_UDP(int SocketIndex, SOCKADDR_IN *src_info, char *Char8ToWait, int NbChar8ToWait);
	int ReadLastnChar8_UDP(int SocketIndex, SOCKADDR_IN *src_info, char *Char8ToWait, int NbChar8ToWait);
	int SendnChar8_UDP(int SocketIndex, SOCKADDR_IN *dest_info, char *Char8ToSend, int NbChar8ToSend);

	/************ UCHAR8 ***********/
	void WaitnUChar8_UDP(int SocketIndex, SOCKADDR_IN *src_info, unsigned char *UChar8ToWait, int NbUChar8ToWait);
	void ReadnUChar8_UDP(int SocketIndex, SOCKADDR_IN *src_info, unsigned char *UChar8ToWait, int NbUChar8ToWait);
	int ReadLastnUChar8_UDP(int SocketIndex, SOCKADDR_IN *src_info, unsigned char *UChar8ToWait, int NbUChar8ToWait);
	int SendnUChar8_UDP(int SocketIndex, SOCKADDR_IN *dest_info, unsigned char *UChar8ToSend, int NbUChar8ToSend);
	
#endif