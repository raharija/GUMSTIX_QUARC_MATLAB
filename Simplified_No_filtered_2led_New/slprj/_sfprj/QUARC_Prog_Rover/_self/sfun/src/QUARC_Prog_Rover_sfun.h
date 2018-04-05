#ifndef __QUARC_Prog_Rover_sfun_h__
#define __QUARC_Prog_Rover_sfun_h__

/* Include files */
#define S_FUNCTION_NAME                sf_sfun
#include "sfc_sf.h"
#include "sfc_mex.h"
#include "rtwtypes.h"
#include "sfcdebug.h"
#define rtInf                          (mxGetInf())
#define rtMinusInf                     (-(mxGetInf()))
#define rtNaN                          (mxGetNaN())
#define rtIsNaN(X)                     ((int)mxIsNaN(X))
#define rtIsInf(X)                     ((int)mxIsInf(X))

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */
extern uint32_T _QUARC_Prog_RoverMachineNumber_;
extern real_T _sfTime_;

/* Variable Definitions */

/* Function Declarations */
extern void QUARC_Prog_Rover_initializer(void);
extern void QUARC_Prog_Rover_terminator(void);

/* Function Definitions */

/* We load infoStruct for rtw_optimation_info on demand in mdlSetWorkWidths and
   free it immediately in mdlStart. Given that this is machine-wide as
   opposed to chart specific, we use NULL check to make sure it gets loaded
   and unloaded once per machine even though the  methods mdlSetWorkWidths/mdlStart
   are chart/instance specific. The following methods abstract this out. */
extern mxArray* load_QUARC_Prog_Rover_optimization_info(void);
extern void unload_QUARC_Prog_Rover_optimization_info(void);

#endif
