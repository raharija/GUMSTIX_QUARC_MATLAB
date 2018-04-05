/* Include files */

#include "blascompat32.h"
#include "QUARC_Prog_Rover_sfun.h"
#include "c9_QUARC_Prog_Rover.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "QUARC_Prog_Rover_sfun_debug_macros.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
static const char * c9_debug_family_names[9] = { "torad", "X", "Y", "nargin",
  "nargout", "H", "Tr", "Parm", "pos" };

/* Function Declarations */
static void initialize_c9_QUARC_Prog_Rover(SFc9_QUARC_Prog_RoverInstanceStruct
  *chartInstance);
static void initialize_params_c9_QUARC_Prog_Rover
  (SFc9_QUARC_Prog_RoverInstanceStruct *chartInstance);
static void enable_c9_QUARC_Prog_Rover(SFc9_QUARC_Prog_RoverInstanceStruct
  *chartInstance);
static void disable_c9_QUARC_Prog_Rover(SFc9_QUARC_Prog_RoverInstanceStruct
  *chartInstance);
static void c9_update_debugger_state_c9_QUARC_Prog_Rover
  (SFc9_QUARC_Prog_RoverInstanceStruct *chartInstance);
static void ext_mode_exec_c9_QUARC_Prog_Rover
  (SFc9_QUARC_Prog_RoverInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c9_QUARC_Prog_Rover
  (SFc9_QUARC_Prog_RoverInstanceStruct *chartInstance);
static void set_sim_state_c9_QUARC_Prog_Rover
  (SFc9_QUARC_Prog_RoverInstanceStruct *chartInstance, const mxArray *c9_st);
static void finalize_c9_QUARC_Prog_Rover(SFc9_QUARC_Prog_RoverInstanceStruct
  *chartInstance);
static void sf_c9_QUARC_Prog_Rover(SFc9_QUARC_Prog_RoverInstanceStruct
  *chartInstance);
static void initSimStructsc9_QUARC_Prog_Rover
  (SFc9_QUARC_Prog_RoverInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c9_machineNumber, uint32_T
  c9_chartNumber);
static const mxArray *c9_sf_marshallOut(void *chartInstanceVoid, void *c9_inData);
static void c9_emlrt_marshallIn(SFc9_QUARC_Prog_RoverInstanceStruct
  *chartInstance, const mxArray *c9_pos, const char_T *c9_identifier, real_T
  c9_y[2]);
static void c9_b_emlrt_marshallIn(SFc9_QUARC_Prog_RoverInstanceStruct
  *chartInstance, const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId,
  real_T c9_y[2]);
static void c9_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, void *c9_outData);
static const mxArray *c9_b_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData);
static const mxArray *c9_c_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData);
static real_T c9_c_emlrt_marshallIn(SFc9_QUARC_Prog_RoverInstanceStruct
  *chartInstance, const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId);
static void c9_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, void *c9_outData);
static real_T c9_power(SFc9_QUARC_Prog_RoverInstanceStruct *chartInstance,
  real_T c9_a);
static const mxArray *c9_d_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData);
static int32_T c9_d_emlrt_marshallIn(SFc9_QUARC_Prog_RoverInstanceStruct
  *chartInstance, const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId);
static void c9_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, void *c9_outData);
static uint8_T c9_e_emlrt_marshallIn(SFc9_QUARC_Prog_RoverInstanceStruct
  *chartInstance, const mxArray *c9_is_active_c9_QUARC_Prog_Rover, const char_T *
  c9_identifier);
static uint8_T c9_f_emlrt_marshallIn(SFc9_QUARC_Prog_RoverInstanceStruct
  *chartInstance, const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId);
static void init_dsm_address_info(SFc9_QUARC_Prog_RoverInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c9_QUARC_Prog_Rover(SFc9_QUARC_Prog_RoverInstanceStruct
  *chartInstance)
{
  int32_T *c9_sfEvent;
  uint8_T *c9_is_active_c9_QUARC_Prog_Rover;
  c9_is_active_c9_QUARC_Prog_Rover = (uint8_T *)ssGetDWork(chartInstance->S, 3);
  c9_sfEvent = (int32_T *)ssGetDWork(chartInstance->S, 0);
  *c9_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  *c9_is_active_c9_QUARC_Prog_Rover = 0U;
}

static void initialize_params_c9_QUARC_Prog_Rover
  (SFc9_QUARC_Prog_RoverInstanceStruct *chartInstance)
{
}

static void enable_c9_QUARC_Prog_Rover(SFc9_QUARC_Prog_RoverInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c9_QUARC_Prog_Rover(SFc9_QUARC_Prog_RoverInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c9_update_debugger_state_c9_QUARC_Prog_Rover
  (SFc9_QUARC_Prog_RoverInstanceStruct *chartInstance)
{
}

static void ext_mode_exec_c9_QUARC_Prog_Rover
  (SFc9_QUARC_Prog_RoverInstanceStruct *chartInstance)
{
  c9_update_debugger_state_c9_QUARC_Prog_Rover(chartInstance);
}

static const mxArray *get_sim_state_c9_QUARC_Prog_Rover
  (SFc9_QUARC_Prog_RoverInstanceStruct *chartInstance)
{
  const mxArray *c9_st;
  const mxArray *c9_y = NULL;
  int32_T c9_i0;
  real_T c9_u[2];
  const mxArray *c9_b_y = NULL;
  uint8_T c9_hoistedGlobal;
  uint8_T c9_b_u;
  const mxArray *c9_c_y = NULL;
  uint8_T *c9_is_active_c9_QUARC_Prog_Rover;
  real_T (*c9_pos)[2];
  c9_pos = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 1);
  c9_is_active_c9_QUARC_Prog_Rover = (uint8_T *)ssGetDWork(chartInstance->S, 3);
  c9_st = NULL;
  c9_st = NULL;
  c9_y = NULL;
  sf_mex_assign(&c9_y, sf_mex_createcellarray(2), FALSE);
  for (c9_i0 = 0; c9_i0 < 2; c9_i0++) {
    c9_u[c9_i0] = (*c9_pos)[c9_i0];
  }

  c9_b_y = NULL;
  sf_mex_assign(&c9_b_y, sf_mex_create("y", c9_u, 0, 0U, 1U, 0U, 2, 1, 2), FALSE);
  sf_mex_setcell(c9_y, 0, c9_b_y);
  c9_hoistedGlobal = *c9_is_active_c9_QUARC_Prog_Rover;
  c9_b_u = c9_hoistedGlobal;
  c9_c_y = NULL;
  sf_mex_assign(&c9_c_y, sf_mex_create("y", &c9_b_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c9_y, 1, c9_c_y);
  sf_mex_assign(&c9_st, c9_y, FALSE);
  return c9_st;
}

static void set_sim_state_c9_QUARC_Prog_Rover
  (SFc9_QUARC_Prog_RoverInstanceStruct *chartInstance, const mxArray *c9_st)
{
  const mxArray *c9_u;
  real_T c9_dv0[2];
  int32_T c9_i1;
  boolean_T *c9_doneDoubleBufferReInit;
  uint8_T *c9_is_active_c9_QUARC_Prog_Rover;
  real_T (*c9_pos)[2];
  c9_pos = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 1);
  c9_is_active_c9_QUARC_Prog_Rover = (uint8_T *)ssGetDWork(chartInstance->S, 3);
  c9_doneDoubleBufferReInit = (boolean_T *)ssGetDWork(chartInstance->S, 2);
  *c9_doneDoubleBufferReInit = TRUE;
  c9_u = sf_mex_dup(c9_st);
  c9_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c9_u, 0)), "pos",
                      c9_dv0);
  for (c9_i1 = 0; c9_i1 < 2; c9_i1++) {
    (*c9_pos)[c9_i1] = c9_dv0[c9_i1];
  }

  *c9_is_active_c9_QUARC_Prog_Rover = c9_e_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c9_u, 1)), "is_active_c9_QUARC_Prog_Rover");
  sf_mex_destroy(&c9_u);
  c9_update_debugger_state_c9_QUARC_Prog_Rover(chartInstance);
  sf_mex_destroy(&c9_st);
}

static void finalize_c9_QUARC_Prog_Rover(SFc9_QUARC_Prog_RoverInstanceStruct
  *chartInstance)
{
}

static void sf_c9_QUARC_Prog_Rover(SFc9_QUARC_Prog_RoverInstanceStruct
  *chartInstance)
{
  int32_T c9_i2;
  int32_T c9_i3;
  int32_T c9_i4;
  real_T c9_hoistedGlobal;
  real_T c9_H;
  int32_T c9_i5;
  real_T c9_Tr[2];
  int32_T c9_i6;
  real_T c9_Parm[10];
  uint32_T c9_debug_family_var_map[9];
  real_T c9_torad;
  real_T c9_X;
  real_T c9_Y;
  real_T c9_nargin = 3.0;
  real_T c9_nargout = 1.0;
  real_T c9_pos[2];
  real_T c9_x;
  real_T c9_b_x;
  real_T c9_c_x;
  real_T c9_d_x;
  int32_T c9_i7;
  int32_T *c9_sfEvent;
  real_T *c9_b_H;
  real_T (*c9_b_pos)[2];
  real_T (*c9_b_Parm)[10];
  real_T (*c9_b_Tr)[2];
  c9_b_Parm = (real_T (*)[10])ssGetInputPortSignal(chartInstance->S, 2);
  c9_b_pos = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 1);
  c9_b_Tr = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 1);
  c9_b_H = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
  c9_sfEvent = (int32_T *)ssGetDWork(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 6U, *c9_sfEvent);
  _SFD_DATA_RANGE_CHECK(*c9_b_H, 0U);
  for (c9_i2 = 0; c9_i2 < 2; c9_i2++) {
    _SFD_DATA_RANGE_CHECK((*c9_b_Tr)[c9_i2], 1U);
  }

  for (c9_i3 = 0; c9_i3 < 2; c9_i3++) {
    _SFD_DATA_RANGE_CHECK((*c9_b_pos)[c9_i3], 2U);
  }

  for (c9_i4 = 0; c9_i4 < 10; c9_i4++) {
    _SFD_DATA_RANGE_CHECK((*c9_b_Parm)[c9_i4], 3U);
  }

  *c9_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 6U, *c9_sfEvent);
  c9_hoistedGlobal = *c9_b_H;
  c9_H = c9_hoistedGlobal;
  for (c9_i5 = 0; c9_i5 < 2; c9_i5++) {
    c9_Tr[c9_i5] = (*c9_b_Tr)[c9_i5];
  }

  for (c9_i6 = 0; c9_i6 < 10; c9_i6++) {
    c9_Parm[c9_i6] = (*c9_b_Parm)[c9_i6];
  }

  sf_debug_symbol_scope_push_eml(0U, 9U, 9U, c9_debug_family_names,
    c9_debug_family_var_map);
  sf_debug_symbol_scope_add_eml_importable(&c9_torad, 0U, c9_c_sf_marshallOut,
    c9_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c9_X, 1U, c9_c_sf_marshallOut,
    c9_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c9_Y, 2U, c9_c_sf_marshallOut,
    c9_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c9_nargin, 3U, c9_c_sf_marshallOut,
    c9_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c9_nargout, 4U, c9_c_sf_marshallOut,
    c9_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml(&c9_H, 5U, c9_c_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c9_Tr, 6U, c9_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c9_Parm, 7U, c9_b_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(c9_pos, 8U, c9_sf_marshallOut,
    c9_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, *c9_sfEvent, 2);
  c9_torad = 0.017453292519943295;
  _SFD_EML_CALL(0U, *c9_sfEvent, 3);
  c9_x = c9_torad * (((c9_Parm[0] * c9_Tr[0] + c9_Parm[1] * c9_power
                       (chartInstance, c9_Tr[0])) + c9_Parm[2] * c9_Tr[1]) +
                     c9_Parm[3]);
  c9_b_x = c9_x;
  c9_b_x = muDoubleScalarTan(c9_b_x);
  c9_X = c9_H * c9_b_x;
  _SFD_EML_CALL(0U, *c9_sfEvent, 4);
  c9_c_x = c9_torad * (((c9_Parm[4] * c9_Tr[1] + c9_Parm[5] * c9_power
    (chartInstance, c9_Tr[1])) + c9_Parm[6] * c9_Tr[0]) + c9_Parm[7]);
  c9_d_x = c9_c_x;
  c9_d_x = muDoubleScalarTan(c9_d_x);
  c9_Y = c9_H * c9_d_x;
  _SFD_EML_CALL(0U, *c9_sfEvent, 5);
  c9_pos[0] = c9_X;
  c9_pos[1] = c9_Y;
  _SFD_EML_CALL(0U, *c9_sfEvent, -5);
  sf_debug_symbol_scope_pop();
  for (c9_i7 = 0; c9_i7 < 2; c9_i7++) {
    (*c9_b_pos)[c9_i7] = c9_pos[c9_i7];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 6U, *c9_sfEvent);
  sf_debug_check_for_state_inconsistency(_QUARC_Prog_RoverMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void initSimStructsc9_QUARC_Prog_Rover
  (SFc9_QUARC_Prog_RoverInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c9_machineNumber, uint32_T
  c9_chartNumber)
{
}

static const mxArray *c9_sf_marshallOut(void *chartInstanceVoid, void *c9_inData)
{
  const mxArray *c9_mxArrayOutData = NULL;
  int32_T c9_i8;
  real_T c9_b_inData[2];
  int32_T c9_i9;
  real_T c9_u[2];
  const mxArray *c9_y = NULL;
  SFc9_QUARC_Prog_RoverInstanceStruct *chartInstance;
  chartInstance = (SFc9_QUARC_Prog_RoverInstanceStruct *)chartInstanceVoid;
  c9_mxArrayOutData = NULL;
  for (c9_i8 = 0; c9_i8 < 2; c9_i8++) {
    c9_b_inData[c9_i8] = (*(real_T (*)[2])c9_inData)[c9_i8];
  }

  for (c9_i9 = 0; c9_i9 < 2; c9_i9++) {
    c9_u[c9_i9] = c9_b_inData[c9_i9];
  }

  c9_y = NULL;
  sf_mex_assign(&c9_y, sf_mex_create("y", c9_u, 0, 0U, 1U, 0U, 2, 1, 2), FALSE);
  sf_mex_assign(&c9_mxArrayOutData, c9_y, FALSE);
  return c9_mxArrayOutData;
}

static void c9_emlrt_marshallIn(SFc9_QUARC_Prog_RoverInstanceStruct
  *chartInstance, const mxArray *c9_pos, const char_T *c9_identifier, real_T
  c9_y[2])
{
  emlrtMsgIdentifier c9_thisId;
  c9_thisId.fIdentifier = c9_identifier;
  c9_thisId.fParent = NULL;
  c9_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c9_pos), &c9_thisId, c9_y);
  sf_mex_destroy(&c9_pos);
}

static void c9_b_emlrt_marshallIn(SFc9_QUARC_Prog_RoverInstanceStruct
  *chartInstance, const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId,
  real_T c9_y[2])
{
  real_T c9_dv1[2];
  int32_T c9_i10;
  sf_mex_import(c9_parentId, sf_mex_dup(c9_u), c9_dv1, 1, 0, 0U, 1, 0U, 2, 1, 2);
  for (c9_i10 = 0; c9_i10 < 2; c9_i10++) {
    c9_y[c9_i10] = c9_dv1[c9_i10];
  }

  sf_mex_destroy(&c9_u);
}

static void c9_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, void *c9_outData)
{
  const mxArray *c9_pos;
  const char_T *c9_identifier;
  emlrtMsgIdentifier c9_thisId;
  real_T c9_y[2];
  int32_T c9_i11;
  SFc9_QUARC_Prog_RoverInstanceStruct *chartInstance;
  chartInstance = (SFc9_QUARC_Prog_RoverInstanceStruct *)chartInstanceVoid;
  c9_pos = sf_mex_dup(c9_mxArrayInData);
  c9_identifier = c9_varName;
  c9_thisId.fIdentifier = c9_identifier;
  c9_thisId.fParent = NULL;
  c9_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c9_pos), &c9_thisId, c9_y);
  sf_mex_destroy(&c9_pos);
  for (c9_i11 = 0; c9_i11 < 2; c9_i11++) {
    (*(real_T (*)[2])c9_outData)[c9_i11] = c9_y[c9_i11];
  }

  sf_mex_destroy(&c9_mxArrayInData);
}

static const mxArray *c9_b_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData)
{
  const mxArray *c9_mxArrayOutData = NULL;
  int32_T c9_i12;
  real_T c9_b_inData[10];
  int32_T c9_i13;
  real_T c9_u[10];
  const mxArray *c9_y = NULL;
  SFc9_QUARC_Prog_RoverInstanceStruct *chartInstance;
  chartInstance = (SFc9_QUARC_Prog_RoverInstanceStruct *)chartInstanceVoid;
  c9_mxArrayOutData = NULL;
  for (c9_i12 = 0; c9_i12 < 10; c9_i12++) {
    c9_b_inData[c9_i12] = (*(real_T (*)[10])c9_inData)[c9_i12];
  }

  for (c9_i13 = 0; c9_i13 < 10; c9_i13++) {
    c9_u[c9_i13] = c9_b_inData[c9_i13];
  }

  c9_y = NULL;
  sf_mex_assign(&c9_y, sf_mex_create("y", c9_u, 0, 0U, 1U, 0U, 1, 10), FALSE);
  sf_mex_assign(&c9_mxArrayOutData, c9_y, FALSE);
  return c9_mxArrayOutData;
}

static const mxArray *c9_c_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData)
{
  const mxArray *c9_mxArrayOutData = NULL;
  real_T c9_u;
  const mxArray *c9_y = NULL;
  SFc9_QUARC_Prog_RoverInstanceStruct *chartInstance;
  chartInstance = (SFc9_QUARC_Prog_RoverInstanceStruct *)chartInstanceVoid;
  c9_mxArrayOutData = NULL;
  c9_u = *(real_T *)c9_inData;
  c9_y = NULL;
  sf_mex_assign(&c9_y, sf_mex_create("y", &c9_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c9_mxArrayOutData, c9_y, FALSE);
  return c9_mxArrayOutData;
}

static real_T c9_c_emlrt_marshallIn(SFc9_QUARC_Prog_RoverInstanceStruct
  *chartInstance, const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId)
{
  real_T c9_y;
  real_T c9_d0;
  sf_mex_import(c9_parentId, sf_mex_dup(c9_u), &c9_d0, 1, 0, 0U, 0, 0U, 0);
  c9_y = c9_d0;
  sf_mex_destroy(&c9_u);
  return c9_y;
}

static void c9_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, void *c9_outData)
{
  const mxArray *c9_nargout;
  const char_T *c9_identifier;
  emlrtMsgIdentifier c9_thisId;
  real_T c9_y;
  SFc9_QUARC_Prog_RoverInstanceStruct *chartInstance;
  chartInstance = (SFc9_QUARC_Prog_RoverInstanceStruct *)chartInstanceVoid;
  c9_nargout = sf_mex_dup(c9_mxArrayInData);
  c9_identifier = c9_varName;
  c9_thisId.fIdentifier = c9_identifier;
  c9_thisId.fParent = NULL;
  c9_y = c9_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c9_nargout), &c9_thisId);
  sf_mex_destroy(&c9_nargout);
  *(real_T *)c9_outData = c9_y;
  sf_mex_destroy(&c9_mxArrayInData);
}

const mxArray *sf_c9_QUARC_Prog_Rover_get_eml_resolved_functions_info(void)
{
  const mxArray *c9_nameCaptureInfo;
  c9_ResolvedFunctionInfo c9_info[9];
  c9_ResolvedFunctionInfo (*c9_b_info)[9];
  const mxArray *c9_m0 = NULL;
  int32_T c9_i14;
  c9_ResolvedFunctionInfo *c9_r0;
  c9_nameCaptureInfo = NULL;
  c9_nameCaptureInfo = NULL;
  c9_b_info = (c9_ResolvedFunctionInfo (*)[9])c9_info;
  (*c9_b_info)[0].context = "";
  (*c9_b_info)[0].name = "mrdivide";
  (*c9_b_info)[0].dominantType = "double";
  (*c9_b_info)[0].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  (*c9_b_info)[0].fileTimeLo = 1310137456U;
  (*c9_b_info)[0].fileTimeHi = 0U;
  (*c9_b_info)[0].mFileTimeLo = 1289519692U;
  (*c9_b_info)[0].mFileTimeHi = 0U;
  (*c9_b_info)[1].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  (*c9_b_info)[1].name = "rdivide";
  (*c9_b_info)[1].dominantType = "double";
  (*c9_b_info)[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  (*c9_b_info)[1].fileTimeLo = 1286818844U;
  (*c9_b_info)[1].fileTimeHi = 0U;
  (*c9_b_info)[1].mFileTimeLo = 0U;
  (*c9_b_info)[1].mFileTimeHi = 0U;
  (*c9_b_info)[2].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  (*c9_b_info)[2].name = "eml_div";
  (*c9_b_info)[2].dominantType = "double";
  (*c9_b_info)[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  (*c9_b_info)[2].fileTimeLo = 1305318000U;
  (*c9_b_info)[2].fileTimeHi = 0U;
  (*c9_b_info)[2].mFileTimeLo = 0U;
  (*c9_b_info)[2].mFileTimeHi = 0U;
  (*c9_b_info)[3].context = "";
  (*c9_b_info)[3].name = "power";
  (*c9_b_info)[3].dominantType = "double";
  (*c9_b_info)[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  (*c9_b_info)[3].fileTimeLo = 1294067944U;
  (*c9_b_info)[3].fileTimeHi = 0U;
  (*c9_b_info)[3].mFileTimeLo = 0U;
  (*c9_b_info)[3].mFileTimeHi = 0U;
  (*c9_b_info)[4].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  (*c9_b_info)[4].name = "eml_scalar_eg";
  (*c9_b_info)[4].dominantType = "double";
  (*c9_b_info)[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  (*c9_b_info)[4].fileTimeLo = 1286818796U;
  (*c9_b_info)[4].fileTimeHi = 0U;
  (*c9_b_info)[4].mFileTimeLo = 0U;
  (*c9_b_info)[4].mFileTimeHi = 0U;
  (*c9_b_info)[5].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  (*c9_b_info)[5].name = "eml_scalexp_alloc";
  (*c9_b_info)[5].dominantType = "double";
  (*c9_b_info)[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  (*c9_b_info)[5].fileTimeLo = 1286818796U;
  (*c9_b_info)[5].fileTimeHi = 0U;
  (*c9_b_info)[5].mFileTimeLo = 0U;
  (*c9_b_info)[5].mFileTimeHi = 0U;
  (*c9_b_info)[6].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  (*c9_b_info)[6].name = "eml_scalar_floor";
  (*c9_b_info)[6].dominantType = "double";
  (*c9_b_info)[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m";
  (*c9_b_info)[6].fileTimeLo = 1286818726U;
  (*c9_b_info)[6].fileTimeHi = 0U;
  (*c9_b_info)[6].mFileTimeLo = 0U;
  (*c9_b_info)[6].mFileTimeHi = 0U;
  (*c9_b_info)[7].context = "";
  (*c9_b_info)[7].name = "tan";
  (*c9_b_info)[7].dominantType = "double";
  (*c9_b_info)[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/tan.m";
  (*c9_b_info)[7].fileTimeLo = 1286818752U;
  (*c9_b_info)[7].fileTimeHi = 0U;
  (*c9_b_info)[7].mFileTimeLo = 0U;
  (*c9_b_info)[7].mFileTimeHi = 0U;
  (*c9_b_info)[8].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/tan.m";
  (*c9_b_info)[8].name = "eml_scalar_tan";
  (*c9_b_info)[8].dominantType = "double";
  (*c9_b_info)[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_tan.m";
  (*c9_b_info)[8].fileTimeLo = 1286818738U;
  (*c9_b_info)[8].fileTimeHi = 0U;
  (*c9_b_info)[8].mFileTimeLo = 0U;
  (*c9_b_info)[8].mFileTimeHi = 0U;
  sf_mex_assign(&c9_m0, sf_mex_createstruct("nameCaptureInfo", 1, 9), FALSE);
  for (c9_i14 = 0; c9_i14 < 9; c9_i14++) {
    c9_r0 = &c9_info[c9_i14];
    sf_mex_addfield(c9_m0, sf_mex_create("nameCaptureInfo", c9_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c9_r0->context)), "context", "nameCaptureInfo",
                    c9_i14);
    sf_mex_addfield(c9_m0, sf_mex_create("nameCaptureInfo", c9_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c9_r0->name)), "name", "nameCaptureInfo", c9_i14);
    sf_mex_addfield(c9_m0, sf_mex_create("nameCaptureInfo", c9_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c9_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c9_i14);
    sf_mex_addfield(c9_m0, sf_mex_create("nameCaptureInfo", c9_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c9_r0->resolved)), "resolved", "nameCaptureInfo",
                    c9_i14);
    sf_mex_addfield(c9_m0, sf_mex_create("nameCaptureInfo", &c9_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c9_i14);
    sf_mex_addfield(c9_m0, sf_mex_create("nameCaptureInfo", &c9_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c9_i14);
    sf_mex_addfield(c9_m0, sf_mex_create("nameCaptureInfo", &c9_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c9_i14);
    sf_mex_addfield(c9_m0, sf_mex_create("nameCaptureInfo", &c9_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c9_i14);
  }

  sf_mex_assign(&c9_nameCaptureInfo, c9_m0, FALSE);
  return c9_nameCaptureInfo;
}

static real_T c9_power(SFc9_QUARC_Prog_RoverInstanceStruct *chartInstance,
  real_T c9_a)
{
  real_T c9_ak;
  c9_ak = c9_a;
  return muDoubleScalarPower(c9_ak, 2.0);
}

static const mxArray *c9_d_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData)
{
  const mxArray *c9_mxArrayOutData = NULL;
  int32_T c9_u;
  const mxArray *c9_y = NULL;
  SFc9_QUARC_Prog_RoverInstanceStruct *chartInstance;
  chartInstance = (SFc9_QUARC_Prog_RoverInstanceStruct *)chartInstanceVoid;
  c9_mxArrayOutData = NULL;
  c9_u = *(int32_T *)c9_inData;
  c9_y = NULL;
  sf_mex_assign(&c9_y, sf_mex_create("y", &c9_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c9_mxArrayOutData, c9_y, FALSE);
  return c9_mxArrayOutData;
}

static int32_T c9_d_emlrt_marshallIn(SFc9_QUARC_Prog_RoverInstanceStruct
  *chartInstance, const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId)
{
  int32_T c9_y;
  int32_T c9_i15;
  sf_mex_import(c9_parentId, sf_mex_dup(c9_u), &c9_i15, 1, 6, 0U, 0, 0U, 0);
  c9_y = c9_i15;
  sf_mex_destroy(&c9_u);
  return c9_y;
}

static void c9_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, void *c9_outData)
{
  const mxArray *c9_sfEvent;
  const char_T *c9_identifier;
  emlrtMsgIdentifier c9_thisId;
  int32_T c9_y;
  SFc9_QUARC_Prog_RoverInstanceStruct *chartInstance;
  chartInstance = (SFc9_QUARC_Prog_RoverInstanceStruct *)chartInstanceVoid;
  c9_sfEvent = sf_mex_dup(c9_mxArrayInData);
  c9_identifier = c9_varName;
  c9_thisId.fIdentifier = c9_identifier;
  c9_thisId.fParent = NULL;
  c9_y = c9_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c9_sfEvent), &c9_thisId);
  sf_mex_destroy(&c9_sfEvent);
  *(int32_T *)c9_outData = c9_y;
  sf_mex_destroy(&c9_mxArrayInData);
}

static uint8_T c9_e_emlrt_marshallIn(SFc9_QUARC_Prog_RoverInstanceStruct
  *chartInstance, const mxArray *c9_is_active_c9_QUARC_Prog_Rover, const char_T *
  c9_identifier)
{
  uint8_T c9_y;
  emlrtMsgIdentifier c9_thisId;
  c9_thisId.fIdentifier = c9_identifier;
  c9_thisId.fParent = NULL;
  c9_y = c9_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c9_is_active_c9_QUARC_Prog_Rover), &c9_thisId);
  sf_mex_destroy(&c9_is_active_c9_QUARC_Prog_Rover);
  return c9_y;
}

static uint8_T c9_f_emlrt_marshallIn(SFc9_QUARC_Prog_RoverInstanceStruct
  *chartInstance, const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId)
{
  uint8_T c9_y;
  uint8_T c9_u0;
  sf_mex_import(c9_parentId, sf_mex_dup(c9_u), &c9_u0, 1, 3, 0U, 0, 0U, 0);
  c9_y = c9_u0;
  sf_mex_destroy(&c9_u);
  return c9_y;
}

static void init_dsm_address_info(SFc9_QUARC_Prog_RoverInstanceStruct
  *chartInstance)
{
}

/* SFunction Glue Code */
static uint32_T* sf_get_sfun_dwork_checksum();
void sf_c9_QUARC_Prog_Rover_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1027115387U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2668279444U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(604395059U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3745112540U);
}

mxArray *sf_c9_QUARC_Prog_Rover_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("oI5aTOtQRjsmZjaVKwjEMH");
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
      pr[1] = (double)(2);
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
      pr[0] = (double)(10);
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
      pr[0] = (double)(1);
      pr[1] = (double)(2);
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

static const mxArray *sf_get_sim_state_info_c9_QUARC_Prog_Rover(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"pos\",},{M[8],M[0],T\"is_active_c9_QUARC_Prog_Rover\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c9_QUARC_Prog_Rover_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc9_QUARC_Prog_RoverInstanceStruct *chartInstance;
    chartInstance = (SFc9_QUARC_Prog_RoverInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (_QUARC_Prog_RoverMachineNumber_,
           9,
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
          _SFD_SET_DATA_PROPS(0,1,1,0,"H");
          _SFD_SET_DATA_PROPS(1,1,1,0,"Tr");
          _SFD_SET_DATA_PROPS(2,2,0,1,"pos");
          _SFD_SET_DATA_PROPS(3,1,1,0,"Parm");
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
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,231);
        _SFD_TRANS_COV_WTS(0,0,0,1,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(0,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              1,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c9_c_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[2];
          dimVector[0]= 1;
          dimVector[1]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c9_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 1;
          dimVector[1]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c9_sf_marshallOut,(MexInFcnForType)
            c9_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 10;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c9_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          real_T *c9_H;
          real_T (*c9_Tr)[2];
          real_T (*c9_pos)[2];
          real_T (*c9_Parm)[10];
          c9_Parm = (real_T (*)[10])ssGetInputPortSignal(chartInstance->S, 2);
          c9_pos = (real_T (*)[2])ssGetOutputPortSignal(chartInstance->S, 1);
          c9_Tr = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 1);
          c9_H = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, c9_H);
          _SFD_SET_DATA_VALUE_PTR(1U, *c9_Tr);
          _SFD_SET_DATA_VALUE_PTR(2U, *c9_pos);
          _SFD_SET_DATA_VALUE_PTR(3U, *c9_Parm);
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
      9, "dworkChecksum");
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

static void sf_opaque_initialize_c9_QUARC_Prog_Rover(void *chartInstanceVar)
{
  sf_check_dwork_consistency(((SFc9_QUARC_Prog_RoverInstanceStruct*)
    chartInstanceVar)->S);
  chart_debug_initialization(((SFc9_QUARC_Prog_RoverInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c9_QUARC_Prog_Rover((SFc9_QUARC_Prog_RoverInstanceStruct*)
    chartInstanceVar);
  initialize_c9_QUARC_Prog_Rover((SFc9_QUARC_Prog_RoverInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c9_QUARC_Prog_Rover(void *chartInstanceVar)
{
  enable_c9_QUARC_Prog_Rover((SFc9_QUARC_Prog_RoverInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c9_QUARC_Prog_Rover(void *chartInstanceVar)
{
  disable_c9_QUARC_Prog_Rover((SFc9_QUARC_Prog_RoverInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c9_QUARC_Prog_Rover(void *chartInstanceVar)
{
  sf_c9_QUARC_Prog_Rover((SFc9_QUARC_Prog_RoverInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_ext_mode_exec_c9_QUARC_Prog_Rover(void *chartInstanceVar)
{
  ext_mode_exec_c9_QUARC_Prog_Rover((SFc9_QUARC_Prog_RoverInstanceStruct*)
    chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c9_QUARC_Prog_Rover(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c9_QUARC_Prog_Rover
    ((SFc9_QUARC_Prog_RoverInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c9_QUARC_Prog_Rover();/* state var info */
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

extern void sf_internal_set_sim_state_c9_QUARC_Prog_Rover(SimStruct* S, const
  mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c9_QUARC_Prog_Rover();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c9_QUARC_Prog_Rover((SFc9_QUARC_Prog_RoverInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c9_QUARC_Prog_Rover(SimStruct* S)
{
  return sf_internal_get_sim_state_c9_QUARC_Prog_Rover(S);
}

static void sf_opaque_set_sim_state_c9_QUARC_Prog_Rover(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c9_QUARC_Prog_Rover(S, st);
}

static void sf_opaque_terminate_c9_QUARC_Prog_Rover(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc9_QUARC_Prog_RoverInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
    }

    finalize_c9_QUARC_Prog_Rover((SFc9_QUARC_Prog_RoverInstanceStruct*)
      chartInstanceVar);
    free((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }

  unload_QUARC_Prog_Rover_optimization_info();
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc9_QUARC_Prog_Rover((SFc9_QUARC_Prog_RoverInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c9_QUARC_Prog_Rover(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c9_QUARC_Prog_Rover((SFc9_QUARC_Prog_RoverInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

mxArray *sf_c9_QUARC_Prog_Rover_get_testpoint_info(void)
{
  const char *infoEncStr[] = {
    "100 S'varName','path'{{T\"is_active_c9_QUARC_Prog_Rover\",T\"is_active_c9_QUARC_Prog_Rover\"}}"
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

static void mdlSetWorkWidths_c9_QUARC_Prog_Rover(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_QUARC_Prog_Rover_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,infoStruct,9);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,infoStruct,9,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,infoStruct,9,
      "gatewayCannotBeInlinedMultipleTimes"));
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,infoStruct,9,3);
      sf_mark_chart_reusable_outputs(S,infoStruct,9,1);
    }

    sf_set_rtw_dwork_info(S,infoStruct,9);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
    sf_set_sfun_dwork_info(S);
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(2093750955U));
  ssSetChecksum1(S,(208742489U));
  ssSetChecksum2(S,(2325302198U));
  ssSetChecksum3(S,(4247617791U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
}

static void mdlRTW_c9_QUARC_Prog_Rover(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c9_QUARC_Prog_Rover(SimStruct *S)
{
  SFc9_QUARC_Prog_RoverInstanceStruct *chartInstance;
  chartInstance = (SFc9_QUARC_Prog_RoverInstanceStruct *)malloc(sizeof
    (SFc9_QUARC_Prog_RoverInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc9_QUARC_Prog_RoverInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c9_QUARC_Prog_Rover;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c9_QUARC_Prog_Rover;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c9_QUARC_Prog_Rover;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c9_QUARC_Prog_Rover;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c9_QUARC_Prog_Rover;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c9_QUARC_Prog_Rover;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c9_QUARC_Prog_Rover;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c9_QUARC_Prog_Rover;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c9_QUARC_Prog_Rover;
  chartInstance->chartInfo.mdlStart = mdlStart_c9_QUARC_Prog_Rover;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c9_QUARC_Prog_Rover;
  chartInstance->chartInfo.extModeExec =
    sf_opaque_ext_mode_exec_c9_QUARC_Prog_Rover;
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

void c9_QUARC_Prog_Rover_method_dispatcher(SimStruct *S, int_T method, void
  *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c9_QUARC_Prog_Rover(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c9_QUARC_Prog_Rover(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c9_QUARC_Prog_Rover(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c9_QUARC_Prog_Rover_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
