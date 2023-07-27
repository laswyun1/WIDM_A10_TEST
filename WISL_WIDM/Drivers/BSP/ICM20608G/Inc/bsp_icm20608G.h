#ifndef BSP_ICM20608G_ICM20608G_H_
#define BSP_ICM20608G_ICM20608G_H_

#include "bsp_icm20608G_regmap.h"

#include <stdint.h>
#include <string.h>

#define ICM20608G_TIMEOUT         200
#define ICM20608G_TRIALS          10
#define ICM20608G_STRAT_UP_DELAY  500
#define ICM20608G_DATA_TIMEOUT    1

#define ICM20608G_DEFAULT_GCC   0xFF
#define ICM20608G_DEFAULT_SCALE 0xFF

typedef uint8_t ICM20608G;

typedef uint8_t (*Init_ICM20608G_Fnc)       (void);
typedef uint8_t (*DeInit_ICM20608G_Fnc)     (void);
typedef uint8_t (*IsDevReady_ICM20608G_Fnc) (uint16_t);                               // DevAddr
typedef uint8_t (*ReadReg_ICM20608G_Fnc)    (uint16_t, uint16_t, uint8_t*, uint16_t); // DevAddr, RegAddr, Data, DataSize
typedef uint8_t (*WriteReg_ICM20608G_Fnc)   (uint16_t, uint16_t, uint8_t*, uint16_t); // DevAddr, RegAddr, Data, DataSize
typedef uint8_t (*Wait_ICM20608G_Fnc)       (uint32_t);			                      // ms to wait

// IO context
typedef struct _ICM20608GIOctx{
    Init_ICM20608G_Fnc       Init;
    DeInit_ICM20608G_Fnc     DeInit;
    IsDevReady_ICM20608G_Fnc IsDevReady;
    ReadReg_ICM20608G_Fnc    ReadReg;
    WriteReg_ICM20608G_Fnc   WriteReg;
    Wait_ICM20608G_Fnc       Wait;
} ICM20608GIOctx;

// Value
typedef struct _ICM20608GValue{
    float icm20608_acc_x;
    float icm20608_acc_y;
    float icm20608_acc_z;
    float icm20608_gyr_x;
    float icm20608_gyr_y;
    float icm20608_gyr_z;
} ICM20608GValue;

// Object handle
typedef struct _ICM20608GObject{
    uint16_t        addr;
    ICM20608GIOctx  io;
    ICM20608GValue  value;
} ICM20608GObject;

typedef enum _ICM20608GState{
    e_ICM20608G_STATUS_OK = 0,
    e_ICM20608G_STATUS_ERROR,
    e_ICM20608G_STATUS_BUSY,
    e_ICM20608G_STATUS_TIMEOUT,
} ICM20608GState;

ICM20608G Init_ICM20608G(ICM20608GObject* t_obj);
ICM20608G Set_Ioctx_ICM20608G(ICM20608GObject* t_obj, ICM20608GIOctx* ioctx);
ICM20608G Get_Value_ICM20608G(ICM20608GObject* t_obj);

#endif /* BSP_ICM20602_ICM20602_H_ */
