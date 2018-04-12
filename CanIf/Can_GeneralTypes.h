#ifndef CAN_GENERAL_TYPES
#define CAN_GENERAL_TYPES

#include "CanIf_Cfg.h"


typedef uint32 Can_IdType; /* Assuming extended IDs are used, revert to uint16 for standard IDs, 0x Std ID, 1x Ext ID*/ 

/* Use uint16 if more than 255 H/W handles otherwise, uint8*/
typedef uint16 Can_HwHandleType;

typedef enum {
	CAN_T_STOP = 1, /* Cannot request mode CAN_UNINIT */
	CAN_T_START,
	CAN_T_SLEEP,
	CAN_T_WAKEUP
} Can_StateTransitionType;

typedef enum {
	CAN_OK, /* Successful operation */
	CAN_NOT_OK, /* Error occurred or wakeup event occurred during sleep transition */
	CAN_BUSY /* Transmit request not processed because no transmit object was available*/
} Can_ReturnType;


typedef struct {	
	/* TODO: Implement */
} Can_ConfigType ;

typedef struct {	
	Can_IdType CanId /* Standard/Extended CAN ID of CAN LPDU */
	Can_HwHandleType Hoh /* ID of the corresponding HardwareObject Range */
	uint8 ControllerId /* ControllerId provided by CanIf clearly identify the corresponding controller */
} Can_HwType;

typedef struct {	
	PduIdType   swPduHandle; /*CanIf private data , may be used by Callback */
	uint8 length; /* Length (8 bytes max) */
	Can_IdType 	id; /* the CAN ID, 29 or 11-bit */
	const uint8 *sdu; /* Data pointer */
} Can_PduType;

typedef enum {
  CANTRCV_TRCVMODE_NORMAL = 0, /* Transceiver mode NORMAL */
  CANTRCV_TRCVMODE_STANDBY, /* Transceiver mode STANDBY */
  CANTRCV_TRCVMODE_SLEEP /* Transceiver mode SLEEP */
} CanTrcv_TrcvModeType ;

typedef enum {
	CANTRCV_WU_ERROR = 0,  /* This value may only be reported when error was reported to DEM before. Wake-up reason was not detected */
	CANTRCV_WU_NOT_SUPPORTED, /* The transceiver does not support any information for the wakeup reason. */
	CANTRCV_WU_BY_BUS, /* Network has caused the wake up of the ECU */
	CANTRCV_WU_BY_PIN, /* Wake-up event at one of the transceiver's pins (not at the CAN bus). */
	CANTRCV_WU_INTERNALLY, /* Network has woken the ECU via a request to NORMAL mode */
	CANTRCV_WU_RESET, /* Wake-up is due to an ECU reset */
	CANTRCV_WU_POWER_ON /* Wake-up is due to an ECU reset after power on. */
} CanTrcv_TrcvWakeupReasonType;

typedef enum {
	CANTRCV_WUMODE_ENABLE = 0, /* Wakeup events notifications are enabled on the addressed network. */
	CANTRCV_WUMODE_DISABLE, /* Wakeup events notifications are disabled on the addressed network. */
	CANTRCV_WUMODE_CLEAR /* A stored wakeup event is cleared on the addressed network */
} CanTrcv_TrcvWakeupModeType;

#endif /* CAN_GENERAL_TYPES */
