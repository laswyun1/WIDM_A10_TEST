/*
 * ioif_fdcan.c
 *
 *  Created on: 2022. 7. 26.
 *      Author: mingoo
 */

#include "ioif_fdcan.h"

RecieveCallback fdcan_rx_callback_ptr = NULL;

FdcanObjectStruct fdcan1_obj;
FdcanObjectStruct fdcan2_obj;

uint8_t RxData1[64];
uint8_t RxData2[64];

void Init_IOIF_Fdcan(uint32_t t_Mask, uint32_t t_FilterID1, uint32_t t_FilterID2)
{
	fdcan1_obj.hfdcan = &hfdcan1;
	fdcan1_obj.mask_window = t_Mask;
	fdcan1_obj.filter1 = t_FilterID1;
	fdcan1_obj.filter2 = t_FilterID2;

	fdcan1_obj.sFilterConfig.IdType = FDCAN_STANDARD_ID;
	fdcan1_obj.sFilterConfig.FilterIndex = 0;
	fdcan1_obj.sFilterConfig.FilterType = FDCAN_FILTER_RANGE; //FDCAN_FILTER_RANGE;
	fdcan1_obj.sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
	fdcan1_obj.sFilterConfig.FilterID1 = 0x000;	// Filter ID1
	fdcan1_obj.sFilterConfig.FilterID2 = 0x7FF;	// Filter ID2

	fdcan1_obj.TxHeader.IdType = FDCAN_STANDARD_ID;
	fdcan1_obj.TxHeader.TxFrameType = FDCAN_DATA_FRAME;
	fdcan1_obj.TxHeader.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
	fdcan1_obj.TxHeader.BitRateSwitch = FDCAN_BRS_ON;
	fdcan1_obj.TxHeader.FDFormat = FDCAN_FD_CAN;
	fdcan1_obj.TxHeader.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
	fdcan1_obj.TxHeader.MessageMarker = 0;
 
	/* Fault Check */
	if ( HAL_FDCAN_ConfigGlobalFilter ( fdcan1_obj.hfdcan, FDCAN_REJECT, FDCAN_REJECT, FDCAN_FILTER_REMOTE, FDCAN_FILTER_REMOTE ) != HAL_OK ){
		Error_Handler ( );  // Configure Filter
	}

	if ( HAL_FDCAN_ConfigFilter ( fdcan1_obj.hfdcan, &fdcan1_obj.sFilterConfig ) != HAL_OK ){
		Error_Handler ( );  // Configure Filter
	}

	if ( HAL_FDCAN_ActivateNotification ( fdcan1_obj.hfdcan, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0 ) != HAL_OK ) {
		Error_Handler ( );
	}

	if ( HAL_FDCAN_ConfigTxDelayCompensation ( fdcan1_obj.hfdcan, fdcan1_obj.hfdcan->Init.DataPrescaler * fdcan1_obj.hfdcan->Init.DataTimeSeg1, 0 ) != HAL_OK ) {
		Error_Handler ( );
	}

	if ( HAL_FDCAN_EnableTxDelayCompensation ( fdcan1_obj.hfdcan ) != HAL_OK ) {
		Error_Handler ( );
	}

	if ( HAL_FDCAN_Start ( fdcan1_obj.hfdcan ) != HAL_OK ) {
		Error_Handler ( );
	}
}

int Transmit_IOIF_Fdcan(uint16_t t_COB_ID, uint32_t t_len, uint8_t* t_tx_data)
{
	fdcan1_obj.TxHeader.Identifier = t_COB_ID;
	fdcan1_obj.TxHeader.DataLength = t_len; //FDCAN_DLC_BYTES_64 //FDCAN_DLC_BYTES_32 //FDCAN_DLC_BYTES_20

	return HAL_FDCAN_AddMessageToTxFifoQ(fdcan1_obj.hfdcan, &fdcan1_obj.TxHeader, t_tx_data);
}


void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
{
	/* Recieve Message */
	if (hfdcan->Instance == FDCAN1){
		if (HAL_FDCAN_GetRxMessage(fdcan1_obj.hfdcan, FDCAN_RX_FIFO0, &fdcan1_obj.RxHeader, RxData1) != HAL_OK) {
			Error_Handler();
		}
		
		if (((fdcan1_obj.RxHeader.Identifier & fdcan1_obj.mask_window) != fdcan1_obj.filter1) && \
			((fdcan1_obj.RxHeader.Identifier & fdcan1_obj.mask_window) != fdcan1_obj.filter2)){
			return;
		}

		if (fdcan_rx_callback_ptr != NULL) {
			fdcan_rx_callback_ptr(fdcan1_obj.RxHeader.Identifier, RxData1);
		}
	}
}
