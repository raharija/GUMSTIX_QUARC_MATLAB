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
 
#include "UDP_Tools_Win.h"
 
SOCKET socket_id[NB_IP_MAX];                       // Socket identifier
SOCKADDR_IN gumstix_info[NB_IP_MAX], host_info[NB_IP_MAX];	// Structure linked to client socket information
SOCKADDR_IN src_info[NB_IP_MAX];							// Structure linked to src socket information
//real_T data_rcv[NB_IP_MAX][HOST_UDP_NB_DATA_RECV];  	// data received (maximum number set in "define_udp.h")
FILE* FID_debug_SendReceiveUDP[NB_IP_MAX];
unsigned short init_status_SendReceiveUDP[NB_IP_MAX];
struct TicToc struc_TicToc;


int GetIPlastNumber(const char IP_address_str[16])
{
	char *lastNumber_str;
	int cpt = 0;
	
	lastNumber_str = strpbrk(IP_address_str, "_");
	while(cpt < 2)
	{
		lastNumber_str = strpbrk(lastNumber_str+1, "_");
		cpt++;
	}
	
	cpt = atoi(lastNumber_str+1);
	
	return(cpt-1);
}

// int CmpSockAddrIn(const struct SOCKADDR_IN *sa, const struct SOCKADDR_IN *sb)
// {
//     if (sa->sin_family != sb->sin_family)
//     {
//         return (sa->sin_family - sb->sin_family);
//     }
//     
//     if (sa->sin_family == AF_INET) 
//     {
//         return (sa->sin_addr.s_addr - sb->sin_addr.s_addr);
//     }
// }

/********** INITIALIZATION AND TERMINATE FUNCTIONS *********/
int initUDPconnection(int index, char *ip_remote, char *ip_host, int port)
{
    WSADATA initialisation_win32;           // To recover initialisation structure
    int error;                              // To recover eventual error code
    unsigned long iMode;                    // to make reception blocking or not
    bool my_bool = TRUE;
    int i;
    SOCKET socket_temp[NB_IP_MAX];
    
    printf("<UDP> \tUDP initialization:\n");
    fprintf(FID_debug_SendReceiveUDP[index],"\tUDP initialization: \n");
	printf("\t\t IP_remote: %s, IP_host: %s, Port: %d\n", ip_remote, ip_host, port);
	fprintf(FID_debug_SendReceiveUDP[index],"\t\t IP_remote: %s, IP_host: %s, Port: %d\n", ip_remote, ip_host, port);
    // ********************************************************
	// Initialisation de Winsock
	// ********************************************************
	printf("<UDP> \t\tWinsock initialization: ");
	fprintf(FID_debug_SendReceiveUDP[index],"\t\tWinsock initialization: ");
	fflush(FID_debug_SendReceiveUDP[index]);
	error=WSAStartup(MAKEWORD(2,2),&initialisation_win32);
	if (error!=0)
    {
		printf("<UDP> FAILED! error %d  and %d\n",error,WSAGetLastError());
		fprintf(FID_debug_SendReceiveUDP[index],"FAILED! error %d  and %d\n",error,WSAGetLastError());
		fflush(FID_debug_SendReceiveUDP[index]);
		init_status_SendReceiveUDP[index] = (init_status_SendReceiveUDP[index]|ERROR_WINSOCK);
    }
	else
	{
		printf("OK!\n");
		fprintf(FID_debug_SendReceiveUDP[index]," OK!\n");
		fflush(FID_debug_SendReceiveUDP[index]);
	}
	
	// ********************************************************
	// Ouverture d'une Socket
	// ********************************************************
	if (socket_id[index]!=0)
	{
		printf("<UDP> \t\tRemove existing socket: %d... ", socket_id[index]);
		fprintf(FID_debug_SendReceiveUDP[index],"\t\tRemove existing socket: %d... ", socket_id[index]);
		fflush(FID_debug_SendReceiveUDP[index]);
		if(closesocket(socket_id[index]) != 0)
		{
			printf("<UDP> success!\n");	
			fprintf(FID_debug_SendReceiveUDP[index],"success!\n");
			fflush(FID_debug_SendReceiveUDP[index]);
		}
		else
		{
			printf("<UDP> FAILED!, error %d\n", WSAGetLastError());
			fprintf(FID_debug_SendReceiveUDP[index], "FAILED!, error %d\n", WSAGetLastError());
			fflush(FID_debug_SendReceiveUDP[index]);
		}
	}
	printf("<UDP> \t\tsocket creation: ");
	fprintf(FID_debug_SendReceiveUDP[index],"\t\tsocket creation: ");
	fflush(FID_debug_SendReceiveUDP[index]);
    
    // open as many temporary sockets as the number of the last ip number (to have a unique socket identifier)
    for(i=0; i<(index-1); i++)
    {
        socket_temp[i] = socket(PF_INET,SOCK_DGRAM,0);//(AF_INET, SOCK_DGRAM, IPPROTO_UDP);//(PF_INET,SOCK_DGRAM,0);
    }
    // open the socket
    socket_id[index]=socket(PF_INET,SOCK_DGRAM,0);//(AF_INET, SOCK_DGRAM, IPPROTO_UDP);//(PF_INET,SOCK_DGRAM,0); 
    // close all the temporary sockets
    for(i=0; i<(index-1); i++)
    {
        closesocket(socket_temp[i]);
    }
    
	if (socket_id[index]==INVALID_SOCKET)
    {
		printf("<UDP> FAILED! error %d\n",WSAGetLastError());
		fprintf(FID_debug_SendReceiveUDP[index],"FAILED! error %d\n",WSAGetLastError());
		fflush(FID_debug_SendReceiveUDP[index]);
		init_status_SendReceiveUDP[index] = (init_status_SendReceiveUDP[index]|ERROR_SOCKET);
    }
	else
    {
		printf("OK! (socket %d)\n", socket_id[index]);
		fprintf(FID_debug_SendReceiveUDP[index]," OK! (socket %d)\n", socket_id[index]);
		fflush(FID_debug_SendReceiveUDP[index]);
    }
	printf("<UDP> \t\tsetsockopt(): ");
    fprintf(FID_debug_SendReceiveUDP[index],"\t\tsetsockopt(): ");        
	fflush(FID_debug_SendReceiveUDP[index]);
    if (setsockopt(socket_id[index], SOL_SOCKET, SO_REUSEADDR, (char *)&my_bool, sizeof(my_bool))< 0) 
    {
        printf("<UDP>  FAILED! %d\n",WSAGetLastError());
		fprintf(FID_debug_SendReceiveUDP[index]," FAILED! %d\n",WSAGetLastError());
		fflush(FID_debug_SendReceiveUDP[index]);
    }
    else
    {
        printf("OK!\n");
		fprintf(FID_debug_SendReceiveUDP[index]," OK!\n");
		fflush(FID_debug_SendReceiveUDP[index]);
    }
    
    // If iMode!=0, non-blocking mode is enabled.
	iMode=1;
	ioctlsocket(socket_id[index],FIONBIO,&iMode); // rcvfrom is unbloking!
	// ********************************************************
	// Link socket
	// ********************************************************
	gumstix_info[index].sin_family=AF_INET;
	gumstix_info[index].sin_addr.s_addr=inet_addr(ip_remote); // listen only udp stream from ip_host, (INADDR_ANY) listen every udp stream
	gumstix_info[index].sin_port=htons(port); // listen on port PORT

    printf("<UDP> \t\tBind: ");
	fprintf(FID_debug_SendReceiveUDP[index],"\t\tBind: ");
    host_info[index].sin_family=AF_INET;
	host_info[index].sin_addr.s_addr=inet_addr(ip_host); // listen only udp stream from ip_remote, (INADDR_ANY) listen every udp stream 
	host_info[index].sin_port=htons(port); // listen on port PORT
    
	error=bind(socket_id[index],(struct sockaddr*)&host_info[index],sizeof(host_info[index]));
	if (error!=0)
    {
		printf("<UDP> FAILED! error %d %d\n",error,WSAGetLastError());
		fprintf(FID_debug_SendReceiveUDP[index],"FAILED! error %d %d\n",error,WSAGetLastError());
		fflush(FID_debug_SendReceiveUDP[index]);
        init_status_SendReceiveUDP[index] = (init_status_SendReceiveUDP[index]|ERROR_BIND);
    }
	else
	{
		printf("OK!\n");
		fprintf(FID_debug_SendReceiveUDP[index],"OK!\n");
		fflush(FID_debug_SendReceiveUDP[index]);
	}
    if(init_status_SendReceiveUDP[index] != 0)
    {
        printf("<UDP> \tUDP initialization -> FAILED!\n");
        fprintf(FID_debug_SendReceiveUDP[index],"\tUDP initialization -> FAILED!\n");
		fflush(FID_debug_SendReceiveUDP[index]);
	}
    else
    {
        printf("<UDP> \tUDP initialization -> OK!\n");
        fprintf(FID_debug_SendReceiveUDP[index],"\tUDP initialization -> OK!\n");
		fflush(FID_debug_SendReceiveUDP[index]);
    }
    return(init_status_SendReceiveUDP[index]);
}

int CleanUpSocket(int index)
{
	int error;
	int CloseStatus = 0;

	// ********************************************************
	// Close the socket
	// ********************************************************
    printf("<UDP> \t\tClose the socket %d: ", socket_id[index]);
    fprintf(FID_debug_SendReceiveUDP[index],"\t\tClose the socket %d: ", socket_id[index]);
	error=closesocket(socket_id[index]);
	if (error!=0)
	{
		printf("<UDP> FAILED! error: %d\n",error);
		fprintf(FID_debug_SendReceiveUDP[index],"FAILED! error: %d\n",error);
		ReportUDPerror(index);
		CloseStatus |= ERROR_CLOSESOCKET;
	}
	else
	{
		printf("OK!\n");
		fprintf(FID_debug_SendReceiveUDP[index],"OK!\n");
	}
	// ********************************************************
	// Close the WinSock (opend with WSAStartup() )
	// ********************************************************
    printf("<UDP> \t\tWSACleanup: ");
    fprintf(FID_debug_SendReceiveUDP[index],"\tWSACleanup: ");
	error=WSACleanup(); // Call this function as many times WSAStartup() was called
	if (error!=0)
    {
		printf("<UDP> FAILED! error : %d %d\n",error,WSAGetLastError());
		fprintf(FID_debug_SendReceiveUDP[index],"FAILED! error : %d %d\n",error,WSAGetLastError());
		CloseStatus |= ERROR_WSACLEANUP;
    }
	else
	{
		printf("<UDP> WSACleanup  : OK\n");
		fprintf(FID_debug_SendReceiveUDP[index],"WSACleanup  : OK\n");
	}
	return(CloseStatus);
}

void ConnectLogUpdate_SendReceiveUDP(FILE* FID_Debug, char* IP_remote_str, int index)
{
	FILE* FID_connect = NULL;
	char readline[20];
	int CleanUp_Asked;
	char NameConnect[200];

	memset(NameConnect, '\0', 200);
	strcat(NameConnect, "./SendReceiveUDP_sources/SendReceiveUDP_log_IP_");
	strcat(NameConnect, IP_remote_str);
	strcat(NameConnect, ".debug");
	
    printf("<UDP> \tConnectLogUpdate_SendReceiveUDP()\n");
    fprintf(FID_Debug,"\tConnectLogUpdate_SendReceiveUDP()\n");
	fflush(FID_Debug);
    
    // read first line of "SendReceiveUDP_log.debug"
	FID_connect = fopen(NameConnect,"r"); // pour le debuggage
	fgets(readline,20,FID_connect);
    printf("<UDP> readline: %s\n", readline);
	fclose(FID_connect);
	FID_connect = NULL;
	
	if (strcmp(readline, "generation")==0)
	{
		printf("<UDP> \t\t COMPILATION\n");
		fprintf(FID_Debug, "\t\t COMPILATION\n");
		FID_connect = fopen(NameConnect,"w"); // pour le debuggage
		fprintf(FID_connect, "mdl_start_connect");
		printf("<UDP> FID_Connect %d, FID_debug_SendReceiveUDP[%d] %d\n", FID_connect, index, FID_debug_SendReceiveUDP[index]);
		fclose(FID_connect);
		FID_connect = NULL;
		CleanUp_Asked = 1;
	}
	
	/*// if it is MATLAB compilation
	if (strcmp(readline, "generation")==0)
	{
		printf("<UDP> \t\t COMPILATION\n");
		fprintf(FID_Debug, "\t\t COMPILATION\n");
		fflush(FID_Debug);
		fclose(FID_connect);
		FID_connect = NULL;
		FID_connect = fopen(NameConnect,"w"); // pour le debuggage
		fprintf(FID_connect, "mdl_start_compile");
		printf("<UDP> \t\tFID_Connect %d, FID_debug_SendReceiveUDP[index] %d\n", FID_connect, FID_Debug);
		fclose(FID_connect);
		FID_connect = NULL;
	}
	
	// if it is MATLAB connect to target
	if ((strcmp(readline, "mdl_start_compile")==0)||(strcmp(readline, "mdl_start_QUARCend")==0))
	{
		printf("<UDP> \t\t CONNECT\n");
		fprintf(FID_Debug, "\t\t CONNECT\n");
		fflush(FID_Debug);
		fclose(FID_connect);
		FID_connect = NULL;
		FID_connect = fopen(NameConnect,"w"); // pour le debuggage
		fprintf(FID_connect, "mdl_start_connect");
		printf("<UDP> \t\tFID_Connect %d, FID_debug_SendReceiveUDP[index] %d\n", FID_connect, FID_Debug);
		fclose(FID_connect);
		FID_connect = NULL;
		CleanUp_Asked = 1;
	}*/
	// if it is QUARC which begins simulation
	if (strcmp(readline, "mdl_start_connect")==0)
	{
		printf("<UDP> \t\t SIMULATION\n");
		fprintf(FID_Debug, "\t\t SIMULATION\n");
		fflush(FID_Debug);
		fflush(FID_Debug);
		FID_connect = fopen(NameConnect,"w"); // pour le debuggage
		fprintf(FID_connect, "mdl_start_QUARCsim");
		printf("<UDP> \t\tFID_Connect %d, FID_debug_SendReceiveUDP[index] %d\n", FID_connect, FID_Debug);
		fclose(FID_connect);
		FID_connect = NULL;
	}
// 	fprintf(FID_Debug,"FID_Connect %d, FID_debug_SendReceiveUDP[index] %d\n", FID_connect, FID_Debug);
//     fprintf(FID_Debug,"init_status_SendReceiveUDP: %u\n", init_status_SendReceiveUDP[index]);
	if (CleanUp_Asked == 1)
		CleanUpMdlStartSendReceiveUDP(index, IP_remote_str);
}

void CleanUpMdlStartSendReceiveUDP(int index, char* IP_remote_str)
{
    char readline[20];
	char NameConnect[200];
	FILE* FID_connect = NULL;

	memset(NameConnect, '\0', 200);
	strcat(NameConnect, "./SendReceiveUDP_sources/SendReceiveUDP_log_IP_");
	strcat(NameConnect, IP_remote_str);
	strcat(NameConnect, ".debug");
	
	printf("<UDP> \tCleanUpMdlStartSendReceiveUDP()\n");
	fprintf(FID_debug_SendReceiveUDP[index], "\tCleanUpMdlStartSendReceiveUDP()\n");
	FID_connect = fopen(NameConnect, "r"); // pour le debuggage
	if (FID_connect == NULL)
	{
		printf("<UDP> \t\tError, can't read 'SendReceiveUDP_log.debug'\n");
		fprintf(FID_debug_SendReceiveUDP[index], "\t\tError, can't read 'SendReceiveUDP_log.debug'\n");
	}
	else
	{
		fgets(readline,20,FID_connect);
		printf("<UDP> \t\tFID_Connect %d, FID_debug_SendReceiveUDP[index] %d\n", FID_connect, FID_debug_SendReceiveUDP[index]);
		fclose(FID_connect);
		FID_connect = NULL;
		if (strcmp(readline, "mdl_start_QUARCsim")==0)
		{
			FID_connect = fopen(NameConnect, "w"); // pour le debuggage
			if (FID_connect == NULL)
			{
				printf("<UDP> \t\tError, can't read 'SendReceiveUDP_log.debug'\n");
				fprintf(FID_debug_SendReceiveUDP[index], "\t\tError, can't read 'SendReceiveUDP_log.debug'\n");
			}
			else
			{
				printf("<UDP> \t\tFID_Connect %d, FID_debug_SendReceiveUDP[index] %d\n", FID_connect, FID_debug_SendReceiveUDP[index]);
				fprintf(FID_connect, "mdl_start_QUARCend");
				fprintf(FID_debug_SendReceiveUDP[index], "\t\tStatus 'mdl_start_QUARCsim' updated to 'mdl_start_QUARCend'\n");
				fclose(FID_connect);
				FID_connect = NULL;
			}
		}
	}
    CleanUpSocket(index);
	printf("<UDP> \tCleanUpMdlStartSendReceiveUDP() -> OK!\n");
	fprintf(FID_debug_SendReceiveUDP[index], "\tCleanUpMdlStartSendReceiveUDP() -> OK!\n");
	printf("FID_debug_SendReceiveUDP[index] %d\n", FID_debug_SendReceiveUDP[index]);
    fprintf(FID_debug_SendReceiveUDP[index], "FID_debug_SendReceiveUDP[index] %d\n", FID_debug_SendReceiveUDP[index]);
    fclose(FID_debug_SendReceiveUDP[index]);
	FID_debug_SendReceiveUDP[index] = NULL;
}

int ReportInitUDPError(int index)
{
	printf("<UDP> INITIALISATION FAILED!\n\tCheck SendReceiveUDP_debug.debug to more details...\n\n");
	fprintf(FID_debug_SendReceiveUDP[index],"INITIALISATION FAILED!\n\tCheck SendReceiveUDP_debug.debug to more details...\n\n");
	fflush(FID_debug_SendReceiveUDP[index]);
	if ((init_status_SendReceiveUDP[index]&0x01)>0)
	{
		printf("<UDP> \tfopen() error! Can not create/write file SendReceiveUDP_debug.debug!\n");
		fprintf(FID_debug_SendReceiveUDP[index],"\tfopen() error! Can not create/write file SendReceiveUDP_debug.debug!\n");
		fflush(FID_debug_SendReceiveUDP[index]);
	}
	if ((init_status_SendReceiveUDP[index]&0x02)>0)
	{
		printf("<UDP> \tWSAStartup() error! Can not initialize WINSOCK!\n");
		fprintf(FID_debug_SendReceiveUDP[index],"\tWSAStartup() error! Can not initialize WINSOCK!\n");
		fflush(FID_debug_SendReceiveUDP[index]);
	}
	if ((init_status_SendReceiveUDP[index]&0x04)>0)
	{
		printf("<UDP> \tsocket() error! Can not create socket!\n");
		fprintf(FID_debug_SendReceiveUDP[index],"\tsocket() error! Can not create socket!\n");
		fflush(FID_debug_SendReceiveUDP[index]);
	}
	if ((init_status_SendReceiveUDP[index]&0x08)>0)
	{
		printf("<UDP> \tbind() error! Can not bind socket!\n");
		printf("<UDP> \t\t => check IP configuration is static\n");
		fprintf(FID_debug_SendReceiveUDP[index],"\tbind() error! Can not bind socket!\n");
		fprintf(FID_debug_SendReceiveUDP[index],"\t\t => check IP configuration is static\n");
		fflush(FID_debug_SendReceiveUDP[index]);		
	}
	return(0);
}

void ReportUDPerror(int index)
{
    int last_error = WSAGetLastError();
    char error_message[256] = "";
    
    switch (last_error)
    {
        case WSAEWOULDBLOCK:
            strcpy(error_message, "Resource temporarily unavailable");
            break;
		case WSANOTINITIALISED:
			strcpy(error_message, "Successful WSAStartup not yet performed");
			break;
        default:
            itoa(last_error, error_message, 10);   
    }
    printf("<UDP> \t\t UDP reception error: %s\n", error_message);
	fprintf(FID_debug_SendReceiveUDP[index], "\t\t UDP reception error: %s\n", error_message);
}

/*********** CLASSIC STREAM OPERATION **********/

int receiveUDPstream(struct sockaddr_in *host_info, SOCKET socket_id, char *buffer, int index)
{
	int src_len=sizeof(*host_info);
	int nb_packet = 0;
    int tempo = sizeof(gumstix_info); // Passe par une variable afin d'utiliser un pointeur
    
	printf("<UDP> \t UDP RECEPTION:\n");
	fprintf(FID_debug_SendReceiveUDP[index], "\t UDP RECEPTION:\n");
	memset(buffer, 0, MAX_BUF); // erase previous data
    
	if (recvfrom(socket_id,buffer,MAX_BUF,RCV_FLAG,(struct sockaddr*)host_info,&tempo)==-1)
	{
        ReportUDPerror(index);
        return(0);
	}
	else
	{
		nb_packet = 1; // one packet was received yet
		printf("<UDP> \t\t Received packet from %s:%d\nData: %s\n", inet_ntoa(host_info->sin_addr), ntohs(host_info->sin_port), buffer);
		fprintf(FID_debug_SendReceiveUDP[index],"\t\t Received packet from %s:%d\nData: %s\n", inet_ntoa(host_info->sin_addr), ntohs(host_info->sin_port), buffer);
		while(recvfrom(socket_id,buffer,MAX_BUF,RCV_FLAG,(struct sockaddr*)host_info,&tempo)!=-1)
		{
			nb_packet++; // another packet was received 
			printf("<UDP> \t\t New packet from %s:%d\nData: %s\n", inet_ntoa(host_info->sin_addr), ntohs(host_info->sin_port), buffer);
            fprintf(FID_debug_SendReceiveUDP[index], "\t\t New packet from %s:%d\nData: %s\n", inet_ntoa(host_info->sin_addr), ntohs(host_info->sin_port), buffer);
            // to be sure to have the last packet
		}
		printf("<UDP> \t\t %d packet(s) received!\n", nb_packet);
		fprintf(FID_debug_SendReceiveUDP[index], "\t\t %d packet(s) received!\n", nb_packet);
        return(1);
	}
}

int sendUDPstream(SOCKADDR_IN *host_info, char *buffer, SOCKET socket_id, int index)
{
	int n_sent;
    
	printf("<UDP> \t UDP SENDING:\n");
	fprintf(FID_debug_SendReceiveUDP[index], "\t UDP SENDING:\n");
		
    // send packet to remote host
    n_sent=sendto(socket_id,buffer,strlen(buffer),0,(struct sockaddr*)host_info,(int)sizeof(*host_info));
    if(n_sent < 0) 
	{
		printf("<UDP> \t\t UDP Send error!!\n");
		fprintf(FID_debug_SendReceiveUDP[index], "\t\t UDP Send error!!\n");
		return(-1);
    }
	else
	{
		printf("<UDP> \t\t Stream: %s successfully sent!\n", buffer);
		fprintf(FID_debug_SendReceiveUDP[index], "\t\t Stream: %s successfully sent!\n", buffer);
	}
    return(n_sent);
}

int formatUDPstream_in(double *tab, char *buf, int nb_waiting_data, int index)
{
	char *pch;
	int nb_formated = 0;
	
	printf("<UDP> \t UDP_IN FORMATAGE:%d\n", nb_waiting_data);
	fprintf(FID_debug_SendReceiveUDP[index], "\t UDP_IN FORMATAGE:%d\n", nb_waiting_data);
	pch = strtok(buf,";");
	while (pch != NULL)
	{
		if (nb_formated <= (nb_waiting_data-1)) // if number of received data is not upper than number of box in the array "tab" 
		{
			tab[nb_formated] = atof(pch); // received data are up to dat in "tab"
			printf("<UDP> \t\t ReceivedData[%d]=%.13f\n",nb_formated, tab[nb_formated]);
			fprintf (FID_debug_SendReceiveUDP[index], "\t\t ReceivedData[%d]=%.13f\n",nb_formated, tab[nb_formated]);
		}
        else
        {
            printf("<UDP> \t\t Too much data received! ReceivedData[%d]=%.13f ignored!\n",nb_formated, tab[nb_formated]);
			fprintf (FID_debug_SendReceiveUDP[index], "\t\t Too much data received! ReceivedData[%d]=%.13f ignored!\n",nb_formated, tab[nb_formated]);
        }
		pch = strtok (NULL, ";");
        nb_formated++;
	}
	return nb_formated;
}

/*************** OPIMIZED STREAM OPERATION *************/

/************ DOUBLE ***********/
void WaitnDouble_UDP(int SocketIndex, SOCKADDR_IN *src_info, double *DoubleToWait, int NbDoubleToWait)
{
	int n_read;
	int index = 0;
	int NbByteToWait = NbDoubleToWait*NB_BYTE_DOUBLE;
	int src_len=sizeof(*src_info);
	int nb_packet = 0;
	#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
		int nb_formated;
	#endif
	
	#ifdef ECHO_PRINTF
		printf("<UDP> WaitnDouble_UDP...\n ");
		printf("\t\t bytes received: ");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> WaitnDouble_UDP...\n ");
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\t\t bytes received: ");
	#endif
	while(index<NbByteToWait)
	{
		n_read = recvfrom(socket_id[SocketIndex],(char *)(DoubleToWait+index),(NbByteToWait-index),RCV_FLAG,(struct sockaddr*)src_info,&src_len);
		if (n_read!= -1)
		{
			index+=n_read;
			#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
				if (n_read != 0)
				{
					#ifdef ECHO_PRINTF
						printf("%d ", index);
					#endif
					#ifdef ECHO_FPRINTF
						fprintf(FID_debug_SendReceiveUDP[SocketIndex], "%d ", index);
					#endif
				}
			#endif
		}
	}
	#ifdef ECHO_PRINTF
		printf("\n");
		printf("<UDP> \t\t Received packet from %s:%d\n", inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
		for (nb_formated = 0; nb_formated<NbDoubleToWait; nb_formated++)
		{
			printf("<UDP> ReceivedDouble[%d] = %.6f\n", nb_formated, DoubleToWait[nb_formated]);
		}
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\n");
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> \t\t Received packet from %s:%d\n", inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
		for (nb_formated = 0; nb_formated<NbDoubleToWait; nb_formated++)
		{
			fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> ReceivedDouble[%d] = %.6f\n", nb_formated, DoubleToWait[nb_formated]);
		}
	#endif
}

void ReadnDouble_UDP(int SocketIndex, SOCKADDR_IN *src_info, double *DoubleToWait, int NbDoubleToWait)
{
	int n_read;
	int NbByteToWait = NbDoubleToWait*NB_BYTE_DOUBLE;
	int src_len=sizeof(*src_info);
	int nb_packet = 0;
	#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
		int nb_formated;
	#endif
	
	#ifdef ECHO_PRINTF
		printf("<UDP> ReadnDouble_UDP...\n ");
		printf("\t\t bytes received: ");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> ReadnDouble_UDP...\n ");
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\t\t bytes received: ");
	#endif
	n_read = recvfrom(socket_id[SocketIndex],(char *)DoubleToWait, NbByteToWait, RCV_FLAG, (struct sockaddr*)src_info, &src_len);
	if (n_read == -1)
	{
		ReportUDPerror(SocketIndex);
	}
	else
	{
		#ifdef ECHO_PRINTF
			printf("\n");
			printf("<UDP> \t\t Received packet from %s:%d\n", inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
			for (nb_formated = 0; nb_formated<NbDoubleToWait; nb_formated++)
			{
				printf("<UDP> ReceivedDouble[%d] = %.6f\n", nb_formated, DoubleToWait[nb_formated]);
			}
		#endif
		#ifdef ECHO_FPRINTF
			fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\n");
			fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> \t\t Received packet from %s:%d\n", inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
			for (nb_formated = 0; nb_formated<NbDoubleToWait; nb_formated++)
			{
				fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> ReceivedDouble[%d] = %.6f\n", nb_formated, DoubleToWait[nb_formated]);
			}
		#endif
	}
}

int ReadLastnDouble_UDP(int SocketIndex, SOCKADDR_IN *src_info, double *DoubleToWait, int NbDoubleToWait)
{
	int n_read;
	int NbByteToWait = NbDoubleToWait*NB_BYTE_DOUBLE;
	int src_len=sizeof(*src_info);
	int nb_packet = 0;
	#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
		int nb_formated;
	#endif
	
	#ifdef ECHO_PRINTF
		printf("<UDP> ReadnDouble_UDP...\n ");
		printf("\t\t bytes received: ");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> ReadnDouble_UDP...\n ");
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\t\t bytes received: ");
	#endif
	do
	{
		n_read = recvfrom(socket_id[SocketIndex],(char *)DoubleToWait, NbByteToWait, RCV_FLAG, (struct sockaddr*)src_info, &src_len);
		if (n_read != -1)
			nb_packet++;
	}
	while(n_read != -1);
	if (nb_packet == 0)
	{
		ReportUDPerror(SocketIndex);
	}
	else
	{
		#ifdef ECHO_PRINTF
			printf("\n");
			printf("<UDP> \t\t %d packet received from %s:%d\n", nb_packet, inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
			for (nb_formated = 0; nb_formated<NbDoubleToWait; nb_formated++)
			{
				printf("<UDP> LastReceivedDouble[%d] = %.6f\n", nb_formated, DoubleToWait[nb_formated]);
			}
		#endif
		#ifdef ECHO_FPRINTF
			fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\n");
			fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> \t\t %d packet received from %s:%d\n", nb_packet, inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
			for (nb_formated = 0; nb_formated<NbDoubleToWait; nb_formated++)
			{
				fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> LastReceivedDouble[%d] = %.6f\n", nb_formated, DoubleToWait[nb_formated]);
			}
		#endif
	}
    return(nb_packet);
}

int SendnDouble_UDP(int SocketIndex, SOCKADDR_IN *dest_info, double *DoubleToSend, int NbDoubleToSend)
{
	int n_sent;
	#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
		int i;
	#endif
	
	 n_sent=sendto(socket_id[SocketIndex],(char *)DoubleToSend,NbDoubleToSend*NB_BYTE_DOUBLE,0,(struct sockaddr*)dest_info,(int)sizeof(*dest_info));

	#ifdef ECHO_PRINTF
		printf("<UDP> SendnDouble_UDP...\n");
		printf("\t %d bytes sent\n\t", n_sent);
		for(i=0; i<NbDoubleToSend; i++)
		{
			printf("%.13f ", DoubleToSend[i]);
		}
		printf("\n");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> SendnDouble_UDP...\n");
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\t %d bytes sent\n\t", n_sent);
		for(i=0; i<NbDoubleToSend; i++)
		{
			fprintf(FID_debug_SendReceiveUDP[SocketIndex], "%.13f ", DoubleToSend[i]);
		}
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\n");
	#endif
	
	return(n_sent);
}

/************ FLOAT32 ***********/
void WaitnFloat_UDP(int SocketIndex, SOCKADDR_IN *src_info, float *Float32ToWait, int NbFloat32ToWait)
{
	int n_read;
	int index = 0;
	int NbByteToWait = NbFloat32ToWait*NB_BYTE_FLOAT;
	int src_len=sizeof(*src_info);
	int nb_packet = 0;
	#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
		int nb_formated;
	#endif
	
	#ifdef ECHO_PRINTF
		printf("<UDP> WaitnFloat32_UDP...\n ");
		printf("\t\t bytes received: ");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> WaitnFloat32_UDP...\n ");
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\t\t bytes received: ");
	#endif
	while(index<NbByteToWait)
	{
		n_read = recvfrom(socket_id[SocketIndex],(char *)(Float32ToWait+index),(NbByteToWait-index),RCV_FLAG,(struct sockaddr*)src_info,&src_len);
		if (n_read!= -1)
		{
			index+=n_read;
			#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
				if (n_read != 0)
				{
					#ifdef ECHO_PRINTF
						printf("%d ", index);
					#endif
					#ifdef ECHO_FPRINTF
						fprintf(FID_debug_SendReceiveUDP[SocketIndex], "%d ", index);
					#endif
				}
			#endif
		}
	}
	#ifdef ECHO_PRINTF
		printf("\n");
		printf("<UDP> \t\t Received packet from %s:%d\n", inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
		for (nb_formated = 0; nb_formated<NbFloat32ToWait; nb_formated++)
		{
			printf("<UDP> ReceivedFloat32[%d] = %.6f\n", nb_formated, Float32ToWait[nb_formated]);
		}
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\n");
		fprintf(FID_debug_SendReceiveUDP[SocketIndex],"<UDP> \t\t Received packet from %s:%d\n", inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
		for (nb_formated = 0; nb_formated<NbFloat32ToWait; nb_formated++)
		{
			fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> ReceivedFloat32[%d] = %.6f\n", nb_formated, Float32ToWait[nb_formated]);
		}
	#endif
}

void ReadnFloat_UDP(int SocketIndex, SOCKADDR_IN *src_info, float *FloatToWait, int NbFloatToWait)
{
	int n_read;
	int NbByteToWait = NbFloatToWait*NB_BYTE_FLOAT;
	int src_len=sizeof(*src_info);
	int nb_packet = 0;
	#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
		int nb_formated;
	#endif
	
	#ifdef ECHO_PRINTF
		printf("<UDP> ReadnFloat_UDP...\n ");
		printf("\t\t bytes received: ");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> ReadnFloat_UDP...\n ");
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\t\t bytes received: ");
	#endif
	n_read = recvfrom(socket_id[SocketIndex],(char *)FloatToWait, NbByteToWait, RCV_FLAG, (struct sockaddr*)src_info, &src_len);
	if (n_read == -1)
	{
		ReportUDPerror(SocketIndex);
	}
	else
	{
		#ifdef ECHO_PRINTF
			printf("\n");
			printf("<UDP> \t\t Received packet from %s:%d\n", inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
			for (nb_formated = 0; nb_formated<NbFloatToWait; nb_formated++)
			{
				printf("<UDP> ReceivedFloat[%d] = %.6f\n", nb_formated, FloatToWait[nb_formated]);
			}
		#endif
		#ifdef ECHO_FPRINTF
			fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\n");
			fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> \t\t Received packet from %s:%d\n", inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
			for (nb_formated = 0; nb_formated<NbFloatToWait; nb_formated++)
			{
				fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> ReceivedFloat[%d] = %.6f\n", nb_formated, FloatToWait[nb_formated]);
			}
		#endif
	}
}

int ReadLastnFloat_UDP(int SocketIndex, SOCKADDR_IN *src_info, float *FloatToWait, int NbFloatToWait)
{
	int n_read;
	int NbByteToWait = NbFloatToWait*NB_BYTE_FLOAT;
	int src_len=sizeof(*src_info);
	int nb_packet = 0;
	#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
		int nb_formated;
	#endif
	
	#ifdef ECHO_PRINTF
		printf("<UDP> ReadnFloat_UDP...\n ");
		printf("\t\t bytes received: ");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> ReadnFloat_UDP...\n ");
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\t\t bytes received: ");
	#endif
	do
	{
		n_read = recvfrom(socket_id[SocketIndex],(char *)FloatToWait, NbByteToWait, RCV_FLAG, (struct sockaddr*)src_info, &src_len);
		if (n_read != -1)
			nb_packet++;
	}
	while(n_read != -1);
	if (nb_packet == 0)
	{
		ReportUDPerror(SocketIndex);
	}
	else
	{
		#ifdef ECHO_PRINTF
			printf("\n");
			printf("<UDP> \t\t %d packet received from %s:%d\n", nb_packet, inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
			for (nb_formated = 0; nb_formated<NbFloatToWait; nb_formated++)
			{
				printf("<UDP> LastReceivedFloat[%d] = %.6f\n", nb_formated, FloatToWait[nb_formated]);
			}
		#endif
		#ifdef ECHO_FPRINTF
			fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\n");
			fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> \t\t %d packet received from %s:%d\n", nb_packet, inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
			for (nb_formated = 0; nb_formated<NbFloatToWait; nb_formated++)
			{
				fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> LastReceivedFloat[%d] = %.6f\n", nb_formated, FloatToWait[nb_formated]);
			}
		#endif
	}
    return(nb_packet);
}

int SendnFloat_UDP(int SocketIndex, SOCKADDR_IN *dest_info, float *Float32ToSend, int NbFloat32ToSend)
{
	int n_sent;
	#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
		int i;
	#endif
	
	 n_sent=sendto(socket_id[SocketIndex],(char *)Float32ToSend,NbFloat32ToSend*NB_BYTE_FLOAT,0,(struct sockaddr*)dest_info,(int)sizeof(*dest_info));

	#ifdef ECHO_PRINTF
		printf("<UDP> SendnFloat32_UDP...\n");
		printf("\t %d bytes sent\n\t", n_sent);
		for(i=0; i<NbFloat32ToSend; i++)
		{
			printf("%.13f ", Float32ToSend[i]);
		}
		printf("\n");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> SendnFloat32_UDP...\n");
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\t %d bytes sent\n\t", n_sent);
		for(i=0; i<NbFloat32ToSend; i++)
		{
			fprintf(FID_debug_SendReceiveUDP[SocketIndex], "%.13f ", Float32ToSend[i]);
		}
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\n");
	#endif
	
	return(n_sent);
}

/************ INT32 ***********/
void WaitnInt32_UDP(int SocketIndex, SOCKADDR_IN *src_info, int *Int32ToWait, int NbInt32ToWait)
{
	int n_read;
	int index = 0;
	int NbByteToWait = NbInt32ToWait*NB_BYTE_INT32;
	int src_len=sizeof(*src_info);
	int nb_packet = 0;
	#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
		int nb_formated;
	#endif

	#ifdef ECHO_PRINTF
		printf("<UDP> WaitnInt32_UDP...\n ");
		printf("\t\t bytes received: ");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> WaitnInt32_UDP...\n ");
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\t\t bytes received: ");
	#endif
	while(index<NbByteToWait)
	{
		n_read = recvfrom(socket_id[SocketIndex],(char *)(Int32ToWait+index),(NbByteToWait-index),RCV_FLAG,(struct sockaddr*)src_info,&src_len);
		if (n_read!= -1)
		{
			index+=n_read;
			#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
				if (n_read != 0)
				{
					#ifdef ECHO_PRINTF
						printf("%d ", index);
					#endif
					#ifdef ECHO_FPRINTF
						fprintf(FID_debug_SendReceiveUDP[SocketIndex], "%d ", index);
					#endif
				}
			#endif
		}
	}
	#ifdef ECHO_PRINTF
		printf("\n");
		printf("<UDP> \t\t Received packet from %s:%d\n", inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
		for (nb_formated = 0; nb_formated<NbInt32ToWait; nb_formated++)
		{
			printf("<UDP> ReceivedInt32[%d] = %d\n", nb_formated, Int32ToWait[nb_formated]);
		}
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\n");
		fprintf(FID_debug_SendReceiveUDP[SocketIndex],"<UDP> \t\t Received packet from %s:%d\n", inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
		for (nb_formated = 0; nb_formated<NbInt32ToWait; nb_formated++)
		{
			fprintf(FID_debug_SendReceiveUDP[SocketIndex],"<UDP> ReceivedInt32[%d] = %d\n", nb_formated, Int32ToWait[nb_formated]);
		}
	#endif
}

void ReadnInt32_UDP(int SocketIndex, SOCKADDR_IN *src_info, int *Int32ToWait, int NbInt32ToWait)
{
	int n_read;
	int NbByteToWait = NbInt32ToWait*NB_BYTE_INT32;
	int src_len=sizeof(*src_info);
	#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
		int nb_formated;
	#endif

	#ifdef ECHO_PRINTF
		printf("<UDP> ReadnInt32_UDP...\n ");
		printf("\t\t bytes received: ");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> ReadnInt32_UDP...\n ");
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\t\t bytes received: ");
	#endif
	n_read = recvfrom(socket_id[SocketIndex],(char *)Int32ToWait, NbByteToWait, RCV_FLAG, (struct sockaddr*)src_info, &src_len);
	if (n_read == -1)
	{
		ReportUDPerror(SocketIndex);
	}
	else
	{
		#ifdef ECHO_PRINTF
			printf("\n");
			printf("<UDP> \t\t Received packet from %s:%d\n", inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
			for (nb_formated = 0; nb_formated<NbInt32ToWait; nb_formated++)
			{
				printf("<UDP> ReceivedInt32[%d] = %d\n", nb_formated, Int32ToWait[nb_formated]);
			}
		#endif
		#ifdef ECHO_FPRINTF
			fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\n");
			fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> \t\t Received packet from %s:%d\n", inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
			for (nb_formated = 0; nb_formated<NbInt32ToWait; nb_formated++)
			{
				fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> ReceivedInt32[%d] = %d\n", nb_formated, Int32ToWait[nb_formated]);
			}
		#endif
	}
}

int ReadLastnInt32_UDP(int SocketIndex, SOCKADDR_IN *src_info, int *Int32ToWait, int NbInt32ToWait)
{
	int n_read;
	int NbByteToWait = NbInt32ToWait*NB_BYTE_INT32;
	int src_len=sizeof(*src_info);
	int nb_packet = 0;
	#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
		int nb_formated;
	#endif

	#ifdef ECHO_PRINTF
		printf("<UDP> ReadnInt32_UDP...\n ");
		printf("\t\t bytes received: ");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> ReadnInt32_UDP...\n ");
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\t\t bytes received: ");
	#endif
	do
	{
		n_read = recvfrom(socket_id[SocketIndex],(char *)Int32ToWait, NbByteToWait, RCV_FLAG, (struct sockaddr*)src_info, &src_len);
		if (n_read != -1)
			nb_packet++;
	}
	while(n_read != -1);
	if (nb_packet == 0)
	{
		ReportUDPerror(SocketIndex);
	}
	else
	{
		#ifdef ECHO_PRINTF
			printf("\n");
			printf("<UDP> \t\t %d packet received from %s:%d\n", nb_packet, inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
			for (nb_formated = 0; nb_formated<NbInt32ToWait; nb_formated++)
			{
				printf("<UDP> LastReceivedInt32[%d] = %d\n", nb_formated, Int32ToWait[nb_formated]);
			}
		#endif
		#ifdef ECHO_FPRINTF
			fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\n");
			fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> \t\t %d packet received from %s:%d\n", nb_packet, inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
			for (nb_formated = 0; nb_formated<NbInt32ToWait; nb_formated++)
			{
				fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> LastReceivedInt32[%d] = %d\n", nb_formated, Int32ToWait[nb_formated]);
			}
		#endif
	}
    return(nb_packet);
}

int SendnInt32_UDP(int SocketIndex, SOCKADDR_IN *dest_info, int *Int32ToSend, int NbInt32ToSend)
{
	int n_sent;
	#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
		int i;
	#endif
	
	 n_sent=sendto(socket_id[SocketIndex],(char *)Int32ToSend,NbInt32ToSend*NB_BYTE_INT32,0,(struct sockaddr*)dest_info,(int)sizeof(*dest_info));

	#ifdef ECHO_PRINTF
		printf("<UDP> SendnInt32_UDP...\n");
		printf("\t %d bytes sent\n\t", n_sent);
		for(i=0; i<NbInt32ToSend; i++)
		{
			printf("%d ", Int32ToSend[i]);
		}
		printf("\n");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> SendnInt32_UDP...\n");
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\t %d bytes sent\n\t", n_sent);
		for(i=0; i<NbInt32ToSend; i++)
		{
			fprintf(FID_debug_SendReceiveUDP[SocketIndex], "%d ", Int32ToSend[i]);
		}
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\n");
	#endif
	
	return(n_sent);
}

/************ UINT32 ***********/
void WaitnUInt32_UDP(int SocketIndex, SOCKADDR_IN *src_info, unsigned int *UInt32ToWait, int NbUInt32ToWait)
{
	int n_read;
	int index = 0;
	int NbByteToWait = NbUInt32ToWait*NB_BYTE_UINT32;
	int src_len=sizeof(*src_info);
	int nb_packet = 0;
	#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
		int nb_formated;
	#endif

	#ifdef ECHO_PRINTF
		printf("<UDP> WaitnUInt32_UDP...\n ");
		printf("\t\t bytes received: ");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> WaitnUInt32_UDP...\n ");
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\t\t bytes received: ");
	#endif
	while(index<NbByteToWait)
	{
		n_read = recvfrom(socket_id[SocketIndex],(char *)(UInt32ToWait+index),(NbByteToWait-index),RCV_FLAG,(struct sockaddr*)src_info,&src_len);
		if (n_read!= -1)
		{
			index+=n_read;
			#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
				if (n_read != 0)
				{
					#ifdef ECHO_PRINTF
						printf("%d ", index);
					#endif
					#ifdef ECHO_FPRINTF
						fprintf(FID_debug_SendReceiveUDP[SocketIndex], "%d ", index);
					#endif
				}
			#endif
		}
	}
	#ifdef ECHO_PRINTF
		printf("\n");
		printf("<UDP> \t\t Received packet from %s:%d\n", inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
		for (nb_formated = 0; nb_formated<NbUInt32ToWait; nb_formated++)
		{
			printf("<UDP> ReceivedUInt32[%d] = %u\n", nb_formated, UInt32ToWait[nb_formated]);
		}
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\n");
		fprintf(FID_debug_SendReceiveUDP[SocketIndex],"<UDP> \t\t Received packet from %s:%d\n", inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
		for (nb_formated = 0; nb_formated<NbUInt32ToWait; nb_formated++)
		{
			fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> ReceivedUInt32[%d] = %u\n", nb_formated, UInt32ToWait[nb_formated]);
		}
	#endif
}

void ReadnUInt32_UDP(int SocketIndex, SOCKADDR_IN *src_info, unsigned int *UInt32ToWait, int NbUInt32ToWait)
{
	int n_read;
	int NbByteToWait = NbUInt32ToWait*NB_BYTE_UINT32;
	int src_len=sizeof(*src_info);
	#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
		int nb_formated;
	#endif

	#ifdef ECHO_PRINTF
		printf("<UDP> ReadnUInt32_UDP...\n ");
		printf("\t\t bytes received: ");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> ReadnUInt32_UDP...\n ");
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\t\t bytes received: ");
	#endif
	n_read = recvfrom(socket_id[SocketIndex],(char *)UInt32ToWait, NbByteToWait, RCV_FLAG, (struct sockaddr*)src_info, &src_len);
	if (n_read == -1)
	{
		ReportUDPerror(SocketIndex);
	}
	else
	{
		#ifdef ECHO_PRINTF
			printf("\n");
			printf("<UDP> \t\t Received packet from %s:%d\n", inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
			for (nb_formated = 0; nb_formated<NbUInt32ToWait; nb_formated++)
			{
				printf("<UDP> ReceivedUInt32[%d] = %u\n", nb_formated, UInt32ToWait[nb_formated]);
			}
		#endif
		#ifdef ECHO_FPRINTF
			fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\n");
			fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> \t\t Received packet from %s:%d\n", inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
			for (nb_formated = 0; nb_formated<NbUInt32ToWait; nb_formated++)
			{
				fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> ReceivedUInt32[%d] = %u\n", nb_formated, UInt32ToWait[nb_formated]);
			}
		#endif
	}
}

int ReadLastnUInt32_UDP(int SocketIndex, SOCKADDR_IN *src_info, unsigned int *UInt32ToWait, int NbUInt32ToWait)
{
	int n_read;
	int NbByteToWait = NbUInt32ToWait*NB_BYTE_UINT32;
	int src_len=sizeof(*src_info);
	int nb_packet = 0;
	#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
		int nb_formated;
	#endif

	#ifdef ECHO_PRINTF
		printf("<UDP> ReadnUInt32_UDP...\n ");
		printf("\t\t bytes received: ");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> ReadnUInt32_UDP...\n ");
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\t\t bytes received: ");
	#endif
	do
	{
		n_read = recvfrom(socket_id[SocketIndex],(char *)UInt32ToWait, NbByteToWait, RCV_FLAG, (struct sockaddr*)src_info, &src_len);
		if (n_read != -1)
			nb_packet++;
	}
	while(n_read != -1);
	if (nb_packet == 0)
	{
		ReportUDPerror(SocketIndex);
	}
	else
	{
		#ifdef ECHO_PRINTF
			printf("\n");
			printf("<UDP> \t\t %d packet received from %s:%d\n", nb_packet, inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
			for (nb_formated = 0; nb_formated<NbUInt32ToWait; nb_formated++)
			{
				printf("<UDP> LastReceivedUInt32[%d] = %u\n", nb_formated, UInt32ToWait[nb_formated]);
			}
		#endif
		#ifdef ECHO_FPRINTF
			fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\n");
			fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> \t\t %d packet received from %s:%d\n", nb_packet, inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
			for (nb_formated = 0; nb_formated<NbUInt32ToWait; nb_formated++)
			{
				fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> LastReceivedUInt32[%d] = %u\n", nb_formated, UInt32ToWait[nb_formated]);
			}
		#endif
	}
    return(nb_packet);
}

int SendnUInt32_UDP(int SocketIndex, SOCKADDR_IN *dest_info, unsigned int *UInt32ToSend, int NbUInt32ToSend)
{
	int n_sent;
	#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
		int i;
	#endif
	
	 n_sent=sendto(socket_id[SocketIndex],(char *)UInt32ToSend,NbUInt32ToSend*NB_BYTE_UINT32,0,(struct sockaddr*)dest_info,(int)sizeof(*dest_info));

	#ifdef ECHO_PRINTF
		printf("<UDP> SendnUInt32_UDP...\n");
		printf("\t %d bytes sent\n\t", n_sent);
		for(i=0; i<NbUInt32ToSend; i++)
		{
			printf("%u ", UInt32ToSend[i]);
		}
		printf("\n");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> SendnUInt32_UDP...\n");
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\t %d bytes sent\n\t", n_sent);
		for(i=0; i<NbUInt32ToSend; i++)
		{
			fprintf(FID_debug_SendReceiveUDP[SocketIndex], "%u ", UInt32ToSend[i]);
		}
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\n");
	#endif
	
	return(n_sent);
}

/************ INT16 ***********/
void WaitnInt16_UDP(int SocketIndex, SOCKADDR_IN *src_info, short *Int16ToWait, int NbInt16ToWait)
{
	int n_read;
	int index = 0;
	int NbByteToWait = NbInt16ToWait*NB_BYTE_INT16;
	int src_len=sizeof(*src_info);
	int nb_packet = 0;
	#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
		int nb_formated;
	#endif

	#ifdef ECHO_PRINTF
		printf("<UDP> WaitnInt16_UDP...\n ");
		printf("\t\t bytes received: ");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> WaitnInt16_UDP...\n ");
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\t\t bytes received: ");
	#endif
	while(index<NbByteToWait)
	{
		n_read = recvfrom(socket_id[SocketIndex],(char *)(Int16ToWait+index),(NbByteToWait-index),RCV_FLAG,(struct sockaddr*)src_info,&src_len);
		if (n_read!= -1)
		{
			index+=n_read;
			#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
				if (n_read != 0)
				{
					#ifdef ECHO_PRINTF
						printf("%d ", index);
					#endif
					#ifdef ECHO_FPRINTF
						fprintf(FID_debug_SendReceiveUDP[SocketIndex], "%d ", index);
					#endif
				}
			#endif
		}
	}
	#ifdef ECHO_PRINTF
		printf("\n");
		printf("<UDP> \t\t Received packet from %s:%d\n", inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
		for (nb_formated = 0; nb_formated<NbInt16ToWait; nb_formated++)
		{
			printf("<UDP> ReceivedInt16[%d] = %d\n", nb_formated, Int16ToWait[nb_formated]);
		}
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\n");
		fprintf(FID_debug_SendReceiveUDP[SocketIndex],"<UDP> \t\t Received packet from %s:%d\n", inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
		for (nb_formated = 0; nb_formated<NbInt16ToWait; nb_formated++)
		{
			fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> ReceivedInt16[%d] = %d\n", nb_formated, Int16ToWait[nb_formated]);
		}
	#endif
}

void ReadnInt16_UDP(int SocketIndex, SOCKADDR_IN *src_info, short *Int16ToWait, int NbInt16ToWait)
{
	int n_read;
	int NbByteToWait = NbInt16ToWait*NB_BYTE_INT16;
	int src_len=sizeof(*src_info);
	#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
		int nb_formated;
	#endif

	#ifdef ECHO_PRINTF
		printf("<UDP> ReadnInt16_UDP...\n ");
		printf("\t\t bytes received: ");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> ReadnInt16_UDP...\n ");
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\t\t bytes received: ");
	#endif
	n_read = recvfrom(socket_id[SocketIndex],(char *)Int16ToWait, NbByteToWait, RCV_FLAG, (struct sockaddr*)src_info, &src_len);
	if (n_read == -1)
	{
		ReportUDPerror(SocketIndex);
	}
	else
	{
		#ifdef ECHO_PRINTF
			printf("\n");
			printf("<UDP> \t\t Received packet from %s:%d\n", inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
			for (nb_formated = 0; nb_formated<NbInt16ToWait; nb_formated++)
			{
				printf("<UDP> ReceivedInt16[%d] = %d\n", nb_formated, Int16ToWait[nb_formated]);
			}
		#endif
		#ifdef ECHO_FPRINTF
			fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\n");
			fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> \t\t Received packet from %s:%d\n", inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
			for (nb_formated = 0; nb_formated<NbInt16ToWait; nb_formated++)
			{
				fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> ReceivedInt16[%d] = %d\n", nb_formated, Int16ToWait[nb_formated]);
			}
		#endif
	}
}

int ReadLastnInt16_UDP(int SocketIndex, SOCKADDR_IN *src_info, short *Int16ToWait, int NbInt16ToWait)
{
	int n_read;
	int NbByteToWait = NbInt16ToWait*NB_BYTE_INT16;
	int src_len=sizeof(*src_info);
	int nb_packet = 0;
	#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
		int nb_formated;
	#endif

	#ifdef ECHO_PRINTF
		printf("<UDP> ReadnInt16_UDP...\n ");
		printf("\t\t bytes received: ");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> ReadnInt16_UDP...\n ");
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\t\t bytes received: ");
	#endif
	do
	{
		n_read = recvfrom(socket_id[SocketIndex],(char *)Int16ToWait, NbByteToWait, RCV_FLAG, (struct sockaddr*)src_info, &src_len);
		if (n_read != -1)
			nb_packet++;
	}
	while(n_read != -1);
	if (nb_packet == 0)
	{
		ReportUDPerror(SocketIndex);
	}
	else
	{
		#ifdef ECHO_PRINTF
			printf("\n");
			printf("<UDP> \t\t %d packet received from %s:%d\n", nb_packet, inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
			for (nb_formated = 0; nb_formated<NbInt16ToWait; nb_formated++)
			{
				printf("<UDP> LastReceivedInt16[%d] = %d\n", nb_formated, Int16ToWait[nb_formated]);
			}
		#endif
		#ifdef ECHO_FPRINTF
			fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\n");
			fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> \t\t %d packet received from %s:%d\n", nb_packet, inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
			for (nb_formated = 0; nb_formated<NbInt16ToWait; nb_formated++)
			{
				fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> LastReceivedInt16[%d] = %d\n", nb_formated, Int16ToWait[nb_formated]);
			}
		#endif
	}
    return(nb_packet);
}

int SendnInt16_UDP(int SocketIndex, SOCKADDR_IN *dest_info, short *Int16ToSend, int NbInt16ToSend)
{
	int n_sent;
	#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
		int i;
	#endif
	
	 n_sent=sendto(socket_id[SocketIndex],(char *)Int16ToSend,NbInt16ToSend*NB_BYTE_INT16,0,(struct sockaddr*)dest_info,(int)sizeof(*dest_info));

	#ifdef ECHO_PRINTF
		printf("<UDP> SendnInt16_UDP...\n");
		printf("\t %d bytes sent\n\t", n_sent);
		for(i=0; i<NbInt16ToSend; i++)
		{
			printf("%d ", Int16ToSend[i]);
		}
		printf("\n");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> SendnInt16_UDP...\n");
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\t %d bytes sent\n\t", n_sent);
		for(i=0; i<NbInt16ToSend; i++)
		{
			fprintf(FID_debug_SendReceiveUDP[SocketIndex], "%d ", Int16ToSend[i]);
		}
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\n");
	#endif
	
	return(n_sent);
}

/************ UINT16 ***********/
void WaitnUInt16_UDP(int SocketIndex, SOCKADDR_IN *src_info, unsigned short *UInt16ToWait, int NbUInt16ToWait)
{
	int n_read;
	int index = 0;
	int NbByteToWait = NbUInt16ToWait*NB_BYTE_UINT16;
	int src_len=sizeof(*src_info);
	int nb_packet = 0;
	#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
		int nb_formated;
	#endif

	#ifdef ECHO_PRINTF
		printf("<UDP> WaitnUInt16_UDP...\n ");
		printf("\t\t bytes received: ");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> WaitnUInt16_UDP...\n ");
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\t\t bytes received: ");
	#endif
	while(index<NbByteToWait)
	{
		n_read = recvfrom(socket_id[SocketIndex],(char *)(UInt16ToWait+index),(NbByteToWait-index),RCV_FLAG,(struct sockaddr*)src_info,&src_len);
		if (n_read!= -1)
		{
			index+=n_read;
			#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
				if (n_read != 0)
				{
					#ifdef ECHO_PRINTF
						printf("%d ", index);
					#endif
					#ifdef ECHO_FPRINTF
						fprintf(FID_debug_SendReceiveUDP[SocketIndex], "%d ", index);
					#endif
				}
			#endif
		}
	}
	#ifdef ECHO_PRINTF
		printf("\n");
		printf("<UDP> \t\t Received packet from %s:%d\n", inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
		for (nb_formated = 0; nb_formated<NbUInt16ToWait; nb_formated++)
		{
			printf("<UDP> ReceivedUInt16[%d] = %u\n", nb_formated, UInt16ToWait[nb_formated]);
		}
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\n");
		fprintf(FID_debug_SendReceiveUDP[SocketIndex],"<UDP> \t\t Received packet from %s:%d\n", inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
		for (nb_formated = 0; nb_formated<NbUInt16ToWait; nb_formated++)
		{
			fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> ReceivedUInt16[%d] = %u\n", nb_formated, UInt16ToWait[nb_formated]);
		}
	#endif
}

void ReadnUInt16_UDP(int SocketIndex, SOCKADDR_IN *src_info, unsigned short *UInt16ToWait, int NbUInt16ToWait)
{
	int n_read;
	int NbByteToWait = NbUInt16ToWait*NB_BYTE_UINT16;
	int src_len=sizeof(*src_info);
	#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
		int nb_formated;
	#endif

	#ifdef ECHO_PRINTF
		printf("<UDP> ReadnUInt16_UDP...\n ");
		printf("\t\t bytes received: ");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> ReadnUInt16_UDP...\n ");
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\t\t bytes received: ");
	#endif
	n_read = recvfrom(socket_id[SocketIndex],(char *)UInt16ToWait, NbByteToWait, RCV_FLAG, (struct sockaddr*)src_info, &src_len);
	if (n_read == -1)
	{
		ReportUDPerror(SocketIndex);
	}
	else
	{
		#ifdef ECHO_PRINTF
			printf("\n");
			printf("<UDP> \t\t Received packet from %s:%d\n", inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
			for (nb_formated = 0; nb_formated<NbUInt16ToWait; nb_formated++)
			{
				printf("<UDP> ReceivedUInt16[%d] = %u\n", nb_formated, UInt16ToWait[nb_formated]);
			}
		#endif
		#ifdef ECHO_FPRINTF
			fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\n");
			fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> \t\t Received packet from %s:%d\n", inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
			for (nb_formated = 0; nb_formated<NbUInt16ToWait; nb_formated++)
			{
				fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> ReceivedUInt16[%d] = %u\n", nb_formated, UInt16ToWait[nb_formated]);
			}
		#endif
	}
}

int ReadLastnUInt16_UDP(int SocketIndex, SOCKADDR_IN *src_info, unsigned short *UInt16ToWait, int NbUInt16ToWait)
{
	int n_read;
	int NbByteToWait = NbUInt16ToWait*NB_BYTE_UINT16;
	int src_len=sizeof(*src_info);
	int nb_packet = 0;
	#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
		int nb_formated;
	#endif

	#ifdef ECHO_PRINTF
		printf("<UDP> ReadnUInt16_UDP...\n ");
		printf("\t\t bytes received: ");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> ReadnUInt16_UDP...\n ");
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\t\t bytes received: ");
	#endif
	do
	{
		n_read = recvfrom(socket_id[SocketIndex],(char *)UInt16ToWait, NbByteToWait, RCV_FLAG, (struct sockaddr*)src_info, &src_len);
		if (n_read != -1)
			nb_packet++;
	}
	while(n_read != -1);
	if (nb_packet == 0)
	{
		ReportUDPerror(SocketIndex);
	}
	else
	{
		#ifdef ECHO_PRINTF
			printf("\n");
			printf("<UDP> \t\t %d packet received from %s:%d\n", nb_packet, inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
			for (nb_formated = 0; nb_formated<NbUInt16ToWait; nb_formated++)
			{
				printf("<UDP> LastReceivedUInt16[%d] = %u\n", nb_formated, UInt16ToWait[nb_formated]);
			}
		#endif
		#ifdef ECHO_FPRINTF
			fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\n");
			fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> \t\t %d packet received from %s:%d\n", nb_packet, inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
			for (nb_formated = 0; nb_formated<NbUInt16ToWait; nb_formated++)
			{
				fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> LastReceivedUInt16[%d] = %u\n", nb_formated, UInt16ToWait[nb_formated]);
			}
		#endif
	}
    return(nb_packet);
}

int SendnUInt16_UDP(int SocketIndex, SOCKADDR_IN *dest_info, unsigned short *UInt16ToSend, int NbUInt16ToSend)
{
	int n_sent;
	#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
		int i;
	#endif
	
	 n_sent=sendto(socket_id[SocketIndex],(char *)UInt16ToSend,NbUInt16ToSend*NB_BYTE_UINT16,0,(struct sockaddr*)dest_info,(int)sizeof(*dest_info));

	#ifdef ECHO_PRINTF
		printf("<UDP> SendnUInt16_UDP...\n");
		printf("\t %d bytes sent\n\t", n_sent);
		for(i=0; i<NbUInt16ToSend; i++)
		{
			printf("%u ", UInt16ToSend[i]);
		}
		printf("\n");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> SendnUInt16_UDP...\n");
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\t %d bytes sent\n\t", n_sent);
		for(i=0; i<NbUInt16ToSend; i++)
		{
			fprintf(FID_debug_SendReceiveUDP[SocketIndex], "%u ", UInt16ToSend[i]);
		}
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\n");
	#endif
	
	return(n_sent);
}

/************ CHAR8 ***********/
void WaitnChar8_UDP(int SocketIndex, SOCKADDR_IN *src_info, char *Char8ToWait, int NbChar8ToWait)
{
	int n_read;
	int index = 0;
	int NbByteToWait = NbChar8ToWait*NB_BYTE_CHAR8;
	int src_len=sizeof(*src_info);
	int nb_packet = 0;
	#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
		int nb_formated;
	#endif

	#ifdef ECHO_PRINTF
		printf("<UDP> WaitnChar8_UDP...\n ");
		printf("\t\t bytes received: ");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> WaitnChar8_UDP...\n ");
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\t\t bytes received: ");
	#endif
	while(index<NbByteToWait)
	{
		n_read = recvfrom(socket_id[SocketIndex],(char *)(Char8ToWait+index),(NbByteToWait-index),RCV_FLAG,(struct sockaddr*)src_info,&src_len);
		if (n_read!= -1)
		{
			index+=n_read;
			#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
				if (n_read != 0)
				{
					#ifdef ECHO_PRINTF
						printf("%d ", index);
					#endif
					#ifdef ECHO_FPRINTF
						fprintf(FID_debug_SendReceiveUDP[SocketIndex], "%d ", index);
					#endif
				}
			#endif
		}
	}
	#ifdef ECHO_PRINTF
		printf("\n");
		printf("<UDP> \t\t Received packet from %s:%d\n", inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
		for (nb_formated = 0; nb_formated<NbChar8ToWait; nb_formated++)
		{
			printf("<UDP> ReceivedChar8[%d] = %d\n", nb_formated, Char8ToWait[nb_formated]);
		}
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\n");
		fprintf(FID_debug_SendReceiveUDP[SocketIndex],"<UDP> \t\t Received packet from %s:%d\n", inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
		for (nb_formated = 0; nb_formated<NbChar8ToWait; nb_formated++)
		{
			fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> ReceivedChar8[%d] = %d\n", nb_formated, Char8ToWait[nb_formated]);
		}
	#endif
}

void ReadnChar8_UDP(int SocketIndex, SOCKADDR_IN *src_info, char *Char8ToWait, int NbChar8ToWait)
{
	int n_read;
	int NbByteToWait = NbChar8ToWait*NB_BYTE_CHAR8;
	int src_len=sizeof(*src_info);
	#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
		int nb_formated;
	#endif

	#ifdef ECHO_PRINTF
		printf("<UDP> ReadnChar8_UDP...\n ");
		printf("\t\t bytes received: ");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> ReadnChar8_UDP...\n ");
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\t\t bytes received: ");
	#endif
	n_read = recvfrom(socket_id[SocketIndex],(char *)Char8ToWait, NbByteToWait, RCV_FLAG, (struct sockaddr*)src_info, &src_len);
	if (n_read == -1)
	{
		ReportUDPerror(SocketIndex);
	}
	else
	{
		#ifdef ECHO_PRINTF
			printf("\n");
			printf("<UDP> \t\t Received packet from %s:%d\n", inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
			for (nb_formated = 0; nb_formated<NbChar8ToWait; nb_formated++)
			{
				printf("<UDP> ReceivedChar8[%d] = %d\n", nb_formated, Char8ToWait[nb_formated]);
			}
		#endif
		#ifdef ECHO_FPRINTF
			fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\n");
			fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> \t\t Received packet from %s:%d\n", inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
			for (nb_formated = 0; nb_formated<NbChar8ToWait; nb_formated++)
			{
				fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> ReceivedChar8[%d] = %d\n", nb_formated, Char8ToWait[nb_formated]);
			}
		#endif
	}
}

int ReadLastnChar8_UDP(int SocketIndex, SOCKADDR_IN *src_info, char *Char8ToWait, int NbChar8ToWait)
{
	int n_read;
	int NbByteToWait = NbChar8ToWait*NB_BYTE_CHAR8;
	int src_len=sizeof(*src_info);
	int nb_packet = 0;
	#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
		int nb_formated;
	#endif

	#ifdef ECHO_PRINTF
		printf("<UDP> ReadnChar8_UDP...\n ");
		printf("\t\t bytes received: ");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> ReadnChar8_UDP...\n ");
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\t\t bytes received: ");
	#endif
	do
	{
		n_read = recvfrom(socket_id[SocketIndex],(char *)Char8ToWait, NbByteToWait, RCV_FLAG, (struct sockaddr*)src_info, &src_len);
		if (n_read != -1)
			nb_packet++;
	}
	while(n_read != -1);
	if (nb_packet == 0)
	{
		ReportUDPerror(SocketIndex);
	}
	else
	{
		#ifdef ECHO_PRINTF
			printf("\n");
			printf("<UDP> \t\t %d packet received from %s:%d\n", nb_packet, inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
			for (nb_formated = 0; nb_formated<NbChar8ToWait; nb_formated++)
			{
				printf("<UDP> LastReceivedChar8[%d] = %d\n", nb_formated, Char8ToWait[nb_formated]);
			}
		#endif
		#ifdef ECHO_FPRINTF
			fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\n");
			fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> \t\t %d packet received from %s:%d\n", nb_packet, inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
			for (nb_formated = 0; nb_formated<NbChar8ToWait; nb_formated++)
			{
				fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> LastReceivedChar8[%d] = %d\n", nb_formated, Char8ToWait[nb_formated]);
			}
		#endif
	}
    return(nb_packet);
}

int SendnChar8_UDP(int SocketIndex, SOCKADDR_IN *dest_info, char *Char8ToSend, int NbChar8ToSend)
{
	int n_sent;
	#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
		int i;
	#endif
	
	 n_sent=sendto(socket_id[SocketIndex],(char *)Char8ToSend,NbChar8ToSend*NB_BYTE_CHAR8,0,(struct sockaddr*)dest_info,(int)sizeof(*dest_info));

	#ifdef ECHO_PRINTF
		printf("<UDP> SendnChar8_UDP...\n");
		printf("\t %d bytes sent\n\t", n_sent);
		for(i=0; i<NbChar8ToSend; i++)
		{
			printf("%d ", Char8ToSend[i]);
		}
		printf("\n");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> SendnChar8_UDP...\n");
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\t %d bytes sent\n\t", n_sent);
		for(i=0; i<NbChar8ToSend; i++)
		{
			fprintf(FID_debug_SendReceiveUDP[SocketIndex], "%d ", Char8ToSend[i]);
		}
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\n");
	#endif
	
	return(n_sent);
}

/************ UCHAR8 ***********/
void WaitnUChar8_UDP(int SocketIndex, SOCKADDR_IN *src_info, unsigned char *UChar8ToWait, int NbUChar8ToWait)
{
	int n_read;
	int index = 0;
	int NbByteToWait = NbUChar8ToWait*NB_BYTE_UCHAR8;
	int src_len=sizeof(*src_info);
	int nb_packet = 0;
	#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
		int nb_formated;
	#endif

	#ifdef ECHO_PRINTF
		printf("<UDP> WaitnUChar8_UDP...\n ");
		printf("\t\t bytes received: ");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> WaitnUChar8_UDP...\n ");
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\t\t bytes received: ");
	#endif
	while(index<NbByteToWait)
	{
		n_read = recvfrom(socket_id[SocketIndex],(char *)(UChar8ToWait+index),(NbByteToWait-index),RCV_FLAG,(struct sockaddr*)src_info,&src_len);
		if (n_read!= -1)
		{
			index+=n_read;
			#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
				if (n_read != 0)
				{
					#ifdef ECHO_PRINTF
						printf("%d ", index);
					#endif
					#ifdef ECHO_FPRINTF
						fprintf(FID_debug_SendReceiveUDP[SocketIndex], "%d ", index);
					#endif
				}
			#endif
		}
	}
	#ifdef ECHO_PRINTF
		printf("\n");
		printf("<UDP> \t\t Received packet from %s:%d\n", inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
		for (nb_formated = 0; nb_formated<NbUChar8ToWait; nb_formated++)
		{
			printf("<UDP> ReceivedUChar8[%d] = %u\n", nb_formated, UChar8ToWait[nb_formated]);
		}
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\n");
		fprintf(FID_debug_SendReceiveUDP[SocketIndex],"<UDP> \t\t Received packet from %s:%d\n", inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
		for (nb_formated = 0; nb_formated<NbUChar8ToWait; nb_formated++)
		{
			fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> ReceivedUChar8[%d] = %u\n", nb_formated, UChar8ToWait[nb_formated]);
		}
	#endif
}

void ReadnUChar8_UDP(int SocketIndex, SOCKADDR_IN *src_info, unsigned char *UChar8ToWait, int NbUChar8ToWait)
{
	int n_read;
	int NbByteToWait = NbUChar8ToWait*NB_BYTE_UCHAR8;
	int src_len=sizeof(*src_info);
	#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
		int nb_formated;
	#endif

	#ifdef ECHO_PRINTF
		printf("<UDP> ReadnUChar8_UDP...\n ");
		printf("\t\t bytes received: ");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> ReadnUChar8_UDP...\n ");
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\t\t bytes received: ");
	#endif
	n_read = recvfrom(socket_id[SocketIndex],(char *)UChar8ToWait, NbByteToWait, RCV_FLAG, (struct sockaddr*)src_info, &src_len);
	if (n_read == -1)
	{
		ReportUDPerror(SocketIndex);
	}
	else
	{
		#ifdef ECHO_PRINTF
			printf("\n");
			printf("<UDP> \t\t Received packet from %s:%d\n", inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
			for (nb_formated = 0; nb_formated<NbUChar8ToWait; nb_formated++)
			{
				printf("<UDP> ReceivedUChar8[%d] = %u\n", nb_formated, UChar8ToWait[nb_formated]);
			}
		#endif
		#ifdef ECHO_FPRINTF
			fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\n");
			fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> \t\t Received packet from %s:%d\n", inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
			for (nb_formated = 0; nb_formated<NbUChar8ToWait; nb_formated++)
			{
				fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> ReceivedUChar8[%d] = %u\n", nb_formated, UChar8ToWait[nb_formated]);
			}
		#endif
	}
}

int ReadLastnUChar8_UDP(int SocketIndex, SOCKADDR_IN *src_info, unsigned char *UChar8ToWait, int NbUChar8ToWait)
{
	int n_read;
	int NbByteToWait = NbUChar8ToWait*NB_BYTE_UCHAR8;
	int src_len=sizeof(*src_info);
	int nb_packet = 0;
	#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
		int nb_formated;
	#endif

	#ifdef ECHO_PRINTF
		printf("<UDP> ReadnUChar8_UDP...\n ");
		printf("\t\t bytes received: ");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> ReadnUChar8_UDP...\n ");
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\t\t bytes received: ");
	#endif
	do
	{
		n_read = recvfrom(socket_id[SocketIndex],(char *)UChar8ToWait, NbByteToWait, RCV_FLAG, (struct sockaddr*)src_info, &src_len);
		if (n_read != -1)
			nb_packet++;
	}
	while(n_read != -1);
	if (nb_packet == 0)
	{
		ReportUDPerror(SocketIndex);
	}
	else
	{
		#ifdef ECHO_PRINTF
			printf("\n");
			printf("<UDP> \t\t %d packet received from %s:%d\n", nb_packet, inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
			for (nb_formated = 0; nb_formated<NbUChar8ToWait; nb_formated++)
			{
				printf("<UDP> LastReceivedUChar8[%d] = %u\n", nb_formated, UChar8ToWait[nb_formated]);
			}
		#endif
		#ifdef ECHO_FPRINTF
			fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\n");
			fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> \t\t %d packet received from %s:%d\n", nb_packet, inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
			for (nb_formated = 0; nb_formated<NbUChar8ToWait; nb_formated++)
			{
				fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> LastReceivedUChar8[%d] = %u\n", nb_formated, UChar8ToWait[nb_formated]);
			}
		#endif
	}
    return(nb_packet);
}

int SendnUChar8_UDP(int SocketIndex, SOCKADDR_IN *dest_info, unsigned char *UChar8ToSend, int NbUChar8ToSend)
{
	int n_sent;
	#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
		int i;
	#endif
	
	 n_sent=sendto(socket_id[SocketIndex],(char *)UChar8ToSend,NbUChar8ToSend*NB_BYTE_UCHAR8,0,(struct sockaddr*)dest_info,(int)sizeof(*dest_info));

	#ifdef ECHO_PRINTF
		printf("<UDP> SendnUChar8_UDP...\n");
		printf("\t %d bytes sent\n\t", n_sent);
		for(i=0; i<NbUChar8ToSend; i++)
		{
			printf("%u ", UChar8ToSend[i]);
		}
		printf("\n");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "<UDP> SendnUChar8_UDP...\n");
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\t %d bytes sent\n\t", n_sent);
		for(i=0; i<NbUChar8ToSend; i++)
		{
			fprintf(FID_debug_SendReceiveUDP[SocketIndex], "%u ", UChar8ToSend[i]);
		}
		fprintf(FID_debug_SendReceiveUDP[SocketIndex], "\n");
	#endif
	
	return(n_sent);
}