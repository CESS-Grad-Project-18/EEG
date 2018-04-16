
#include "CanIf.h"
#include "CanIf_PBCfg.h"

#if defined(USE_PDUR)
#include "PduR.h"
#include "PduR_PbCfg.h"
#endif

#include "MemMap.h"



// Data for init configuration CanIfInitConfiguration

const CanIf_HthCfgType CanIfHthConfigData_CanIfInitHohCfg[] =
{
	{ 
    	.CanIfHthType 				= BASIC,
    	.CanIfCanControllerIdRef 	= CANIF_CanIfCtrlCfg,
    	.CanIfHthIdSymRef 			= TX, /* ? */
    	.CanIf_EOL 				    = TRUE,
	},
};

const CanIf_HrhCfgType CanIfHrhConfigData_CanIfInitHohCfg[] =
{
	{
    	.CanIfHrhType 				 = BASIC,
    	.CanIfSoftwareFilterHrh 	 = TRUE,
    	.CanIfCanControllerHrhIdRef = CANIF_CanIfCtrlCfg,
    	.CanIfHrhIdSymRef 			 = RX,
    	.CanIf_EOL				     = TRUE,
  	},
};

const CanIf_InitHohCfgType CanIfHohConfigData[] = {
	{
		.CanIfHrhConfig 	= CanIfHrhConfigData_CanIfInitHohCfg,
	    .CanIfHthConfig 	= CanIfHthConfigData_CanIfInitHohCfg,
    	.CanIf_EOL 		    = TRUE,
	},
};


const CanIf_TxPduCfgType CanIfTxPduConfigData[] = {
	{
		.CanIfTxPduId 				 = PDUR_PDU_REV_EMOTION,
    	.CanIfCanTxPduIdCanId 		 = 184,
    	.CanIfCanTxPduIdDlc 		 = 1,
    	.CanIfCanTxPduType 			 = STATIC,
    	.CanIfReadTxPduNotifyStatus = FALSE,
    	.CanIfTxPduIdCanIdType 		 = STANDARD_CAN,
    	.CanIfUserTxConfirmation 	 = PDUR_CALLOUT,
    	.CanIfTxPduBufferRef		 = &CanIfBufferCfgData[0],
    	.PduIdRef 					 = NULL,
	},
	{
		.CanIfTxPduId 				 = PDUR_PDU_REV_SLEEP,
    	.CanIfCanTxPduIdCanId 		 = 142,
    	.CanIfCanTxPduIdDlc 		 = 1,
    	.CanIfCanTxPduType 			 = STATIC,
    	.CanIfReadTxPduNotifyStatus = FALSE,
    	.CanIfTxPduIdCanIdType 		 = STANDARD_CAN,
    	.CanIfUserTxConfirmation 	 = PDUR_CALLOUT,
    	.CanIfTxPduBufferRef		 = &CanIfBufferCfgData[0],
    	.PduIdRef 					 = NULL,
	},
};

const CanIf_RxPduCfgType CanIfRxPduConfigData[] = {
	{
		.CanIfCanRxPduId 			 = PDUR_PDU_ID_EMOTION,
    	.CanIfCanRxPduLowerCanId 	 = 137,
    	.CanIfCanRxPduUpperCanId 	 = 137,
    	.CanIfCanRxPduDlc 			 = 1,
    	.CanIfReadRxPduData 		 = FALSE,
    	.CanIfReadRxPduNotifyStatus = FALSE,
		.CanIfCanRxPduHrhRef		 = &CanIfHrhConfigData_CanIfInitHohCfg[0],
    	.CanIfRxPduIdCanIdType 		 = STANDARD_CAN,
    	.CanIfUserRxIndication 		 = PDUR_CALLOUT,
    	.CanIfCanRxPduCanIdMask 	 = 0x7FF,
    	.PduIdRef	 				 = NULL,
	},
	{
		.CanIfCanRxPduId 			 = PDUR_PDU_ID_SLEEP,
    	.CanIfCanRxPduLowerCanId 	 = 387,
    	.CanIfCanRxPduUpperCanId 	 = 387,
    	.CanIfCanRxPduDlc 			 = 1,
    	.CanIfReadRxPduData 		 = FALSE,
    	.CanIfReadRxPduNotifyStatus = FALSE,
		.CanIfCanRxPduHrhRef		 = &CanIfHrhConfigData_CanIfInitHohCfg[0],
    	.CanIfRxPduIdCanIdType 		 = STANDARD_CAN,
    	.CanIfUserRxIndication 		 = PDUR_CALLOUT,
    	.CanIfCanRxPduCanIdMask 	 = 0x7FF,
    	.PduIdRef	 				 = NULL,
	},
};

/* This container contains the init parameters of the CAN. Multiplicity 1. */
const CanIf_InitCfgType CanIfInitConfig =
{
	.CanIfConfigSet 					= 0, /* Not used  */
	.CanIfNumberOfCanRxPduIds 			= 2,
	.CanIfNumberOfCanTXPduIds 			= 2,
	.CanIfNumberOfDynamicCanTXPduIds	= 0, /* Not used */
	.CanIfHohConfigPtr 					= CanIfHohConfigData,
	.CanIfRxPduConfigPtr 				= CanIfRxPduConfigData,
	.CanIfTxPduConfigPtr 				= CanIfTxPduConfigData,
};

/* Container including all necessary configuration sub-containers */
const CanIf_ConfigType CanIf_Config =
{
	.InitConfig 					= &CanIfInitConfig,
};



