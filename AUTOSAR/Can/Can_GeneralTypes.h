#ifndef CAN_GENERAL_TYPES
#define CAN_GENERAL_TYPES

#include "CanIf_Cfg.h"

typedef struct {	
	/* TODO: Implement */
} Can_ConfigType ;


typedef struct {	
	PduIdType   swPduHandle; /*CanIf private data , may be used by Callback */
	uint8 length; /* Length (8 bytes max) */
	Can_IdType 	id; /* the CAN ID, 29 or 11-bit */
	const uint8 *sdu; /* Data pointer */
} Can_PduType;


typedef uint32 Can_IdType; /* Assuming extended IDs are used, revert to uint16 for standard IDs, 0x Std ID, 1x Ext ID*/ 


/* Use uint16 if more than 255 H/W handles otherwise, uint8*/
typedef uint16 Can_HwHandleType;


typedef struct {	
	Can_IdType CanId /* Standard/Extended CAN ID of CAN LPDU */
	Can_HwHandleType Hoh /* ID of the corresponding HardwareObject Range */
	uint8 ControllerId /* ControllerId provided by CanIf clearly identify the corresponding controller */
} Can_HwType;


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

#endif /* CAN_GENERAL_TYPES */
