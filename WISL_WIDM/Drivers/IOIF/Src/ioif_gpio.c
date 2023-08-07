/*
 * ioif_gpio.c
 *
 *  Created on: 2022. 7. 21.
 *      Author: User
 */

#include "ioif_gpio.h"

GPIO_PIN_STATE Get_GPIO_A_State(uint16_t t_GPIO_Pin) { return HAL_GPIO_ReadPin(GPIOA, t_GPIO_Pin); }
GPIO_PIN_STATE Get_GPIO_B_State(uint16_t t_GPIO_Pin) { return HAL_GPIO_ReadPin(GPIOB, t_GPIO_Pin); }
GPIO_PIN_STATE Get_GPIO_C_State(uint16_t t_GPIO_Pin) { return HAL_GPIO_ReadPin(GPIOC, t_GPIO_Pin); }
GPIO_PIN_STATE Get_GPIO_D_State(uint16_t t_GPIO_Pin) { return HAL_GPIO_ReadPin(GPIOD, t_GPIO_Pin); }
GPIO_PIN_STATE Get_GPIO_E_State(uint16_t t_GPIO_Pin) { return HAL_GPIO_ReadPin(GPIOE, t_GPIO_Pin); }
GPIO_PIN_STATE Get_GPIO_G_State(uint16_t t_GPIO_Pin) { return HAL_GPIO_ReadPin(GPIOG, t_GPIO_Pin); }

void Set_GPIO_A_State(uint16_t t_GPIO_Pin, GPIO_PIN_STATE t_pin_state) { HAL_GPIO_WritePin(GPIOA, t_GPIO_Pin, t_pin_state); }
void Set_GPIO_B_State(uint16_t t_GPIO_Pin, GPIO_PIN_STATE t_pin_state) { HAL_GPIO_WritePin(GPIOB, t_GPIO_Pin, t_pin_state); }
void Set_GPIO_C_State(uint16_t t_GPIO_Pin, GPIO_PIN_STATE t_pin_state) { HAL_GPIO_WritePin(GPIOC, t_GPIO_Pin, t_pin_state); }
void Set_GPIO_D_State(uint16_t t_GPIO_Pin, GPIO_PIN_STATE t_pin_state) { HAL_GPIO_WritePin(GPIOD, t_GPIO_Pin, t_pin_state); }
void Set_GPIO_E_State(uint16_t t_GPIO_Pin, GPIO_PIN_STATE t_pin_state) { HAL_GPIO_WritePin(GPIOE, t_GPIO_Pin, t_pin_state); }
void Set_GPIO_G_State(uint16_t t_GPIO_Pin, GPIO_PIN_STATE t_pin_state) { HAL_GPIO_WritePin(GPIOG, t_GPIO_Pin, t_pin_state); }

void Toggle_GPIO_A_Sate(uint16_t t_GPIO_Pin) { HAL_GPIO_TogglePin(GPIOA, t_GPIO_Pin); }
void Toggle_GPIO_B_Sate(uint16_t t_GPIO_Pin) { HAL_GPIO_TogglePin(GPIOB, t_GPIO_Pin); }
void Toggle_GPIO_C_Sate(uint16_t t_GPIO_Pin) { HAL_GPIO_TogglePin(GPIOC, t_GPIO_Pin); }
void Toggle_GPIO_D_Sate(uint16_t t_GPIO_Pin) { HAL_GPIO_TogglePin(GPIOD, t_GPIO_Pin); }
void Toggle_GPIO_E_Sate(uint16_t t_GPIO_Pin) { HAL_GPIO_TogglePin(GPIOE, t_GPIO_Pin); }
void Toggle_GPIO_G_Sate(uint16_t t_GPIO_Pin) { HAL_GPIO_TogglePin(GPIOG, t_GPIO_Pin); }

void HAL_GPIO_EXTI_Callback(uint16_t t_GPIO_Pin)
{
	UNUSED(t_GPIO_Pin);
}
