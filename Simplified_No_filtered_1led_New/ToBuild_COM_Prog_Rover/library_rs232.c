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
 
#include "library_rs232.h"
 
extern FILE *FID_debug;
	
#ifdef XENOMAI
	int Cport[22], error;
	char comPorts[22][13]={"rtser1","rtser2","rtser3","/dev/ttyO3","/dev/ttyO4","/dev/ttyO5",
						   "/dev/ttyO6","/dev/ttyO7","/dev/ttyO8","/dev/ttyO9","/dev/ttyO10","/dev/ttyO11",
						   "/dev/ttyO12","/dev/ttyO13","/dev/ttyO14","/dev/ttyO15","/dev/ttyUSB0",
						   "/dev/ttyUSB1","/dev/ttyUSB2","/dev/ttyUSB3","/dev/ttyUSB4","/dev/ttyUSB5"};
#else
	int Cport[22], error;
	struct termios wished_port_settings;
	struct termios new_port_settings,
		   old_port_settings[22];
	/*	   
	char comPorts[22][13]={"/dev/ttyS0","/dev/ttyS1","/dev/ttyS2","/dev/ttyS3","/dev/ttyS4","/dev/ttyS5",
						   "/dev/ttyS6","/dev/ttyS7","/dev/ttyS8","/dev/ttyS9","/dev/ttyS10","/dev/ttyS11",
						   "/dev/ttyS12","/dev/ttyS13","/dev/ttyS14","/dev/ttyS15","/dev/ttyUSB0",
						   "/dev/ttyUSB1","/dev/ttyUSB2","/dev/ttyUSB3","/dev/ttyUSB4","/dev/ttyUSB5"};*/
	char comPorts[22][13]={"/dev/ttyO0","/dev/ttyO1","/dev/ttyO2","/dev/ttyO3","/dev/ttyO4","/dev/ttyO5",
						   "/dev/ttyO6","/dev/ttyO7","/dev/ttyO8","/dev/ttyO9","/dev/ttyO10","/dev/ttyO11",
						   "/dev/ttyO12","/dev/ttyO13","/dev/ttyO14","/dev/ttyO15","/dev/ttyUSB0",
						   "/dev/ttyUSB1","/dev/ttyUSB2","/dev/ttyUSB3","/dev/ttyUSB4","/dev/ttyUSB5"};
#endif
 

/************************* Ring buffer tools *************************/
void InitRingBuffer(volatile struct RingBuffer *RingBufferPtr)
{
	int i;
	
    RingBufferPtr->SizeOfBuffer = (unsigned int)RING_BUF_SIZE;
    RingBufferPtr->BeginIndex = 0;
    RingBufferPtr->EndIndex = 0;
    for (i=0; i<RING_BUF_SIZE; i++)
    {
		RingBufferPtr->Data[i] = '\0';
	} 
    RingBufferPtr->NbByteInBuffer = 0;
}

void ClearRingBuffer(volatile struct RingBuffer *RingBufferPtr)
{
	RingBufferPtr->BeginIndex = 0;
    RingBufferPtr->EndIndex = 0;
    RingBufferPtr->Data[0] = '\0';
    RingBufferPtr->NbByteInBuffer = 0;
}

void RemoveToRingBufferEnd(volatile struct RingBuffer *RingBufferPtr, int NbBytes)
{
	RingBufferPtr->NbByteInBuffer -= NbBytes;
	RingBufferPtr->NbByteInBuffer  = MAX(RingBufferPtr->NbByteInBuffer, 0);
	RingBufferPtr->EndIndex -= NbBytes;
	RingBufferPtr->EndIndex &= RingBufferPtr->SizeOfBuffer-1;
	RingBufferPtr->Data[RingBufferPtr->EndIndex] = '\0';
}

void RemoveToRingBufferBegin(volatile struct RingBuffer *RingBufferPtr, int NbBytes)
{
	RingBufferPtr->NbByteInBuffer -= NbBytes;
	RingBufferPtr->NbByteInBuffer  = MAX(RingBufferPtr->NbByteInBuffer, 0);
	RingBufferPtr->BeginIndex += NbBytes;
	RingBufferPtr->BeginIndex &= RingBufferPtr->SizeOfBuffer-1;
}	

void AddDataToRingBuffer(volatile struct RingBuffer *RingBufferPtr, char* ToFill, int NbBytes)
{
	int i;
	
	for (i=0; i<NbBytes; i++)
	{
		RingBufferPtr->Data[RingBufferPtr->EndIndex] = ToFill[i];
		RingBufferPtr->NbByteInBuffer ++;
		RingBufferPtr->NbByteInBuffer  = MIN(RingBufferPtr->NbByteInBuffer, RING_BUF_SIZE);
		RingBufferPtr->EndIndex += NbBytes;
		RingBufferPtr->EndIndex &= RingBufferPtr->SizeOfBuffer-1;
	}
}

void AddToRingBuffer(volatile struct RingBuffer *RingBufferPtr, int NbBytes)
{
	RingBufferPtr->NbByteInBuffer += NbBytes;
	RingBufferPtr->NbByteInBuffer = MIN(RingBufferPtr->NbByteInBuffer, RING_BUF_SIZE);
	RingBufferPtr->EndIndex += NbBytes;
	RingBufferPtr->EndIndex &= RingBufferPtr->SizeOfBuffer-1;
}

/********* UART configurations operations *********/
int CleanInputRS232(int ComPortNum)
{
	return(tcflush(Cport[ComPortNum], TCIFLUSH));
}
 
int CleanOutputRS232(int ComPortNum)
{
	return(tcflush(Cport[ComPortNum], TCOFLUSH));
}

int CleanBothRS232(int ComPortNum)
{
	return(tcflush(Cport[ComPortNum], TCIOFLUSH));
} 
 
int initCOMconnection(int ComPortNum, int BaudRate)
{
	printf("<RS232> COM initialization:\n");
	if(OpenComPort(ComPortNum, BaudRate))
	{
		printf("<RS232> \t COM port openning -> FAILED!\n");
		printf("<RS232> COM initialization failed!!!\n\n");
		return(-1);
	}
	else
	{
		printf("<RS232> \t COM port openning -> OK!\n");
		printf("<RS232> COM successfully initialized!!!\n\n");
		return(0);
	}
} 
 
int OpenComPort(int ComPortNum, int BaudRate)
{
	int baudr, config_OK = 1;
	
	if((ComPortNum>21)||(ComPortNum<0))
	{
		printf("<RS232> \t Illegal ComPort number! Device not opened...\n");
		return(1);
	}

	switch(BaudRate)
	{
	case      50 : baudr = B50;
				   break;
	case      75 : baudr = B75;
				   break;
	case     110 : baudr = B110;
				   break;
	case     134 : baudr = B134;
				   break;
	case     150 : baudr = B150;
				   break;
	case     200 : baudr = B200;
				   break;
	case     300 : baudr = B300;
				   break;
	case     600 : baudr = B600;
				   break;
	case    1200 : baudr = B1200;
				   break;
	case    1800 : baudr = B1800;
				   break;
	case    2400 : baudr = B2400;
				   break;
	case    4800 : baudr = B4800;
				   break;
	case    9600 : baudr = B9600;
				   break;
	case   19200 : baudr = B19200;
				   break;
	case   38400 : baudr = B38400;
				   break;
	case   57600 : baudr = B57600;
				   break;
	case  115200 : baudr = B115200;
				   break;
	case  230400 : baudr = B230400;
				   break;
	case  460800 : baudr = B460800;
				   break;
	case  500000 : baudr = B500000;
				   break;
	case  576000 : baudr = B576000;
				   break;
	case  921600 : baudr = B921600;
				   break;
	case  1000000 : baudr = B1000000;
				   break;
	case  1152000 : baudr = B1152000;
				   break;
	case  1500000 : baudr = B1500000;
				   break;
	case  2000000 : baudr = B2000000;
				   break;
	case  2500000 : baudr = B2500000;
				   break;
	case  3000000 : baudr = B3000000;
				   break;
	case  3500000 : baudr = B3500000;
				   break;
	case  4000000 : baudr = B4000000;
				   break;
	default      : 
					printf("<RS232> \tINVALID BaudRate!\n");
					printf("<RS232> \t -> Available BaudRate:  ");
					printf("\t\t50\n");
					printf("\t\t75\n");
					printf("\t\t110\n");
					printf("\t\t134\n");
					printf("\t\t150\n");
					printf("\t\t200\n");
					printf("\t\t300\n");
					printf("\t\t600\n");
					printf("\t\t1200\n");
					printf("\t\t1800\n");
					printf("\t\t2400\n");
					printf("\t\t4800\n");
					printf("\t\t9600\n");
					printf("\t\t19200\n");
					printf("\t\t38400\n");
					printf("\t\t57600\n");
					printf("\t\t115200\n");
					printf("\t\t230400\n");
					printf("\t\t460800\n");
					printf("\t\t500000\n");
					printf("\t\t576000\n");
					printf("\t\t921600\n");
					printf("\t\t1000000\n");
					printf("\t\t1152000\n");
					printf("\t\t1500000\n");
					printf("\t\t2000000\n");
					printf("\t\t2500000\n");
					printf("\t\t3000000\n");
					printf("\t\t3500000\n");
					printf("\t\t4000000\n");
					return(1);
					break;
	}

    #ifdef XENOMAI
		struct rtser_config UARTconfig;
	
		/* open the device */
		Cport[ComPortNum] = rt_dev_open(comPorts[ComPortNum], 0);
		if (Cport[ComPortNum] < 0) {
			printf("ERROR: can't open device %s (%s)\n", comPorts[ComPortNum], strerror(-Cport[ComPortNum]));
			return(1); //exit(1);
		}
		
		/*configuration of the UART bus */
		UARTconfig.config_mask       = RTSER_SET_BAUD | RTSER_SET_TIMEOUT_RX | RTSER_SET_TIMEOUT_TX | RTSER_SET_TIMEOUT_EVENT | RTSER_SET_EVENT_MASK;
		UARTconfig.baud_rate         = BaudRate;
		UARTconfig.rx_timeout        = -1;		// timeout in nanoseconds (non-blocking if negative)
		UARTconfig.tx_timeout        = -1;		// timeout in nanoseconds (non-blocking if negative)
		UARTconfig.event_timeout     = -1;		// timeout in nanoseconds (non-blocking if negative)
		UARTconfig.event_mask		 = RTSER_EVENT_RXPEND;
		
		error = rt_dev_ioctl(Cport[ComPortNum], RTSER_RTIOC_SET_CONFIG, &UARTconfig);
		if (error)
		{
			printf("ERROR: rt_dev_ioctl RTSER_RTIOC_SET_CONFIG (-%d)\n", error);
			return(1); //exit(1);
		}
	#else
		struct serial_struct serial;
		
		Cport[ComPortNum] = open(comPorts[ComPortNum], O_RDWR);
		if(Cport[ComPortNum]==-1)
		{
			char* errorStr = strerror(errno);
			printf("<RS232> unable to open comPort '%s': %s\n", comPorts[ComPortNum], errorStr);
			fprintf(FID_debug, "<RS232> unable to open comPort '%s': %s\n", comPorts[ComPortNum], errorStr);
			return(1);
		}
		else
		{
			printf("<RS232> ComPort opened with flag %d\n", fcntl(Cport[ComPortNum], F_GETFL));
		}
		error = fcntl(Cport[ComPortNum], F_SETFL, O_NOCTTY | fcntl(Cport[ComPortNum], F_GETFL));
		if (error)
		{
			printf("<RS232> Can not set flag O_NOCTTY\n");
		}
		else
		{
			printf("<RS232> ComPort's flag modified to %d\n", fcntl(Cport[ComPortNum], F_GETFL));
		}
		error = fcntl(Cport[ComPortNum], F_SETFL, O_NDELAY | fcntl(Cport[ComPortNum], F_GETFL));
		if (error)
		{
			printf("<RS232> Can not set flag O_NDELAY\n");
		}
		else
		{
			printf("<RS232> ComPort's flag modified to %d\n", fcntl(Cport[ComPortNum], F_GETFL));
		}
		error = fcntl(Cport[ComPortNum], F_SETFL, FNDELAY | fcntl(Cport[ComPortNum], F_GETFL));
		if (error)
		{
			printf("<RS232> Can not set flag FNDELAY\n");
		}
		else
		{
			printf("<RS232> ComPort's flag modified to %d\n", fcntl(Cport[ComPortNum], F_GETFL));
		}
		error = fcntl(Cport[ComPortNum], F_SETFL, O_NONBLOCK | fcntl(Cport[ComPortNum], F_GETFL));
		if (error)
		{
			printf("<RS232> Can not set flag O_NONBLOCK\n");
		}
		else
		{
			printf("<RS232> ComPort's flag modified to %d\n", fcntl(Cport[ComPortNum], F_GETFL));
		}
		/*error = fcntl(Cport[ComPortNum], F_SETFL, O_ASYNC | fcntl(Cport[ComPortNum], F_GETFL));
		if (error)
		{
			printf("<RS232> Can not set flag O_ASYNC\n");
		}
		else
		{
			printf("<RS232> ComPort's flag modified to %d\n", fcntl(Cport[ComPortNum], F_GETFL));
		}*/
		ioctl(Cport[ComPortNum], TIOCGSERIAL, &serial); 
		serial.flags |= ASYNC_LOW_LATENCY; // (0x2000)
		ioctl(Cport[ComPortNum], TIOCSSERIAL, &serial);

		error = tcgetattr(Cport[ComPortNum], old_port_settings + ComPortNum);
		if(error==-1)
		{
			close(Cport[ComPortNum]);
			perror("<RS232> unable to read portsettings ");
			fprintf(FID_debug,"<RS232> unable to read portsettings\n");
			return(1);
		}
		memset(&wished_port_settings, 0, sizeof(wished_port_settings));  /* clear the wished struct */
		memset(&new_port_settings, 0, sizeof(new_port_settings));  /* clear the new struct */

		wished_port_settings.c_cflag = baudr | CS8 | CLOCAL | CREAD;
		wished_port_settings.c_iflag = IGNPAR;
		wished_port_settings.c_oflag = 0;
		wished_port_settings.c_lflag = 0;
		wished_port_settings.c_cc[VMIN] = 0;      /* block until n bytes are received */
		wished_port_settings.c_cc[VTIME] = 0;     /* block until a timer expires (n * 100 mSec.) */
		error = tcsetattr(Cport[ComPortNum], TCSANOW, &wished_port_settings);
		// check that port settings have been applied
		tcgetattr(Cport[ComPortNum], &new_port_settings);
		// test if changes have been applied with success
		if(wished_port_settings.c_cflag != new_port_settings.c_cflag)
		{
			printf("<RS232> Error, BaudRate can not be changed to %d\n", BaudRate);
			config_OK = 0;
		}
		if(wished_port_settings.c_iflag != new_port_settings.c_iflag)
		{
			printf("<RS232> Error, c_iflag can not be changed to %d\n", wished_port_settings.c_iflag);
			config_OK = 0;
		}
		if(wished_port_settings.c_oflag != new_port_settings.c_oflag)
		{
			printf("<RS232> Error, c_oflag can not be changed to %d\n", wished_port_settings.c_oflag);
			config_OK = 0;
		}
		if(wished_port_settings.c_lflag != new_port_settings.c_lflag)
		{
			printf("<RS232> Error, c_lflag can not be changed to %d\n", wished_port_settings.c_lflag);
			config_OK = 0;
		}
		if(wished_port_settings.c_cc[VMIN] != new_port_settings.c_cc[VMIN])
		{
			printf("<RS232> Error, c_cc[VMIN] can not be changed to %d\n", wished_port_settings.c_cc[VMIN]);
			config_OK = 0;
		}
		if(wished_port_settings.c_cc[VTIME] != new_port_settings.c_cc[VTIME])
		{
			printf("<RS232> Error, c_cc[VTIME] can not be changed to %d\n", wished_port_settings.c_cc[VTIME]);
			config_OK = 0;
		}
		if(error==-1)
		{
			close(Cport[ComPortNum]);
			perror("<RS232> unable to adjust portsettings ");
			fprintf(FID_debug, "<RS232> unable to adjust portsettings \n");
			return(1);
		}
	#endif
	
	if (config_OK == 1)
	{
		printf("<RS232> COM port %d successfully opened!!!\n", ComPortNum);
		fprintf(FID_debug, "<RS232> COM port %d successfully opened!!!\n", ComPortNum);
		printf("<RS232> \t   BaudRate: %d\n", BaudRate);
		fprintf(FID_debug, "\t   BaudRate: %d\n", BaudRate);
		printf("<RS232> \t   final flag: %d\n", fcntl(Cport[ComPortNum], F_GETFL));
		return(0);
	}
	else
	{
		return(1);
	}
}
 
void EnableIOinterrupt_RS232(int ComPortNum)
{
	// to be able to catch SIGIO
	fcntl(Cport[ComPortNum], F_SETOWN, getpid());
	fcntl(Cport[ComPortNum], F_SETFL, FASYNC);
}
 
void CloseComPort(int ComPortNum)
{
	#ifdef XENOMAI
		/* close the device */
		error = rt_dev_close(Cport[ComPortNum]);
		if (error < 0) {
			printf("ERROR : can't close ComPort '%s' (%s)\n",	comPorts[ComPortNum], strerror(-error));
		}
		else {
			printf("\t ComPort '%s' successfully closed\n", comPorts[ComPortNum]);
		}
	#else
		error = close(Cport[ComPortNum]);
		if (error < 0) {
			printf("ERROR : can't close ComPort '%s' (%s)\n",	comPorts[ComPortNum], strerror(-error));
		}
		else {
			tcsetattr(Cport[ComPortNum], TCSANOW, old_port_settings + ComPortNum);
			printf("\t ComPort '%s' successfully closed\n", comPorts[ComPortNum]);
		}
	#endif
}

int BytesAvailable(int ComPortNum)
{
	int n_available = 0;
	
	#ifdef XENOMAI	
		struct rtser_event event;
		
		error = rt_dev_ioctl(Cport[ComPortNum], RTSER_RTIOC_WAIT_EVENT, &event);
		if (error)	// && (-error != EAGAIN) && (-error != ETIMEDOUT)
		{
			printf("ERROR: rt_dev_ioctl RTSER_RTIOC_WAIT_EVENT (%d)\n", -error);
			return(-1); //exit(1);
		}
		n_available = event.rx_pending;
	#else
		ioctl(Cport[ComPortNum], FIONREAD, &n_available);
	#endif
	
	#ifdef ECHO_PRINTF
		printf("<RS232> BytesAvailable... \n");
		printf("\t\t %d bytes available on ComPort '%s'\n", n_available, comPorts[ComPortNum]);
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug, "<RS232> BytesAvailable... \n");
		fprintf(FID_debug, "\t\t %d bytes available on ComPort '%s'\n", n_available, comPorts[ComPortNum]);
	#endif
	
	return(n_available);
}
 
int ReadnChar(int ComPortNum, char *ptr, int nb_to_read)
 {
	int ret;
	#ifdef XENOMAI	
		ret = rt_dev_read (Cport[ComPortNum], (void *)ptr, nb_to_read);
	#else
		ret = read (Cport[ComPortNum], ptr, nb_to_read);
	#endif 
	
	return(ret);
 }
 
int WritenChar(int ComPortNum, char *ptr)
 {
	int ret;
	#ifdef XENOMAI
		ret = rt_dev_write (Cport[ComPortNum], (const void *)ptr, strlen(ptr) + 1);
	#else
		ret = write (Cport[ComPortNum], ptr, strlen(ptr) + 1);
	#endif 
	
	return(ret);
 }
 
/********* SYNCHRONIZATION PROTOCOLS RS232 *********/

int SendStartStream_RS232(int ComPortNum, char* StartMessage)
{
	int n_sent;

	#ifdef XENOMAI
		n_sent = rt_dev_write(Cport[ComPortNum], StartMessage, strlen(StartMessage));
	#else
		n_sent = write(Cport[ComPortNum], StartMessage, strlen(StartMessage));
	#endif 
	
	printf("<RS232> SendStartStream_RS232...\n");
	printf("<RS232> \t %d bytes sent: %s\n\t", n_sent, StartMessage);
	fflush(stdout);
	fprintf(FID_debug, "<RS232> SendStartStream_RS232...\n");
	fprintf(FID_debug, "<RS232> \t %d bytes sent: %s\n\t", n_sent, StartMessage);
	//fflush(FID_debug);
	
	return(n_sent);
}

int SendStopStream_RS232(int ComPortNum, char* StopMessage)
{
	int n_sent;

	#ifdef XENOMAI
		n_sent = rt_dev_write(Cport[ComPortNum], StopMessage, strlen(StopMessage));
	#else
		n_sent = write(Cport[ComPortNum], StopMessage, strlen(StopMessage));
	#endif 
	
	printf("<RS232> SendStopStream_RS232...\n");
	printf("<RS232> \t %d bytes sent: %s\n\t", n_sent, StopMessage);
	fflush(stdout);
	fprintf(FID_debug, "<RS232> SendStopStream_RS232...\n");
	fprintf(FID_debug, "<RS232> \t %d bytes sent: %s\n\t", n_sent, StopMessage);
	//fflush(FID_debug);
	
	return(n_sent);
}

int WaitStartStream_RS232(int ComPortNum, char* StartMessage, int TimeOut_ms)
{
	int n_read;
	char ReceivedMessage[6] = "";
	int MessageLen = strlen(StartMessage);
	int index = 0;
	double InitTime = us_time();
	
	printf("<RS232> WaitStartStream_RS232...\n ");
	printf("<RS232: %s> \t\t Bytes Received: ", comPorts[ComPortNum]);
	fflush(stdout);
	fprintf(FID_debug, "<RS232> WaitStartStream_RS232...\n ");
	fprintf(FID_debug, "<RS232: %s> \t\t Bytes Received: ", comPorts[ComPortNum]);
	//fflush(FID_debug);
	
	while(index<(MessageLen))
	{
		#ifdef XENOMAI
			n_read = rt_dev_read(Cport[ComPortNum], (ReceivedMessage+index), (MessageLen-index)); // read only one character
		#else
			n_read = read(Cport[ComPortNum], (ReceivedMessage+index), (MessageLen-index)); // read only one character
		#endif 
		if (n_read > 0)
		{
			index+=n_read;
			printf("%d ", index);
			fprintf(FID_debug, "%d ", index);
		}
		else
		{
			if (us_time()-InitTime > (double)TimeOut_ms*1000.0) // if TimeOut_ms ms are elapsed
			{
				printf("WARNING!!!! Remote peer Unreachable on %s!!!!\n \t=> SIMULATION ABORTED!!!\n", comPorts[ComPortNum]);
				fprintf(FID_debug, "WARNING!!!! Remote peer Unreachable on %s!!!!\n \t=> SIMULATION ABORTED!!!\n", comPorts[ComPortNum]);
				return(-1);
			}
		}
	}
	printf(" -> %s\n", ReceivedMessage);
	fprintf(FID_debug, " -> %s\n", ReceivedMessage);
	
	if(strcmp(ReceivedMessage, StartMessage)==0)
	{
		return(0);
	}
	else
	{
		printf("Start Message '%s' doesn't match to expected message '%s'...\n", ReceivedMessage, StartMessage);
		fprintf(FID_debug, "Start Message '%s' doesn't match to expected message '%s'...\n", ReceivedMessage, StartMessage);
		printf("    -> Check your BaudRate for the remote peer and your COM on %s...\n",  comPorts[ComPortNum]);
		fprintf(FID_debug, "    -> Check your BaudRate for the remote peer and your COM on %s...\n",  comPorts[ComPortNum]);
		return(-1);
	}
}

int WaitStopStream_RS232(int ComPortNum, char* StopMessage, int TimeOut_ms)
{
	int n_read;
	struct RingBuffer MyRingBuffer;		// a circular buffer
	struct RingBuffer *MyRingBufferPtr = &MyRingBuffer;	
	int MessageLen = strlen(StopMessage);
	double InitTime = us_time();
	int StopReceived = 0;
	int TimeOutReached = 0;
	
	printf("<RS232> WaitStopStream_RS232...\n ");
	printf("<RS232: %s> \t\t Bytes Received: ", comPorts[ComPortNum]);
	fflush(stdout);
	fprintf(FID_debug, "<RS232> WaitStopStream_RS232...\n ");
	fprintf(FID_debug, "<RS232: %s> \t\t Bytes Received: ", comPorts[ComPortNum]);
	//fflush(FID_debug);
	
	InitRingBuffer(MyRingBufferPtr);
	
	while(!TimeOutReached && !StopReceived)
	{
		#ifdef XENOMAI
			n_read = rt_dev_read(Cport[ComPortNum], &(MyRingBufferPtr->Data[MyRingBufferPtr->EndIndex]), 1); // read only one character
		#else
			n_read = read(Cport[ComPortNum], &(MyRingBufferPtr->Data[MyRingBufferPtr->EndIndex]), 1); // read only one character
		#endif 
		if (n_read > 0)
		{
			AddToRingBuffer(MyRingBufferPtr, n_read);
			printf("%d (%s)", n_read, &(MyRingBufferPtr->Data[MyRingBufferPtr->EndIndex-MessageLen]));
			fprintf(FID_debug, "%d (%s)", n_read, &(MyRingBufferPtr->Data[MyRingBufferPtr->EndIndex-MessageLen]));
			if(strcmp(&(MyRingBufferPtr->Data[(MyRingBufferPtr->EndIndex)-MessageLen]), StopMessage)==0)
			{
				StopReceived = 1;
			}
		}
		else
		{
			perror("<RS232> Read error: ");
			fprintf(FID_debug, "<RS232> Read error: %s\n", strerror(errno));
		}
		TimeOutReached = (us_time()-InitTime > (double)TimeOut_ms*1000.0);
	}
	printf(" -> %s\n", &(MyRingBufferPtr->Data[(MyRingBufferPtr->EndIndex)-MessageLen]));
	fprintf(FID_debug, " -> %s\n", &(MyRingBufferPtr->Data[(MyRingBufferPtr->EndIndex)-MessageLen]));
	
	if(StopReceived)
	{
		return(0);
	}
	else if(TimeOutReached)
	{
		printf("WARNING! Time out reached and stop message not received...\n");
		fprintf(FID_debug, "WARNING! Time out reached and stop message not received...\n");
	}
	else
	{
		printf("Stop Message '%s' doesn't match to expected message '%s'...\n", &(MyRingBufferPtr->Data[(MyRingBufferPtr->EndIndex)-MessageLen]), StopMessage);
		fprintf(FID_debug, "Stop Message '%s' doesn't match to expected message '%s'...\n", &(MyRingBufferPtr->Data[(MyRingBufferPtr->EndIndex)-MessageLen]), StopMessage);
	}
	printf("    -> Can not be sure that RS232 communication was stopped in remote peer on %s...\n",  comPorts[ComPortNum]);
	fprintf(FID_debug, "    -> Can not be sure that RS232 communication was stopped in remote peer on %s...\n",  comPorts[ComPortNum]);
	return(-1);
}

/***************** RS232 READ/WRITE/WAIT FUNCTIONS ********************/

int Write_RS232(int ComPortNum, void *ToWrite, int NbByteToWrite)
{
	int n_write;
	#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
		//int i;
	#endif
	
	#ifdef XENOMAI
		n_write = rt_dev_write(Cport[ComPortNum], ToWrite, NbByteToWrite);
	#else
		n_write = write(Cport[ComPortNum], ToWrite, NbByteToWrite);
	#endif
	
	#ifdef ECHO_PRINTF
		printf("<RS232> Write_RS232...\n");
		printf("\t %d bytes written\n", n_write);
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug, "<RS232> Write_RS232...\n");
		fprintf(FID_debug, "\t %d bytes written\n", n_write);
	#endif
	
	return(n_write);
}
	
int Wait_RS232(int ComPortNum, void *ToWait, int NbByteToWait)
{
	int n_read;
	int index = 0;
	double InitTime = us_time();
	
	#ifdef ECHO_PRINTF
		printf("<RS232: %s> Wait_RS232...\n ", comPorts[ComPortNum]);
		printf("<RS232: %s> \t\t Bytes Received: ", comPorts[ComPortNum]);
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug, "<RS232: %s> Wait_RS232...\n ", comPorts[ComPortNum]);
		fprintf(FID_debug, "<RS232: %s> \t\t Bytes Received: ", comPorts[ComPortNum]);
	#endif
	while(index<NbByteToWait)
	{
		#ifdef XENOMAI
			n_read = rt_dev_read(Cport[ComPortNum], ToWait+index,  (NbByteToWait-index));
		#else
			n_read = read(Cport[ComPortNum], ToWait+index,  (NbByteToWait-index));
		#endif
		if (n_read > 0)
		{
			index+=n_read;
			#ifdef ECHO_PRINTF
				printf("%d ", index);
			#endif
			#ifdef ECHO_FPRINTF
				fprintf(FID_debug, "%d ", index);
			#endif
		}
		else
		{
			if (us_time()-InitTime > NANOWII_TIMEOUT) // if 100 ms are elapsed
			{
				#ifdef ECHO_PRINTF
					printf("\n<RS232: %s> Wait TIME OUT!\n", comPorts[ComPortNum]);
				#endif
				#ifdef ECHO_FPRINTF
					fprintf(FID_debug, "\n<RS232: %s> Wait TIME OUT!\n", comPorts[ComPortNum]);
				#endif
				return(-1);
			}
		}
	}
	
    return(index); // all is ok
}

int Read_RS232(int ComPortNum, void *ToWait, int NbByteToWait)
{
	int n_read;
	int index = 0;
	double InitTime = us_time();
	
	#ifdef ECHO_PRINTF
		printf("<RS232: %s> Read_RS232...\n ", comPorts[ComPortNum]);
		printf("<RS232: %s> \t\t Bytes Received: ", comPorts[ComPortNum]);
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug, "<RS232: %s> Read_RS232...\n ", comPorts[ComPortNum]);
		fprintf(FID_debug, "<RS232: %s> \t\t Bytes Received: ", comPorts[ComPortNum]);
	#endif
	
	#ifdef XENOMAI
		n_read = rt_dev_read(Cport[ComPortNum], ToWait+index,  (NbByteToWait-index));
	#else
		n_read = read(Cport[ComPortNum], ToWait+index,  (NbByteToWait-index));
	#endif
	if (n_read > 0)
	{
		index+=n_read;
		#ifdef ECHO_PRINTF
			printf("%d\n", index);
		#endif
		#ifdef ECHO_FPRINTF
			fprintf(FID_debug, "%d\n", index);
		#endif
	}
	
	while(n_read>0)
	{
		#ifdef XENOMAI
			n_read = rt_dev_read(Cport[ComPortNum], ToWait+index,  (NbByteToWait-index));
		#else
			n_read = read(Cport[ComPortNum], ToWait+index,  (NbByteToWait-index));
		#endif
		if (n_read > 0)
		{
			index+=n_read;
			#ifdef ECHO_PRINTF
				printf("%d ", index);
			#endif
			#ifdef ECHO_FPRINTF
				fprintf(FID_debug, "%d ", index);
			#endif
		}
		else
		{
			if (us_time()-InitTime > NANOWII_TIMEOUT) // if 100 ms are elapsed
			{
				#ifdef ECHO_PRINTF
					printf("\n<RS232: %s> Wait TIME OUT!\n", comPorts[ComPortNum]);
				#endif
				#ifdef ECHO_FPRINTF
					fprintf(FID_debug, "\n<RS232: %s> Wait TIME OUT!\n", comPorts[ComPortNum]);
				#endif
				return(-1);
			}
		}
	}
	
    return(index); // all is ok
}

int HeaderWrite_RS232(int ComPortNum, void *ToWrite, int NbByteToWrite, unsigned char Header)
{
	int n_write;
	#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
		//int i;
		#ifdef ECHO_PRINTF
			printf("<RS232: %s> HeaderWrite_RS232...\n", comPorts[ComPortNum]);
		#endif
		#ifdef ECHO_FPRINTF
			fprintf(FID_debug, "<RS232: %s> HeaderWrite_RS232...\n", comPorts[ComPortNum]);
		#endif
	#endif
	
	// send the header character
	#ifdef XENOMAI
		n_write = rt_dev_write(Cport[ComPortNum], &Header, 1);
	#else
		n_write = write(Cport[ComPortNum], &Header, 1);
	#endif
	// print the header
	#ifdef ECHO_PRINTF
		printf("<RS232: %s> Header sent: %u\n", comPorts[ComPortNum], Header);
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug, "<RS232: %s> Header sent: %u\n", comPorts[ComPortNum], Header);
	#endif
	// send the data
	#ifdef XENOMAI
		n_write = rt_dev_write(Cport[ComPortNum], ToWrite, NbByteToWrite);
	#else
		n_write = write(Cport[ComPortNum], ToWrite, NbByteToWrite);
	#endif
	
	return(n_write);
}

int HeaderRead_RS232(int ComPortNum, void *ToWait, int NbByteToWait, unsigned char Header)
{
	int n_read;
	int index = 0;
	unsigned char StreamBegin = Header-1;
	int BytesAvailableOnCom;
	#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
		//int nb_formated;
		char Prefix[25];
		sprintf((char*)Prefix, "<RS232: %s>", comPorts[ComPortNum]);
	#endif
	
	#ifdef ECHO_PRINTF
		printf("%s HeaderRead_RS232(%d), (fd = %d)\n", Prefix, NbByteToWait, Cport[ComPortNum]);
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug, "%s HeaderRead_RS232(%d), (fd = %d)\n", Prefix, NbByteToWait, Cport[ComPortNum]);
	#endif
	
	// read how much data are available
	BytesAvailableOnCom = BytesAvailable(ComPortNum);
	if (BytesAvailableOnCom>0)
	{
		while (BytesAvailableOnCom >= (NbByteToWait+1))
		{
			// look for the header of the last stream
			#ifdef XENOMAI
				n_read = rt_dev_read (Cport[ComPortNum], &StreamBegin,  1);
			#else
				n_read = read(Cport[ComPortNum], &StreamBegin,  1);
			#endif
			#ifdef ECHO_PRINTF
				printf("\n%s Header read: %u", Prefix, StreamBegin);
			#endif
			#ifdef ECHO_FPRINTF
				fprintf(FID_debug, "\n%s Header read: %u", Prefix, StreamBegin);
			#endif
			while( (n_read>0)&&(StreamBegin!=Header) )
			{
				#ifdef XENOMAI
					n_read = rt_dev_read (Cport[ComPortNum], &StreamBegin,  1);
				#else
					n_read = read(Cport[ComPortNum], &StreamBegin,  1);
				#endif
				#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
					if (n_read>0)
					{
						#ifdef ECHO_PRINTF
							printf(" %u", StreamBegin);
						#endif
						#ifdef ECHO_FPRINTF
							fprintf(FID_debug, " %u", StreamBegin);
						#endif
					}
					else if (n_read < 0)
					{
						#ifdef ECHO_PRINTF
							perror("<RS232> error: ");
						#endif
						#ifdef ECHO_FPRINTF
							fprintf(FID_debug, "<RS232> error: %s\n", strerror(errno));
						#endif
					}
				#endif
			}
			index = 0;
			// Read the data until there is no more 
			#ifdef XENOMAI
				n_read = rt_dev_read(Cport[ComPortNum], ToWait,  NbByteToWait);
			#else
				n_read = read(Cport[ComPortNum], ToWait,  NbByteToWait);
			#endif
			if (n_read > 0)
			{
				index+=n_read;
				#ifdef ECHO_PRINTF
					printf("\n%s Nb Data read: %d\n", Prefix, n_read);
				#endif
				#ifdef ECHO_FPRINTF
					fprintf(FID_debug, "\n%s Nb Bytes read:  = %d\n", Prefix, n_read);
				#endif
			}
			#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
				else if (n_read < 0)
				{
					#ifdef ECHO_PRINTF
						perror("<RS232> error: ");
					#endif
					#ifdef ECHO_FPRINTF
						fprintf(FID_debug, "\nRS232 error: %s\n", strerror(errno));
					#endif
				}
			#endif
			// while all the data were not read
			while( (n_read>0) && ( index<NbByteToWait ))
			{
				#ifdef XENOMAI
					n_read = rt_dev_read(Cport[ComPortNum], ToWait+index,  NbByteToWait-index);
				#else
					n_read = read(Cport[ComPortNum], ToWait+index,  NbByteToWait-index);
				#endif
				#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
					if (n_read>0)
					{
						#ifdef ECHO_PRINTF
							printf(" %d", n_read);
						#endif
						#ifdef ECHO_FPRINTF
							fprintf(FID_debug, " %d", n_read);
						#endif
					}
					else if (n_read < 0)
					{
						#ifdef ECHO_PRINTF
							perror("<RS232> error: ");
						#endif
						#ifdef ECHO_FPRINTF
							fprintf(FID_debug, "<RS232> error: %s\n", strerror(errno));
						#endif
					}
				#endif
				index+=n_read;
			}
			
			if (BytesAvailableOnCom > (NbByteToWait+1)) {
				BytesAvailableOnCom = BytesAvailable(ComPortNum);
			}
			else {
				BytesAvailableOnCom = 0;	// avoid calling ioctl if data were exactly the number needed (could stock if timeout != -1)
			}
		}
	}
	else
	{
		#ifdef ECHO_PRINTF
			printf("%s Nothing to read!\n", Prefix);
		#endif
		#ifdef ECHO_FPRINTF
			fprintf(FID_debug, "%s Nothing to read!\n", Prefix);
		#endif
		return(0);
	}
	
	return(index);
}

int HeaderWait_RS232(int ComPortNum, void *ToWait, int NbByteToWait, unsigned char Header, int BlockingTimeOut_us)
{
	int n_read, i;
	int index = 0;
	unsigned char StreamBegin = Header-1;
	int BytesAvailableOnCom = 0;
	int dt;
	//struct timeval InitTime, CurrentTime;
	struct timespec InitTime, CurrentTime;
	#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
		//int nb_formated;
		char Prefix[25];
		sprintf((char*)Prefix, "<RS232: %s>", comPorts[ComPortNum]);
	#endif
	
	//gettimeofday(&InitTime, NULL);		// recover current time in microseconds
	clock_gettime(CLOCK_MONOTONIC, &InitTime);	// recover current time in nanoseconds
	
	#ifdef ECHO_PRINTF
		printf("%s HeaderWait_RS232(%d), (fd = %d)\n", Prefix, NbByteToWait, Cport[ComPortNum]);
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug, "%s HeaderWait_RS232(%d), (fd = %d)\n", Prefix, NbByteToWait, Cport[ComPortNum]);
	#endif
	
	// recover eventual old data
	BytesAvailableOnCom = BytesAvailable(ComPortNum);
	if (BytesAvailableOnCom > (NbByteToWait+1))
	{
		// recover eventual old stream(s)
		#ifdef ECHO_PRINTF
			printf("\n%s Old data skipped (bytes): ", Prefix);
		#endif
		#ifdef ECHO_FPRINTF
			fprintf(FID_debug, "\n%s Old data skipped (bytes): ", Prefix);
		#endif
		for(i=0; i<(BytesAvailableOnCom-(NbByteToWait+1)); i++)
		{
			#ifdef XENOMAI
				n_read = rt_dev_read (Cport[ComPortNum], &StreamBegin,  1);
			#else
				n_read = read(Cport[ComPortNum], &StreamBegin,  1);
			#endif
			#ifdef ECHO_PRINTF
				printf("%u ", StreamBegin);
			#endif
			#ifdef ECHO_FPRINTF
				fprintf(FID_debug, "%u ", StreamBegin);
			#endif
		}
	}
	
	// look for the header of the last stream
	StreamBegin = Header-1;
	#ifdef XENOMAI
		n_read = rt_dev_read (Cport[ComPortNum], &StreamBegin,  1);
	#else
		n_read = read(Cport[ComPortNum], &StreamBegin,  1);
	#endif
	#ifdef ECHO_PRINTF
		printf("\n%s Header: %u", Prefix, StreamBegin);
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug, "\n%s Header: %u", Prefix, StreamBegin);
	#endif
	while( (n_read>=0)&&(StreamBegin!=Header) )
	{
		#ifdef XENOMAI
			n_read = rt_dev_read (Cport[ComPortNum], &StreamBegin,  1);
		#else
			n_read = read(Cport[ComPortNum], &StreamBegin,  1);
		#endif
		#if (defined(ECHO_PRINTF)||defined(ECHO_FPRINTF))
			if (n_read>0)
			{
				#ifdef ECHO_PRINTF
					printf(" %u", StreamBegin);
				#endif
				#ifdef ECHO_FPRINTF
					fprintf(FID_debug, " %u", StreamBegin);
				#endif
			}
			else if (n_read < 0)
			{
				#ifdef ECHO_PRINTF
					perror("<RS232> error: ");
				#endif
				#ifdef ECHO_FPRINTF
					fprintf(FID_debug, "<RS232> error: %s\n", strerror(errno));
				#endif
			}
		#endif
		//gettimeofday(&CurrentTime, NULL);	// recover current time in microseconds
		//dt = (CurrentTime.tv_sec - InitTime.tv_sec) * 1000000
		//	+ CurrentTime.tv_usec - InitTime.tv_usec;
		clock_gettime(CLOCK_MONOTONIC, &CurrentTime);	// recover current time in nanoseconds
		dt = (CurrentTime.tv_sec - InitTime.tv_sec) * 1000000
			+ (CurrentTime.tv_nsec - InitTime.tv_nsec)/1000;
		if (dt > BlockingTimeOut_us)
		{
			#ifdef ECHO_PRINTF
				printf("\n%s Wait TIME OUT!\n", Prefix);
			#endif
			#ifdef ECHO_FPRINTF
				fprintf(FID_debug, "\n%s Wait TIME OUT!\n", Prefix);
			#endif
			return -1; //break;
		}
	}
	
	// recover the current stream
	#ifdef ECHO_PRINTF
		printf("\n%s NbBytesRead: ", Prefix);
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug, "\n%s NbBytesRead: ", Prefix);
	#endif
	while(index<NbByteToWait)
	{
		#ifdef XENOMAI
			n_read = rt_dev_read(Cport[ComPortNum], ToWait+index,  (NbByteToWait-index));
		#else
			n_read = read(Cport[ComPortNum], ToWait+index,  (NbByteToWait-index));
		#endif
		if ( n_read > 0 )
		{
			index+=n_read;
			#ifdef ECHO_PRINTF
				printf("%d ", index);
			#endif
			#ifdef ECHO_FPRINTF
				fprintf(FID_debug, "%d ", index);
			#endif
		}
		else
		{
			//gettimeofday(&CurrentTime, NULL);	// recover current time in microseconds
			//dt = (CurrentTime.tv_sec - InitTime.tv_sec) * 1000000
			//	+ CurrentTime.tv_usec - InitTime.tv_usec;
			clock_gettime(CLOCK_MONOTONIC, &CurrentTime);	// recover current time in nanoseconds
			dt = (CurrentTime.tv_sec - InitTime.tv_sec) * 1000000
				+ (CurrentTime.tv_nsec - InitTime.tv_nsec)/1000;
			if (dt > BlockingTimeOut_us)
			{
				#ifdef ECHO_PRINTF
					printf("\n%s Wait TIME OUT!\n", Prefix);
				#endif
				#ifdef ECHO_FPRINTF
					fprintf(FID_debug, "\n%s Wait TIME OUT!\n", Prefix);
				#endif
				return -1; //break;
			}
		}
	}
	#ifdef ECHO_PRINTF
		printf("\n");
	#endif
	#ifdef ECHO_FPRINTF
		fprintf(FID_debug, "\n");
	#endif
	
	return(index);
}

