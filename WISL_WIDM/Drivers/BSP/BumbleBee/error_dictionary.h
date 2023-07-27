/*
 * error_dictionary.h
 *
 *  Created on: Oct 27, 2022
 *      Author: mingoo
 */

#ifndef ERROR_DICTIONARY_H_
#define ERROR_DICTIONARY_H_

#define NO_ERROR						0x0000

/* FDCAN COMMUNICATION ERROR */
#define SDO_RX_ERR						0x0001
#define SDO_TX_ERR						0x0002
#define PDO_RX_ERR						0x0003
#define SYNC_RX_ERR						0x0004	

// /* LOW LEVEL CONTROL ERROR */
// #define LOW_LEVEL_CTRL_HAL_FUNC_ERROR   0x1100
// #define PHASE_OVER_CURR		            0x1101
// #define PHASE_OVER_VOLT		            0x1102
// #define CURR_INIT_VALUE_ERROR		    0x1103
// #define MOTOR_ALIGNED_ERROR		        0x1104
// #define HALL_PATTERN_ERROR		        0x1105
// #define INC_ENC_25KHZ_ERROR		        0x1106
// #define INC_STACKING_25KHZ_ERROR        0x1107
// #define PEAK_CURR_ERROR		            0x1108
// #define CONT_CURR_ERROR		            0x1109
// #define LOW_LEVEL_CTRL_PARAMETER_ERROR	0x1110
// #define LOW_LEVEL_CTRL_RT_BROKEN	    0x1111

// /* MID LEVEL CONTROL ERROR */
// #define MID_LEVEL_CTRL_HAL_FUNC_ERROR	0x1200	
// #define INC_ENC_1KHZ_ERROR		        0x1201
// #define INC_ENC_STACKING_1KHZ_ERROR     0x1202
// #define ABS_ENC_ERROR		            0x1203
// #define ABS_ENC_STACKING_ERROR		    0x1204
// #define POS_LIMIT_ERROR		            0x1205
// #define VEL_LIMIT_ERROR		            0x1206
// #define POS_CTRL_ERROR		            0x1207
// #define VEL_CTRL_ERROR		            0x1208
// #define TENSIONAL_VSD_ERROR		        0x1209
// #define COMPRESSIONAL_VSD_ERROR		    0x1210
// #define MID_LEVEL_CTRL_PARAMETER_ERROR	0x1211
// #define MID_LEVEL_CTRL_RT_BROKEN	    0x1212

/* FDCAN COMMUNICATION ERROR */
#define MSG_HDLR_HAL_FUNC_ERROR         0x1301
#define SDO_RX_ERROR                    0x1300
#define SDO_TX_ERROR                    0x1302
#define PDO_RX_ERROR                    0x1303
#define PDO_TX_ERROR                    0x1304
#define MSG_TX_ERROR                    0x1305
#define CANNOT_FIND_SDO_ERROR           0x1306
#define SDO_ARGUMENT_ERROR              0x1307
#define SDO_STATUS_ERROR                0x1308
#define UNPACK_SDO_ERROR                0x1309
#define PACK_RES_SDO_ERROR              0x1310
#define PACK_REQ_SDO_ERROR              0x1311
#define SDO_SEND_ERROR                  0x1312
#define TX_MSG_LONG_ERROR               0x1313
#define CANNOT_FIND_PDO_ERROR           0x1314
#define COPY_PDO_TO_RECEIVE_ERROR       0x1315
#define UNPACK_PDO_ERROR                0x1316
#define COPY_PDO_TO_SEND_ERROR          0x1317
#define PACK_PDO_ERROR                  0x1318
#define PDO_SEND_ERROR                  0x1319
#define MSG_HDLR_RT_BROKEN              0x1320

// /* EXTERNAL DEVICE CONTROL ERROR */
// #define EXT_DEV_CTRL_HAL_FUNC_ERROR		0x1400
// #define MOTOR_OVER_TEMPERATURE		    0x1401
// #define LINEAR_POT_ADC_ERROR		    0x1402
// #define FSR_ADC_ERROR		            0x1403
// #define LENGTH_ADC_ERROR		        0x1404
// #define DC_MOTOR_CTRL_ERROR		        0x1405
// #define EXT_DEV_CTRL_RT_BROKEN		    0x1406

/* IMU CONTROL ERROR */
#define IMU_HDLR_HAL_FUNC_ERROR		    0x1500
#define ACCEL_ERROR		                0x1501
#define GYRO_ERROR		                0x1502
#define MAG_ERROR		                0x1503
#define FUZZY_LOGIC_ERROR		        0x1504
#define GAIT_PATTERN_ERROR		        0x1505
#define IMU_CTRL_RT_BROKEN		        0x1506

// /* SYSTEM MANAGEMENT ERROR */
// #define SYS_MNGT_HAL_FUNC_ERROR		    0x1600
// #define BOARD_OVER_CURR		            0x1601
// #define BOARD_OVER_VOLT		            0x1602
// #define BOARD_OVER_TEMP		            0x1603
// #define BOARD_UNDER_VOLT                0x1604
// #define BOOT_SEQUENCE_ERROR		        0x1605
// #define SYS_MNGT_RT_BROKEN		        0x1606

uint32_t Msg_Hdlr_Error_Type;
uint32_t Imu_Ctrl_Error_Type;

#endif /* ERROR_DICTIONARY_H_ */
