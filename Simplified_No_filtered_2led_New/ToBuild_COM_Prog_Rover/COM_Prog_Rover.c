/*
 * File: COM_Prog_Rover.c
 *
 * Code generated for Simulink model 'COM_Prog_Rover'.
 *
 * Model version                  : 1.2014
 * Simulink Coder version         : 8.1 (R2011b) 08-Jul-2011
 * TLC version                    : 8.1 (Jul  9 2011)
 * C/C++ source code generated on : Sun Jun 18 14:52:40 2017
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "COM_Prog_Rover.h"
#include "COM_Prog_Rover_private.h"

/* Block signals (auto storage) */
BlockIO_COM_Prog_Rover COM_Prog_Rover_B;

/* Block states (auto storage) */
D_Work_COM_Prog_Rover COM_Prog_Rover_DWork;

/* External inputs (root inport signals with auto storage) */
ExternalInputs_COM_Prog_Rover COM_Prog_Rover_U;

/* External outputs (root outports fed by signals with auto storage) */
ExternalOutputs_COM_Prog_Rover COM_Prog_Rover_Y;

/* Real-time model */
RT_MODEL_COM_Prog_Rover COM_Prog_Rover_M_;
RT_MODEL_COM_Prog_Rover *const COM_Prog_Rover_M = &COM_Prog_Rover_M_;
real32_T rt_powf_snf(real32_T u0, real32_T u1)
{
  real32_T y;
  real32_T tmp;
  real32_T tmp_0;
  if (rtIsNaNF(u0) || rtIsNaNF(u1)) {
    y = (rtNaNF);
  } else {
    tmp = (real32_T)fabs(u0);
    tmp_0 = (real32_T)fabs(u1);
    if (rtIsInfF(u1)) {
      if (tmp == 1.0F) {
        y = (rtNaNF);
      } else if (tmp > 1.0F) {
        if (u1 > 0.0F) {
          y = (rtInfF);
        } else {
          y = 0.0F;
        }
      } else if (u1 > 0.0F) {
        y = 0.0F;
      } else {
        y = (rtInfF);
      }
    } else if (tmp_0 == 0.0F) {
      y = 1.0F;
    } else if (tmp_0 == 1.0F) {
      if (u1 > 0.0F) {
        y = u0;
      } else {
        y = 1.0F / u0;
      }
    } else if (u1 == 2.0F) {
      y = u0 * u0;
    } else if ((u1 == 0.5F) && (u0 >= 0.0F)) {
      y = (real32_T)sqrt(u0);
    } else if ((u0 < 0.0F) && (u1 > (real32_T)floor(u1))) {
      y = (rtNaNF);
    } else {
      y = (real32_T)pow(u0, u1);
    }
  }

  return y;
}

/*
 * Output and update for atomic system:
 *    '<S2>/Calcu de position2'
 *    '<S2>/Calcu de position3'
 *    '<S2>/Calcul pos LED1'
 */
void COM_Prog_R_Calcudeposition2(real32_T rtu_ph1, real32_T rtu_ph3, real32_T
  rtu_ph2, const real32_T rtu_Parm[10], real32_T rtu_H,
  rtB_Calcudeposition2_COM_Prog_R *localB)
{
  real32_T tr;
  real32_T tr_0;

  /* MATLAB Function 'GUMSTIX/Calcu de position2': '<S3>:1' */
  /* '<S3>:1:2' */
  /* '<S3>:1:3' */
  tr = (rtu_ph1 - rtu_ph2) / (rtu_ph1 + rtu_ph2);

  /* '<S3>:1:4' */
  tr_0 = ((rtu_ph1 + rtu_ph2) / 2.0F - rtu_ph3) / ((rtu_ph1 + rtu_ph2) / 2.0F +
    rtu_ph3);

  /* x = H*tan(trd*(a1*tr1+b1)); */
  /* y = H*tan(trd*(a2*tr2+b2)); */
  /*  x = H.*tan(trd.*(Parm(1).*tr1 + Parm(2).*tr1.^2+ Parm(3).*tr2+Parm(4) )); */
  /*  y = H.*tan(trd.*(Parm(5).*tr2 + Parm(6).*tr2.^2+Parm(7).*tr1 + Parm(8))); */
  /* '<S3>:1:9' */
  /* '<S3>:1:10' */
  /* '<S3>:1:11' */
  localB->X_ref[0] = (real32_T)tan(((((rtu_Parm[0] * tr_0 + rtu_Parm[1] *
    rt_powf_snf(tr_0, 2.0F)) + rtu_Parm[2] * tr) + rtu_Parm[3] * rt_powf_snf(tr,
    2.0F)) + rtu_Parm[4]) * 0.0174532924F) * rtu_H;
  localB->X_ref[1] = (real32_T)tan(((((rtu_Parm[5] * tr + rtu_Parm[6] *
    rt_powf_snf(tr, 2.0F)) + rtu_Parm[7] * tr_0) + rtu_Parm[8] * rt_powf_snf
    (tr_0, 2.0F)) + rtu_Parm[9]) * 0.0174532924F) * rtu_H;
}

/* Model step function for TID0 */
void COM_Prog_Rover_step0(void)        /* Sample time: [0.002s, 0.0s] */
{
  int32_T i;

  /* Update the flag to indicate when data transfers from
   *  Sample time: [0.002s, 0.0s] to Sample time: [0.01s, 0.0s]  */
  (COM_Prog_Rover_M->Timing.RateInteraction.TID0_1)++;
  if ((COM_Prog_Rover_M->Timing.RateInteraction.TID0_1) > 4) {
    COM_Prog_Rover_M->Timing.RateInteraction.TID0_1 = 0;
  }

  /* RateTransition: '<S2>/Rate Transition3' */
  if ((COM_Prog_Rover_M->Timing.RateInteraction.TID0_1 == 1)) {
    COM_Prog_Rover_B.RateTransition3[0] =
      COM_Prog_Rover_DWork.RateTransition3_Buffer0[0];
    COM_Prog_Rover_B.RateTransition3[1] =
      COM_Prog_Rover_DWork.RateTransition3_Buffer0[1];
    COM_Prog_Rover_B.RateTransition3[2] =
      COM_Prog_Rover_DWork.RateTransition3_Buffer0[2];

    /* RateTransition: '<S2>/Rate Transition1' */
    COM_Prog_Rover_B.RateTransition1[0] =
      COM_Prog_Rover_DWork.RateTransition1_Buffer0[0];
    COM_Prog_Rover_B.RateTransition1[1] =
      COM_Prog_Rover_DWork.RateTransition1_Buffer0[1];
    COM_Prog_Rover_B.RateTransition1[2] =
      COM_Prog_Rover_DWork.RateTransition1_Buffer0[2];
    COM_Prog_Rover_B.RateTransition1[3] =
      COM_Prog_Rover_DWork.RateTransition1_Buffer0[3];

    /* RateTransition: '<S2>/Rate Transition20' */
    COM_Prog_Rover_B.RateTransition20[0] =
      COM_Prog_Rover_DWork.RateTransition20_Buffer0[0];
    COM_Prog_Rover_B.RateTransition20[1] =
      COM_Prog_Rover_DWork.RateTransition20_Buffer0[1];
    COM_Prog_Rover_B.RateTransition20[2] =
      COM_Prog_Rover_DWork.RateTransition20_Buffer0[2];
    COM_Prog_Rover_B.RateTransition20[3] =
      COM_Prog_Rover_DWork.RateTransition20_Buffer0[3];

    /* RateTransition: '<S2>/Rate Transition27' */
    COM_Prog_Rover_B.RateTransition27[0] =
      COM_Prog_Rover_DWork.RateTransition27_Buffer0[0];
    COM_Prog_Rover_B.RateTransition27[1] =
      COM_Prog_Rover_DWork.RateTransition27_Buffer0[1];
    COM_Prog_Rover_B.RateTransition27[2] =
      COM_Prog_Rover_DWork.RateTransition27_Buffer0[2];
    COM_Prog_Rover_B.RateTransition27[3] =
      COM_Prog_Rover_DWork.RateTransition27_Buffer0[3];

    /* RateTransition: '<S2>/Rate Transition29' */
    COM_Prog_Rover_B.RateTransition29[0] =
      COM_Prog_Rover_DWork.RateTransition29_Buffer0[0];
    COM_Prog_Rover_B.RateTransition29[1] =
      COM_Prog_Rover_DWork.RateTransition29_Buffer0[1];
    COM_Prog_Rover_B.RateTransition29[2] =
      COM_Prog_Rover_DWork.RateTransition29_Buffer0[2];
    COM_Prog_Rover_B.RateTransition29[3] =
      COM_Prog_Rover_DWork.RateTransition29_Buffer0[3];
  }

  /* End of RateTransition: '<S2>/Rate Transition3' */

  /* Outport: '<Root>/Out_to_UDP1' incorporates:
   *  Inport: '<Root>/In_from_UDP2'
   */
  COM_Prog_Rover_Y.Out_to_UDP1[0] = COM_Prog_Rover_U.In_from_UDP2[0];
  COM_Prog_Rover_Y.Out_to_UDP1[1] = COM_Prog_Rover_B.RateTransition3[0];
  COM_Prog_Rover_Y.Out_to_UDP1[2] = COM_Prog_Rover_B.RateTransition3[1];
  COM_Prog_Rover_Y.Out_to_UDP1[3] = COM_Prog_Rover_B.RateTransition3[2];
  COM_Prog_Rover_Y.Out_to_UDP1[4] = COM_Prog_Rover_B.RateTransition1[0];
  COM_Prog_Rover_Y.Out_to_UDP1[5] = COM_Prog_Rover_B.RateTransition1[1];
  COM_Prog_Rover_Y.Out_to_UDP1[6] = COM_Prog_Rover_B.RateTransition1[2];
  COM_Prog_Rover_Y.Out_to_UDP1[7] = COM_Prog_Rover_B.RateTransition1[3];
  COM_Prog_Rover_Y.Out_to_UDP1[8] = COM_Prog_Rover_B.RateTransition20[0];
  COM_Prog_Rover_Y.Out_to_UDP1[9] = COM_Prog_Rover_B.RateTransition20[1];
  COM_Prog_Rover_Y.Out_to_UDP1[10] = COM_Prog_Rover_B.RateTransition20[2];
  COM_Prog_Rover_Y.Out_to_UDP1[11] = COM_Prog_Rover_B.RateTransition20[3];
  COM_Prog_Rover_Y.Out_to_UDP1[12] = COM_Prog_Rover_B.RateTransition27[0];
  COM_Prog_Rover_Y.Out_to_UDP1[13] = COM_Prog_Rover_B.RateTransition27[1];
  COM_Prog_Rover_Y.Out_to_UDP1[14] = COM_Prog_Rover_B.RateTransition27[2];
  COM_Prog_Rover_Y.Out_to_UDP1[15] = COM_Prog_Rover_B.RateTransition27[3];
  COM_Prog_Rover_Y.Out_to_UDP1[16] = COM_Prog_Rover_B.RateTransition29[0];
  COM_Prog_Rover_Y.Out_to_UDP1[17] = COM_Prog_Rover_B.RateTransition29[1];
  COM_Prog_Rover_Y.Out_to_UDP1[18] = COM_Prog_Rover_B.RateTransition29[2];
  COM_Prog_Rover_Y.Out_to_UDP1[19] = COM_Prog_Rover_B.RateTransition29[3];

  /* RateTransition: '<S2>/Rate Transition7' incorporates:
   *  Inport: '<Root>/In_from_UDP2'
   */
  if (!(COM_Prog_Rover_DWork.RateTransition7_semaphoreTaken != 0)) {
    for (i = 0; i < 13; i++) {
      COM_Prog_Rover_DWork.RateTransition7_Buffer0[i] =
        COM_Prog_Rover_U.In_from_UDP2[i + 12];
    }
  }

  /* End of RateTransition: '<S2>/Rate Transition7' */

  /* RateTransition: '<S2>/Rate Transition9' incorporates:
   *  Inport: '<Root>/In_from_UDP2'
   */
  if (!(COM_Prog_Rover_DWork.RateTransition9_semaphoreTaken != 0)) {
    COM_Prog_Rover_DWork.RateTransition9_Buffer0[0] =
      COM_Prog_Rover_U.In_from_UDP2[9];
    COM_Prog_Rover_DWork.RateTransition9_Buffer0[1] =
      COM_Prog_Rover_U.In_from_UDP2[10];
    COM_Prog_Rover_DWork.RateTransition9_Buffer0[2] =
      COM_Prog_Rover_U.In_from_UDP2[11];
  }

  /* End of RateTransition: '<S2>/Rate Transition9' */

  /* RateTransition: '<S2>/Rate Transition6' incorporates:
   *  Inport: '<Root>/In_from_UDP2'
   */
  if (!(COM_Prog_Rover_DWork.RateTransition6_semaphoreTaken != 0)) {
    COM_Prog_Rover_DWork.RateTransition6_Buffer0[0] =
      COM_Prog_Rover_U.In_from_UDP2[2];
    COM_Prog_Rover_DWork.RateTransition6_Buffer0[1] =
      COM_Prog_Rover_U.In_from_UDP2[3];
    COM_Prog_Rover_DWork.RateTransition6_Buffer0[2] =
      COM_Prog_Rover_U.In_from_UDP2[4];
  }

  /* End of RateTransition: '<S2>/Rate Transition6' */
}

/* Model step function for TID1 */
void COM_Prog_Rover_step1(void)        /* Sample time: [0.01s, 0.0s] */
{
  /* local block i/o variables */
  real32_T rtb_DataTypeConversion1[6];
  real32_T rtb_RateTransition7[13];
  real32_T tr;
  real32_T tr_0;
  uint8_T rtb_DataTypeConversion[12];
  real32_T rtb_RateTransition6[3];
  int32_T i;
  real32_T rtb_X_ref_idx;

  /* Outport: '<Root>/Out_to_Serial1' incorporates:
   *  Constant: '<S2>/Constant1'
   */
  COM_Prog_Rover_Y.Out_to_Serial1 = COM_Prog_Rover_P.Constant1_Value;

  /* DataTypeConversion: '<S7>/Data Type Conversion' incorporates:
   *  Inport: '<Root>/In_from_Serial2'
   */
  for (i = 0; i < 12; i++) {
    rtb_DataTypeConversion[i] = COM_Prog_Rover_U.In_from_Serial2[i];
  }

  /* End of DataTypeConversion: '<S7>/Data Type Conversion' */

  /* DataTypeConversion: '<S7>/Data Type Conversion1' incorporates:
   *  ArithShift: '<S10>/Shift Arithmetic'
   *  ArithShift: '<S10>/Shift Arithmetic1'
   *  ArithShift: '<S11>/Shift Arithmetic'
   *  ArithShift: '<S11>/Shift Arithmetic1'
   *  ArithShift: '<S12>/Shift Arithmetic'
   *  ArithShift: '<S12>/Shift Arithmetic1'
   *  ArithShift: '<S13>/Shift Arithmetic'
   *  ArithShift: '<S13>/Shift Arithmetic1'
   *  ArithShift: '<S14>/Shift Arithmetic'
   *  ArithShift: '<S14>/Shift Arithmetic1'
   *  ArithShift: '<S9>/Shift Arithmetic'
   *  ArithShift: '<S9>/Shift Arithmetic1'
   *  Constant: '<S10>/Constant'
   *  Constant: '<S11>/Constant'
   *  Constant: '<S12>/Constant'
   *  Constant: '<S13>/Constant'
   *  Constant: '<S14>/Constant'
   *  Constant: '<S9>/Constant'
   *  Sum: '<S10>/Add'
   *  Sum: '<S10>/Add1'
   *  Sum: '<S11>/Add'
   *  Sum: '<S11>/Add1'
   *  Sum: '<S12>/Add'
   *  Sum: '<S12>/Add1'
   *  Sum: '<S13>/Add'
   *  Sum: '<S13>/Add1'
   *  Sum: '<S14>/Add'
   *  Sum: '<S14>/Add1'
   *  Sum: '<S9>/Add'
   *  Sum: '<S9>/Add1'
   */
  rtb_DataTypeConversion1[0] = (real32_T)((real_T)((uint32_T)
    (rtb_DataTypeConversion[1] << 7) + (uint32_T)rtb_DataTypeConversion[0]) -
    COM_Prog_Rover_P.Constant_Value);
  rtb_DataTypeConversion1[1] = (real32_T)((real_T)((uint32_T)
    (rtb_DataTypeConversion[3] << 7) + (uint32_T)rtb_DataTypeConversion[2]) -
    COM_Prog_Rover_P.Constant_Value_c);
  rtb_DataTypeConversion1[2] = (real32_T)((real_T)((uint32_T)
    (rtb_DataTypeConversion[5] << 7) + (uint32_T)rtb_DataTypeConversion[4]) -
    COM_Prog_Rover_P.Constant_Value_j);
  rtb_DataTypeConversion1[3] = (real32_T)((real_T)((uint32_T)
    (rtb_DataTypeConversion[7] << 7) + (uint32_T)rtb_DataTypeConversion[6]) -
    COM_Prog_Rover_P.Constant_Value_jv);
  rtb_DataTypeConversion1[4] = (real32_T)((real_T)((uint32_T)
    (rtb_DataTypeConversion[9] << 7) + (uint32_T)rtb_DataTypeConversion[8]) -
    COM_Prog_Rover_P.Constant_Value_i);
  rtb_DataTypeConversion1[5] = (real32_T)((real_T)((uint32_T)
    (rtb_DataTypeConversion[11] << 7) + (uint32_T)rtb_DataTypeConversion[10]) -
    COM_Prog_Rover_P.Constant_Value_b);

  /* RateTransition: '<S2>/Rate Transition7' */
  COM_Prog_Rover_DWork.RateTransition7_semaphoreTaken = 1;
  for (i = 0; i < 13; i++) {
    rtb_RateTransition7[i] = COM_Prog_Rover_DWork.RateTransition7_Buffer0[i];
  }

  COM_Prog_Rover_DWork.RateTransition7_semaphoreTaken = 0;

  /* End of RateTransition: '<S2>/Rate Transition7' */

  /* MATLAB Function: '<S2>/Calcu de position2' */
  COM_Prog_R_Calcudeposition2(rtb_DataTypeConversion1[0],
    rtb_DataTypeConversion1[1], rtb_DataTypeConversion1[2], rtb_RateTransition7,
    rtb_RateTransition7[12], &COM_Prog_Rover_B.sf_Calcudeposition2);

  /* MATLAB Function: '<S2>/Calcu de position3' */
  COM_Prog_R_Calcudeposition2(rtb_DataTypeConversion1[3],
    rtb_DataTypeConversion1[4], rtb_DataTypeConversion1[5], rtb_RateTransition7,
    rtb_RateTransition7[12], &COM_Prog_Rover_B.sf_Calcudeposition3);

  /* MATLAB Function: '<S2>/Calcul pos LED1' */
  COM_Prog_R_Calcudeposition2(rtb_DataTypeConversion1[0],
    rtb_DataTypeConversion1[1], rtb_DataTypeConversion1[2], rtb_RateTransition7,
    rtb_RateTransition7[12], &COM_Prog_Rover_B.sf_CalculposLED1);

  /* MATLAB Function: '<S2>/Calcul pos LED2' */
  /* MATLAB Function 'GUMSTIX/Calcul pos LED2': '<S6>:1' */
  /* xl,yl,H qre position of LED1 */
  /* '<S6>:1:2' */
  /* '<S6>:1:3' */
  tr = (rtb_DataTypeConversion1[3] - rtb_DataTypeConversion1[5]) /
    (rtb_DataTypeConversion1[3] + rtb_DataTypeConversion1[5]);

  /* '<S6>:1:4' */
  tr_0 = ((rtb_DataTypeConversion1[3] + rtb_DataTypeConversion1[5]) / 2.0F -
          rtb_DataTypeConversion1[4]) / ((rtb_DataTypeConversion1[3] +
    rtb_DataTypeConversion1[5]) / 2.0F + rtb_DataTypeConversion1[4]);

  /* x = H*tan(trd*(a1*tr1+b1)); */
  /* y = H*tan(trd*(a2*tr2+b2)); */
  /*  x = H.*tan(trd.*(Parm(1).*tr1 + Parm(2).*tr1.^2+ Parm(3).*tr2+Parm(4) )); */
  /*  y = H.*tan(trd.*(Parm(5).*tr2 + Parm(6).*tr2.^2+Parm(7).*tr1 + Parm(8))); */
  /* '<S6>:1:9' */
  /* '<S6>:1:10' */
  /* '<S6>:1:11' */
  rtb_X_ref_idx = (real32_T)tan(((((rtb_RateTransition7[0] * tr_0 +
    rtb_RateTransition7[1] * rt_powf_snf(tr_0, 2.0F)) + rtb_RateTransition7[2] *
    tr) + rtb_RateTransition7[3] * rt_powf_snf(tr, 2.0F)) + rtb_RateTransition7
    [4]) * 0.0174532924F) * rtb_RateTransition7[12];
  tr = (real32_T)tan(((((rtb_RateTransition7[5] * tr + rtb_RateTransition7[6] *
    rt_powf_snf(tr, 2.0F)) + rtb_RateTransition7[7] * tr_0) +
                       rtb_RateTransition7[8] * rt_powf_snf(tr_0, 2.0F)) +
                      rtb_RateTransition7[9]) * 0.0174532924F) *
    rtb_RateTransition7[12];

  /* RateTransition: '<S2>/Rate Transition9' */
  COM_Prog_Rover_DWork.RateTransition9_semaphoreTaken = 1;
  COM_Prog_Rover_DWork.RateTransition9_semaphoreTaken = 0;

  /* RateTransition: '<S2>/Rate Transition6' */
  /* MATLAB Function 'GUMSTIX/Position VIC+Hyper': '<S8>:1' */
  /* '<S8>:1:3' */
  /* '<S8>:1:4' */
  /* '<S8>:1:5' */
  COM_Prog_Rover_DWork.RateTransition6_semaphoreTaken = 1;
  rtb_RateTransition6[0] = COM_Prog_Rover_DWork.RateTransition6_Buffer0[0];
  rtb_RateTransition6[1] = COM_Prog_Rover_DWork.RateTransition6_Buffer0[1];
  rtb_RateTransition6[2] = COM_Prog_Rover_DWork.RateTransition6_Buffer0[2];
  COM_Prog_Rover_DWork.RateTransition6_semaphoreTaken = 0;

  /* Update for RateTransition: '<S2>/Rate Transition3' */
  COM_Prog_Rover_DWork.RateTransition3_Buffer0[0] = rtb_RateTransition6[0];
  COM_Prog_Rover_DWork.RateTransition3_Buffer0[1] = rtb_RateTransition6[1];
  COM_Prog_Rover_DWork.RateTransition3_Buffer0[2] = rtb_RateTransition6[2];

  /* Update for RateTransition: '<S2>/Rate Transition1' incorporates:
   *  Constant: '<S2>/Constant'
   */
  COM_Prog_Rover_DWork.RateTransition1_Buffer0[0] = rtb_DataTypeConversion1[0];
  COM_Prog_Rover_DWork.RateTransition1_Buffer0[1] = rtb_DataTypeConversion1[1];
  COM_Prog_Rover_DWork.RateTransition1_Buffer0[2] = rtb_DataTypeConversion1[2];
  COM_Prog_Rover_DWork.RateTransition1_Buffer0[3] =
    COM_Prog_Rover_P.Constant_Value_ii;

  /* Update for RateTransition: '<S2>/Rate Transition20' incorporates:
   *  Constant: '<S2>/Constant'
   */
  COM_Prog_Rover_DWork.RateTransition20_Buffer0[0] = rtb_DataTypeConversion1[3];
  COM_Prog_Rover_DWork.RateTransition20_Buffer0[1] = rtb_DataTypeConversion1[4];
  COM_Prog_Rover_DWork.RateTransition20_Buffer0[2] = rtb_DataTypeConversion1[5];
  COM_Prog_Rover_DWork.RateTransition20_Buffer0[3] =
    COM_Prog_Rover_P.Constant_Value_ii;

  /* Update for RateTransition: '<S2>/Rate Transition27' */
  COM_Prog_Rover_DWork.RateTransition27_Buffer0[0] = rtb_X_ref_idx;
  COM_Prog_Rover_DWork.RateTransition27_Buffer0[1] = tr;
  COM_Prog_Rover_DWork.RateTransition27_Buffer0[2] =
    COM_Prog_Rover_B.sf_CalculposLED1.X_ref[0];
  COM_Prog_Rover_DWork.RateTransition27_Buffer0[3] =
    COM_Prog_Rover_B.sf_CalculposLED1.X_ref[1];

  /* Update for RateTransition: '<S2>/Rate Transition29' */
  COM_Prog_Rover_DWork.RateTransition29_Buffer0[0] =
    COM_Prog_Rover_B.sf_Calcudeposition3.X_ref[0];
  COM_Prog_Rover_DWork.RateTransition29_Buffer0[1] =
    COM_Prog_Rover_B.sf_Calcudeposition3.X_ref[1];
  COM_Prog_Rover_DWork.RateTransition29_Buffer0[2] =
    COM_Prog_Rover_B.sf_Calcudeposition2.X_ref[0];
  COM_Prog_Rover_DWork.RateTransition29_Buffer0[3] =
    COM_Prog_Rover_B.sf_Calcudeposition2.X_ref[1];
}

/* Model initialize function */
void COM_Prog_Rover_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)COM_Prog_Rover_M, 0,
                sizeof(RT_MODEL_COM_Prog_Rover));

  /* block I/O */
  {
    COM_Prog_Rover_B.RateTransition3[0] = 0.0F;
    COM_Prog_Rover_B.RateTransition3[1] = 0.0F;
    COM_Prog_Rover_B.RateTransition3[2] = 0.0F;
    COM_Prog_Rover_B.RateTransition1[0] = 0.0F;
    COM_Prog_Rover_B.RateTransition1[1] = 0.0F;
    COM_Prog_Rover_B.RateTransition1[2] = 0.0F;
    COM_Prog_Rover_B.RateTransition1[3] = 0.0F;
    COM_Prog_Rover_B.RateTransition20[0] = 0.0F;
    COM_Prog_Rover_B.RateTransition20[1] = 0.0F;
    COM_Prog_Rover_B.RateTransition20[2] = 0.0F;
    COM_Prog_Rover_B.RateTransition20[3] = 0.0F;
    COM_Prog_Rover_B.RateTransition27[0] = 0.0F;
    COM_Prog_Rover_B.RateTransition27[1] = 0.0F;
    COM_Prog_Rover_B.RateTransition27[2] = 0.0F;
    COM_Prog_Rover_B.RateTransition27[3] = 0.0F;
    COM_Prog_Rover_B.RateTransition29[0] = 0.0F;
    COM_Prog_Rover_B.RateTransition29[1] = 0.0F;
    COM_Prog_Rover_B.RateTransition29[2] = 0.0F;
    COM_Prog_Rover_B.RateTransition29[3] = 0.0F;
    COM_Prog_Rover_B.sf_CalculposLED1.X_ref[0] = 0.0F;
    COM_Prog_Rover_B.sf_CalculposLED1.X_ref[1] = 0.0F;
    COM_Prog_Rover_B.sf_Calcudeposition3.X_ref[0] = 0.0F;
    COM_Prog_Rover_B.sf_Calcudeposition3.X_ref[1] = 0.0F;
    COM_Prog_Rover_B.sf_Calcudeposition2.X_ref[0] = 0.0F;
    COM_Prog_Rover_B.sf_Calcudeposition2.X_ref[1] = 0.0F;
  }

  /* states (dwork) */
  (void) memset((void *)&COM_Prog_Rover_DWork, 0,
                sizeof(D_Work_COM_Prog_Rover));
  COM_Prog_Rover_DWork.RateTransition3_Buffer0[0] = 0.0F;
  COM_Prog_Rover_DWork.RateTransition3_Buffer0[1] = 0.0F;
  COM_Prog_Rover_DWork.RateTransition3_Buffer0[2] = 0.0F;
  COM_Prog_Rover_DWork.RateTransition1_Buffer0[0] = 0.0F;
  COM_Prog_Rover_DWork.RateTransition1_Buffer0[1] = 0.0F;
  COM_Prog_Rover_DWork.RateTransition1_Buffer0[2] = 0.0F;
  COM_Prog_Rover_DWork.RateTransition1_Buffer0[3] = 0.0F;
  COM_Prog_Rover_DWork.RateTransition20_Buffer0[0] = 0.0F;
  COM_Prog_Rover_DWork.RateTransition20_Buffer0[1] = 0.0F;
  COM_Prog_Rover_DWork.RateTransition20_Buffer0[2] = 0.0F;
  COM_Prog_Rover_DWork.RateTransition20_Buffer0[3] = 0.0F;
  COM_Prog_Rover_DWork.RateTransition27_Buffer0[0] = 0.0F;
  COM_Prog_Rover_DWork.RateTransition27_Buffer0[1] = 0.0F;
  COM_Prog_Rover_DWork.RateTransition27_Buffer0[2] = 0.0F;
  COM_Prog_Rover_DWork.RateTransition27_Buffer0[3] = 0.0F;
  COM_Prog_Rover_DWork.RateTransition29_Buffer0[0] = 0.0F;
  COM_Prog_Rover_DWork.RateTransition29_Buffer0[1] = 0.0F;
  COM_Prog_Rover_DWork.RateTransition29_Buffer0[2] = 0.0F;
  COM_Prog_Rover_DWork.RateTransition29_Buffer0[3] = 0.0F;

  {
    int_T i;
    for (i = 0; i < 13; i++) {
      COM_Prog_Rover_DWork.RateTransition7_Buffer0[i] = 0.0F;
    }
  }

  COM_Prog_Rover_DWork.RateTransition9_Buffer0[0] = 0.0F;
  COM_Prog_Rover_DWork.RateTransition9_Buffer0[1] = 0.0F;
  COM_Prog_Rover_DWork.RateTransition9_Buffer0[2] = 0.0F;
  COM_Prog_Rover_DWork.RateTransition6_Buffer0[0] = 0.0F;
  COM_Prog_Rover_DWork.RateTransition6_Buffer0[1] = 0.0F;
  COM_Prog_Rover_DWork.RateTransition6_Buffer0[2] = 0.0F;

  /* external inputs */
  (void) memset((void *)&COM_Prog_Rover_U, 0,
                sizeof(ExternalInputs_COM_Prog_Rover));

  {
    int_T i;
    for (i = 0; i < 26; i++) {
      COM_Prog_Rover_U.In_from_UDP2[i] = 0.0F;
    }
  }

  /* external outputs */
  (void) memset((void *)&COM_Prog_Rover_Y, 0,
                sizeof(ExternalOutputs_COM_Prog_Rover));

  {
    int_T i;
    for (i = 0; i < 20; i++) {
      COM_Prog_Rover_Y.Out_to_UDP1[i] = 0.0F;
    }
  }

  /* Start for RateTransition: '<S2>/Rate Transition3' */
  COM_Prog_Rover_B.RateTransition3[0] = COM_Prog_Rover_P.RateTransition3_X0;
  COM_Prog_Rover_B.RateTransition3[1] = COM_Prog_Rover_P.RateTransition3_X0;
  COM_Prog_Rover_B.RateTransition3[2] = COM_Prog_Rover_P.RateTransition3_X0;

  /* Start for RateTransition: '<S2>/Rate Transition1' */
  COM_Prog_Rover_B.RateTransition1[0] = COM_Prog_Rover_P.RateTransition1_X0;
  COM_Prog_Rover_B.RateTransition1[1] = COM_Prog_Rover_P.RateTransition1_X0;
  COM_Prog_Rover_B.RateTransition1[2] = COM_Prog_Rover_P.RateTransition1_X0;
  COM_Prog_Rover_B.RateTransition1[3] = COM_Prog_Rover_P.RateTransition1_X0;

  /* Start for RateTransition: '<S2>/Rate Transition20' */
  COM_Prog_Rover_B.RateTransition20[0] = COM_Prog_Rover_P.RateTransition20_X0;
  COM_Prog_Rover_B.RateTransition20[1] = COM_Prog_Rover_P.RateTransition20_X0;
  COM_Prog_Rover_B.RateTransition20[2] = COM_Prog_Rover_P.RateTransition20_X0;
  COM_Prog_Rover_B.RateTransition20[3] = COM_Prog_Rover_P.RateTransition20_X0;

  /* Start for RateTransition: '<S2>/Rate Transition27' */
  COM_Prog_Rover_B.RateTransition27[0] = COM_Prog_Rover_P.RateTransition27_X0;
  COM_Prog_Rover_B.RateTransition27[1] = COM_Prog_Rover_P.RateTransition27_X0;
  COM_Prog_Rover_B.RateTransition27[2] = COM_Prog_Rover_P.RateTransition27_X0;
  COM_Prog_Rover_B.RateTransition27[3] = COM_Prog_Rover_P.RateTransition27_X0;

  /* Start for RateTransition: '<S2>/Rate Transition29' */
  COM_Prog_Rover_B.RateTransition29[0] = COM_Prog_Rover_P.RateTransition29_X0;
  COM_Prog_Rover_B.RateTransition29[1] = COM_Prog_Rover_P.RateTransition29_X0;
  COM_Prog_Rover_B.RateTransition29[2] = COM_Prog_Rover_P.RateTransition29_X0;
  COM_Prog_Rover_B.RateTransition29[3] = COM_Prog_Rover_P.RateTransition29_X0;

  /* InitializeConditions for RateTransition: '<S2>/Rate Transition3' */
  COM_Prog_Rover_DWork.RateTransition3_Buffer0[0] =
    COM_Prog_Rover_P.RateTransition3_X0;
  COM_Prog_Rover_DWork.RateTransition3_Buffer0[1] =
    COM_Prog_Rover_P.RateTransition3_X0;
  COM_Prog_Rover_DWork.RateTransition3_Buffer0[2] =
    COM_Prog_Rover_P.RateTransition3_X0;

  /* InitializeConditions for RateTransition: '<S2>/Rate Transition1' */
  COM_Prog_Rover_DWork.RateTransition1_Buffer0[0] =
    COM_Prog_Rover_P.RateTransition1_X0;
  COM_Prog_Rover_DWork.RateTransition1_Buffer0[1] =
    COM_Prog_Rover_P.RateTransition1_X0;
  COM_Prog_Rover_DWork.RateTransition1_Buffer0[2] =
    COM_Prog_Rover_P.RateTransition1_X0;
  COM_Prog_Rover_DWork.RateTransition1_Buffer0[3] =
    COM_Prog_Rover_P.RateTransition1_X0;

  /* InitializeConditions for RateTransition: '<S2>/Rate Transition20' */
  COM_Prog_Rover_DWork.RateTransition20_Buffer0[0] =
    COM_Prog_Rover_P.RateTransition20_X0;
  COM_Prog_Rover_DWork.RateTransition20_Buffer0[1] =
    COM_Prog_Rover_P.RateTransition20_X0;
  COM_Prog_Rover_DWork.RateTransition20_Buffer0[2] =
    COM_Prog_Rover_P.RateTransition20_X0;
  COM_Prog_Rover_DWork.RateTransition20_Buffer0[3] =
    COM_Prog_Rover_P.RateTransition20_X0;

  /* InitializeConditions for RateTransition: '<S2>/Rate Transition27' */
  COM_Prog_Rover_DWork.RateTransition27_Buffer0[0] =
    COM_Prog_Rover_P.RateTransition27_X0;
  COM_Prog_Rover_DWork.RateTransition27_Buffer0[1] =
    COM_Prog_Rover_P.RateTransition27_X0;
  COM_Prog_Rover_DWork.RateTransition27_Buffer0[2] =
    COM_Prog_Rover_P.RateTransition27_X0;
  COM_Prog_Rover_DWork.RateTransition27_Buffer0[3] =
    COM_Prog_Rover_P.RateTransition27_X0;

  /* InitializeConditions for RateTransition: '<S2>/Rate Transition29' */
  COM_Prog_Rover_DWork.RateTransition29_Buffer0[0] =
    COM_Prog_Rover_P.RateTransition29_X0;
  COM_Prog_Rover_DWork.RateTransition29_Buffer0[1] =
    COM_Prog_Rover_P.RateTransition29_X0;
  COM_Prog_Rover_DWork.RateTransition29_Buffer0[2] =
    COM_Prog_Rover_P.RateTransition29_X0;
  COM_Prog_Rover_DWork.RateTransition29_Buffer0[3] =
    COM_Prog_Rover_P.RateTransition29_X0;
}

/* Model terminate function */
void COM_Prog_Rover_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
