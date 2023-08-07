/*
 * ioif_fdcan.h
 *
 *  Created on: 2022. 7. 26.
 *      Author: mingoo
 */

#ifndef DRIVERS_IOIF_INC_IOIF_FDCAN_H_
#define DRIVERS_IOIF_INC_IOIF_FDCAN_H_

#include "fdcan.h"
#include "main.h"
#include "ioif_tim.h"

#include <stdint.h>

typedef int (*RecieveCallback) (uint16_t, uint8_t*);

extern RecieveCallback fdcan_rx_callback_ptr;

typedef struct _FdcanObjectStruct{
    
    FDCAN_HandleTypeDef *hfdcan;
    FDCAN_FilterTypeDef sFilterConfig;
    FDCAN_TxHeaderTypeDef TxHeader;
	FDCAN_RxHeaderTypeDef RxHeader;

    uint32_t mask_window;
    uint32_t filter1;
    uint32_t filter2;

} FdcanObjectStruct;

extern FDCAN_HandleTypeDef hfdcan1;
extern FDCAN_HandleTypeDef hfdcan2;


void Init_IOIF_Fdcan(uint32_t t_Mask, uint32_t t_FilterID1, uint32_t t_FilterID2);
int Transmit_IOIF_Fdcan(uint16_t t_COB_ID, uint32_t t_len, uint8_t* t_tx_data);

#endif /* DRIVERS_IOIF_INC_IOIF_FDCAN_H_ */
