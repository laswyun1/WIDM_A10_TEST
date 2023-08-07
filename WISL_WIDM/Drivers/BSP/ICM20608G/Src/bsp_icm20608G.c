/*
 * bsp_icm20608.c
 *
 *  Created on: Aug 7, 2023
 *      Author: Seung-WonYun
 */


#include "bsp_icm20608G.h"

//I2C_HandleTypeDef hi2c1;

void Initialize_ICM(ICMObject* t_icm_obj)
{
	memset(t_icm_obj, 0, sizeof(ICMObject));
	t_icm_obj->i2cport = &hi2c1;
	t_icm_obj->addr    = ICM20608G_DEV_ADDR;
}

uint8_t IsDevReady_ICM(ICMObject* t_icm_obj)
{
	uint8_t t_res = HAL_I2C_IsDeviceReady(t_icm_obj->i2cport, t_icm_obj->addr, ICM_I2C_TRIALS, ICM_I2C_TIMEOUT);
	return t_res;
}

uint8_t Init_ICM(ICMObject* t_icm_obj)
{
	uint8_t t_res = HAL_I2C_Init(t_icm_obj->i2cport);
	return t_res;
}

uint8_t DeInit_ICM(ICMObject* t_icm_obj)
{
	uint8_t t_res = HAL_I2C_DeInit(t_icm_obj->i2cport);
	return t_res;
}


uint8_t Read_Data_ICM(ICMObject* t_icm_obj)
{
	uint8_t t_res = 0;
	uint8_t t_buff[14];
	t_res = HAL_I2C_Mem_Read(t_icm_obj->i2cport, t_icm_obj->addr, ICM20608G_ACCEL_XOUT_H, I2C_MEMADD_SIZE_8BIT, t_buff, 14, ICM_I2C_TIMEOUT);

	int16_t t_Xacc = (int16_t)(t_buff[0]  << 8 | t_buff[1]);
	int16_t t_Yacc = (int16_t)(t_buff[2]  << 8 | t_buff[3]);
	int16_t t_Zacc = (int16_t)(t_buff[4]  << 8 | t_buff[5]);
	int16_t t_Xgyr = (int16_t)(t_buff[8]  << 8 | t_buff[9]);
	int16_t t_Ygyr = (int16_t)(t_buff[10] << 8 | t_buff[11]);
	int16_t t_Zgyr = (int16_t)(t_buff[12] << 8 | t_buff[13]);

	/* NEED TO BE SCALED */
	t_icm_obj->acc_x = (float)(t_Xacc / 8192.0f);
	t_icm_obj->acc_y = (float)(t_Yacc / 8192.0f);
	t_icm_obj->acc_z = (float)(t_Zacc / 8192.0f);
	t_icm_obj->gyr_x = (float)(t_Xgyr / 65.5f); //65.5f
	t_icm_obj->gyr_y = (float)(t_Ygyr / 65.5f);
	t_icm_obj->gyr_z = (float)(t_Zgyr / 65.5f);

	return t_res;
}


uint8_t Write_Data_ICM(ICMObject* t_icm_obj)
{
	uint8_t t_res = 0;

    uint8_t conf_1 = ICM20608G_PWR_MGMT_1_ONE;
    t_res = HAL_I2C_Mem_Write(t_icm_obj->i2cport, t_icm_obj->addr, ICM20608G_PWR_MGMT_1, I2C_MEMADD_SIZE_8BIT, &conf_1, ICM20608G_CONTROL_SIZE, ICM_I2C_TIMEOUT);
    uint8_t conf_2 = ICM20608G_PWR_MGMT_2_ONE;
    t_res = HAL_I2C_Mem_Write(t_icm_obj->i2cport, t_icm_obj->addr, ICM20608G_PWR_MGMT_2, I2C_MEMADD_SIZE_8BIT, &conf_2, ICM20608G_CONTROL_SIZE, ICM_I2C_TIMEOUT);
    uint8_t conf_3 = ICM20608G_GYR_CONFIG_ONE;
    t_res = HAL_I2C_Mem_Write(t_icm_obj->i2cport, t_icm_obj->addr, ICM20608G_GYRO_CONFIG, I2C_MEMADD_SIZE_8BIT, &conf_3, ICM20608G_CONTROL_SIZE, ICM_I2C_TIMEOUT);
    uint8_t conf_4 = ICM20608G_ACC_CONFIG_ONE;
    t_res = HAL_I2C_Mem_Write(t_icm_obj->i2cport, t_icm_obj->addr, ICM20608G_ACCEL_CONFIG, I2C_MEMADD_SIZE_8BIT, &conf_4, ICM20608G_CONTROL_SIZE, ICM_I2C_TIMEOUT);

    return t_res;
}
