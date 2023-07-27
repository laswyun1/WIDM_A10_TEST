#include "bsp_bm1422agmv.h"

static BM1422AGMV Read_Reg_BM1422AGMV(BM1422AGMVObject* t_obj, uint16_t t_reg, uint8_t* t_data, uint32_t t_size)
{
    return t_obj->io.ReadReg(t_obj->addr, t_reg, t_data, t_size);
}

static BM1422AGMV Write_Reg_BM1422AGMV(BM1422AGMVObject* t_obj, uint16_t t_reg, uint8_t* t_data, uint32_t t_size)
{
    return t_obj->io.WriteReg(t_obj->addr, t_reg, t_data, t_size);
}

static BM1422AGMV Set_Reg_BM1422AGMV(BM1422AGMVObject* t_obj, uint16_t t_reg, uint8_t* t_data, uint32_t t_size)
{
	uint8_t t_res = e_BM1422AGMV_STATUS_OK;
    t_res = Write_Reg_BM1422AGMV(t_obj, t_reg, t_data, t_size);
    return t_res;
}

BM1422AGMV Set_Ioctx_BM1422AGMV(BM1422AGMVObject* t_obj, BM1422AGMVIOctx* t_ioctx)
{
    if (!t_obj || !t_ioctx->IsDevReady || !t_ioctx->ReadReg || !t_ioctx->WriteReg ) {
        return e_BM1422AGMV_STATUS_ERROR;
    }

    t_obj->io.Init       = t_ioctx->Init;
    t_obj->io.DeInit     = t_ioctx->DeInit;
    t_obj->io.IsDevReady = t_ioctx->IsDevReady;
    t_obj->io.ReadReg    = t_ioctx->ReadReg;
    t_obj->io.WriteReg   = t_ioctx->WriteReg;
    t_obj->io.Wait       = t_ioctx->Wait;

    return e_BM1422AGMV_STATUS_OK;
}

BM1422AGMV Init_BM1422AGMV(BM1422AGMVObject* t_obj)			// Setting control register
{
	static uint8_t t_res  = e_BM1422AGMV_STATUS_OK;

    // Check Address
    t_res = e_BM1422AGMV_STATUS_ERROR;
    t_obj->addr = BM1422AGMV_DEV_ADDR;
    if (t_obj->io.IsDevReady(t_obj->addr) == 0){
    	t_res = e_BM1422AGMV_STATUS_OK;
    }

    // Configure Control
    if (t_res == e_BM1422AGMV_STATUS_OK) {
    	uint8_t conf_1 = BM1422AGMV_CNTL1_VALUE;
        t_res = Set_Reg_BM1422AGMV(t_obj, BM1422AGMV_CNTL1_REG, &conf_1, BM1422AGMV_CONTROL_SIZE);
        uint8_t conf_2 = BM1422AGMV_CNTL2_VALUE;
        t_res = Set_Reg_BM1422AGMV(t_obj, BM1422AGMV_CNTL2_REG, &conf_2, BM1422AGMV_CONTROL_SIZE);
        uint8_t conf_4 = BM1422AGMV_CNTL4_H_VALUE;
        t_res = Set_Reg_BM1422AGMV(t_obj, BM1422AGMV_CNTL4_REG_H, &conf_4, BM1422AGMV_CONTROL_SIZE);
        uint8_t conf_5 = BM1422AGMV_CNTL4_L_VALUE;
        t_res = Set_Reg_BM1422AGMV(t_obj, BM1422AGMV_CNTL4_REG_L, &conf_5, BM1422AGMV_CONTROL_SIZE);


        // CNTL3 should be set at LAST //
        uint8_t conf_3 = BM1422AGMV_CNTL3_VALUE;
        Set_Reg_BM1422AGMV(t_obj, BM1422AGMV_CNTL3_REG, &conf_3, BM1422AGMV_CONTROL_SIZE);
    }

    return t_res;
}

BM1422AGMV Get_Value_BM1422AGMV(BM1422AGMVObject* t_obj)
{
    uint8_t t_res = 0;
	uint8_t t_buff[6];

    t_res = t_obj->io.ReadReg(t_obj->addr, BM1422AGMV_DATAX_REG, t_buff, 6);

    int16_t t_magX = (int16_t)(t_buff[0] | t_buff[1] << 8);
    int16_t t_magY = (int16_t)(t_buff[2] | t_buff[3] << 8);
    int16_t t_magZ = (int16_t)(t_buff[4] | t_buff[5] << 8);

	/* NEED TO BE SCALED */
    t_obj->value.bm1422_mag_x = (float)t_magX;
	t_obj->value.bm1422_mag_y = (float)t_magY;
	t_obj->value.bm1422_mag_z = (float)t_magZ;

	return t_res;
}
