#ifndef FRAMEWORK_APPS_IMU_CTRL_TASK_IMU_CTRL_TASK_H_
#define FRAMEWORK_APPS_IMU_CTRL_TASK_IMU_CTRL_TASK_H_

#include "main.h"
#include "ioif_tim.h"
#include "ioif_i2c.h"
#include "msg_common.h"
#include "msg_hdlr_task.h"
#include "error_dictionary.h"
#include "task.h"
#include "widm_calculation.h"

typedef struct _RollPitchYaw{
	float roll;
	float pitch;
	float yaw;
} RollPitchYaw;

TaskStruct imu_ctrl_task;

RollPitchYaw rpy;

/*
 
   ___ __  __ _   _ 
  |_ _|  \/  | | | |
   | || |\/| | | | |
   | || |  | | |_| |
  |___|_|  |_|\___/ 
                    
 
*/

AccGyroData acc_gyro_data;
MagData     mag_data;

/*
 
  __        _____ ____  __  __ 
  \ \      / /_ _|  _ \|  \/  |
   \ \ /\ / / | || | | | |\/| |
    \ V  V /  | || |_| | |  | |
     \_/\_/  |___|____/|_|  |_|
                               
 
*/

Sensor_Params sensor_params;
Normalization_Params norm_params;
Gait_Params gait_params;
Fuzzy_Params fuzzy_params;
Thigh_Angle_Params thigh_angle_params;
Threshold_Params th_params;
Assist_Params assist_params;

float wc_test;
uint8_t walking;
AttachPlane attach_plane;
float thigh_angle_tvcf_demo;

/*
 
   ____       _                 
  |  _ \  ___| |__  _   _  __ _ 
  | | | |/ _ \ '_ \| | | |/ _` |
  | |_| |  __/ |_) | |_| | (_| |
  |____/ \___|_.__/ \__,_|\__, |
                          |___/ 
 
*/

//uint8_t test_res_3axis;
//uint8_t test_res_6axis;
//
//uint8_t i2c_3axis_res;
//uint8_t i2c_6axis_res;

//uint32_t imu_ctrl_loop_time_cnt_1;
//uint32_t imu_ctrl_loop_time_cnt_2;

//uint32_t imu_ctrl_task_us;

void Init_Imu_Ctrl(void);
void Run_Imu_Ctrl(void);

#endif /* FRAMEWORK_APPS_IMU_CTRL_TASK_IMU_CTRL_TASK_H_ */
