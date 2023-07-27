/*
 * fdcan_ctrl.c
 *
 *  Created on: Jul 27, 2022
 *      Author: mingoo
 */


#include "msg_hdlr_task.h"

extern volatile Semaphore s_position_ref;

int32_t test_dummy[10];

/* --------------------------- */
//static int Read_Node_ID()
//{
//    int temp1, temp2, temp3, temp4;
//
//    temp1 = Get_GPIO_A_State(GPIO_PIN_0);
//    temp2 = Get_GPIO_A_State(GPIO_PIN_1);
//    temp3 = Get_GPIO_A_State(GPIO_PIN_2);
//    temp4 = Get_GPIO_A_State(GPIO_PIN_3);
//
//    return ((temp1<<3)|(temp2<<2)|(temp3<<1)|(temp4));
//}

static int Convert_Byte_Length(uint8_t t_length)
{
    if(t_length == 0 )                       		{return FDCAN_DLC_BYTES_0; }
    else if(t_length == 1 )                  		{return FDCAN_DLC_BYTES_1; }
    else if(t_length == 2 )                  		{return FDCAN_DLC_BYTES_2; }
    else if(t_length == 3 )                  		{return FDCAN_DLC_BYTES_3; }
    else if(t_length == 4 )                  		{return FDCAN_DLC_BYTES_4; }
    else if(t_length == 5 )                  		{return FDCAN_DLC_BYTES_5; }
    else if(t_length == 6 )                  		{return FDCAN_DLC_BYTES_6; }
    else if(t_length == 7 )                  		{return FDCAN_DLC_BYTES_7; }
    else if(t_length == 8 )                  		{return FDCAN_DLC_BYTES_8; }
    else if((t_length > 8 ) && (t_length <= 12 )) 	{return FDCAN_DLC_BYTES_12; }
    else if((t_length > 12 ) && (t_length <= 16 ))	{return FDCAN_DLC_BYTES_16; }
    else if((t_length > 16 ) && (t_length <= 20 ))	{return FDCAN_DLC_BYTES_20; }
    else if((t_length > 20 ) && (t_length <= 24 ))	{return FDCAN_DLC_BYTES_24; }
    else if((t_length > 24 ) && (t_length <= 32 ))	{return FDCAN_DLC_BYTES_32; }
    else if((t_length > 32 ) && (t_length <= 48 ))	{return FDCAN_DLC_BYTES_48; }
    else if((t_length > 48 ) && (t_length <= 64 ))	{return FDCAN_DLC_BYTES_64; }
    else                                			{return FDCAN_DLC_BYTES_0; }
}

static MsgDataObjectHeader Get_Header(uint8_t* t_byte_arr)
{
	MsgDataObjectHeader t_header;
    memcpy(&t_header, t_byte_arr, sizeof(MsgDataObjectHeader));
    return t_header;
}

/*
  ___ __  __  _____   __
 | __|  \/  |/ __\ \ / /
 | _|| |\/| | (__ \ V / 
 |___|_|  |_|\___| |_|  
                        
*/

void Send_EMCY(uint32_t* t_err_code)
{
    uint8_t* t_tx_data = malloc(sizeof(uint8_t)*4);
    uint16_t t_identifier = EMCY|(node_id<<4);

    memcpy(t_tx_data, t_err_code, ERR_CODE_SIZE);

    if(Send_MSG(t_identifier, 4, t_tx_data) != 0){
        //TODO: MSG TX ERROR
    }

    free(t_tx_data);
    t_tx_data = NULL;
}

static void Recv_EMCY(uint8_t* t_byte_arr, uint32_t* t_err_code)
{
    memcpy(t_err_code, t_byte_arr, ERR_CODE_SIZE);
}

/*
  ___ ___   ___    ___ __  __
 / __|   \ / _ \  | _ \\ \/ /
 \__ \ |) | (_) | |   / >  < 
 |___/___/ \___/  |_|_\/_/\_\
                             
*/

static MsgSDOargs Convert_Bytes_to_SDO_req(uint8_t* t_byte_arr, uint16_t *t_byte_len)
{
	MsgSDOargs t_req;
    *t_byte_len = 0;

    int t_idx = sizeof(t_req.status);
    int t_len = sizeof(t_req.size);

    memcpy(&t_req.size, &t_byte_arr[t_idx], t_len);
    *t_byte_len += t_len;

    t_req.data = &t_byte_arr[t_idx + t_len];

    t_req.status = t_byte_arr[0];
    *t_byte_len += 1;

    return t_req;
}

static int Read_SDO(uint8_t* t_byte_arr)
{
    int t_byte_read = 0;
    MsgDataObjectHeader t_header = Get_Header(t_byte_arr);
    t_byte_read += sizeof(MsgDataObjectHeader);

    MsgSDOStruct* t_sdo = Find_SDO(t_header.dod_id, t_header.obj_id);
    if (t_sdo == NULL) {
        //TODO: Cannot Find SDO ERROR
        return -2;
    }

    uint16_t t_req_bytes = 0;
    MsgSDOargs t_req = Convert_Bytes_to_SDO_req(t_byte_arr + t_byte_read, &t_req_bytes);
    t_req.data_size = t_sdo->args.data_size; // Copy SDO info
    t_byte_read += t_req_bytes;

    uint16_t t_n_bytes = 0;
    if (t_req.status == DATA_OBJECT_SDO_REQU) {
    	t_n_bytes = Call_SDO(t_sdo, &t_req);
        cvector_push_back(sdo_res_list, t_header); // Assign Response
    } else if(t_req.status == DATA_OBJECT_SDO_SUCC || t_req.status == DATA_OBJECT_SDO_FAIL) {
    	t_n_bytes = Set_SDO_args(t_sdo, &t_req);
        if (t_n_bytes < 0) {
            //TODO: Set SDO Argument ERROR
            return -1;
        }
    } else {
        //TODO: Read SDO Status ERROR
        return -1;
    }

    t_byte_read += t_n_bytes;
    return t_byte_read;
}

static int Unpack_SDO(uint8_t* t_byte_arr)
{
    int t_cursor = 0;

    // Get # of SDOs
    uint16_t t_n_sdo = 0;
    memcpy(&t_n_sdo, &t_byte_arr[t_cursor], OBJ_NUMS_SIZE);
    t_cursor += OBJ_NUMS_SIZE;

    // Call & Respond SDOs
    if (t_n_sdo > 0) {
        for (int i = 0; i < t_n_sdo; ++i) {
            int temp_cursor = Read_SDO(&t_byte_arr[t_cursor]);
            if (temp_cursor > 0) {
            	t_cursor += temp_cursor;
            } else if (temp_cursor < 0) {
                //TODO: Unpack SDO ERROR
                return MSG_SDO_FAULT;
            }
        }
    }

    return MSG_DO_SUCCESS;
}

/*
  ___ ___   ___    _______  __
 / __|   \ / _ \  |_   _\ \/ /
 \__ \ |) | (_) |   | |  >  < 
 |___/___/ \___/    |_| /_/\_\
                              
*/

static int Convert_SDOres_to_Bytes(MsgDataObjectHeader* t_header, uint8_t* t_byte_arr)
{
    int t_byte_written = 0;
    // Set SDO Header
    memcpy(t_byte_arr, t_header, sizeof(MsgDataObjectHeader));
    t_byte_written += sizeof(MsgDataObjectHeader);

    // Return Response
    MsgSDOStruct* t_sdo = Find_SDO(t_header->dod_id, t_header->obj_id);
    if (t_sdo == NULL) {
        //TODO: Cannot Find SDO ERROR
        return -2;
    }

    memcpy(t_byte_arr + t_byte_written, &t_sdo->args.status, sizeof(t_sdo->args.status));
    t_byte_written += sizeof(t_sdo->args.status);
    memcpy(t_byte_arr + t_byte_written, &t_sdo->args.size,   sizeof(t_sdo->args.size));
    t_byte_written += sizeof(t_sdo->args.size);

    int t_data_len = t_sdo->args.size * t_sdo->args.data_size;
    memcpy(t_byte_arr + t_byte_written, t_sdo->args.data, t_data_len);

    t_byte_written += t_data_len;

    return t_byte_written;
}

static int Pack_SDO(uint8_t* t_byte_arr, uint8_t* t_byte_len)
{
	// check send list whether these are empty or not 
	if ((sdo_res_list == NULL) && (sdo_req_list == NULL)){
		return MSG_SDO_NOTHING;
	}

	// Message Packaging
    int t_cursor = 0;

    // Res SDOs
    int t_n_sdo_cursor = t_cursor;
    t_cursor += OBJ_NUMS_SIZE;

    uint8_t t_n_sdo = 0;
    
    if (sdo_res_list != NULL) {
        for(int i = 0; i < cvector_size(sdo_res_list); ++i) {
            int temp_cursor = Convert_SDOres_to_Bytes(&sdo_res_list[i], &t_byte_arr[t_cursor]);
            if (temp_cursor > 0) {
            	t_cursor += temp_cursor;
                ++t_n_sdo;
            } else if (temp_cursor < 0) {
                //TODO: Pack Response SDO Error
                return MSG_SDO_FAULT;
            }
        }
        cvector_free(sdo_res_list);
        sdo_res_list = NULL;
    }

    // Req SDOs
    if (sdo_req_list != NULL) {
        for(int i = 0; i < cvector_size(sdo_req_list); ++i) {
            int temp_cursor = Convert_SDOres_to_Bytes(&sdo_req_list[i], &t_byte_arr[t_cursor]);
            if (temp_cursor > 0) {
            	t_cursor += temp_cursor;
                ++t_n_sdo;
            } else if (temp_cursor < 0) {
                //TODO: Pack Request SDO Error
                return MSG_SDO_FAULT;
            }
        }
        cvector_free(sdo_req_list);
        sdo_req_list = NULL;
    }

    // Set # of SDOs
    memcpy(&t_byte_arr[t_n_sdo_cursor], &t_n_sdo, OBJ_NUMS_SIZE);

    *t_byte_len = t_cursor;

    return MSG_DO_SUCCESS;
}

static int Send_SDO(uint8_t t_dest_node)
{
    uint8_t t_byte_len;
    uint16_t t_identifier = SDO|(node_id<<4)|t_dest_node;

    int t_check = Pack_SDO(fdcanRxData, &t_byte_len);

    if(t_check < 0){
        //TODO: Send SDO Error
    	return t_check;
    } else if(t_check){
    	return t_check;
    }

    if (t_byte_len > 64) {
        //TODO: TX MESSAGE TOO LONG ERROR 
    }

    if(Send_MSG(t_identifier, t_byte_len, fdcanRxData) != 0){
        return t_check;
        //TODO: MSG TX ERROR
    }

    return t_check;
}

/*
  ___ ___   ___    ___ __  __
 | _ \   \ / _ \  | _ \\ \/ /
 |  _/ |) | (_) | |   / >  < 
 |_| |___/ \___/  |_|_\/_/\_\
                             
*/

static int Convert_Bytes_to_PDO(uint8_t* t_byte_arr)
{
    int t_byte_read = 0;

    MsgDataObjectHeader t_header = Get_Header(t_byte_arr);
    t_byte_read += sizeof(MsgDataObjectHeader);

    MsgPDOStruct* t_pdo = Find_PDO(t_header.dod_id, t_header.obj_id);
    if (t_pdo == NULL) {
        //TODO: Cannot Find PDO Error
        return -2;
    }

    uint16_t t_n_bytes = Get_PDO(t_pdo, (void*)(t_byte_arr + t_byte_read));
    if (t_n_bytes < 0) {
        //TODO: Copy PDO to Receive Error
        return -1;
    }
    t_byte_read += t_n_bytes;

    return t_byte_read;
}

static int Unpack_PDO(uint8_t* t_byte_arr)
{
    int t_cursor = 0;

    // Get # of PDOs
    uint8_t t_n_pdo = 0;
    memcpy(&t_n_pdo, &t_byte_arr[t_cursor], OBJ_NUMS_SIZE);
    t_cursor += OBJ_NUMS_SIZE;

    if (t_n_pdo > 0) {
        for (int i = 0; i < t_n_pdo; ++i) {
            int temp_cursor = Convert_Bytes_to_PDO(&t_byte_arr[t_cursor]);
            if (temp_cursor > 0) {
            	t_cursor += temp_cursor;
            } else if (temp_cursor < 0) {
                //TODO: Unpack PDO Error
                return MSG_PDO_FAULT;
            }
        }
    }

    return MSG_DO_SUCCESS;
}

/*
  ___ ___   ___    _______  __
 | _ \   \ / _ \  |_   _\ \/ /
 |  _/ |) | (_) |   | |  >  < 
 |_| |___/ \___/    |_| /_/\_\
                              
*/

static int Convert_PDO_to_Bytes(MsgDataObjectHeader* t_header, uint8_t* t_byte_arr)
{
    int t_header_size = sizeof(MsgDataObjectHeader);
    // Publish PDO
    MsgPDOStruct* t_pdo = Find_PDO(t_header->dod_id, t_header->obj_id);
    if (t_pdo == NULL) {
        //TODO: Cannot Find PDO
        return -2;
    }

    uint16_t t_n_bytes = Set_PDO(t_pdo, t_byte_arr + t_header_size);
    if (t_n_bytes < 0) {
        //TODO: Copy PDO to Send 
        return -1;
    } else if (t_n_bytes == 0) { // Nothing to publish
        return 0;
    }

    memcpy(t_byte_arr, t_header, t_header_size);
    return t_header_size + t_n_bytes;
}

static int Pack_PDO(uint8_t* t_byte_arr, uint8_t* t_byte_len)
{
	// check send list whether these are empty or not 
    if (pdo_send_list == NULL){
        return 0;
    }

    int t_cursor = 0;

    // Pub PDO
    int t_n_pdo_cursor = t_cursor;
    t_cursor += OBJ_NUMS_SIZE;

    uint8_t t_n_pdo = 0;

    if (pdo_send_list != NULL) {
        for(int i = 0; i < cvector_size(pdo_send_list); ++i) {

            int temp_cursor = Convert_PDO_to_Bytes(&pdo_send_list[i], &t_byte_arr[t_cursor]);
            if (temp_cursor > 0) {
            	t_cursor += temp_cursor;
                ++t_n_pdo;
            } else if (temp_cursor < 0) {
                //TODO: Pack PDO Error
                return temp_cursor;
            }
        }
    }

    // Set # of PDOs
    memcpy(&t_byte_arr[t_n_pdo_cursor], &t_n_pdo, OBJ_NUMS_SIZE);

    *t_byte_len = t_cursor;

    return MSG_DO_SUCCESS;
}

static int Send_PDO()
{
    uint8_t t_byte_len;
    uint8_t t_dest_node = NODE_ID_RA;
    uint16_t t_identifier;

    if(GUI_onoff)	{	t_identifier = GUI_SYNC|GUI_command;	}
    else 			{	t_identifier = PDO|(node_id<<4)|t_dest_node;	}

    int t_check = Pack_PDO(fdcanTxData, &t_byte_len);

    if(t_check != 0){
        //TODO: Send PDO Error
    	return t_check;
    } else if(t_check){
    	return t_check;
    }

    if (t_byte_len != 1){
		if(Send_MSG(t_identifier, t_byte_len, fdcanTxData) == 0){
			return t_check;
			//TODO: MSG TX ERROR
		}
    }

	return t_check;
}

static int Ext_Send_PDO()
{
	if(GUI_command == GET_DIRECTION_SET_DATA){
		Send_MSG((uint16_t)(GUI_SYNC|GET_DIRECTION_SET_DONE), 1, (uint8_t*)0);
	}

	return 0;
}

static int Set_PDO_Dummy()
{
	static int t_count = 0;

	test_dummy[0] = comm_loop_cnt;
	test_dummy[1] = comm_loop_cnt;
	test_dummy[2] = comm_loop_cnt;
	test_dummy[3] = comm_loop_cnt;
	test_dummy[4] = comm_loop_cnt;
	test_dummy[5] = comm_loop_cnt;
	test_dummy[6] = comm_loop_cnt;
	test_dummy[7] = comm_loop_cnt;
	test_dummy[8] = comm_loop_cnt;
	test_dummy[9] = comm_loop_cnt;

	t_count++;

	return 0;
}

static int Check_Trajectory_Error(uint16_t t_frame_idx)
{
	if((t_frame_idx % D10_TRAJECTORY_ELEMENT_NUMBER) != 0)		{return -1;}
	if( (t_frame_idx - trajectory_buffer.frame_idx) != 0)		{return -2;}

	trajectory_buffer.frame_idx += D10_TRAJECTORY_ELEMENT_NUMBER;

	return 0;
}

static int Assemble_Trajectory(uint8_t* t_byte_arr)
{
	uint8_t t_cursor, t_check, t_buf;
	uint16_t t_index;
	int8_t t_ack;
    uint16_t t_identifier = TRAJECTORY|(node_id<<4)|NODE_ID_CM;

	/* Get index */
	t_cursor = 0;
	memcpy(&t_index, &t_byte_arr[t_cursor], 2);
	t_cursor += 2;

	/* Check Error*/
	t_check = Check_Trajectory_Error(t_index);

	if(t_check != 0) {
		trajectory_buffer.frame_idx = 0;
		t_ack = -2;
	} else {

		/* Save Buffer */
		for(int i = 0; i < D10_TRAJECTORY_ELEMENT_NUMBER; ++i){
			memcpy(&trajectory_buffer.buff[t_index++], &t_byte_arr[t_cursor], 4);
			t_cursor += 4;
		}

		/* Check End of Trajectory */
		if(t_index >= D10_TRAJECTORY_TOTAL_LENGTH){
			t_ack = -1;
			trajectory_buffer.frame_idx = 0;
		} else {
			t_ack = 0;
		}
	}

	/* Send Acknowledgement */
	memcpy(&t_buf, &t_ack, 1);
	Send_MSG(t_identifier, 1, &t_buf);

	return t_check;
}

/*
  _    _    _     __  __                                       _   
 | |  (_)__| |_  |  \/  |__ _ _ _  __ _ __ _ ___ _ __  ___ _ _| |_ 
 | |__| (_-<  _| | |\/| / _` | ' \/ _` / _` / -_) '  \/ -_) ' \  _|
 |____|_/__/\__| |_|  |_\__,_|_||_\__,_\__, \___|_|_|_\___|_||_\__|
                                       |___/                       
*/


static void Add_PDO_to_Send(uint8_t t_dod_id, uint8_t t_obj_id)
{
	MsgPDOStruct* temp_pdo = Find_PDO(t_dod_id, t_obj_id);
    if (temp_pdo == NULL) {
        //TODO: Cannot Find PDO Error
        return;
    }

    MsgDataObjectHeader t_pdo = {t_dod_id, t_obj_id};

    for (int i = 0; i < cvector_size(pdo_send_list); ++i) {
        if ((pdo_send_list[i].dod_id == t_dod_id) && (pdo_send_list[i].obj_id == t_obj_id)){
            return;
        }
    }
    cvector_push_back(pdo_send_list, t_pdo);
}

static void Clear_PDO_to_Send()
{
    cvector_free(pdo_send_list);
    pdo_send_list = NULL;
}


/*
  __  __                            _  _              _ _         
 |  \/  |___ ______ __ _ __ _ ___  | || |__ _ _ _  __| | |___ _ _ 
 | |\/| / -_|_-<_-</ _` / _` / -_) | __ / _` | ' \/ _` | / -_) '_|
 |_|  |_\___/__/__/\__,_\__, \___| |_||_\__,_|_||_\__,_|_\___|_|  
                        |___/                                     
*/

static void Send_USB_Trick(uint8_t* t_in_buf, uint32_t t_in_len, uint8_t* t_out_buf)
{
	/*
	 * This function is designed to prevent
	 * the continuous array of 'CR/LF' used
	 * as a terminal signal in matlab gui.
	 *
	 * Sometimes, when sending a float signal,
	 * a continuous array of 'CR/LF' is created by coincidence,
	 * which interrupts the USB communication between the GUI
	 * and MD and breaks the sequence of the GUI.
	 *
	 * Therefore, 0x00 is inserted between every byte and sent.
	 * */

	for(int i = 0; i < t_in_len; ++i){
		*(t_out_buf + (2*i)) = *(t_in_buf + i);
		*(t_out_buf + (2*i+1)) = 0;
	}
}

int Send_MSG(uint16_t t_COB_ID, uint32_t t_len, uint8_t* t_tx_data)
{
	static uint8_t t_fnc_code, t_node_id;
	int t_check = 0;
	uint8_t t_txBuf[67];
	uint8_t t_usb_txBuf[137];

	if(comm_type == e_FDCAN){
		if(Transmit_IOIF_Fdcan(t_COB_ID, Convert_Byte_Length(t_len), t_tx_data) != 0){
			return t_check;
			//TODO: MSG TX ERROR
		}
	} else if(comm_type == e_USB){

		t_fnc_code = (t_COB_ID & 0xF00) >> 8;
		t_node_id = (t_COB_ID & 0xFF);

		memcpy(&t_txBuf[2], t_tx_data, t_len);
		memcpy(t_txBuf, &t_fnc_code, 1);			t_len++;
		memcpy(&t_txBuf[1], &t_node_id, 1);			t_len++;


		Send_USB_Trick(t_txBuf, t_len, t_usb_txBuf);
		t_len *= 2;

		t_usb_txBuf[t_len++] = '\r';
		t_usb_txBuf[t_len++] = '\n';

//		if(CDC_Transmit_FS(t_usb_txBuf, t_len) != 0){
//			return t_check;
//			//TODO: MSG TX ERROR
//		}
	}

	return -1;
}

//static int USB_Rx_Hdlr(uint8_t* t_Buf, uint32_t *t_Len)
//{
//	uint32_t t_cursor = 0;
//
//	fnc_code = ((uint16_t)*t_Buf) << 8;
//	t_cursor++;
//
//	ori_node = ((*(t_Buf+t_cursor)) & 0xF0)>>4;
//	t_cursor++;
//
//	memcpy(usbRxData, &t_Buf[t_cursor], *t_Len);
//
//	switch(fnc_code){
//
//		case EMCY:
//			Recv_EMCY(usbRxData, &err_code);
//			// TODO: ERROR Process
//			break;
//
//		case SDO:
//			if (Unpack_SDO(usbRxData) < 0) {
//				return SDO_RX_ERR;
//			} else{
//				Send_SDO(ori_node);
//			}
//			break;
//
//		case PDO:
//			if (Unpack_PDO(usbRxData) < 0) {
//				return PDO_RX_ERR;
//			} else{
//				Send_PDO(ori_node);
//			}
//			break;
//
//		default: break;
//	}
//
//	return 0;
//}

static int Fdcan_Rx_Hdlr(uint16_t t_wasp_id, uint8_t* t_rx_data)
{
    fnc_code = t_wasp_id & 0xF00;
    ori_node = (t_wasp_id & 0x0F0)>>4;

    switch(fnc_code){

        case EMCY:
            Recv_EMCY(t_rx_data, &err_code);
            // TODO: ERROR Process
            break;

        case SDO:
            if (Unpack_SDO(t_rx_data) < 0) {
                return SDO_RX_ERR;
            } else{
                Send_SDO(ori_node);
            }
            break;

        case PDO:
            if (Unpack_PDO(t_rx_data) < 0) {
                return PDO_RX_ERR;
            } else{
                Send_PDO(ori_node);
            }
            break;

        case TRAJECTORY:
			Assemble_Trajectory(t_rx_data);
        	break;
        default: break;
    }

    return 0;
}

/*
  ___ ___   ___     ___      _ _ _             _
 / __|   \ / _ \   / __|__ _| | | |__  __ _ __| |__ ___
 \__ \ |) | (_) | | (__/ _` | | | '_ \/ _` / _| / /(_-<
 |___/___/ \___/   \___\__,_|_|_|_.__/\__,_\__|_\_\/__/

*/

MSG_COMMON_SDO_CALLBACK(msg_hdlr_task)

static void Set_Send_PDO_List(MsgSDOargs* t_req, MsgSDOargs* t_res)
{
	Clear_PDO_to_Send();

    int t_cursor = 0;
    uint8_t* t_ids = (uint8_t*)t_req->data;
    while (t_cursor < 2*t_req->size) {
        uint8_t t_dod_id = t_ids[t_cursor++];
        uint8_t t_obj_id = t_ids[t_cursor++];
        Add_PDO_to_Send(t_dod_id, t_obj_id);
    }

    t_res->status = DATA_OBJECT_SDO_SUCC;
}

static void Set_MS_Enum(MsgSDOargs* t_req, MsgSDOargs* t_res)
{
	memcpy(&MS_enum, t_req->data, 1);

	t_res->size = 0;
	t_res->status = DATA_OBJECT_SDO_SUCC;
}

static void Set_GUI_COMM_OnOff(MsgSDOargs* t_req, MsgSDOargs* t_res)
{
	memcpy(&GUI_onoff, t_req->data, 1);

	t_res->size = 1;
	t_res->status = DATA_OBJECT_SDO_SUCC;
}

static void Set_GUI_COMM_Command(MsgSDOargs* t_req, MsgSDOargs* t_res)
{
	memcpy(&GUI_command, t_req->data, 1);

	t_res->size = 1;
	t_res->status = DATA_OBJECT_SDO_SUCC;
}

/*
  ___ _        _
 / __| |_ __ _| |_ ___ ___
 \__ \  _/ _` |  _/ -_|_-<
 |___/\__\__,_|\__\___/__/

*/

static void StateOff_Ent()
{
	GUI_onoff = 0;
	GUI_command = 0;
    Transition_State(&msg_hdlr_task.state_machine, e_State_Standby);
}

static void StateStandby_Ent()
{}

static void StateStandby_Run()
{

}

static void StateStandby_Ext()
{
}

static void StateEnable_Ent()
{
	comm_loop_cnt = 0;
	Ent_Routines(&msg_hdlr_task.routine);
}

static void StateEnable_Run()
{
	Run_Routines(&msg_hdlr_task.routine);

    comm_loop_cnt++;
}

static void StateEnable_Ext()
{
	Ext_Routines(&msg_hdlr_task.routine);

	GUI_onoff = 0;
	GUI_command = 0;
}

static void StateError_Run()
{

}


/*
  __  __      _      
 |  \/  |__ _(_)_ _  
 | |\/| / _` | | ' \ 
 |_|  |_\__,_|_|_||_|
                     
*/

void Init_Msg_Hdlr()
{
	node_id = NODE_ID_LA;
    ori_node = 0x00;

    uint16_t t_mask = 0x00F;
    uint32_t t_filter1 = 0;
    uint32_t t_filter2 = NODE_ID_LA;

    /*Communication Init*/
//    comm_type = Init_IOIF_USB();
    comm_type = e_FDCAN;

    if(comm_type == e_FDCAN){
    	Init_IOIF_Fdcan(t_mask, t_filter1, t_filter2);
    }

    /*Task Init*/
    Init_Task(&msg_hdlr_task);

	/* State Definition */
	TASK_CREATE_STATE(&msg_hdlr_task, e_State_Off,      StateOff_Ent,       NULL,    			NULL,   				 true);
	TASK_CREATE_STATE(&msg_hdlr_task, e_State_Standby,  StateStandby_Ent,   StateStandby_Run,	StateStandby_Ext,   	false);
	TASK_CREATE_STATE(&msg_hdlr_task, e_State_Enable,   StateEnable_Ent,   	StateEnable_Run, 	StateEnable_Ext,   		false);
	TASK_CREATE_STATE(&msg_hdlr_task, e_State_Error,    NULL,   			StateError_Run,    	NULL,   				false);

    TASK_CREATE_ROUTINE(&msg_hdlr_task,  ROUTINE_ID_MSG_PDO_SEND, 			NULL, Send_PDO, 		Ext_Send_PDO);
    TASK_CREATE_ROUTINE(&msg_hdlr_task,  ROUTINE_ID_MSG_PDO_DUMMY_TEST, 	NULL, Set_PDO_Dummy, 	NULL);

	/* Data Object Definition */
    Create_DOD(TASK_ID_MSG);

	MSG_COMMON_SDO_CREATE(TASK_ID_MSG)
    Create_SDO(TASK_ID_MSG, SDO_ID_MSG_PDO_LIST, 				e_UInt16, Set_Send_PDO_List);
    Create_SDO(TASK_ID_MSG, SDO_ID_MSG_MS_ENUM,  				e_UInt8, Set_MS_Enum);
    Create_SDO(TASK_ID_MSG, SDO_ID_MSG_GUI_COMM_ONOFF,  		e_UInt8, Set_GUI_COMM_OnOff);
    Create_SDO(TASK_ID_MSG, SDO_ID_MSG_GUI_COMM_COMMAND,  		e_UInt8, Set_GUI_COMM_Command);

	Create_PDO(TASK_ID_MSG, PDO_ID_MSG_TEST1, 					e_Int32, 1, &test_dummy[0]);
	Create_PDO(TASK_ID_MSG, PDO_ID_MSG_TEST2, 					e_Int32, 1, &test_dummy[1]);
	Create_PDO(TASK_ID_MSG, PDO_ID_MSG_TEST3, 					e_Int32, 1, &test_dummy[2]);
	Create_PDO(TASK_ID_MSG, PDO_ID_MSG_TEST4, 					e_Int32, 1, &test_dummy[3]);
	Create_PDO(TASK_ID_MSG, PDO_ID_MSG_TEST5, 					e_Int32, 1, &test_dummy[4]);
	Create_PDO(TASK_ID_MSG, PDO_ID_MSG_TEST6, 					e_Int32, 1, &test_dummy[5]);
	Create_PDO(TASK_ID_MSG, PDO_ID_MSG_TEST7, 					e_Int32, 1, &test_dummy[6]);
	Create_PDO(TASK_ID_MSG, PDO_ID_MSG_TEST8, 					e_Int32, 1, &test_dummy[7]);
	Create_PDO(TASK_ID_MSG, PDO_ID_MSG_TEST9, 					e_Int32, 1, &test_dummy[8]);
	Create_PDO(TASK_ID_MSG, PDO_ID_MSG_TEST10, 					e_Int32, 1, &test_dummy[9]);

	/* Callback Allocation */
    if(comm_type == e_FDCAN){
    	fdcan_rx_callback_ptr = Fdcan_Rx_Hdlr;
    } else {
//    	ioif_usb_rx_callback_ptr = USB_Rx_Hdlr;
    }

    /* Start */
    if(Start_TIM6()>0){
        //TODO: ERROR PROCESS
    }
    ioif_tim6_callback_ptr = Run_Msg_Hdlr;
}

void Run_Msg_Hdlr()
{
//	uint32_t msg_hdlr_loop_time_cnt_1 = DWT->CYCCNT;

	Run_Task(&msg_hdlr_task);

//	uint32_t msg_hdlr_loop_time_cnt_2 = DWT->CYCCNT;
//	msg_hdlr_loop_time_us = (msg_hdlr_loop_time_cnt_2 - msg_hdlr_loop_time_cnt_1)/480; // microsecond
}
