#ifndef BSP_BM1422AGMV_BM1422AGMV_H_
#define BSP_BM1422AGMV_BM1422AGMV_H_

#include "bsp_bm1422agmv_regmap.h"

#include <stdint.h>
#include <string.h>

#define BM1422AGMV_TIMEOUT              200
#define BM1422AGMV_TRIALS               10
#define BM1422AGMV_STRAT_UP_DELAY       500
#define BM1422AGMV_DATA_TIMEOUT         1

typedef uint8_t BM1422AGMV;

typedef uint8_t (*Init_BM1422AGMV_Fnc)			(void);
typedef uint8_t (*DeInit_BM1422AGMV_Fnc)		(void);
typedef uint8_t (*IsDevReady_BM1422AGMV_Fnc)	(uint16_t);    								// DevAddr
typedef uint8_t (*ReadReg_BM1422AGMV_Fnc)		(uint16_t, uint16_t, uint8_t*, uint16_t);	// DevAddr, RegAddr, Data, DataSize
typedef uint8_t (*WriteReg_BM1422AGMV_Fnc)		(uint16_t, uint16_t, uint8_t*, uint16_t);	// DevAddr, RegAddr, Data, DataSize
typedef uint8_t (*Wait_BM1422AGMV_Fnc)			(uint32_t); 								// DevAddr, ms to wait

/* IO context */
typedef struct _BM1422AGMVIOctx {
	Init_BM1422AGMV_Fnc 		Init;
	DeInit_BM1422AGMV_Fnc 		DeInit;
	IsDevReady_BM1422AGMV_Fnc 	IsDevReady;
	ReadReg_BM1422AGMV_Fnc 		ReadReg;
	WriteReg_BM1422AGMV_Fnc 	WriteReg;
	Wait_BM1422AGMV_Fnc 		Wait;
} BM1422AGMVIOctx;

// Value
typedef struct _BM1422AGMVValue {
    float bm1422_mag_x;
    float bm1422_mag_y;
    float bm1422_mag_z;
} BM1422AGMVValue;

// Object handle
typedef struct _BM1422AGMVObject {
	uint16_t 		addr;
	BM1422AGMVIOctx io;
	BM1422AGMVValue value;
} BM1422AGMVObject;

typedef enum _BM1422AGMVState {
    e_BM1422AGMV_STATUS_OK = 0,
    e_BM1422AGMV_STATUS_ERROR,
    e_BM1422AGMV_STATUS_BUSY,
    e_BM1422AGMV_STATUS_TIMEOUT,
} BM1422AGMVState;

BM1422AGMV Init_BM1422AGMV(BM1422AGMVObject* t_obj);
BM1422AGMV Set_Ioctx_BM1422AGMV(BM1422AGMVObject *t_obj, BM1422AGMVIOctx *t_ioctx);
BM1422AGMV Get_Value_BM1422AGMV(BM1422AGMVObject* t_obj);

#endif /* BSP_BM1422AGMV_BM1422AGMV_H_ */
