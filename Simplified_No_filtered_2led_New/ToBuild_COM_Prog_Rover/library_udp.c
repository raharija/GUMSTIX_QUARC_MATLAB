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
 
#include "library_udp.h"
 
extern FILE *FID_debug;
 
int initUDPlocalSocket(struct sockaddr_in *local_info, int *sk, char *local_address, unsigned short local_port)
{
	int flags;
	printf("<UDP> \t local Socket initialization:\n");
	fprintf(FID_debug, "<UDP> \t local Socket initialization:\n");
	// creation of socket
	if( (*sk=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0 ) 
	{
		printf("<UDP> \t\t Socket -> failed!!!\n");
		fprintf(FID_debug, "<UDP> \t\t Socket -> failed!!!\n");
		return(-1);
	}
	else
	{
		printf("<UDP> \t\t socket: %d -> OK!\n", *sk);
		fprintf(FID_debug, "<UDP> \t\t socket: %d -> OK!\n", *sk);
	}
	// render socket reception non blocking
	flags = fcntl(*sk, F_GETFL, 0);
	fcntl(*sk, F_SETFL, flags | O_NONBLOCK); 
	
	// local configuration
	memset((char *) local_info, 0, sizeof(*local_info));
    local_info->sin_family = AF_INET;
    local_info->sin_port = htons(local_port);
	//local_info->sin_addr.s_addr = htonl(INADDR_ANY);	// to receive from any interface 
	local_info->sin_addr.s_addr = inet_addr(local_address); // to receive from a specific IP address (local IP)
		// bind socket
	if (bind(*sk,(struct sockaddr *)local_info,sizeof(*local_info))!=0)
    {
		perror("<UDP> \t\t Bind error! ");
		fprintf(FID_debug, "<UDP> \t\t Bind error! ");
        return(-1);
    }
	else
	{
		printf("<UDP> \t\t bind -> OK!\n");
		printf("<UDP> \t\t\t IP address: %s\n", local_address);
		printf("<UDP> \t\t\t local Port: %u\n", local_port);
		fprintf(FID_debug, "<UDP> \t\t bind -> OK!\n");
		fprintf(FID_debug, "<UDP> \t\t\t IP address: %s\n", local_address);
		fprintf(FID_debug, "<UDP> \t\t\t local Port: %u\n", local_port);
	}
	printf("<UDP> \t socket successfully initialized!!!\n\n");
	fprintf(FID_debug, "<UDP> \t socket connection successfully initialized!!!\n\n");
	return(0);
}

 
int initUDPremote(struct sockaddr_in *remote_info, const char *remote_address, unsigned short remote_port)
{
	int flags;
	printf("<UDP> \t initialisation of remote peer:\n");
	fprintf(FID_debug, "<UDP> \t initialisation of remote peer:\n");

	// remote configuration
	memset((char *) remote_info, 0, sizeof(*remote_info));
    remote_info->sin_family = AF_INET;
    remote_info->sin_port = htons(remote_port);
    if (inet_aton(remote_address, &remote_info->sin_addr)==0) 
	{
      printf("<UDP> \t\t inet_aton() -> failed!!!\n");
	  fprintf(FID_debug, "<UDP> \t\t inet_aton() -> failed!!!\n");
      return(-1);
    }
	else
	{
		printf("<UDP> \t\t Remote address: %s -> OK!\n ", remote_address);
		printf("<UDP> \t\t Remote port: %u -> OK!\n ", remote_port);
		fprintf(FID_debug, "<UDP> \t\t Remote address: %s -> OK!\n ", remote_address);
		fprintf(FID_debug, "<UDP> \t\t Remote port: %u -> OK!\n ", remote_port);
	}
	
	printf("<UDP> \t remote peer successfully initialized!!!\n\n");
	fprintf(FID_debug, "<UDP> \t remote peer successfully initialized!!!\n\n");
	return(0);
} 
 
char *getAddressOfInterface(const char *interface, char IPaddress[IP_LENGTH])
{
	FILE *FID;
	char get_str[255];
	short if_fund = 0;
	short addr_fund = 0;
	int error;
	char* temp;
	
	printf("<UDP> \t Recover '%s' informations:\n", interface);
	fprintf(FID_debug, "<UDP> \t Recover '%s' informations:\n", interface);
	
	error = system("rm ifconfig_result.txt >> cin");
	error = system("rm cin"); // just to not print error from previous command
	error = system("ifconfig >> ifconfig_result.txt"); 	// call ifconfig and save result in ifconfig_result.txt
	FID = fopen("ifconfig_result.txt", "r");
	fgets(get_str,255,FID); 
	while((get_str!=NULL) && (feof(FID)==0))	// while end of file isn't reached
	{
		temp = strstr(get_str,interface); 
		if ((temp != NULL) || (if_fund == 1)) // test if interface declaration is here
		{
			if_fund = 1; // interface declaration was fund
			temp = strstr(get_str,"inet addr:"); 
			if (temp != NULL) // test if it is the line where ip address is declared
			{
				strtok(temp,":"); // select only the ip address
				temp = strtok(NULL," ");
				addr_fund = 1;
				break;
			}
		}
		fgets(get_str,255,FID);
	}
	fclose(FID);
	if(if_fund == 1)
	{
		if (addr_fund == 1)
		{
			strcpy(IPaddress, temp);
			printf("<UDP> \t\t IP address of interface '%s': %s\n", interface, IPaddress);
			fprintf(FID_debug, "<UDP> \t\t IP address of interface '%s': %s\n", interface, IPaddress);
		}
		else
		{
			printf("\t\t No valid IP address found for interface %s\n", interface);
			printf("\t\t type 'ifconfig' to check your network configuration\n");
			fprintf(FID_debug, "\t\t No valid IP address found for interface %s\n", interface);
			fprintf(FID_debug, "\t\t type 'ifconfig' to check your network configuration\n");
			fflush(stdout);
			exit(-1);
		}
	}
	else
	{
		printf("\t\t ERROR: interface %s is not configured or turned off\n\t  ", interface);
		printf("\t\t type 'ifconfig' to check your network configuration\n");
		fprintf(FID_debug, "\t\t ERROR: interface %s is not configured or turned off\n\t  ", interface);
		fprintf(FID_debug, "\t\t type 'ifconfig' to check your network configuration\n");
		fflush(stdout);
		exit(-1);
	}
	return(temp);
}

int isValidIP(const char *ip)
{
	if(strlen(ip) > IP_LENGTH )
	{
        return(0);
	}
	else
	{
		return(1);
	}
}

char* socket2str(int socket, char* str)
{
	struct sockaddr_in address;
	socklen_t address_len = sizeof(struct sockaddr_in);
	getsockname(socket, (struct sockaddr*)&address, &address_len);
	sprintf(str, "%d->%s:%d", socket, inet_ntoa(address.sin_addr), ntohs(address.sin_port));
	//sockaddr2str(address, str);
	
	return(str);
}

char* sockaddr2str(struct sockaddr_in addr, char* str)
{
	sprintf(str, "%s:%d", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
	
	return(str);
}

/*********** DOUBLE **********/
void WaitnDouble_UDP(int socket_id, struct sockaddr_in *src_info, double *DoubleToWait, int NbDoubleToWait, unsigned int BlockingTimeOut_us)
{
	int n_read;
	int index = 0;
	int NbByteToWait = NbDoubleToWait*NB_BYTE_DOUBLE;
	socklen_t src_len = (socklen_t)sizeof(*src_info);
	struct timespec InitTime, CurrentTime;
	int dt;
	
	clock_gettime(CLOCK_MONOTONIC, &InitTime);	// recover current time in nanoseconds
	
	#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
		int nb_formated;
	#endif

	#ifdef ECHO_PRINTF
		printf("<UDP> WaitnDouble_UDP...\n ");
		printf("\t\t bytes received: ");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug, "<UDP> WaitnDouble_UDP...\n ");
		fprintf(FID_debug, "\t\t bytes received: ");
	#endif
	while(index<NbByteToWait)
	{
		n_read = recvfrom(socket_id,(char *)(DoubleToWait+index), (NbByteToWait-index), 0, (struct sockaddr *)src_info, (socklen_t *)&src_len);
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
						fprintf(FID_debug, "%d ", index);
					#endif
				}
			#endif
		}
		clock_gettime(CLOCK_MONOTONIC, &CurrentTime);	// recover current time in nanoseconds
		dt = (CurrentTime.tv_sec - InitTime.tv_sec) * 1000000
			+ (CurrentTime.tv_nsec - InitTime.tv_nsec)/1000;
		if (dt > BlockingTimeOut_us)
		{
			#ifdef ECHO_PRINTF
				printf("\n<UDP> Wait TIME OUT!\n");
			#endif
			#ifdef ECHO_FPRINTF
				fprintf(FID_debug, "\n<UDP> Wait TIME OUT!\n");
			#endif
			return -1; //break;
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
		fprintf(FID_debug, "\n");
		fprintf(FID_debug,"\t\t Received packet from %s:%d\n", inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
		for (nb_formated = 0; nb_formated<NbDoubleToWait; nb_formated++)
		{
			fprintf(FID_debug, "<UDP> ReceivedDouble[%d] = %.6f\n", nb_formated, DoubleToWait[nb_formated]);
		}
	#endif
}

void ReadnDouble_UDP(int socket_id, struct sockaddr_in *src_info, double *DoubleToWait, int NbDoubleToWait)
{
	int n_read;
	int NbByteToWait = NbDoubleToWait*NB_BYTE_DOUBLE;
	int src_len=sizeof(*src_info);
	#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
		int nb_formated;
	#endif

	#ifdef ECHO_PRINTF
		printf("<UDP> ReadnDouble_UDP...\n ");
		printf("\t\t bytes received: ");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug, "<UDP> ReadnDouble_UDP...\n ");
		fprintf(FID_debug, "\t\t bytes received: ");
	#endif
	n_read = recvfrom(socket_id,(char *)DoubleToWait, NbByteToWait, 0, (struct sockaddr*)src_info, (socklen_t *)&src_len);
	if (n_read == -1)
	{
		#ifdef ECHO_PRINTF
			printf("\n");
			printf("<UDP> \t\t ERROR! Any NewData Received! (previous data are conserved...)\n");
		#endif
		#ifdef ECHO_FPRINTF
			fprintf(FID_debug, "\n");
			fprintf(FID_debug, "<UDP> \t\t ERROR! Any NewData Received! (previous data are conserved...)\n");
		#endif	
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
			fprintf(FID_debug, "\n");
			fprintf(FID_debug, "<UDP> \t\t Received packet from %s:%d\n", inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
			for (nb_formated = 0; nb_formated<NbDoubleToWait; nb_formated++)
			{
				fprintf(FID_debug, "<UDP> ReceivedDouble[%d] = %.6f\n", nb_formated, DoubleToWait[nb_formated]);
			}
		#endif
	}
}

void ReadLastnDouble_UDP(int socket_id, struct sockaddr_in *src_info, double *DoubleToWait, int NbDoubleToWait)
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
		fprintf(FID_debug, "<UDP> ReadnDouble_UDP...\n ");
		fprintf(FID_debug, "\t\t bytes received: ");
	#endif
	do
	{
		n_read = recvfrom(socket_id,(char *)DoubleToWait, NbByteToWait, 0, (struct sockaddr*)src_info, (socklen_t *)&src_len);
		if (n_read != -1)
			nb_packet++;
	}
	while(n_read != -1);
	if (nb_packet == 0)
	{
		#ifdef ECHO_PRINTF
			printf("\n");
			printf("<UDP> \t\t ERROR! Any NewData Received! (previous data are conserved...)\n");
		#endif
		#ifdef ECHO_FPRINTF
			fprintf(FID_debug, "\n");
			fprintf(FID_debug, "<UDP> \t\t ERROR! Any NewData Received! (previous data are conserved...)\n");
		#endif	
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
			fprintf(FID_debug, "\n");
			fprintf(FID_debug, "<UDP> \t\t %d packet received from %s:%d\n", nb_packet, inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
			for (nb_formated = 0; nb_formated<NbDoubleToWait; nb_formated++)
			{
				fprintf(FID_debug, "<UDP> LastReceivedDouble[%d] = %.6f\n", nb_formated, DoubleToWait[nb_formated]);
			}
		#endif
	}
}

int SendnDouble_UDP(int socket_id, struct sockaddr_in *dest_info, double *DoubleToSend, int NbDoubleToSend)
{
	int n_sent;
	#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
		int i;
	#endif
	#ifdef ECHO_PRINTF
		printf("<UDP> SendnDouble_UDP...\n");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug, "<UDP> SendnDouble_UDP...\n");
	#endif
	
	n_sent = sendto(socket_id, (char *)DoubleToSend, NbDoubleToSend*NB_BYTE_DOUBLE,0, (struct sockaddr *)dest_info, sizeof(*dest_info));
	
	#ifdef ECHO_PRINTF
		printf("\t %d bytes sent to %s:%u\n\t", n_sent, inet_ntoa(dest_info->sin_addr), ntohs(dest_info->sin_port));
		for(i=0; i<NbDoubleToSend; i++)
		{
			printf("%.13f ", DoubleToSend[i]);
		}
		printf("\n");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug, "<UDP> SendnDouble_UDP...\n");
		fprintf(FID_debug, "\t %d bytes sent\n\t", n_sent);
		for(i=0; i<NbDoubleToSend; i++)
		{
			fprintf(FID_debug, "%.13f ", DoubleToSend[i]);
		}
		fprintf(FID_debug, "\n");
	#endif
	
	return(n_sent);
}

/************ FLOAT32 ***********/
void WaitnFloat_UDP(int socket_id, struct sockaddr_in *src_info, float *Float32ToWait, int NbFloat32ToWait, unsigned int BlockingTimeOut_us)
{
	int n_read;
	int index = 0;
	int NbByteToWait = NbFloat32ToWait*NB_BYTE_FLOAT;
	socklen_t src_len = (socklen_t)sizeof(*src_info);
	struct timespec InitTime, CurrentTime;
	int dt;
	
	clock_gettime(CLOCK_MONOTONIC, &InitTime);	// recover current time in nanoseconds
	
	#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
		int nb_formated;
	#endif

	#ifdef ECHO_PRINTF
		printf("<UDP> WaitnFloat32_UDP...\n ");
		printf("\t\t bytes received: ");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug, "<UDP> WaitnFloat32_UDP...\n ");
		fprintf(FID_debug, "\t\t bytes received: ");
	#endif
	while(index<NbByteToWait)
	{
		n_read = recvfrom(socket_id,(char *)(Float32ToWait+index),(NbByteToWait-index), 0, (struct sockaddr *)src_info, (socklen_t *)&src_len);
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
						fprintf(FID_debug, "%d ", index);
					#endif
				}
			#endif
		}
		clock_gettime(CLOCK_MONOTONIC, &CurrentTime);	// recover current time in nanoseconds
		dt = (CurrentTime.tv_sec - InitTime.tv_sec) * 1000000
			+ (CurrentTime.tv_nsec - InitTime.tv_nsec)/1000;
		if (dt > BlockingTimeOut_us)
		{
			#ifdef ECHO_PRINTF
				printf("\n<UDP> Wait TIME OUT!\n");
			#endif
			#ifdef ECHO_FPRINTF
				fprintf(FID_debug, "\n<UDP> Wait TIME OUT!\n");
			#endif
			return -1; //break;
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
		fprintf(FID_debug, "\n");
		fprintf(FID_debug,"\t\t Received packet from %s:%d\n", inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
		for (nb_formated = 0; nb_formated<NbFloat32ToWait; nb_formated++)
		{
			fprintf(FID_debug, "<UDP> ReceivedFloat32[%d] = %.6f\n", nb_formated, Float32ToWait[nb_formated]);
		}
	#endif
}

void ReadnFloat_UDP(int socket_id, struct sockaddr_in *src_info, float *FloatToWait, int NbFloatToWait)
{
	int n_read;
	int NbByteToWait = NbFloatToWait*NB_BYTE_FLOAT;
	int src_len=sizeof(*src_info);
	#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
		int nb_formated;
	#endif

	#ifdef ECHO_PRINTF
		printf("<UDP> ReadnFloat_UDP...\n ");
		printf("\t\t bytes received: ");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug, "<UDP> ReadnFloat_UDP...\n ");
		fprintf(FID_debug, "\t\t bytes received: ");
	#endif
	n_read = recvfrom(socket_id,(char *)FloatToWait, NbByteToWait, 0, (struct sockaddr*)src_info, (socklen_t *)&src_len);
	if (n_read == -1)
	{
		#ifdef ECHO_PRINTF
			printf("\n");
			printf("<UDP> \t\t ERROR! Any NewData Received! (previous data are conserved...)\n");
		#endif
		#ifdef ECHO_FPRINTF
			fprintf(FID_debug, "\n");
			fprintf(FID_debug, "<UDP> \t\t ERROR! Any NewData Received! (previous data are conserved...)\n");
		#endif
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
			fprintf(FID_debug, "\n");
			fprintf(FID_debug, "<UDP> \t\t Received packet from %s:%d\n", inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
			for (nb_formated = 0; nb_formated<NbFloatToWait; nb_formated++)
			{
				fprintf(FID_debug, "<UDP> ReceivedFloat[%d] = %.6f\n", nb_formated, FloatToWait[nb_formated]);
			}
		#endif
	}
}

// void ReadLastnFloat_UDP(int socket_id, struct sockaddr_in *src_info, float *FloatToWait, int NbFloatToWait)
// {
	// int n_read;
	// int NbByteToWait = NbFloatToWait*NB_BYTE_FLOAT;
	// int src_len=sizeof(*src_info);
	// int nb_packet = 0;
	// #if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
		// int nb_formated;
	// #endif

	// #ifdef ECHO_PRINTF
		// printf("<UDP> ReadnFloat_UDP...\n ");
		// printf("\t\t bytes received: ");
	// #endif
	// #ifdef ECHO_FPRINTF
		// fprintf(FID_debug, "<UDP> ReadnFloat_UDP...\n ");
		// fprintf(FID_debug, "\t\t bytes received: ");
	// #endif
	// do
	// {
		// n_read = recvfrom(socket_id,(char *)FloatToWait, NbByteToWait, 0, (struct sockaddr*)src_info, (socklen_t *)&src_len);
		// if (n_read != -1)
			// nb_packet++;
	// }
	// while(n_read != -1);
	// if (nb_packet == 0)
	// {
		// #ifdef ECHO_PRINTF
			// printf("\n");
			// printf("<UDP> \t\t ERROR! Any NewData Received! (previous data are conserved...)\n");
		// #endif
		// #ifdef ECHO_FPRINTF
			// fprintf(FID_debug, "\n");
			// fprintf(FID_debug, "<UDP> \t\t ERROR! Any NewData Received! (previous data are conserved...)\n");
		// #endif	
	// }
	// else
	// {
		// #ifdef ECHO_PRINTF
			// printf("\n");
			// printf("<UDP> \t\t %d packet received from %s:%d\n", nb_packet, inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
			// for (nb_formated = 0; nb_formated<NbFloatToWait; nb_formated++)
			// {
				// printf("<UDP> LastReceivedFloat[%d] = %.6f\n", nb_formated, FloatToWait[nb_formated]);
			// }
		// #endif
		// #ifdef ECHO_FPRINTF
			// fprintf(FID_debug, "\n");
			// fprintf(FID_debug, "<UDP> \t\t %d packet received from %s:%d\n", nb_packet, inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
			// for (nb_formated = 0; nb_formated<NbFloatToWait; nb_formated++)
			// {
				// fprintf(FID_debug, "<UDP> LastReceivedFloat[%d] = %.6f\n", nb_formated, FloatToWait[nb_formated]);
			// }
		// #endif
	// }
// }

void ReadLastnFloat_UDP(int socket_id, struct sockaddr_in *src_info, float *FloatToWait, int NbFloatToWait)
{
	int n_read;
	int NbByteToWait = NbFloatToWait*NB_BYTE_FLOAT;
	int src_len=sizeof(*src_info);
	int nb_packet = 0;
	#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
		int nb_formated;
		char str[30];
	#endif

	#ifdef ECHO_PRINTF
		printf("<UDP> ReadLastnFloat_UDP on socket '%s'...\n", socket2str(socket_id, str));		
		printf("\t\t bytes received: ");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug, "<UDP> ReadLastnFloat_UDP on socket '%s'...\n", socket2str(socket_id, str));	
		fprintf(FID_debug, "\t\t bytes received: ");
	#endif
	do
	{
		n_read = recvfrom(socket_id,(char *)FloatToWait, NbByteToWait, 0, (struct sockaddr*)src_info, (socklen_t *)&src_len);
		if (n_read > 0)
			nb_packet++;
	}
	while(n_read > 0);
	if (nb_packet == 0)
	{
		#ifdef ECHO_PRINTF
			printf("\n");
			printf("<UDP> \t\t ERROR! Any NewData Received! (previous data are conserved...)\n");
		#endif
		#ifdef ECHO_FPRINTF
			fprintf(FID_debug, "\n");
			fprintf(FID_debug, "<UDP> \t\t ERROR! Any NewData Received! (previous data are conserved...)\n");
		#endif	
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
			fprintf(FID_debug, "\n");
			fprintf(FID_debug, "<UDP> \t\t %d packet received from %s:%d\n", nb_packet, inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
			for (nb_formated = 0; nb_formated<NbFloatToWait; nb_formated++)
			{
				fprintf(FID_debug, "<UDP> LastReceivedFloat[%d] = %.6f\n", nb_formated, FloatToWait[nb_formated]);
			}
		#endif
	}
}

int SendnFloat_UDP(int socket_id, struct sockaddr_in *dest_info, float *Float32ToSend, int NbFloat32ToSend)
{
	int n_sent;
	#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
		int i;
		char str1[30];  
		char str2[30];  
	#endif
	#ifdef ECHO_PRINTF
		printf("<UDP> SendnFloat32_UDP from socket '%s' to '%s'...\n", socket2str(socket_id, str1), sockaddr2str(*dest_info, str2));
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug, "<UDP> SendnFloat32_UDP from socket '%s' to '%s'...\n", socket2str(socket_id, str1), sockaddr2str(*dest_info, str2));
	#endif
	n_sent=sendto(socket_id,(char *)Float32ToSend,NbFloat32ToSend*NB_BYTE_FLOAT, MSG_DONTWAIT, (struct sockaddr *)dest_info, (int)sizeof(*dest_info));
	if (n_sent==-1)
	{
		char* errorStr = strerror(errno);
		printf("<UDP> sendto error: %s\n", errorStr);
		fprintf(FID_debug, "<UDP> sendto error: %s\n", errorStr);
	}
	else
	{
		#ifdef ECHO_PRINTF
			printf("\t %d bytes sent\n\t", n_sent);
			for(i=0; i<NbFloat32ToSend; i++)
			{
				printf("%.13f ", Float32ToSend[i]);
			}
			printf("\n");
		#endif
		#ifdef ECHO_FPRINTF  
			fprintf(FID_debug, "\t %d bytes sent\n\t", n_sent);
			for(i=0; i<NbFloat32ToSend; i++)
			{
				fprintf(FID_debug, "%.13f ", Float32ToSend[i]);
			}
			fprintf(FID_debug, "\n");
		#endif
	}
	
	return(n_sent);
}

/************ INT32 ***********/
void WaitnInt32_UDP(int socket_id, struct sockaddr_in *src_info, int *Int32ToWait, int NbInt32ToWait, unsigned int BlockingTimeOut_us)
{
	int n_read;
	int index = 0;
	int NbByteToWait = NbInt32ToWait*NB_BYTE_INT32;
	socklen_t src_len = (socklen_t)sizeof(*src_info);
	struct timespec InitTime, CurrentTime;
	int dt;
	
	clock_gettime(CLOCK_MONOTONIC, &InitTime);	// recover current time in nanoseconds
	
	#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
		int nb_formated;
	#endif

	#ifdef ECHO_PRINTF
		printf("<UDP> WaitnInt32_UDP...\n ");
		printf("\t\t bytes received: ");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug, "<UDP> WaitnInt32_UDP...\n ");
		fprintf(FID_debug, "\t\t bytes received: ");
	#endif
	while(index<NbByteToWait)
	{
		n_read = recvfrom(socket_id,(char *)(Int32ToWait+index),(NbByteToWait-index),0, (struct sockaddr *)src_info,&src_len);
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
						fprintf(FID_debug, "%d ", index);
					#endif
				}
			#endif
		}
		clock_gettime(CLOCK_MONOTONIC, &CurrentTime);	// recover current time in nanoseconds
		dt = (CurrentTime.tv_sec - InitTime.tv_sec) * 1000000
			+ (CurrentTime.tv_nsec - InitTime.tv_nsec)/1000;
		if (dt > BlockingTimeOut_us)
		{
			#ifdef ECHO_PRINTF
				printf("\n<UDP> Wait TIME OUT!\n");
			#endif
			#ifdef ECHO_FPRINTF
				fprintf(FID_debug, "\n<UDP> Wait TIME OUT!\n");
			#endif
			return -1; //break;
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
		fprintf(FID_debug, "\n");
		fprintf(FID_debug,"\t\t Received packet from %s:%d\n", inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
		for (nb_formated = 0; nb_formated<NbInt32ToWait; nb_formated++)
		{
			fprintf(FID_debug, "<UDP> ReceivedInt32[%d] = %d\n", nb_formated, Int32ToWait[nb_formated]);
		}
	#endif
}

void ReadnInt32_UDP(int socket_id, struct sockaddr_in *src_info, int *Int32ToWait, int NbInt32ToWait)
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
		fprintf(FID_debug, "<UDP> ReadnInt32_UDP...\n ");
		fprintf(FID_debug, "\t\t bytes received: ");
	#endif
	n_read = recvfrom(socket_id,(char *)Int32ToWait, NbByteToWait, 0, (struct sockaddr*)src_info, (socklen_t *)&src_len);
	if (n_read == -1)
	{
		#ifdef ECHO_PRINTF
			printf("\n");
			printf("<UDP> \t\t ERROR! Any NewData Received! (previous data are conserved...)\n");
		#endif
		#ifdef ECHO_FPRINTF
			fprintf(FID_debug, "\n");
			fprintf(FID_debug, "<UDP> \t\t ERROR! Any NewData Received! (previous data are conserved...)\n");
		#endif
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
			fprintf(FID_debug, "\n");
			fprintf(FID_debug, "<UDP> \t\t Received packet from %s:%d\n", inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
			for (nb_formated = 0; nb_formated<NbInt32ToWait; nb_formated++)
			{
				fprintf(FID_debug, "<UDP> ReceivedInt32[%d] = %d\n", nb_formated, Int32ToWait[nb_formated]);
			}
		#endif
	}
}

void ReadLastnInt32_UDP(int socket_id, struct sockaddr_in *src_info, int *Int32ToWait, int NbInt32ToWait)
{
	int n_read;
	int NbByteToWait = NbInt32ToWait*NB_BYTE_INT32;
	int src_len=sizeof(*src_info);
	int nb_packet = 0;
	#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
		int nb_formated;
	#endif

	#ifdef ECHO_PRINTF
		char str1[30];
		printf("<UDP> ReadnInt32_UDP from socket '%s'...\n", socket2str(socket_id, str1));
		printf("\t\t bytes received: ");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug, "<UDP> ReadnInt32_UDP...\n ");
		fprintf(FID_debug, "\t\t bytes received: ");
	#endif
	do
	{
		n_read = recvfrom(socket_id,(char *)Int32ToWait, NbByteToWait, 0, (struct sockaddr*)src_info, (socklen_t *)&src_len);
		if (n_read != -1)
			nb_packet++;
	}
	while(n_read != -1);
	if (nb_packet == 0)
	{
		#ifdef ECHO_PRINTF
			printf("\n");
			printf("<UDP> \t\t ERROR! Any NewData Received! (previous data are conserved...)\n");
		#endif
		#ifdef ECHO_FPRINTF
			fprintf(FID_debug, "\n");
			fprintf(FID_debug, "<UDP> \t\t ERROR! Any NewData Received! (previous data are conserved...)\n");
		#endif	
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
			fprintf(FID_debug, "\n");
			fprintf(FID_debug, "<UDP> \t\t %d packet received from %s:%d\n", nb_packet, inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
			for (nb_formated = 0; nb_formated<NbInt32ToWait; nb_formated++)
			{
				fprintf(FID_debug, "<UDP> LastReceivedInt32[%d] = %d\n", nb_formated, Int32ToWait[nb_formated]);
			}
		#endif
	}
}

int SendnInt32_UDP(int socket_id, struct sockaddr_in *dest_info, int *Int32ToSend, int NbInt32ToSend)
{
	int n_sent;
	#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
		int i;
	#endif
	
	 n_sent=sendto(socket_id,(char *)Int32ToSend,NbInt32ToSend*NB_BYTE_INT32,0,(struct sockaddr *)dest_info,sizeof(*dest_info));

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
		fprintf(FID_debug, "<UDP> SendnInt32_UDP...\n");
		fprintf(FID_debug, "\t %d bytes sent\n\t", n_sent);
		for(i=0; i<NbInt32ToSend; i++)
		{
			fprintf(FID_debug, "%d ", Int32ToSend[i]);
		}
		fprintf(FID_debug, "\n");
	#endif
	
	return(n_sent);
}

/************ UINT32 ***********/
void WaitnUInt32_UDP(int socket_id, struct sockaddr_in  *src_info, unsigned int *UInt32ToWait, int NbUInt32ToWait, unsigned int BlockingTimeOut_us)
{
	int n_read;
	int index = 0;
	int NbByteToWait = NbUInt32ToWait*NB_BYTE_UINT32;
	socklen_t src_len = (socklen_t)sizeof(*src_info);
	struct timespec InitTime, CurrentTime;
	int dt;
	
	clock_gettime(CLOCK_MONOTONIC, &InitTime);	// recover current time in nanoseconds
	
	#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
		int nb_formated;
	#endif

	#ifdef ECHO_PRINTF
		printf("<UDP> WaitnUInt32_UDP...\n ");
		printf("\t\t bytes received: ");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug, "<UDP> WaitnUInt32_UDP...\n ");
		fprintf(FID_debug, "\t\t bytes received: ");
	#endif
	while(index<NbByteToWait)
	{
		n_read = recvfrom(socket_id,(char *)(UInt32ToWait+index),(NbByteToWait-index),0,(struct sockaddr *)src_info,&src_len);
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
						fprintf(FID_debug, "%d ", index);
					#endif
				}
			#endif
		}
		clock_gettime(CLOCK_MONOTONIC, &CurrentTime);	// recover current time in nanoseconds
		dt = (CurrentTime.tv_sec - InitTime.tv_sec) * 1000000
			+ (CurrentTime.tv_nsec - InitTime.tv_nsec)/1000;
		if (dt > BlockingTimeOut_us)
		{
			#ifdef ECHO_PRINTF
				printf("\n<UDP> Wait TIME OUT!\n");
			#endif
			#ifdef ECHO_FPRINTF
				fprintf(FID_debug, "\n<UDP> Wait TIME OUT!\n");
			#endif
			return -1; //break;
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
		fprintf(FID_debug, "\n");
		fprintf(FID_debug,"\t\t Received packet from %s:%d\n", inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
		for (nb_formated = 0; nb_formated<NbUInt32ToWait; nb_formated++)
		{
			fprintf(FID_debug, "<UDP> ReceivedUInt32[%d] = %u\n", nb_formated, UInt32ToWait[nb_formated]);
		}
	#endif
}

void ReadnUInt32_UDP(int socket_id, struct sockaddr_in *src_info, unsigned int *UInt32ToWait, int NbUInt32ToWait)
{
	int n_read;
	int NbByteToWait = NbUInt32ToWait*NB_BYTE_UINT32;
	int src_len=sizeof(*src_info);
	#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
		int nb_formated;
	#endif

	#ifdef ECHO_PRINTF
		printf("<UDP>ReadnUInt32_UDP...\n ");
		printf("\t\t bytes received: ");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug, "<UDP> ReadnUInt32_UDP...\n ");
		fprintf(FID_debug, "\t\t bytes received: ");
	#endif
	n_read = recvfrom(socket_id,(char *)UInt32ToWait, NbByteToWait, 0, (struct sockaddr*)src_info, (socklen_t *)&src_len);
	if (n_read == -1)
	{
		#ifdef ECHO_PRINTF
			printf("\n");
			printf("<UDP> \t\t ERROR! Any NewData Received! (previous data are conserved...)\n");
		#endif
		#ifdef ECHO_FPRINTF
			fprintf(FID_debug, "\n");
			fprintf(FID_debug, "<UDP> \t\t ERROR! Any NewData Received! (previous data are conserved...)\n");
		#endif
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
			fprintf(FID_debug, "\n");
			fprintf(FID_debug, "<UDP> \t\t Received packet from %s:%d\n", inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
			for (nb_formated = 0; nb_formated<NbUInt32ToWait; nb_formated++)
			{
				fprintf(FID_debug, "<UDP> ReceivedUInt32[%d] = %u\n", nb_formated, UInt32ToWait[nb_formated]);
			}
		#endif
	}
}

void ReadLastnUInt32_UDP(int socket_id, struct sockaddr_in *src_info, unsigned int *UInt32ToWait, int NbUInt32ToWait)
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
		fprintf(FID_debug, "<UDP> ReadnUInt32_UDP...\n ");
		fprintf(FID_debug, "\t\t bytes received: ");
	#endif
	do
	{
		n_read = recvfrom(socket_id,(char *)UInt32ToWait, NbByteToWait, 0, (struct sockaddr*)src_info, (socklen_t *)&src_len);
		if (n_read != -1)
			nb_packet++;
	}
	while(n_read != -1);
	if (nb_packet == 0)
	{
		#ifdef ECHO_PRINTF
			printf("\n");
			printf("<UDP> \t\t ERROR! Any NewData Received! (previous data are conserved...)\n");
		#endif
		#ifdef ECHO_FPRINTF
			fprintf(FID_debug, "\n");
			fprintf(FID_debug, "<UDP> \t\t ERROR! Any NewData Received! (previous data are conserved...)\n");
		#endif	
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
			fprintf(FID_debug, "\n");
			fprintf(FID_debug, "<UDP> \t\t %d packet received from %s:%d\n", nb_packet, inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
			for (nb_formated = 0; nb_formated<NbUInt32ToWait; nb_formated++)
			{
				fprintf(FID_debug, "<UDP> LastReceivedUInt32[%d] = %u\n", nb_formated, UInt32ToWait[nb_formated]);
			}
		#endif
	}
}

int SendnUInt32_UDP(int socket_id, struct sockaddr_in *dest_info, unsigned int *UInt32ToSend, int NbUInt32ToSend)
{
	int n_sent;
	#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
		int i;
	#endif
	
	 n_sent=sendto(socket_id,(char *)UInt32ToSend,NbUInt32ToSend*NB_BYTE_UINT32,0, (struct sockaddr *)dest_info,sizeof(*dest_info));

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
		fprintf(FID_debug, "<UDP> SendnUInt32_UDP...\n");
		fprintf(FID_debug, "\t %d bytes sent\n\t", n_sent);
		for(i=0; i<NbUInt32ToSend; i++)
		{
			fprintf(FID_debug, "%u ", UInt32ToSend[i]);
		}
		fprintf(FID_debug, "\n");
	#endif
	
	return(n_sent);
}

/************ INT16 ***********/
void WaitnInt16_UDP(int socket_id, struct sockaddr_in  *src_info, short *Int16ToWait, int NbInt16ToWait, unsigned int BlockingTimeOut_us)
{
	int n_read;
	int index = 0;
	int NbByteToWait = NbInt16ToWait*NB_BYTE_INT16;
	socklen_t src_len = (socklen_t)sizeof(*src_info);
	struct timespec InitTime, CurrentTime;
	int dt;
	
	clock_gettime(CLOCK_MONOTONIC, &InitTime);	// recover current time in nanoseconds
	
	#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
		int nb_formated;
	#endif

	#ifdef ECHO_PRINTF
		printf("<UDP> WaitnInt16_UDP...\n ");
		printf("\t\t bytes received: ");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug, "<UDP> WaitnInt16_UDP...\n ");
		fprintf(FID_debug, "\t\t bytes received: ");
	#endif
	while(index<NbByteToWait)
	{
		n_read = recvfrom(socket_id,(char *)(Int16ToWait+index),(NbByteToWait-index),0,(struct sockaddr *)src_info,&src_len);
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
						fprintf(FID_debug, "%d ", index);
					#endif
				}
			#endif
		}
		clock_gettime(CLOCK_MONOTONIC, &CurrentTime);	// recover current time in nanoseconds
		dt = (CurrentTime.tv_sec - InitTime.tv_sec) * 1000000
			+ (CurrentTime.tv_nsec - InitTime.tv_nsec)/1000;
		if (dt > BlockingTimeOut_us)
		{
			#ifdef ECHO_PRINTF
				printf("\n<UDP> Wait TIME OUT!\n");
			#endif
			#ifdef ECHO_FPRINTF
				fprintf(FID_debug, "\n<UDP> Wait TIME OUT!\n");
			#endif
			return -1; //break;
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
		fprintf(FID_debug, "\n");
		fprintf(FID_debug,"\t\t Received packet from %s:%d\n", inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
		for (nb_formated = 0; nb_formated<NbInt16ToWait; nb_formated++)
		{
			fprintf(FID_debug, "<UDP> ReceivedInt16[%d] = %d\n", nb_formated, Int16ToWait[nb_formated]);
		}
	#endif
}

void ReadnInt16_UDP(int socket_id, struct sockaddr_in *src_info, short *Int16ToWait, int NbInt16ToWait)
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
		fprintf(FID_debug, "<UDP> ReadnInt16_UDP...\n ");
		fprintf(FID_debug, "\t\t bytes received: ");
	#endif
	n_read = recvfrom(socket_id,(char *)Int16ToWait, NbByteToWait, 0, (struct sockaddr*)src_info, (socklen_t *)&src_len);
	if (n_read == -1)
	{
		#ifdef ECHO_PRINTF
			printf("\n");
			printf("<UDP> \t\t ERROR! Any NewData Received! (previous data are conserved...)\n");
		#endif
		#ifdef ECHO_FPRINTF
			fprintf(FID_debug, "\n");
			fprintf(FID_debug, "<UDP> \t\t ERROR! Any NewData Received! (previous data are conserved...)\n");
		#endif
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
			fprintf(FID_debug, "\n");
			fprintf(FID_debug, "<UDP> \t\t Received packet from %s:%d\n", inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
			for (nb_formated = 0; nb_formated<NbInt16ToWait; nb_formated++)
			{
				fprintf(FID_debug, "<UDP> ReceivedInt16[%d] = %d\n", nb_formated, Int16ToWait[nb_formated]);
			}
		#endif
	}
}

void ReadLastnInt16_UDP(int socket_id, struct sockaddr_in *src_info, short *Int16ToWait, int NbInt16ToWait)
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
		fprintf(FID_debug, "<UDP> ReadnInt16_UDP...\n ");
		fprintf(FID_debug, "\t\t bytes received: ");
	#endif
	do
	{
		n_read = recvfrom(socket_id,(char *)Int16ToWait, NbByteToWait, 0, (struct sockaddr*)src_info, (socklen_t *)&src_len);
		if (n_read != -1)
			nb_packet++;
	}
	while(n_read != -1);
	if (nb_packet == 0)
	{
		#ifdef ECHO_PRINTF
			printf("\n");
			printf("<UDP> \t\t ERROR! Any NewData Received! (previous data are conserved...)\n");
		#endif
		#ifdef ECHO_FPRINTF
			fprintf(FID_debug, "\n");
			fprintf(FID_debug, "<UDP> \t\t ERROR! Any NewData Received! (previous data are conserved...)\n");
		#endif	
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
			fprintf(FID_debug, "\n");
			fprintf(FID_debug, "<UDP> \t\t %d packet received from %s:%d\n", nb_packet, inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
			for (nb_formated = 0; nb_formated<NbInt16ToWait; nb_formated++)
			{
				fprintf(FID_debug, "<UDP> LastReceivedInt16[%d] = %d\n", nb_formated, Int16ToWait[nb_formated]);
			}
		#endif
	}
}

int SendnInt16_UDP(int socket_id, struct sockaddr_in *dest_info, short *Int16ToSend, int NbInt16ToSend)
{
	int n_sent;
	#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
		int i;
	#endif
	
	 n_sent=sendto(socket_id,(char *)Int16ToSend,NbInt16ToSend*NB_BYTE_INT16,0,(struct sockaddr *)dest_info,sizeof(*dest_info));

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
		fprintf(FID_debug, "<UDP> SendnInt16_UDP...\n");
		fprintf(FID_debug, "\t %d bytes sent\n\t", n_sent);
		for(i=0; i<NbInt16ToSend; i++)
		{
			fprintf(FID_debug, "%d ", Int16ToSend[i]);
		}
		fprintf(FID_debug, "\n");
	#endif
	
	return(n_sent);
}

/************ UINT16 ***********/
void WaitnUInt16_UDP(int socket_id, struct sockaddr_in  *src_info, unsigned short *UInt16ToWait, int NbUInt16ToWait, unsigned int BlockingTimeOut_us)
{
	int n_read;
	int index = 0;
	int NbByteToWait = NbUInt16ToWait*NB_BYTE_UINT16;
	socklen_t src_len = (socklen_t)sizeof(*src_info);
	struct timespec InitTime, CurrentTime;
	int dt;
	
	clock_gettime(CLOCK_MONOTONIC, &InitTime);	// recover current time in nanoseconds
	
	#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
		int nb_formated;
	#endif

	#ifdef ECHO_PRINTF
		printf("<UDP> WaitnUInt16_UDP...\n ");
		printf("\t\t bytes received: ");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug, "<UDP> WaitnUInt16_UDP...\n ");
		fprintf(FID_debug, "\t\t bytes received: ");
	#endif
	while(index<NbByteToWait)
	{
		n_read = recvfrom(socket_id,(char *)(UInt16ToWait+index),(NbByteToWait-index),0,(struct sockaddr *)src_info,&src_len);
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
						fprintf(FID_debug, "%d ", index);
					#endif
				}
			#endif
		}
		clock_gettime(CLOCK_MONOTONIC, &CurrentTime);	// recover current time in nanoseconds
		dt = (CurrentTime.tv_sec - InitTime.tv_sec) * 1000000
			+ (CurrentTime.tv_nsec - InitTime.tv_nsec)/1000;
		if (dt > BlockingTimeOut_us)
		{
			#ifdef ECHO_PRINTF
				printf("\n<UDP> Wait TIME OUT!\n");
			#endif
			#ifdef ECHO_FPRINTF
				fprintf(FID_debug, "\n<UDP> Wait TIME OUT!\n");
			#endif
			return -1; //break;
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
		fprintf(FID_debug, "\n");
		fprintf(FID_debug,"\t\t Received packet from %s:%d\n", inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
		for (nb_formated = 0; nb_formated<NbUInt16ToWait; nb_formated++)
		{
			fprintf(FID_debug, "<UDP> ReceivedUInt16[%d] = %u\n", nb_formated, UInt16ToWait[nb_formated]);
		}
	#endif
}

void ReadnUInt16_UDP(int socket_id, struct sockaddr_in *src_info, unsigned short *UInt16ToWait, int NbUInt16ToWait)
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
		fprintf(FID_debug, "<UDP> ReadnUInt16_UDP...\n ");
		fprintf(FID_debug, "\t\t bytes received: ");
	#endif
	n_read = recvfrom(socket_id,(char *)UInt16ToWait, NbByteToWait, 0, (struct sockaddr*)src_info, (socklen_t *)&src_len);
	if (n_read == -1)
	{
		#ifdef ECHO_PRINTF
			printf("\n");
			printf("<UDP> \t\t ERROR! Any NewData Received! (previous data are conserved...)\n");
		#endif
		#ifdef ECHO_FPRINTF
			fprintf(FID_debug, "\n");
			fprintf(FID_debug, "<UDP> \t\t ERROR! Any NewData Received! (previous data are conserved...)\n");
		#endif
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
			fprintf(FID_debug, "\n");
			fprintf(FID_debug, "<UDP> \t\t Received packet from %s:%d\n", inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
			for (nb_formated = 0; nb_formated<NbUInt16ToWait; nb_formated++)
			{
				fprintf(FID_debug, "<UDP> ReceivedUInt16[%d] = %u\n", nb_formated, UInt16ToWait[nb_formated]);
			}
		#endif
	}
}

void ReadLastnUInt16_UDP(int socket_id, struct sockaddr_in *src_info, unsigned short *UInt16ToWait, int NbUInt16ToWait)
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
		fprintf(FID_debug, "<UDP> ReadnUInt16_UDP...\n ");
		fprintf(FID_debug, "\t\t bytes received: ");
	#endif
	do
	{
		n_read = recvfrom(socket_id,(char *)UInt16ToWait, NbByteToWait, 0, (struct sockaddr*)src_info, (socklen_t *)&src_len);
		if (n_read != -1)
			nb_packet++;
	}
	while(n_read != -1);
	if (nb_packet == 0)
	{
		#ifdef ECHO_PRINTF
			printf("\n");
			printf("<UDP> \t\t ERROR! Any NewData Received! (previous data are conserved...)\n");
		#endif
		#ifdef ECHO_FPRINTF
			fprintf(FID_debug, "\n");
			fprintf(FID_debug, "<UDP> \t\t ERROR! Any NewData Received! (previous data are conserved...)\n");
		#endif	
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
			fprintf(FID_debug, "\n");
			fprintf(FID_debug, "<UDP> \t\t %d packet received from %s:%d\n", nb_packet, inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
			for (nb_formated = 0; nb_formated<NbUInt16ToWait; nb_formated++)
			{
				fprintf(FID_debug, "<UDP> LastReceivedUInt16[%d] = %u\n", nb_formated, UInt16ToWait[nb_formated]);
			}
		#endif
	}
}

int SendnUInt16_UDP(int socket_id, struct sockaddr_in *dest_info, unsigned short *UInt16ToSend, int NbUInt16ToSend)
{
	int n_sent;
	#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
		int i;
	#endif
	
	 n_sent=sendto(socket_id,(char *)UInt16ToSend,NbUInt16ToSend*NB_BYTE_UINT16,0,(struct sockaddr *)dest_info,sizeof(*dest_info));

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
		fprintf(FID_debug, "<UDP> SendnUInt16_UDP...\n");
		fprintf(FID_debug, "\t %d bytes sent\n\t", n_sent);
		for(i=0; i<NbUInt16ToSend; i++)
		{
			fprintf(FID_debug, "%u ", UInt16ToSend[i]);
		}
		fprintf(FID_debug, "\n");
	#endif
	
	return(n_sent);
}

/************ CHAR8 ***********/
void WaitnChar8_UDP(int socket_id, struct sockaddr_in  *src_info, char *Char8ToWait, int NbChar8ToWait, unsigned int BlockingTimeOut_us)
{
	int n_read;
	int index = 0;
	int NbByteToWait = NbChar8ToWait*NB_BYTE_CHAR8;
	socklen_t src_len = (socklen_t)sizeof(*src_info);
	struct timespec InitTime, CurrentTime;
	int dt;
	
	clock_gettime(CLOCK_MONOTONIC, &InitTime);	// recover current time in nanoseconds
	
	#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
		int nb_formated;
	#endif

	#ifdef ECHO_PRINTF
		printf("<UDP> WaitnChar8_UDP...\n ");
		printf("\t\t bytes received: ");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug, "<UDP> WaitnChar8_UDP...\n ");
		fprintf(FID_debug, "\t\t bytes received: ");
	#endif
	while(index<NbByteToWait)
	{
		n_read = recvfrom(socket_id,(char *)(Char8ToWait+index),(NbByteToWait-index),0,(struct sockaddr *)src_info,&src_len);
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
						fprintf(FID_debug, "%d ", index);
					#endif
				}
			#endif
		}
		clock_gettime(CLOCK_MONOTONIC, &CurrentTime);	// recover current time in nanoseconds
		dt = (CurrentTime.tv_sec - InitTime.tv_sec) * 1000000
			+ (CurrentTime.tv_nsec - InitTime.tv_nsec)/1000;
		if (dt > BlockingTimeOut_us)
		{
			#ifdef ECHO_PRINTF
				printf("\n<UDP> Wait TIME OUT!\n");
			#endif
			#ifdef ECHO_FPRINTF
				fprintf(FID_debug, "\n<UDP> Wait TIME OUT!\n");
			#endif
			return -1; //break;
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
		fprintf(FID_debug, "\n");
		fprintf(FID_debug,"\t\t Received packet from %s:%d\n", inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
		for (nb_formated = 0; nb_formated<NbChar8ToWait; nb_formated++)
		{
			fprintf(FID_debug, "<UDP> ReceivedChar8[%d] = %d\n", nb_formated, Char8ToWait[nb_formated]);
		}
	#endif
}

void ReadnChar8_UDP(int socket_id, struct sockaddr_in *src_info, char *Char8ToWait, int NbChar8ToWait)
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
		fprintf(FID_debug, "<UDP> ReadnChar8_UDP...\n ");
		fprintf(FID_debug, "\t\t bytes received: ");
	#endif
	n_read = recvfrom(socket_id,(char *)Char8ToWait, NbByteToWait, 0, (struct sockaddr*)src_info, (socklen_t *)&src_len);
	if (n_read == -1)
	{
		#ifdef ECHO_PRINTF
			printf("\n");
			printf("<UDP> \t\t ERROR! Any NewData Received! (previous data are conserved...)\n");
		#endif
		#ifdef ECHO_FPRINTF
			fprintf(FID_debug, "\n");
			fprintf(FID_debug, "<UDP> \t\t ERROR! Any NewData Received! (previous data are conserved...)\n");
		#endif
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
			fprintf(FID_debug, "\n");
			fprintf(FID_debug, "<UDP> \t\t Received packet from %s:%d\n", inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
			for (nb_formated = 0; nb_formated<NbChar8ToWait; nb_formated++)
			{
				fprintf(FID_debug, "<UDP> ReceivedChar8[%d] = %d\n", nb_formated, Char8ToWait[nb_formated]);
			}
		#endif
	}
}

void ReadLastnChar8_UDP(int socket_id, struct sockaddr_in *src_info, char *Char8ToWait, int NbChar8ToWait)
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
		fprintf(FID_debug, "<UDP> ReadnChar8_UDP...\n ");
		fprintf(FID_debug, "\t\t bytes received: ");
	#endif
	do
	{
		n_read = recvfrom(socket_id,(char *)Char8ToWait, NbByteToWait, 0, (struct sockaddr*)src_info, (socklen_t *)&src_len);
		if (n_read != -1)
			nb_packet++;
	}
	while(n_read != -1);
	if (nb_packet == 0)
	{
		#ifdef ECHO_PRINTF
			printf("\n");
			printf("<UDP> \t\t ERROR! Any NewData Received! (previous data are conserved...)\n");
		#endif
		#ifdef ECHO_FPRINTF
			fprintf(FID_debug, "\n");
			fprintf(FID_debug, "<UDP> \t\t ERROR! Any NewData Received! (previous data are conserved...)\n");
		#endif	
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
			fprintf(FID_debug, "\n");
			fprintf(FID_debug, "<UDP> \t\t %d packet received from %s:%d\n", nb_packet, inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
			for (nb_formated = 0; nb_formated<NbChar8ToWait; nb_formated++)
			{
				fprintf(FID_debug, "<UDP> LastReceivedChar8[%d] = %d\n", nb_formated, Char8ToWait[nb_formated]);
			}
		#endif
	}
}

int SendnChar8_UDP(int socket_id, struct sockaddr_in *dest_info, char *Char8ToSend, int NbChar8ToSend)
{
	int n_sent;
	#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
		int i;
	#endif
	
	 n_sent=sendto(socket_id,(char *)Char8ToSend,NbChar8ToSend*NB_BYTE_CHAR8,0,(struct sockaddr *)dest_info,sizeof(*dest_info));

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
		fprintf(FID_debug, "<UDP> SendnChar8_UDP...\n");
		fprintf(FID_debug, "\t %d bytes sent\n\t", n_sent);
		for(i=0; i<NbChar8ToSend; i++)
		{
			fprintf(FID_debug, "%d ", Char8ToSend[i]);
		}
		fprintf(FID_debug, "\n");
	#endif
	
	return(n_sent);
}

/************ UCHAR8 ***********/
void WaitnUChar8_UDP(int socket_id, struct sockaddr_in  *src_info, unsigned char *UChar8ToWait, int NbUChar8ToWait, unsigned int BlockingTimeOut_us)
{
	int n_read;
	int index = 0;
	int NbByteToWait = NbUChar8ToWait*NB_BYTE_UCHAR8;
	socklen_t src_len = (socklen_t)sizeof(*src_info);
	struct timespec InitTime, CurrentTime;
	int dt;
	
	clock_gettime(CLOCK_MONOTONIC, &InitTime);	// recover current time in nanoseconds
	
	#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
		int nb_formated;
	#endif

	#ifdef ECHO_PRINTF
		printf("<UDP> WaitnUChar8_UDP...\n ");
		printf("\t\t bytes received: ");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug, "<UDP> WaitnUChar8_UDP...\n ");
		fprintf(FID_debug, "\t\t bytes received: ");
	#endif
	while(index<NbByteToWait)
	{
		n_read = recvfrom(socket_id,(char *)(UChar8ToWait+index),(NbByteToWait-index),0,(struct sockaddr *)src_info,&src_len);
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
						fprintf(FID_debug, "%d ", index);
					#endif
				}
			#endif
		}
		clock_gettime(CLOCK_MONOTONIC, &CurrentTime);	// recover current time in nanoseconds
		dt = (CurrentTime.tv_sec - InitTime.tv_sec) * 1000000
			+ (CurrentTime.tv_nsec - InitTime.tv_nsec)/1000;
		if (dt > BlockingTimeOut_us)
		{
			#ifdef ECHO_PRINTF
				printf("\n<UDP> Wait TIME OUT!\n");
			#endif
			#ifdef ECHO_FPRINTF
				fprintf(FID_debug, "\n<UDP> Wait TIME OUT!\n");
			#endif
			return -1; //break;
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
		fprintf(FID_debug, "\n");
		fprintf(FID_debug,"\t\t Received packet from %s:%d\n", inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
		for (nb_formated = 0; nb_formated<NbUChar8ToWait; nb_formated++)
		{
			fprintf(FID_debug, "<UDP> ReceivedUChar8[%d] = %u\n", nb_formated, UChar8ToWait[nb_formated]);
		}
	#endif
}

void ReadnUChar8_UDP(int socket_id, struct sockaddr_in *src_info, unsigned char *UChar8ToWait, int NbUChar8ToWait)
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
		fprintf(FID_debug, "<UDP> ReadnUChar8_UDP...\n ");
		fprintf(FID_debug, "\t\t bytes received: ");
	#endif
	n_read = recvfrom(socket_id,(char *)UChar8ToWait, NbByteToWait, 0, (struct sockaddr*)src_info, (socklen_t *)&src_len);
	if (n_read == -1)
	{
		#ifdef ECHO_PRINTF
			printf("\n");
			printf("<UDP> \t\t ERROR! Any NewData Received! (previous data are conserved...)\n");
		#endif
		#ifdef ECHO_FPRINTF
			fprintf(FID_debug, "\n");
			fprintf(FID_debug, "<UDP> \t\t ERROR! Any NewData Received! (previous data are conserved...)\n");
		#endif
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
			fprintf(FID_debug, "\n");
			fprintf(FID_debug, "<UDP> \t\t Received packet from %s:%d\n", inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
			for (nb_formated = 0; nb_formated<NbUChar8ToWait; nb_formated++)
			{
				fprintf(FID_debug, "<UDP> ReceivedUChar8[%d] = %u\n", nb_formated, UChar8ToWait[nb_formated]);
			}
		#endif
	}
}

void ReadLastnUChar8_UDP(int socket_id, struct sockaddr_in *src_info, unsigned char *UChar8ToWait, int NbUChar8ToWait)
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
		fprintf(FID_debug, "<UDP> ReadnUChar8_UDP...\n ");
		fprintf(FID_debug, "\t\t bytes received: ");
	#endif
	do
	{
		n_read = recvfrom(socket_id,(char *)UChar8ToWait, NbByteToWait, 0, (struct sockaddr*)src_info, (socklen_t *)&src_len);
		if (n_read != -1)
			nb_packet++;
	}
	while(n_read != -1);
	if (nb_packet == 0)
	{
		#ifdef ECHO_PRINTF
			printf("\n");
			printf("<UDP> \t\t ERROR! Any NewData Received! (previous data are conserved...)\n");
		#endif
		#ifdef ECHO_FPRINTF
			fprintf(FID_debug, "\n");
			fprintf(FID_debug, "<UDP> \t\t ERROR! Any NewData Received! (previous data are conserved...)\n");
		#endif	
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
			fprintf(FID_debug, "\n");
			fprintf(FID_debug, "<UDP> \t\t %d packet received from %s:%d\n", nb_packet, inet_ntoa(src_info->sin_addr), ntohs(src_info->sin_port));
			for (nb_formated = 0; nb_formated<NbUChar8ToWait; nb_formated++)
			{
				fprintf(FID_debug, "<UDP> LastReceivedUChar8[%d] = %u\n", nb_formated, UChar8ToWait[nb_formated]);
			}
		#endif
	}
}

int SendnUChar8_UDP(int socket_id, struct sockaddr_in *dest_info, unsigned char *UChar8ToSend, int NbUChar8ToSend)
{
	int n_sent;
	#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
		int i;
	#endif
	
	 n_sent=sendto(socket_id,(char *)UChar8ToSend,NbUChar8ToSend*NB_BYTE_UCHAR8,0,(struct sockaddr *)dest_info,sizeof(*dest_info));

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
		fprintf(FID_debug, "<UDP> SendnUChar8_UDP...\n");
		fprintf(FID_debug, "\t %d bytes sent\n\t", n_sent);
		for(i=0; i<NbUChar8ToSend; i++)
		{
			fprintf(FID_debug, "%u ", UChar8ToSend[i]);
		}
		fprintf(FID_debug, "\n");
	#endif
	
	return(n_sent);
}
