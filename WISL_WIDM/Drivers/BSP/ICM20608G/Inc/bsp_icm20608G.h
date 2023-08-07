/*
 * bsp_icm20608.h
 *
 *  Created on: Aug 7, 2023
 *      Author: Seung-WonYun
 */

#ifndef DRIVERS_BSP_ICM20608G_INC_BSP_ICM20608G_H_
#define DRIVERS_BSP_ICM20608G_INC_BSP_ICM20608G_H_

#include "bsp_icm20608G_regmap.h"
#include "i2c.h"

#include <stdint.h>
#include <string.h>

#define ICM_BUFF_SIZE				20

#define ICM_I2C_TRIALS				10
#define ICM_I2C_DELAY				50
#define ICM_I2C_TIMEOUT				5


extern I2C_HandleTypeDef hi2c1;


typedef struct _ICMObject{
	I2C_HandleTypeDef* 		i2cport;
	uint16_t 				addr;

	float 					acc_x;
	float 					acc_y;
	float 					acc_z;
	float 					gyr_x;
	float 					gyr_y;
	float 					gyr_z;
} ICMObject;

uint8_t IsDevReady_ICM(ICMObject* t_icm_obj);
uint8_t Init_ICM(ICMObject* t_icm_obj);
uint8_t DeInit_ICM(ICMObject* t_icm_obj);
uint8_t Read_Data_ICM(ICMObject* t_icm_obj);
uint8_t Write_Data_ICM(ICMObject* t_icm_obj);
void Initialize_ICM(ICMObject* t_icm_obj);

#endif /* DRIVERS_BSP_ICM20608G_INC_BSP_ICM20608G_H_ */
