/*
 * fdcan_hdlr.h
 *
 *  Created on: Aug 2, 2022
 *      Author: User
 */

#ifndef FRAMEWORK_APPS_FDCAN_MSG_HDLR_MSG_HDLR_H_
#define FRAMEWORK_APPS_FDCAN_MSG_HDLR_MSG_HDLR_H_

#include "task.h"
#include "cvector.h"
#include "ioif_fdcan.h"
#include "ioif_tim.h"
#include "ioif_gpio.h"
#include "error_dictionary.h"
//#include "usbd_cdc_if.h"
//#include "ioif_usb.h"
#include "msg_common.h"
#include "BumbleBee.h"


#define FDCAN_DLC_BYTES_0  ((uint32_t)0x00000000U) /*!< 0 bytes data field  */
#define FDCAN_DLC_BYTES_1  ((uint32_t)0x00010000U) /*!< 1 bytes data field  */
#define FDCAN_DLC_BYTES_2  ((uint32_t)0x00020000U) /*!< 2 bytes data field  */
#define FDCAN_DLC_BYTES_3  ((uint32_t)0x00030000U) /*!< 3 bytes data field  */
#define FDCAN_DLC_BYTES_4  ((uint32_t)0x00040000U) /*!< 4 bytes data field  */
#define FDCAN_DLC_BYTES_5  ((uint32_t)0x00050000U) /*!< 5 bytes data field  */
#define FDCAN_DLC_BYTES_6  ((uint32_t)0x00060000U) /*!< 6 bytes data field  */
#define FDCAN_DLC_BYTES_7  ((uint32_t)0x00070000U) /*!< 7 bytes data field  */
#define FDCAN_DLC_BYTES_8  ((uint32_t)0x00080000U) /*!< 8 bytes data field  */
#define FDCAN_DLC_BYTES_12 ((uint32_t)0x00090000U) /*!< 12 bytes data field */
#define FDCAN_DLC_BYTES_16 ((uint32_t)0x000A0000U) /*!< 16 bytes data field */
#define FDCAN_DLC_BYTES_20 ((uint32_t)0x000B0000U) /*!< 20 bytes data field */
#define FDCAN_DLC_BYTES_24 ((uint32_t)0x000C0000U) /*!< 24 bytes data field */
#define FDCAN_DLC_BYTES_32 ((uint32_t)0x000D0000U) /*!< 32 bytes data field */
#define FDCAN_DLC_BYTES_48 ((uint32_t)0x000E0000U) /*!< 48 bytes data field */
#define FDCAN_DLC_BYTES_64 ((uint32_t)0x000F0000U) /*!< 64 bytes data field */

extern uint32_t Msg_Hdlr_Error_Type;

typedef enum{

	FIRST_USE = 0x01,
	SECOND_USE,
	MEMORY_UI_MOTOR_PROPERTIES,
	MEMORY_UI_ELECTRICAL_PROPERTIES,
	MEMORY_UI_MECHANICAL_PROPERTIES,
	MEMORY_UI_CONTROL_PARAMETERS,
	MEMORY_UI_ADDITIONAL_FUNCTION_PARAMETERS,

	E_SYS_BATCH,
	E_SYS_BEMF,
	BEMF_ID_OVER_CURRENT,
	BW_CHECK,
	FRICTION_ID_RAW_DATA,
	FRICTION_ID_AVERAGED_DATA,
	FRICTION_ID_DONE,
	FRICTION_COMPENSATOR_VERIFICATION,

	MECH_SYS_ID_SBS_RAW_DATA,
	MECH_SYS_ID_SBS_DONE,

	IRC_VERIFICATION,

	GET_IMPEDANCE_SINE_CTRL,
	GET_IMPEDANCE_REC_CTRL,

	GAIN_TUNER,
	GET_VELOCITY_CTRL,
	GET_POSITION_CTRL,

	GET_INCENCODER,
	GET_ABSENCODER,

	GET_VSD_UPPER_LIMIT,
	GET_VSD_LOWER_LIMIT,

	VSD_VERIFICATION_DATA,

	GET_BACKLASH_TEST,
	GET_DOB_DATA,

	GET_DIRECTION_SET_DATA,
	GET_DIRECTION_SET_DONE,

	SAVE_DONE,
	GET_VE_TEST_DATA,
	GET_SYSTEM_ID_VERIFY,
	VE_KF_SETTING_ERROR,
	GET_FF_CTRL,
	GET_TOTAL_CTRL,

	ADV_FRICTION_ID_DATA,
	ADV_FRICTION_ID_DONE,

} GUISequence_Enum;


#define MEMORY_SECOND_HAND_CHECK	1

typedef enum{

	IDLE,
	UPLOAD_PROPERTIES,
	SAVE_PROPERTIES,
	DOWNLOAD_PROPERTIES,
	ELECTRICAL_SYSTEM_ID,
	BEMF_ID,
	CURRENT_BANDWIDTH_CHECK,
	AUTO_TUNING,
	ADV_FRICTION_ID,
	CAL_FRICTION_LUT,

} MainSequence_Enum;



typedef enum _COMMType{
	e_FDCAN = 0U,
	e_USB
}COMMType;

extern RecieveCallback fdcan_rx_callback_ptr;
//extern USBCallback ioif_usb_rx_callback_ptr;
extern TimCallback ioif_tim6_callback_ptr;
extern TaskStruct msg_hdlr_task;
extern TaskStruct mid_level_ctrl_task;
extern MainSequence_Enum MS_enum;

void Send_EMCY(uint32_t* f_err_code);
int Send_MSG(uint16_t COB_ID, uint32_t len, uint8_t* tx_data);
void Init_Msg_Hdlr();
void Run_Msg_Hdlr();

#endif /* FRAMEWORK_APPS_FDCAN_MSG_HDLR_MSG_HDLR_H_ */
