#ifndef DRIVERS_IOIF_INC_IOIF_I2C_H_
#define DRIVERS_IOIF_INC_IOIF_I2C_H_

#include "main.h"
#include "i2c.h"

#include <string.h>
#include <stdint.h>

#define I2C_BUFF_SIZE               20

#define I2C1_TRIALS                 10
#define I2C1_STRAT_UP_DELAY         50
#define I2C1_TIMEOUT                5

#define I2C2_TRIALS                 10
#define I2C2_STRAT_UP_DELAY         50
#define I2C2_TIMEOUT                5

#define I2C3_TRIALS                 10
#define I2C3_STRAT_UP_DELAY         50
#define I2C3_TIMEOUT                5

I2C_HandleTypeDef hi2c1;
I2C_HandleTypeDef hi2c2;
I2C_HandleTypeDef hi2c3;

/* I2C Configuration */
void Delay_I2C(uint32_t t_ms_wait);

/* I2C1 */
HAL_StatusTypeDef Init_I2C1(void);
HAL_StatusTypeDef DeInit_I2C1(void);
HAL_StatusTypeDef IsDevReady_I2C1(uint16_t t_dev_addr);

HAL_StatusTypeDef Mem_Write_I2C1(uint16_t t_dev_addr, uint16_t t_mem_addr, uint16_t t_mem_size, uint8_t *t_data, uint16_t t_size);
HAL_StatusTypeDef Mem_Read_I2C1(uint16_t t_dev_addr, uint16_t t_mem_addr, uint16_t t_mem_size, uint8_t *t_data, uint16_t t_size);

/* I2C2 */
HAL_StatusTypeDef Init_I2C2(void);
HAL_StatusTypeDef DeInit_I2C2(void);
HAL_StatusTypeDef IsDevReady_I2C2(uint16_t t_dev_addr);

HAL_StatusTypeDef Mem_Write_I2C2(uint16_t t_dev_addr, uint16_t t_mem_addr, uint16_t t_mem_size, uint8_t *t_data, uint16_t t_size);
HAL_StatusTypeDef Mem_Read_Dma_I2C2(uint16_t t_dev_addr, uint8_t *t_data, uint16_t t_size);

/* I2C3 */
HAL_StatusTypeDef Init_I2C3(void);
HAL_StatusTypeDef DeInit_I2C3(void);
HAL_StatusTypeDef IsDevReady_I2C3(uint16_t t_dev_addr);

HAL_StatusTypeDef Mem_Write_I2C3(uint16_t t_dev_addr, uint16_t t_mem_addr, uint16_t t_mem_size, uint8_t *t_data, uint16_t t_size);
HAL_StatusTypeDef Mem_Read_I2C3(uint16_t t_dev_addr, uint16_t t_mem_addr, uint16_t t_mem_size, uint8_t *t_data, uint16_t t_size);

#endif /* DRIVERS_IOIF_INC_IOIF_I2C_H_ */
