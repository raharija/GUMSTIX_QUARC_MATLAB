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
 
#ifndef SEND_RECEIVE_UDP_h
#define SEND_RECEIVE_UDP_h
	
	#include <winsock2.h> // pour les fonctions socket
	#include <stdio.h> // Pour les Sprintf
	#include <string.h> // pour les manipulations de chaines de caractères
	#include "simstruc.h"
    #include "UDP_Tools_Win.h"
	
	#ifndef ECHO_PRINTF
		//#define ECHO_PRINTF
    #endif
    #ifndef ECHO_FPRINTF
        //#define ECHO_FPRINTF// fprintf (for debug only!) disabled during simulation! (not during initialization...)
    #endif	 
	
	// udp port number
#define PORT 2012 // code generated automatically  //(code generated automatically)

	
	// server address (windows/host side)
#define HOST_ADDRESS "192.168.137.3" // code generated automatically  //(code generated automatically)

	 
	// client address (ip address of gumstix verdex card)
#define GUMSTIX_ADDRESS "192.168.137.11" // code generated automatically  //(code generated automatically)

	 
	// number of data which are received by udp
#define HOST_UDP_NB_DATA_RECV 20 // code generated automatically  //(code generated automatically)

	 
	// number of data to send by udp
#define HOST_UDP_NB_DATA_SEND 26 // code generated automatically  //(code generated automatically)

#endif

