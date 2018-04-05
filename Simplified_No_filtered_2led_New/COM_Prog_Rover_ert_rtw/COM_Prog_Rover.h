/*
 * File: COM_Prog_Rover.h
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

#ifndef RTW_HEADER_COM_Prog_Rover_h_
#define RTW_HEADER_COM_Prog_Rover_h_
#ifndef COM_Prog_Rover_COMMON_INCLUDES_
# define COM_Prog_Rover_COMMON_INCLUDES_
#include <math.h>
#include <stddef.h>
#include <string.h>
#include "rtwtypes.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"
#include "rtGetNaN.h"
#include "rt_defines.h"
#endif                                 /* COM_Prog_Rover_COMMON_INCLUDES_ */

#include "COM_Prog_Rover_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block signals for system '<S2>/Calcu de position2' */
typedef struct {
  real32_T X_ref[2];                   /* '<S2>/Calcu de position2' */
} rtB_Calcudeposition2_COM_Prog_R;

/* Block signals (auto storage) */
typedef struct {
  real32_T RateTransition3[3];         /* '<S2>/Rate Transition3' */
  real32_T RateTransition1[4];         /* '<S2>/Rate Transition1' */
  real32_T RateTransition20[4];        /* '<S2>/Rate Transition20' */
  real32_T RateTransition27[4];        /* '<S2>/Rate Transition27' */
  real32_T RateTransition29[4];        /* '<S2>/Rate Transition29' */
  rtB_Calcudeposition2_COM_Prog_R sf_CalculposLED1;/* '<S2>/Calcul pos LED1' */
  rtB_Calcudeposition2_COM_Prog_R sf_Calcudeposition3;/* '<S2>/Calcu de position3' */
  rtB_Calcudeposition2_COM_Prog_R sf_Calcudeposition2;/* '<S2>/Calcu de position2' */
} BlockIO_COM_Prog_Rover;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real32_T RateTransition3_Buffer0[3]; /* '<S2>/Rate Transition3' */
  real32_T RateTransition1_Buffer0[4]; /* '<S2>/Rate Transition1' */
  real32_T RateTransition20_Buffer0[4];/* '<S2>/Rate Transition20' */
  real32_T RateTransition27_Buffer0[4];/* '<S2>/Rate Transition27' */
  real32_T RateTransition29_Buffer0[4];/* '<S2>/Rate Transition29' */
  real32_T RateTransition7_Buffer0[13];/* '<S2>/Rate Transition7' */
  real32_T RateTransition9_Buffer0[3]; /* '<S2>/Rate Transition9' */
  real32_T RateTransition6_Buffer0[3]; /* '<S2>/Rate Transition6' */
  int8_T RateTransition7_semaphoreTaken;/* '<S2>/Rate Transition7' */
  int8_T RateTransition9_semaphoreTaken;/* '<S2>/Rate Transition9' */
  int8_T RateTransition6_semaphoreTaken;/* '<S2>/Rate Transition6' */
} D_Work_COM_Prog_Rover;

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real32_T In_from_UDP2[26];           /* '<Root>/In_from_UDP2' */
  uint8_T In_from_Serial2[12];         /* '<Root>/In_from_Serial2' */
} ExternalInputs_COM_Prog_Rover;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real32_T Out_to_UDP1[20];            /* '<Root>/Out_to_UDP1' */
  uint16_T Out_to_Serial1;             /* '<Root>/Out_to_Serial1' */
} ExternalOutputs_COM_Prog_Rover;

/* Parameters (auto storage) */
struct Parameters_COM_Prog_Rover_ {
  real_T Constant_Value;               /* Expression: 2^13
                                        * Referenced by: '<S9>/Constant'
                                        */
  real_T Constant_Value_c;             /* Expression: 2^13
                                        * Referenced by: '<S10>/Constant'
                                        */
  real_T Constant_Value_j;             /* Expression: 2^13
                                        * Referenced by: '<S11>/Constant'
                                        */
  real_T Constant_Value_jv;            /* Expression: 2^13
                                        * Referenced by: '<S12>/Constant'
                                        */
  real_T Constant_Value_i;             /* Expression: 2^13
                                        * Referenced by: '<S13>/Constant'
                                        */
  real_T Constant_Value_b;             /* Expression: 2^13
                                        * Referenced by: '<S14>/Constant'
                                        */
  real32_T RateTransition3_X0;         /* Computed Parameter: RateTransition3_X0
                                        * Referenced by: '<S2>/Rate Transition3'
                                        */
  real32_T RateTransition1_X0;         /* Computed Parameter: RateTransition1_X0
                                        * Referenced by: '<S2>/Rate Transition1'
                                        */
  real32_T RateTransition20_X0;        /* Computed Parameter: RateTransition20_X0
                                        * Referenced by: '<S2>/Rate Transition20'
                                        */
  real32_T RateTransition27_X0;        /* Computed Parameter: RateTransition27_X0
                                        * Referenced by: '<S2>/Rate Transition27'
                                        */
  real32_T RateTransition29_X0;        /* Computed Parameter: RateTransition29_X0
                                        * Referenced by: '<S2>/Rate Transition29'
                                        */
  real32_T Constant_Value_ii;          /* Computed Parameter: Constant_Value_ii
                                        * Referenced by: '<S2>/Constant'
                                        */
  int16_T ShiftArithmetic_Power2Exponent;/* Computed Parameter: ShiftArithmetic_Power2Exponent
                                          * Referenced by: '<S9>/Shift Arithmetic'
                                          */
  int16_T ShiftArithmetic1_Power2Exponent;/* Computed Parameter: ShiftArithmetic1_Power2Exponent
                                           * Referenced by: '<S9>/Shift Arithmetic1'
                                           */
  int16_T ShiftArithmetic_Power2Exponen_g;/* Computed Parameter: ShiftArithmetic_Power2Exponen_g
                                           * Referenced by: '<S10>/Shift Arithmetic'
                                           */
  int16_T ShiftArithmetic1_Power2Expone_g;/* Computed Parameter: ShiftArithmetic1_Power2Expone_g
                                           * Referenced by: '<S10>/Shift Arithmetic1'
                                           */
  int16_T ShiftArithmetic_Power2Exponen_f;/* Computed Parameter: ShiftArithmetic_Power2Exponen_f
                                           * Referenced by: '<S11>/Shift Arithmetic'
                                           */
  int16_T ShiftArithmetic1_Power2Expone_d;/* Computed Parameter: ShiftArithmetic1_Power2Expone_d
                                           * Referenced by: '<S11>/Shift Arithmetic1'
                                           */
  int16_T ShiftArithmetic_Power2Exponen_h;/* Computed Parameter: ShiftArithmetic_Power2Exponen_h
                                           * Referenced by: '<S12>/Shift Arithmetic'
                                           */
  int16_T ShiftArithmetic1_Power2Expone_f;/* Computed Parameter: ShiftArithmetic1_Power2Expone_f
                                           * Referenced by: '<S12>/Shift Arithmetic1'
                                           */
  int16_T ShiftArithmetic_Power2Exponen_e;/* Computed Parameter: ShiftArithmetic_Power2Exponen_e
                                           * Referenced by: '<S13>/Shift Arithmetic'
                                           */
  int16_T ShiftArithmetic1_Power2Expon_gr;/* Computed Parameter: ShiftArithmetic1_Power2Expon_gr
                                           * Referenced by: '<S13>/Shift Arithmetic1'
                                           */
  int16_T ShiftArithmetic_Power2Expone_ho;/* Computed Parameter: ShiftArithmetic_Power2Expone_ho
                                           * Referenced by: '<S14>/Shift Arithmetic'
                                           */
  int16_T ShiftArithmetic1_Power2Expone_j;/* Computed Parameter: ShiftArithmetic1_Power2Expone_j
                                           * Referenced by: '<S14>/Shift Arithmetic1'
                                           */
  uint16_T Constant1_Value;            /* Computed Parameter: Constant1_Value
                                        * Referenced by: '<S2>/Constant1'
                                        */
};

/* Real-time Model Data Structure */
struct RT_MODEL_COM_Prog_Rover {
  const char_T * volatile errorStatus;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    struct {
      uint8_T TID0_1;
    } RateInteraction;
  } Timing;
};

/* Block parameters (auto storage) */
extern Parameters_COM_Prog_Rover COM_Prog_Rover_P;

/* Block signals (auto storage) */
extern BlockIO_COM_Prog_Rover COM_Prog_Rover_B;

/* Block states (auto storage) */
extern D_Work_COM_Prog_Rover COM_Prog_Rover_DWork;

/* External inputs (root inport signals with auto storage) */
extern ExternalInputs_COM_Prog_Rover COM_Prog_Rover_U;

/* External outputs (root outports fed by signals with auto storage) */
extern ExternalOutputs_COM_Prog_Rover COM_Prog_Rover_Y;

/* Model entry point functions */
extern void COM_Prog_Rover_initialize(void);
extern void COM_Prog_Rover_step0(void);
extern void COM_Prog_Rover_step1(void);
extern void COM_Prog_Rover_terminate(void);

/* Real-time Model object */
extern struct RT_MODEL_COM_Prog_Rover *const COM_Prog_Rover_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'COM_Prog_Rover'
 * '<S1>'   : 'COM_Prog_Rover/DisplaySampleTimeColors'
 * '<S2>'   : 'COM_Prog_Rover/GUMSTIX'
 * '<S3>'   : 'COM_Prog_Rover/GUMSTIX/Calcu de position2'
 * '<S4>'   : 'COM_Prog_Rover/GUMSTIX/Calcu de position3'
 * '<S5>'   : 'COM_Prog_Rover/GUMSTIX/Calcul pos LED1'
 * '<S6>'   : 'COM_Prog_Rover/GUMSTIX/Calcul pos LED2'
 * '<S7>'   : 'COM_Prog_Rover/GUMSTIX/Decode1'
 * '<S8>'   : 'COM_Prog_Rover/GUMSTIX/Position VIC+Hyper'
 * '<S9>'   : 'COM_Prog_Rover/GUMSTIX/Decode1/Subsystem'
 * '<S10>'  : 'COM_Prog_Rover/GUMSTIX/Decode1/Subsystem1'
 * '<S11>'  : 'COM_Prog_Rover/GUMSTIX/Decode1/Subsystem2'
 * '<S12>'  : 'COM_Prog_Rover/GUMSTIX/Decode1/Subsystem3'
 * '<S13>'  : 'COM_Prog_Rover/GUMSTIX/Decode1/Subsystem4'
 * '<S14>'  : 'COM_Prog_Rover/GUMSTIX/Decode1/Subsystem5'
 */
#endif                                 /* RTW_HEADER_COM_Prog_Rover_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
