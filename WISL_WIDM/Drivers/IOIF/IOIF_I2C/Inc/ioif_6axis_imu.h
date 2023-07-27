#ifndef FRAMEWORK_APPS_IMU_CTRL_TASK_IMU_6AXIS_H_
#define FRAMEWORK_APPS_IMU_CTRL_TASK_IMU_6AXIS_H_

#include "bsp_icm20608G.h"
#include "ioif_i2c_func.h"
#include "error_dictionary.h"

typedef struct _AccGyroData{
	float acc_x;
	float acc_y;
	float acc_z;
	float gyr_x;
	float gyr_y;
	float gyr_z;
} AccGyroData;

ICM20608GObject icm20608_obj;

HAL_StatusTypeDef Init_6Axis_IMU(AccGyroData* t_acc_gyro_Data);
HAL_StatusTypeDef Get_Value_6Axis_IMU(AccGyroData* t_acc_gyro_Data);

#endif /* FRAMEWORK_APPS_IMU_CTRL_TASK_IMU_6AXIS_H_ */
