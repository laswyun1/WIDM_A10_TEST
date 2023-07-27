/*
 * tim.h
 *
 *  Created on: Jul 27, 2022
 *      Author: User
 */

#ifndef DRIVERS_IOIF_INC_IOIF_TIM_H_
#define DRIVERS_IOIF_INC_IOIF_TIM_H_

#include "main.h"
#include "tim.h"

typedef void (*TimCallback)	(void);

TimCallback ioif_tim1_callback_ptr;
TimCallback ioif_tim2_callback_ptr;
TimCallback ioif_tim3_callback_ptr;
TimCallback ioif_tim4_callback_ptr;
TimCallback ioif_tim5_callback_ptr;
TimCallback ioif_tim6_callback_ptr;
TimCallback ioif_tim7_callback_ptr;
TimCallback ioif_tim8_callback_ptr;
TimCallback ioif_tim9_callback_ptr;
TimCallback ioif_tim10_callback_ptr;
TimCallback ioif_tim11_callback_ptr;
TimCallback ioif_tim12_callback_ptr;
TimCallback ioif_tim13_callback_ptr;
TimCallback ioif_tim14_callback_ptr;
TimCallback ioif_tim15_callback_ptr;
TimCallback ioif_tim16_callback_ptr;
TimCallback ioif_tim17_callback_ptr;

int Start_TIM1( );
int Start_TIM2( );
int Start_TIM3( );
int Start_TIM4( );
int Start_TIM5( );
int Start_TIM6( );
int Start_TIM7( );
int Start_TIM8( );
int Start_TIM9( );
int Start_TIM10( );
int Start_TIM11( );
int Start_TIM12( );
int Start_TIM13( );
int Start_TIM14( );
int Start_TIM15( );
int Start_TIM16( );
int Start_TIM17( );

int Stop_TIM1( );
int Stop_TIM2( );
int Stop_TIM3( );
int Stop_TIM4( );
int Stop_TIM5( );
int Stop_TIM6( );
int Stop_TIM7( );
int Stop_TIM8( );
int Stop_TIM9( );
int Stop_TIM10( );
int Stop_TIM11( );
int Stop_TIM12( );
int Stop_TIM13( );
int Stop_TIM14( );
int Stop_TIM15( );
int Stop_TIM16( );
int Stop_TIM17( );

typedef struct _Semaphore{
	volatile uint8_t semaphore;
	volatile float shared_variable;
	uint32_t dead_lock;
	uint32_t cnt;
}Semaphore;

volatile Semaphore s_current_ref;
volatile Semaphore s_position_ref;

void ms_Delay(uint32_t ms_wait);
void semaphore_acquire(volatile Semaphore *t_semaphore);
void semaphore_release(volatile Semaphore *t_semaphore);

#endif /* DRIVERS_IOIF_INC_IOIF_TIM_H_ */
