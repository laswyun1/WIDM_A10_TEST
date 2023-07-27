#ifndef FRAMEWORK_APPS_IMU_CTRL_TASK_IMU_3AXIS_H_
#define FRAMEWORK_APPS_IMU_CTRL_TASK_IMU_3AXIS_H_

#include "bsp_bm1422agmv.h"
#include "ioif_i2c_func.h"
#include "error_dictionary.h"

typedef struct _MagData{
	float mag_x;
	float mag_y;
	float mag_z;
} MagData;

BM1422AGMVObject bm1422agmv_obj;

HAL_StatusTypeDef Init_3Axis_IMU(MagData* t_mag_data);
HAL_StatusTypeDef Get_Value_3Axis_IMU(MagData* t_mag_data);

#endif /* FRAMEWORK_APPS_IMU_CTRL_TASK_IMU_3AXIS_H_ */
