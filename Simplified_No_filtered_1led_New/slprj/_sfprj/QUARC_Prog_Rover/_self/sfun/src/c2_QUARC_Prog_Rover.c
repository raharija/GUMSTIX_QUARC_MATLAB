/* Include files */

#include "blascompat32.h"
#include "QUARC_Prog_Rover_sfun.h"
#include "c2_QUARC_Prog_Rover.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "QUARC_Prog_Rover_sfun_debug_macros.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
static const char * c2_debug_family_names[14] = { "ex", "ey", "ez", "qx", "qy",
  "qz", "Q", "phi", "theta", "psi", "nargin", "nargout", "Angles", "Euler" };

static const char * c2_b_debug_family_names[4] = { "nargin", "nargout", "Q",
  "Qn" };

static const char * c2_c_debug_family_names[5] = { "nargin", "nargout", "S", "V",
  "Q" };

static const char * c2_d_debug_family_names[9] = { "s1", "s2", "v1", "v2",
  "nargin", "nargout", "Q1", "Q2", "q" };

static const char * c2_e_debug_family_names[6] = { "nargin", "nargout", "Q",
  "PHI", "THETA", "PSI" };

/* Function Declarations */
static void initialize_c2_QUARC_Prog_Rover(SFc2_QUARC_Prog_RoverInstanceStruct
  *chartInstance);
static void initialize_params_c2_QUARC_Prog_Rover
  (SFc2_QUARC_Prog_RoverInstanceStruct *chartInstance);
static void enable_c2_QUARC_Prog_Rover(SFc2_QUARC_Prog_RoverInstanceStruct
  *chartInstance);
static void disable_c2_QUARC_Prog_Rover(SFc2_QUARC_Prog_RoverInstanceStruct
  *chartInstance);
static void c2_update_debugger_state_c2_QUARC_Prog_Rover
  (SFc2_QUARC_Prog_RoverInstanceStruct *chartInstance);
static void ext_mode_exec_c2_QUARC_Prog_Rover
  (SFc2_QUARC_Prog_RoverInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c2_QUARC_Prog_Rover
  (SFc2_QUARC_Prog_RoverInstanceStruct *chartInstance);
static void set_sim_state_c2_QUARC_Prog_Rover
  (SFc2_QUARC_Prog_RoverInstanceStruct *chartInstance, const mxArray *c2_st);
static void finalize_c2_QUARC_Prog_Rover(SFc2_QUARC_Prog_RoverInstanceStruct
  *chartInstance);
static void sf_c2_QUARC_Prog_Rover(SFc2_QUARC_Prog_RoverInstanceStruct
  *chartInstance);
static void initSimStructsc2_QUARC_Prog_Rover
  (SFc2_QUARC_Prog_RoverInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber);
static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData);
static void c2_emlrt_marshallIn(SFc2_QUARC_Prog_RoverInstanceStruct
  *chartInstance, const mxArray *c2_Euler, const char_T *c2_identifier, real_T
  c2_y[3]);
static void c2_b_emlrt_marshallIn(SFc2_QUARC_Prog_RoverInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[3]);
static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static real_T c2_c_emlrt_marshallIn(SFc2_QUARC_Prog_RoverInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_d_emlrt_marshallIn(SFc2_QUARC_Prog_RoverInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[4]);
static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_e_emlrt_marshallIn(SFc2_QUARC_Prog_RoverInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[3]);
static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static void c2_info_helper(c2_ResolvedFunctionInfo c2_info[38]);
static void c2_Quaternion(SFc2_QUARC_Prog_RoverInstanceStruct *chartInstance,
  real_T c2_S, real_T c2_V[3], real_T c2_Q[4]);
static void c2_eml_scalar_eg(SFc2_QUARC_Prog_RoverInstanceStruct *chartInstance);
static void c2_QuaternionProduct(SFc2_QUARC_Prog_RoverInstanceStruct
  *chartInstance, real_T c2_Q1[4], real_T c2_Q2[4], real_T c2_q[4]);
static void c2_b_eml_scalar_eg(SFc2_QUARC_Prog_RoverInstanceStruct
  *chartInstance);
static real_T c2_mpower(SFc2_QUARC_Prog_RoverInstanceStruct *chartInstance,
  real_T c2_a);
static real_T c2_atan2(SFc2_QUARC_Prog_RoverInstanceStruct *chartInstance,
  real_T c2_y, real_T c2_x);
static void c2_eml_error(SFc2_QUARC_Prog_RoverInstanceStruct *chartInstance);
static const mxArray *c2_e_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static int32_T c2_f_emlrt_marshallIn(SFc2_QUARC_Prog_RoverInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static uint8_T c2_g_emlrt_marshallIn(SFc2_QUARC_Prog_RoverInstanceStruct
  *chartInstance, const mxArray *c2_is_active_c2_QUARC_Prog_Rover, const char_T *
  c2_identifier);
static uint8_T c2_h_emlrt_marshallIn(SFc2_QUARC_Prog_RoverInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void init_dsm_address_info(SFc2_QUARC_Prog_RoverInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c2_QUARC_Prog_Rover(SFc2_QUARC_Prog_RoverInstanceStruct
  *chartInstance)
{
  int32_T *c2_sfEvent;
  uint8_T *c2_is_active_c2_QUARC_Prog_Rover;
  c2_is_active_c2_QUARC_Prog_Rover = (uint8_T *)ssGetDWork(chartInstance->S, 3);
  c2_sfEvent = (int32_T *)ssGetDWork(chartInstance->S, 0);
  *c2_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  *c2_is_active_c2_QUARC_Prog_Rover = 0U;
}

static void initialize_params_c2_QUARC_Prog_Rover
  (SFc2_QUARC_Prog_RoverInstanceStruct *chartInstance)
{
}

static void enable_c2_QUARC_Prog_Rover(SFc2_QUARC_Prog_RoverInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c2_QUARC_Prog_Rover(SFc2_QUARC_Prog_RoverInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c2_update_debugger_state_c2_QUARC_Prog_Rover
  (SFc2_QUARC_Prog_RoverInstanceStruct *chartInstance)
{
}

static void ext_mode_exec_c2_QUARC_Prog_Rover
  (SFc2_QUARC_Prog_RoverInstanceStruct *chartInstance)
{
  c2_update_debugger_state_c2_QUARC_Prog_Rover(chartInstance);
}

static const mxArray *get_sim_state_c2_QUARC_Prog_Rover
  (SFc2_QUARC_Prog_RoverInstanceStruct *chartInstance)
{
  const mxArray *c2_st;
  const mxArray *c2_y = NULL;
  int32_T c2_i0;
  real_T c2_u[3];
  const mxArray *c2_b_y = NULL;
  uint8_T c2_hoistedGlobal;
  uint8_T c2_b_u;
  const mxArray *c2_c_y = NULL;
  uint8_T *c2_is_active_c2_QUARC_Prog_Rover;
  real_T (*c2_Euler)[3];
  c2_Euler = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c2_is_active_c2_QUARC_Prog_Rover = (uint8_T *)ssGetDWork(chartInstance->S, 3);
  c2_st = NULL;
  c2_st = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_createcellarray(2), FALSE);
  for (c2_i0 = 0; c2_i0 < 3; c2_i0++) {
    c2_u[c2_i0] = (*c2_Euler)[c2_i0];
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 3, 1), FALSE);
  sf_mex_setcell(c2_y, 0, c2_b_y);
  c2_hoistedGlobal = *c2_is_active_c2_QUARC_Prog_Rover;
  c2_b_u = c2_hoistedGlobal;
  c2_c_y = NULL;
  sf_mex_assign(&c2_c_y, sf_mex_create("y", &c2_b_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c2_y, 1, c2_c_y);
  sf_mex_assign(&c2_st, c2_y, FALSE);
  return c2_st;
}

static void set_sim_state_c2_QUARC_Prog_Rover
  (SFc2_QUARC_Prog_RoverInstanceStruct *chartInstance, const mxArray *c2_st)
{
  const mxArray *c2_u;
  real_T c2_dv0[3];
  int32_T c2_i1;
  boolean_T *c2_doneDoubleBufferReInit;
  uint8_T *c2_is_active_c2_QUARC_Prog_Rover;
  real_T (*c2_Euler)[3];
  c2_Euler = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c2_is_active_c2_QUARC_Prog_Rover = (uint8_T *)ssGetDWork(chartInstance->S, 3);
  c2_doneDoubleBufferReInit = (boolean_T *)ssGetDWork(chartInstance->S, 2);
  *c2_doneDoubleBufferReInit = TRUE;
  c2_u = sf_mex_dup(c2_st);
  c2_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 0)),
                      "Euler", c2_dv0);
  for (c2_i1 = 0; c2_i1 < 3; c2_i1++) {
    (*c2_Euler)[c2_i1] = c2_dv0[c2_i1];
  }

  *c2_is_active_c2_QUARC_Prog_Rover = c2_g_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c2_u, 1)), "is_active_c2_QUARC_Prog_Rover");
  sf_mex_destroy(&c2_u);
  c2_update_debugger_state_c2_QUARC_Prog_Rover(chartInstance);
  sf_mex_destroy(&c2_st);
}

static void finalize_c2_QUARC_Prog_Rover(SFc2_QUARC_Prog_RoverInstanceStruct
  *chartInstance)
{
}

static void sf_c2_QUARC_Prog_Rover(SFc2_QUARC_Prog_RoverInstanceStruct
  *chartInstance)
{
  int32_T c2_i2;
  int32_T c2_i3;
  int32_T c2_i4;
  real_T c2_Angles[3];
  uint32_T c2_debug_family_var_map[14];
  real_T c2_ex[3];
  real_T c2_ey[3];
  real_T c2_ez[3];
  real_T c2_qx[4];
  real_T c2_qy[4];
  real_T c2_qz[4];
  real_T c2_Q[4];
  real_T c2_phi;
  real_T c2_theta;
  real_T c2_psi;
  real_T c2_nargin = 1.0;
  real_T c2_nargout = 1.0;
  real_T c2_Euler[3];
  int32_T c2_i5;
  int32_T c2_i6;
  static real_T c2_dv1[3] = { 1.0, 0.0, 0.0 };

  int32_T c2_i7;
  static real_T c2_dv2[3] = { 0.0, 1.0, 0.0 };

  int32_T c2_i8;
  static real_T c2_dv3[3] = { 0.0, 0.0, 1.0 };

  int32_T c2_i9;
  real_T c2_dv4[3];
  real_T c2_dv5[4];
  int32_T c2_i10;
  int32_T c2_i11;
  real_T c2_dv6[3];
  real_T c2_dv7[4];
  int32_T c2_i12;
  int32_T c2_i13;
  real_T c2_dv8[3];
  real_T c2_dv9[4];
  int32_T c2_i14;
  int32_T c2_i15;
  real_T c2_b_qy[4];
  int32_T c2_i16;
  real_T c2_b_qz[4];
  real_T c2_dv10[4];
  int32_T c2_i17;
  real_T c2_b_qx[4];
  int32_T c2_i18;
  real_T c2_dv11[4];
  real_T c2_dv12[4];
  int32_T c2_i19;
  int32_T c2_i20;
  real_T c2_b_Q[4];
  uint32_T c2_b_debug_family_var_map[6];
  real_T c2_b_nargin = 1.0;
  real_T c2_b_nargout = 3.0;
  real_T c2_b_phi;
  real_T c2_b_theta;
  real_T c2_b_psi;
  real_T c2_a;
  real_T c2_b;
  real_T c2_y;
  real_T c2_b_a;
  real_T c2_b_b;
  real_T c2_b_y;
  real_T c2_c_b;
  real_T c2_c_y;
  real_T c2_d_b;
  real_T c2_d_y;
  real_T c2_c_a;
  real_T c2_e_b;
  real_T c2_e_y;
  real_T c2_d_a;
  real_T c2_f_b;
  real_T c2_f_y;
  real_T c2_g_b;
  real_T c2_g_y;
  real_T c2_x;
  real_T c2_b_x;
  real_T c2_e_a;
  real_T c2_h_b;
  real_T c2_h_y;
  real_T c2_f_a;
  real_T c2_i_b;
  real_T c2_i_y;
  real_T c2_j_b;
  real_T c2_j_y;
  real_T c2_k_b;
  real_T c2_k_y;
  int32_T c2_i21;
  int32_T *c2_sfEvent;
  real_T (*c2_b_Euler)[3];
  real_T (*c2_b_Angles)[3];
  boolean_T guard1 = FALSE;
  c2_b_Euler = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c2_b_Angles = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
  c2_sfEvent = (int32_T *)ssGetDWork(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 1U, *c2_sfEvent);
  for (c2_i2 = 0; c2_i2 < 3; c2_i2++) {
    _SFD_DATA_RANGE_CHECK((*c2_b_Angles)[c2_i2], 0U);
  }

  for (c2_i3 = 0; c2_i3 < 3; c2_i3++) {
    _SFD_DATA_RANGE_CHECK((*c2_b_Euler)[c2_i3], 1U);
  }

  *c2_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 1U, *c2_sfEvent);
  for (c2_i4 = 0; c2_i4 < 3; c2_i4++) {
    c2_Angles[c2_i4] = (*c2_b_Angles)[c2_i4];
  }

  sf_debug_symbol_scope_push_eml(0U, 14U, 14U, c2_debug_family_names,
    c2_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(c2_ex, 0U, c2_d_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c2_ey, 1U, c2_d_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c2_ez, 2U, c2_d_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(c2_qx, 3U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_qy, 4U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_qz, 5U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_Q, 6U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_phi, 7U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_theta, 8U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_psi, 9U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargin, 10U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargout, 11U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml(c2_Angles, 12U, c2_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(c2_Euler, 13U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, *c2_sfEvent, 4);
  for (c2_i5 = 0; c2_i5 < 3; c2_i5++) {
    c2_Euler[c2_i5] = 0.0;
  }

  _SFD_EML_CALL(0U, *c2_sfEvent, 6);
  for (c2_i6 = 0; c2_i6 < 3; c2_i6++) {
    c2_ex[c2_i6] = c2_dv1[c2_i6];
  }

  _SFD_EML_CALL(0U, *c2_sfEvent, 7);
  for (c2_i7 = 0; c2_i7 < 3; c2_i7++) {
    c2_ey[c2_i7] = c2_dv2[c2_i7];
  }

  _SFD_EML_CALL(0U, *c2_sfEvent, 8);
  for (c2_i8 = 0; c2_i8 < 3; c2_i8++) {
    c2_ez[c2_i8] = c2_dv3[c2_i8];
  }

  _SFD_EML_CALL(0U, *c2_sfEvent, 10);
  for (c2_i9 = 0; c2_i9 < 3; c2_i9++) {
    c2_dv4[c2_i9] = c2_dv1[c2_i9];
  }

  c2_Quaternion(chartInstance, c2_Angles[0], c2_dv4, c2_dv5);
  for (c2_i10 = 0; c2_i10 < 4; c2_i10++) {
    c2_qx[c2_i10] = c2_dv5[c2_i10];
  }

  _SFD_EML_CALL(0U, *c2_sfEvent, 11);
  for (c2_i11 = 0; c2_i11 < 3; c2_i11++) {
    c2_dv6[c2_i11] = c2_dv2[c2_i11];
  }

  c2_Quaternion(chartInstance, c2_Angles[1], c2_dv6, c2_dv7);
  for (c2_i12 = 0; c2_i12 < 4; c2_i12++) {
    c2_qy[c2_i12] = c2_dv7[c2_i12];
  }

  _SFD_EML_CALL(0U, *c2_sfEvent, 12);
  for (c2_i13 = 0; c2_i13 < 3; c2_i13++) {
    c2_dv8[c2_i13] = c2_dv3[c2_i13];
  }

  c2_Quaternion(chartInstance, c2_Angles[2], c2_dv8, c2_dv9);
  for (c2_i14 = 0; c2_i14 < 4; c2_i14++) {
    c2_qz[c2_i14] = c2_dv9[c2_i14];
  }

  _SFD_EML_CALL(0U, *c2_sfEvent, 14);
  for (c2_i15 = 0; c2_i15 < 4; c2_i15++) {
    c2_b_qy[c2_i15] = c2_qy[c2_i15];
  }

  for (c2_i16 = 0; c2_i16 < 4; c2_i16++) {
    c2_b_qz[c2_i16] = c2_qz[c2_i16];
  }

  c2_QuaternionProduct(chartInstance, c2_b_qy, c2_b_qz, c2_dv10);
  for (c2_i17 = 0; c2_i17 < 4; c2_i17++) {
    c2_b_qx[c2_i17] = c2_qx[c2_i17];
  }

  for (c2_i18 = 0; c2_i18 < 4; c2_i18++) {
    c2_dv11[c2_i18] = c2_dv10[c2_i18];
  }

  c2_QuaternionProduct(chartInstance, c2_b_qx, c2_dv11, c2_dv12);
  for (c2_i19 = 0; c2_i19 < 4; c2_i19++) {
    c2_Q[c2_i19] = c2_dv12[c2_i19];
  }

  _SFD_EML_CALL(0U, *c2_sfEvent, 16);
  for (c2_i20 = 0; c2_i20 < 4; c2_i20++) {
    c2_b_Q[c2_i20] = c2_Q[c2_i20];
  }

  sf_debug_symbol_scope_push_eml(0U, 6U, 6U, c2_e_debug_family_names,
    c2_b_debug_family_var_map);
  sf_debug_symbol_scope_add_eml_importable(&c2_b_nargin, 0U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_b_nargout, 1U,
    c2_b_sf_marshallOut, c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_b_Q, 2U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_b_phi, 3U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_b_theta, 4U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_b_psi, 5U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  CV_SCRIPT_FCN(3, 0);
  _SFD_SCRIPT_CALL(3U, *c2_sfEvent, 26);
  c2_a = c2_b_Q[2];
  c2_b = c2_b_Q[3];
  c2_y = c2_a * c2_b;
  c2_b_a = c2_b_Q[0];
  c2_b_b = c2_b_Q[1];
  c2_b_y = c2_b_a * c2_b_b;
  c2_c_b = c2_y + c2_b_y;
  c2_c_y = 2.0 * c2_c_b;
  c2_d_b = c2_mpower(chartInstance, c2_b_Q[1]) + c2_mpower(chartInstance,
    c2_b_Q[2]);
  c2_d_y = 2.0 * c2_d_b;
  c2_b_phi = c2_atan2(chartInstance, c2_c_y, 1.0 - c2_d_y);
  _SFD_SCRIPT_CALL(3U, *c2_sfEvent, 27);
  c2_c_a = c2_b_Q[1];
  c2_e_b = c2_b_Q[3];
  c2_e_y = c2_c_a * c2_e_b;
  c2_d_a = c2_b_Q[0];
  c2_f_b = c2_b_Q[2];
  c2_f_y = c2_d_a * c2_f_b;
  c2_g_b = c2_e_y - c2_f_y;
  c2_g_y = 2.0 * c2_g_b;
  c2_x = c2_g_y;
  c2_b_x = c2_x;
  guard1 = FALSE;
  if (c2_b_x < -1.0) {
    guard1 = TRUE;
  } else {
    if (1.0 < c2_b_x) {
      guard1 = TRUE;
    }
  }

  if (guard1 == TRUE) {
    c2_eml_error(chartInstance);
  }

  c2_b_x = muDoubleScalarAsin(c2_b_x);
  c2_b_theta = -c2_b_x;
  _SFD_SCRIPT_CALL(3U, *c2_sfEvent, 28);
  c2_e_a = c2_b_Q[2];
  c2_h_b = c2_b_Q[1];
  c2_h_y = c2_e_a * c2_h_b;
  c2_f_a = c2_b_Q[0];
  c2_i_b = c2_b_Q[3];
  c2_i_y = c2_f_a * c2_i_b;
  c2_j_b = c2_h_y + c2_i_y;
  c2_j_y = 2.0 * c2_j_b;
  c2_k_b = c2_mpower(chartInstance, c2_b_Q[2]) + c2_mpower(chartInstance,
    c2_b_Q[3]);
  c2_k_y = 2.0 * c2_k_b;
  c2_b_psi = c2_atan2(chartInstance, c2_j_y, 1.0 - c2_k_y);
  _SFD_SCRIPT_CALL(3U, *c2_sfEvent, -28);
  sf_debug_symbol_scope_pop();
  c2_phi = c2_b_phi;
  c2_theta = c2_b_theta;
  c2_psi = c2_b_psi;
  _SFD_EML_CALL(0U, *c2_sfEvent, 17);
  c2_Euler[0] = c2_phi;
  _SFD_EML_CALL(0U, *c2_sfEvent, 18);
  c2_Euler[1] = c2_theta;
  _SFD_EML_CALL(0U, *c2_sfEvent, 19);
  c2_Euler[2] = c2_psi;
  _SFD_EML_CALL(0U, *c2_sfEvent, -19);
  sf_debug_symbol_scope_pop();
  for (c2_i21 = 0; c2_i21 < 3; c2_i21++) {
    (*c2_b_Euler)[c2_i21] = c2_Euler[c2_i21];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, *c2_sfEvent);
  sf_debug_check_for_state_inconsistency(_QUARC_Prog_RoverMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void initSimStructsc2_QUARC_Prog_Rover
  (SFc2_QUARC_Prog_RoverInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber)
{
  _SFD_SCRIPT_TRANSLATION(c2_chartNumber, 0U, sf_debug_get_script_id(
    "E:/TOOLBOX/RT_MaG/RT_MaG_ToolBox/MATLAB_RESSOURCES/TOOLS/MathTools/Rotation/Quaternion.m"));
  _SFD_SCRIPT_TRANSLATION(c2_chartNumber, 1U, sf_debug_get_script_id(
    "E:/TOOLBOX/RT_MaG/RT_MaG_ToolBox/MATLAB_RESSOURCES/TOOLS/MathTools/Rotation/UnitQuaternion.m"));
  _SFD_SCRIPT_TRANSLATION(c2_chartNumber, 2U, sf_debug_get_script_id(
    "E:/TOOLBOX/RT_MaG/RT_MaG_ToolBox/MATLAB_RESSOURCES/TOOLS/MathTools/Rotation/QuaternionProduct.m"));
  _SFD_SCRIPT_TRANSLATION(c2_chartNumber, 3U, sf_debug_get_script_id(
    "E:/TOOLBOX/RT_MaG/RT_MaG_ToolBox/MATLAB_RESSOURCES/TOOLS/MathTools/Rotation/Quaternion2Euler2.m"));
}

static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i22;
  real_T c2_b_inData[3];
  int32_T c2_i23;
  real_T c2_u[3];
  const mxArray *c2_y = NULL;
  SFc2_QUARC_Prog_RoverInstanceStruct *chartInstance;
  chartInstance = (SFc2_QUARC_Prog_RoverInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i22 = 0; c2_i22 < 3; c2_i22++) {
    c2_b_inData[c2_i22] = (*(real_T (*)[3])c2_inData)[c2_i22];
  }

  for (c2_i23 = 0; c2_i23 < 3; c2_i23++) {
    c2_u[c2_i23] = c2_b_inData[c2_i23];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 3, 1), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_emlrt_marshallIn(SFc2_QUARC_Prog_RoverInstanceStruct
  *chartInstance, const mxArray *c2_Euler, const char_T *c2_identifier, real_T
  c2_y[3])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_Euler), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_Euler);
}

static void c2_b_emlrt_marshallIn(SFc2_QUARC_Prog_RoverInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[3])
{
  real_T c2_dv13[3];
  int32_T c2_i24;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv13, 1, 0, 0U, 1, 0U, 2, 3, 1);
  for (c2_i24 = 0; c2_i24 < 3; c2_i24++) {
    c2_y[c2_i24] = c2_dv13[c2_i24];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_Euler;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[3];
  int32_T c2_i25;
  SFc2_QUARC_Prog_RoverInstanceStruct *chartInstance;
  chartInstance = (SFc2_QUARC_Prog_RoverInstanceStruct *)chartInstanceVoid;
  c2_Euler = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_Euler), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_Euler);
  for (c2_i25 = 0; c2_i25 < 3; c2_i25++) {
    (*(real_T (*)[3])c2_outData)[c2_i25] = c2_y[c2_i25];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  real_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_QUARC_Prog_RoverInstanceStruct *chartInstance;
  chartInstance = (SFc2_QUARC_Prog_RoverInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(real_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static real_T c2_c_emlrt_marshallIn(SFc2_QUARC_Prog_RoverInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  real_T c2_y;
  real_T c2_d0;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_d0, 1, 0, 0U, 0, 0U, 0);
  c2_y = c2_d0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_nargout;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y;
  SFc2_QUARC_Prog_RoverInstanceStruct *chartInstance;
  chartInstance = (SFc2_QUARC_Prog_RoverInstanceStruct *)chartInstanceVoid;
  c2_nargout = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_nargout), &c2_thisId);
  sf_mex_destroy(&c2_nargout);
  *(real_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i26;
  real_T c2_b_inData[4];
  int32_T c2_i27;
  real_T c2_u[4];
  const mxArray *c2_y = NULL;
  SFc2_QUARC_Prog_RoverInstanceStruct *chartInstance;
  chartInstance = (SFc2_QUARC_Prog_RoverInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i26 = 0; c2_i26 < 4; c2_i26++) {
    c2_b_inData[c2_i26] = (*(real_T (*)[4])c2_inData)[c2_i26];
  }

  for (c2_i27 = 0; c2_i27 < 4; c2_i27++) {
    c2_u[c2_i27] = c2_b_inData[c2_i27];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 1, 4), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_d_emlrt_marshallIn(SFc2_QUARC_Prog_RoverInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[4])
{
  real_T c2_dv14[4];
  int32_T c2_i28;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv14, 1, 0, 0U, 1, 0U, 1, 4);
  for (c2_i28 = 0; c2_i28 < 4; c2_i28++) {
    c2_y[c2_i28] = c2_dv14[c2_i28];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_Q;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[4];
  int32_T c2_i29;
  SFc2_QUARC_Prog_RoverInstanceStruct *chartInstance;
  chartInstance = (SFc2_QUARC_Prog_RoverInstanceStruct *)chartInstanceVoid;
  c2_Q = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_Q), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_Q);
  for (c2_i29 = 0; c2_i29 < 4; c2_i29++) {
    (*(real_T (*)[4])c2_outData)[c2_i29] = c2_y[c2_i29];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i30;
  real_T c2_b_inData[3];
  int32_T c2_i31;
  real_T c2_u[3];
  const mxArray *c2_y = NULL;
  SFc2_QUARC_Prog_RoverInstanceStruct *chartInstance;
  chartInstance = (SFc2_QUARC_Prog_RoverInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i30 = 0; c2_i30 < 3; c2_i30++) {
    c2_b_inData[c2_i30] = (*(real_T (*)[3])c2_inData)[c2_i30];
  }

  for (c2_i31 = 0; c2_i31 < 3; c2_i31++) {
    c2_u[c2_i31] = c2_b_inData[c2_i31];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_e_emlrt_marshallIn(SFc2_QUARC_Prog_RoverInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real_T c2_y[3])
{
  real_T c2_dv15[3];
  int32_T c2_i32;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv15, 1, 0, 0U, 1, 0U, 1, 3);
  for (c2_i32 = 0; c2_i32 < 3; c2_i32++) {
    c2_y[c2_i32] = c2_dv15[c2_i32];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_V;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[3];
  int32_T c2_i33;
  SFc2_QUARC_Prog_RoverInstanceStruct *chartInstance;
  chartInstance = (SFc2_QUARC_Prog_RoverInstanceStruct *)chartInstanceVoid;
  c2_V = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_V), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_V);
  for (c2_i33 = 0; c2_i33 < 3; c2_i33++) {
    (*(real_T (*)[3])c2_outData)[c2_i33] = c2_y[c2_i33];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

const mxArray *sf_c2_QUARC_Prog_Rover_get_eml_resolved_functions_info(void)
{
  const mxArray *c2_nameCaptureInfo;
  c2_ResolvedFunctionInfo c2_info[38];
  const mxArray *c2_m0 = NULL;
  int32_T c2_i34;
  c2_ResolvedFunctionInfo *c2_r0;
  c2_nameCaptureInfo = NULL;
  c2_nameCaptureInfo = NULL;
  c2_info_helper(c2_info);
  sf_mex_assign(&c2_m0, sf_mex_createstruct("nameCaptureInfo", 1, 38), FALSE);
  for (c2_i34 = 0; c2_i34 < 38; c2_i34++) {
    c2_r0 = &c2_info[c2_i34];
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c2_r0->context)), "context", "nameCaptureInfo",
                    c2_i34);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c2_r0->name)), "name", "nameCaptureInfo", c2_i34);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c2_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c2_i34);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c2_r0->resolved)), "resolved", "nameCaptureInfo",
                    c2_i34);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c2_i34);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c2_i34);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c2_i34);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c2_i34);
  }

  sf_mex_assign(&c2_nameCaptureInfo, c2_m0, FALSE);
  return c2_nameCaptureInfo;
}

static void c2_info_helper(c2_ResolvedFunctionInfo c2_info[38])
{
  c2_info[0].context = "";
  c2_info[0].name = "Quaternion";
  c2_info[0].dominantType = "double";
  c2_info[0].resolved =
    "[E]E:/TOOLBOX/RT_MaG/RT_MaG_ToolBox/MATLAB_RESSOURCES/TOOLS/MathTools/Rotation/Quaternion.m";
  c2_info[0].fileTimeLo = 1395830762U;
  c2_info[0].fileTimeHi = 0U;
  c2_info[0].mFileTimeLo = 0U;
  c2_info[0].mFileTimeHi = 0U;
  c2_info[1].context =
    "[E]E:/TOOLBOX/RT_MaG/RT_MaG_ToolBox/MATLAB_RESSOURCES/TOOLS/MathTools/Rotation/Quaternion.m";
  c2_info[1].name = "mrdivide";
  c2_info[1].dominantType = "double";
  c2_info[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c2_info[1].fileTimeLo = 1310137456U;
  c2_info[1].fileTimeHi = 0U;
  c2_info[1].mFileTimeLo = 1289519692U;
  c2_info[1].mFileTimeHi = 0U;
  c2_info[2].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c2_info[2].name = "rdivide";
  c2_info[2].dominantType = "double";
  c2_info[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c2_info[2].fileTimeLo = 1286818844U;
  c2_info[2].fileTimeHi = 0U;
  c2_info[2].mFileTimeLo = 0U;
  c2_info[2].mFileTimeHi = 0U;
  c2_info[3].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c2_info[3].name = "eml_div";
  c2_info[3].dominantType = "double";
  c2_info[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  c2_info[3].fileTimeLo = 1305318000U;
  c2_info[3].fileTimeHi = 0U;
  c2_info[3].mFileTimeLo = 0U;
  c2_info[3].mFileTimeHi = 0U;
  c2_info[4].context =
    "[E]E:/TOOLBOX/RT_MaG/RT_MaG_ToolBox/MATLAB_RESSOURCES/TOOLS/MathTools/Rotation/Quaternion.m";
  c2_info[4].name = "cos";
  c2_info[4].dominantType = "double";
  c2_info[4].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  c2_info[4].fileTimeLo = 1286818706U;
  c2_info[4].fileTimeHi = 0U;
  c2_info[4].mFileTimeLo = 0U;
  c2_info[4].mFileTimeHi = 0U;
  c2_info[5].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  c2_info[5].name = "eml_scalar_cos";
  c2_info[5].dominantType = "double";
  c2_info[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_cos.m";
  c2_info[5].fileTimeLo = 1286818722U;
  c2_info[5].fileTimeHi = 0U;
  c2_info[5].mFileTimeLo = 0U;
  c2_info[5].mFileTimeHi = 0U;
  c2_info[6].context =
    "[E]E:/TOOLBOX/RT_MaG/RT_MaG_ToolBox/MATLAB_RESSOURCES/TOOLS/MathTools/Rotation/Quaternion.m";
  c2_info[6].name = "sin";
  c2_info[6].dominantType = "double";
  c2_info[6].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m";
  c2_info[6].fileTimeLo = 1286818750U;
  c2_info[6].fileTimeHi = 0U;
  c2_info[6].mFileTimeLo = 0U;
  c2_info[6].mFileTimeHi = 0U;
  c2_info[7].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m";
  c2_info[7].name = "eml_scalar_sin";
  c2_info[7].dominantType = "double";
  c2_info[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sin.m";
  c2_info[7].fileTimeLo = 1286818736U;
  c2_info[7].fileTimeHi = 0U;
  c2_info[7].mFileTimeLo = 0U;
  c2_info[7].mFileTimeHi = 0U;
  c2_info[8].context =
    "[E]E:/TOOLBOX/RT_MaG/RT_MaG_ToolBox/MATLAB_RESSOURCES/TOOLS/MathTools/Rotation/Quaternion.m";
  c2_info[8].name = "mtimes";
  c2_info[8].dominantType = "double";
  c2_info[8].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c2_info[8].fileTimeLo = 1289519692U;
  c2_info[8].fileTimeHi = 0U;
  c2_info[8].mFileTimeLo = 0U;
  c2_info[8].mFileTimeHi = 0U;
  c2_info[9].context =
    "[E]E:/TOOLBOX/RT_MaG/RT_MaG_ToolBox/MATLAB_RESSOURCES/TOOLS/MathTools/Rotation/Quaternion.m";
  c2_info[9].name = "UnitQuaternion";
  c2_info[9].dominantType = "double";
  c2_info[9].resolved =
    "[E]E:/TOOLBOX/RT_MaG/RT_MaG_ToolBox/MATLAB_RESSOURCES/TOOLS/MathTools/Rotation/UnitQuaternion.m";
  c2_info[9].fileTimeLo = 1395830762U;
  c2_info[9].fileTimeHi = 0U;
  c2_info[9].mFileTimeLo = 0U;
  c2_info[9].mFileTimeHi = 0U;
  c2_info[10].context =
    "[E]E:/TOOLBOX/RT_MaG/RT_MaG_ToolBox/MATLAB_RESSOURCES/TOOLS/MathTools/Rotation/UnitQuaternion.m";
  c2_info[10].name = "norm";
  c2_info[10].dominantType = "double";
  c2_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m";
  c2_info[10].fileTimeLo = 1286818826U;
  c2_info[10].fileTimeHi = 0U;
  c2_info[10].mFileTimeLo = 0U;
  c2_info[10].mFileTimeHi = 0U;
  c2_info[11].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!genpnorm";
  c2_info[11].name = "eml_index_class";
  c2_info[11].dominantType = "";
  c2_info[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[11].fileTimeLo = 1286818778U;
  c2_info[11].fileTimeHi = 0U;
  c2_info[11].mFileTimeLo = 0U;
  c2_info[11].mFileTimeHi = 0U;
  c2_info[12].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!genpnorm";
  c2_info[12].name = "eml_xnrm2";
  c2_info[12].dominantType = "int32";
  c2_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xnrm2.m";
  c2_info[12].fileTimeLo = 1299076776U;
  c2_info[12].fileTimeHi = 0U;
  c2_info[12].mFileTimeLo = 0U;
  c2_info[12].mFileTimeHi = 0U;
  c2_info[13].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xnrm2.m";
  c2_info[13].name = "eml_blas_inline";
  c2_info[13].dominantType = "";
  c2_info[13].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c2_info[13].fileTimeLo = 1299076768U;
  c2_info[13].fileTimeHi = 0U;
  c2_info[13].mFileTimeLo = 0U;
  c2_info[13].mFileTimeHi = 0U;
  c2_info[14].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xnrm2.m";
  c2_info[14].name = "eml_refblas_xnrm2";
  c2_info[14].dominantType = "int32";
  c2_info[14].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c2_info[14].fileTimeLo = 1299076784U;
  c2_info[14].fileTimeHi = 0U;
  c2_info[14].mFileTimeLo = 0U;
  c2_info[14].mFileTimeHi = 0U;
  c2_info[15].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c2_info[15].name = "realmin";
  c2_info[15].dominantType = "char";
  c2_info[15].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmin.m";
  c2_info[15].fileTimeLo = 1286818768U;
  c2_info[15].fileTimeHi = 0U;
  c2_info[15].mFileTimeLo = 0U;
  c2_info[15].mFileTimeHi = 0U;
  c2_info[16].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmin.m";
  c2_info[16].name = "mpower";
  c2_info[16].dominantType = "double";
  c2_info[16].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m";
  c2_info[16].fileTimeLo = 1286818842U;
  c2_info[16].fileTimeHi = 0U;
  c2_info[16].mFileTimeLo = 0U;
  c2_info[16].mFileTimeHi = 0U;
  c2_info[17].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m";
  c2_info[17].name = "power";
  c2_info[17].dominantType = "double";
  c2_info[17].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  c2_info[17].fileTimeLo = 1294067944U;
  c2_info[17].fileTimeHi = 0U;
  c2_info[17].mFileTimeLo = 0U;
  c2_info[17].mFileTimeHi = 0U;
  c2_info[18].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  c2_info[18].name = "eml_scalar_eg";
  c2_info[18].dominantType = "double";
  c2_info[18].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c2_info[18].fileTimeLo = 1286818796U;
  c2_info[18].fileTimeHi = 0U;
  c2_info[18].mFileTimeLo = 0U;
  c2_info[18].mFileTimeHi = 0U;
  c2_info[19].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  c2_info[19].name = "eml_scalexp_alloc";
  c2_info[19].dominantType = "double";
  c2_info[19].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  c2_info[19].fileTimeLo = 1286818796U;
  c2_info[19].fileTimeHi = 0U;
  c2_info[19].mFileTimeLo = 0U;
  c2_info[19].mFileTimeHi = 0U;
  c2_info[20].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  c2_info[20].name = "eml_scalar_floor";
  c2_info[20].dominantType = "double";
  c2_info[20].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m";
  c2_info[20].fileTimeLo = 1286818726U;
  c2_info[20].fileTimeHi = 0U;
  c2_info[20].mFileTimeLo = 0U;
  c2_info[20].mFileTimeHi = 0U;
  c2_info[21].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c2_info[21].name = "eml_index_minus";
  c2_info[21].dominantType = "int32";
  c2_info[21].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c2_info[21].fileTimeLo = 1286818778U;
  c2_info[21].fileTimeHi = 0U;
  c2_info[21].mFileTimeLo = 0U;
  c2_info[21].mFileTimeHi = 0U;
  c2_info[22].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c2_info[22].name = "eml_index_times";
  c2_info[22].dominantType = "int32";
  c2_info[22].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c2_info[22].fileTimeLo = 1286818780U;
  c2_info[22].fileTimeHi = 0U;
  c2_info[22].mFileTimeLo = 0U;
  c2_info[22].mFileTimeHi = 0U;
  c2_info[23].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c2_info[23].name = "eml_index_plus";
  c2_info[23].dominantType = "int32";
  c2_info[23].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c2_info[23].fileTimeLo = 1286818778U;
  c2_info[23].fileTimeHi = 0U;
  c2_info[23].mFileTimeLo = 0U;
  c2_info[23].mFileTimeHi = 0U;
  c2_info[24].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c2_info[24].name = "abs";
  c2_info[24].dominantType = "double";
  c2_info[24].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c2_info[24].fileTimeLo = 1286818694U;
  c2_info[24].fileTimeHi = 0U;
  c2_info[24].mFileTimeLo = 0U;
  c2_info[24].mFileTimeHi = 0U;
  c2_info[25].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c2_info[25].name = "eml_scalar_abs";
  c2_info[25].dominantType = "double";
  c2_info[25].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m";
  c2_info[25].fileTimeLo = 1286818712U;
  c2_info[25].fileTimeHi = 0U;
  c2_info[25].mFileTimeLo = 0U;
  c2_info[25].mFileTimeHi = 0U;
  c2_info[26].context = "";
  c2_info[26].name = "QuaternionProduct";
  c2_info[26].dominantType = "double";
  c2_info[26].resolved =
    "[E]E:/TOOLBOX/RT_MaG/RT_MaG_ToolBox/MATLAB_RESSOURCES/TOOLS/MathTools/Rotation/QuaternionProduct.m";
  c2_info[26].fileTimeLo = 1395830762U;
  c2_info[26].fileTimeHi = 0U;
  c2_info[26].mFileTimeLo = 0U;
  c2_info[26].mFileTimeHi = 0U;
  c2_info[27].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c2_info[27].name = "eml_xdotu";
  c2_info[27].dominantType = "int32";
  c2_info[27].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdotu.m";
  c2_info[27].fileTimeLo = 1299076772U;
  c2_info[27].fileTimeHi = 0U;
  c2_info[27].mFileTimeLo = 0U;
  c2_info[27].mFileTimeHi = 0U;
  c2_info[28].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdotu.m";
  c2_info[28].name = "eml_xdot";
  c2_info[28].dominantType = "int32";
  c2_info[28].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdot.m";
  c2_info[28].fileTimeLo = 1299076772U;
  c2_info[28].fileTimeHi = 0U;
  c2_info[28].mFileTimeLo = 0U;
  c2_info[28].mFileTimeHi = 0U;
  c2_info[29].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xdot.m";
  c2_info[29].name = "eml_refblas_xdot";
  c2_info[29].dominantType = "int32";
  c2_info[29].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdot.m";
  c2_info[29].fileTimeLo = 1299076772U;
  c2_info[29].fileTimeHi = 0U;
  c2_info[29].mFileTimeLo = 0U;
  c2_info[29].mFileTimeHi = 0U;
  c2_info[30].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdot.m";
  c2_info[30].name = "eml_refblas_xdotx";
  c2_info[30].dominantType = "int32";
  c2_info[30].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  c2_info[30].fileTimeLo = 1299076774U;
  c2_info[30].fileTimeHi = 0U;
  c2_info[30].mFileTimeLo = 0U;
  c2_info[30].mFileTimeHi = 0U;
  c2_info[31].context =
    "[E]E:/TOOLBOX/RT_MaG/RT_MaG_ToolBox/MATLAB_RESSOURCES/TOOLS/MathTools/Rotation/QuaternionProduct.m";
  c2_info[31].name = "cross";
  c2_info[31].dominantType = "double";
  c2_info[31].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/specfun/cross.m";
  c2_info[31].fileTimeLo = 1286818842U;
  c2_info[31].fileTimeHi = 0U;
  c2_info[31].mFileTimeLo = 0U;
  c2_info[31].mFileTimeHi = 0U;
  c2_info[32].context = "";
  c2_info[32].name = "Quaternion2Euler2";
  c2_info[32].dominantType = "double";
  c2_info[32].resolved =
    "[E]E:/TOOLBOX/RT_MaG/RT_MaG_ToolBox/MATLAB_RESSOURCES/TOOLS/MathTools/Rotation/Quaternion2Euler2.m";
  c2_info[32].fileTimeLo = 1396943667U;
  c2_info[32].fileTimeHi = 0U;
  c2_info[32].mFileTimeLo = 0U;
  c2_info[32].mFileTimeHi = 0U;
  c2_info[33].context =
    "[E]E:/TOOLBOX/RT_MaG/RT_MaG_ToolBox/MATLAB_RESSOURCES/TOOLS/MathTools/Rotation/Quaternion2Euler2.m";
  c2_info[33].name = "atan2";
  c2_info[33].dominantType = "double";
  c2_info[33].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/atan2.m";
  c2_info[33].fileTimeLo = 1286818704U;
  c2_info[33].fileTimeHi = 0U;
  c2_info[33].mFileTimeLo = 0U;
  c2_info[33].mFileTimeHi = 0U;
  c2_info[34].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/atan2.m";
  c2_info[34].name = "eml_scalar_atan2";
  c2_info[34].dominantType = "double";
  c2_info[34].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_atan2.m";
  c2_info[34].fileTimeLo = 1286818720U;
  c2_info[34].fileTimeHi = 0U;
  c2_info[34].mFileTimeLo = 0U;
  c2_info[34].mFileTimeHi = 0U;
  c2_info[35].context =
    "[E]E:/TOOLBOX/RT_MaG/RT_MaG_ToolBox/MATLAB_RESSOURCES/TOOLS/MathTools/Rotation/Quaternion2Euler2.m";
  c2_info[35].name = "asin";
  c2_info[35].dominantType = "double";
  c2_info[35].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/asin.m";
  c2_info[35].fileTimeLo = 1286818702U;
  c2_info[35].fileTimeHi = 0U;
  c2_info[35].mFileTimeLo = 0U;
  c2_info[35].mFileTimeHi = 0U;
  c2_info[36].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/asin.m";
  c2_info[36].name = "eml_error";
  c2_info[36].dominantType = "char";
  c2_info[36].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_error.m";
  c2_info[36].fileTimeLo = 1305318000U;
  c2_info[36].fileTimeHi = 0U;
  c2_info[36].mFileTimeLo = 0U;
  c2_info[36].mFileTimeHi = 0U;
  c2_info[37].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/asin.m";
  c2_info[37].name = "eml_scalar_asin";
  c2_info[37].dominantType = "double";
  c2_info[37].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_asin.m";
  c2_info[37].fileTimeLo = 1286818716U;
  c2_info[37].fileTimeHi = 0U;
  c2_info[37].mFileTimeLo = 0U;
  c2_info[37].mFileTimeHi = 0U;
}

static void c2_Quaternion(SFc2_QUARC_Prog_RoverInstanceStruct *chartInstance,
  real_T c2_S, real_T c2_V[3], real_T c2_Q[4])
{
  uint32_T c2_debug_family_var_map[5];
  real_T c2_nargin = 2.0;
  real_T c2_nargout = 1.0;
  real_T c2_A;
  real_T c2_x;
  real_T c2_b_x;
  real_T c2_y;
  real_T c2_c_x;
  real_T c2_d_x;
  real_T c2_b_A;
  real_T c2_e_x;
  real_T c2_f_x;
  real_T c2_b_y;
  real_T c2_g_x;
  real_T c2_h_x;
  real_T c2_a;
  int32_T c2_i35;
  real_T c2_b[3];
  int32_T c2_i36;
  real_T c2_b_Q[4];
  int32_T c2_i37;
  uint32_T c2_b_debug_family_var_map[4];
  real_T c2_b_nargin = 1.0;
  real_T c2_b_nargout = 1.0;
  int32_T c2_i38;
  real_T c2_i_x[4];
  real_T c2_c_y;
  real_T c2_scale;
  int32_T c2_k;
  int32_T c2_b_k;
  real_T c2_j_x;
  real_T c2_k_x;
  real_T c2_absxk;
  real_T c2_t;
  int32_T c2_i39;
  real_T c2_B;
  real_T c2_d_y;
  real_T c2_e_y;
  int32_T c2_i40;
  int32_T *c2_sfEvent;
  c2_sfEvent = (int32_T *)ssGetDWork(chartInstance->S, 0);
  sf_debug_symbol_scope_push_eml(0U, 5U, 5U, c2_c_debug_family_names,
    c2_debug_family_var_map);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargin, 0U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargout, 1U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_S, 2U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_V, 3U, c2_d_sf_marshallOut,
    c2_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_Q, 4U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  CV_SCRIPT_FCN(0, 0);
  _SFD_SCRIPT_CALL(0U, *c2_sfEvent, 48);
  c2_A = c2_S;
  c2_x = c2_A;
  c2_b_x = c2_x;
  c2_y = c2_b_x / 2.0;
  c2_c_x = c2_y;
  c2_d_x = c2_c_x;
  c2_d_x = muDoubleScalarCos(c2_d_x);
  c2_b_A = c2_S;
  c2_e_x = c2_b_A;
  c2_f_x = c2_e_x;
  c2_b_y = c2_f_x / 2.0;
  c2_g_x = c2_b_y;
  c2_h_x = c2_g_x;
  c2_h_x = muDoubleScalarSin(c2_h_x);
  c2_a = c2_h_x;
  for (c2_i35 = 0; c2_i35 < 3; c2_i35++) {
    c2_b[c2_i35] = c2_V[c2_i35];
  }

  for (c2_i36 = 0; c2_i36 < 3; c2_i36++) {
    c2_b[c2_i36] *= c2_a;
  }

  c2_b_Q[0] = c2_d_x;
  for (c2_i37 = 0; c2_i37 < 3; c2_i37++) {
    c2_b_Q[c2_i37 + 1] = c2_b[c2_i37];
  }

  sf_debug_symbol_scope_push_eml(0U, 4U, 4U, c2_b_debug_family_names,
    c2_b_debug_family_var_map);
  sf_debug_symbol_scope_add_eml_importable(&c2_b_nargin, 0U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_b_nargout, 1U,
    c2_b_sf_marshallOut, c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_b_Q, 2U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_Q, 3U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  CV_SCRIPT_FCN(1, 0);
  _SFD_SCRIPT_CALL(1U, *c2_sfEvent, 44);
  for (c2_i38 = 0; c2_i38 < 4; c2_i38++) {
    c2_i_x[c2_i38] = c2_b_Q[c2_i38];
  }

  c2_c_y = 0.0;
  c2_scale = 2.2250738585072014E-308;
  for (c2_k = 1; c2_k < 5; c2_k++) {
    c2_b_k = c2_k;
    c2_j_x = c2_i_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
      "", (real_T)c2_b_k), 1, 4, 1, 0) - 1];
    c2_k_x = c2_j_x;
    c2_absxk = muDoubleScalarAbs(c2_k_x);
    if (c2_absxk > c2_scale) {
      c2_t = c2_scale / c2_absxk;
      c2_c_y = 1.0 + c2_c_y * c2_t * c2_t;
      c2_scale = c2_absxk;
    } else {
      c2_t = c2_absxk / c2_scale;
      c2_c_y += c2_t * c2_t;
    }
  }

  c2_c_y = c2_scale * muDoubleScalarSqrt(c2_c_y);
  for (c2_i39 = 0; c2_i39 < 4; c2_i39++) {
    c2_i_x[c2_i39] = c2_b_Q[c2_i39];
  }

  c2_B = c2_c_y;
  c2_d_y = c2_B;
  c2_e_y = c2_d_y;
  for (c2_i40 = 0; c2_i40 < 4; c2_i40++) {
    c2_Q[c2_i40] = c2_i_x[c2_i40] / c2_e_y;
  }

  _SFD_SCRIPT_CALL(1U, *c2_sfEvent, -44);
  sf_debug_symbol_scope_pop();
  _SFD_SCRIPT_CALL(0U, *c2_sfEvent, -48);
  sf_debug_symbol_scope_pop();
}

static void c2_eml_scalar_eg(SFc2_QUARC_Prog_RoverInstanceStruct *chartInstance)
{
}

static void c2_QuaternionProduct(SFc2_QUARC_Prog_RoverInstanceStruct
  *chartInstance, real_T c2_Q1[4], real_T c2_Q2[4], real_T c2_q[4])
{
  uint32_T c2_debug_family_var_map[9];
  real_T c2_s1;
  real_T c2_s2;
  real_T c2_v1[3];
  real_T c2_v2[3];
  real_T c2_nargin = 2.0;
  real_T c2_nargout = 1.0;
  int32_T c2_i41;
  int32_T c2_i42;
  real_T c2_a;
  real_T c2_b;
  real_T c2_y;
  int32_T c2_i43;
  real_T c2_b_a[3];
  int32_T c2_i44;
  real_T c2_b_b[3];
  real_T c2_b_y;
  int32_T c2_k;
  int32_T c2_b_k;
  real_T c2_c_a;
  int32_T c2_i45;
  int32_T c2_i46;
  real_T c2_d_a;
  int32_T c2_i47;
  real_T c2_c_b[3];
  int32_T c2_i48;
  int32_T c2_i49;
  real_T c2_e_a[3];
  int32_T c2_i50;
  real_T c2_d_b[3];
  real_T c2_f_a;
  real_T c2_e_b;
  real_T c2_c_y;
  real_T c2_g_a;
  real_T c2_f_b;
  real_T c2_d_y;
  real_T c2_c1;
  real_T c2_h_a;
  real_T c2_g_b;
  real_T c2_e_y;
  real_T c2_i_a;
  real_T c2_h_b;
  real_T c2_f_y;
  real_T c2_c2;
  real_T c2_j_a;
  real_T c2_i_b;
  real_T c2_g_y;
  real_T c2_k_a;
  real_T c2_j_b;
  real_T c2_h_y;
  real_T c2_c3;
  int32_T c2_i51;
  int32_T *c2_sfEvent;
  c2_sfEvent = (int32_T *)ssGetDWork(chartInstance->S, 0);
  sf_debug_symbol_scope_push_eml(0U, 9U, 9U, c2_d_debug_family_names,
    c2_debug_family_var_map);
  sf_debug_symbol_scope_add_eml_importable(&c2_s1, 0U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_s2, 1U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_v1, 2U, c2_d_sf_marshallOut,
    c2_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_v2, 3U, c2_d_sf_marshallOut,
    c2_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargin, 4U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargout, 5U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_Q1, 6U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_Q2, 7U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_q, 8U, c2_c_sf_marshallOut,
    c2_c_sf_marshallIn);
  CV_SCRIPT_FCN(2, 0);
  _SFD_SCRIPT_CALL(2U, *c2_sfEvent, 44);
  c2_s1 = c2_Q1[0];
  _SFD_SCRIPT_CALL(2U, *c2_sfEvent, 44);
  c2_s2 = c2_Q2[0];
  _SFD_SCRIPT_CALL(2U, *c2_sfEvent, 45);
  for (c2_i41 = 0; c2_i41 < 3; c2_i41++) {
    c2_v1[c2_i41] = c2_Q1[c2_i41 + 1];
  }

  _SFD_SCRIPT_CALL(2U, *c2_sfEvent, 45);
  for (c2_i42 = 0; c2_i42 < 3; c2_i42++) {
    c2_v2[c2_i42] = c2_Q2[c2_i42 + 1];
  }

  _SFD_SCRIPT_CALL(2U, *c2_sfEvent, 47);
  c2_a = c2_s1;
  c2_b = c2_s2;
  c2_y = c2_a * c2_b;
  for (c2_i43 = 0; c2_i43 < 3; c2_i43++) {
    c2_b_a[c2_i43] = c2_v1[c2_i43];
  }

  for (c2_i44 = 0; c2_i44 < 3; c2_i44++) {
    c2_b_b[c2_i44] = c2_v2[c2_i44];
  }

  c2_b_eml_scalar_eg(chartInstance);
  c2_b_eml_scalar_eg(chartInstance);
  c2_b_y = 0.0;
  for (c2_k = 1; c2_k < 4; c2_k++) {
    c2_b_k = c2_k;
    c2_b_y += c2_b_a[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK
      ("", (real_T)c2_b_k), 1, 3, 1, 0) - 1] *
      c2_b_b[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c2_b_k), 1, 3, 1, 0) - 1];
  }

  c2_c_a = c2_s1;
  for (c2_i45 = 0; c2_i45 < 3; c2_i45++) {
    c2_b_b[c2_i45] = c2_v2[c2_i45];
  }

  for (c2_i46 = 0; c2_i46 < 3; c2_i46++) {
    c2_b_b[c2_i46] *= c2_c_a;
  }

  c2_d_a = c2_s2;
  for (c2_i47 = 0; c2_i47 < 3; c2_i47++) {
    c2_c_b[c2_i47] = c2_v1[c2_i47];
  }

  for (c2_i48 = 0; c2_i48 < 3; c2_i48++) {
    c2_c_b[c2_i48] *= c2_d_a;
  }

  for (c2_i49 = 0; c2_i49 < 3; c2_i49++) {
    c2_e_a[c2_i49] = c2_v1[c2_i49];
  }

  for (c2_i50 = 0; c2_i50 < 3; c2_i50++) {
    c2_d_b[c2_i50] = c2_v2[c2_i50];
  }

  c2_f_a = c2_e_a[1];
  c2_e_b = c2_d_b[2];
  c2_c_y = c2_f_a * c2_e_b;
  c2_g_a = c2_e_a[2];
  c2_f_b = c2_d_b[1];
  c2_d_y = c2_g_a * c2_f_b;
  c2_c1 = c2_c_y - c2_d_y;
  c2_h_a = c2_e_a[2];
  c2_g_b = c2_d_b[0];
  c2_e_y = c2_h_a * c2_g_b;
  c2_i_a = c2_e_a[0];
  c2_h_b = c2_d_b[2];
  c2_f_y = c2_i_a * c2_h_b;
  c2_c2 = c2_e_y - c2_f_y;
  c2_j_a = c2_e_a[0];
  c2_i_b = c2_d_b[1];
  c2_g_y = c2_j_a * c2_i_b;
  c2_k_a = c2_e_a[1];
  c2_j_b = c2_d_b[0];
  c2_h_y = c2_k_a * c2_j_b;
  c2_c3 = c2_g_y - c2_h_y;
  c2_e_a[0] = c2_c1;
  c2_e_a[1] = c2_c2;
  c2_e_a[2] = c2_c3;
  c2_q[0] = c2_y - c2_b_y;
  for (c2_i51 = 0; c2_i51 < 3; c2_i51++) {
    c2_q[c2_i51 + 1] = (c2_b_b[c2_i51] + c2_c_b[c2_i51]) + c2_e_a[c2_i51];
  }

  _SFD_SCRIPT_CALL(2U, *c2_sfEvent, -47);
  sf_debug_symbol_scope_pop();
}

static void c2_b_eml_scalar_eg(SFc2_QUARC_Prog_RoverInstanceStruct
  *chartInstance)
{
}

static real_T c2_mpower(SFc2_QUARC_Prog_RoverInstanceStruct *chartInstance,
  real_T c2_a)
{
  real_T c2_b_a;
  real_T c2_ak;
  c2_b_a = c2_a;
  c2_eml_scalar_eg(chartInstance);
  c2_ak = c2_b_a;
  return muDoubleScalarPower(c2_ak, 2.0);
}

static real_T c2_atan2(SFc2_QUARC_Prog_RoverInstanceStruct *chartInstance,
  real_T c2_y, real_T c2_x)
{
  real_T c2_b_y;
  real_T c2_b_x;
  c2_eml_scalar_eg(chartInstance);
  c2_b_y = c2_y;
  c2_b_x = c2_x;
  return muDoubleScalarAtan2(c2_b_y, c2_b_x);
}

static void c2_eml_error(SFc2_QUARC_Prog_RoverInstanceStruct *chartInstance)
{
  int32_T c2_i52;
  static char_T c2_varargin_1[30] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o',
    'o', 'l', 'b', 'o', 'x', ':', 'a', 's', 'i', 'n', '_', 'd', 'o', 'm', 'a',
    'i', 'n', 'E', 'r', 'r', 'o', 'r' };

  char_T c2_u[30];
  const mxArray *c2_y = NULL;
  for (c2_i52 = 0; c2_i52 < 30; c2_i52++) {
    c2_u[c2_i52] = c2_varargin_1[c2_i52];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 10, 0U, 1U, 0U, 2, 1, 30), FALSE);
  sf_mex_call_debug("error", 0U, 1U, 14, sf_mex_call_debug("message", 1U, 1U, 14,
    c2_y));
}

static const mxArray *c2_e_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_QUARC_Prog_RoverInstanceStruct *chartInstance;
  chartInstance = (SFc2_QUARC_Prog_RoverInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(int32_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static int32_T c2_f_emlrt_marshallIn(SFc2_QUARC_Prog_RoverInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  int32_T c2_y;
  int32_T c2_i53;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_i53, 1, 6, 0U, 0, 0U, 0);
  c2_y = c2_i53;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_sfEvent;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  int32_T c2_y;
  SFc2_QUARC_Prog_RoverInstanceStruct *chartInstance;
  chartInstance = (SFc2_QUARC_Prog_RoverInstanceStruct *)chartInstanceVoid;
  c2_sfEvent = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_sfEvent), &c2_thisId);
  sf_mex_destroy(&c2_sfEvent);
  *(int32_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static uint8_T c2_g_emlrt_marshallIn(SFc2_QUARC_Prog_RoverInstanceStruct
  *chartInstance, const mxArray *c2_is_active_c2_QUARC_Prog_Rover, const char_T *
  c2_identifier)
{
  uint8_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_h_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c2_is_active_c2_QUARC_Prog_Rover), &c2_thisId);
  sf_mex_destroy(&c2_is_active_c2_QUARC_Prog_Rover);
  return c2_y;
}

static uint8_T c2_h_emlrt_marshallIn(SFc2_QUARC_Prog_RoverInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  uint8_T c2_u0;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_u0, 1, 3, 0U, 0, 0U, 0);
  c2_y = c2_u0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void init_dsm_address_info(SFc2_QUARC_Prog_RoverInstanceStruct
  *chartInstance)
{
}

/* SFunction Glue Code */
static uint32_T* sf_get_sfun_dwork_checksum();
void sf_c2_QUARC_Prog_Rover_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2402999952U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3150838758U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1059348237U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1558418511U);
}

mxArray *sf_c2_QUARC_Prog_Rover_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("SX4Hv2xdyk0cE1epuN6MxE");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
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

static const mxArray *sf_get_sim_state_info_c2_QUARC_Prog_Rover(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[11],T\"Euler\",},{M[8],M[0],T\"is_active_c2_QUARC_Prog_Rover\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c2_QUARC_Prog_Rover_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc2_QUARC_Prog_RoverInstanceStruct *chartInstance;
    chartInstance = (SFc2_QUARC_Prog_RoverInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (_QUARC_Prog_RoverMachineNumber_,
           2,
           1,
           1,
           2,
           0,
           0,
           0,
           0,
           4,
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
          _SFD_SET_DATA_PROPS(0,1,1,0,"Angles");
          _SFD_SET_DATA_PROPS(1,2,0,1,"Euler");
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
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,440);
        _SFD_CV_INIT_SCRIPT(0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_SCRIPT_FCN(0,0,"Quaternion",1565,-1,1666);
        _SFD_CV_INIT_SCRIPT(1,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_SCRIPT_FCN(1,0,"UnitQuaternion",1352,-1,1433);
        _SFD_CV_INIT_SCRIPT(2,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_SCRIPT_FCN(2,0,"QuaternionProduct",1401,-1,1632);
        _SFD_CV_INIT_SCRIPT(3,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_SCRIPT_FCN(3,0,"Quaternion2Euler2",827,-1,1077);
        _SFD_TRANS_COV_WTS(0,0,0,1,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(0,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              1,NULL,NULL,
                              0,NULL,NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 3;
          dimVector[1]= 1;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 3;
          dimVector[1]= 1;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)
            c2_sf_marshallIn);
        }

        {
          real_T (*c2_Angles)[3];
          real_T (*c2_Euler)[3];
          c2_Euler = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
          c2_Angles = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c2_Angles);
          _SFD_SET_DATA_VALUE_PTR(1U, *c2_Euler);
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
      2, "dworkChecksum");
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

static void sf_opaque_initialize_c2_QUARC_Prog_Rover(void *chartInstanceVar)
{
  sf_check_dwork_consistency(((SFc2_QUARC_Prog_RoverInstanceStruct*)
    chartInstanceVar)->S);
  chart_debug_initialization(((SFc2_QUARC_Prog_RoverInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c2_QUARC_Prog_Rover((SFc2_QUARC_Prog_RoverInstanceStruct*)
    chartInstanceVar);
  initialize_c2_QUARC_Prog_Rover((SFc2_QUARC_Prog_RoverInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c2_QUARC_Prog_Rover(void *chartInstanceVar)
{
  enable_c2_QUARC_Prog_Rover((SFc2_QUARC_Prog_RoverInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c2_QUARC_Prog_Rover(void *chartInstanceVar)
{
  disable_c2_QUARC_Prog_Rover((SFc2_QUARC_Prog_RoverInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c2_QUARC_Prog_Rover(void *chartInstanceVar)
{
  sf_c2_QUARC_Prog_Rover((SFc2_QUARC_Prog_RoverInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_ext_mode_exec_c2_QUARC_Prog_Rover(void *chartInstanceVar)
{
  ext_mode_exec_c2_QUARC_Prog_Rover((SFc2_QUARC_Prog_RoverInstanceStruct*)
    chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c2_QUARC_Prog_Rover(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c2_QUARC_Prog_Rover
    ((SFc2_QUARC_Prog_RoverInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c2_QUARC_Prog_Rover();/* state var info */
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

extern void sf_internal_set_sim_state_c2_QUARC_Prog_Rover(SimStruct* S, const
  mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c2_QUARC_Prog_Rover();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c2_QUARC_Prog_Rover((SFc2_QUARC_Prog_RoverInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c2_QUARC_Prog_Rover(SimStruct* S)
{
  return sf_internal_get_sim_state_c2_QUARC_Prog_Rover(S);
}

static void sf_opaque_set_sim_state_c2_QUARC_Prog_Rover(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c2_QUARC_Prog_Rover(S, st);
}

static void sf_opaque_terminate_c2_QUARC_Prog_Rover(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc2_QUARC_Prog_RoverInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
    }

    finalize_c2_QUARC_Prog_Rover((SFc2_QUARC_Prog_RoverInstanceStruct*)
      chartInstanceVar);
    free((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }

  unload_QUARC_Prog_Rover_optimization_info();
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc2_QUARC_Prog_Rover((SFc2_QUARC_Prog_RoverInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c2_QUARC_Prog_Rover(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c2_QUARC_Prog_Rover((SFc2_QUARC_Prog_RoverInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

mxArray *sf_c2_QUARC_Prog_Rover_get_testpoint_info(void)
{
  const char *infoEncStr[] = {
    "100 S'varName','path'{{T\"is_active_c2_QUARC_Prog_Rover\",T\"is_active_c2_QUARC_Prog_Rover\"}}"
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

static void mdlSetWorkWidths_c2_QUARC_Prog_Rover(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_QUARC_Prog_Rover_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,infoStruct,2);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,infoStruct,2,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,infoStruct,2,
      "gatewayCannotBeInlinedMultipleTimes"));
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,infoStruct,2,1);
      sf_mark_chart_reusable_outputs(S,infoStruct,2,1);
    }

    sf_set_rtw_dwork_info(S,infoStruct,2);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
    sf_set_sfun_dwork_info(S);
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(1508538265U));
  ssSetChecksum1(S,(3860925910U));
  ssSetChecksum2(S,(1098577485U));
  ssSetChecksum3(S,(3316198808U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
}

static void mdlRTW_c2_QUARC_Prog_Rover(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c2_QUARC_Prog_Rover(SimStruct *S)
{
  SFc2_QUARC_Prog_RoverInstanceStruct *chartInstance;
  chartInstance = (SFc2_QUARC_Prog_RoverInstanceStruct *)malloc(sizeof
    (SFc2_QUARC_Prog_RoverInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc2_QUARC_Prog_RoverInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c2_QUARC_Prog_Rover;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c2_QUARC_Prog_Rover;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c2_QUARC_Prog_Rover;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c2_QUARC_Prog_Rover;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c2_QUARC_Prog_Rover;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c2_QUARC_Prog_Rover;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c2_QUARC_Prog_Rover;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c2_QUARC_Prog_Rover;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c2_QUARC_Prog_Rover;
  chartInstance->chartInfo.mdlStart = mdlStart_c2_QUARC_Prog_Rover;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c2_QUARC_Prog_Rover;
  chartInstance->chartInfo.extModeExec =
    sf_opaque_ext_mode_exec_c2_QUARC_Prog_Rover;
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

void c2_QUARC_Prog_Rover_method_dispatcher(SimStruct *S, int_T method, void
  *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c2_QUARC_Prog_Rover(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c2_QUARC_Prog_Rover(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c2_QUARC_Prog_Rover(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c2_QUARC_Prog_Rover_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
