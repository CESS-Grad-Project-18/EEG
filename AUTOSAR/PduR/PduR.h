#ifndef PDUR_H
#define PDUR_H

#define PDUR_VENDOR_ID		   VENDOR_ID_MENTOR_GRAPHICS
#define PDUR_MODULE_ID		   5 /* Update */
#define PDUR_AR_MAJOR_VERSION  3
#define PDUR_AR_MINOR_VERSION  1
#define PDUR_AR_PATCH_VERSION  5
#define PDUR_SW_MAJOR_VERSION  2
#define PDUR_SW_MINOR_VERSION  0
#define PDUR_SW_PATCH_VERSION  0



/* ERROR CODES */
#define PDUR_E_CONFIG_PTR_INVALID 		0x06
#define PDUR_E_INVALID_REQUEST 			0x01
#define PDUR_E_PDU_ID_INVALID			0x02
#define PDUR_E_TP_TX_REQ_REJECTED		0x03
#define PDUR_E_DATA_PTR_INVALID			0x05
#define PDUR_E_BUFFER_ERROR				0x06
#define PDUR_E_INIT_FAILED				0x0X /* Check error code */

#include "PduR_Cfg.h"
#include "PduR_Types.h"
#include "PduR_PbCfg.h"

#if PDUR_COM_SUPPORT == STD_ON
#include "PduR_Com.h"
#endif
#if PDUR_CANIF_SUPPORT == STD_ON
#include "PduR_CanIf.h"
#endif
#if PDUR_CANTP_SUPPORT == STD_ON
#include "PduR_CanTp.h"
#endif
#if PDUR_DCM_SUPPORT == STD_ON
#include "PduR_Dcm.h"
#endif


extern const PduR_PBConfigType *PduRConfig;

/*  The state of the PDU router. */
extern PduR_StateType PduRState;


#if (PDUR_DEV_ERROR_DETECT == STD_ON)

#define PDUR_DET_REPORTERROR(_x,_y,_z,_o) Det_ReportError(_x,_y,_z,_o)

#define PDUR_VALIDATE_INITIALIZED(_api,...) \
	if ((PduRState == PDUR_UNINIT) || (PduRState == PDUR_REDUCED)) { \
		Det_ReportError(MODULE_ID_PDUR, PDUR_INSTANCE_ID, _api, PDUR_E_INVALID_REQUEST); \
		return __VA_ARGS__; \
	}

#define PDUR_VALIDATE_PDUPTR(_api, _pduPtr, ...) \
	if ((_pduPtr == NULL) && (PDUR_DEV_ERROR_DETECT)) { \
		Det_ReportError(MODULE_ID_PDUR, PDUR_INSTANCE_ID, _api, PDUR_E_DATA_PTR_INVALID); \
		return __VA_ARGS__; \
	}

#define PDUR_VALIDATE_PDUID(_api, _pduId, ...) \
	if ((_pduId >= PduRConfig->NRoutingPaths) && PDUR_DEV_ERROR_DETECT) { \
		Det_ReportError(MODULE_ID_PDUR, PDUR_INSTANCE_ID, _api, PDUR_E_PDU_ID_INVALID); \
		return __VA_ARGS__; \
	}


#else
#define PDUR_DET_REPORTERROR(_x,_y,_z,_o)
#define PDUR_VALIDATE_INITIALIZED(_api,...)
#define PDUR_VALIDATE_PDUPTR(_api, _pduPtr, ...)
#define PDUR_VALIDATE_PDUID(_api, _pduId, ...)

#endif

/* Zero Cost Operation function definitions
 * These macros replaces the original functions if zero cost
 * operation is desired. */
#if PDUR_ZERO_COST_OPERATION == STD_ON
#define PduR_Init(...)
#define PduR_GetVersionInfo(...)
#define PduR_GetConfigurationId(...) 0

#else /* Not zero cost operation */

/* General PDU Router functionality */
void PduR_Init(const PduR_PBConfigType* ConfigPtr); /* SID: 0x00 */
void PduR_GetVersionInfo(Std_VersionInfoType* versionInfo); /* SID: 0x17 */
uint32 PduR_GetConfigurationId(void); /* SID: 0x18 */


/* CAN Interface functions */
void PduR_CanIfRxIndication(PduIdType CanRxPduId, const uint8* CanSduPtr); /* SID: 0x01 */
void PduR_CanIfTxConfirmation(PduIdType CanTxPduId); /* SID: 0x02 */
BufReq_ReturnType PduR_CanTpProvideRxBuffer(PduIdType CanTpRxPduId, PduLengthType TpSduLength, PduInfoType **PduInfoPtr); /* SID: 0x03 */
void PduR_CanTpRxIndication(PduIdType CanTpRxPduId, NotifResultType Result); /* SID: 0x04 */
BufReq_ReturnType PduR_CanTpProvideTxBuffer(PduIdType CanTpTxPduId, PduInfoType **PduInfoPtr, uint16 Length); /* SID: 0x05 */
void PduR_CanTpTxConfirmation(PduIdType CanTpTxPduId, NotifResultType Result); /* SID: 0x06*/

/* COM */
Std_ReturnType PduR_ComTransmit(PduIdType ComTxPduId, const PduInfoType *PduInfoPtr); /* SID: 0x15 */

/* DCM */
Std_ReturnType PduR_DcmTransmit(PduIdType DcmTxPduId, const PduInfoType *PduInfoPtr); /* SID: 0x16 */

/* IPDUM */
Std_ReturnType PduR_IpdumTransmit(PduIdType IpdumTxPduId, const PduInfoType *PduInfoPtr); /* SID: 0x19 */
void PduR_IpdumTxConfirmation(PduIdType IpdumLoTxPduId) /* SID: 0x1A */
void PduR_IpdumRxIndication(PduIdType IpdumLoRxPduId, const uint8 *IpdumSduPtr); /* SID: 0x1B */

#endif /* PDUR_H */
