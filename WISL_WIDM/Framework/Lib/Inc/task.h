/*
 * device.h
 *
 *  Created on: Aug 5, 2022
 *      Author: User
 */

#ifndef FRAMEWORK_LIB_INC_TASK_H_
#define FRAMEWORK_LIB_INC_TASK_H_

#include "routine.h"
#include "stdbool.h"
#include "state_machine.h"

#define TASK_CREATE_STATE(t_task_ptr, t_state, t_ent_fncptr, t_run_fncptr, t_ext_fncptr, t_is_default)  \
	Set_Task_State_Entity((t_task_ptr), (t_state), Create_State_Entity((t_ent_fncptr), (t_run_fncptr), (t_ext_fncptr)), t_is_default)

#define TASK_CREATE_ROUTINE(t_task_ptr, t_id, t_ent_fncptr, t_run_fncptr, t_ext_fncptr) \
    Set_Task_Routine_Entity((t_task_ptr), (t_id), Create_Routine_Entity((t_ent_fncptr), (t_run_fncptr), (t_ext_fncptr)))



typedef struct TaskStruct {
    int id;
    char* name;
    int period;

    StateMachineStruct state_machine;
    RoutineStruct routine;
    uint16_t err_code;

} TaskStruct;

void Init_Task(TaskStruct* t_task);
void Run_Task(TaskStruct* t_task);

void Set_Task_State_Entity(TaskStruct* t_task, StateEnum t_state, StateEntityStruct t_entity, bool t_is_default);
void Set_Task_Routine_Entity(TaskStruct* t_task, int t_id, RoutineEntityStruct t_entity);

#endif /* FRAMEWORK_LIB_INC_TASK_H_ */
