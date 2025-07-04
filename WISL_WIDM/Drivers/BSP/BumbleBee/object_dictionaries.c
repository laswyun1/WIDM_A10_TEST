/*
 * object_dictionaries.c
 *
 *  Created on: 2022. 10. 13.
 *      Author: mingoo
 */

#include "object_dictionaries.h"


/*
    _   ___ ___ ___ __  __ ___ _    ___
   /_\ / __/ __| __|  \/  | _ ) |  | __|
  / _ \\__ \__ \ _|| |\/| | _ \ |__| _|
 /_/ \_\___/___/___|_|  |_|___/____|___|

*/

uint8_t Convert_DataSize(int t_data_type)
{
	switch(t_data_type){
	case UINT8_T: 		return 1;		break;
	case UINT16_T:		return 2;		break;
	case UINT32_T:		return 4;		break;
	case INT8_T:		return 1;		break;
	case INT16_T:		return 2;		break;
	case INT32_T:		return 4;		break;
	case FLOAT32_T:		return 4;		break;
	case FLOAT64_T:		return 8;		break;
	case STRING10:		return 32;		break;
	default:			return 0;		break;
	}
}

static void Assemble_SDO(SDOinfo* t_do_addr, uint8_t t_data_type)
{
	SDOinfo temp = t_data_type;
	memcpy(t_do_addr, &temp, sizeof(SDOinfo));
}

static void Assemble_PDO(PDOinfo* t_do_addr, uint8_t t_data_type, uint8_t t_num_of_data)
{
	PDOinfo temp = {t_data_type, t_num_of_data};
	memcpy(t_do_addr, &temp, sizeof(PDOinfo));
}




/*
  _____ _   ___ _    ___
 |_   _/_\ | _ ) |  | __|
   | |/ _ \| _ \ |__| _|
   |_/_/ \_\___/____|___|

*/

void Create_SDOTable_ObjDictionary()
{
	//********************************************************************************//
	//						|	  Task_ID	  |			SDO_ID			| DATA_TYPE | //
	//********************************************************************************//
	/*LOWLEVEL Task*/
	Assemble_SDO( &SDO_Table [TASK_ID_LOWLEVEL] [SDO_ID_LOWLEVEL_GET_STATE],  	    			UINT8_T);
	Assemble_SDO( &SDO_Table [TASK_ID_LOWLEVEL] [SDO_ID_LOWLEVEL_SET_STATE],  	    			UINT8_T);
	Assemble_SDO( &SDO_Table [TASK_ID_LOWLEVEL] [SDO_ID_LOWLEVEL_GET_ROUTINE],  				UINT8_T);
	Assemble_SDO( &SDO_Table [TASK_ID_LOWLEVEL] [SDO_ID_LOWLEVEL_SET_ROUTINE],  				UINT8_T);
	Assemble_SDO( &SDO_Table [TASK_ID_LOWLEVEL] [SDO_ID_LOWLEVEL_NAME],  						STRING10);
	Assemble_SDO( &SDO_Table [TASK_ID_LOWLEVEL] [SDO_ID_LOWLEVEL_POLE_PAIR],  					UINT8_T);
	Assemble_SDO( &SDO_Table [TASK_ID_LOWLEVEL] [SDO_ID_LOWLEVEL_ENCODER_RESOLUTION],  			UINT16_T);
	Assemble_SDO( &SDO_Table [TASK_ID_LOWLEVEL] [SDO_ID_LOWLEVEL_GEAR_RATIO],  					FLOAT32_T);
	Assemble_SDO( &SDO_Table [TASK_ID_LOWLEVEL] [SDO_ID_LOWLEVEL_TORQUE_CONSTANT],  			FLOAT32_T);
	Assemble_SDO( &SDO_Table [TASK_ID_LOWLEVEL] [SDO_ID_LOWLEVEL_VELOCITY_CONSTANT],  			FLOAT32_T);
	Assemble_SDO( &SDO_Table [TASK_ID_LOWLEVEL] [SDO_ID_LOWLEVEL_PEAK_CURRENT_LIMIT],  			FLOAT32_T);
	Assemble_SDO( &SDO_Table [TASK_ID_LOWLEVEL] [SDO_ID_LOWLEVEL_CONTINUOUS_CURRENT_LIMIT],  	FLOAT32_T);
	Assemble_SDO( &SDO_Table [TASK_ID_LOWLEVEL] [SDO_ID_LOWLEVEL_MAX_VELOCITY],		  			FLOAT32_T);
	Assemble_SDO( &SDO_Table [TASK_ID_LOWLEVEL] [SDO_ID_LOWLEVEL_COMMUTATION_DUTY],  			UINT16_T);
	Assemble_SDO( &SDO_Table [TASK_ID_LOWLEVEL] [SDO_ID_LOWLEVEL_USER_DIRECTION],  				FLOAT32_T);
	Assemble_SDO( &SDO_Table [TASK_ID_LOWLEVEL] [SDO_ID_LOWLEVEL_ELEC_SYSTEM_ID_MAG],  			FLOAT32_T);
	Assemble_SDO( &SDO_Table [TASK_ID_LOWLEVEL] [SDO_ID_LOWLEVEL_TERMINAL_RESISTANCE],  		FLOAT32_T);
	Assemble_SDO( &SDO_Table [TASK_ID_LOWLEVEL] [SDO_ID_LOWLEVEL_TERMINAL_INDUCTANCE],  		FLOAT32_T);
	Assemble_SDO( &SDO_Table [TASK_ID_LOWLEVEL] [SDO_ID_LOWLEVEL_BEMF_ID_VELOCITY],  			FLOAT32_T);
	Assemble_SDO( &SDO_Table [TASK_ID_LOWLEVEL] [SDO_ID_LOWLEVEL_BEMF_ID_GAIN_PCTG],  			UINT8_T);
	Assemble_SDO( &SDO_Table [TASK_ID_LOWLEVEL] [SDO_ID_LOWLEVEL_CURRENT_CTRL_BW_RAD],  		FLOAT32_T);
	Assemble_SDO( &SDO_Table [TASK_ID_LOWLEVEL] [SDO_ID_LOWLEVEL_INERTIA],  					FLOAT32_T);
	Assemble_SDO( &SDO_Table [TASK_ID_LOWLEVEL] [SDO_ID_LOWLEVEL_DAMPING_COEF],  				FLOAT32_T);
	Assemble_SDO( &SDO_Table [TASK_ID_LOWLEVEL] [SDO_ID_LOWLEVEL_MECH_MODEL_A],  				FLOAT32_T);
	Assemble_SDO( &SDO_Table [TASK_ID_LOWLEVEL] [SDO_ID_LOWLEVEL_MECH_MODEL_B],  				FLOAT32_T);

	Assemble_SDO( &SDO_Table [TASK_ID_LOWLEVEL] [SDO_ID_LOWLEVEL_FRICTION_ID_INFO],  			FLOAT32_T);
	Assemble_SDO( &SDO_Table [TASK_ID_LOWLEVEL] [SDO_ID_LOWLEVEL_FRICTION_LUT_INFO],  			FLOAT32_T);




	/*Joint Task*/
	Assemble_SDO( &SDO_Table [TASK_ID_MIDLEVEL] [SDO_ID_MIDLEVEL_GET_STATE],  					UINT8_T);
	Assemble_SDO( &SDO_Table [TASK_ID_MIDLEVEL] [SDO_ID_MIDLEVEL_SET_STATE],  					UINT8_T);
	Assemble_SDO( &SDO_Table [TASK_ID_MIDLEVEL] [SDO_ID_MIDLEVEL_GET_ROUTINE], 					UINT8_T);
	Assemble_SDO( &SDO_Table [TASK_ID_MIDLEVEL] [SDO_ID_MIDLEVEL_SET_ROUTINE], 					UINT8_T);

	Assemble_SDO( &SDO_Table [TASK_ID_MIDLEVEL] [SDO_ID_MIDLEVEL_IRC_NUMERATOR_LENGTH],	 		UINT8_T);
	Assemble_SDO( &SDO_Table [TASK_ID_MIDLEVEL] [SDO_ID_MIDLEVEL_IRC_DENOMINATOR_LENGTH],		UINT8_T);
	Assemble_SDO( &SDO_Table [TASK_ID_MIDLEVEL] [SDO_ID_MIDLEVEL_IRC_NUMERATOR],	  			FLOAT32_T);
	Assemble_SDO( &SDO_Table [TASK_ID_MIDLEVEL] [SDO_ID_MIDLEVEL_IRC_DENOMINATOR],	  			FLOAT32_T);
	Assemble_SDO( &SDO_Table [TASK_ID_MIDLEVEL] [SDO_ID_MIDLEVEL_IRC_SATURATION],	  			FLOAT32_T);

	Assemble_SDO( &SDO_Table [TASK_ID_MIDLEVEL] [SDO_ID_MIDLEVEL_IMP_VIRTUAL_STIFFNESS],	  	FLOAT32_T);
	Assemble_SDO( &SDO_Table [TASK_ID_MIDLEVEL] [SDO_ID_MIDLEVEL_IMP_VIRTUAL_DAMPER],	  		FLOAT32_T);

	Assemble_SDO( &SDO_Table [TASK_ID_MIDLEVEL] [SDO_ID_MIDLEVEL_VELOCITY_PERIODIC_SIG_INFO],	FLOAT32_T);
	Assemble_SDO( &SDO_Table [TASK_ID_MIDLEVEL] [SDO_ID_MIDLEVEL_POSITION_PERIODIC_SIG_INFO],	FLOAT32_T);

	Assemble_SDO( &SDO_Table [TASK_ID_MIDLEVEL] [SDO_ID_MIDLEVEL_DOB_Q_BW],						FLOAT32_T);
	Assemble_SDO( &SDO_Table [TASK_ID_MIDLEVEL] [SDO_ID_MIDLEVEL_DOB_GQ_NUM],					FLOAT32_T);
	Assemble_SDO( &SDO_Table [TASK_ID_MIDLEVEL] [SDO_ID_MIDLEVEL_DOB_GQ_DEN],					FLOAT32_T);
	Assemble_SDO( &SDO_Table [TASK_ID_MIDLEVEL] [SDO_ID_MIDLEVEL_DOB_Q_NUM],					FLOAT32_T);
	Assemble_SDO( &SDO_Table [TASK_ID_MIDLEVEL] [SDO_ID_MIDLEVEL_DOB_Q_DEN],					FLOAT32_T);
	Assemble_SDO( &SDO_Table [TASK_ID_MIDLEVEL] [SDO_ID_MIDLEVEL_DOB_SATURATION],				FLOAT32_T);

	Assemble_SDO( &SDO_Table [TASK_ID_MIDLEVEL] [SDO_ID_MIDLEVEL_VELOCITY_CTRL_BW],				FLOAT32_T);
	Assemble_SDO( &SDO_Table [TASK_ID_MIDLEVEL] [SDO_ID_MIDLEVEL_VELOCITY_CTRL_P_GAIN],			FLOAT32_T);
	Assemble_SDO( &SDO_Table [TASK_ID_MIDLEVEL] [SDO_ID_MIDLEVEL_VELOCITY_CTRL_I_GAIN],			FLOAT32_T);

	Assemble_SDO( &SDO_Table [TASK_ID_MIDLEVEL] [SDO_ID_MIDLEVEL_POSITION_CTRL_INPUT_PENALTY],	FLOAT32_T);
	Assemble_SDO( &SDO_Table [TASK_ID_MIDLEVEL] [SDO_ID_MIDLEVEL_POSITION_CTRL_P_GAIN],			FLOAT32_T);
	Assemble_SDO( &SDO_Table [TASK_ID_MIDLEVEL] [SDO_ID_MIDLEVEL_POSITION_CTRL_D_GAIN],			FLOAT32_T);

	Assemble_SDO( &SDO_Table [TASK_ID_MIDLEVEL] [SDO_ID_MIDLEVEL_MID_CTRL_SATURATION],			FLOAT32_T);

	Assemble_SDO( &SDO_Table [TASK_ID_MIDLEVEL] [SDO_ID_MIDLEVEL_INCENCODER_SET_OFFSET],		UINT8_T);
	Assemble_SDO( &SDO_Table [TASK_ID_MIDLEVEL] [SDO_ID_MIDLEVEL_ABSENCODER_SET_OFFSET],		UINT8_T);
	Assemble_SDO( &SDO_Table [TASK_ID_MIDLEVEL] [SDO_ID_MIDLEVEL_ABSENCODER_CHANGE_DIRECTION],	UINT8_T);

	Assemble_SDO( &SDO_Table [TASK_ID_MIDLEVEL] [SDO_ID_MIDLEVEL_VSD_STIFFNESS],				FLOAT32_T);
	Assemble_SDO( &SDO_Table [TASK_ID_MIDLEVEL] [SDO_ID_MIDLEVEL_VSD_DAMPER],					FLOAT32_T);
	Assemble_SDO( &SDO_Table [TASK_ID_MIDLEVEL] [SDO_ID_MIDLEVEL_VSD_DAMPED_RANGE],				FLOAT32_T);
	Assemble_SDO( &SDO_Table [TASK_ID_MIDLEVEL] [SDO_ID_MIDLEVEL_VSD_STIFF_RANGE],				FLOAT32_T);
	Assemble_SDO( &SDO_Table [TASK_ID_MIDLEVEL] [SDO_ID_MIDLEVEL_SET_VSD_UPPER_LIMIT],			UINT8_T);
	Assemble_SDO( &SDO_Table [TASK_ID_MIDLEVEL] [SDO_ID_MIDLEVEL_SET_VSD_LOWER_LIMIT],			UINT8_T);
	Assemble_SDO( &SDO_Table [TASK_ID_MIDLEVEL] [SDO_ID_MIDLEVEL_VSD_SATURATION],				FLOAT32_T);

	Assemble_SDO( &SDO_Table [TASK_ID_MIDLEVEL] [SDO_ID_MIDLEVEL_FEEDFORWARD_NUM],				FLOAT32_T);
	Assemble_SDO( &SDO_Table [TASK_ID_MIDLEVEL] [SDO_ID_MIDLEVEL_FEEDFORWARD_DEN],				FLOAT32_T);
	Assemble_SDO( &SDO_Table [TASK_ID_MIDLEVEL] [SDO_ID_MIDLEVEL_VELOCITY_ESTIMATOR],			UINT8_T);
	Assemble_SDO( &SDO_Table [TASK_ID_MIDLEVEL] [SDO_ID_MIDLEVEL_VELOCITY_ESTIMATOR_LEAD_LAG],	FLOAT32_T);

	Assemble_SDO( &SDO_Table [TASK_ID_MIDLEVEL] [SDO_ID_MIDLEVEL_ENCODER_RESOLUTION],			UINT16_T);
	Assemble_SDO( &SDO_Table [TASK_ID_MIDLEVEL] [SDO_ID_MIDLEVEL_SYSTEM_ID_SBS_INFO],			FLOAT32_T);
	Assemble_SDO( &SDO_Table [TASK_ID_MIDLEVEL] [SDO_ID_MIDLEVEL_SYSTEM_ID_VERIFICATION_MAG],	FLOAT32_T);

	Assemble_SDO( &SDO_Table [TASK_ID_MIDLEVEL] [SDO_ID_MIDLEVEL_TORQUE_GENERATOR_MODE_IDX],	UINT8_T);
	Assemble_SDO( &SDO_Table [TASK_ID_MIDLEVEL] [SDO_ID_MIDLEVEL_TORQUE_GENERATOR_TMAX],		INT16_T);



	/*MSG Handler Task*/
	Assemble_SDO( &SDO_Table [TASK_ID_MSG] [SDO_ID_MSG_GET_STATE],  	    UINT8_T);
	Assemble_SDO( &SDO_Table [TASK_ID_MSG] [SDO_ID_MSG_SET_STATE],  	    UINT8_T);
	Assemble_SDO( &SDO_Table [TASK_ID_MSG] [SDO_ID_MSG_GET_ROUTINE],  		UINT8_T);
	Assemble_SDO( &SDO_Table [TASK_ID_MSG] [SDO_ID_MSG_SET_ROUTINE],  		UINT8_T);
	Assemble_SDO( &SDO_Table [TASK_ID_MSG] [SDO_ID_MSG_PDO_LIST], 			UINT16_T);
	Assemble_SDO( &SDO_Table [TASK_ID_MSG] [SDO_ID_MSG_MS_ENUM],  			UINT8_T);
	Assemble_SDO( &SDO_Table [TASK_ID_MSG] [SDO_ID_MSG_GUI_COMM_ONOFF],  	UINT8_T);
	Assemble_SDO( &SDO_Table [TASK_ID_MSG] [SDO_ID_MSG_GUI_COMM_COMMAND],  	UINT8_T);

	/*IMU Task*/
	Assemble_SDO( &SDO_Table [TASK_ID_IMU] [SDO_ID_IMU_GET_STATE],  		UINT8_T);
	Assemble_SDO( &SDO_Table [TASK_ID_IMU] [SDO_ID_IMU_SET_STATE],  		UINT8_T);
	Assemble_SDO( &SDO_Table [TASK_ID_IMU] [SDO_ID_IMU_GET_ROUTINE],  	    UINT8_T);
	Assemble_SDO( &SDO_Table [TASK_ID_IMU] [SDO_ID_IMU_SET_ROUTINE],  	    UINT8_T);
	Assemble_SDO( &SDO_Table [TASK_ID_IMU] [SDO_ID_IMU_FOR_TEST],  			UINT16_T);


	/*SYSMNGT Task*/
	Assemble_SDO( &SDO_Table [TASK_ID_SYSMNGT] [SDO_ID_SYSMNGT_GET_STATE],  	UINT8_T);
	Assemble_SDO( &SDO_Table [TASK_ID_SYSMNGT] [SDO_ID_SYSMNGT_SET_STATE],  	UINT8_T);
	Assemble_SDO( &SDO_Table [TASK_ID_SYSMNGT] [SDO_ID_SYSMNGT_GET_ROUTINE],  	UINT8_T);
	Assemble_SDO( &SDO_Table [TASK_ID_SYSMNGT] [SDO_ID_SYSMNGT_SET_ROUTINE],  	UINT8_T);
	Assemble_SDO( &SDO_Table [TASK_ID_SYSMNGT] [SDO_ID_SYSMNGT_FOR_TEST],  		UINT16_T);


	/*EXTDEV Task*/
	Assemble_SDO( &SDO_Table [TASK_ID_EXTDEV] [SDO_ID_EXTDEV_GET_STATE],  		UINT8_T);
	Assemble_SDO( &SDO_Table [TASK_ID_EXTDEV] [SDO_ID_EXTDEV_SET_STATE],  		UINT8_T);
	Assemble_SDO( &SDO_Table [TASK_ID_EXTDEV] [SDO_ID_EXTDEV_GET_ROUTINE],  	UINT8_T);
	Assemble_SDO( &SDO_Table [TASK_ID_EXTDEV] [SDO_ID_EXTDEV_SET_ROUTINE],  	UINT8_T);
	Assemble_SDO( &SDO_Table [TASK_ID_EXTDEV] [SDO_ID_EXTDEV_DC_SET_LENGTH],  	FLOAT32_T);
	Assemble_SDO( &SDO_Table [TASK_ID_EXTDEV] [SDO_ID_EXTDEV_DC_SET_DIRECT],  	UINT8_T);
	Assemble_SDO( &SDO_Table [TASK_ID_EXTDEV] [SDO_ID_EXTDEV_FOR_TEST],  		INT16_T);
}


void Create_PDOTable_ObjDictionary()
{
	//**************************************************************************************************//
	//							   |	  Task_ID	  |				PDO_ID				| DATA_TYPE | #_of_DATA //
	//**************************************************************************************************//
	/*LOWLEVEL Task*/
	Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_LOWLEVEL] [PDO_ID_LOWLEVEL_PHASES_CURRENT],  			UINT16_T, 	 	3);
	Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_LOWLEVEL] [PDO_ID_LOWLEVEL_PHASES_VOLTAGE],  			UINT16_T,  		3);
	Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_LOWLEVEL] [PDO_ID_LOWLEVEL_POSITION],  					FLOAT32_T,  	1);
	Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_LOWLEVEL] [PDO_ID_LOWLEVEL_VELOCITY],  					INT32_T,  		2);
	Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_LOWLEVEL] [PDO_ID_LOWLEVEL_CLARKE_OUT],  				INT32_T,  		2);
	Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_LOWLEVEL] [PDO_ID_LOWLEVEL_PARK_OUT],  					FLOAT32_T,  	3);
	Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_LOWLEVEL] [PDO_ID_LOWLEVEL_VOLTAGE_IN],	    			FLOAT32_T,  	3);
	Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_LOWLEVEL] [PDO_ID_LOWLEVEL_ELEC_ANGLE],	    			UINT16_T,  		1);
	Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_LOWLEVEL] [PDO_ID_LOWLEVEL_PRBS_DATA],	    			FLOAT32_T, 		2);
	Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_LOWLEVEL] [PDO_ID_LOWLEVEL_RAW_CURRENT],	    			INT32_T,  		3);
	Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_LOWLEVEL] [PDO_ID_LOWLEVEL_KF_CURRENT],	    			FLOAT32_T, 		3);

	Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_LOWLEVEL] [PDO_ID_LOWLEVEL_TOTAL_CURRENT_INPUT],			FLOAT32_T, 		1);
	Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_LOWLEVEL] [PDO_ID_LOWLEVEL_CURRENT_OUTPUT],  			FLOAT32_T,  	1);

	Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_LOWLEVEL] [PDO_ID_LOWLEVEL_AUXILIARY_INPUT],  			FLOAT32_T,  	1);
	Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_LOWLEVEL] [PDO_ID_LOWLEVEL_LOW_ID_PROCESS_INPUT],		FLOAT32_T, 		1);
	Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_LOWLEVEL] [PDO_ID_LOWLEVEL_FRICTION_COMPENSATOR_INPUT],  FLOAT32_T,  	1);
	Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_LOWLEVEL] [PDO_ID_LOWLEVEL_MID_ID_PROCESS_INPUT],		FLOAT32_T, 		1);
	Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_LOWLEVEL] [PDO_ID_LOWLEVEL_IRC_INPUT],					FLOAT32_T, 		1);
	Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_LOWLEVEL] [PDO_ID_LOWLEVEL_MID_CTRL_INPUT],  			FLOAT32_T,  	1);
	Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_LOWLEVEL] [PDO_ID_LOWLEVEL_ANALYZER_INPUT],				FLOAT32_T, 		1);
	Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_LOWLEVEL] [PDO_ID_LOWLEVEL_COMMUTATION_STEP],			UINT8_T, 		1);


	/*Joint Task*/
	Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_MIDLEVEL] [PDO_ID_MIDLEVEL_LOOP_CNT],			UINT32_T, 		1);
	Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_MIDLEVEL] [PDO_ID_MIDLEVEL_REF_POSITION],  		FLOAT32_T,  	1);
	Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_MIDLEVEL] [PDO_ID_MIDLEVEL_REF_VELOCITY],  		FLOAT32_T,  	1);
	Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_MIDLEVEL] [PDO_ID_MIDLEVEL_ACTUAL_POSITION], 	FLOAT32_T, 		1);
	Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_MIDLEVEL] [PDO_ID_MIDLEVEL_ACTUAL_VELOCITY_RAW], FLOAT32_T,  	1);
	Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_MIDLEVEL] [PDO_ID_MIDLEVEL_SYSTEM_ID_SBS_FREQ],	FLOAT32_T, 		1);

	Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_MIDLEVEL] [PDO_ID_MIDLEVEL_IMP_INPUT], 					FLOAT32_T,  	1);
	Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_MIDLEVEL] [PDO_ID_MIDLEVEL_POS_PID_CTRL_INPUT], 			FLOAT32_T,  	1);
	Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_MIDLEVEL] [PDO_ID_MIDLEVEL_VEL_PID_CTRL_INPUT],			FLOAT32_T, 		1);
	Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_MIDLEVEL] [PDO_ID_MIDLEVEL_VSD_INPUT],					FLOAT32_T, 		1);
	Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_MIDLEVEL] [PDO_ID_MIDLEVEL_UNIT_TRAJECTORY_BUFF_COUNT],	FLOAT32_T, 		1);
	Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_MIDLEVEL] [PDO_ID_MIDLEVEL_TORQUE_TRAJECTORY_INPUT],		FLOAT32_T, 		1);
	Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_MIDLEVEL] [PDO_ID_MIDLEVEL_ABS_POSITION],				FLOAT32_T, 		1);
	Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_MIDLEVEL] [PDO_ID_MIDLEVEL_DOB_DISTURABNCE],				FLOAT32_T, 		1);
	Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_MIDLEVEL] [PDO_ID_MIDLEVEL_DOB_INPUT],					FLOAT32_T, 		1);
	Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_MIDLEVEL] [PDO_ID_MIDLEVEL_FF_INPUT],					FLOAT32_T, 		1);
	Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_MIDLEVEL] [PDO_ID_MIDLEVEL_VELOCITY_ESTIMATED],			FLOAT32_T, 		1);



	/*COMM Task*/
	 Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_MSG] [PDO_ID_MSG_TEST1],  			INT32_T,  	1);
	 Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_MSG] [PDO_ID_MSG_TEST2],  			INT32_T,  	1);
	 Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_MSG] [PDO_ID_MSG_TEST3],  			INT32_T,  	1);
	 Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_MSG] [PDO_ID_MSG_TEST4],  			INT32_T,  	1);
	 Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_MSG] [PDO_ID_MSG_TEST5],  			INT32_T,  	1);
	 Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_MSG] [PDO_ID_MSG_TEST6],  			INT32_T,  	1);
	 Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_MSG] [PDO_ID_MSG_TEST7],  			INT32_T,  	1);
	 Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_MSG] [PDO_ID_MSG_TEST8],  			INT32_T,  	1);
	 Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_MSG] [PDO_ID_MSG_TEST9],  			INT32_T,  	1);
	 Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_MSG] [PDO_ID_MSG_TEST10],  			INT32_T,  	1);

	/*IMU Task*/
	 Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_IMU] [PDO_ID_IMU_ACC_X],  			FLOAT32_T,  	1);
	 Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_IMU] [PDO_ID_IMU_ACC_Y],  			FLOAT32_T,  	1);
	 Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_IMU] [PDO_ID_IMU_ACC_Z],  			FLOAT32_T,  	1);
	 Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_IMU] [PDO_ID_IMU_GYR_X],  			FLOAT32_T,  	1);
	 Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_IMU] [PDO_ID_IMU_GYR_Y],  			FLOAT32_T,  	1);
	 Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_IMU] [PDO_ID_IMU_GYR_Z],  			FLOAT32_T,  	1);
	 Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_IMU] [PDO_ID_IMU_WALKING_STATE],  	FLOAT32_T,  	1);
	 Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_IMU] [PDO_ID_IMU_GAIT_PHASE],  		FLOAT32_T,  	1);
	 Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_IMU] [PDO_ID_IMU_MAG_X],  			FLOAT32_T,  	1);
	 Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_IMU] [PDO_ID_IMU_MAG_Y],  			FLOAT32_T,  	1);
	 Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_IMU] [PDO_ID_IMU_MAG_Z],  			FLOAT32_T,  	1);
	 Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_IMU] [PDO_ID_IMU_TENSION_P],  		FLOAT32_T,  	1);
	 Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_IMU] [PDO_ID_IMU_TENSION_D],  		FLOAT32_T,  	1);
	 Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_IMU] [PDO_ID_IMU_DEG_ACC],  		FLOAT32_T,  	1);
	 Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_IMU] [PDO_ID_IMU_DEG_GYR],  		FLOAT32_T,  	1);
	 Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_IMU] [PDO_ID_IMU_DEG_ACC_FILTERED], FLOAT32_T,  	1);
	 Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_IMU] [PDO_ID_IMU_DEG_GYR_FILTERED], FLOAT32_T,  	1);
	 Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_IMU] [PDO_ID_DEG_TVCF],  			FLOAT32_T,  	1);


	/*SYSMNGT Task*/
	 Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_SYSMNGT] [PDO_ID_SYSTEM_VOLT],  			FLOAT32_T,  	1);
	 Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_SYSMNGT] [PDO_ID_SYSTEM_CURR],  			FLOAT32_T,  	1);
	 Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_SYSMNGT] [PDO_ID_SYSTEM_TEMP],  			FLOAT32_T,  	1);

	/*EXTDEV Task*/
	 Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_EXTDEV] [PDO_ID_EXTDEV_FSR],  				FLOAT32_T,  	1);
	 Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_EXTDEV] [PDO_ID_EXTDEV_LP],  				FLOAT32_T,  	1);
	 Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_EXTDEV] [PDO_ID_EXTDEV_DC_LENGTH_REF],  	FLOAT32_T,  	1);
	 Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_EXTDEV] [PDO_ID_EXTDEV_DC_DIRECTION_CMD],  	UINT8_T,  		1);
	 Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_EXTDEV] [PDO_ID_EXTDEV_DC_LENGTH_ACT],  	FLOAT32_T,  	1);
	 Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_EXTDEV] [PDO_ID_EXTDEV_DC_DIRECTION_ACT],  	UINT8_T,  		1);
	 Assemble_PDO( (PDOinfo*)PDO_Table [TASK_ID_EXTDEV] [PDO_ID_EXTDEV_DC_BUTTON_STATE],  	UINT8_T,  		1);
}



