/*
 * bsp_bm1422agmv.h
 *
 *  Created on: Aug 7, 2023
 *      Author: Seung-WonYun
 */

#ifndef DRIVERS_BSP_BM1422AGMV_INC_BSP_BM1422AGMV_H_
#define DRIVERS_BSP_BM1422AGMV_INC_BSP_BM1422AGMV_H_

#include "bsp_bm1422agmv_regmap.h"
#include "i2c.h"

#include <stdint.h>
#include <string.h>

#define BM_BUFF_SIZE				20

#define BM_I2C_TRIALS				10
#define BM_I2C_DELAY				50
#define BM_I2C_TIMEOUT				5

extern I2C_HandleTypeDef hi2c2;


typedef struct _BMObject{
	I2C_HandleTypeDef* 		i2cport;
	uint16_t 				addr;

	float 					mag_x;
	float 					mag_y;
	float 					mag_z;
} BMObject;

uint8_t IsDevReady_BM(BMObject* t_bm_obj);
uint8_t Init_BM(BMObject* t_bm_obj);
uint8_t DeInit_BM(BMObject* t_bm_obj);
uint8_t Read_Data_BM(BMObject* t_bm_obj);
uint8_t Write_Data_BM(BMObject* t_bm_obj);
void Initialize_BM(BMObject* t_bm_obj);

#endif /* DRIVERS_BSP_BM1422AGMV_INC_BSP_BM1422AGMV_H_ */
