#ifndef CANIF_CFG_H_
#define CANIF_CFG_H_

#include "Can.h"

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
#define CANIF_ID_RxDiagP2P                        0
#define CANIF_ID_RxDiagP2A                        1
#define CANIF_ID_RxMsgAbsInfo                     2
/* CanIf Transmit */
#define CANIF_ID_TxDiagP2P                        0
#define CANIF_ID_TxDiagP2A                        1
#define CANIF_ID_LS_NM_TX                         2
#define CANIF_ID_TxMsgTime                        3
#define CANIF_ID_HS_NM_TX                         4

typedef enum {
	CAN_CTRL_1 = 0,
	CAN_CONTROLLER_CNT = 1
} Can_ControllerIdType;

#endif
