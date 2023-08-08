/*
 * bsp_bm1422agmv.c
 *
 *  Created on: Aug 7, 2023
 *      Author: Seung-WonYun
 */


#include "bsp_bm1422agmv.h"

//I2C_HandleTypeDef hi2c2;
uint8_t I2C2_RxBuff[BM_BUFF_SIZE] __attribute__((section(".I2C2_RxBuff")));


void Initialize_BM(BMObject* t_bm_obj)
{
	memset(t_bm_obj, 0, sizeof(BMObject));
	t_bm_obj->i2cport = &hi2c2;
	t_bm_obj->addr    = BM1422AGMV_DEV_ADDR;
}

uint8_t IsDevReady_BM(BMObject* t_bm_obj)
{
	uint8_t t_res = HAL_I2C_IsDeviceReady(t_bm_obj->i2cport, t_bm_obj->addr, BM_I2C_TRIALS, BM_I2C_TIMEOUT);
	return t_res;
}

uint8_t Init_BM(BMObject* t_bm_obj)
{
	uint8_t t_res = HAL_I2C_Init(t_bm_obj->i2cport);
	return t_res;
}

uint8_t DeInit_BM(BMObject* t_bm_obj)
{
	uint8_t t_res = HAL_I2C_DeInit(t_bm_obj->i2cport);
	return t_res;
}


uint8_t Read_Data_BM(BMObject* t_bm_obj)
{
	uint8_t t_res = 0;
	uint8_t t_buff[6];

	//Mem_Read ver//
//	t_res = HAL_I2C_Mem_Read(t_bm_obj->i2cport, t_bm_obj->addr, BM1422AGMV_DATAX_REG, I2C_MEMADD_SIZE_8BIT, t_buff, 6, BM_I2C_TIMEOUT);

	//DMA ver//
	t_res = HAL_I2C_Mem_Read_DMA(t_bm_obj->i2cport, t_bm_obj->addr, BM1422AGMV_DATAX_REG, I2C_MEMADD_SIZE_8BIT, I2C2_RxBuff, 6);
	memcpy(t_buff, I2C2_RxBuff, 6);

    int16_t t_magX = (int16_t)(t_buff[0] | t_buff[1] << 8);
    int16_t t_magY = (int16_t)(t_buff[2] | t_buff[3] << 8);
    int16_t t_magZ = (int16_t)(t_buff[4] | t_buff[5] << 8);

	/* NEED TO BE SCALED */
    t_bm_obj->mag_x = (float)t_magX;
	t_bm_obj->mag_y = (float)t_magY;
	t_bm_obj->mag_z = (float)t_magZ;

	return t_res;
}


uint8_t Write_Data_BM(BMObject* t_bm_obj)
{
	uint8_t t_res = 0;

	uint8_t conf_1 = BM1422AGMV_CNTL1_VALUE;
    t_res = HAL_I2C_Mem_Write(t_bm_obj->i2cport, t_bm_obj->addr, BM1422AGMV_CNTL1_REG, I2C_MEMADD_SIZE_8BIT, &conf_1, BM1422AGMV_CONTROL_SIZE, BM_I2C_TIMEOUT);
    uint8_t conf_2 = BM1422AGMV_CNTL2_VALUE;
    t_res = HAL_I2C_Mem_Write(t_bm_obj->i2cport, t_bm_obj->addr, BM1422AGMV_CNTL2_REG, I2C_MEMADD_SIZE_8BIT, &conf_2, BM1422AGMV_CONTROL_SIZE, BM_I2C_TIMEOUT);
    uint8_t conf_4 = BM1422AGMV_CNTL4_H_VALUE;
    t_res = HAL_I2C_Mem_Write(t_bm_obj->i2cport, t_bm_obj->addr, BM1422AGMV_CNTL4_REG_H, I2C_MEMADD_SIZE_8BIT, &conf_4, BM1422AGMV_CONTROL_SIZE, BM_I2C_TIMEOUT);
    uint8_t conf_5 = BM1422AGMV_CNTL4_L_VALUE;
    t_res = HAL_I2C_Mem_Write(t_bm_obj->i2cport, t_bm_obj->addr, BM1422AGMV_CNTL4_REG_L, I2C_MEMADD_SIZE_8BIT, &conf_5, BM1422AGMV_CONTROL_SIZE, BM_I2C_TIMEOUT);


    // CNTL3 should be set at LAST //
    uint8_t conf_3 = BM1422AGMV_CNTL3_VALUE;
    t_res = HAL_I2C_Mem_Write(t_bm_obj->i2cport, t_bm_obj->addr, BM1422AGMV_CNTL3_REG, I2C_MEMADD_SIZE_8BIT, &conf_3, BM1422AGMV_CONTROL_SIZE, BM_I2C_TIMEOUT);


    return t_res;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
