/*
 * imu_ctrl_task.h
 *
 *  Created on: Aug 7, 2023
 *      Author: Seung-WonYun
 */

#ifndef FRAMEWORK_APPS_IMU_CTRL_TASK_IMU_CTRL_TASK_H_
#define FRAMEWORK_APPS_IMU_CTRL_TASK_IMU_CTRL_TASK_H_

#include "ioif_tim.h"
#include "bsp_icm20608G.h"
#include "bsp_bm1422agmv.h"
#include "msg_common.h"
#include "msg_hdlr_task.h"
#include "task.h"
#include "widm_calculation.h"


void Init_Imu_Ctrl(void);
void Run_Imu_Ctrl(void);

#endif /* FRAMEWORK_APPS_IMU_CTRL_TASK_IMU_CTRL_TASK_H_ */
