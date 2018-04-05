/* Include files */

#include "QUARC_Prog_Rover_sfun.h"
#include "c1_QUARC_Prog_Rover.h"
#include "c2_QUARC_Prog_Rover.h"
#include "c5_QUARC_Prog_Rover.h"
#include "c6_QUARC_Prog_Rover.h"
#include "c7_QUARC_Prog_Rover.h"
#include "c8_QUARC_Prog_Rover.h"
#include "c9_QUARC_Prog_Rover.h"
#include "c10_QUARC_Prog_Rover.h"
#include "c11_QUARC_Prog_Rover.h"
#include "c12_QUARC_Prog_Rover.h"
#include "c13_QUARC_Prog_Rover.h"
#include "c15_QUARC_Prog_Rover.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
uint32_T _QUARC_Prog_RoverMachineNumber_;
real_T _sfTime_;

/* Function Declarations */

/* Function Definitions */
void QUARC_Prog_Rover_initializer(void)
{
}

void QUARC_Prog_Rover_terminator(void)
{
}

/* SFunction Glue Code */
unsigned int sf_QUARC_Prog_Rover_method_dispatcher(SimStruct *simstructPtr,
  unsigned int chartFileNumber, const char* specsCksum, int_T method, void *data)
{
  if (chartFileNumber==1) {
    c1_QUARC_Prog_Rover_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==2) {
    c2_QUARC_Prog_Rover_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==5) {
    c5_QUARC_Prog_Rover_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==6) {
    c6_QUARC_Prog_Rover_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==7) {
    c7_QUARC_Prog_Rover_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==8) {
    c8_QUARC_Prog_Rover_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==9) {
    c9_QUARC_Prog_Rover_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==10) {
    c10_QUARC_Prog_Rover_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==11) {
    c11_QUARC_Prog_Rover_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==12) {
    c12_QUARC_Prog_Rover_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==13) {
    c13_QUARC_Prog_Rover_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  if (chartFileNumber==15) {
    c15_QUARC_Prog_Rover_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  return 0;
}

unsigned int sf_QUARC_Prog_Rover_process_testpoint_info_call( int nlhs, mxArray *
  plhs[], int nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[32];
  char machineName[128];
  if (nrhs < 3 || !mxIsChar(prhs[0]) || !mxIsChar(prhs[1]))
    return 0;

  /* Possible call to get testpoint info. */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_testpoint_info"))
    return 0;
  mxGetString(prhs[1], machineName, sizeof(machineName)/sizeof(char));
  machineName[(sizeof(machineName)/sizeof(char)-1)] = '\0';
  if (!strcmp(machineName, "QUARC_Prog_Rover")) {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[2]);
    switch (chartFileNumber) {
     case 1:
      {
        extern mxArray *sf_c1_QUARC_Prog_Rover_get_testpoint_info(void);
        plhs[0] = sf_c1_QUARC_Prog_Rover_get_testpoint_info();
        break;
      }

     case 2:
      {
        extern mxArray *sf_c2_QUARC_Prog_Rover_get_testpoint_info(void);
        plhs[0] = sf_c2_QUARC_Prog_Rover_get_testpoint_info();
        break;
      }

     case 5:
      {
        extern mxArray *sf_c5_QUARC_Prog_Rover_get_testpoint_info(void);
        plhs[0] = sf_c5_QUARC_Prog_Rover_get_testpoint_info();
        break;
      }

     case 6:
      {
        extern mxArray *sf_c6_QUARC_Prog_Rover_get_testpoint_info(void);
        plhs[0] = sf_c6_QUARC_Prog_Rover_get_testpoint_info();
        break;
      }

     case 7:
      {
        extern mxArray *sf_c7_QUARC_Prog_Rover_get_testpoint_info(void);
        plhs[0] = sf_c7_QUARC_Prog_Rover_get_testpoint_info();
        break;
      }

     case 8:
      {
        extern mxArray *sf_c8_QUARC_Prog_Rover_get_testpoint_info(void);
        plhs[0] = sf_c8_QUARC_Prog_Rover_get_testpoint_info();
        break;
      }

     case 9:
      {
        extern mxArray *sf_c9_QUARC_Prog_Rover_get_testpoint_info(void);
        plhs[0] = sf_c9_QUARC_Prog_Rover_get_testpoint_info();
        break;
      }

     case 10:
      {
        extern mxArray *sf_c10_QUARC_Prog_Rover_get_testpoint_info(void);
        plhs[0] = sf_c10_QUARC_Prog_Rover_get_testpoint_info();
        break;
      }

     case 11:
      {
        extern mxArray *sf_c11_QUARC_Prog_Rover_get_testpoint_info(void);
        plhs[0] = sf_c11_QUARC_Prog_Rover_get_testpoint_info();
        break;
      }

     case 12:
      {
        extern mxArray *sf_c12_QUARC_Prog_Rover_get_testpoint_info(void);
        plhs[0] = sf_c12_QUARC_Prog_Rover_get_testpoint_info();
        break;
      }

     case 13:
      {
        extern mxArray *sf_c13_QUARC_Prog_Rover_get_testpoint_info(void);
        plhs[0] = sf_c13_QUARC_Prog_Rover_get_testpoint_info();
        break;
      }

     case 15:
      {
        extern mxArray *sf_c15_QUARC_Prog_Rover_get_testpoint_info(void);
        plhs[0] = sf_c15_QUARC_Prog_Rover_get_testpoint_info();
        break;
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }

    return 1;
  }

  return 0;

#else

  return 0;

#endif

}

unsigned int sf_QUARC_Prog_Rover_process_check_sum_call( int nlhs, mxArray *
  plhs[], int nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[20];
  if (nrhs<1 || !mxIsChar(prhs[0]) )
    return 0;

  /* Possible call to get the checksum */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"sf_get_check_sum"))
    return 0;
  plhs[0] = mxCreateDoubleMatrix( 1,4,mxREAL);
  if (nrhs>1 && mxIsChar(prhs[1])) {
    mxGetString(prhs[1], commandName,sizeof(commandName)/sizeof(char));
    commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
    if (!strcmp(commandName,"machine")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(24720114U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3046594254U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(4285646935U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3539785500U);
    } else if (!strcmp(commandName,"exportedFcn")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(0U);
    } else if (!strcmp(commandName,"makefile")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3479359287U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2864699186U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2931264985U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3910966921U);
    } else if (nrhs==3 && !strcmp(commandName,"chart")) {
      unsigned int chartFileNumber;
      chartFileNumber = (unsigned int)mxGetScalar(prhs[2]);
      switch (chartFileNumber) {
       case 1:
        {
          extern void sf_c1_QUARC_Prog_Rover_get_check_sum(mxArray *plhs[]);
          sf_c1_QUARC_Prog_Rover_get_check_sum(plhs);
          break;
        }

       case 2:
        {
          extern void sf_c2_QUARC_Prog_Rover_get_check_sum(mxArray *plhs[]);
          sf_c2_QUARC_Prog_Rover_get_check_sum(plhs);
          break;
        }

       case 5:
        {
          extern void sf_c5_QUARC_Prog_Rover_get_check_sum(mxArray *plhs[]);
          sf_c5_QUARC_Prog_Rover_get_check_sum(plhs);
          break;
        }

       case 6:
        {
          extern void sf_c6_QUARC_Prog_Rover_get_check_sum(mxArray *plhs[]);
          sf_c6_QUARC_Prog_Rover_get_check_sum(plhs);
          break;
        }

       case 7:
        {
          extern void sf_c7_QUARC_Prog_Rover_get_check_sum(mxArray *plhs[]);
          sf_c7_QUARC_Prog_Rover_get_check_sum(plhs);
          break;
        }

       case 8:
        {
          extern void sf_c8_QUARC_Prog_Rover_get_check_sum(mxArray *plhs[]);
          sf_c8_QUARC_Prog_Rover_get_check_sum(plhs);
          break;
        }

       case 9:
        {
          extern void sf_c9_QUARC_Prog_Rover_get_check_sum(mxArray *plhs[]);
          sf_c9_QUARC_Prog_Rover_get_check_sum(plhs);
          break;
        }

       case 10:
        {
          extern void sf_c10_QUARC_Prog_Rover_get_check_sum(mxArray *plhs[]);
          sf_c10_QUARC_Prog_Rover_get_check_sum(plhs);
          break;
        }

       case 11:
        {
          extern void sf_c11_QUARC_Prog_Rover_get_check_sum(mxArray *plhs[]);
          sf_c11_QUARC_Prog_Rover_get_check_sum(plhs);
          break;
        }

       case 12:
        {
          extern void sf_c12_QUARC_Prog_Rover_get_check_sum(mxArray *plhs[]);
          sf_c12_QUARC_Prog_Rover_get_check_sum(plhs);
          break;
        }

       case 13:
        {
          extern void sf_c13_QUARC_Prog_Rover_get_check_sum(mxArray *plhs[]);
          sf_c13_QUARC_Prog_Rover_get_check_sum(plhs);
          break;
        }

       case 15:
        {
          extern void sf_c15_QUARC_Prog_Rover_get_check_sum(mxArray *plhs[]);
          sf_c15_QUARC_Prog_Rover_get_check_sum(plhs);
          break;
        }

       default:
        ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(0.0);
      }
    } else if (!strcmp(commandName,"target")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3842585362U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2705523056U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3052964604U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1081919687U);
    } else {
      return 0;
    }
  } else {
    ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1047869317U);
    ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3650184591U);
    ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(989842616U);
    ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3997061765U);
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_QUARC_Prog_Rover_autoinheritance_info( int nlhs, mxArray * plhs[],
  int nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[32];
  char aiChksum[64];
  if (nrhs<3 || !mxIsChar(prhs[0]) )
    return 0;

  /* Possible call to get the autoinheritance_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_autoinheritance_info"))
    return 0;
  mxGetString(prhs[2], aiChksum,sizeof(aiChksum)/sizeof(char));
  aiChksum[(sizeof(aiChksum)/sizeof(char)-1)] = '\0';

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        if (strcmp(aiChksum, "SX4Hv2xdyk0cE1epuN6MxE") == 0) {
          extern mxArray *sf_c1_QUARC_Prog_Rover_get_autoinheritance_info(void);
          plhs[0] = sf_c1_QUARC_Prog_Rover_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 2:
      {
        if (strcmp(aiChksum, "SX4Hv2xdyk0cE1epuN6MxE") == 0) {
          extern mxArray *sf_c2_QUARC_Prog_Rover_get_autoinheritance_info(void);
          plhs[0] = sf_c2_QUARC_Prog_Rover_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 5:
      {
        if (strcmp(aiChksum, "PO3A0kb20TajMPKqBrR9YH") == 0) {
          extern mxArray *sf_c5_QUARC_Prog_Rover_get_autoinheritance_info(void);
          plhs[0] = sf_c5_QUARC_Prog_Rover_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 6:
      {
        if (strcmp(aiChksum, "VGdH57tRujPi3iv08647JC") == 0) {
          extern mxArray *sf_c6_QUARC_Prog_Rover_get_autoinheritance_info(void);
          plhs[0] = sf_c6_QUARC_Prog_Rover_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 7:
      {
        if (strcmp(aiChksum, "wlpUYXzzWo6Ri1NDE9HITB") == 0) {
          extern mxArray *sf_c7_QUARC_Prog_Rover_get_autoinheritance_info(void);
          plhs[0] = sf_c7_QUARC_Prog_Rover_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 8:
      {
        if (strcmp(aiChksum, "hHq8mstHY5iMSOQii3v7hH") == 0) {
          extern mxArray *sf_c8_QUARC_Prog_Rover_get_autoinheritance_info(void);
          plhs[0] = sf_c8_QUARC_Prog_Rover_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 9:
      {
        if (strcmp(aiChksum, "oI5aTOtQRjsmZjaVKwjEMH") == 0) {
          extern mxArray *sf_c9_QUARC_Prog_Rover_get_autoinheritance_info(void);
          plhs[0] = sf_c9_QUARC_Prog_Rover_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 10:
      {
        if (strcmp(aiChksum, "PO3A0kb20TajMPKqBrR9YH") == 0) {
          extern mxArray *sf_c10_QUARC_Prog_Rover_get_autoinheritance_info(void);
          plhs[0] = sf_c10_QUARC_Prog_Rover_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 11:
      {
        if (strcmp(aiChksum, "SX4Hv2xdyk0cE1epuN6MxE") == 0) {
          extern mxArray *sf_c11_QUARC_Prog_Rover_get_autoinheritance_info(void);
          plhs[0] = sf_c11_QUARC_Prog_Rover_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 12:
      {
        if (strcmp(aiChksum, "wlpUYXzzWo6Ri1NDE9HITB") == 0) {
          extern mxArray *sf_c12_QUARC_Prog_Rover_get_autoinheritance_info(void);
          plhs[0] = sf_c12_QUARC_Prog_Rover_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 13:
      {
        if (strcmp(aiChksum, "PO3A0kb20TajMPKqBrR9YH") == 0) {
          extern mxArray *sf_c13_QUARC_Prog_Rover_get_autoinheritance_info(void);
          plhs[0] = sf_c13_QUARC_Prog_Rover_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     case 15:
      {
        if (strcmp(aiChksum, "hHq8mstHY5iMSOQii3v7hH") == 0) {
          extern mxArray *sf_c15_QUARC_Prog_Rover_get_autoinheritance_info(void);
          plhs[0] = sf_c15_QUARC_Prog_Rover_get_autoinheritance_info();
          break;
        }

        plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
        break;
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_QUARC_Prog_Rover_get_eml_resolved_functions_info( int nlhs,
  mxArray * plhs[], int nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[64];
  if (nrhs<2 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the get_eml_resolved_functions_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_eml_resolved_functions_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        extern const mxArray
          *sf_c1_QUARC_Prog_Rover_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c1_QUARC_Prog_Rover_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 2:
      {
        extern const mxArray
          *sf_c2_QUARC_Prog_Rover_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c2_QUARC_Prog_Rover_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 5:
      {
        extern const mxArray
          *sf_c5_QUARC_Prog_Rover_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c5_QUARC_Prog_Rover_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 6:
      {
        extern const mxArray
          *sf_c6_QUARC_Prog_Rover_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c6_QUARC_Prog_Rover_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 7:
      {
        extern const mxArray
          *sf_c7_QUARC_Prog_Rover_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c7_QUARC_Prog_Rover_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 8:
      {
        extern const mxArray
          *sf_c8_QUARC_Prog_Rover_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c8_QUARC_Prog_Rover_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 9:
      {
        extern const mxArray
          *sf_c9_QUARC_Prog_Rover_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c9_QUARC_Prog_Rover_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 10:
      {
        extern const mxArray
          *sf_c10_QUARC_Prog_Rover_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c10_QUARC_Prog_Rover_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 11:
      {
        extern const mxArray
          *sf_c11_QUARC_Prog_Rover_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c11_QUARC_Prog_Rover_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 12:
      {
        extern const mxArray
          *sf_c12_QUARC_Prog_Rover_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c12_QUARC_Prog_Rover_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 13:
      {
        extern const mxArray
          *sf_c13_QUARC_Prog_Rover_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c13_QUARC_Prog_Rover_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     case 15:
      {
        extern const mxArray
          *sf_c15_QUARC_Prog_Rover_get_eml_resolved_functions_info(void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c15_QUARC_Prog_Rover_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;

#else

  return 0;

#endif

}

void QUARC_Prog_Rover_debug_initialize(void)
{
  _QUARC_Prog_RoverMachineNumber_ = sf_debug_initialize_machine(
    "QUARC_Prog_Rover","sfun",0,12,0,0,0);
  sf_debug_set_machine_event_thresholds(_QUARC_Prog_RoverMachineNumber_,0,0);
  sf_debug_set_machine_data_thresholds(_QUARC_Prog_RoverMachineNumber_,0);
}

void QUARC_Prog_Rover_register_exported_symbols(SimStruct* S)
{
}

static mxArray* sRtwOptimizationInfoStruct= NULL;
mxArray* load_QUARC_Prog_Rover_optimization_info(void)
{
  if (sRtwOptimizationInfoStruct==NULL) {
    sRtwOptimizationInfoStruct = sf_load_rtw_optimization_info(
      "QUARC_Prog_Rover", "QUARC_Prog_Rover");
    mexMakeArrayPersistent(sRtwOptimizationInfoStruct);
  }

  return(sRtwOptimizationInfoStruct);
}

void unload_QUARC_Prog_Rover_optimization_info(void)
{
  if (sRtwOptimizationInfoStruct!=NULL) {
    mxDestroyArray(sRtwOptimizationInfoStruct);
    sRtwOptimizationInfoStruct = NULL;
  }
}
