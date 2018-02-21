#if defined(USE_DET)
#include "Det.h"
#endif
#include "Dem.h"
#include "CanIf.h"
#include "CanIf_Cbk.h"


#if  ( CANIF_DEV_ERROR_DETECT == STD_ON )
/* Validation with return value */	
#define CHECK(_exp,_api,_err ) \
        if( !(_exp) ) { \
          Det_ReportError(MODULE_ID_CANIF, 0, _api, _err); \
          return E_NOT_OK; \
        }

/* Validation without return value */	
#define CHECK_NO_RV(_exp,_api,_err ) \
  if( !(_exp) ) { \
          Det_ReportError(MODULE_ID_CANIF, 0, _api, _err); \
          return; \
        }
#define DET_REPORTERROR(_x,_y,_z,_q) Det_ReportError(_x, _y, _z, _q)

#else
	
#define CHECK(_exp,_api,_err )
#define CHECK_NO_RV(_exp,_api,_err )
#define DET_REPORTERROR(_x,_y,_z,_q)

#endif

Std_ReturnType CanIf_GetControllerMode(uint8 Controller, CanIf_ControllerModeType *ControllerModePtr){
  CanIf_Arc_ChannelIdType channel = (CanIf_Arc_ChannelIdType) Controller;

  CHECK(CanIf_Global.initRun, CANIF_GET_CONTROLLER_MODE_ID, CANIF_E_UNINIT );
  CHECK(channel < CANIF_CHANNEL_CNT, CANIF_GET_CONTROLLER_MODE_ID, CANIF_E_PARAM_CONTROLLER );
  CHECK(ControllerModePtr != NULL, CANIF_GET_CONTROLLER_MODE_ID, CANIF_E_PARAM_POINTER );

  *ControllerModePtr = CanIf_Global.channelData[channel].ControllerMode;

  return E_OK;
}


Std_ReturnType CanIf_Transmit(PduIdType CanTxPduId, const PduInfoType *CanIfTxInfoPtr){
  Can_PduType canPdu;
  const CanIf_TxPduConfigType *txEntry;
  CanIf_ControllerModeType csMode;
  CanIf_ChannelGetModeType pduMode;

  CHECK(CanIf_Global.initRun, CANIF_TRANSMIT_ID, CANIF_E_UNINIT);
  CHECK((CanIfTxInfoPtr != 0), CANIF_TRANSMIT_ID, CANIF_E_PARAM_POINTER);

  /* Get the controller from L-PDU handle */
  txEntry = CanIf_FindTxPduEntry(CanTxPduId);

  if (txEntry == 0)
  {
    CHECK(FALSE, CANIF_TRANSMIT_ID, CANIF_E_INVALID_TXPDUID);
    return E_NOT_OK;
  }

  CanIf_Arc_ChannelIdType channel = txEntry->CanIfCanTxPduHthRef->CanIfCanControllerIdRef;

  /* Get and verify the controller mode */
  if (CanIf_GetControllerMode(channel, &csMode) == E_NOT_OK){
    return E_NOT_OK;
  }

  if (csMode != CANIF_CS_STARTED){  /* CANIF_161 */
    return E_NOT_OK;
  }

  /* Get and verify the PDU channel mode control */
  if (CanIf_GetPduMode(channel, &pduMode) == E_NOT_OK){
    return E_NOT_OK;
  }

  if ((pduMode != CANIF_GET_TX_ONLINE) && (pduMode != CANIF_GET_ONLINE)){
    return E_NOT_OK;
  }

  canPdu.id = txEntry->CanIfCanTxPduIdCanId;

  canPdu.length = CanIfTxInfoPtr->SduLength;
  canPdu.sdu = CanIfTxInfoPtr->SduDataPtr;
  canPdu.swPduHandle = CanTxPduId;

  Can_ReturnType rVal = Can_Write(txEntry->CanIfCanTxPduHthRef->CanIfHthIdSymRef, &canPdu);

  if (rVal == CAN_NOT_OK){
    return E_NOT_OK;
  }

  if (rVal == CAN_BUSY)  /* CANIF 082, CANIF 161
  {
    /* Tx buffering not supported so just return. */
    return E_NOT_OK;
  }

  return E_OK;
}