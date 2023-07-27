/*
 * drive_routine.h
 *
 *  Created on: Sep 6, 2022
 *      Author: mingoo
 */

#ifndef FRAMEWORK_LIB_INC_ROUTINE_H_
#define FRAMEWORK_LIB_INC_ROUTINE_H_

#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#define ROUTINE_MAX_ENTITIES 8
#define ROUTINE_DEFAULT_ID -1

// Routine Entity
typedef int (*RoutineFncPtr) (void);

typedef enum _RoutineEntityEnum{
    e_RoutineEntity_Ent,
	e_RoutineEntity_Run,
	e_RoutineEntity_Ext,
} RoutineEntityEnum;

typedef struct _RoutineEntityStruct {
    RoutineFncPtr on_enter;
    RoutineFncPtr on_run;
    RoutineFncPtr on_exit;
} RoutineEntityStruct;

RoutineEntityStruct Create_Routine_Entity(RoutineFncPtr t_ent, RoutineFncPtr t_run, RoutineFncPtr t_ext);


typedef struct RoutineStruct {
    int id[ROUTINE_MAX_ENTITIES];
    size_t n_id;
    RoutineEntityStruct entities[ROUTINE_MAX_ENTITIES];
} RoutineStruct;


// DriveRoutine Interface
void Init_Routine(RoutineStruct* t_routine);

int Ent_Routines(RoutineStruct* t_routine);
int Run_Routines(RoutineStruct* t_routine);
int Ext_Routines(RoutineStruct* t_routine);

void Clear_Routines(RoutineStruct* t_routine);

int Push_Routine(RoutineStruct* t_routine, uint8_t t_id);

#endif /* FRAMEWORK_LIB_INC_ROUTINE_H_ */
