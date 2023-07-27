/*
 * state_machine.h
 *
 *  Created on: Aug 5, 2022
 *      Author: User
 */

#ifndef FRAMEWORK_LIB_INC_STATE_MACHINE_H_
#define FRAMEWORK_LIB_INC_STATE_MACHINE_H_

#include "unistd.h"

// State & Transition Map
#define STATE_MACHINE_N_STATES 4

typedef enum _StateEnum{
    e_State_Off = 0,
	e_State_Standby = 1,
	e_State_Enable = 2,
	e_State_Error = 3,
} StateEnum;


// State Functions
typedef void (*StateFuncPtr) (void);

typedef struct _StateEntityStruct
{
    StateFuncPtr on_enter;
    StateFuncPtr on_run;
    StateFuncPtr on_exit;
} StateEntityStruct;


StateEntityStruct Create_State_Entity(StateFuncPtr t_ent, StateFuncPtr t_run, StateFuncPtr t_ext);


// State Machine
typedef enum StateEntityLifeCycle{
    e_StateEntity_Ent,
	e_StateEntity_Run,
	e_StateEntity_Ext,
} StateEntityLifeCycle;

typedef struct _StateMachineStruct
{
    StateEnum curr_state;
    StateEnum prev_state;
    StateEntityLifeCycle entity_life_cycle;

    StateEntityStruct entity[STATE_MACHINE_N_STATES];
} StateMachineStruct;


// State Machine Interfaces
void Init_State_Machine(StateMachineStruct* t_sm);
void Run_State_Machine(StateMachineStruct* t_sm);

void Transition_State(StateMachineStruct* t_sm, StateEnum t_state_cmd);

#endif /* FRAMEWORK_LIB_INC_STATE_MACHINE_H_ */
