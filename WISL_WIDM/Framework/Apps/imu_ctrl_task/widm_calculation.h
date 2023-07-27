/*
 * widm_calculataion.h
 *
 *  Created on: 2023. 2. 6.
 *      Author: ONE
 */

#ifndef FRAMEWORK_APPS_IMU_CTRL_TASK_WIDM_CALCULATION_H_
#define FRAMEWORK_APPS_IMU_CTRL_TASK_WIDM_CALCULATION_H_

#include "main.h"

#include <math.h>
#include <string.h>

/* Definition of Constant */
#define IMU_CONTROL_PERIOD	0.001
#define PI					3.141592
#define PLANTAR_REF_OFFSET 	5.0
#define DORSI_REF_OFFSET 	5.0

/* Assist Mode */
#define ASSIST_ON			1
#define ASSIST_OFF			0

/* Reference Shape */
#define TRAPEZOIDAL			0

/* Definition of enum */
typedef enum _WalkingState{
	e_STOP,
	e_WALKING_START,
	e_WALKING_HALF,
	e_WALKING_ONE_CYCLE,
} WalkingState;

typedef enum _GaitPhaseTimeState{
	e_STANDBY,
	e_RISING,
	e_CONTINUOUS,
	e_FALLING,
	e_END
} GaitPhaseTimeState;

typedef enum _AssistType{
    e_PLANTAR,
    e_DORSI
} AssistType;

typedef enum _AttachPlane{
	e_LEFT_SAGITAL,
	e_RIGHT_SAGITAL,
	e_LEFT_SAGITAL_DEMO
} AttachPlane;


/* Definition of Struct */
typedef struct _Sensor_Params{
	float accX[2];			// [0] is current value, [1] is previous value (Accelerometer X axis)
	float accY[2];			// [0] is current value, [1] is previous value (Accelerometer Y axis)
	float accZ[2];
	float gyrX[2];
	float gyrY[2];
	float gyrZ[2];			// [0] is current value, [1] is previous value (Gyroscope Z axis)
	float magX[2];
	float magY[2];
	float magZ[2];
} Sensor_Params;

typedef struct _Thigh_Angle_Params{
	float angle_init;			// initally will be set angle(degree) maybe 0

	float deg_acc;				// Angle using Accelerometer measurements
	float deg_gyr;				// Angle using Gyroscope measurements

	float deg_acc_filtered;		// Angle through LPF(Acc)
	float deg_gyr_filtered;		// Angle through HPF(Gyro)
	float deg_tvcf_filtered;	// Angle through TVCF

	float vel_raw[2];			// [0] is current value, [1] is previous value (velocity)
	float deg_tvcf[2];			// [0] is current value, [1] is previous value (Angel(degree) through TVCF)
	float deg_LPF_1st[2];		// [0] is current value, [1] is previous value (Angle(degree) through 1st order LPF)
	float deg_LPF_2nd[2];		// [0] is current value, [1] is previous value (Angle(degree) through 2nd order LPF)
	float vel_LPF_1st[2];		// [0] is current value, [1] is previous value (Angular velocity through 1st order LPF)
	float vel_LPF_2nd[2];		// [0] is current value, [1] is previous value (Angular velocity through 2nd order LPF)
} Thigh_Angle_Params;

typedef struct _Normalization_Params{
	float deg_o;		// Center point location of elliptical graph before normalization
	float vel_o;		// Center point location of elliptical graph before normalization
	float sum_deg;		// Sum of angle for calculating deg_o
	float sum_vel;		// Sum of angular velocity for calculating vel_o
	uint16_t sum_i;		// Sum of number(gait phase 50%) for calculating deg_o, vel_o

	float deg_max;		// Max of angle in elliptical plot
	float deg_min;		// Min of angle in elliptical plot
	float vel_max;		// Max of angular velocity in elliptical plot
	float vel_min;		// Min of angular velocity in elliptical plot

	float deg_norm;		// Current angle value on circle after normalization
	float vel_norm;		// Current angular velocity value on circle after normalization

	float A_deg;		// Amplitude of angle of an elliptical graph before normalization
	float A_vel;		// Amplitude of angular velocity of an elliptical graph before normalization
} Normalization_Params;

typedef struct _Gait_Params{
	uint16_t gait_period;	// Gait Period (ms) < 2000ms
	float gait_phase;		// Current Gait Phase 0 ~ 100%
	float gait_phase_pre;	// Previous Gait Phase
} Gait_Params;

typedef struct _Fuzzy_Params{
	float Fuzzy_input[4];	// Acc, Jerk, Gyro, Wdot(measurement value)
	float wc;				// Cut off Frequency
	float wl;				// Low Frequency
	float wh;				// High Frequency
	float var[4];			// Acc, Jerk, Gyro, Wdot-variance(initially set velue)
} Fuzzy_Params;

typedef struct _Threshold_Params{
	float deg_th_start;			// Angle Threshold (Gait Phase Stop)
	float vel_th_start;			// Angular Velocity Threshold (Gait Phase Stop)
	float deg_th_stop;			// Angle Threshold (Gait Phase Stop)
	float vel_th_stop;			// Angular Velocity Threshold (Gait Phase Stop)
} Threshold_Params;

typedef struct _Assist_Params{
	/* Assist Force Time Params (ms)*/
	uint16_t t_P_start;		// Start Time Plantar
	uint16_t t_D_start;		// Start Time Dorsi
	uint16_t t_r_P_end;		// Rising End Time Plantar
	uint16_t t_c_P_end;		// Continuous End Time Plantar
	uint16_t t_f_P_end;		// Falling End Time Plantar
	uint16_t t_r_D_end;		// Rising End Time Dorsi
	uint16_t t_c_D_end;		// Continuouse End Time Dorsi
	uint16_t t_f_D_end;		// Falling End Time Dorsi
	uint16_t t_r_P;			// Rising Time Plantar
	uint16_t t_c_P;			// Continuous Time Plantar
	uint16_t t_f_P;			// Falling Time Plantar
	uint16_t t_r_D;			// Rising Time Dorsi
	uint16_t t_c_D;			// Continuouse Time Dorsi
	uint16_t t_f_D;			// Falling Time Dorsi
	uint16_t t_r_limit;		// Rising Time Limit
	uint16_t t_f_limit;		// Falling Time Limit

	uint8_t ref_shape;		// Reference Shape(0=Trapezoidal, ...)

	uint8_t manual_time_set_P;	// Set Manual rising/continuous/falling time Plantar
	uint8_t manual_time_set_D;	// Set Manual rising/continuous/falling time Dorsi

	uint8_t phase_state_P;		// Phase State (0 = standby state, 1 = rising time state, 2 = continuous time state, 3 = falling time state, 4 = end state) Plantar
	uint8_t phase_state_D;		// Phase State (0 = standby state, 1 = rising time state, 2 = continuous time state, 3 = falling time state, 4 = end state) Plantar
	uint16_t phase_loop_time_P;	// Phase State Loop Time Plantar(ms)
	uint16_t phase_loop_time_D;	// Phase State Loop Time Dorsi(ms)

	uint8_t trigger_P;		// if walking state is 3, trigger 1 - Assist Mode ON
	uint8_t trigger_D;		// if walking state is 3, trigger 1 - Assist Mode ON

	float Plantar_ref;		// Reference Input Plantar
	float Dorsi_ref;		// Reference Input Dorsi
	float Amplitude_P;		// Amplitude Plantar
	float Amplitude_D;		// Amplitude Dorsi
} Assist_Params;

typedef struct _Assist_Params_P{
	/* Assist Force Time Params (ms)*/
	uint16_t t_P_start;		// Start Time Plantar
	uint16_t t_r_P_end;		// Rising End Time Plantar
	uint16_t t_c_P_end;		// Continuous End Time Plantar
	uint16_t t_f_P_end;		// Falling End Time Plantar
	uint16_t t_r_P;			// Rising Time Plantar
	uint16_t t_c_P;			// Continuous Time Plantar
	uint16_t t_f_P;			// Falling Time Plantar
	uint16_t t_r_limit;		// Rising Time Limit
	uint16_t t_f_limit;		// Falling Time Limit

	uint8_t ref_shape;		// Reference Shape(0=Trapezoidal, ...)

	uint8_t manual_time_set_P;	// Set Manual rising/continuous/falling time Plantar

	uint8_t phase_state_P;		// Phase State (0 = standby state, 1 = rising time state, 2 = continuous time state, 3 = falling time state, 4 = end state) Plantar
	uint16_t phase_loop_time_P;	// Phase State Loop Time Plantar(ms)

	uint8_t trigger_P;		// if walking state is 3, trigger 1 - Assist Mode ON

	float Plantar_ref;		// Reference Input Plantar
	float Amplitude_P;		// Amplitude Plantar
} Assist_Params_P;

typedef struct _Assist_Params_D{
	/* Assist Force Time Params (ms)*/
	uint16_t t_D_start;		// Start Time Dorsi
	uint16_t t_r_D_end;		// Rising End Time Dorsi
	uint16_t t_c_D_end;		// Continuouse End Time Dorsi
	uint16_t t_f_D_end;		// Falling End Time Dorsi
	uint16_t t_r_D;			// Rising Time Dorsi
	uint16_t t_c_D;			// Continuouse Time Dorsi
	uint16_t t_f_D;			// Falling Time Dorsi
	uint16_t t_r_limit;		// Rising Time Limit
	uint16_t t_f_limit;		// Falling Time Limit

	uint8_t ref_shape;		// Reference Shape(0=Trapezoidal, ...)
	uint8_t manual_time_set_D;	// Set Manual rising/continuous/falling time Dorsi

	uint8_t phase_state_D;		// Phase State (0 = standby state, 1 = rising time state, 2 = continuous time state, 3 = falling time state, 4 = end state) Plantar
	uint16_t phase_loop_time_D;	// Phase State Loop Time Dorsi(ms)

	uint8_t trigger_D;		// if walking state is 3, trigger 1 - Assist Mode ON

	float Dorsi_ref;		// Reference Input Dorsi
	float Amplitude_D;		// Amplitude Dorsi
} Assist_Params_D;

/* Calculate Functions */
float Calculate_Square_Root_Sum(float t_x, float t_y);
float Calculate_Absolute_Value_Float(float t_value);

/* Set Parameters */
void Set_Init_Parameters(Normalization_Params* t_norm_params, Gait_Params* t_gait_params, Fuzzy_Params* t_fuzzy_params, Threshold_Params* t_th_params, Assist_Params* t_assist_params);

/* Save Previous Value */
void Save_Previous_Value(Sensor_Params* t_sensor_params, Thigh_Angle_Params* t_thigh_angle_params, Gait_Params* t_gait_params);

/* Fuzzy Logic */
void Generate_Fuzzy_Input(Sensor_Params* t_sensor_params, Fuzzy_Params* t_fuzzy_params);
float Calculate_Fuzzy_Wc(Fuzzy_Params* t_fuzzy_params);

/* Filters (LPF, HPF, TVCF) */
float Perform_LPF_on_Acc(float t_curr_acc, float t_prev_filterd_acc, float t_cutoff_frequency, float t_sampling_Period);
float Perform_HPF_on_Gyro(float t_curr_gyro, float t_prev_filterd_gyro, float t_cutoff_frequency, float t_sampling_Period);
void Run_TVCF(Sensor_Params* t_sensor_params, Thigh_Angle_Params* t_thigh_angle_params, float t_cutoff_frequency, float t_sampling_Period, AttachPlane t_attach_plane);

/* Get Max or Min Value between two variables */
float Get_Max_Float(float t_x, float t_y);
float Get_Min_Float(float t_x, float t_y);

/* Normalization & Get Gait Phase */
void Set_First_Half_Gait_Phase_Parameters(Normalization_Params* t_norm_params, Gait_Params* t_gait_params);
void Set_Second_Half_Gait_Phase_Parameters(Normalization_Params* t_norm_params, Thigh_Angle_Params* t_thigh_angle_params);
void Prepare_for_Circular_Normalization(Thigh_Angle_Params* t_thigh_angle_params, Normalization_Params* t_norm_params, Gait_Params* t_gait_params);
float Get_Current_Gait_Phase(Normalization_Params* t_norm_params, Gait_Params* t_gait_params);

/* Generate Assit Force */
void Calculate_Assist_Force_Timing_Params(uint16_t* t_r, uint16_t* t_c, uint16_t* t_f, uint16_t t_r_end, uint16_t t_start, uint16_t t_c_end, uint16_t t_f_end, uint16_t t_t_r_limit, uint16_t t_t_f_limit, uint16_t t_gait_period);
void Update_Assist_Params(Assist_Params* t_assist_params, float t_new_tension_ref, AssistType t_assist_type);
void Transfer_Phase_State(Assist_Params* t_assist_params, AssistType t_pd_sel);
void Set_Assist_Force_Timing_Params(Assist_Params* t_assist_params, Gait_Params* t_gait_params);
//void Update_Plantar_Assist_Force(Assist_Params* t_assist_params);
//void Update_Dorsi_Assist_Force(Assist_Params* t_assist_params);
void Update_Assist_Force(Assist_Params* t_assist_params, AssistType t_pd_sel);

#endif /* FRAMEWORK_APPS_IMU_CTRL_TASK_WIDM_CALCULATION_H_ */
