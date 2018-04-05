/* Include files */

#include "blascompat32.h"
#include "QUARC_Prog_Rover_sfun.h"
#include "c7_QUARC_Prog_Rover.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "QUARC_Prog_Rover_sfun_debug_macros.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
static const char * c7_debug_family_names[6] = { "nargin", "nargout", "t", "r",
  "T", "X_ref" };

/* Function Declarations */
static void initialize_c7_QUARC_Prog_Rover(SFc7_QUARC_Prog_RoverInstanceStruct
  *chartInstance);
static void initialize_params_c7_QUARC_Prog_Rover
  (SFc7_QUARC_Prog_RoverInstanceStruct *chartInstance);
static void enable_c7_QUARC_Prog_Rover(SFc7_QUARC_Prog_RoverInstanceStruct
  *chartInstance);
static void disable_c7_QUARC_Prog_Rover(SFc7_QUARC_Prog_RoverInstanceStruct
  *chartInstance);
static void c7_update_debugger_state_c7_QUARC_Prog_Rover
  (SFc7_QUARC_Prog_RoverInstanceStruct *chartInstance);
static void ext_mode_exec_c7_QUARC_Prog_Rover
  (SFc7_QUARC_Prog_RoverInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c7_QUARC_Prog_Rover
  (SFc7_QUARC_Prog_RoverInstanceStruct *chartInstance);
static void set_sim_state_c7_QUARC_Prog_Rover
  (SFc7_QUARC_Prog_RoverInstanceStruct *chartInstance, const mxArray *c7_st);
static void finalize_c7_QUARC_Prog_Rover(SFc7_QUARC_Prog_RoverInstanceStruct
  *chartInstance);
static void sf_c7_QUARC_Prog_Rover(SFc7_QUARC_Prog_RoverInstanceStruct
  *chartInstance);
static void initSimStructsc7_QUARC_Prog_Rover
  (SFc7_QUARC_Prog_RoverInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c7_machineNumber, uint32_T
  c7_chartNumber);
static const mxArray *c7_sf_marshallOut(void *chartInstanceVoid, void *c7_inData);
static void c7_emlrt_marshallIn(SFc7_QUARC_Prog_RoverInstanceStruct
  *chartInstance, const mxArray *c7_X_ref, const char_T *c7_identifier, real_T
  c7_y[3]);
static void c7_b_emlrt_marshallIn(SFc7_QUARC_Prog_RoverInstanceStruct
  *chartInstance, const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId,
  real_T c7_y[3]);
static void c7_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData);
static const mxArray *c7_b_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData);
static real_T c7_c_emlrt_marshallIn(SFc7_QUARC_Prog_RoverInstanceStruct
  *chartInstance, const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId);
static void c7_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData);
static const mxArray *c7_c_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData);
static int32_T c7_d_emlrt_marshallIn(SFc7_QUARC_Prog_RoverInstanceStruct
  *chartInstance, const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId);
static void c7_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData);
static uint8_T c7_e_emlrt_marshallIn(SFc7_QUARC_Prog_RoverInstanceStruct
  *chartInstance, const mxArray *c7_is_active_c7_QUARC_Prog_Rover, const char_T *
  c7_identifier);
static uint8_T c7_f_emlrt_marshallIn(SFc7_QUARC_Prog_RoverInstanceStruct
  *chartInstance, const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId);
static void init_dsm_address_info(SFc7_QUARC_Prog_RoverInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c7_QUARC_Prog_Rover(SFc7_QUARC_Prog_RoverInstanceStruct
  *chartInstance)
{
  int32_T *c7_sfEvent;
  uint8_T *c7_is_active_c7_QUARC_Prog_Rover;
  c7_is_active_c7_QUARC_Prog_Rover = (uint8_T *)ssGetDWork(chartInstance->S, 3);
  c7_sfEvent = (int32_T *)ssGetDWork(chartInstance->S, 0);
  *c7_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  *c7_is_active_c7_QUARC_Prog_Rover = 0U;
}

static void initialize_params_c7_QUARC_Prog_Rover
  (SFc7_QUARC_Prog_RoverInstanceStruct *chartInstance)
{
}

static void enable_c7_QUARC_Prog_Rover(SFc7_QUARC_Prog_RoverInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c7_QUARC_Prog_Rover(SFc7_QUARC_Prog_RoverInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c7_update_debugger_state_c7_QUARC_Prog_Rover
  (SFc7_QUARC_Prog_RoverInstanceStruct *chartInstance)
{
}

static void ext_mode_exec_c7_QUARC_Prog_Rover
  (SFc7_QUARC_Prog_RoverInstanceStruct *chartInstance)
{
  c7_update_debugger_state_c7_QUARC_Prog_Rover(chartInstance);
}

static const mxArray *get_sim_state_c7_QUARC_Prog_Rover
  (SFc7_QUARC_Prog_RoverInstanceStruct *chartInstance)
{
  const mxArray *c7_st;
  const mxArray *c7_y = NULL;
  int32_T c7_i0;
  real_T c7_u[3];
  const mxArray *c7_b_y = NULL;
  uint8_T c7_hoistedGlobal;
  uint8_T c7_b_u;
  const mxArray *c7_c_y = NULL;
  uint8_T *c7_is_active_c7_QUARC_Prog_Rover;
  real_T (*c7_X_ref)[3];
  c7_X_ref = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c7_is_active_c7_QUARC_Prog_Rover = (uint8_T *)ssGetDWork(chartInstance->S, 3);
  c7_st = NULL;
  c7_st = NULL;
  c7_y = NULL;
  sf_mex_assign(&c7_y, sf_mex_createcellarray(2), FALSE);
  for (c7_i0 = 0; c7_i0 < 3; c7_i0++) {
    c7_u[c7_i0] = (*c7_X_ref)[c7_i0];
  }

  c7_b_y = NULL;
  sf_mex_assign(&c7_b_y, sf_mex_create("y", c7_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_setcell(c7_y, 0, c7_b_y);
  c7_hoistedGlobal = *c7_is_active_c7_QUARC_Prog_Rover;
  c7_b_u = c7_hoistedGlobal;
  c7_c_y = NULL;
  sf_mex_assign(&c7_c_y, sf_mex_create("y", &c7_b_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c7_y, 1, c7_c_y);
  sf_mex_assign(&c7_st, c7_y, FALSE);
  return c7_st;
}

static void set_sim_state_c7_QUARC_Prog_Rover
  (SFc7_QUARC_Prog_RoverInstanceStruct *chartInstance, const mxArray *c7_st)
{
  const mxArray *c7_u;
  real_T c7_dv0[3];
  int32_T c7_i1;
  boolean_T *c7_doneDoubleBufferReInit;
  uint8_T *c7_is_active_c7_QUARC_Prog_Rover;
  real_T (*c7_X_ref)[3];
  c7_X_ref = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c7_is_active_c7_QUARC_Prog_Rover = (uint8_T *)ssGetDWork(chartInstance->S, 3);
  c7_doneDoubleBufferReInit = (boolean_T *)ssGetDWork(chartInstance->S, 2);
  *c7_doneDoubleBufferReInit = TRUE;
  c7_u = sf_mex_dup(c7_st);
  c7_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c7_u, 0)),
                      "X_ref", c7_dv0);
  for (c7_i1 = 0; c7_i1 < 3; c7_i1++) {
    (*c7_X_ref)[c7_i1] = c7_dv0[c7_i1];
  }

  *c7_is_active_c7_QUARC_Prog_Rover = c7_e_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c7_u, 1)), "is_active_c7_QUARC_Prog_Rover");
  sf_mex_destroy(&c7_u);
  c7_update_debugger_state_c7_QUARC_Prog_Rover(chartInstance);
  sf_mex_destroy(&c7_st);
}

static void finalize_c7_QUARC_Prog_Rover(SFc7_QUARC_Prog_RoverInstanceStruct
  *chartInstance)
{
}

static void sf_c7_QUARC_Prog_Rover(SFc7_QUARC_Prog_RoverInstanceStruct
  *chartInstance)
{
  int32_T c7_i2;
  real_T c7_hoistedGlobal;
  real_T c7_b_hoistedGlobal;
  real_T c7_c_hoistedGlobal;
  real_T c7_t;
  real_T c7_r;
  real_T c7_T;
  uint32_T c7_debug_family_var_map[6];
  real_T c7_nargin = 3.0;
  real_T c7_nargout = 1.0;
  real_T c7_X_ref[3];
  int32_T c7_i3;
  real_T c7_B;
  real_T c7_y;
  real_T c7_b_y;
  real_T c7_c_y;
  real_T c7_a;
  real_T c7_b;
  real_T c7_d_y;
  real_T c7_x;
  real_T c7_b_x;
  real_T c7_b_a;
  real_T c7_b_b;
  real_T c7_e_y;
  real_T c7_b_B;
  real_T c7_f_y;
  real_T c7_g_y;
  real_T c7_h_y;
  real_T c7_c_a;
  real_T c7_c_b;
  real_T c7_i_y;
  real_T c7_c_x;
  real_T c7_d_x;
  real_T c7_d_a;
  real_T c7_d_b;
  real_T c7_j_y;
  int32_T c7_i4;
  real_T *c7_b_T;
  real_T *c7_b_r;
  real_T *c7_b_t;
  int32_T *c7_sfEvent;
  real_T (*c7_b_X_ref)[3];
  c7_b_T = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
  c7_b_r = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c7_b_X_ref = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c7_b_t = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
  c7_sfEvent = (int32_T *)ssGetDWork(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 4U, *c7_sfEvent);
  _SFD_DATA_RANGE_CHECK(*c7_b_t, 0U);
  for (c7_i2 = 0; c7_i2 < 3; c7_i2++) {
    _SFD_DATA_RANGE_CHECK((*c7_b_X_ref)[c7_i2], 1U);
  }

  _SFD_DATA_RANGE_CHECK(*c7_b_r, 2U);
  _SFD_DATA_RANGE_CHECK(*c7_b_T, 3U);
  *c7_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 4U, *c7_sfEvent);
  c7_hoistedGlobal = *c7_b_t;
  c7_b_hoistedGlobal = *c7_b_r;
  c7_c_hoistedGlobal = *c7_b_T;
  c7_t = c7_hoistedGlobal;
  c7_r = c7_b_hoistedGlobal;
  c7_T = c7_c_hoistedGlobal;
  sf_debug_symbol_scope_push_eml(0U, 6U, 6U, c7_debug_family_names,
    c7_debug_family_var_map);
  sf_debug_symbol_scope_add_eml_importable(&c7_nargin, 0U, c7_b_sf_marshallOut,
    c7_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c7_nargout, 1U, c7_b_sf_marshallOut,
    c7_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml(&c7_t, 2U, c7_b_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c7_r, 3U, c7_b_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c7_T, 4U, c7_b_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(c7_X_ref, 5U, c7_sf_marshallOut,
    c7_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, *c7_sfEvent, 8);
  for (c7_i3 = 0; c7_i3 < 3; c7_i3++) {
    c7_X_ref[c7_i3] = 0.0;
  }

  _SFD_EML_CALL(0U, *c7_sfEvent, 9);
  c7_B = c7_T;
  c7_y = c7_B;
  c7_b_y = c7_y;
  c7_c_y = 6.2831853071795862 / c7_b_y;
  c7_a = c7_c_y;
  c7_b = c7_t;
  c7_d_y = c7_a * c7_b;
  c7_x = c7_d_y;
  c7_b_x = c7_x;
  c7_b_x = muDoubleScalarSin(c7_b_x);
  c7_b_a = c7_r;
  c7_b_b = c7_b_x;
  c7_e_y = c7_b_a * c7_b_b;
  c7_X_ref[0] = c7_e_y;
  _SFD_EML_CALL(0U, *c7_sfEvent, 10);
  c7_b_B = c7_T;
  c7_f_y = c7_b_B;
  c7_g_y = c7_f_y;
  c7_h_y = 6.2831853071795862 / c7_g_y;
  c7_c_a = c7_h_y;
  c7_c_b = c7_t;
  c7_i_y = c7_c_a * c7_c_b;
  c7_c_x = c7_i_y;
  c7_d_x = c7_c_x;
  c7_d_x = muDoubleScalarCos(c7_d_x);
  c7_d_a = c7_r;
  c7_d_b = c7_d_x;
  c7_j_y = c7_d_a * c7_d_b;
  c7_X_ref[1] = c7_j_y;
  _SFD_EML_CALL(0U, *c7_sfEvent, 11);
  c7_X_ref[2] = 0.0;
  _SFD_EML_CALL(0U, *c7_sfEvent, -11);
  sf_debug_symbol_scope_pop();
  for (c7_i4 = 0; c7_i4 < 3; c7_i4++) {
    (*c7_b_X_ref)[c7_i4] = c7_X_ref[c7_i4];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 4U, *c7_sfEvent);
  sf_debug_check_for_state_inconsistency(_QUARC_Prog_RoverMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void initSimStructsc7_QUARC_Prog_Rover
  (SFc7_QUARC_Prog_RoverInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c7_machineNumber, uint32_T
  c7_chartNumber)
{
}

static const mxArray *c7_sf_marshallOut(void *chartInstanceVoid, void *c7_inData)
{
  const mxArray *c7_mxArrayOutData = NULL;
  int32_T c7_i5;
  real_T c7_b_inData[3];
  int32_T c7_i6;
  real_T c7_u[3];
  const mxArray *c7_y = NULL;
  SFc7_QUARC_Prog_RoverInstanceStruct *chartInstance;
  chartInstance = (SFc7_QUARC_Prog_RoverInstanceStruct *)chartInstanceVoid;
  c7_mxArrayOutData = NULL;
  for (c7_i5 = 0; c7_i5 < 3; c7_i5++) {
    c7_b_inData[c7_i5] = (*(real_T (*)[3])c7_inData)[c7_i5];
  }

  for (c7_i6 = 0; c7_i6 < 3; c7_i6++) {
    c7_u[c7_i6] = c7_b_inData[c7_i6];
  }

  c7_y = NULL;
  sf_mex_assign(&c7_y, sf_mex_create("y", c7_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_assign(&c7_mxArrayOutData, c7_y, FALSE);
  return c7_mxArrayOutData;
}

static void c7_emlrt_marshallIn(SFc7_QUARC_Prog_RoverInstanceStruct
  *chartInstance, const mxArray *c7_X_ref, const char_T *c7_identifier, real_T
  c7_y[3])
{
  emlrtMsgIdentifier c7_thisId;
  c7_thisId.fIdentifier = c7_identifier;
  c7_thisId.fParent = NULL;
  c7_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c7_X_ref), &c7_thisId, c7_y);
  sf_mex_destroy(&c7_X_ref);
}

static void c7_b_emlrt_marshallIn(SFc7_QUARC_Prog_RoverInstanceStruct
  *chartInstance, const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId,
  real_T c7_y[3])
{
  real_T c7_dv1[3];
  int32_T c7_i7;
  sf_mex_import(c7_parentId, sf_mex_dup(c7_u), c7_dv1, 1, 0, 0U, 1, 0U, 1, 3);
  for (c7_i7 = 0; c7_i7 < 3; c7_i7++) {
    c7_y[c7_i7] = c7_dv1[c7_i7];
  }

  sf_mex_destroy(&c7_u);
}

static void c7_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData)
{
  const mxArray *c7_X_ref;
  const char_T *c7_identifier;
  emlrtMsgIdentifier c7_thisId;
  real_T c7_y[3];
  int32_T c7_i8;
  SFc7_QUARC_Prog_RoverInstanceStruct *chartInstance;
  chartInstance = (SFc7_QUARC_Prog_RoverInstanceStruct *)chartInstanceVoid;
  c7_X_ref = sf_mex_dup(c7_mxArrayInData);
  c7_identifier = c7_varName;
  c7_thisId.fIdentifier = c7_identifier;
  c7_thisId.fParent = NULL;
  c7_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c7_X_ref), &c7_thisId, c7_y);
  sf_mex_destroy(&c7_X_ref);
  for (c7_i8 = 0; c7_i8 < 3; c7_i8++) {
    (*(real_T (*)[3])c7_outData)[c7_i8] = c7_y[c7_i8];
  }

  sf_mex_destroy(&c7_mxArrayInData);
}

static const mxArray *c7_b_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData)
{
  const mxArray *c7_mxArrayOutData = NULL;
  real_T c7_u;
  const mxArray *c7_y = NULL;
  SFc7_QUARC_Prog_RoverInstanceStruct *chartInstance;
  chartInstance = (SFc7_QUARC_Prog_RoverInstanceStruct *)chartInstanceVoid;
  c7_mxArrayOutData = NULL;
  c7_u = *(real_T *)c7_inData;
  c7_y = NULL;
  sf_mex_assign(&c7_y, sf_mex_create("y", &c7_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c7_mxArrayOutData, c7_y, FALSE);
  return c7_mxArrayOutData;
}

static real_T c7_c_emlrt_marshallIn(SFc7_QUARC_Prog_RoverInstanceStruct
  *chartInstance, const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId)
{
  real_T c7_y;
  real_T c7_d0;
  sf_mex_import(c7_parentId, sf_mex_dup(c7_u), &c7_d0, 1, 0, 0U, 0, 0U, 0);
  c7_y = c7_d0;
  sf_mex_destroy(&c7_u);
  return c7_y;
}

static void c7_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData)
{
  const mxArray *c7_nargout;
  const char_T *c7_identifier;
  emlrtMsgIdentifier c7_thisId;
  real_T c7_y;
  SFc7_QUARC_Prog_RoverInstanceStruct *chartInstance;
  chartInstance = (SFc7_QUARC_Prog_RoverInstanceStruct *)chartInstanceVoid;
  c7_nargout = sf_mex_dup(c7_mxArrayInData);
  c7_identifier = c7_varName;
  c7_thisId.fIdentifier = c7_identifier;
  c7_thisId.fParent = NULL;
  c7_y = c7_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c7_nargout), &c7_thisId);
  sf_mex_destroy(&c7_nargout);
  *(real_T *)c7_outData = c7_y;
  sf_mex_destroy(&c7_mxArrayInData);
}

const mxArray *sf_c7_QUARC_Prog_Rover_get_eml_resolved_functions_info(void)
{
  const mxArray *c7_nameCaptureInfo;
  c7_ResolvedFunctionInfo c7_info[8];
  c7_ResolvedFunctionInfo (*c7_b_info)[8];
  const mxArray *c7_m0 = NULL;
  int32_T c7_i9;
  c7_ResolvedFunctionInfo *c7_r0;
  c7_nameCaptureInfo = NULL;
  c7_nameCaptureInfo = NULL;
  c7_b_info = (c7_ResolvedFunctionInfo (*)[8])c7_info;
  (*c7_b_info)[0].context = "";
  (*c7_b_info)[0].name = "mtimes";
  (*c7_b_info)[0].dominantType = "double";
  (*c7_b_info)[0].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  (*c7_b_info)[0].fileTimeLo = 1289519692U;
  (*c7_b_info)[0].fileTimeHi = 0U;
  (*c7_b_info)[0].mFileTimeLo = 0U;
  (*c7_b_info)[0].mFileTimeHi = 0U;
  (*c7_b_info)[1].context = "";
  (*c7_b_info)[1].name = "mrdivide";
  (*c7_b_info)[1].dominantType = "double";
  (*c7_b_info)[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  (*c7_b_info)[1].fileTimeLo = 1310137456U;
  (*c7_b_info)[1].fileTimeHi = 0U;
  (*c7_b_info)[1].mFileTimeLo = 1289519692U;
  (*c7_b_info)[1].mFileTimeHi = 0U;
  (*c7_b_info)[2].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  (*c7_b_info)[2].name = "rdivide";
  (*c7_b_info)[2].dominantType = "double";
  (*c7_b_info)[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  (*c7_b_info)[2].fileTimeLo = 1286818844U;
  (*c7_b_info)[2].fileTimeHi = 0U;
  (*c7_b_info)[2].mFileTimeLo = 0U;
  (*c7_b_info)[2].mFileTimeHi = 0U;
  (*c7_b_info)[3].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  (*c7_b_info)[3].name = "eml_div";
  (*c7_b_info)[3].dominantType = "double";
  (*c7_b_info)[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  (*c7_b_info)[3].fileTimeLo = 1305318000U;
  (*c7_b_info)[3].fileTimeHi = 0U;
  (*c7_b_info)[3].mFileTimeLo = 0U;
  (*c7_b_info)[3].mFileTimeHi = 0U;
  (*c7_b_info)[4].context = "";
  (*c7_b_info)[4].name = "sin";
  (*c7_b_info)[4].dominantType = "double";
  (*c7_b_info)[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m";
  (*c7_b_info)[4].fileTimeLo = 1286818750U;
  (*c7_b_info)[4].fileTimeHi = 0U;
  (*c7_b_info)[4].mFileTimeLo = 0U;
  (*c7_b_info)[4].mFileTimeHi = 0U;
  (*c7_b_info)[5].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m";
  (*c7_b_info)[5].name = "eml_scalar_sin";
  (*c7_b_info)[5].dominantType = "double";
  (*c7_b_info)[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sin.m";
  (*c7_b_info)[5].fileTimeLo = 1286818736U;
  (*c7_b_info)[5].fileTimeHi = 0U;
  (*c7_b_info)[5].mFileTimeLo = 0U;
  (*c7_b_info)[5].mFileTimeHi = 0U;
  (*c7_b_info)[6].context = "";
  (*c7_b_info)[6].name = "cos";
  (*c7_b_info)[6].dominantType = "double";
  (*c7_b_info)[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  (*c7_b_info)[6].fileTimeLo = 1286818706U;
  (*c7_b_info)[6].fileTimeHi = 0U;
  (*c7_b_info)[6].mFileTimeLo = 0U;
  (*c7_b_info)[6].mFileTimeHi = 0U;
  (*c7_b_info)[7].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  (*c7_b_info)[7].name = "eml_scalar_cos";
  (*c7_b_info)[7].dominantType = "double";
  (*c7_b_info)[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_cos.m";
  (*c7_b_info)[7].fileTimeLo = 1286818722U;
  (*c7_b_info)[7].fileTimeHi = 0U;
  (*c7_b_info)[7].mFileTimeLo = 0U;
  (*c7_b_info)[7].mFileTimeHi = 0U;
  sf_mex_assign(&c7_m0, sf_mex_createstruct("nameCaptureInfo", 1, 8), FALSE);
  for (c7_i9 = 0; c7_i9 < 8; c7_i9++) {
    c7_r0 = &c7_info[c7_i9];
    sf_mex_addfield(c7_m0, sf_mex_create("nameCaptureInfo", c7_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c7_r0->context)), "context", "nameCaptureInfo",
                    c7_i9);
    sf_mex_addfield(c7_m0, sf_mex_create("nameCaptureInfo", c7_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c7_r0->name)), "name", "nameCaptureInfo", c7_i9);
    sf_mex_addfield(c7_m0, sf_mex_create("nameCaptureInfo", c7_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c7_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c7_i9);
    sf_mex_addfield(c7_m0, sf_mex_create("nameCaptureInfo", c7_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c7_r0->resolved)), "resolved", "nameCaptureInfo",
                    c7_i9);
    sf_mex_addfield(c7_m0, sf_mex_create("nameCaptureInfo", &c7_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c7_i9);
    sf_mex_addfield(c7_m0, sf_mex_create("nameCaptureInfo", &c7_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c7_i9);
    sf_mex_addfield(c7_m0, sf_mex_create("nameCaptureInfo", &c7_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c7_i9);
    sf_mex_addfield(c7_m0, sf_mex_create("nameCaptureInfo", &c7_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c7_i9);
  }

  sf_mex_assign(&c7_nameCaptureInfo, c7_m0, FALSE);
  return c7_nameCaptureInfo;
}

static const mxArray *c7_c_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData)
{
  const mxArray *c7_mxArrayOutData = NULL;
  int32_T c7_u;
  const mxArray *c7_y = NULL;
  SFc7_QUARC_Prog_RoverInstanceStruct *chartInstance;
  chartInstance = (SFc7_QUARC_Prog_RoverInstanceStruct *)chartInstanceVoid;
  c7_mxArrayOutData = NULL;
  c7_u = *(int32_T *)c7_inData;
  c7_y = NULL;
  sf_mex_assign(&c7_y, sf_mex_create("y", &c7_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c7_mxArrayOutData, c7_y, FALSE);
  return c7_mxArrayOutData;
}

static int32_T c7_d_emlrt_marshallIn(SFc7_QUARC_Prog_RoverInstanceStruct
  *chartInstance, const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId)
{
  int32_T c7_y;
  int32_T c7_i10;
  sf_mex_import(c7_parentId, sf_mex_dup(c7_u), &c7_i10, 1, 6, 0U, 0, 0U, 0);
  c7_y = c7_i10;
  sf_mex_destroy(&c7_u);
  return c7_y;
}

static void c7_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData)
{
  const mxArray *c7_sfEvent;
  const char_T *c7_identifier;
  emlrtMsgIdentifier c7_thisId;
  int32_T c7_y;
  SFc7_QUARC_Prog_RoverInstanceStruct *chartInstance;
  chartInstance = (SFc7_QUARC_Prog_RoverInstanceStruct *)chartInstanceVoid;
  c7_sfEvent = sf_mex_dup(c7_mxArrayInData);
  c7_identifier = c7_varName;
  c7_thisId.fIdentifier = c7_identifier;
  c7_thisId.fParent = NULL;
  c7_y = c7_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c7_sfEvent), &c7_thisId);
  sf_mex_destroy(&c7_sfEvent);
  *(int32_T *)c7_outData = c7_y;
  sf_mex_destroy(&c7_mxArrayInData);
}

static uint8_T c7_e_emlrt_marshallIn(SFc7_QUARC_Prog_RoverInstanceStruct
  *chartInstance, const mxArray *c7_is_active_c7_QUARC_Prog_Rover, const char_T *
  c7_identifier)
{
  uint8_T c7_y;
  emlrtMsgIdentifier c7_thisId;
  c7_thisId.fIdentifier = c7_identifier;
  c7_thisId.fParent = NULL;
  c7_y = c7_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c7_is_active_c7_QUARC_Prog_Rover), &c7_thisId);
  sf_mex_destroy(&c7_is_active_c7_QUARC_Prog_Rover);
  return c7_y;
}

static uint8_T c7_f_emlrt_marshallIn(SFc7_QUARC_Prog_RoverInstanceStruct
  *chartInstance, const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId)
{
  uint8_T c7_y;
  uint8_T c7_u0;
  sf_mex_import(c7_parentId, sf_mex_dup(c7_u), &c7_u0, 1, 3, 0U, 0, 0U, 0);
  c7_y = c7_u0;
  sf_mex_destroy(&c7_u);
  return c7_y;
}

static void init_dsm_address_info(SFc7_QUARC_Prog_RoverInstanceStruct
  *chartInstance)
{
}

/* SFunction Glue Code */
static uint32_T* sf_get_sfun_dwork_checksum();
void sf_c7_QUARC_Prog_Rover_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(389902219U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2028180058U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1768434770U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1678215806U);
}

mxArray *sf_c7_QUARC_Prog_Rover_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("wlpUYXzzWo6Ri1NDE9HITB");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,3,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

static const mxArray *sf_get_sim_state_info_c7_QUARC_Prog_Rover(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"X_ref\",},{M[8],M[0],T\"is_active_c7_QUARC_Prog_Rover\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c7_QUARC_Prog_Rover_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc7_QUARC_Prog_RoverInstanceStruct *chartInstance;
    chartInstance = (SFc7_QUARC_Prog_RoverInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (_QUARC_Prog_RoverMachineNumber_,
           7,
           1,
           1,
           4,
           0,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           ssGetPath(S),
           (void *)S);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          init_script_number_translation(_QUARC_Prog_RoverMachineNumber_,
            chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting
            (_QUARC_Prog_RoverMachineNumber_,chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(_QUARC_Prog_RoverMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"t");
          _SFD_SET_DATA_PROPS(1,2,0,1,"X_ref");
          _SFD_SET_DATA_PROPS(2,1,1,0,"r");
          _SFD_SET_DATA_PROPS(3,1,1,0,"T");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,282);
        _SFD_TRANS_COV_WTS(0,0,0,1,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(0,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              1,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c7_b_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c7_sf_marshallOut,(MexInFcnForType)
            c7_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c7_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c7_b_sf_marshallOut,(MexInFcnForType)NULL);

        {
          real_T *c7_t;
          real_T *c7_r;
          real_T *c7_T;
          real_T (*c7_X_ref)[3];
          c7_T = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
          c7_r = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
          c7_X_ref = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
          c7_t = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, c7_t);
          _SFD_SET_DATA_VALUE_PTR(1U, *c7_X_ref);
          _SFD_SET_DATA_VALUE_PTR(2U, c7_r);
          _SFD_SET_DATA_VALUE_PTR(3U, c7_T);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(_QUARC_Prog_RoverMachineNumber_,
        chartInstance->chartNumber,chartInstance->instanceNumber);
    }
  }
}

static void sf_check_dwork_consistency(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    const uint32_T *sfunDWorkChecksum = sf_get_sfun_dwork_checksum();
    mxArray *infoStruct = load_QUARC_Prog_Rover_optimization_info();
    mxArray* mxRTWDWorkChecksum = sf_get_dwork_info_from_mat_file(S, infoStruct,
      7, "dworkChecksum");
    if (mxRTWDWorkChecksum != NULL) {
      double *pr = mxGetPr(mxRTWDWorkChecksum);
      if ((uint32_T)pr[0] != sfunDWorkChecksum[0] ||
          (uint32_T)pr[1] != sfunDWorkChecksum[1] ||
          (uint32_T)pr[2] != sfunDWorkChecksum[2] ||
          (uint32_T)pr[3] != sfunDWorkChecksum[3]) {
        sf_mex_error_message("Code generation and simulation targets registered different sets of persistent variables for the block. "
                             "External or Rapid Accelerator mode simulation requires code generation and simulation targets to "
                             "register the same set of persistent variables for this block. "
                             "This discrepancy is typically caused by MATLAB functions that have different code paths for "
                             "simulation and code generation targets where these code paths define different sets of persistent variables. "
                             "Please identify these code paths in the offending block and rewrite the MATLAB code so that "
                             "the set of persistent variables is the same between simulation and code generation.");
      }
    }
  }
}

static void sf_opaque_initialize_c7_QUARC_Prog_Rover(void *chartInstanceVar)
{
  sf_check_dwork_consistency(((SFc7_QUARC_Prog_RoverInstanceStruct*)
    chartInstanceVar)->S);
  chart_debug_initialization(((SFc7_QUARC_Prog_RoverInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c7_QUARC_Prog_Rover((SFc7_QUARC_Prog_RoverInstanceStruct*)
    chartInstanceVar);
  initialize_c7_QUARC_Prog_Rover((SFc7_QUARC_Prog_RoverInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c7_QUARC_Prog_Rover(void *chartInstanceVar)
{
  enable_c7_QUARC_Prog_Rover((SFc7_QUARC_Prog_RoverInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c7_QUARC_Prog_Rover(void *chartInstanceVar)
{
  disable_c7_QUARC_Prog_Rover((SFc7_QUARC_Prog_RoverInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c7_QUARC_Prog_Rover(void *chartInstanceVar)
{
  sf_c7_QUARC_Prog_Rover((SFc7_QUARC_Prog_RoverInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_ext_mode_exec_c7_QUARC_Prog_Rover(void *chartInstanceVar)
{
  ext_mode_exec_c7_QUARC_Prog_Rover((SFc7_QUARC_Prog_RoverInstanceStruct*)
    chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c7_QUARC_Prog_Rover(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c7_QUARC_Prog_Rover
    ((SFc7_QUARC_Prog_RoverInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c7_QUARC_Prog_Rover();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_raw2high'.\n");
  }

  return plhs[0];
}

extern void sf_internal_set_sim_state_c7_QUARC_Prog_Rover(SimStruct* S, const
  mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c7_QUARC_Prog_Rover();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c7_QUARC_Prog_Rover((SFc7_QUARC_Prog_RoverInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c7_QUARC_Prog_Rover(SimStruct* S)
{
  return sf_internal_get_sim_state_c7_QUARC_Prog_Rover(S);
}

static void sf_opaque_set_sim_state_c7_QUARC_Prog_Rover(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c7_QUARC_Prog_Rover(S, st);
}

static void sf_opaque_terminate_c7_QUARC_Prog_Rover(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc7_QUARC_Prog_RoverInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
    }

    finalize_c7_QUARC_Prog_Rover((SFc7_QUARC_Prog_RoverInstanceStruct*)
      chartInstanceVar);
    free((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }

  unload_QUARC_Prog_Rover_optimization_info();
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc7_QUARC_Prog_Rover((SFc7_QUARC_Prog_RoverInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c7_QUARC_Prog_Rover(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c7_QUARC_Prog_Rover((SFc7_QUARC_Prog_RoverInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

mxArray *sf_c7_QUARC_Prog_Rover_get_testpoint_info(void)
{
  const char *infoEncStr[] = {
    "100 S'varName','path'{{T\"is_active_c7_QUARC_Prog_Rover\",T\"is_active_c7_QUARC_Prog_Rover\"}}"
  };

  mxArray *mxTpInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 1, 10);
  return mxTpInfo;
}

static void sf_set_sfun_dwork_info(SimStruct *S)
{
  const char *dworkEncStr[] = {
    "100 S1x4'type','isSigned','wordLength','bias','slope','exponent','isComplex','size'{{T\"int32\",,,,,,M[0],M[]},{T\"boolean\",,,,,,M[0],M[]},{T\"boolean\",,,,,,M[0],M[]},{T\"uint8\",,,,,,M[0],M[]}}"
  };

  sf_set_encoded_dwork_info(S, dworkEncStr, 4, 10);
}

static uint32_T* sf_get_sfun_dwork_checksum()
{
  static uint32_T checksum[4] = { 3851270630U, 3363230343U, 1651207761U,
    946165807U };

  return checksum;
}

static void mdlSetWorkWidths_c7_QUARC_Prog_Rover(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_QUARC_Prog_Rover_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,infoStruct,7);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,infoStruct,7,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,infoStruct,7,
      "gatewayCannotBeInlinedMultipleTimes"));
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,infoStruct,7,3);
      sf_mark_chart_reusable_outputs(S,infoStruct,7,1);
    }

    sf_set_rtw_dwork_info(S,infoStruct,7);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
    sf_set_sfun_dwork_info(S);
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(3567056166U));
  ssSetChecksum1(S,(902486824U));
  ssSetChecksum2(S,(3818895163U));
  ssSetChecksum3(S,(1034616489U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
}

static void mdlRTW_c7_QUARC_Prog_Rover(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c7_QUARC_Prog_Rover(SimStruct *S)
{
  SFc7_QUARC_Prog_RoverInstanceStruct *chartInstance;
  chartInstance = (SFc7_QUARC_Prog_RoverInstanceStruct *)malloc(sizeof
    (SFc7_QUARC_Prog_RoverInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc7_QUARC_Prog_RoverInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c7_QUARC_Prog_Rover;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c7_QUARC_Prog_Rover;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c7_QUARC_Prog_Rover;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c7_QUARC_Prog_Rover;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c7_QUARC_Prog_Rover;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c7_QUARC_Prog_Rover;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c7_QUARC_Prog_Rover;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c7_QUARC_Prog_Rover;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c7_QUARC_Prog_Rover;
  chartInstance->chartInfo.mdlStart = mdlStart_c7_QUARC_Prog_Rover;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c7_QUARC_Prog_Rover;
  chartInstance->chartInfo.extModeExec =
    sf_opaque_ext_mode_exec_c7_QUARC_Prog_Rover;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->S = S;
  ssSetUserData(S,(void *)(&(chartInstance->chartInfo)));/* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
  chart_debug_initialization(S,1);
}

void c7_QUARC_Prog_Rover_method_dispatcher(SimStruct *S, int_T method, void
  *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c7_QUARC_Prog_Rover(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c7_QUARC_Prog_Rover(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c7_QUARC_Prog_Rover(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c7_QUARC_Prog_Rover_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
