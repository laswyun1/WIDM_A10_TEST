#include "ioif_3axis_imu.h"

static HAL_StatusTypeDef IsDevReady_3Axis_IMU(uint16_t t_dev_addr)
{
	return IsDevReady_I2C3(t_dev_addr);
}

static HAL_StatusTypeDef Read_3Axis_IMU(uint16_t t_dev_addr, uint16_t t_reg_addr, uint8_t *t_data, uint16_t t_data_size)
{
	return Mem_Read_I2C3(t_dev_addr, t_reg_addr, I2C_MEMADD_SIZE_8BIT, t_data, t_data_size);
}

static HAL_StatusTypeDef Write_3Axis_IMU(uint16_t t_dev_addr, uint16_t t_reg_addr, uint8_t *t_data, uint16_t t_data_size)
{
	return Mem_Write_I2C3(t_dev_addr, t_reg_addr, I2C_MEMADD_SIZE_8BIT, t_data, t_data_size);
}

HAL_StatusTypeDef Init_3Axis_IMU(MagData* t_mag_data)
{
	uint8_t t_init_res = 0;

	memset(t_mag_data, 0, sizeof(MagData));

	BM1422AGMVIOctx ioctx = {
		NULL,
		NULL,
		IsDevReady_3Axis_IMU,
		Read_3Axis_IMU,
		Write_3Axis_IMU,
		NULL, 
	};

	t_init_res = Set_Ioctx_BM1422AGMV(&bm1422agmv_obj, &ioctx);

	if (Init_BM1422AGMV(&bm1422agmv_obj) != HAL_OK){
		t_init_res = Init_BM1422AGMV(&bm1422agmv_obj);
		return t_init_res;
	}

	return t_init_res;
}

HAL_StatusTypeDef Get_Value_3Axis_IMU(MagData* t_mag_data)
{
	uint8_t t_get_value_res = 0;
	t_get_value_res = Get_Value_BM1422AGMV(&bm1422agmv_obj);

	if (t_get_value_res == HAL_OK){
		memcpy(t_mag_data, &bm1422agmv_obj.value, sizeof(MagData));
	} else{
		return t_get_value_res;
	}

	return t_get_value_res;
}
