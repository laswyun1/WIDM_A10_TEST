/*
 * device.c
 *
 *  Created on: Aug 5, 2022
 *      Author: User
 */


#include <task.h>

// Device Interface
void Init_Task(TaskStruct* t_task)
{
    Init_State_Machine(&t_task->state_machine);
    Init_Routine(&t_task->routine);
}

void Run_Task(TaskStruct* t_task)
{
    Run_State_Machine(&t_task->state_machine);
}

void Set_Task_State_Entity(TaskStruct* t_task, StateEnum t_state, StateEntityStruct t_entity, bool t_is_default)
{
	t_task->state_machine.entity[t_state] = t_entity;

    if (t_is_default) {
    	t_task->state_machine.curr_state = t_state;
    	t_task->state_machine.prev_state = t_state;
    }
}

//TODO: id, order range/duplication check
void Set_Task_Routine_Entity(TaskStruct* t_task, int t_id, RoutineEntityStruct t_entity)
{
	t_task->routine.entities[t_id] = t_entity;
}

