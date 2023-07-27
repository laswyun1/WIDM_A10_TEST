#include "bsp_icm20608G.h"

static ICM20608G Read_Reg_ICM20608G(ICM20608GObject* t_obj, uint16_t t_reg, uint8_t* t_data, uint32_t t_size)
{
    return t_obj->io.ReadReg(t_obj->addr, t_reg, t_data, t_size);
}

static ICM20608G Write_Reg_ICM20608G(ICM20608GObject* t_obj, uint16_t t_reg, uint8_t* t_data, uint32_t t_size)
{
    return t_obj->io.WriteReg(t_obj->addr, t_reg, t_data, t_size);
}

static ICM20608G Set_Reg_ICM20608G(ICM20608GObject* t_obj, uint16_t t_reg, uint8_t* t_data, uint32_t t_size)
{
	uint8_t t_res = e_ICM20608G_STATUS_OK;
    t_res = Write_Reg_ICM20608G(t_obj, t_reg, t_data, t_size);
    return t_res;
}

ICM20608G Set_Ioctx_ICM20608G(ICM20608GObject* t_obj, ICM20608GIOctx* t_ioctx)
{
    if (!t_obj || !t_ioctx->IsDevReady || !t_ioctx->ReadReg || !t_ioctx->WriteReg){
        return e_ICM20608G_STATUS_ERROR;
    }

    t_obj->io.Init       = t_ioctx->Init;
    t_obj->io.DeInit     = t_ioctx->DeInit;
    t_obj->io.IsDevReady = t_ioctx->IsDevReady;
    t_obj->io.ReadReg    = t_ioctx->ReadReg;
    t_obj->io.WriteReg   = t_ioctx->WriteReg;
    t_obj->io.Wait       = t_ioctx->Wait;

    return e_ICM20608G_STATUS_OK;
}

ICM20608G Init_ICM20608G(ICM20608GObject* t_obj)			// Setting control register
{
	static uint8_t t_res = e_ICM20608G_STATUS_OK;

    // Check Address
    t_res = e_ICM20608G_STATUS_ERROR;
    t_obj->addr = ICM20608G_DEV_ADDR;
    if (t_obj->io.IsDevReady(t_obj->addr) == 0){
        t_res = e_ICM20608G_STATUS_OK;
    }

    // Configure Control
    if (t_res == e_ICM20608G_STATUS_OK){
        uint8_t conf_1 = ICM20608G_PWR_MGMT_1_ONE;
        t_res = Set_Reg_ICM20608G(t_obj, ICM20608G_PWR_MGMT_1, &conf_1, ICM20608G_CONTROL_SIZE);
        uint8_t conf_2 = ICM20608G_PWR_MGMT_2_ONE;
        t_res = Set_Reg_ICM20608G(t_obj, ICM20608G_PWR_MGMT_2, &conf_2, ICM20608G_CONTROL_SIZE);
        uint8_t conf_3 = ICM20608G_GYR_CONFIG_ONE;
        t_res = Set_Reg_ICM20608G(t_obj, ICM20608G_GYRO_CONFIG, &conf_3, ICM20608G_CONTROL_SIZE);
        uint8_t conf_4 = ICM20608G_ACC_CONFIG_ONE;
        t_res = Set_Reg_ICM20608G(t_obj, ICM20608G_ACCEL_CONFIG, &conf_4, ICM20608G_CONTROL_SIZE);
    }

    return t_res;
}

ICM20608G Get_Value_ICM20608G(ICM20608GObject* t_obj)
{
	uint8_t t_res = 0;
    uint8_t t_buff[14];

	t_res = t_obj->io.ReadReg(t_obj->addr, ICM20608G_ACCEL_XOUT_H, t_buff, 14);

	int16_t t_Xacc = (int16_t)(t_buff[0]  << 8 | t_buff[1]);
	int16_t t_Yacc = (int16_t)(t_buff[2]  << 8 | t_buff[3]);
	int16_t t_Zacc = (int16_t)(t_buff[4]  << 8 | t_buff[5]);
	int16_t t_Xgyr = (int16_t)(t_buff[8]  << 8 | t_buff[9]);
	int16_t t_Ygyr = (int16_t)(t_buff[10] << 8 | t_buff[11]);
	int16_t t_Zgyr = (int16_t)(t_buff[12] << 8 | t_buff[13]);

	/* NEED TO BE SCALED */
	t_obj->value.icm20608_acc_x = (float)(t_Xacc / 8192.0f);
	t_obj->value.icm20608_acc_y = (float)(t_Yacc / 8192.0f);
	t_obj->value.icm20608_acc_z = (float)(t_Zacc / 8192.0f);
	t_obj->value.icm20608_gyr_x = (float)(t_Xgyr / 65.5f); //65.5f
	t_obj->value.icm20608_gyr_y = (float)(t_Ygyr / 65.5f);
	t_obj->value.icm20608_gyr_z = (float)(t_Zgyr / 65.5f);

	return t_res;
}
