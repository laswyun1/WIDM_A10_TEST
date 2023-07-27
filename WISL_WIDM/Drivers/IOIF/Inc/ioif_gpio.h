/*
 * gpio.h
 *
 *  Created on: 2022. 7. 21.
 *      Author: User
 */

#ifndef IOIF_INC_IOIF_GPIO_H_
#define IOIF_INC_IOIF_GPIO_H_

#include "main.h"
#include "gpio.h"

typedef enum{
	LOW = 0,
	HIGH = 1
} GPIO_PIN_STATE;

typedef void (*IOIF_EXT_GPIO_Callback_Ptr) (void);

IOIF_EXT_GPIO_Callback_Ptr ioif_ext_gpio1_callback_ptr;
IOIF_EXT_GPIO_Callback_Ptr ioif_ext_gpio2_callback_ptr;
IOIF_EXT_GPIO_Callback_Ptr ioif_ext_gpio3_callback_ptr;
IOIF_EXT_GPIO_Callback_Ptr ioif_ext_gpio4_callback_ptr;
IOIF_EXT_GPIO_Callback_Ptr ioif_ext_gpio5_callback_ptr;
IOIF_EXT_GPIO_Callback_Ptr ioif_ext_gpio6_callback_ptr;
IOIF_EXT_GPIO_Callback_Ptr ioif_ext_gpio7_callback_ptr;
IOIF_EXT_GPIO_Callback_Ptr ioif_ext_gpio8_callback_ptr;
IOIF_EXT_GPIO_Callback_Ptr ioif_ext_gpio9_callback_ptr;
IOIF_EXT_GPIO_Callback_Ptr ioif_ext_gpio10_callback_ptr;

GPIO_PIN_STATE Get_GPIO_A_State(uint16_t t_GPIO_Pin);
GPIO_PIN_STATE Get_GPIO_B_State(uint16_t t_GPIO_Pin);
GPIO_PIN_STATE Get_GPIO_C_State(uint16_t t_GPIO_Pin);
GPIO_PIN_STATE Get_GPIO_D_State(uint16_t t_GPIO_Pin);
GPIO_PIN_STATE Get_GPIO_E_State(uint16_t t_GPIO_Pin);
GPIO_PIN_STATE Get_GPIO_G_State(uint16_t t_GPIO_Pin);

void Set_GPIO_A_State(uint16_t t_GPIO_Pin, GPIO_PIN_STATE t_pin_state);
void Set_GPIO_B_State(uint16_t t_GPIO_Pin, GPIO_PIN_STATE t_pin_state);
void Set_GPIO_C_State(uint16_t t_GPIO_Pin, GPIO_PIN_STATE t_pin_state);
void Set_GPIO_D_State(uint16_t t_GPIO_Pin, GPIO_PIN_STATE t_pin_state);
void Set_GPIO_E_State(uint16_t t_GPIO_Pin, GPIO_PIN_STATE t_pin_state);
void Set_GPIO_G_State(uint16_t t_GPIO_Pin, GPIO_PIN_STATE t_pin_state);

void Toggle_GPIO_A_Sate(uint16_t t_GPIO_Pin);
void Toggle_GPIO_B_Sate(uint16_t t_GPIO_Pin);
void Toggle_GPIO_C_Sate(uint16_t t_GPIO_Pin);
void Toggle_GPIO_D_Sate(uint16_t t_GPIO_Pin);
void Toggle_GPIO_E_Sate(uint16_t t_GPIO_Pin);
void Toggle_GPIO_G_Sate(uint16_t t_GPIO_Pin);

#endif /* IOIF_INC_IOIF_GPIO_H_ */
