#ifndef CANIF_CFG_H
#define CANIF_CFG_H

#define CANIF_VERSION_INFO_API   STD_OFF
#define CANIF_DEV_ERROR_DETECT   STD_OFF
#define CANIF_DLC_CHECK          STD_ON

#define CANIF_MULITPLE_DRIVER_SUPPORT       STD_OFF   
#define CANIF_READRXPDU_DATA_API             STD_OFF   
#define CANIF_READRXPDU_NOTIFY_STATUS_API     STD_OFF   
#define CANIF_READTXPDU_NOTIFY_STATUS_API     STD_OFF   
#define CANIF_SETDYNAMICTXID_API            STD_OFF   
#define CANIF_WAKEUP_EVENT_API                 STD_OFF   
#define CANIF_TRANSCEIVER_API               STD_OFF   
#define CANIF_TRANSMIT_CANCELLATION         STD_OFF   
#define CANIF_ARC_RUNTIME_PDU_CONFIGURATION STD_OFF   
#define CANIF_CANPDUID_READDATA_API         STD_OFF   
#define CANIF_READRXPDU_NOTIF_STATUS_API    STD_OFF   

/* CanIf Receive */

/* CanIf Transmit */
#define CANIF_ID_EMOTIONSIGNAL                    0
#define CANIF_ID_SLEEPSIGNAL                      1

typedef enum {
	CAN_CTRL_1 = 0,
	CAN_CONTROLLER_CNT = 2
} Can_ControllerIdType;

typedef struct {

	boolean CanControllerActivation;
	uint32 CanControllerBaseAddress;
	uint8 CanControllerId;

} Can_ControllerType;

#endif

