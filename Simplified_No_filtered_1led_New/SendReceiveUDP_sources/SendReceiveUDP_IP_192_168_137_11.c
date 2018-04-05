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
 
#define S_FUNCTION_NAME SendReceiveUDP_IP_192_168_137_11
#define S_FUNCTION_LEVEL 2

/*================*
 * Build checking *
 *================*/
 
// ********************************************************
// Les includes
// ********************************************************
#include "SendReceiveUDP_IP_192_168_137_11.h"

// ********************************************************
// Les librairies
// ********************************************************
#pragma comment(lib,"ws2_32.lib")

// ********************************************************
// Définition des variables
// ********************************************************
extern SOCKET socket_id[NB_IP_MAX];                       // Socket identifier
extern SOCKADDR_IN gumstix_info[NB_IP_MAX], host_info[NB_IP_MAX];	// Structure linked to client socket information
extern SOCKADDR_IN src_info[NB_IP_MAX];	// Structure linked to client socket information
//real_T data_rcv[HOST_UDP_NB_DATA_RECV];  	// data received (maximum number set in "define_udp.h")
extern FILE* FID_debug_SendReceiveUDP[NB_IP_MAX];
extern unsigned short init_status_SendReceiveUDP[NB_IP_MAX];
extern struct TicToc struc_TicToc;

/* Function: mdlInitializeSizes ===============================================
 * Abstract:
 *   Setup sizes of the various vectors.
 */
static void mdlInitializeSizes(SimStruct *S)
{
	//DTypeId SendDataType = GetDataToSendType_UDP(S);
	//DTypeId ReceiveDataType = GetDataToReceiveType_UDP(S);
	char *Type_str = (char*)calloc(8, sizeof(char)); // 8 is the max length of data type ('double64' is a string containing 8 character)
    char IP_remote_str[16], IP_host_str[16];
	int buflen, status, port;	
	DTypeId SendDataType, ReceiveDataType;
	
	// GetIPinfo()
		// recover IP_remote_str length
		buflen = (int)(mxGetN(ssGetSFcnParam(S, 2))*sizeof(mxChar)+1);
		// recover IP_address_str
		status = mxGetString(ssGetSFcnParam(S, 2), IP_remote_str, (mwSize)buflen);
		printf("\t<UDP> \t\t Initialization of SendReceiveUDP_IP_%s.c\n", IP_remote_str);
		printf("\t<UDP> \t\t\t GetIPremote_UDP()\n");
		printf("\t<UDP> \t\t\t -> %s \n", IP_remote_str);
		// recover IP_host_str length
		printf("\t<UDP> \t\t\t GetIPhost_UDP()\n");
		buflen = (int)(mxGetN(ssGetSFcnParam(S, 3))*sizeof(mxChar)+1);
		// recover IP_host_str
		status = mxGetString(ssGetSFcnParam(S, 3), IP_host_str, (mwSize)buflen);
		printf("\t<UDP> \t\t\t -> %s \n", IP_host_str);
		// recover int port;
		printf("\t<UDP> \t\t\t GetPort_UDP()\n");
		port = (int)(( mxGetPr(ssGetSFcnParam(S, 4)))[0]);
		printf("\t<UDP> \t\t\t -> %d \n", port);
		
	
	//DTypeId SendDataType = GetDataToSendType_UDP(S);
		printf("\t<UDP> \t\t\t GetDataToSendType_UDP()\n");
		// recover DataToSendType length
		buflen = (int)(mxGetN(ssGetSFcnParam(S, 0))*sizeof(mxChar)+1);
		// recover file_name
		status = mxGetString(ssGetSFcnParam(S, 0), Type_str, (mwSize)buflen);
		
		// return the DTypeId corresponding to the DataToSendType
		if(strcmp(Type_str, "double64") == 0)
		{
			SendDataType = SS_DOUBLE;
		}
		if(strcmp(Type_str, "float32") == 0)
		{
			SendDataType = SS_SINGLE;
		}
		if(strcmp(Type_str, "int32") == 0)
		{
			SendDataType = SS_INT32;
		}
		if(strcmp(Type_str, "Uint32") == 0)
		{
			SendDataType = SS_UINT32;
		}
		if(strcmp(Type_str, "int16") == 0)
		{
			SendDataType = SS_INT16;
		}
		if(strcmp(Type_str, "Uint16") == 0)
		{
			SendDataType = SS_UINT16;
		}
		if(strcmp(Type_str, "char8") == 0)
		{
			SendDataType = SS_INT8;
		}
		if(strcmp(Type_str, "Uchar8") == 0)
		{
			SendDataType = SS_UINT8;
		}
		
		printf("\t<UDP> \t\t\t -> %s \n", Type_str);
		memset(Type_str, '\0', 8*sizeof(char));
	
	//DTypeId ReceiveDataType = GetDataToReceiveType_UDP(S);
		printf("\t<UDP> \t\t\t GetDataToReceiveType_UDP()\n");
		// recover DataToSendType length
		buflen = (int)(mxGetN(ssGetSFcnParam(S, 1))*sizeof(mxChar)+1);
		// recover file_name
		status = mxGetString(ssGetSFcnParam(S, 1), Type_str, (mwSize)buflen);
		// return the DTypeId corresponding to the DataToSendType
		if(strcmp(Type_str, "double64") == 0)
		{
			ReceiveDataType = SS_DOUBLE;
		}
		if(strcmp(Type_str, "float32") == 0)
		{
			ReceiveDataType = SS_SINGLE;
		}
		if(strcmp(Type_str, "int32") == 0)
		{
			ReceiveDataType = SS_INT32;
		}
		if(strcmp(Type_str, "Uint32") == 0)
		{
			ReceiveDataType = SS_UINT32;
		}
		if(strcmp(Type_str, "int16") == 0)
		{
			ReceiveDataType = SS_INT16;
		}
		if(strcmp(Type_str, "Uint16") == 0)
		{
			ReceiveDataType = SS_UINT16;
		}
		if(strcmp(Type_str, "char8") == 0)
		{
			ReceiveDataType = SS_INT8;
		}
		if(strcmp(Type_str, "Uchar8") == 0)
		{
			ReceiveDataType = SS_UINT8;
		}
		
		printf("\t<UDP> \t\t\t -> %s\n", Type_str);
		free(Type_str);
	
	
    ssSetNumSFcnParams(S, 5);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        return; /* Parameter mismatch will be reported by Simulink */
    }

    if (!ssSetNumInputPorts(S, 1)) return;
    ssSetInputPortWidth(S, 0, HOST_UDP_NB_DATA_SEND);
	ssSetInputPortDataType(S, 0, SendDataType); // to enforce the type of data in the input...
	ssSetInputPortRequiredContiguous(S, 0, 1); // enforce the input to be written inn contiguous memory space
    ssSetInputPortDirectFeedThrough(S, 0, 1);

    if (!ssSetNumOutputPorts(S,1)) return;
    ssSetOutputPortWidth(S, 0, HOST_UDP_NB_DATA_RECV+1);
	ssSetOutputPortDataType(S, 0, ReceiveDataType); // to enforce the type of data in the output...
        
    ssSetNumSampleTimes(S, 1);

    /* specify the sim state compliance to be same as a built-in block */
    ssSetSimStateCompliance(S, USE_DEFAULT_SIM_STATE);

    /* Take care when specifying exception free code - see sfuntmpl_doc.c */
    ssSetOptions(S,
                 SS_OPTION_EXCEPTION_FREE_CODE |
                 SS_OPTION_USE_TLC_WITH_ACCELERATOR);
}


/* Function: mdlInitializeSampleTimes =========================================
 * Abstract:
 *    Specifiy that we inherit our sample time from the driving block.
 */
static void mdlInitializeSampleTimes(SimStruct *S)
{
    ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
    ssSetOffsetTime(S, 0, 0.0);
    ssSetModelReferenceSampleTimeDefaultInheritance(S); 
}

/* Function: mdlOutputs =======================================================
 * Abstract:
 *    y = 2*u
 */
static void mdlOutputs(SimStruct *S, int_T tid)
{
	char IP_remote_str[16]; // 15 is the max length of IP in format '255_255_255_255' 
    int buflen;
	int status;
	int index;
	
	// simulink variables
	real32_T *uPtrs = (real32_T *)ssGetInputPortSignal(S,0);	
	real32_T *yPtrs = (real32_T *)ssGetOutputPortSignal(S,0);
	
   // udp receive/send variables
    int nb_packet = 0;                   // to know if data were updated
    static double first_time_ms = 0.0;
    double init_time_ms = ms_time();
    
	// GetIPaddress()
		// recover DataToSendType length
		buflen = (int)(mxGetN(ssGetSFcnParam(S, 2))*sizeof(mxChar)+1);
		// recover file_name
		status = mxGetString(ssGetSFcnParam(S, 2), IP_remote_str, (mwSize)buflen);
		// GetIPlastNumber()
		index = GetIPlastNumber(IP_remote_str);
	
	#ifdef ECHO_PRINTF
        printf("\n-------------------------------\n");
	#endif
	#ifdef ECHO_FPRINTF
        fprintf(FID_debug_SendReceiveUDP[index],"\n-------------------------------\n");
    #endif
	if (first_time_ms == 0.0)
    {
        first_time_ms = ms_time();
		#if (defined(ECHO_PRINTF) || defined(ECHO_FPRINTF))
			init_time_ms = ms_time();
			#ifdef ECHO_PRINTF
				printf("\t<UDP> Time: %.3f\n", init_time_ms-first_time_ms);
			#endif
			#ifdef ECHO_FPRINTF
				fprintf(FID_debug_SendReceiveUDP[index],"\t<UDP> Time: %.3f\n", init_time_ms-first_time_ms);
			#endif
		#endif
		// ********************************************************
		// Format and send the first stream
		// ********************************************************
		SendnFloat_UDP(index, &(gumstix_info[index]), uPtrs, HOST_UDP_NB_DATA_SEND);
    }
	else
	{
		#if (defined(ECHO_PRINTF) || defined(ECHO_FPRINTF))
			init_time_ms = ms_time();
			#ifdef ECHO_PRINTF
				printf("\t<UDP> Time: %.3f\n", init_time_ms-first_time_ms);
			#endif
			#ifdef ECHO_FPRINTF
				fprintf(FID_debug_SendReceiveUDP[index],"\t<UDP> Time: %.3f\n", init_time_ms-first_time_ms);
			#endif
		#endif
		if(init_status_SendReceiveUDP[index]==0)
		{
			// ********************************************************
			// Format and send the stream
			// ********************************************************
			SendnFloat_UDP(index, &(gumstix_info[index]), uPtrs, HOST_UDP_NB_DATA_SEND);
			
			// ********************************************************
			// Reception of data
			// ********************************************************
			nb_packet = ReadLastnFloat_UDP(index, &(src_info[index]), &yPtrs[1], HOST_UDP_NB_DATA_RECV);
			
			yPtrs[0] = (real32_T)nb_packet; 
		}
		else
		{
			printf("\t<UDP> \t\tERROR, UDP connection FAILED!\n");
			fprintf(FID_debug_SendReceiveUDP[index],"\t\tERROR, UDP connection FAILED!\n");
		}
	}
}


/* Function: mdlTerminate =====================================================
 * Abstract:
 *    No termination needed, but we are required to have this routine.
 */
#define MDL_TERMINATE  /* Change to #undef to remove function */
#if defined(MDL_TERMINATE)
static void mdlTerminate(SimStruct *S)
{
	char IP_remote_str[16]; // 15 is the max length of IP in format '255_255_255_255' 
    int buflen;
	int status;
	int index;
	
	// GetIPaddress()
		// recover DataToSendType length
		buflen = (int)(mxGetN(ssGetSFcnParam(S, 2))*sizeof(mxChar)+1);
		// recover file_name
		status = mxGetString(ssGetSFcnParam(S, 2), IP_remote_str, (mwSize)buflen);
		// GetIPlastNumber()
		index = GetIPlastNumber(IP_remote_str);
		
    printf("\t<UDP> MdlTerminate()\n");
	if (FID_debug_SendReceiveUDP[index] != NULL)
	{
		fprintf(FID_debug_SendReceiveUDP[index],"MdlTerminate()\n");
		fflush(FID_debug_SendReceiveUDP[index]);
		CleanUpMdlStartSendReceiveUDP(index, IP_remote_str);
	}
    else
    {
        printf("\t<UDP> \tModel already terminated with QuarcRealTimeWindowsTarget... Nothing to do.\n");
    }
}
#endif

#define MDL_START  /* Change to #undef to remove function */
#if defined(MDL_START) 
  /* Function: mdlStart =======================================================
   * Abstract:
   *    This function is called once at start of model execution. If you
   *    have states that should be initialized once, this is the place
   *    to do it.
   */
  static void mdlStart(SimStruct *S)
  {
	char IP_remote_str[16]; // 15 is the max length of IP in format '255_255_255_255' 
	char IP_host_str[16]; // 15 is the max length of IP in format '255_255_255_255' 
    int buflen, status, index, port, i;
	char NameDebug[200];
	
	// GetIPinfo()
		// recover IP_remote_str length
		printf("\t<UDP> \t\t\t GetIPremote_UDP()\n");
		buflen = (int)(mxGetN(ssGetSFcnParam(S, 2))*sizeof(mxChar)+1);
		// recover IP_address_str
		status = mxGetString(ssGetSFcnParam(S, 2), IP_remote_str, (mwSize)buflen);
		printf("\t<UDP> \t\t\t -> %s \n", IP_remote_str);
		// recover IP_host_str length
		printf("\t<UDP> \t\t\t GetIPhost_UDP()\n");
		buflen = (int)(mxGetN(ssGetSFcnParam(S, 3))*sizeof(mxChar)+1);
		// recover IP_host_str
		status = mxGetString(ssGetSFcnParam(S, 3), IP_host_str, (mwSize)buflen);
		printf("\t<UDP> \t\t\t -> %s \n", IP_host_str);
		// recover int port;
		printf("\t<UDP> \t\t\t GetPort_UDP()\n");
		port = (int)(( mxGetPr(ssGetSFcnParam(S, 4)))[0]);
		printf("\t<UDP> \t\t\t -> %d \n", port);
		
		// GetIPlastNumber()
		index = GetIPlastNumber(IP_remote_str);
		
		printf("\t<UDP> \t\t\t -> %s \n", IP_remote_str);
		printf("\t<UDP> \t\t\t -> %d \n", index);
	
	memset(NameDebug, '\0', 200);
	strcat(NameDebug, "./SendReceiveUDP_sources/SendReceiveUDP_debug_IP_");
	strcat(NameDebug, IP_remote_str);
	strcat(NameDebug, ".debug");
	
	printf("\t<UDP> \t\t\t -> %s \n", NameDebug);
	
	/********* INITIALISATION***********/
	FID_debug_SendReceiveUDP[index] = fopen(NameDebug, "w"); // pour le debuggage
	printf("\t<UDP> INITIALISATION...\n");
	fprintf(FID_debug_SendReceiveUDP[index],"INITIALISATION...\n");
	
	if (FID_debug_SendReceiveUDP[index]==NULL)
	{
		printf("\t<UDP> \tDebug file: SendReceiveUDP_debug.debug CREATION ERROR!\n");
		init_status_SendReceiveUDP[index] = (init_status_SendReceiveUDP[index]|ERROR_FOPEN);
	}
	else
	{
		printf("\t<UDP> \tDebug file: SendReceiveUDP_debug.debug with file_ID: %d!\n", FID_debug_SendReceiveUDP[index]);
		fprintf(FID_debug_SendReceiveUDP[index],"\tDebug file: SendReceiveUDP_debug.debug with file_ID: %d!\n", FID_debug_SendReceiveUDP[index]);
		fflush(FID_debug_SendReceiveUDP[index]);
	}
	
	fprintf(FID_debug_SendReceiveUDP[index],"index: %d, IP_remot: %s, IP_host: %s\n", index, IP_remote_str, IP_host_str);
	fflush(FID_debug_SendReceiveUDP[index]);

	// ********************************************************
	// Open UDP connection
	// ********************************************************
	// reformat the string of IP address
	for (i=0; i<15; i++)
	{
		if (IP_remote_str[i] == '_')
		{
			IP_remote_str[i] = '.';
		}
		if (IP_host_str[i] == '_')
		{
			IP_host_str[i] = '.';
		}
	}

	initUDPconnection(index, IP_remote_str, IP_host_str, port);
	
    // ********************************************************
	// Update Connect To Target Log File
	// ********************************************************
	// reformat the string of IP address
	for (i=0; i<15; i++)
	{
		if (IP_remote_str[i] == '.')
		{
			IP_remote_str[i] = '_';
		}
	}
	
    ConnectLogUpdate_SendReceiveUDP(FID_debug_SendReceiveUDP[index], IP_remote_str, index);
    
    printf("\t<UDP> INITIALISATION DONE!\n");
    
  }
#endif /*  MDL_START */

#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif
