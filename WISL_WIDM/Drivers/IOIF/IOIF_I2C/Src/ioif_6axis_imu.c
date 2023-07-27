#include "ioif_6axis_imu.h"

static HAL_StatusTypeDef IsDevReady_6Axis_IMU(uint16_t t_dev_addr)
{
   return IsDevReady_I2C1(t_dev_addr);
}

static HAL_StatusTypeDef Read_6Axis_IMU(uint16_t t_dev_addr, uint16_t t_reg_addr, uint8_t *t_data, uint16_t t_data_size)
{
	return Mem_Read_I2C1(t_dev_addr, t_reg_addr, I2C_MEMADD_SIZE_8BIT, t_data, t_data_size);
}

static HAL_StatusTypeDef Write_6Axis_IMU(uint16_t t_dev_addr, uint16_t t_reg_addr, uint8_t *t_data, uint16_t t_data_size)
{
	return Mem_Write_I2C1(t_dev_addr, t_reg_addr, I2C_MEMADD_SIZE_8BIT, t_data, t_data_size);
}

HAL_StatusTypeDef Init_6Axis_IMU(AccGyroData* t_acc_gyro_Data)
{
	uint8_t t_init_res = 0;

	memset(&t_acc_gyro_Data, 0, sizeof(AccGyroData));

	ICM20608GIOctx ioctx = {
		NULL,
		NULL,
		IsDevReady_6Axis_IMU,
		Read_6Axis_IMU,
		Write_6Axis_IMU,
		NULL
	};

	t_init_res = Set_Ioctx_ICM20608G(&icm20608_obj, &ioctx);

	if (Init_ICM20608G(&icm20608_obj) != HAL_OK){
		t_init_res = Init_ICM20608G(&icm20608_obj);
		return t_init_res;
	}

	return t_init_res;
}

HAL_StatusTypeDef Get_Value_6Axis_IMU(AccGyroData* t_acc_gyro_Data)
{
	uint8_t t_get_value_res = 0;
	t_get_value_res = Get_Value_ICM20608G(&icm20608_obj);

	if (t_get_value_res == HAL_OK){
		memcpy(t_acc_gyro_Data, &icm20608_obj.value, sizeof(AccGyroData));
	} else{
		return t_get_value_res;
	}

	return t_get_value_res;
}
