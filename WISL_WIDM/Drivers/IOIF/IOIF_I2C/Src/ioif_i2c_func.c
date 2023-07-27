#include <ioif_i2c_func.h>

uint8_t i2c1_tx_buff;
uint8_t i2c3_tx_buff;

//uint8_t i2c1_rx_buff[I2C_BUFF_SIZE] __attribute__((section(".i2c1_rx_buff")));
//uint8_t i2c3_rx_buff[I2C_BUFF_SIZE] __attribute__((section(".i2c3_rx_buff")));

uint8_t i2c1_rx_buff[I2C_BUFF_SIZE];
uint8_t i2c3_rx_buff[I2C_BUFF_SIZE];

/* I2C Configure */
void Delay_I2C(uint32_t t_ms_wait) {HAL_Delay(t_ms_wait);}

HAL_StatusTypeDef Init_I2C1( ) {return HAL_I2C_Init(&hi2c1);}
HAL_StatusTypeDef Init_I2C2( ) {return HAL_I2C_Init(&hi2c2);}
HAL_StatusTypeDef Init_I2C3( ) {return HAL_I2C_Init(&hi2c3);}

HAL_StatusTypeDef DeInit_I2C1( ) {return HAL_I2C_DeInit(&hi2c1);}
HAL_StatusTypeDef DeInit_I2C2( ) {return HAL_I2C_DeInit(&hi2c2);}
HAL_StatusTypeDef DeInit_I2C3( ) {return HAL_I2C_DeInit(&hi2c3);}

HAL_StatusTypeDef IsDevReady_I2C1(uint16_t t_dev_addr) {return HAL_I2C_IsDeviceReady(&hi2c1, t_dev_addr, I2C1_TRIALS, I2C1_STRAT_UP_DELAY);}
HAL_StatusTypeDef IsDevReady_I2C2(uint16_t t_dev_addr) {return HAL_I2C_IsDeviceReady(&hi2c2, t_dev_addr, I2C2_TRIALS, I2C2_STRAT_UP_DELAY);}
HAL_StatusTypeDef IsDevReady_I2C3(uint16_t t_dev_addr) {return HAL_I2C_IsDeviceReady(&hi2c3, t_dev_addr, I2C3_TRIALS, I2C3_STRAT_UP_DELAY);}

/* I2C1 Read/Write */
HAL_StatusTypeDef Mem_Write_I2C1(uint16_t t_dev_addr, uint16_t t_mem_addr, uint16_t t_mem_size, uint8_t *t_data, uint16_t t_size)
{
	HAL_StatusTypeDef t_read_status = HAL_OK;

	memcpy(&i2c1_tx_buff, t_data, t_size);
	if ( hi2c1.State != HAL_I2C_STATE_BUSY ){
		t_read_status = HAL_I2C_Mem_Write(&hi2c1, t_dev_addr, t_mem_addr, t_mem_size, &i2c1_tx_buff, t_size, I2C1_TIMEOUT);
	} else {
		return HAL_BUSY;
	}

	return t_read_status;
}

HAL_StatusTypeDef Mem_Read_I2C1(uint16_t t_dev_addr, uint16_t t_mem_addr, uint16_t t_mem_size, uint8_t *t_data, uint16_t t_size)
{
	HAL_StatusTypeDef t_read_status = HAL_OK;

	if ( hi2c1.State != HAL_I2C_STATE_BUSY ){
		t_read_status = HAL_I2C_Mem_Read(&hi2c1, t_dev_addr, t_mem_addr, t_mem_size, i2c1_rx_buff, t_size, I2C1_TIMEOUT);
//		t_read_status = HAL_I2C_Mem_Read_DMA(&hi2c1, t_dev_addr, t_mem_addr, t_mem_size, i2c1_rx_buff, t_size);
//		t_read_status = HAL_I2C_Master_Receive_DMA(&hi2c1, t_dev_addr, i2c1_rx_buff, t_size);
//		while (HAL_DMA_GetState(&hdma_i2c1_rx) != HAL_DMA_STATE_READY){
//		}
		memcpy(t_data, i2c1_rx_buff, t_size);
	} else {
		return HAL_BUSY;
	}

	return t_read_status;
}

/* I2C3 Read/Write */
HAL_StatusTypeDef Mem_Write_I2C3(uint16_t t_dev_addr, uint16_t t_mem_addr, uint16_t t_mem_size, uint8_t *t_data, uint16_t t_size)
{
	HAL_StatusTypeDef t_read_status = HAL_OK;

	memcpy(&i2c3_tx_buff, t_data, t_size);
	if ( hi2c3.State != HAL_I2C_STATE_BUSY ){
		t_read_status = HAL_I2C_Mem_Write(&hi2c3, t_dev_addr, t_mem_addr, t_mem_size, &i2c3_tx_buff, t_size, I2C3_TIMEOUT);
	} else {
		return HAL_BUSY;
	}

	return t_read_status;
}

HAL_StatusTypeDef Mem_Read_I2C3(uint16_t t_dev_addr, uint16_t t_mem_addr, uint16_t t_mem_size, uint8_t *t_data, uint16_t t_size)
{
	HAL_StatusTypeDef t_read_status = HAL_OK;

	if ( hi2c3.State != HAL_I2C_STATE_BUSY ){
//		t_read_status = HAL_I2C_Mem_Read_DMA(&hi2c3, t_dev_addr, t_mem_addr, t_mem_size, i2c3_rx_buff, t_size);
		t_read_status = HAL_I2C_Mem_Read(&hi2c3, t_dev_addr, t_mem_addr, t_mem_size, i2c3_rx_buff, t_size, I2C3_TIMEOUT);
		memcpy(t_data, i2c3_rx_buff, t_size);
	} else {
		return HAL_BUSY;
	}

	return t_read_status;
}
