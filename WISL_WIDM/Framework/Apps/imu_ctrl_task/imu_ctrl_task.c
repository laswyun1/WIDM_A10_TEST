/*
 * imu_ctrl_task.c
 *
 *  Created on: 2022. 1. 4.
 *      Author: ONE
 */


#include "imu_ctrl_task.h"

/*
 ___     _          _          __              _   _
 | _ \_ _(_)_ ____ _| |_ ___   / _|_  _ _ _  __| |_(_)___ _ _  ___
 |  _/ '_| \ V / _` |  _/ -_) |  _| || | ' \/ _|  _| / _ \ ' \(_-<
 |_| |_| |_|\_/\__,_|\__\___| |_|  \_,_|_||_\__|\__|_\___/_||_/__/

*/

/* Reset Value Zero */
static void Reset_Parameters( )
{
	sensor_params 		= 	(Sensor_Params){0};
	norm_params 		= 	(Normalization_Params){0};
	gait_params 		= 	(Gait_Params){0};
	fuzzy_params 		= 	(Fuzzy_Params){0};
	thigh_angle_params 	= 	(Thigh_Angle_Params){0};
	th_params 			= 	(Threshold_Params){0};
	plantar_params      = 	(Plantar_Params){0};
	dorsi_params		= 	(Dorsi_Params){0};
	assist_params		= 	(Assist_Params){0};

	walking 				=	0;
	attach_plane 			=	e_LEFT_SAGITAL;
	wc_test					= 	0.0;
	thigh_angle_tvcf_demo   =   0.0;
}


static void Set_Initial_Angle_Values(Thigh_Angle_Params* t_thigh_angle_params, Normalization_Params* t_norm_params, float t_initial_angle)
{
    t_thigh_angle_params->deg_acc_filtered = t_initial_angle;
    t_thigh_angle_params->deg_gyr_filtered = 0;
    t_thigh_angle_params->deg_LPF_1st[0] = t_initial_angle;
    t_thigh_angle_params->deg_LPF_1st[1] = t_initial_angle;
    t_thigh_angle_params->deg_LPF_2nd[0] = t_initial_angle;
    t_thigh_angle_params->deg_LPF_2nd[1] = t_initial_angle;
    t_norm_params->deg_o = t_initial_angle;
}

/*
 *Function to calculate the initial thigh angle
*/
static void Calculate_Initial_Thigh_Angle(Thigh_Angle_Params* t_thigh_angle_params, Normalization_Params* t_norm_params, AccGyroData* t_acc_gyro_data, AttachPlane t_attach_plane)
{
	uint8_t t_total_samples = 100;
	float t_accumulated_angle = 0.0;
	uint8_t data_check = 0;
	float t_init_thigh_angle = 0.0;

	for (uint8_t i = 1; i <= t_total_samples; i++){
        data_check = Get_Value_6Axis_IMU(t_acc_gyro_data);
        if (data_check == 0){
    		/* Calculate the accelerometer angle (in degrees) */
            float accelerometer_angle = 0.0;

            if (t_attach_plane == e_LEFT_SAGITAL){
            	accelerometer_angle = (atan2((t_acc_gyro_data->acc_y)*(-1), (t_acc_gyro_data->acc_x)*(-1))) * (180 / PI);	// arctan(-y/-x) Left Sagital case
            }
            else if (t_attach_plane == e_RIGHT_SAGITAL){
            	accelerometer_angle = (atan2(t_acc_gyro_data->acc_y, (t_acc_gyro_data->acc_x)*(-1))) * (180 / PI);	// arctan(y/-x) Right Sagital case
            }
            else if (t_attach_plane == e_LEFT_SAGITAL_DEMO){
            	accelerometer_angle = (atan2(t_acc_gyro_data->acc_x, (t_acc_gyro_data->acc_y)*(-1))) * (180 / PI);	// arctan(x/-y) Left Sagital - DEMO ver case
            }

    		/* Accumulate the accelerometer angle */
            t_accumulated_angle += accelerometer_angle;

    		/* Calculate and update the initial thigh angle (average) */
            t_init_thigh_angle = t_accumulated_angle / ((float)i);
        }
        else{

        	i--;
        	err_chk = 50;
        }
    }

	t_thigh_angle_params->angle_init = t_init_thigh_angle;
    Set_Initial_Angle_Values(t_thigh_angle_params, t_norm_params, t_init_thigh_angle);
}


/*
 *Function to execute the time-varying complementary filter (with Fuzzy Logic - wc)
*/
static void Run_Complementary_Filter(Sensor_Params* t_sensor_params, Thigh_Angle_Params* t_thigh_angle_params, Fuzzy_Params* t_fuzzy_params, float t_sampling_Period, AttachPlane t_attach_plane)
{
	/* Apply time-varying complementary filter on the sensor data using fuzzy logic(wc) and update the thigh angle parameters */
	Run_TVCF(t_sensor_params, t_thigh_angle_params, t_fuzzy_params->wc, t_sampling_Period, t_attach_plane);
	/* Update the unfiltered thigh angle to be the same as the filtered thigh angle */
	t_thigh_angle_params->deg_tvcf[0] = t_thigh_angle_params->deg_tvcf_filtered;
}

/*
 *Function to normalize sensor data and calculate the current phase of the gait
*/
static void Run_Normalization_And_Get_Gait_Phase(Thigh_Angle_Params* t_thigh_angle_params, Normalization_Params* t_norm_params, Gait_Params* t_gait_params)
{
	/* Prepare for circular normalization by finding the center point of the original ellipse */
	Prepare_for_Circular_Normalization(t_thigh_angle_params, t_norm_params, t_gait_params);

	/* Normalize degree and velocity data based on calculated origin and amplitude */
	t_norm_params->deg_norm = (t_thigh_angle_params->deg_LPF_2nd[0] - t_norm_params->deg_o) / t_norm_params->A_deg;
	t_norm_params->vel_norm = (t_thigh_angle_params->vel_LPF_2nd[0] - t_norm_params->vel_o) / t_norm_params->A_vel;

	/* Calculate and update the current phase of the gait */
	t_gait_params->gait_phase = Get_Current_Gait_Phase(t_norm_params, t_gait_params); // Current phase (0 ~ 100%)
}

/*
 *Function to reduce noise in sensor data
*/
static void Reduce_Noise_In_Sensor_Data(Thigh_Angle_Params* t_thigh_angle_params, Gait_Params* t_gait_params)
{
	float t_dt = 1000.0;
	float w_target = Get_Max_Float(0.3, t_dt/t_gait_params->gait_period);
	float t_lpf_freq = 2.5 * w_target * 2 * PI;

	/* First LPF filter on angle data */
	t_thigh_angle_params->deg_LPF_1st[0] = Perform_LPF_on_Acc(
		t_thigh_angle_params->deg_tvcf[0],
		t_thigh_angle_params->deg_LPF_1st[1],
		t_lpf_freq,
		IMU_CONTROL_PERIOD
	);

	/* Second LPF filter on angle data */
	t_thigh_angle_params->deg_LPF_2nd[0] = Perform_LPF_on_Acc(
		t_thigh_angle_params->deg_LPF_1st[0],
		t_thigh_angle_params->deg_LPF_2nd[1],
		t_lpf_freq,
		IMU_CONTROL_PERIOD
	);

	/* Compute raw velocity from angle data */
	t_thigh_angle_params->vel_raw[0] = (t_thigh_angle_params->deg_tvcf[0] - t_thigh_angle_params->deg_tvcf[1]) * t_dt;											// dt = 0.001sec

	/* First LPF filter on velocity data */
	t_thigh_angle_params->vel_LPF_1st[0] = Perform_LPF_on_Acc(
		t_thigh_angle_params->vel_raw[0],
		t_thigh_angle_params->vel_LPF_1st[1],
		t_lpf_freq,
		IMU_CONTROL_PERIOD
	);

	/* Second LPF filter on velocity data */
	t_thigh_angle_params->vel_LPF_2nd[0] = Perform_LPF_on_Acc(
		t_thigh_angle_params->vel_LPF_1st[0],
		t_thigh_angle_params->vel_LPF_2nd[1],
		t_lpf_freq,
		IMU_CONTROL_PERIOD
	);
}

/*
 *This function calculates and returns the phase radius
*/
static float Compute_Phase_Radius(float t_deg_diff, float t_deg_th, float t_vel_diff, float t_vel_th)
{
    /* Calculate degree ratio */
    float t_deg_ratio = t_deg_diff / t_deg_th;

    /* Calculate velocity ratio */
    float t_vel_ratio = t_vel_diff / t_vel_th;

    /* Calculate and return the phase radius */
    return Calculate_Square_Root_Sum(t_deg_ratio, t_vel_ratio);
}

/*
 *This function updates the walking state based on the phase radii and sum_i
*/
static void Update_Walking_State(uint8_t* t_walking, float t_phase_radius_start, float t_phase_radius_stop, int16_t t_sum_i)
{
    /* The walking state is updated based on the current walking state, phase radii, and t_sum_i */
    switch (*t_walking)
    {
        case e_STOP:
            /* If the start phase radius is greater than 1, set the walking state to 1 */
            if (t_phase_radius_start > 1){
                *t_walking = 1;
            }
            break;
        case e_WALKING_START:
            /* If sum_i is greater than 1000, set the walking state to 2 */
            if (t_sum_i > 1000){
                *t_walking = 2;
            }
            break;
        case e_WALKING_HALF:
            /* If sum_i is 0, set the walking state to 3 */
            if (t_sum_i == 0){
                *t_walking = 3;
            }
            break;
        default:
            /* If the stop phase radius is less than 1, set the walking state to 0 */
            if (t_phase_radius_stop < 1){
                *t_walking = 0;
            }
            break;
    }
}

/*
*This function checks the walking state using the walking parameters and IMU system information
*/
static void Check_Walking_State(Thigh_Angle_Params* t_thigh_angle_params, Normalization_Params* t_norm_params, Threshold_Params* t_th_params, Gait_Params* t_gait_params, uint8_t* t_walking)
{
	float t_deg_diff = 0.0;
	float t_vel_diff = 0.0;
	float t_phase_radius_start = 0.0;
	float t_phase_radius_stop = 0.0;

    /* Get the relevant values from the walking parameters and IMU system */
    t_deg_diff = t_thigh_angle_params->deg_LPF_2nd[0] - t_norm_params->deg_o;
    t_vel_diff = t_thigh_angle_params->vel_LPF_2nd[0] - t_norm_params->vel_o;

    /* Calculate the start and stop phase radii */
    t_phase_radius_start = Compute_Phase_Radius(t_deg_diff, t_th_params->deg_th_start, t_vel_diff, t_th_params->vel_th_start);
    t_phase_radius_stop = Compute_Phase_Radius(t_deg_diff, t_th_params->deg_th_stop, t_vel_diff, t_th_params->vel_th_stop);

    /* Update the walking state based on the phase radii and sum_i */
    Update_Walking_State(t_walking, t_phase_radius_start, t_phase_radius_stop, t_norm_params->sum_i);

    /* If the walking state is 0 or 1, set the gait phase to -100 */
    if (*t_walking == 0 || *t_walking == 1){
        t_gait_params->gait_phase = -100;
    }
}


static void Setting_Assist_Time(Plantar_Params* t_plantar_params, Dorsi_Params* t_dorsi_params, Assist_Params* t_assist_params, Gait_Params* t_gait_params)
{
	Set_Assist_Force_Timing_Params(t_plantar_params, t_dorsi_params, t_assist_params, t_gait_params);
}


/*
*The function Update_IMU_Raw_Value updates the IMU raw values.
*/
static void Update_IMU_Raw_Value(Sensor_Params* t_sensor_params, AccGyroData* t_acc_gyro_data, MagData* t_mag_data, AttachPlane t_attach_plane)
{
	t_sensor_params->accX[0] = t_acc_gyro_data->acc_x;
	t_sensor_params->accY[0] = t_acc_gyro_data->acc_y;
	t_sensor_params->accZ[0] = t_acc_gyro_data->acc_z;

	t_sensor_params->gyrX[0] = t_acc_gyro_data->gyr_x;
	t_sensor_params->gyrY[0] = t_acc_gyro_data->gyr_y;

	if (t_attach_plane == e_LEFT_SAGITAL || t_attach_plane == e_LEFT_SAGITAL_DEMO){
		t_sensor_params->gyrZ[0] = (-1) * (t_acc_gyro_data->gyr_z); 	// For Left Sagital case
	}
	else if (t_attach_plane == e_RIGHT_SAGITAL){
		t_sensor_params->gyrZ[0] = t_acc_gyro_data->gyr_z; 	// For Right Sagital case
	}
//	t_sensor_params->magX[0] = t_mag_data->mag_x;
//	t_sensor_params->magY[0] = t_mag_data->mag_y;
//	t_sensor_params->magZ[0] = t_mag_data->mag_z;
}


/*
*Main function to calculate Roll, Pitch and Yaw
*/
static void Calculate_RPY(RollPitchYaw* t_rpy, AccGyroData* t_acc_gyro_data)
{
	const float t_yaw_value = 0.001;

    /* Calculating Roll, Pitch and Yaw */
    t_rpy->roll = atanf(t_acc_gyro_data->acc_y /
                    Calculate_Square_Root_Sum(t_acc_gyro_data->acc_x, t_acc_gyro_data->acc_z))*180/PI;

    t_rpy->pitch = atanf(-t_acc_gyro_data->acc_x /
                    Calculate_Square_Root_Sum(t_acc_gyro_data->acc_y, t_acc_gyro_data->acc_z))*180/PI;

    t_rpy->yaw += t_acc_gyro_data->gyr_z*t_yaw_value;
}

/*
 ___          _   _
 | _ \___ _  _| |_(_)_ _  ___ ___
 |   / _ \ || |  _| | ' \/ -_|_-<
 |_|_\___/\_,_|\__|_|_||_\___/__/

 */


static int Run_Total_function()
{
	thigh_angle_tvcf_demo = (-1) * thigh_angle_params.deg_tvcf_filtered;

	Save_Previous_Value(&sensor_params, &thigh_angle_params, &gait_params);

	uint8_t t_3axis_res = Get_Value_3Axis_IMU(&mag_data);
	if (t_3axis_res != NO_ERROR){
		Imu_Ctrl_Error_Type = IMU_HDLR_HAL_FUNC_ERROR;
		err_chk = 11;
	}
	uint8_t t_6axis_res = Get_Value_6Axis_IMU(&acc_gyro_data);
	if (t_6axis_res != NO_ERROR){
		Imu_Ctrl_Error_Type = IMU_HDLR_HAL_FUNC_ERROR;
		err_chk = 33;
	}

	Update_IMU_Raw_Value(&sensor_params, &acc_gyro_data, &mag_data, attach_plane);

	Generate_Fuzzy_Input(&sensor_params, &fuzzy_params);
	wc_test = Calculate_Fuzzy_Wc(&fuzzy_params);

	Run_Complementary_Filter(&sensor_params, &thigh_angle_params, &fuzzy_params, IMU_CONTROL_PERIOD, attach_plane);

	Reduce_Noise_In_Sensor_Data(&thigh_angle_params, &gait_params);

	Run_Normalization_And_Get_Gait_Phase(&thigh_angle_params, &norm_params, &gait_params);

	Check_Walking_State(&thigh_angle_params, &norm_params, &th_params, &gait_params, &walking);

	Setting_Assist_Time(&plantar_params, &dorsi_params, &assist_params, &gait_params);

//	// Msg_Hdlr problem //
//	Setting_Assist_Force_and_Time(&assist_params, &gait_params);
//	Set_Trigger(&assist_params, &gait_params, walking);

	return 0;
}





/*
 ___ ___   ___     ___      _ _ _             _
 / __|   \ / _ \   / __|__ _| | | |__  __ _ __| |__ ___
 \__ \ |) | (_) | | (__/ _` | | | '_ \/ _` / _| / /(_-<
 |___/___/ \___/   \___\__,_|_|_|_.__/\__,_\__|_\_\/__/

 */

MSG_COMMON_SDO_CALLBACK(imu_ctrl_task)

/*
 ___ _        _         ___             _   _
 / __| |_ __ _| |_ ___  | __|  _ _ _  __| |_(_)___ _ _  ___
 \__ \  _/ _` |  _/ -_) | _| || | ' \/ _|  _| / _ \ ' \(_-<
 |___/\__\__,_|\__\___| |_| \_,_|_||_\__|\__|_\___/_||_/__/

 */
static void StateOff_Run( )
{
	// TODO: I2C Initialization
	uint8_t i2c_3axis_res = Get_Value_3Axis_IMU(&mag_data);
	uint8_t i2c_6axis_res = Get_Value_6Axis_IMU(&acc_gyro_data);

	if (i2c_3axis_res == NO_ERROR && i2c_6axis_res == NO_ERROR){
		Push_Routine(&imu_ctrl_task.routine, ROUTINE_ID_IMU_TOTAL_FUNCTION);
		Transition_State(&imu_ctrl_task.state_machine, e_State_Standby);
	}

}

static void StateStandby_Run( )
{
	Transition_State(&imu_ctrl_task.state_machine, e_State_Enable);
}

static void StateEnable_Ent()
{

}

static void StateEnable_Run( )
{
	Run_Routines(&imu_ctrl_task.routine);
}

static void StateEnable_Ext()
{

}

static void StateError_Run()
{

}

/*
 __  __      _
 |  \/  |__ _(_)_ _
 | |\/| / _` | | ' \
 |_|  |_\__,_|_|_||_|

 */

void Init_Imu_Ctrl(void)
{
    Init_Task(&imu_ctrl_task);

	/* State Definition */
	TASK_CREATE_STATE(&imu_ctrl_task, e_State_Off,      NULL,   			StateOff_Run,       NULL,         		 true);
	TASK_CREATE_STATE(&imu_ctrl_task, e_State_Standby,  NULL,   			StateStandby_Run,	NULL,         		 false);
	TASK_CREATE_STATE(&imu_ctrl_task, e_State_Enable,   StateEnable_Ent,  	StateEnable_Run, 	StateEnable_Ext,	 false);
	TASK_CREATE_STATE(&imu_ctrl_task, e_State_Error,    NULL,			  	StateError_Run,    	NULL,				 false);

	/* Routine Definition */
	TASK_CREATE_ROUTINE(&imu_ctrl_task, ROUTINE_ID_IMU_TOTAL_FUNCTION, 		NULL, Run_Total_function, 		NULL);

	/* DOD Definition */
	// DOD
	Create_DOD(TASK_ID_IMU);

	// PDO
	Create_PDO(TASK_ID_IMU, PDO_ID_IMU_ACC_X, e_Float32, 1, &acc_gyro_data.acc_x);
	Create_PDO(TASK_ID_IMU, PDO_ID_IMU_ACC_Y, e_Float32, 1, &acc_gyro_data.acc_y);
	Create_PDO(TASK_ID_IMU, PDO_ID_IMU_ACC_Z, e_Float32, 1, &acc_gyro_data.acc_z);
	Create_PDO(TASK_ID_IMU, PDO_ID_IMU_GYR_X, e_Float32, 1, &acc_gyro_data.gyr_x);
	Create_PDO(TASK_ID_IMU, PDO_ID_IMU_GYR_Y, e_Float32, 1, &acc_gyro_data.gyr_y);
	Create_PDO(TASK_ID_IMU, PDO_ID_IMU_GYR_Z, e_Float32, 1, &acc_gyro_data.gyr_z);

	Create_PDO(TASK_ID_IMU, PDO_ID_IMU_DEG_ACC,          e_Float32, 1, &thigh_angle_params.deg_acc);
	Create_PDO(TASK_ID_IMU, PDO_ID_IMU_DEG_GYR,          e_Float32, 1, &thigh_angle_params.deg_gyr);
	Create_PDO(TASK_ID_IMU, PDO_ID_IMU_DEG_ACC_FILTERED, e_Float32, 1, &thigh_angle_params.deg_acc_filtered);
	Create_PDO(TASK_ID_IMU, PDO_ID_IMU_DEG_GYR_FILTERED, e_Float32, 1, &thigh_angle_params.deg_gyr_filtered);
//	Create_PDO(TASK_ID_IMU, PDO_ID_DEG_TVCF,             e_Float32, 1, &thigh_angle_params.deg_tvcf_filtered);			// Real application
	Create_PDO(TASK_ID_IMU, PDO_ID_DEG_TVCF,             e_Float32, 1, &thigh_angle_tvcf_demo);							// Only for DEMO

	Create_PDO(TASK_ID_IMU, PDO_ID_IMU_WALKING_STATE, 	e_UInt8, 	1, &walking);
	Create_PDO(TASK_ID_IMU, PDO_ID_IMU_GAIT_PHASE, 		e_Float32,  1, &gait_params.gait_phase);

	// Assist mode //
	Create_PDO(TASK_ID_IMU, PDO_ID_IMU_TENSION_P, e_Float32, 1, &plantar_params.Plantar_ref);
	Create_PDO(TASK_ID_IMU, PDO_ID_IMU_TENSION_D, e_Float32, 1, &dorsi_params.Dorsi_ref);

	// SDO
	MSG_COMMON_SDO_CREATE(TASK_ID_IMU)

	uint8_t err_chk_6axis = 0;
	uint8_t err_chk_3axis = 0;
	err_chk_6axis = Init_6Axis_IMU(&acc_gyro_data);
	err_chk_3axis = Init_3Axis_IMU(&mag_data);
	if (err_chk_6axis != 0){
		err_chk = 111;
	}

	Reset_Parameters();
	attach_plane = e_LEFT_SAGITAL_DEMO;		// WIDM Attached Plane Selection
	Set_Init_Parameters(&norm_params, &gait_params, &fuzzy_params, &th_params, &plantar_params, &dorsi_params, &assist_params);
	Calculate_Initial_Thigh_Angle(&thigh_angle_params, &norm_params, &acc_gyro_data, attach_plane);

	/* Callback Allocation */
    if (Start_TIM3() > 0) {
        //TODO: ERROR PROCESS
    }
    ioif_tim3_callback_ptr = Run_Imu_Ctrl;
}

void Run_Imu_Ctrl(void)
{

	uint32_t imu_ctrl_loop_time_cnt_1 = DWT->CYCCNT;

	/*Run Device */
	Run_Task(&imu_ctrl_task);

	uint32_t imu_ctrl_loop_time_cnt_2 = DWT->CYCCNT;

	/* Elapsed Time Check */
	imu_ctrl_task_us = (imu_ctrl_loop_time_cnt_2 - imu_ctrl_loop_time_cnt_1)/480;	// in microsecond
}
