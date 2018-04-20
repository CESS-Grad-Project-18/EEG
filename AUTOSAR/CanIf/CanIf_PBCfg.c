
#include "../CanIf/CanIf.h"
#include "../CanIf/CanIf_PBCfg.h"
#include "../PduR/PduR.h"
#include "../PduR/PduR_PBCfg.h"
#include "../COM/Com_PBCfg.h"




// Data for init configuration CanIfInitConfiguration
const CanIf_HthCfgType CanIfHthConfigData_CanIfInitHohCfg[] =
{
	{ 
    	.CanIfHthType 				= BASIC_HOH,
    	.CanIfCanControllerIdRef 	= CANIF_CanIfCtrlCfg,
    	.CanIfHthIdSymRef 			= TX, /* ? */
    	.CanIf_EOL 				    = TRUE,
	},
};

const CanIf_HrhCfgType CanIfHrhConfigData_CanIfInitHohCfg[] =
{
	{
    	.CanIfHrhType 				 = BASIC_HOH,
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

const CanIf_BufferCfgType CanIfBufferCfgData[] = {
		{
			.CanIfBufferHthRef = CanIfHthConfigData_CanIfInitHohCfg,
			.CanIfBufferSize = 2
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
    	.CanIfUserTxConfirmation 	 = NULL, /* PDUR_CALLOUT */
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
    	.CanIfUserTxConfirmation 	 = NULL, /* PDUR_CALLOUT */
    	.CanIfTxPduBufferRef		 = &CanIfBufferCfgData[0],
    	.PduIdRef 					 = NULL,
	},
};

const CanIf_RxPduCfgType CanIfRxPduConfigData[] = {
	{
		.CanIfCanRxPduId 			 		 = PDUR_PDU_ID_EMOTION,
    	.CanIfRxPduCanIdRangeLowerCanId 	 = 137,
    	.CanIfRxPduCanIdRangeUpperCanId 	 = 137,
    	.CanIfCanRxPduDlc 			 		 = 1,
    	.CanIfReadRxPduNotifyStatus 		 = FALSE,
		.CanIfCanRxPduHrhRef		 		 = &CanIfHrhConfigData_CanIfInitHohCfg[0],
    	.CanIfRxPduIdCanIdType 		  		 = STANDARD_CAN,
    	.CanIfUserRxIndication 		 		 = NULL, /* PDUR_CALLOUT */
    	.CanIfCanRxPduCanIdMask 	 		 = 0x7FF,
    	.PduIdRef	 				 		 = NULL,
	},
	{
		.CanIfCanRxPduId 			 		 = PDUR_PDU_ID_SLEEP,
    	.CanIfRxPduCanIdRangeUpperCanId 	 = 387,
    	.CanIfRxPduCanIdRangeUpperCanId 	 = 387,
    	.CanIfCanRxPduDlc 			 		 = 1,
    	.CanIfReadRxPduNotifyStatus 		 = FALSE,
		.CanIfCanRxPduHrhRef		 		 = &CanIfHrhConfigData_CanIfInitHohCfg[0],
    	.CanIfRxPduIdCanIdType 		 		 = STANDARD_CAN,
    	.CanIfUserRxIndication 		 		 = NULL, /* PDUR_CALLOUT */
    	.CanIfCanRxPduCanIdMask 	 		 = 0x7FF,
    	.PduIdRef	 				 		 = NULL,
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



