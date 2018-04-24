#ifndef CANIF_CFG_H_
#define CANIF_CFG_H_

#include "../Can/Can.h"

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

/*CanIf Receive */
#define CANIF_ID_RxDiagP2P                        0
#define CANIF_ID_RxDiagP2A                        1
#define CANIF_ID_RxMsgAbsInfo                     2
/*CanIf Transmit */
#define CANIF_ID_TxDiagP2P                        0
#define CANIF_ID_TxDiagP2A                        1
#define CANIF_ID_LS_NM_TX                         2
#define CANIF_ID_TxMsgTime                        3
#define CANIF_ID_HS_NM_TX                         4

/* Configuration index in CanIf_InitController() */
typedef enum {
	CANIF_CHL_LS_CONFIG_0,
	CANIF_CHL_HS_CONFIG_0,
    CANIF_CHANNEL_CONFIGURATION_CNT
}CanIf_ConfigurationIndexType;

/* typedef enum {
	CANIF_CHL_LS,		// CAN_CTRL_0
	CANIF_CHL_HS,		// CAN_CTRL_1
    CANIF_CHANNELS_CNT
}CanIf_ChannelIdType; */

#include "CanIf_Types.h"

extern const CanIf_ConfigType CanIf_Config; 

#endif

