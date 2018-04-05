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
 
#ifndef LIBRARY_UDP_h
#define LIBRARY_UDP_h

	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <unistd.h>
	#include <fcntl.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <netdb.h>
	#include <string.h>
	#include <errno.h>
	#include "defines_verdex.h"
	 
	#define IP_LENGTH 16		// length of IP adress
	
	/***************** prototypes declaration ******************/
	//int initUDPconnection(struct sockaddr_in *host_info, struct sockaddr_in *gumstix_info, int *sk, const char *host_address, char *gumstix_address, unsigned short port);
	int initUDPlocalSocket(struct sockaddr_in *local_info, int *sk, char *local_address, unsigned short local_port);
	int initUDPremote(struct sockaddr_in *remote_info, const char *remote_address, unsigned short remote_port);
	char *getAddressOfInterface(const char *interface, char IPaddress[IP_LENGTH]);
	int isValidIP(const char *ip);
	char* socket2str(int socket, char* str);
	char* sockaddr2str(struct sockaddr_in addr, char* str);
	
	/************ DOUBLE ***********/
	void WaitnDouble_UDP(int socket_id, struct sockaddr_in *src_info, double *DoubleToWait, int NbDoubleToWait, unsigned int BlockingTimeOut_us);
	void ReadnDouble_UDP(int socket_id, struct sockaddr_in *src_info, double *DoubleToWait, int NbDoubleToWait);
	void ReadLastnDouble_UDP(int socket_id, struct sockaddr_in *src_info, double *DoubleToWait, int NbDoubleToWait);
	int SendnDouble_UDP(int socket_id, struct sockaddr_in *dest_info, double *DoubleToSend, int NbDoubleToSend);
	
	/************ FLOAT32 ***********/
	void WaitnFloat_UDP(int socket_id, struct sockaddr_in *src_info, float *Float32ToWait, int NbFloat32ToWait, unsigned int BlockingTimeOut_us);
	void ReadnFloat_UDP(int socket_id, struct sockaddr_in *src_info, float *Float32ToWait, int NbFloat32ToWait);
	void ReadLastnFloat_UDP(int socket_id, struct sockaddr_in *src_info, float *Float32ToWait, int NbFloat32ToWait);
	int SendnFloat_UDP(int socket_id, struct sockaddr_in *dest_info, float *Float32ToSend, int NbFloat32ToSend);
	
	/************ INT32 ***********/
	void WaitnInt32_UDP(int socket_id, struct sockaddr_in *src_info, int *Int32ToWait, int NbInt32ToWait, unsigned int BlockingTimeOut_us);
	void ReadnInt32_UDP(int socket_id, struct sockaddr_in *src_info, int *Int32ToWait, int NbInt32ToWait);
	void ReadLastnInt32_UDP(int socket_id, struct sockaddr_in *src_info, int *Int32ToWait, int NbInt32ToWait);
	int SendnInt32_UDP(int socket_id, struct sockaddr_in *dest_info, int *Int32ToSend, int NbInt32ToSend);
	
	/************ UINT32 ***********/
	void WaitnUInt32_UDP(int socket_id, struct sockaddr_in *src_info, unsigned int *UInt32ToWait, int NbUInt32ToWait, unsigned int BlockingTimeOut_us);
	void ReadnUInt32_UDP(int socket_id, struct sockaddr_in *src_info, unsigned int *UInt32ToWait, int NbUInt32ToWait);
	void ReadLastnUInt32_UDP(int socket_id, struct sockaddr_in *src_info, unsigned int *UInt32ToWait, int NbUInt32ToWait);
	int SendnUInt32_UDP(int socket_id, struct sockaddr_in *dest_info, unsigned int *UInt32ToSend, int NbUInt32ToSend);
	
	/************ INT16 ***********/
	void WaitnInt16_UDP(int socket_id, struct sockaddr_in *src_info, short *Int16ToWait, int NbInt16ToWait, unsigned int BlockingTimeOut_us);
	void ReadnInt16_UDP(int socket_id, struct sockaddr_in *src_info, short *Int16ToWait, int NbInt16ToWait);
	void ReadLastnInt16_UDP(int socket_id, struct sockaddr_in *src_info, short *Int16ToWait, int NbInt16ToWait);
	int SendnInt16_UDP(int socket_id, struct sockaddr_in *dest_info, short *Int16ToSend, int NbInt16ToSend);
	
	/************ UINT16 ***********/
	void WaitnUInt16_UDP(int socket_id, struct sockaddr_in *src_info, unsigned short *UInt16ToWait, int NbUInt16ToWait, unsigned int BlockingTimeOut_us);
	void ReadnUInt16_UDP(int socket_id, struct sockaddr_in *src_info, unsigned short *UInt16ToWait, int NbUInt16ToWait);
	void ReadLastnUInt16_UDP(int socket_id, struct sockaddr_in *src_info, unsigned short *UInt16ToWait, int NbUInt16ToWait);
	int SendnUInt16_UDP(int socket_id, struct sockaddr_in *dest_info, unsigned short *UInt16ToSend, int NbUInt16ToSend);
	
	/************ CHAR8 ***********/
	void WaitnChar8_UDP(int socket_id, struct sockaddr_in *src_info, char *Char8ToWait, int NbChar8ToWait, unsigned int BlockingTimeOut_us);
	void ReadnChar8_UDP(int socket_id, struct sockaddr_in *src_info, char *Char8ToWait, int NbChar8ToWait);
	void ReadLastnChar8_UDP(int socket_id, struct sockaddr_in *src_info, char *Char8ToWait, int NbChar8ToWait);
	int SendnChar8_UDP(int socket_id, struct sockaddr_in *dest_info, char *Char8ToSend, int NbChar8ToSend);
	
	/************ UCHAR8 ***********/
	void WaitnUChar8_UDP(int socket_id, struct sockaddr_in *src_info, unsigned char *UChar8ToWait, int NbUChar8ToWait, unsigned int BlockingTimeOut_us);
	void ReadnUChar8_UDP(int socket_id, struct sockaddr_in *src_info, unsigned char *UChar8ToWait, int NbUChar8ToWait);
	void ReadLastnUChar8_UDP(int socket_id, struct sockaddr_in *src_info, unsigned char *UChar8ToWait, int NbUChar8ToWait);
	int SendnUChar8_UDP(int socket_id, struct sockaddr_in *dest_info, unsigned char *UChar8ToSend, int NbUChar8ToSend);
	
#endif
