/* Include files */

#include "blascompat32.h"
#include "QUARC_Prog_Rover_sfun.h"
#include "c1_QUARC_Prog_Rover.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "QUARC_Prog_Rover_sfun_debug_macros.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
static const char * c1_debug_family_names[14] = { "ex", "ey", "ez", "qx", "qy",
  "qz", "Q", "phi", "theta", "psi", "nargin", "nargout", "Angles", "Euler" };

static const char * c1_b_debug_family_names[4] = { "nargin", "nargout", "Q",
  "Qn" };

static const char * c1_c_debug_family_names[5] = { "nargin", "nargout", "S", "V",
  "Q" };

static const char * c1_d_debug_family_names[9] = { "s1", "s2", "v1", "v2",
  "nargin", "nargout", "Q1", "Q2", "q" };

static const char * c1_e_debug_family_names[6] = { "nargin", "nargout", "Q",
  "PHI", "THETA", "PSI" };

/* Function Declarations */
static void initialize_c1_QUARC_Prog_Rover(SFc1_QUARC_Prog_RoverInstanceStruct
  *chartInstance);
static void initialize_params_c1_QUARC_Prog_Rover
  (SFc1_QUARC_Prog_RoverInstanceStruct *chartInstance);
static void enable_c1_QUARC_Prog_Rover(SFc1_QUARC_Prog_RoverInstanceStruct
  *chartInstance);
static void disable_c1_QUARC_Prog_Rover(SFc1_QUARC_Prog_RoverInstanceStruct
  *chartInstance);
static void c1_update_debugger_state_c1_QUARC_Prog_Rover
  (SFc1_QUARC_Prog_RoverInstanceStruct *chartInstance);
static void ext_mode_exec_c1_QUARC_Prog_Rover
  (SFc1_QUARC_Prog_RoverInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c1_QUARC_Prog_Rover
  (SFc1_QUARC_Prog_RoverInstanceStruct *chartInstance);
static void set_sim_state_c1_QUARC_Prog_Rover
  (SFc1_QUARC_Prog_RoverInstanceStruct *chartInstance, const mxArray *c1_st);
static void finalize_c1_QUARC_Prog_Rover(SFc1_QUARC_Prog_RoverInstanceStruct
  *chartInstance);
static void sf_c1_QUARC_Prog_Rover(SFc1_QUARC_Prog_RoverInstanceStruct
  *chartInstance);
static void initSimStructsc1_QUARC_Prog_Rover
  (SFc1_QUARC_Prog_RoverInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber);
static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData);
static void c1_emlrt_marshallIn(SFc1_QUARC_Prog_RoverInstanceStruct
  *chartInstance, const mxArray *c1_Euler, const char_T *c1_identifier, real_T
  c1_y[3]);
static void c1_b_emlrt_marshallIn(SFc1_QUARC_Prog_RoverInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId,
  real_T c1_y[3]);
static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static real_T c1_c_emlrt_marshallIn(SFc1_QUARC_Prog_RoverInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_d_emlrt_marshallIn(SFc1_QUARC_Prog_RoverInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId,
  real_T c1_y[4]);
static void c1_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_d_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_e_emlrt_marshallIn(SFc1_QUARC_Prog_RoverInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId,
  real_T c1_y[3]);
static void c1_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static void c1_info_helper(c1_ResolvedFunctionInfo c1_info[38]);
static void c1_Quaternion(SFc1_QUARC_Prog_RoverInstanceStruct *chartInstance,
  real_T c1_S, real_T c1_V[3], real_T c1_Q[4]);
static void c1_eml_scalar_eg(SFc1_QUARC_Prog_RoverInstanceStruct *chartInstance);
static void c1_QuaternionProduct(SFc1_QUARC_Prog_RoverInstanceStruct
  *chartInstance, real_T c1_Q1[4], real_T c1_Q2[4], real_T c1_q[4]);
static void c1_b_eml_scalar_eg(SFc1_QUARC_Prog_RoverInstanceStruct
  *chartInstance);
static real_T c1_mpower(SFc1_QUARC_Prog_RoverInstanceStruct *chartInstance,
  real_T c1_a);
static real_T c1_atan2(SFc1_QUARC_Prog_RoverInstanceStruct *chartInstance,
  real_T c1_y, real_T c1_x);
static void c1_eml_error(SFc1_QUARC_Prog_RoverInstanceStruct *chartInstance);
static const mxArray *c1_e_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static int32_T c1_f_emlrt_marshallIn(SFc1_QUARC_Prog_RoverInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static uint8_T c1_g_emlrt_marshallIn(SFc1_QUARC_Prog_RoverInstanceStruct
  *chartInstance, const mxArray *c1_is_active_c1_QUARC_Prog_Rover, const char_T *
  c1_identifier);
static uint8_T c1_h_emlrt_marshallIn(SFc1_QUARC_Prog_RoverInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void init_dsm_address_info(SFc1_QUARC_Prog_RoverInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c1_QUARC_Prog_Rover(SFc1_QUARC_Prog_RoverInstanceStruct
  *chartInstance)
{
  int32_T *c1_sfEvent;
  uint8_T *c1_is_active_c1_QUARC_Prog_Rover;
  c1_is_active_c1_QUARC_Prog_Rover = (uint8_T *)ssGetDWork(chartInstance->S, 3);
  c1_sfEvent = (int32_T *)ssGetDWork(chartInstance->S, 0);
  *c1_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  *c1_is_active_c1_QUARC_Prog_Rover = 0U;
}

static void initialize_params_c1_QUARC_Prog_Rover
  (SFc1_QUARC_Prog_RoverInstanceStruct *chartInstance)
{
}

static void enable_c1_QUARC_Prog_Rover(SFc1_QUARC_Prog_RoverInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c1_QUARC_Prog_Rover(SFc1_QUARC_Prog_RoverInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c1_update_debugger_state_c1_QUARC_Prog_Rover
  (SFc1_QUARC_Prog_RoverInstanceStruct *chartInstance)
{
}

static void ext_mode_exec_c1_QUARC_Prog_Rover
  (SFc1_QUARC_Prog_RoverInstanceStruct *chartInstance)
{
  c1_update_debugger_state_c1_QUARC_Prog_Rover(chartInstance);
}

static const mxArray *get_sim_state_c1_QUARC_Prog_Rover
  (SFc1_QUARC_Prog_RoverInstanceStruct *chartInstance)
{
  const mxArray *c1_st;
  const mxArray *c1_y = NULL;
  int32_T c1_i0;
  real_T c1_u[3];
  const mxArray *c1_b_y = NULL;
  uint8_T c1_hoistedGlobal;
  uint8_T c1_b_u;
  const mxArray *c1_c_y = NULL;
  uint8_T *c1_is_active_c1_QUARC_Prog_Rover;
  real_T (*c1_Euler)[3];
  c1_Euler = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c1_is_active_c1_QUARC_Prog_Rover = (uint8_T *)ssGetDWork(chartInstance->S, 3);
  c1_st = NULL;
  c1_st = NULL;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_createcellarray(2), FALSE);
  for (c1_i0 = 0; c1_i0 < 3; c1_i0++) {
    c1_u[c1_i0] = (*c1_Euler)[c1_i0];
  }

  c1_b_y = NULL;
  sf_mex_assign(&c1_b_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 2, 3, 1), FALSE);
  sf_mex_setcell(c1_y, 0, c1_b_y);
  c1_hoistedGlobal = *c1_is_active_c1_QUARC_Prog_Rover;
  c1_b_u = c1_hoistedGlobal;
  c1_c_y = NULL;
  sf_mex_assign(&c1_c_y, sf_mex_create("y", &c1_b_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 1, c1_c_y);
  sf_mex_assign(&c1_st, c1_y, FALSE);
  return c1_st;
}

static void set_sim_state_c1_QUARC_Prog_Rover
  (SFc1_QUARC_Prog_RoverInstanceStruct *chartInstance, const mxArray *c1_st)
{
  const mxArray *c1_u;
  real_T c1_dv0[3];
  int32_T c1_i1;
  boolean_T *c1_doneDoubleBufferReInit;
  uint8_T *c1_is_active_c1_QUARC_Prog_Rover;
  real_T (*c1_Euler)[3];
  c1_Euler = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c1_is_active_c1_QUARC_Prog_Rover = (uint8_T *)ssGetDWork(chartInstance->S, 3);
  c1_doneDoubleBufferReInit = (boolean_T *)ssGetDWork(chartInstance->S, 2);
  *c1_doneDoubleBufferReInit = TRUE;
  c1_u = sf_mex_dup(c1_st);
  c1_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 0)),
                      "Euler", c1_dv0);
  for (c1_i1 = 0; c1_i1 < 3; c1_i1++) {
    (*c1_Euler)[c1_i1] = c1_dv0[c1_i1];
  }

  *c1_is_active_c1_QUARC_Prog_Rover = c1_g_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 1)), "is_active_c1_QUARC_Prog_Rover");
  sf_mex_destroy(&c1_u);
  c1_update_debugger_state_c1_QUARC_Prog_Rover(chartInstance);
  sf_mex_destroy(&c1_st);
}

static void finalize_c1_QUARC_Prog_Rover(SFc1_QUARC_Prog_RoverInstanceStruct
  *chartInstance)
{
}

static void sf_c1_QUARC_Prog_Rover(SFc1_QUARC_Prog_RoverInstanceStruct
  *chartInstance)
{
  int32_T c1_i2;
  int32_T c1_i3;
  int32_T c1_i4;
  real_T c1_Angles[3];
  uint32_T c1_debug_family_var_map[14];
  real_T c1_ex[3];
  real_T c1_ey[3];
  real_T c1_ez[3];
  real_T c1_qx[4];
  real_T c1_qy[4];
  real_T c1_qz[4];
  real_T c1_Q[4];
  real_T c1_phi;
  real_T c1_theta;
  real_T c1_psi;
  real_T c1_nargin = 1.0;
  real_T c1_nargout = 1.0;
  real_T c1_Euler[3];
  int32_T c1_i5;
  int32_T c1_i6;
  static real_T c1_dv1[3] = { 1.0, 0.0, 0.0 };

  int32_T c1_i7;
  static real_T c1_dv2[3] = { 0.0, 1.0, 0.0 };

  int32_T c1_i8;
  static real_T c1_dv3[3] = { 0.0, 0.0, 1.0 };

  int32_T c1_i9;
  real_T c1_dv4[3];
  real_T c1_dv5[4];
  int32_T c1_i10;
  int32_T c1_i11;
  real_T c1_dv6[3];
  real_T c1_dv7[4];
  int32_T c1_i12;
  int32_T c1_i13;
  real_T c1_dv8[3];
  real_T c1_dv9[4];
  int32_T c1_i14;
  int32_T c1_i15;
  real_T c1_b_qy[4];
  int32_T c1_i16;
  real_T c1_b_qz[4];
  real_T c1_dv10[4];
  int32_T c1_i17;
  real_T c1_b_qx[4];
  int32_T c1_i18;
  real_T c1_dv11[4];
  real_T c1_dv12[4];
  int32_T c1_i19;
  int32_T c1_i20;
  real_T c1_b_Q[4];
  uint32_T c1_b_debug_family_var_map[6];
  real_T c1_b_nargin = 1.0;
  real_T c1_b_nargout = 3.0;
  real_T c1_b_phi;
  real_T c1_b_theta;
  real_T c1_b_psi;
  real_T c1_a;
  real_T c1_b;
  real_T c1_y;
  real_T c1_b_a;
  real_T c1_b_b;
  real_T c1_b_y;
  real_T c1_c_b;
  real_T c1_c_y;
  real_T c1_d_b;
  real_T c1_d_y;
  real_T c1_c_a;
  real_T c1_e_b;
  real_T c1_e_y;
  real_T c1_d_a;
  real_T c1_f_b;
  real_T c1_f_y;
  real_T c1_g_b;
  real_T c1_g_y;
  real_T c1_x;
  real_T c1_b_x;
  real_T c1_e_a;
  real_T c1_h_b;
  real_T c1_h_y;
  real_T c1_f_a;
  real_T c1_i_b;
  real_T c1_i_y;
  real_T c1_j_b;
  real_T c1_j_y;
  real_T c1_k_b;
  real_T c1_k_y;
  int32_T c1_i21;
  int32_T *c1_sfEvent;
  real_T (*c1_b_Euler)[3];
  real_T (*c1_b_Angles)[3];
  boolean_T guard1 = FALSE;
  c1_b_Euler = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c1_b_Angles = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
  c1_sfEvent = (int32_T *)ssGetDWork(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, *c1_sfEvent);
  for (c1_i2 = 0; c1_i2 < 3; c1_i2++) {
    _SFD_DATA_RANGE_CHECK((*c1_b_Angles)[c1_i2], 0U);
  }

  for (c1_i3 = 0; c1_i3 < 3; c1_i3++) {
    _SFD_DATA_RANGE_CHECK((*c1_b_Euler)[c1_i3], 1U);
  }

  *c1_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, *c1_sfEvent);
  for (c1_i4 = 0; c1_i4 < 3; c1_i4++) {
    c1_Angles[c1_i4] = (*c1_b_Angles)[c1_i4];
  }

  sf_debug_symbol_scope_push_eml(0U, 14U, 14U, c1_debug_family_names,
    c1_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(c1_ex, 0U, c1_d_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c1_ey, 1U, c1_d_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(c1_ez, 2U, c1_d_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(c1_qx, 3U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c1_qy, 4U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c1_qz, 5U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c1_Q, 6U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_phi, 7U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_theta, 8U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_psi, 9U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_nargin, 10U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_nargout, 11U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml(c1_Angles, 12U, c1_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(c1_Euler, 13U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, *c1_sfEvent, 4);
  for (c1_i5 = 0; c1_i5 < 3; c1_i5++) {
    c1_Euler[c1_i5] = 0.0;
  }

  _SFD_EML_CALL(0U, *c1_sfEvent, 6);
  for (c1_i6 = 0; c1_i6 < 3; c1_i6++) {
    c1_ex[c1_i6] = c1_dv1[c1_i6];
  }

  _SFD_EML_CALL(0U, *c1_sfEvent, 7);
  for (c1_i7 = 0; c1_i7 < 3; c1_i7++) {
    c1_ey[c1_i7] = c1_dv2[c1_i7];
  }

  _SFD_EML_CALL(0U, *c1_sfEvent, 8);
  for (c1_i8 = 0; c1_i8 < 3; c1_i8++) {
    c1_ez[c1_i8] = c1_dv3[c1_i8];
  }

  _SFD_EML_CALL(0U, *c1_sfEvent, 10);
  for (c1_i9 = 0; c1_i9 < 3; c1_i9++) {
    c1_dv4[c1_i9] = c1_dv1[c1_i9];
  }

  c1_Quaternion(chartInstance, c1_Angles[0], c1_dv4, c1_dv5);
  for (c1_i10 = 0; c1_i10 < 4; c1_i10++) {
    c1_qx[c1_i10] = c1_dv5[c1_i10];
  }

  _SFD_EML_CALL(0U, *c1_sfEvent, 11);
  for (c1_i11 = 0; c1_i11 < 3; c1_i11++) {
    c1_dv6[c1_i11] = c1_dv2[c1_i11];
  }

  c1_Quaternion(chartInstance, c1_Angles[1], c1_dv6, c1_dv7);
  for (c1_i12 = 0; c1_i12 < 4; c1_i12++) {
    c1_qy[c1_i12] = c1_dv7[c1_i12];
  }

  _SFD_EML_CALL(0U, *c1_sfEvent, 12);
  for (c1_i13 = 0; c1_i13 < 3; c1_i13++) {
    c1_dv8[c1_i13] = c1_dv3[c1_i13];
  }

  c1_Quaternion(chartInstance, c1_Angles[2], c1_dv8, c1_dv9);
  for (c1_i14 = 0; c1_i14 < 4; c1_i14++) {
    c1_qz[c1_i14] = c1_dv9[c1_i14];
  }

  _SFD_EML_CALL(0U, *c1_sfEvent, 14);
  for (c1_i15 = 0; c1_i15 < 4; c1_i15++) {
    c1_b_qy[c1_i15] = c1_qy[c1_i15];
  }

  for (c1_i16 = 0; c1_i16 < 4; c1_i16++) {
    c1_b_qz[c1_i16] = c1_qz[c1_i16];
  }

  c1_QuaternionProduct(chartInstance, c1_b_qy, c1_b_qz, c1_dv10);
  for (c1_i17 = 0; c1_i17 < 4; c1_i17++) {
    c1_b_qx[c1_i17] = c1_qx[c1_i17];
  }

  for (c1_i18 = 0; c1_i18 < 4; c1_i18++) {
    c1_dv11[c1_i18] = c1_dv10[c1_i18];
  }

  c1_QuaternionProduct(chartInstance, c1_b_qx, c1_dv11, c1_dv12);
  for (c1_i19 = 0; c1_i19 < 4; c1_i19++) {
    c1_Q[c1_i19] = c1_dv12[c1_i19];
  }

  _SFD_EML_CALL(0U, *c1_sfEvent, 16);
  for (c1_i20 = 0; c1_i20 < 4; c1_i20++) {
    c1_b_Q[c1_i20] = c1_Q[c1_i20];
  }

  sf_debug_symbol_scope_push_eml(0U, 6U, 6U, c1_e_debug_family_names,
    c1_b_debug_family_var_map);
  sf_debug_symbol_scope_add_eml_importable(&c1_b_nargin, 0U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_b_nargout, 1U,
    c1_b_sf_marshallOut, c1_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c1_b_Q, 2U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_b_phi, 3U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_b_theta, 4U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_b_psi, 5U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  CV_SCRIPT_FCN(3, 0);
  _SFD_SCRIPT_CALL(3U, *c1_sfEvent, 26);
  c1_a = c1_b_Q[2];
  c1_b = c1_b_Q[3];
  c1_y = c1_a * c1_b;
  c1_b_a = c1_b_Q[0];
  c1_b_b = c1_b_Q[1];
  c1_b_y = c1_b_a * c1_b_b;
  c1_c_b = c1_y + c1_b_y;
  c1_c_y = 2.0 * c1_c_b;
  c1_d_b = c1_mpower(chartInstance, c1_b_Q[1]) + c1_mpower(chartInstance,
    c1_b_Q[2]);
  c1_d_y = 2.0 * c1_d_b;
  c1_b_phi = c1_atan2(chartInstance, c1_c_y, 1.0 - c1_d_y);
  _SFD_SCRIPT_CALL(3U, *c1_sfEvent, 27);
  c1_c_a = c1_b_Q[1];
  c1_e_b = c1_b_Q[3];
  c1_e_y = c1_c_a * c1_e_b;
  c1_d_a = c1_b_Q[0];
  c1_f_b = c1_b_Q[2];
  c1_f_y = c1_d_a * c1_f_b;
  c1_g_b = c1_e_y - c1_f_y;
  c1_g_y = 2.0 * c1_g_b;
  c1_x = c1_g_y;
  c1_b_x = c1_x;
  guard1 = FALSE;
  if (c1_b_x < -1.0) {
    guard1 = TRUE;
  } else {
    if (1.0 < c1_b_x) {
      guard1 = TRUE;
    }
  }

  if (guard1 == TRUE) {
    c1_eml_error(chartInstance);
  }

  c1_b_x = muDoubleScalarAsin(c1_b_x);
  c1_b_theta = -c1_b_x;
  _SFD_SCRIPT_CALL(3U, *c1_sfEvent, 28);
  c1_e_a = c1_b_Q[2];
  c1_h_b = c1_b_Q[1];
  c1_h_y = c1_e_a * c1_h_b;
  c1_f_a = c1_b_Q[0];
  c1_i_b = c1_b_Q[3];
  c1_i_y = c1_f_a * c1_i_b;
  c1_j_b = c1_h_y + c1_i_y;
  c1_j_y = 2.0 * c1_j_b;
  c1_k_b = c1_mpower(chartInstance, c1_b_Q[2]) + c1_mpower(chartInstance,
    c1_b_Q[3]);
  c1_k_y = 2.0 * c1_k_b;
  c1_b_psi = c1_atan2(chartInstance, c1_j_y, 1.0 - c1_k_y);
  _SFD_SCRIPT_CALL(3U, *c1_sfEvent, -28);
  sf_debug_symbol_scope_pop();
  c1_phi = c1_b_phi;
  c1_theta = c1_b_theta;
  c1_psi = c1_b_psi;
  _SFD_EML_CALL(0U, *c1_sfEvent, 17);
  c1_Euler[0] = c1_phi;
  _SFD_EML_CALL(0U, *c1_sfEvent, 18);
  c1_Euler[1] = c1_theta;
  _SFD_EML_CALL(0U, *c1_sfEvent, 19);
  c1_Euler[2] = c1_psi;
  _SFD_EML_CALL(0U, *c1_sfEvent, -19);
  sf_debug_symbol_scope_pop();
  for (c1_i21 = 0; c1_i21 < 3; c1_i21++) {
    (*c1_b_Euler)[c1_i21] = c1_Euler[c1_i21];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, *c1_sfEvent);
  sf_debug_check_for_state_inconsistency(_QUARC_Prog_RoverMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void initSimStructsc1_QUARC_Prog_Rover
  (SFc1_QUARC_Prog_RoverInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber)
{
  _SFD_SCRIPT_TRANSLATION(c1_chartNumber, 0U, sf_debug_get_script_id(
    "E:/TOOLBOX/RT_MaG/RT_MaG_ToolBox/MATLAB_RESSOURCES/TOOLS/MathTools/Rotation/Quaternion.m"));
  _SFD_SCRIPT_TRANSLATION(c1_chartNumber, 1U, sf_debug_get_script_id(
    "E:/TOOLBOX/RT_MaG/RT_MaG_ToolBox/MATLAB_RESSOURCES/TOOLS/MathTools/Rotation/UnitQuaternion.m"));
  _SFD_SCRIPT_TRANSLATION(c1_chartNumber, 2U, sf_debug_get_script_id(
    "E:/TOOLBOX/RT_MaG/RT_MaG_ToolBox/MATLAB_RESSOURCES/TOOLS/MathTools/Rotation/QuaternionProduct.m"));
  _SFD_SCRIPT_TRANSLATION(c1_chartNumber, 3U, sf_debug_get_script_id(
    "E:/TOOLBOX/RT_MaG/RT_MaG_ToolBox/MATLAB_RESSOURCES/TOOLS/MathTools/Rotation/Quaternion2Euler2.m"));
}

static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i22;
  real_T c1_b_inData[3];
  int32_T c1_i23;
  real_T c1_u[3];
  const mxArray *c1_y = NULL;
  SFc1_QUARC_Prog_RoverInstanceStruct *chartInstance;
  chartInstance = (SFc1_QUARC_Prog_RoverInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i22 = 0; c1_i22 < 3; c1_i22++) {
    c1_b_inData[c1_i22] = (*(real_T (*)[3])c1_inData)[c1_i22];
  }

  for (c1_i23 = 0; c1_i23 < 3; c1_i23++) {
    c1_u[c1_i23] = c1_b_inData[c1_i23];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 2, 3, 1), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static void c1_emlrt_marshallIn(SFc1_QUARC_Prog_RoverInstanceStruct
  *chartInstance, const mxArray *c1_Euler, const char_T *c1_identifier, real_T
  c1_y[3])
{
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_Euler), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_Euler);
}

static void c1_b_emlrt_marshallIn(SFc1_QUARC_Prog_RoverInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId,
  real_T c1_y[3])
{
  real_T c1_dv13[3];
  int32_T c1_i24;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv13, 1, 0, 0U, 1, 0U, 2, 3, 1);
  for (c1_i24 = 0; c1_i24 < 3; c1_i24++) {
    c1_y[c1_i24] = c1_dv13[c1_i24];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_Euler;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[3];
  int32_T c1_i25;
  SFc1_QUARC_Prog_RoverInstanceStruct *chartInstance;
  chartInstance = (SFc1_QUARC_Prog_RoverInstanceStruct *)chartInstanceVoid;
  c1_Euler = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_Euler), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_Euler);
  for (c1_i25 = 0; c1_i25 < 3; c1_i25++) {
    (*(real_T (*)[3])c1_outData)[c1_i25] = c1_y[c1_i25];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  real_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_QUARC_Prog_RoverInstanceStruct *chartInstance;
  chartInstance = (SFc1_QUARC_Prog_RoverInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(real_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static real_T c1_c_emlrt_marshallIn(SFc1_QUARC_Prog_RoverInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  real_T c1_y;
  real_T c1_d0;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_d0, 1, 0, 0U, 0, 0U, 0);
  c1_y = c1_d0;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_nargout;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y;
  SFc1_QUARC_Prog_RoverInstanceStruct *chartInstance;
  chartInstance = (SFc1_QUARC_Prog_RoverInstanceStruct *)chartInstanceVoid;
  c1_nargout = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_nargout), &c1_thisId);
  sf_mex_destroy(&c1_nargout);
  *(real_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i26;
  real_T c1_b_inData[4];
  int32_T c1_i27;
  real_T c1_u[4];
  const mxArray *c1_y = NULL;
  SFc1_QUARC_Prog_RoverInstanceStruct *chartInstance;
  chartInstance = (SFc1_QUARC_Prog_RoverInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i26 = 0; c1_i26 < 4; c1_i26++) {
    c1_b_inData[c1_i26] = (*(real_T (*)[4])c1_inData)[c1_i26];
  }

  for (c1_i27 = 0; c1_i27 < 4; c1_i27++) {
    c1_u[c1_i27] = c1_b_inData[c1_i27];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 1, 4), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static void c1_d_emlrt_marshallIn(SFc1_QUARC_Prog_RoverInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId,
  real_T c1_y[4])
{
  real_T c1_dv14[4];
  int32_T c1_i28;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv14, 1, 0, 0U, 1, 0U, 1, 4);
  for (c1_i28 = 0; c1_i28 < 4; c1_i28++) {
    c1_y[c1_i28] = c1_dv14[c1_i28];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_Q;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[4];
  int32_T c1_i29;
  SFc1_QUARC_Prog_RoverInstanceStruct *chartInstance;
  chartInstance = (SFc1_QUARC_Prog_RoverInstanceStruct *)chartInstanceVoid;
  c1_Q = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_Q), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_Q);
  for (c1_i29 = 0; c1_i29 < 4; c1_i29++) {
    (*(real_T (*)[4])c1_outData)[c1_i29] = c1_y[c1_i29];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_d_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i30;
  real_T c1_b_inData[3];
  int32_T c1_i31;
  real_T c1_u[3];
  const mxArray *c1_y = NULL;
  SFc1_QUARC_Prog_RoverInstanceStruct *chartInstance;
  chartInstance = (SFc1_QUARC_Prog_RoverInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i30 = 0; c1_i30 < 3; c1_i30++) {
    c1_b_inData[c1_i30] = (*(real_T (*)[3])c1_inData)[c1_i30];
  }

  for (c1_i31 = 0; c1_i31 < 3; c1_i31++) {
    c1_u[c1_i31] = c1_b_inData[c1_i31];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static void c1_e_emlrt_marshallIn(SFc1_QUARC_Prog_RoverInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId,
  real_T c1_y[3])
{
  real_T c1_dv15[3];
  int32_T c1_i32;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv15, 1, 0, 0U, 1, 0U, 1, 3);
  for (c1_i32 = 0; c1_i32 < 3; c1_i32++) {
    c1_y[c1_i32] = c1_dv15[c1_i32];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_V;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[3];
  int32_T c1_i33;
  SFc1_QUARC_Prog_RoverInstanceStruct *chartInstance;
  chartInstance = (SFc1_QUARC_Prog_RoverInstanceStruct *)chartInstanceVoid;
  c1_V = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_V), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_V);
  for (c1_i33 = 0; c1_i33 < 3; c1_i33++) {
    (*(real_T (*)[3])c1_outData)[c1_i33] = c1_y[c1_i33];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

const mxArray *sf_c1_QUARC_Prog_Rover_get_eml_resolved_functions_info(void)
{
  const mxArray *c1_nameCaptureInfo;
  c1_ResolvedFunctionInfo c1_info[38];
  const mxArray *c1_m0 = NULL;
  int32_T c1_i34;
  c1_ResolvedFunctionInfo *c1_r0;
  c1_nameCaptureInfo = NULL;
  c1_nameCaptureInfo = NULL;
  c1_info_helper(c1_info);
  sf_mex_assign(&c1_m0, sf_mex_createstruct("nameCaptureInfo", 1, 38), FALSE);
  for (c1_i34 = 0; c1_i34 < 38; c1_i34++) {
    c1_r0 = &c1_info[c1_i34];
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", c1_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c1_r0->context)), "context", "nameCaptureInfo",
                    c1_i34);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", c1_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c1_r0->name)), "name", "nameCaptureInfo", c1_i34);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", c1_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c1_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c1_i34);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", c1_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c1_r0->resolved)), "resolved", "nameCaptureInfo",
                    c1_i34);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", &c1_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c1_i34);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", &c1_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c1_i34);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", &c1_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c1_i34);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", &c1_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c1_i34);
  }

  sf_mex_assign(&c1_nameCaptureInfo, c1_m0, FALSE);
  return c1_nameCaptureInfo;
}

static void c1_info_helper(c1_ResolvedFunctionInfo c1_info[38])
{
  c1_info[0].context = "";
  c1_info[0].name = "Quaternion";
  c1_info[0].dominantType = "double";
  c1_info[0].resolved =
    "[E]E:/TOOLBOX/RT_MaG/RT_MaG_ToolBox/MATLAB_RESSOURCES/TOOLS/MathTools/Rotation/Quaternion.m";
  c1_info[0].fileTimeLo = 1395830762U;
  c1_info[0].fileTimeHi = 0U;
  c1_info[0].mFileTimeLo = 0U;
  c1_info[0].mFileTimeHi = 0U;
  c1_info[1].context =
    "[E]E:/TOOLBOX/RT_MaG/RT_MaG_ToolBox/MATLAB_RESSOURCES/TOOLS/MathTools/Rotation/Quaternion.m";
  c1_info[1].name = "mrdivide";
  c1_info[1].dominantType = "double";
  c1_info[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c1_info[1].fileTimeLo = 1310137456U;
  c1_info[1].fileTimeHi = 0U;
  c1_info[1].mFileTimeLo = 1289519692U;
  c1_info[1].mFileTimeHi = 0U;
  c1_info[2].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c1_info[2].name = "rdivide";
  c1_info[2].dominantType = "double";
  c1_info[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c1_info[2].fileTimeLo = 1286818844U;
  c1_info[2].fileTimeHi = 0U;
  c1_info[2].mFileTimeLo = 0U;
  c1_info[2].mFileTimeHi = 0U;
  c1_info[3].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c1_info[3].name = "eml_div";
  c1_info[3].dominantType = "double";
  c1_info[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  c1_info[3].fileTimeLo = 1305318000U;
  c1_info[3].fileTimeHi = 0U;
  c1_info[3].mFileTimeLo = 0U;
  c1_info[3].mFileTimeHi = 0U;
  c1_info[4].context =
    "[E]E:/TOOLBOX/RT_MaG/RT_MaG_ToolBox/MATLAB_RESSOURCES/TOOLS/MathTools/Rotation/Quaternion.m";
  c1_info[4].name = "cos";
  c1_info[4].dominantType = "double";
  c1_info[4].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  c1_info[4].fileTimeLo = 1286818706U;
  c1_info[4].fileTimeHi = 0U;
  c1_info[4].mFileTimeLo = 0U;
  c1_info[4].mFileTimeHi = 0U;
  c1_info[5].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  c1_info[5].name = "eml_scalar_cos";
  c1_info[5].dominantType = "double";
  c1_info[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_cos.m";
  c1_info[5].fileTimeLo = 1286818722U;
  c1_info[5].fileTimeHi = 0U;
  c1_info[5].mFileTimeLo = 0U;
  c1_info[5].mFileTimeHi = 0U;
  c1_info[6].context =
    "[E]E:/TOOLBOX/RT_MaG/RT_MaG_ToolBox/MATLAB_RESSOURCES/TOOLS/MathTools/Rotation/Quaternion.m";
  c1_info[6].name = "sin";
  c1_info[6].dominantType = "double";
  c1_info[6].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m";
  c1_info[6].fileTimeLo = 1286818750U;
  c1_info[6].fileTimeHi = 0U;
  c1_info[6].mFileTimeLo = 0U;
  c1_info[6].mFileTimeHi = 0U;
  c1_info[7].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m";
  c1_info[7].name = "eml_scalar_sin";
  c1_info[7].dominantType = "double";
  c1_info[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sin.m";
  c1_info[7].fileTimeLo = 1286818736U;
  c1_info[7].fileTimeHi = 0U;
  c1_info[7].mFileTimeLo = 0U;
  c1_info[7].mFileTimeHi = 0U;
  c1_info[8].context =
    "[E]E:/TOOLBOX/RT_MaG/RT_MaG_ToolBox/MATLAB_RESSOURCES/TOOLS/MathTools/Rotation/Quaternion.m";
  c1_info[8].name = "mtimes";
  c1_info[8].dominantType = "double";
  c1_info[8].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[8].fileTimeLo = 1289519692U;
  c1_info[8].fileTimeHi = 0U;
  c1_info[8].mFileTimeLo = 0U;
  c1_info[8].mFileTimeHi = 0U;
  c1_info[9].context =
    "[E]E:/TOOLBOX/RT_MaG/RT_MaG_ToolBox/MATLAB_RESSOURCES/TOOLS/MathTools/Rotation/Quaternion.m";
  c1_info[9].name = "UnitQuaternion";
  c1_info[9].dominantType = "double";
  c1_info[9].resolved =
    "[E]E:/TOOLBOX/RT_MaG/RT_MaG_ToolBox/MATLAB_RESSOURCES/TOOLS/MathTools/Rotation/UnitQuaternion.m";
  c1_info[9].fileTimeLo = 1395830762U;
  c1_info[9].fileTimeHi = 0U;
  c1_info[9].mFileTimeLo = 0U;
  c1_info[9].mFileTimeHi = 0U;
  c1_info[10].context =
    "[E]E:/TOOLBOX/RT_MaG/RT_MaG_ToolBox/MATLAB_RESSOURCES/TOOLS/MathTools/Rotation/UnitQuaternion.m";
  c1_info[10].name = "norm";
  c1_info[10].dominantType = "double";
  c1_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m";
  c1_info[10].fileTimeLo = 1286818826U;
  c1_info[10].fileTimeHi = 0U;
  c1_info[10].mFileTimeLo = 0U;
  c1_info[10].mFileTimeHi = 0U;
  c1_info[11].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!genpnorm";
  c1_info[11].name = "eml_index_class";
  c1_info[11].dominantType = "";
  c1_info[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c1_info[11].fileTimeLo = 1286818778U;
  c1_info[11].fileTimeHi = 0U;
  c1_info[11].mFileTimeLo = 0U;
  c1_info[11].mFileTimeHi = 0U;
  c1_info[12].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m!genpnorm";
  c1_info[12].name = "eml_xnrm2";
  c1_info[12].dominantType = "int32";
  c1_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xnrm2.m";
  c1_info[12].fileTimeLo = 1299076776U;
  c1_info[12].fileTimeHi = 0U;
  c1_info[12].mFileTimeLo = 0U;
  c1_info[12].mFileTimeHi = 0U;
  c1_info[13].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xnrm2.m";
  c1_info[13].name = "eml_blas_inline";
  c1_info[13].dominantType = "";
  c1_info[13].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c1_info[13].fileTimeLo = 1299076768U;
  c1_info[13].fileTimeHi = 0U;
  c1_info[13].mFileTimeLo = 0U;
  c1_info[13].mFileTimeHi = 0U;
  c1_info[14].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xnrm2.m";
  c1_info[14].name = "eml_refblas_xnrm2";
  c1_info[14].dominantType = "int32";
  c1_info[14].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c1_info[14].fileTimeLo = 1299076784U;
  c1_info[14].fileTimeHi = 0U;
  c1_info[14].mFileTimeLo = 0U;
  c1_info[14].mFileTimeHi = 0U;
  c1_info[15].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c1_info[15].name = "realmin";
  c1_info[15].dominantType = "char";
  c1_info[15].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmin.m";
  c1_info[15].fileTimeLo = 1286818768U;
  c1_info[15].fileTimeHi = 0U;
  c1_info[15].mFileTimeLo = 0U;
  c1_info[15].mFileTimeHi = 0U;
  c1_info[16].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmin.m";
  c1_info[16].name = "mpower";
  c1_info[16].dominantType = "double";
  c1_info[16].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m";
  c1_info[16].fileTimeLo = 1286818842U;
  c1_info[16].fileTimeHi = 0U;
  c1_info[16].mFileTimeLo = 0U;
  c1_info[16].mFileTimeHi = 0U;
  c1_info[17].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m";
  c1_info[17].name = "power";
  c1_info[17].dominantType = "double";
  c1_info[17].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  c1_info[17].fileTimeLo = 1294067944U;
  c1_info[17].fileTimeHi = 0U;
  c1_info[17].mFileTimeLo = 0U;
  c1_info[17].mFileTimeHi = 0U;
  c1_info[18].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  c1_info[18].name = "eml_scalar_eg";
  c1_info[18].dominantType = "double";
  c1_info[18].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c1_info[18].fileTimeLo = 1286818796U;
  c1_info[18].fileTimeHi = 0U;
  c1_info[18].mFileTimeLo = 0U;
  c1_info[18].mFileTimeHi = 0U;
  c1_info[19].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  c1_info[19].name = "eml_scalexp_alloc";
  c1_info[19].dominantType = "double";
  c1_info[19].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  c1_info[19].fileTimeLo = 1286818796U;
  c1_info[19].fileTimeHi = 0U;
  c1_info[19].mFileTimeLo = 0U;
  c1_info[19].mFileTimeHi = 0U;
  c1_info[20].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  c1_info[20].name = "eml_scalar_floor";
  c1_info[20].dominantType = "double";
  c1_info[20].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m";
  c1_info[20].fileTimeLo = 1286818726U;
  c1_info[20].fileTimeHi = 0U;
  c1_info[20].mFileTimeLo = 0U;
  c1_info[20].mFileTimeHi = 0U;
  c1_info[21].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c1_info[21].name = "eml_index_minus";
  c1_info[21].dominantType = "int32";
  c1_info[21].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c1_info[21].fileTimeLo = 1286818778U;
  c1_info[21].fileTimeHi = 0U;
  c1_info[21].mFileTimeLo = 0U;
  c1_info[21].mFileTimeHi = 0U;
  c1_info[22].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c1_info[22].name = "eml_index_times";
  c1_info[22].dominantType = "int32";
  c1_info[22].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c1_info[22].fileTimeLo = 1286818780U;
  c1_info[22].fileTimeHi = 0U;
  c1_info[22].mFileTimeLo = 0U;
  c1_info[22].mFileTimeHi = 0U;
  c1_info[23].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c1_info[23].name = "eml_index_plus";
  c1_info[23].dominantType = "int32";
  c1_info[23].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c1_info[23].fileTimeLo = 1286818778U;
  c1_info[23].fileTimeHi = 0U;
  c1_info[23].mFileTimeLo = 0U;
  c1_info[23].mFileTimeHi = 0U;
  c1_info[24].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xnrm2.m";
  c1_info[24].name = "abs";
  c1_info[24].dominantType = "double";
  c1_info[24].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c1_info[24].fileTimeLo = 1286818694U;
  c1_info[24].fileTimeHi = 0U;
  c1_info[24].mFileTimeLo = 0U;
  c1_info[24].mFileTimeHi = 0U;
  c1_info[25].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c1_info[25].name = "eml_scalar_abs";
  c1_info[25].dominantType = "double";
  c1_info[25].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m";
  c1_info[25].fileTimeLo = 1286818712U;
  c1_info[25].fileTimeHi = 0U;
  c1_info[25].mFileTimeLo = 0U;
  c1_info[25].mFileTimeHi = 0U;
  c1_info[26].context = "";
  c1_info[26].name = "QuaternionProduct";
  c1_info[26].dominantType = "double";
  c1_info[26].resolved =
    "[E]E:/TOOLBOX/RT_MaG/RT_MaG_ToolBox/MATLAB_RESSOURCES/TOOLS/MathTools/Rotation/QuaternionProduct.m";
  c1_info[26].fileTimeLo = 1395830762U;
  c1_info[26].fileTimeHi = 0U;
  c1_info[26].mFileTimeLo = 0U;
  c1_info[26].mFileTimeHi = 0U;
  c1_info[27].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[27].name = "eml_xdotu";
  c1_info[27].dominantType = "int32";
  c1_info[27].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdotu.m";
  c1_info[27].fileTimeLo = 1299076772U;
  c1_info[27].fileTimeHi = 0U;
  c1_info[27].mFileTimeLo = 0U;
  c1_info[27].mFileTimeHi = 0U;
  c1_info[28].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdotu.m";
  c1_info[28].name = "eml_xdot";
  c1_info[28].dominantType = "int32";
  c1_info[28].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdot.m";
  c1_info[28].fileTimeLo = 1299076772U;
  c1_info[28].fileTimeHi = 0U;
  c1_info[28].mFileTimeLo = 0U;
  c1_info[28].mFileTimeHi = 0U;
  c1_info[29].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xdot.m";
  c1_info[29].name = "eml_refblas_xdot";
  c1_info[29].dominantType = "int32";
  c1_info[29].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdot.m";
  c1_info[29].fileTimeLo = 1299076772U;
  c1_info[29].fileTimeHi = 0U;
  c1_info[29].mFileTimeLo = 0U;
  c1_info[29].mFileTimeHi = 0U;
  c1_info[30].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdot.m";
  c1_info[30].name = "eml_refblas_xdotx";
  c1_info[30].dominantType = "int32";
  c1_info[30].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  c1_info[30].fileTimeLo = 1299076774U;
  c1_info[30].fileTimeHi = 0U;
  c1_info[30].mFileTimeLo = 0U;
  c1_info[30].mFileTimeHi = 0U;
  c1_info[31].context =
    "[E]E:/TOOLBOX/RT_MaG/RT_MaG_ToolBox/MATLAB_RESSOURCES/TOOLS/MathTools/Rotation/QuaternionProduct.m";
  c1_info[31].name = "cross";
  c1_info[31].dominantType = "double";
  c1_info[31].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/specfun/cross.m";
  c1_info[31].fileTimeLo = 1286818842U;
  c1_info[31].fileTimeHi = 0U;
  c1_info[31].mFileTimeLo = 0U;
  c1_info[31].mFileTimeHi = 0U;
  c1_info[32].context = "";
  c1_info[32].name = "Quaternion2Euler2";
  c1_info[32].dominantType = "double";
  c1_info[32].resolved =
    "[E]E:/TOOLBOX/RT_MaG/RT_MaG_ToolBox/MATLAB_RESSOURCES/TOOLS/MathTools/Rotation/Quaternion2Euler2.m";
  c1_info[32].fileTimeLo = 1396943667U;
  c1_info[32].fileTimeHi = 0U;
  c1_info[32].mFileTimeLo = 0U;
  c1_info[32].mFileTimeHi = 0U;
  c1_info[33].context =
    "[E]E:/TOOLBOX/RT_MaG/RT_MaG_ToolBox/MATLAB_RESSOURCES/TOOLS/MathTools/Rotation/Quaternion2Euler2.m";
  c1_info[33].name = "atan2";
  c1_info[33].dominantType = "double";
  c1_info[33].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/atan2.m";
  c1_info[33].fileTimeLo = 1286818704U;
  c1_info[33].fileTimeHi = 0U;
  c1_info[33].mFileTimeLo = 0U;
  c1_info[33].mFileTimeHi = 0U;
  c1_info[34].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/atan2.m";
  c1_info[34].name = "eml_scalar_atan2";
  c1_info[34].dominantType = "double";
  c1_info[34].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_atan2.m";
  c1_info[34].fileTimeLo = 1286818720U;
  c1_info[34].fileTimeHi = 0U;
  c1_info[34].mFileTimeLo = 0U;
  c1_info[34].mFileTimeHi = 0U;
  c1_info[35].context =
    "[E]E:/TOOLBOX/RT_MaG/RT_MaG_ToolBox/MATLAB_RESSOURCES/TOOLS/MathTools/Rotation/Quaternion2Euler2.m";
  c1_info[35].name = "asin";
  c1_info[35].dominantType = "double";
  c1_info[35].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/asin.m";
  c1_info[35].fileTimeLo = 1286818702U;
  c1_info[35].fileTimeHi = 0U;
  c1_info[35].mFileTimeLo = 0U;
  c1_info[35].mFileTimeHi = 0U;
  c1_info[36].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/asin.m";
  c1_info[36].name = "eml_error";
  c1_info[36].dominantType = "char";
  c1_info[36].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_error.m";
  c1_info[36].fileTimeLo = 1305318000U;
  c1_info[36].fileTimeHi = 0U;
  c1_info[36].mFileTimeLo = 0U;
  c1_info[36].mFileTimeHi = 0U;
  c1_info[37].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/asin.m";
  c1_info[37].name = "eml_scalar_asin";
  c1_info[37].dominantType = "double";
  c1_info[37].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_asin.m";
  c1_info[37].fileTimeLo = 1286818716U;
  c1_info[37].fileTimeHi = 0U;
  c1_info[37].mFileTimeLo = 0U;
  c1_info[37].mFileTimeHi = 0U;
}

static void c1_Quaternion(SFc1_QUARC_Prog_RoverInstanceStruct *chartInstance,
  real_T c1_S, real_T c1_V[3], real_T c1_Q[4])
{
  uint32_T c1_debug_family_var_map[5];
  real_T c1_nargin = 2.0;
  real_T c1_nargout = 1.0;
  real_T c1_A;
  real_T c1_x;
  real_T c1_b_x;
  real_T c1_y;
  real_T c1_c_x;
  real_T c1_d_x;
  real_T c1_b_A;
  real_T c1_e_x;
  real_T c1_f_x;
  real_T c1_b_y;
  real_T c1_g_x;
  real_T c1_h_x;
  real_T c1_a;
  int32_T c1_i35;
  real_T c1_b[3];
  int32_T c1_i36;
  real_T c1_b_Q[4];
  int32_T c1_i37;
  uint32_T c1_b_debug_family_var_map[4];
  real_T c1_b_nargin = 1.0;
  real_T c1_b_nargout = 1.0;
  int32_T c1_i38;
  real_T c1_i_x[4];
  real_T c1_c_y;
  real_T c1_scale;
  int32_T c1_k;
  int32_T c1_b_k;
  real_T c1_j_x;
  real_T c1_k_x;
  real_T c1_absxk;
  real_T c1_t;
  int32_T c1_i39;
  real_T c1_B;
  real_T c1_d_y;
  real_T c1_e_y;
  int32_T c1_i40;
  int32_T *c1_sfEvent;
  c1_sfEvent = (int32_T *)ssGetDWork(chartInstance->S, 0);
  sf_debug_symbol_scope_push_eml(0U, 5U, 5U, c1_c_debug_family_names,
    c1_debug_family_var_map);
  sf_debug_symbol_scope_add_eml_importable(&c1_nargin, 0U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_nargout, 1U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_S, 2U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c1_V, 3U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c1_Q, 4U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  CV_SCRIPT_FCN(0, 0);
  _SFD_SCRIPT_CALL(0U, *c1_sfEvent, 48);
  c1_A = c1_S;
  c1_x = c1_A;
  c1_b_x = c1_x;
  c1_y = c1_b_x / 2.0;
  c1_c_x = c1_y;
  c1_d_x = c1_c_x;
  c1_d_x = muDoubleScalarCos(c1_d_x);
  c1_b_A = c1_S;
  c1_e_x = c1_b_A;
  c1_f_x = c1_e_x;
  c1_b_y = c1_f_x / 2.0;
  c1_g_x = c1_b_y;
  c1_h_x = c1_g_x;
  c1_h_x = muDoubleScalarSin(c1_h_x);
  c1_a = c1_h_x;
  for (c1_i35 = 0; c1_i35 < 3; c1_i35++) {
    c1_b[c1_i35] = c1_V[c1_i35];
  }

  for (c1_i36 = 0; c1_i36 < 3; c1_i36++) {
    c1_b[c1_i36] *= c1_a;
  }

  c1_b_Q[0] = c1_d_x;
  for (c1_i37 = 0; c1_i37 < 3; c1_i37++) {
    c1_b_Q[c1_i37 + 1] = c1_b[c1_i37];
  }

  sf_debug_symbol_scope_push_eml(0U, 4U, 4U, c1_b_debug_family_names,
    c1_b_debug_family_var_map);
  sf_debug_symbol_scope_add_eml_importable(&c1_b_nargin, 0U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_b_nargout, 1U,
    c1_b_sf_marshallOut, c1_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c1_b_Q, 2U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c1_Q, 3U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  CV_SCRIPT_FCN(1, 0);
  _SFD_SCRIPT_CALL(1U, *c1_sfEvent, 44);
  for (c1_i38 = 0; c1_i38 < 4; c1_i38++) {
    c1_i_x[c1_i38] = c1_b_Q[c1_i38];
  }

  c1_c_y = 0.0;
  c1_scale = 2.2250738585072014E-308;
  for (c1_k = 1; c1_k < 5; c1_k++) {
    c1_b_k = c1_k;
    c1_j_x = c1_i_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK(
      "", (real_T)c1_b_k), 1, 4, 1, 0) - 1];
    c1_k_x = c1_j_x;
    c1_absxk = muDoubleScalarAbs(c1_k_x);
    if (c1_absxk > c1_scale) {
      c1_t = c1_scale / c1_absxk;
      c1_c_y = 1.0 + c1_c_y * c1_t * c1_t;
      c1_scale = c1_absxk;
    } else {
      c1_t = c1_absxk / c1_scale;
      c1_c_y += c1_t * c1_t;
    }
  }

  c1_c_y = c1_scale * muDoubleScalarSqrt(c1_c_y);
  for (c1_i39 = 0; c1_i39 < 4; c1_i39++) {
    c1_i_x[c1_i39] = c1_b_Q[c1_i39];
  }

  c1_B = c1_c_y;
  c1_d_y = c1_B;
  c1_e_y = c1_d_y;
  for (c1_i40 = 0; c1_i40 < 4; c1_i40++) {
    c1_Q[c1_i40] = c1_i_x[c1_i40] / c1_e_y;
  }

  _SFD_SCRIPT_CALL(1U, *c1_sfEvent, -44);
  sf_debug_symbol_scope_pop();
  _SFD_SCRIPT_CALL(0U, *c1_sfEvent, -48);
  sf_debug_symbol_scope_pop();
}

static void c1_eml_scalar_eg(SFc1_QUARC_Prog_RoverInstanceStruct *chartInstance)
{
}

static void c1_QuaternionProduct(SFc1_QUARC_Prog_RoverInstanceStruct
  *chartInstance, real_T c1_Q1[4], real_T c1_Q2[4], real_T c1_q[4])
{
  uint32_T c1_debug_family_var_map[9];
  real_T c1_s1;
  real_T c1_s2;
  real_T c1_v1[3];
  real_T c1_v2[3];
  real_T c1_nargin = 2.0;
  real_T c1_nargout = 1.0;
  int32_T c1_i41;
  int32_T c1_i42;
  real_T c1_a;
  real_T c1_b;
  real_T c1_y;
  int32_T c1_i43;
  real_T c1_b_a[3];
  int32_T c1_i44;
  real_T c1_b_b[3];
  real_T c1_b_y;
  int32_T c1_k;
  int32_T c1_b_k;
  real_T c1_c_a;
  int32_T c1_i45;
  int32_T c1_i46;
  real_T c1_d_a;
  int32_T c1_i47;
  real_T c1_c_b[3];
  int32_T c1_i48;
  int32_T c1_i49;
  real_T c1_e_a[3];
  int32_T c1_i50;
  real_T c1_d_b[3];
  real_T c1_f_a;
  real_T c1_e_b;
  real_T c1_c_y;
  real_T c1_g_a;
  real_T c1_f_b;
  real_T c1_d_y;
  real_T c1_c1;
  real_T c1_h_a;
  real_T c1_g_b;
  real_T c1_e_y;
  real_T c1_i_a;
  real_T c1_h_b;
  real_T c1_f_y;
  real_T c1_c2;
  real_T c1_j_a;
  real_T c1_i_b;
  real_T c1_g_y;
  real_T c1_k_a;
  real_T c1_j_b;
  real_T c1_h_y;
  real_T c1_c3;
  int32_T c1_i51;
  int32_T *c1_sfEvent;
  c1_sfEvent = (int32_T *)ssGetDWork(chartInstance->S, 0);
  sf_debug_symbol_scope_push_eml(0U, 9U, 9U, c1_d_debug_family_names,
    c1_debug_family_var_map);
  sf_debug_symbol_scope_add_eml_importable(&c1_s1, 0U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_s2, 1U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c1_v1, 2U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c1_v2, 3U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_nargin, 4U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_nargout, 5U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c1_Q1, 6U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c1_Q2, 7U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c1_q, 8U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  CV_SCRIPT_FCN(2, 0);
  _SFD_SCRIPT_CALL(2U, *c1_sfEvent, 44);
  c1_s1 = c1_Q1[0];
  _SFD_SCRIPT_CALL(2U, *c1_sfEvent, 44);
  c1_s2 = c1_Q2[0];
  _SFD_SCRIPT_CALL(2U, *c1_sfEvent, 45);
  for (c1_i41 = 0; c1_i41 < 3; c1_i41++) {
    c1_v1[c1_i41] = c1_Q1[c1_i41 + 1];
  }

  _SFD_SCRIPT_CALL(2U, *c1_sfEvent, 45);
  for (c1_i42 = 0; c1_i42 < 3; c1_i42++) {
    c1_v2[c1_i42] = c1_Q2[c1_i42 + 1];
  }

  _SFD_SCRIPT_CALL(2U, *c1_sfEvent, 47);
  c1_a = c1_s1;
  c1_b = c1_s2;
  c1_y = c1_a * c1_b;
  for (c1_i43 = 0; c1_i43 < 3; c1_i43++) {
    c1_b_a[c1_i43] = c1_v1[c1_i43];
  }

  for (c1_i44 = 0; c1_i44 < 3; c1_i44++) {
    c1_b_b[c1_i44] = c1_v2[c1_i44];
  }

  c1_b_eml_scalar_eg(chartInstance);
  c1_b_eml_scalar_eg(chartInstance);
  c1_b_y = 0.0;
  for (c1_k = 1; c1_k < 4; c1_k++) {
    c1_b_k = c1_k;
    c1_b_y += c1_b_a[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK
      ("", (real_T)c1_b_k), 1, 3, 1, 0) - 1] *
      c1_b_b[_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
      (real_T)c1_b_k), 1, 3, 1, 0) - 1];
  }

  c1_c_a = c1_s1;
  for (c1_i45 = 0; c1_i45 < 3; c1_i45++) {
    c1_b_b[c1_i45] = c1_v2[c1_i45];
  }

  for (c1_i46 = 0; c1_i46 < 3; c1_i46++) {
    c1_b_b[c1_i46] *= c1_c_a;
  }

  c1_d_a = c1_s2;
  for (c1_i47 = 0; c1_i47 < 3; c1_i47++) {
    c1_c_b[c1_i47] = c1_v1[c1_i47];
  }

  for (c1_i48 = 0; c1_i48 < 3; c1_i48++) {
    c1_c_b[c1_i48] *= c1_d_a;
  }

  for (c1_i49 = 0; c1_i49 < 3; c1_i49++) {
    c1_e_a[c1_i49] = c1_v1[c1_i49];
  }

  for (c1_i50 = 0; c1_i50 < 3; c1_i50++) {
    c1_d_b[c1_i50] = c1_v2[c1_i50];
  }

  c1_f_a = c1_e_a[1];
  c1_e_b = c1_d_b[2];
  c1_c_y = c1_f_a * c1_e_b;
  c1_g_a = c1_e_a[2];
  c1_f_b = c1_d_b[1];
  c1_d_y = c1_g_a * c1_f_b;
  c1_c1 = c1_c_y - c1_d_y;
  c1_h_a = c1_e_a[2];
  c1_g_b = c1_d_b[0];
  c1_e_y = c1_h_a * c1_g_b;
  c1_i_a = c1_e_a[0];
  c1_h_b = c1_d_b[2];
  c1_f_y = c1_i_a * c1_h_b;
  c1_c2 = c1_e_y - c1_f_y;
  c1_j_a = c1_e_a[0];
  c1_i_b = c1_d_b[1];
  c1_g_y = c1_j_a * c1_i_b;
  c1_k_a = c1_e_a[1];
  c1_j_b = c1_d_b[0];
  c1_h_y = c1_k_a * c1_j_b;
  c1_c3 = c1_g_y - c1_h_y;
  c1_e_a[0] = c1_c1;
  c1_e_a[1] = c1_c2;
  c1_e_a[2] = c1_c3;
  c1_q[0] = c1_y - c1_b_y;
  for (c1_i51 = 0; c1_i51 < 3; c1_i51++) {
    c1_q[c1_i51 + 1] = (c1_b_b[c1_i51] + c1_c_b[c1_i51]) + c1_e_a[c1_i51];
  }

  _SFD_SCRIPT_CALL(2U, *c1_sfEvent, -47);
  sf_debug_symbol_scope_pop();
}

static void c1_b_eml_scalar_eg(SFc1_QUARC_Prog_RoverInstanceStruct
  *chartInstance)
{
}

static real_T c1_mpower(SFc1_QUARC_Prog_RoverInstanceStruct *chartInstance,
  real_T c1_a)
{
  real_T c1_b_a;
  real_T c1_ak;
  c1_b_a = c1_a;
  c1_eml_scalar_eg(chartInstance);
  c1_ak = c1_b_a;
  return muDoubleScalarPower(c1_ak, 2.0);
}

static real_T c1_atan2(SFc1_QUARC_Prog_RoverInstanceStruct *chartInstance,
  real_T c1_y, real_T c1_x)
{
  real_T c1_b_y;
  real_T c1_b_x;
  c1_eml_scalar_eg(chartInstance);
  c1_b_y = c1_y;
  c1_b_x = c1_x;
  return muDoubleScalarAtan2(c1_b_y, c1_b_x);
}

static void c1_eml_error(SFc1_QUARC_Prog_RoverInstanceStruct *chartInstance)
{
  int32_T c1_i52;
  static char_T c1_varargin_1[30] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o',
    'o', 'l', 'b', 'o', 'x', ':', 'a', 's', 'i', 'n', '_', 'd', 'o', 'm', 'a',
    'i', 'n', 'E', 'r', 'r', 'o', 'r' };

  char_T c1_u[30];
  const mxArray *c1_y = NULL;
  for (c1_i52 = 0; c1_i52 < 30; c1_i52++) {
    c1_u[c1_i52] = c1_varargin_1[c1_i52];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 10, 0U, 1U, 0U, 2, 1, 30), FALSE);
  sf_mex_call_debug("error", 0U, 1U, 14, sf_mex_call_debug("message", 1U, 1U, 14,
    c1_y));
}

static const mxArray *c1_e_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_QUARC_Prog_RoverInstanceStruct *chartInstance;
  chartInstance = (SFc1_QUARC_Prog_RoverInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(int32_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static int32_T c1_f_emlrt_marshallIn(SFc1_QUARC_Prog_RoverInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  int32_T c1_y;
  int32_T c1_i53;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_i53, 1, 6, 0U, 0, 0U, 0);
  c1_y = c1_i53;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_sfEvent;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  int32_T c1_y;
  SFc1_QUARC_Prog_RoverInstanceStruct *chartInstance;
  chartInstance = (SFc1_QUARC_Prog_RoverInstanceStruct *)chartInstanceVoid;
  c1_sfEvent = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_sfEvent), &c1_thisId);
  sf_mex_destroy(&c1_sfEvent);
  *(int32_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static uint8_T c1_g_emlrt_marshallIn(SFc1_QUARC_Prog_RoverInstanceStruct
  *chartInstance, const mxArray *c1_is_active_c1_QUARC_Prog_Rover, const char_T *
  c1_identifier)
{
  uint8_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_h_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c1_is_active_c1_QUARC_Prog_Rover), &c1_thisId);
  sf_mex_destroy(&c1_is_active_c1_QUARC_Prog_Rover);
  return c1_y;
}

static uint8_T c1_h_emlrt_marshallIn(SFc1_QUARC_Prog_RoverInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  uint8_T c1_y;
  uint8_T c1_u0;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_u0, 1, 3, 0U, 0, 0U, 0);
  c1_y = c1_u0;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void init_dsm_address_info(SFc1_QUARC_Prog_RoverInstanceStruct
  *chartInstance)
{
}

/* SFunction Glue Code */
static uint32_T* sf_get_sfun_dwork_checksum();
void sf_c1_QUARC_Prog_Rover_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2402999952U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3150838758U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1059348237U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1558418511U);
}

mxArray *sf_c1_QUARC_Prog_Rover_get_autoinheritance_info(void)
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

static const mxArray *sf_get_sim_state_info_c1_QUARC_Prog_Rover(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[11],T\"Euler\",},{M[8],M[0],T\"is_active_c1_QUARC_Prog_Rover\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c1_QUARC_Prog_Rover_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc1_QUARC_Prog_RoverInstanceStruct *chartInstance;
    chartInstance = (SFc1_QUARC_Prog_RoverInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (_QUARC_Prog_RoverMachineNumber_,
           1,
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
            1.0,0,0,(MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 3;
          dimVector[1]= 1;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)
            c1_sf_marshallIn);
        }

        {
          real_T (*c1_Angles)[3];
          real_T (*c1_Euler)[3];
          c1_Euler = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
          c1_Angles = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c1_Angles);
          _SFD_SET_DATA_VALUE_PTR(1U, *c1_Euler);
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
      1, "dworkChecksum");
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

static void sf_opaque_initialize_c1_QUARC_Prog_Rover(void *chartInstanceVar)
{
  sf_check_dwork_consistency(((SFc1_QUARC_Prog_RoverInstanceStruct*)
    chartInstanceVar)->S);
  chart_debug_initialization(((SFc1_QUARC_Prog_RoverInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c1_QUARC_Prog_Rover((SFc1_QUARC_Prog_RoverInstanceStruct*)
    chartInstanceVar);
  initialize_c1_QUARC_Prog_Rover((SFc1_QUARC_Prog_RoverInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c1_QUARC_Prog_Rover(void *chartInstanceVar)
{
  enable_c1_QUARC_Prog_Rover((SFc1_QUARC_Prog_RoverInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c1_QUARC_Prog_Rover(void *chartInstanceVar)
{
  disable_c1_QUARC_Prog_Rover((SFc1_QUARC_Prog_RoverInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c1_QUARC_Prog_Rover(void *chartInstanceVar)
{
  sf_c1_QUARC_Prog_Rover((SFc1_QUARC_Prog_RoverInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_ext_mode_exec_c1_QUARC_Prog_Rover(void *chartInstanceVar)
{
  ext_mode_exec_c1_QUARC_Prog_Rover((SFc1_QUARC_Prog_RoverInstanceStruct*)
    chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c1_QUARC_Prog_Rover(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c1_QUARC_Prog_Rover
    ((SFc1_QUARC_Prog_RoverInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c1_QUARC_Prog_Rover();/* state var info */
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

extern void sf_internal_set_sim_state_c1_QUARC_Prog_Rover(SimStruct* S, const
  mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c1_QUARC_Prog_Rover();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c1_QUARC_Prog_Rover((SFc1_QUARC_Prog_RoverInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c1_QUARC_Prog_Rover(SimStruct* S)
{
  return sf_internal_get_sim_state_c1_QUARC_Prog_Rover(S);
}

static void sf_opaque_set_sim_state_c1_QUARC_Prog_Rover(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c1_QUARC_Prog_Rover(S, st);
}

static void sf_opaque_terminate_c1_QUARC_Prog_Rover(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc1_QUARC_Prog_RoverInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
    }

    finalize_c1_QUARC_Prog_Rover((SFc1_QUARC_Prog_RoverInstanceStruct*)
      chartInstanceVar);
    free((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }

  unload_QUARC_Prog_Rover_optimization_info();
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc1_QUARC_Prog_Rover((SFc1_QUARC_Prog_RoverInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c1_QUARC_Prog_Rover(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c1_QUARC_Prog_Rover((SFc1_QUARC_Prog_RoverInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

mxArray *sf_c1_QUARC_Prog_Rover_get_testpoint_info(void)
{
  const char *infoEncStr[] = {
    "100 S'varName','path'{{T\"is_active_c1_QUARC_Prog_Rover\",T\"is_active_c1_QUARC_Prog_Rover\"}}"
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

static void mdlSetWorkWidths_c1_QUARC_Prog_Rover(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_QUARC_Prog_Rover_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,infoStruct,1);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,infoStruct,1,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,infoStruct,1,
      "gatewayCannotBeInlinedMultipleTimes"));
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,infoStruct,1,1);
      sf_mark_chart_reusable_outputs(S,infoStruct,1,1);
    }

    sf_set_rtw_dwork_info(S,infoStruct,1);
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

static void mdlRTW_c1_QUARC_Prog_Rover(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c1_QUARC_Prog_Rover(SimStruct *S)
{
  SFc1_QUARC_Prog_RoverInstanceStruct *chartInstance;
  chartInstance = (SFc1_QUARC_Prog_RoverInstanceStruct *)malloc(sizeof
    (SFc1_QUARC_Prog_RoverInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc1_QUARC_Prog_RoverInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c1_QUARC_Prog_Rover;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c1_QUARC_Prog_Rover;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c1_QUARC_Prog_Rover;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c1_QUARC_Prog_Rover;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c1_QUARC_Prog_Rover;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c1_QUARC_Prog_Rover;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c1_QUARC_Prog_Rover;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c1_QUARC_Prog_Rover;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c1_QUARC_Prog_Rover;
  chartInstance->chartInfo.mdlStart = mdlStart_c1_QUARC_Prog_Rover;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c1_QUARC_Prog_Rover;
  chartInstance->chartInfo.extModeExec =
    sf_opaque_ext_mode_exec_c1_QUARC_Prog_Rover;
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

void c1_QUARC_Prog_Rover_method_dispatcher(SimStruct *S, int_T method, void
  *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c1_QUARC_Prog_Rover(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c1_QUARC_Prog_Rover(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c1_QUARC_Prog_Rover(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c1_QUARC_Prog_Rover_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
