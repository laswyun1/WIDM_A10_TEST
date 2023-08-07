/*
 * widm_calculation.c
 *
 *  Created on: Aug 7, 2023
 *      Author: Seung-WonYun
 */



#include "widm_calculation.h"

/*

   ___       _ _   _       _ _          _   _
  |_ _|_ __ (_) |_(_) __ _| (_)______ _| |_(_) ___  _ __
   | || '_ \| | __| |/ _` | | |_  / _` | __| |/ _ \| '_ \
   | || | | | | |_| | (_| | | |/ / (_| | |_| | (_) | | | |
  |___|_| |_|_|\__|_|\__,_|_|_/___\__,_|\__|_|\___/|_| |_|


*/

/* Set Specific Value */
void Set_Init_Parameters(Normalization_Params* t_norm_params, Gait_Params* t_gait_params, Fuzzy_Params* t_fuzzy_params, Threshold_Params* t_th_params, Plantar_Params* t_plantar_params, Dorsi_Params* t_dorsi_params, Assist_Params* t_assist_params)
{
	t_norm_params->A_deg = 30.0; //30
	t_norm_params->A_vel = 400.0; //400

	t_gait_params->gait_period 	  = 1000;
	t_gait_params->gait_phase 	  = -100.0;
	t_gait_params->gait_phase_pre = -100.0;

	t_fuzzy_params->wl 		= 0.5;
	t_fuzzy_params->wh 		= 10.0;
	t_fuzzy_params->var[0] 	= 8.0;
	t_fuzzy_params->var[1] 	= 30.0;
	t_fuzzy_params->var[2] 	= 5.8;
	t_fuzzy_params->var[3] 	= 320.0;

	t_th_params->deg_th_start	= 5.0;
	t_th_params->vel_th_start	= 20.0;
	t_th_params->deg_th_stop 	= 5.0;
	t_th_params->vel_th_stop 	= 3.0;

	t_plantar_params->t_P_start	  = 35;
	t_plantar_params->t_r_P_end   = 35;
	t_plantar_params->t_c_P_end   = 55;
	t_plantar_params->t_f_P_end   = 60;
	t_plantar_params->t_r_P       = 100;
	t_plantar_params->t_c_P 	  = 400;
	t_plantar_params->t_f_P 	  = 100;
	t_plantar_params->Amplitude_P = 60.0;

	t_dorsi_params->t_D_start 	  = 50;
	t_dorsi_params->t_r_D_end 	  = 53;
	t_dorsi_params->t_c_D_end 	  = 70;
	t_dorsi_params->t_f_D_end 	  = 80;
	t_dorsi_params->t_r_D 		  = 100;
	t_dorsi_params->t_c_D 		  = 400;
	t_dorsi_params->t_f_D 		  = 100;
	t_dorsi_params->Amplitude_D   = 60.0;

	t_assist_params->t_r_limit 	 = 20;
	t_assist_params->t_f_limit 	 = 20;
	t_assist_params->ref_shape 	 = TRAPEZOIDAL;
}

/*

   ____                    ____                 _                  __     __    _
  / ___|  __ ___   _____  |  _ \ _ __ _____   _(_) ___  _   _ ___  \ \   / /_ _| |_   _  ___
  \___ \ / _` \ \ / / _ \ | |_) | '__/ _ \ \ / / |/ _ \| | | / __|  \ \ / / _` | | | | |/ _ \
   ___) | (_| |\ V /  __/ |  __/| | |  __/\ V /| | (_) | |_| \__ \   \ V / (_| | | |_| |  __/
  |____/ \__,_| \_/ \___| |_|   |_|  \___| \_/ |_|\___/ \__,_|___/    \_/ \__,_|_|\__,_|\___|


*/

void Save_Previous_Value(Sensor_Params* t_sensor_params, Thigh_Angle_Params* t_thigh_angle_params, Gait_Params* t_gait_params)
{
	t_sensor_params->accX[1] = t_sensor_params->accX[0];
	t_sensor_params->accY[1] = t_sensor_params->accY[0];
	t_sensor_params->gyrZ[1] = t_sensor_params->gyrZ[0];

	t_thigh_angle_params->vel_raw[1] = t_thigh_angle_params->vel_raw[0];

	t_thigh_angle_params->deg_tvcf[1] = t_thigh_angle_params->deg_tvcf[0];

	t_thigh_angle_params->deg_LPF_1st[1] = t_thigh_angle_params->deg_LPF_1st[0];
	t_thigh_angle_params->deg_LPF_2nd[1] = t_thigh_angle_params->deg_LPF_2nd[0];
	t_thigh_angle_params->vel_LPF_1st[1] = t_thigh_angle_params->vel_LPF_1st[0];
	t_thigh_angle_params->vel_LPF_2nd[1] = t_thigh_angle_params->vel_LPF_2nd[0];

	t_gait_params->gait_phase_pre = t_gait_params->gait_phase;
}

/*

   _____                      _                _
  |  ___|   _ _________   _  | |    ___   __ _(_) ___
  | |_ | | | |_  /_  / | | | | |   / _ \ / _` | |/ __|
  |  _|| |_| |/ / / /| |_| | | |__| (_) | (_| | | (__
  |_|   \__,_/___/___|\__, | |_____\___/ \__, |_|\___|
                      |___/              |___/

*/

float Calculate_Square_Root_Sum(float t_x, float t_y)
{
	return sqrt(pow(t_x, 2) + pow(t_y, 2));
}

float Calculate_Absolute_Value_Float(float t_value)
{
	return fabs(t_value);
}

float Calculate_Delta(float t_current, float t_previous)
{
	return (t_current - t_previous) / IMU_CONTROL_PERIOD;
}

void Calculate_xbar_Update_mu(float t_var_i, float t_fuzzy_input, float* t_mu)
{
	/* t_var_i is measurement value (initially set value in Set_Init_Parameters) */
	float t_xoi = 3 * t_var_i;											// Threshold Value (maybe middle value)
	float t_si = log(3) / t_var_i;										// Sensor Sensitivity (natural logarithm)
	float t_xbar = 0.5 * (1 + tanh(t_si * (t_fuzzy_input - t_xoi)));	// Fuzzy Logic Relational Expressions
	*t_mu *= (1 - t_xbar);	// Update mu for TVCF cutoff frequency(wc)
}

/*
*Generate Fuzzy Logic Input (Acc, Jerk, Angular Velocity, Angular Accerleration)
*/
void Generate_Fuzzy_Input(Sensor_Params* t_sensor_params, Fuzzy_Params* t_fuzzy_params)
{
	float t_jerk_x = Calculate_Delta(t_sensor_params->accX[0], t_sensor_params->accX[1]);
	float t_jerk_y = Calculate_Delta(t_sensor_params->accY[0], t_sensor_params->accY[1]);
	float t_wdot_z = Calculate_Delta(t_sensor_params->gyrZ[0], t_sensor_params->gyrZ[1]);

	// absolute ACC
	t_fuzzy_params->Fuzzy_input[0] = Calculate_Square_Root_Sum(t_sensor_params->accX[0], t_sensor_params->accY[0]);
	// absolute Jerk
	t_fuzzy_params->Fuzzy_input[1] = Calculate_Square_Root_Sum(t_jerk_x, t_jerk_y);
	// absolute Gyr(Angular Velocity)
	t_fuzzy_params->Fuzzy_input[2] = Calculate_Absolute_Value_Float(t_sensor_params->gyrZ[0]);
	// absolute Wdot(Angular Acceleration)
	t_fuzzy_params->Fuzzy_input[3] = Calculate_Absolute_Value_Float(t_wdot_z);
}

/*
*Calculate Wc(CutOff Frequency)
*/
float Calculate_Fuzzy_Wc(Fuzzy_Params* t_fuzzy_params)
{
	t_fuzzy_params->wc = 0;
	float t_mu = 1;

	/* Perform calculations for each fuzzy input (Acc, Jerk, Angular Velocity, Angular Accerleration) */
	for (int i = 0; i < 4; i++) {
		Calculate_xbar_Update_mu(t_fuzzy_params->var[i], t_fuzzy_params->Fuzzy_input[i], &t_mu);
	}

	t_fuzzy_params->wc = t_mu * (t_fuzzy_params->wh) + (1 - t_mu) * (t_fuzzy_params->wl);

	return t_fuzzy_params->wc;
}

/*

   _____ _ _ _
  |  ___(_) | |_ ___ _ __ ___
  | |_  | | | __/ _ \ '__/ __|
  |  _| | | | ||  __/ |  \__ \
  |_|   |_|_|\__\___|_|  |___/


*/

/*
*Low pass filtering for deg_acc
*/
float Perform_LPF_on_Acc(float t_curr_acc, float t_prev_filtered_acc, float t_cutoff_frequency, float t_sampling_Period)
{
	float filtered_acc = (t_cutoff_frequency * t_sampling_Period * t_curr_acc + t_prev_filtered_acc) / (t_cutoff_frequency * t_sampling_Period + 1);
	return filtered_acc;
}

/*
*High pass filtering + Integral for gyr
*/
float Perform_HPF_on_Gyro(float t_curr_gyro, float t_prev_filtered_gyro, float t_cutoff_frequency, float t_sampling_Period)
{
	float filtered_gyro = (t_curr_gyro*t_sampling_Period + t_prev_filtered_gyro) / (t_cutoff_frequency * t_sampling_Period + 1);
	return filtered_gyro;
}

/*
*Function to apply a Time Variant Complementary Filter (TVCF) to an angle
*/
void Run_TVCF(Sensor_Params* t_sensor_params, Thigh_Angle_Params* t_thigh_angle_params, float t_cutoff_frequency, float t_sampling_Period, AttachPlane t_attach_plane)
{
	/* Calculate the angle using accelerometer measurements and convert it to degrees */
    /* Thigh Angle Degree */
	float t_deg_acc = 0.0;
	float t_deg_acc_filtered_update = 0.0;
	float t_deg_gyr_filtered_update = 0.0;
	float t_deg_tvcf = 0.0;

	t_deg_acc = Get_Angle_Scenario(t_sensor_params, t_attach_plane);

	/* Apply Low Pass Filter (LPF) on accelerometer angle */
	t_deg_acc_filtered_update = Perform_LPF_on_Acc(t_deg_acc, t_thigh_angle_params->deg_acc_filtered, t_cutoff_frequency, t_sampling_Period);

	/* Apply High Pass Filter (HPF) on gyroscope measurements */
	t_deg_gyr_filtered_update = Perform_HPF_on_Gyro(t_sensor_params->gyrZ[0], t_thigh_angle_params->deg_gyr_filtered, t_cutoff_frequency, t_sampling_Period);

	/* Combine filtered accelerometer and gyroscope measurements */
	t_deg_tvcf = t_deg_acc_filtered_update + t_deg_gyr_filtered_update;

	t_thigh_angle_params->deg_acc_filtered = t_deg_acc_filtered_update;
	t_thigh_angle_params->deg_gyr_filtered = t_deg_gyr_filtered_update;
	t_thigh_angle_params->deg_tvcf_filtered = t_deg_tvcf;
}

/*

    ____       _ _     _____                 _   _
   / ___| __ _(_) |_  |  ___|   _ _ __   ___| |_(_) ___  _ __  ___
  | |  _ / _` | | __| | |_ | | | | '_ \ / __| __| |/ _ \| '_ \/ __|
  | |_| | (_| | | |_  |  _|| |_| | | | | (__| |_| | (_) | | | \__ \
   \____|\__,_|_|\__| |_|   \__,_|_| |_|\___|\__|_|\___/|_| |_|___/


*/

/*
*Get Max or Min Value between two variables for Normalization
*/
float Get_Max_Float(float t_x, float t_y)
{
	return (t_x > t_y) ? t_x: t_y;
}

float Get_Min_Float(float t_x, float t_y)
{
	return (t_x < t_y) ? t_x : t_y;
}

void Set_First_Half_Gait_Phase_Parameters(Normalization_Params* t_norm_params, Gait_Params* t_gait_params)
{
	t_norm_params->deg_o = t_norm_params->sum_deg / t_norm_params->sum_i;
	t_norm_params->vel_o = t_norm_params->sum_vel / t_norm_params->sum_i;

	t_gait_params->gait_period = t_norm_params->sum_i;

	t_norm_params->A_deg = (t_norm_params->deg_max - t_norm_params->deg_min) / 2;
	t_norm_params->A_vel = (t_norm_params->vel_max - t_norm_params->vel_min) / 2;
	t_norm_params->sum_i = 0;
	t_norm_params->sum_deg = 0;
	t_norm_params->sum_vel = 0;
	t_norm_params->deg_max = 0;
	t_norm_params->vel_max = 0;
	t_norm_params->deg_min = 0;
	t_norm_params->vel_min = 0;
}

void Set_Second_Half_Gait_Phase_Parameters(Normalization_Params* t_norm_params, Thigh_Angle_Params* t_thigh_angle_params)
{
	t_norm_params->sum_i++;
	t_norm_params->sum_deg += t_thigh_angle_params->deg_LPF_2nd[0];
	t_norm_params->sum_vel += t_thigh_angle_params->vel_LPF_2nd[0];
	t_norm_params->deg_max = Get_Max_Float(t_thigh_angle_params->deg_LPF_2nd[0], t_norm_params->deg_max);
	t_norm_params->deg_min = Get_Min_Float(t_thigh_angle_params->deg_LPF_2nd[0], t_norm_params->deg_min);
	t_norm_params->vel_max = Get_Max_Float(t_thigh_angle_params->vel_LPF_2nd[0], t_norm_params->vel_max);
	t_norm_params->vel_min = Get_Min_Float(t_thigh_angle_params->vel_LPF_2nd[0], t_norm_params->vel_min);
}

/*
*Function to Prepare for Circular Normalization
*/
void Prepare_for_Circular_Normalization(Thigh_Angle_Params* t_thigh_angle_params, Normalization_Params* t_norm_params, Gait_Params* t_gait_params)
{
	if (t_thigh_angle_params->vel_LPF_2nd[0] < 0 && t_thigh_angle_params->vel_LPF_2nd[1] > 0
		&& t_norm_params->sum_i > (t_gait_params->gait_period)*0.5) {
		Set_First_Half_Gait_Phase_Parameters(t_norm_params, t_gait_params);
	}
	else{
		Set_Second_Half_Gait_Phase_Parameters(t_norm_params, t_thigh_angle_params);
	}
}

/*
*Function to calculate the current phase of the gait (0~100%)
*/
float Get_Current_Gait_Phase(Normalization_Params* t_norm_params, Gait_Params* t_gait_params)
{
	/* Calculate initial phase using atan function */
	float t_gait_phase = atan((-1) * (t_norm_params->vel_norm) / (t_norm_params->deg_norm));

	/* Adjust phase based on the value of normalized degree */
    if (t_norm_params->deg_norm < 0){
        t_gait_phase += PI;
    } else if (t_norm_params->deg_norm > 0 && t_norm_params->vel_norm > 0){
        t_gait_phase += 2 * PI;
    }

	/* Convert phase from radians to custom scale */
    t_gait_phase = t_gait_phase * 50.0f / PI;
    t_gait_phase -= 12.11;

    /* Adjust phase if it falls outside the range 0-100 */
    if (t_gait_phase < 0 && t_gait_phase != -100){
        t_gait_phase += 100;
    }

    /* Compare phase with the stored gait phase in gaitInfo */
    if (t_gait_phase > 5 && t_gait_phase < 95){
        t_gait_phase = Get_Max_Float(t_gait_phase, t_gait_params->gait_phase);
	}

	return t_gait_phase;	// 0 ~ 100%
}

/*
*Function to Calculate timing parameters for Plantar&Dorsi assistance force
*/
static void Calculate_Assist_Force_Timing_Params(uint16_t* t_r, uint16_t* t_c, uint16_t* t_f, uint16_t t_r_end, uint16_t t_start, uint16_t t_c_end, uint16_t t_f_end, uint16_t t_t_r_limit, uint16_t t_t_f_limit, uint16_t t_gait_period)
{
	*t_r = (t_r_end - t_start) * t_gait_period / 100;
	*t_c = (t_c_end - t_r_end) * t_gait_period / 100;
	*t_f = (t_f_end - t_c_end) * t_gait_period / 100;

	if (*t_r < t_t_r_limit){
		*t_c = *t_c - t_t_r_limit + *t_r;
		*t_r = t_t_r_limit;
	}
	if (*t_f < t_t_f_limit){
		*t_c = *t_c - t_t_f_limit + *t_f;
		*t_f = t_t_f_limit;
	}
	if (*t_c < 0){
		*t_c = 0;
	}
}

/*
*Function to Set timing parameters for Plantar&Dorsi assistance force(rising, continuous, falling time)
*/

void Set_Assist_Force_Timing_Params(Plantar_Params* t_plantar_params, Dorsi_Params* t_dorsi_params, Assist_Params* t_assist_params, Gait_Params* t_gait_params)
{
	if (t_gait_params->gait_period > 2000){
		t_gait_params->gait_period = 2000;
	}

	/* Calculate timing parameters for Plantar assistance force */
	Calculate_Assist_Force_Timing_Params(
            &t_plantar_params->t_r_P,        // Plantar rising time
            &t_plantar_params->t_c_P,        // Plantar continuous time
            &t_plantar_params->t_f_P,        // Plantar falling time
			t_plantar_params->t_r_P_end,     // Plantar rising end time
			t_plantar_params->t_P_start, 	// Plantar start time
			t_plantar_params->t_c_P_end,     // Plantar continuous end time
			t_plantar_params->t_f_P_end,     // Plantar falling end time
            t_assist_params->t_r_limit,    	// Rising time limit
            t_assist_params->t_f_limit,    	// Falling time limit
            t_gait_params->gait_period      // Gait period
	);
	/* Calculate timing parameters for Dorsiflexion assistance force */
	Calculate_Assist_Force_Timing_Params(
           	&t_dorsi_params->t_r_D,        // Dorsi rising time
            &t_dorsi_params->t_c_D,        // Dorsi continuous time
            &t_dorsi_params->t_f_D,        // Dorsi falling time
			t_dorsi_params->t_r_D_end,     // Dorsi rising end time
			t_dorsi_params->t_D_start,   	// Dorsi start time
			t_dorsi_params->t_c_D_end,     // Dorsi continuous end time
			t_dorsi_params->t_f_D_end,     // Dorsi falling end time
            t_assist_params->t_r_limit,    	// Rising time limit
            t_assist_params->t_f_limit,   	// Falling time limit
            t_gait_params->gait_period      // Gait period
	);
}


float Get_Angle_Scenario(Sensor_Params* t_sensor_params, AttachPlane t_attach_plane)
{
	float estimated_angle = 0.0;

	switch (t_attach_plane)
	{
		case (e_LEFT_SAGITAL):
			estimated_angle = atan2((t_sensor_params->accY[0])*(-1), (t_sensor_params->accX[0])*(-1)) * (180 / PI);	// arctan(-y/-x) : Left Sagital case
			return estimated_angle;

		case (e_RIGHT_SAGITAL):
			estimated_angle = atan2(t_sensor_params->accY[0], (t_sensor_params->accX[0])*(-1)) * (180 / PI);	// arctan(y/-x) : Right Sagital case
			return estimated_angle;

		case (e_LEFT_SAGITAL_DEMO):
			estimated_angle = atan2(t_sensor_params->accX[0], (t_sensor_params->accY[0])*(-1)) * (180 / PI);	// arctan(x/-y) : Left Sagital DEMO ver case
			return estimated_angle;

		case (e_CM_TEST):
			estimated_angle = atan2(t_sensor_params->accX[0], (t_sensor_params->accY[0])*(-1)) * (180 / PI);	// arctan(x/-y) : FOR CM TEST

		default:
			return estimated_angle;
	}
}



