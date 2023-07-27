/*
 * ioif_tim.c
 *
 *  Created on: Jul 27, 2022
 *      Author: USer
 */

#include "ioif_tim.h"


extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim7;
extern TIM_HandleTypeDef htim8;
extern TIM_HandleTypeDef htim9;
extern TIM_HandleTypeDef htim10;
extern TIM_HandleTypeDef htim11;
extern TIM_HandleTypeDef htim12;
extern TIM_HandleTypeDef htim13;
extern TIM_HandleTypeDef htim14;
extern TIM_HandleTypeDef htim15;
extern TIM_HandleTypeDef htim16;
extern TIM_HandleTypeDef htim17;

int Start_TIM1()    {return HAL_TIM_Base_Start_IT(&htim1);}
int Start_TIM2()    {return HAL_TIM_Base_Start_IT(&htim2);}
int Start_TIM3()    {return HAL_TIM_Base_Start_IT(&htim3);}
int Start_TIM4()    {return HAL_TIM_Base_Start_IT(&htim4);}
int Start_TIM5()    {return HAL_TIM_Base_Start_IT(&htim5);}
int Start_TIM6()    {return HAL_TIM_Base_Start_IT(&htim6);}
int Start_TIM7()    {return HAL_TIM_Base_Start_IT(&htim7);}
int Start_TIM8()    {return HAL_TIM_Base_Start_IT(&htim8);}
int Start_TIM9()    {return HAL_TIM_Base_Start_IT(&htim9);}
int Start_TIM10()   {return HAL_TIM_Base_Start_IT(&htim10);}
int Start_TIM11()   {return HAL_TIM_Base_Start_IT(&htim11);}
int Start_TIM12()   {return HAL_TIM_Base_Start_IT(&htim12);}
int Start_TIM13()   {return HAL_TIM_Base_Start_IT(&htim13);}
int Start_TIM14()   {return HAL_TIM_Base_Start_IT(&htim14);}
int Start_TIM15()   {return HAL_TIM_Base_Start_IT(&htim15);}
int Start_TIM16()   {return HAL_TIM_Base_Start_IT(&htim16);}
int Start_TIM17()   {return HAL_TIM_Base_Start_IT(&htim17);}

int Stop_TIM1()    	{return HAL_TIM_Base_Stop_IT(&htim1);}
int Stop_TIM2()    	{return HAL_TIM_Base_Stop_IT(&htim2);}
int Stop_TIM3()    	{return HAL_TIM_Base_Stop_IT(&htim3);}
int Stop_TIM4()    	{return HAL_TIM_Base_Stop_IT(&htim4);}
int Stop_TIM5()    	{return HAL_TIM_Base_Stop_IT(&htim5);}
int Stop_TIM6()    	{return HAL_TIM_Base_Stop_IT(&htim6);}
int Stop_TIM7()    	{return HAL_TIM_Base_Stop_IT(&htim7);}
int Stop_TIM8()    	{return HAL_TIM_Base_Stop_IT(&htim8);}
int Stop_TIM9()    	{return HAL_TIM_Base_Stop_IT(&htim9);}
int Stop_TIM10()   	{return HAL_TIM_Base_Stop_IT(&htim10);}
int Stop_TIM11()   	{return HAL_TIM_Base_Stop_IT(&htim11);}
int Stop_TIM12()   	{return HAL_TIM_Base_Stop_IT(&htim12);}
int Stop_TIM13()   	{return HAL_TIM_Base_Stop_IT(&htim13);}
int Stop_TIM14()   	{return HAL_TIM_Base_Stop_IT(&htim14);}
int Stop_TIM15()   	{return HAL_TIM_Base_Stop_IT(&htim15);}
int Stop_TIM16()   	{return HAL_TIM_Base_Stop_IT(&htim16);}
int Stop_TIM17()   	{return HAL_TIM_Base_Stop_IT(&htim17);}

void ms_Delay(uint32_t ms_wait) {HAL_Delay(ms_wait);}

void semaphore_acquire(volatile Semaphore* t_semaphore)
{
	t_semaphore->cnt = 0;

	while (t_semaphore->semaphore == 1) {
//		if(t_semaphore->cnt > t_semaphore->dead_lock)	break;
		t_semaphore->cnt ++;
	}

	__disable_irq(); // Disable interrupts to prevent race conditions
	t_semaphore->semaphore = 1; // Lock the semaphore
	__enable_irq(); // Re-enable interrupts
}

void semaphore_release(volatile Semaphore* t_semaphore)
{
	t_semaphore->semaphore = 0; // Release the semaphore
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	/* Timer 3(APB1) - Imu Ctrl Task CallBack*/
	if (htim->Instance == htim3.Instance) {
		if (ioif_tim3_callback_ptr != NULL) {
			ioif_tim3_callback_ptr( );
		}
	}

	/* Timer 6(APB1) - Msg hdlr Task CallBack*/
	if (htim->Instance == htim6.Instance) {
		if (ioif_tim6_callback_ptr != NULL) {
			ioif_tim6_callback_ptr( );
		}
	}
}
