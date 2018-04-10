#if defined(USE_DET)
#include "Det.h"
#endif
#include "CanIf.h"

#include "Can.h"
#include "CanIf_Cbk.h"
#include <string.h>

#include "PduR.h"

/* Global configure */
static const CanIf_ConfigType *CanIf_ConfigPtr;

// Struct of controller private data.
typedef struct{
  CanIf_ControllerModeType  ControllerMode;
  CanIf_PduModeType  PduMode;
} CanIf_ChannelPrivateType;

typedef struct {
  boolean initRun;
  CanIf_ChannelPrivateType channelData[CANIF_CHANNEL_CNT]; /* 2? */
} CanIf_GlobalType;

/* Global config */
CanIf_GlobalType CanIf_Global;

void CanIf_Init(const CanIf_ConfigType *ConfigPtr){
  if(ConfigPtr == NULL) {
    Det_ReportError(MODULE_ID_CANIF, 0, CAN_INIT_ID, CAN_E_PARAM_POINTER);
    return;
  }
  uint8 i;
  CanIf_ConfigPtr = ConfigPtr;

  /* CAN controllers and transceivers till remain non operational */
  for (i = 0; i < CANIF_CHANNEL_CNT; i++){
    CanIf_Global.channelData[i].ControllerMode = CANIF_CS_STOPPED;
    CanIf_Global.channelData[i].PduMode = CANIF_GET_OFFLINE;
    /* @req CAN*/
    CanIf_PreInit_InitController(i, CanIf_ConfigPtr->Arc_ChannelDefaultConfIndex[i]);
  }
  CanIf_Global.initRun = TRUE;
}

void CanIf_PreInit_InitController(uint8 Controller, uint8 ConfigurationIndex);

static CanIf_Arc_ChannelIdType CanIf_Arc_FindHrhChannel( Can_Arc_HRHType hrh )
{
  const CanIf_InitHohConfigType *hohConfig;
  const CanIf_HrhConfigType *hrhConfig;

  // foreach(hoh){ foreach(hrh in hoh) {} }
  hohConfig = CanIf_ConfigPtr->InitConfig->CanIfHohConfigPtr;
  hohConfig--;
  do
  {
    hohConfig++;

    hrhConfig = hohConfig->CanIfHrhConfig;
    hrhConfig--;
    do
    {
      hrhConfig++;
      if (hrhConfig->CanIfHrhIdSymRef == hrh){
        return hrhConfig->CanIfCanControllerHrhIdRef;
      }
    } while(!hrhConfig->CanIf_Arc_EOL);
  } while(!hohConfig->CanIf_Arc_EOL);

  Det_ReportError(MODULE_ID_CANIF, 0, CANIF_RXINDICATION_ID, CANIF_E_PARAM_HRH);

  return (CanIf_Arc_ChannelIdType) -1;
}




//-------------------------------------------------------------------
/*
 * Controller :: CanIf_Arc_ChannelIdType (CanIf-specific id to abstract from Can driver/controllers)
 * ConfigurationIndex :: CanIf_Arc_ConfigurationIndexType
 */

/* Figure 7.7 CanIf State machine*/
void CanIf_InitController(uint8 Controller, uint8 ConfigurationIndex){
  // We call this a CanIf channel. Hopefully makes it easier to follow.
  CanIf_Arc_ChannelIdType channel = (CanIf_Arc_ChannelIdType) Controller;
  CanIf_ControllerModeType mode;

  if(CanIf_Global.initRun == 0){
    Det_ReportError(CANIF_INIT_CONTROLLER_ID, CANIF_E_UNINIT);
    return;
  }

  if(channel > CANIF_CHANNEL_CNT){
    Det_ReportError(CANIF_INIT_CONTROLLER_ID, CANIF_E_PARAM_CONTROLLER);
    return;
  } 

  if(ConfigurationIndex > CANIF_CHANNEL_CONFIGURATION_CNT){
    Det_ReportError(CANIF_INIT_CONTROLLER_ID, CANIF_E_PARAM_POINTER);
    return;
  }

  /* @req CANIF092 */
  if (CanIf_GetControllerMode(channel, &mode) == E_OK){
    if (mode == CANIF_CS_STARTED){
      CanIf_SetControllerMode(channel, CANIF_CS_STOPPED); 
    }
    else if (mode != CANIF_CS_STOPPED){
      Det_ReportError(MODULE_ID_CANIF, 0, CANIF_INIT_CONTROLLER_ID, CANIF_E_PARAM_CONTROLLER_MODE);
      return;
    }
  }
  else{
    Det_ReportError(MODULE_ID_CANIF, 0, CANIF_INIT_CONTROLLER_ID, CANIF_E_PARAM_CONTROLLER_MODE);
    return;
  }

  /* @req CANIF293 */
  /* Subsequently the CAN Interface calls the corresponding CAN Driver initialization services. */

  /* @req CANIF066 */
  /*The CAN Interface has access to the CAN Driver configuration data. All public CAN Driver configuration data are described in [8] Specification of CAN Driver.*/

  // Grab the configuration from the Can Controller
  const Can_ControllerConfigType *canConfig;
  const CanControllerIdType canControllerId = ARC_GET_CHANNEL_CONTROLLER(channel);

  // Validate that the configuration at the index match the right channel
  if(CanIf_ConfigPtr->ControllerConfig[ConfigurationIndex].CanIfControllerIdRef != channel){
    Det_ReportError(CANIF_INIT_CONTROLLER_ID, CANIF_E_PARAM_CONTROLLER);
    return;
  }
  canConfig = CanIf_ConfigPtr->ControllerConfig[ConfigurationIndex].CanIfInitControllerRef;

  // Validate that the CanIfControllerConfig points to configuration for the right Can Controller
  if(canConfig->CanControllerId != canControllerId){
    Det_ReportError(CANIF_INIT_CONTROLLER_ID, CANIF_E_PARAM_CONTROLLER);
    return;
  }

  Can_InitController(canControllerId, canConfig);

  // Set mode to stopped
  CanIf_SetControllerMode(channel, CANIF_CS_STOPPED);
}

void CanIf_PreInit_InitController(uint8 Controller, uint8 ConfigurationIndex){
	// We call this a CanIf channel. Hopefully makes it easier to follow.
	CanIf_Arc_ChannelIdType channel = (CanIf_Arc_ChannelIdType) Controller;

	if(channel > CANIF_CHANNEL_CNT){
    Det_ReportError(CANIF_INIT_ID, CANIF_E_PARAM_POINTER);
    return;
  }
	if(ConfigurationIndex > CANIF_CHANNEL_CONFIGURATION_CNT){
    Det_ReportError(CANIF_INIT_ID, CANIF_E_PARAM_POINTER);
    return;
  }



	const CanControllerIdType canControllerId = ARC_GET_CHANNEL_CONTROLLER(channel);
	// Validate that the configuration at the index match the right channel
	if(CanIf_ConfigPtr->ControllerConfig[ConfigurationIndex].CanIfControllerIdRef != channel){
    Det_ReportError(CANIF_INIT_CONTROLLER_ID, CANIF_E_PARAM_CONTROLLER);    
    return;
  } 
	const Can_ControllerConfigType *canConfig = CanIf_ConfigPtr->ControllerConfig[ConfigurationIndex].CanIfInitControllerRef;
	// Validate that the CanIfControllerConfig points to configuration for the right Can Controller
	if(canConfig->CanControllerId != canControllerId){
    Det_ReportError(CANIF_INIT_CONTROLLER_ID, CANIF_E_PARAM_CONTROLLER);
    return;
  }     

	Can_InitController(canControllerId, canConfig);
}

//-------------------------------------------------------------------

Std_ReturnType CanIf_SetControllerMode(uint8 Controller, CanIf_ControllerModeType ControllerMode){
  // We call this a CanIf channel. Hopefully makes it easier to follow.
  CanIf_Arc_ChannelIdType channel = (CanIf_Arc_ChannelIdType) Controller;


  CanIf_ControllerModeType oldMode;

  VALIDATE( CanIf_Global.initRun, CANIF_SET_CONTROLLER_MODE_ID, CANIF_E_UNINIT );
  VALIDATE( channel < CANIF_CHANNEL_CNT, CANIF_SET_CONTROLLER_MODE_ID, CANIF_E_PARAM_CONTROLLER );

  oldMode = CanIf_Global.channelData[channel].ControllerMode;

  if (oldMode == CANIF_CS_UNINIT){
    VALIDATE(FALSE, CANIF_SET_CONTROLLER_MODE_ID, CANIF_E_UNINIT); // See figure 32, 33
    return E_NOT_OK;
  }
  CanControllerIdType canControllerId = ARC_GET_CHANNEL_CONTROLLER(Controller);
  switch (ControllerMode){
  case CANIF_CS_STARTED:   // Figure 32
  {
    switch (oldMode){
      case CANIF_CS_SLEEP:
        if (Can_SetControllerMode(canControllerId, CAN_T_STOP) == CAN_NOT_OK){
          return E_NOT_OK;
        }
        CanIf_Global.channelData[channel].ControllerMode = CANIF_CS_STOPPED;
        break;
      default:
        // Just fall through
        break;
    }

    CanIf_SetPduMode(channel, CANIF_SET_ONLINE);
    if (Can_SetControllerMode(canControllerId, CAN_T_START) == CAN_NOT_OK){
      return E_NOT_OK;
    }
    CanIf_Global.channelData[channel].ControllerMode = CANIF_CS_STARTED;
  }
  break;

  case CANIF_CS_SLEEP: // Figure 33
  {
    switch (oldMode) {
      case CANIF_CS_STARTED:
        if (Can_SetControllerMode(canControllerId, CAN_T_STOP) == CAN_NOT_OK){
          return E_NOT_OK;
        }
        CanIf_Global.channelData[channel].ControllerMode = CANIF_CS_STOPPED;
        break;
      default:
        // Just fall through for other cases
        break;
    }

    if (Can_SetControllerMode(canControllerId, CAN_T_SLEEP) == CAN_NOT_OK){
      return E_NOT_OK;
    }
    CanIf_Global.channelData[channel].ControllerMode = CANIF_CS_SLEEP;
  }

  case CANIF_CS_STOPPED:
  {
    switch (oldMode){
      case CANIF_CS_SLEEP:
        if (Can_SetControllerMode(canControllerId, CAN_T_WAKEUP) == CAN_NOT_OK){
          return E_NOT_OK;
        }
        break;
      default:
        // Just fall through for other cases
        break;
    }

    CanIf_SetPduMode(channel, CANIF_SET_OFFLINE);
    if (Can_SetControllerMode(canControllerId, CAN_T_STOP) == CAN_NOT_OK){
      return E_NOT_OK;
    }
    CanIf_Global.channelData[channel].ControllerMode = CANIF_CS_STOPPED;
    break;
  }

  case CANIF_CS_UNINIT:
    // Just fall through
    break;
  }
  return E_OK;
}

//-------------------------------------------------------------------

Std_ReturnType CanIf_GetControllerMode(uint8 Controller, CanIf_ControllerModeType *ControllerModePtr){
  // We call this a CanIf channel. Hopefully makes it easier to follow.
  CanIf_Arc_ChannelIdType channel = (CanIf_Arc_ChannelIdType) Controller;

  VALIDATE(CanIf_Global.initRun, CANIF_GET_CONTROLLER_MODE_ID, CANIF_E_UNINIT );
  VALIDATE(channel < CANIF_CHANNEL_CNT, CANIF_GET_CONTROLLER_MODE_ID, CANIF_E_PARAM_CONTROLLER );
  VALIDATE(ControllerModePtr != NULL, CANIF_GET_CONTROLLER_MODE_ID, CANIF_E_PARAM_POINTER );

  *ControllerModePtr = CanIf_Global.channelData[channel].ControllerMode;

  return E_OK;
}

//-------------------------------------------------------------------
/**
 * Matches a Tx PDU id agaist the ones that are in the database.
 *
 * @returns Ptr a TxPdu
 */
CanIf_TxPduConfigType * CanIf_FindTxPduEntry(PduIdType id){
	if (id >= CanIf_ConfigPtr->InitConfig->CanIfNumberOfCanTXPduIds) {
		return NULL;
	} else {
		return &CanIf_ConfigPtr->InitConfig->CanIfTxPduConfigPtr[id];
	}
}

CanIf_RxPduConfigType * CanIf_FindRxPduEntry(PduIdType id) {
	if (id >= CanIf_ConfigPtr->InitConfig->CanIfNumberOfCanRxPduIds) {
		return NULL;
	} else {
		return &CanIf_ConfigPtr->InitConfig->CanIfRxPduConfigPtr[id];
	}
}

//-------------------------------------------------------------------

Std_ReturnType CanIf_Transmit(PduIdType CanIfTxSduId, const PduInfoType *CanIfTxInfoPtr){
  Can_PduType canPdu;
  const CanIf_TxPduConfigType *txEntry;
  CanIf_ControllerModeType csMode;
  CanIf_PduModeType pduMode;

  VALIDATE(CanIf_Global.initRun, CANIF_TRANSMIT_ID, CANIF_E_UNINIT );
  VALIDATE((CanIfTxInfoPtr != 0), CANIF_TRANSMIT_ID, CANIF_E_PARAM_POINTER );

  // Get the controller from L-PDU handle
  txEntry = CanIf_FindTxPduEntry(CanIfTxSduId);

  if (txEntry == 0){
    VALIDATE(FALSE, CANIF_TRANSMIT_ID, CANIF_E_INVALID_TXPDUID);
    return E_NOT_OK;
  }

  CanIf_Arc_ChannelIdType channel = txEntry->CanIfCanTxPduHthRef->CanIfCanControllerIdRef;

  // Get and verify the controller mode
  if (CanIf_GetControllerMode(channel, &csMode) == E_NOT_OK){
    return E_NOT_OK;
  }

  /* @req CANIF161 */
  if (csMode != CANIF_CS_STARTED){
    return E_NOT_OK;
  }

  // Get and verify the PDU channel mode control
  if (CanIf_GetPduMode(channel, &pduMode) == E_NOT_OK){
    return E_NOT_OK;
  }

  if ((pduMode != CANIF_GET_TX_ONLINE) && (pduMode != CANIF_GET_ONLINE)){
    return E_NOT_OK;
  }

  canPdu.id = txEntry->CanIfCanTxPduIdCanId;

  canPdu.length = CanIfTxInfoPtr->SduLength;
  canPdu.sdu = CanIfTxInfoPtr->SduDataPtr;
  canPdu.swPduHandle = CanIfTxSduId;

  Can_ReturnType rVal = Can_Write(txEntry->CanIfCanTxPduHthRef->CanIfHthIdSymRef, &canPdu);

  if (rVal == CAN_NOT_OK){
    return E_NOT_OK;
  }
  /* @req CANIF082 */
  /* @req CANIF161 */
  if (rVal == CAN_BUSY)  {
    /* No buffering */
    return E_NOT_OK;
  }

  return E_OK;
}

//-------------------------------------------------------------------

Std_ReturnType CanIf_SetPduMode(uint8 Controller, CanIf_ChannelSetModeType PduModeRequest){
  // We call this a CanIf channel. Hopefully makes it easier to follow.
  CanIf_Arc_ChannelIdType channel = (CanIf_Arc_ChannelIdType) Controller;

  VALIDATE( CanIf_Global.initRun, CANIF_SETPDUMODE_ID, CANIF_E_UNINIT );
  VALIDATE( channel < CANIF_CHANNEL_CNT, CANIF_SETPDUMODE_ID, CANIF_E_PARAM_CONTROLLER );

  CanIf_PduModeType oldMode = CanIf_Global.channelData[channel].PduMode;

  switch(PduModeRequest)
  {
  case CANIF_SET_OFFLINE:
    CanIf_Global.channelData[channel].PduMode = CANIF_GET_OFFLINE;
    break;
  case CANIF_SET_RX_OFFLINE:
    if (oldMode == CANIF_GET_RX_ONLINE){
      CanIf_Global.channelData[channel].PduMode = CANIF_GET_OFFLINE;
    } else if (oldMode == CANIF_GET_ONLINE){
      CanIf_Global.channelData[channel].PduMode = CANIF_GET_TX_ONLINE;
    } else if (oldMode == CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE){
      CanIf_Global.channelData[channel].PduMode = CANIF_GET_OFFLINE_ACTIVE;
    }

    // Other oldmodes don't care
    break;
  case CANIF_SET_RX_ONLINE:
    if (oldMode == CANIF_GET_OFFLINE){
      CanIf_Global.channelData[channel].PduMode = CANIF_GET_RX_ONLINE;
    } else if (oldMode == CANIF_GET_TX_ONLINE) {
      CanIf_Global.channelData[channel].PduMode = CANIF_GET_ONLINE;
    } else if (oldMode == CANIF_GET_OFFLINE_ACTIVE){
      CanIf_Global.channelData[channel].PduMode = CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE;
    }

    // Other oldmodes don't care
    break;
  case CANIF_SET_TX_OFFLINE:
    if (oldMode == CANIF_GET_TX_ONLINE){
      CanIf_Global.channelData[channel].PduMode = CANIF_GET_OFFLINE;
    } else if (oldMode == CANIF_GET_ONLINE) {
      CanIf_Global.channelData[channel].PduMode = CANIF_GET_RX_ONLINE;
    } else if (oldMode == CANIF_GET_OFFLINE_ACTIVE) {
      CanIf_Global.channelData[channel].PduMode = CANIF_GET_OFFLINE;
    } else if (oldMode == CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE) {
      CanIf_Global.channelData[channel].PduMode = CANIF_GET_RX_ONLINE;
    }

    // Other oldmodes don't care
    break;
  case CANIF_SET_TX_ONLINE:
    if (oldMode == CANIF_GET_OFFLINE){
      CanIf_Global.channelData[channel].PduMode = CANIF_GET_TX_ONLINE;
    } else if (oldMode == CANIF_GET_RX_ONLINE) {
      CanIf_Global.channelData[channel].PduMode = CANIF_GET_ONLINE;
    } else if (oldMode == CANIF_GET_OFFLINE_ACTIVE) {
      CanIf_Global.channelData[channel].PduMode = CANIF_GET_TX_ONLINE;
    } else if (oldMode == CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE) {
      CanIf_Global.channelData[channel].PduMode = CANIF_GET_ONLINE;
    }

    // Other oldmodes don't care
    break;
  case CANIF_SET_ONLINE:
    CanIf_Global.channelData[channel].PduMode = CANIF_GET_ONLINE;
    break;

  case CANIF_SET_TX_OFFLINE_ACTIVE:
    if (oldMode == CANIF_GET_OFFLINE) {
      CanIf_Global.channelData[channel].PduMode = CANIF_GET_OFFLINE_ACTIVE;
    } else if (oldMode == CANIF_GET_RX_ONLINE) {
      CanIf_Global.channelData[channel].PduMode = CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE;
    } else if (oldMode == CANIF_GET_TX_ONLINE) {
      CanIf_Global.channelData[channel].PduMode = CANIF_GET_OFFLINE_ACTIVE;
    } else if (oldMode == CANIF_GET_ONLINE) {
      CanIf_Global.channelData[channel].PduMode = CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE;
    }

    // Other oldmodes don't care
    break;
  }

  return E_OK;
}

//-------------------------------------------------------------------

Std_ReturnType CanIf_GetPduMode(uint8 Controller, CanIf_PduModeType *PduModePtr){
  // We call this a CanIf channel. Hopefully makes it easier to follow.
  CanIf_Arc_ChannelIdType channel = (CanIf_Arc_ChannelIdType) Controller;

  VALIDATE( CanIf_Global.initRun, CANIF_GETPDUMODE_ID, CANIF_E_UNINIT );
  VALIDATE( channel < CANIF_CHANNEL_CNT, CANIF_GETPDUMODE_ID, CANIF_E_PARAM_CONTROLLER );

  *PduModePtr = CanIf_Global.channelData[channel].PduMode;

  return E_OK;
}


/*
 * Callback interface from driver
 */
void CanIf_TxConfirmation(PduIdType canTxPduId)
{
  VALIDATE_NO_RV(CanIf_Global.initRun, CANIF_TXCONFIRMATION_ID, CANIF_E_UNINIT)
  VALIDATE_NO_RV(canTxPduId < CanIf_ConfigPtr->InitConfig->CanIfNumberOfCanTXPduIds, CANIF_TXCONFIRMATION_ID, CANIF_E_PARAM_LPDU);

  const CanIf_TxPduConfigType* entry =
    &CanIf_ConfigPtr->InitConfig->CanIfTxPduConfigPtr[canTxPduId];

      if (entry->CanIfUserTxConfirmation != NULL){
        CanIf_PduModeType mode;
        CanIf_GetPduMode(entry->CanIfCanTxPduHthRef->CanIfCanControllerIdRef, &mode);
        if ((mode == CANIF_GET_TX_ONLINE) || (mode == CANIF_GET_ONLINE)
            || (mode == CANIF_GET_OFFLINE_ACTIVE) || (mode == CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE) ){
          entry->CanIfUserTxConfirmation(entry->CanIfTxPduId);  /* CANIF053 */
        }
      }
      return;
}

void CanIf_RxIndication(const Can_HwType* Mailbox, const PduInfoType* PduInfoPtr){
  VALIDATE_NO_RV(CanIf_Global.initRun, CANIF_RXINDICATION_ID, CANIF_E_UNINIT);
  VALIDATE_NO_RV(CanSduPtr != NULL, CANIF_RXINDICATION_ID, CANIF_E_PARAM_POINTER);
  /* Check PDU mode before continue processing */
  CanIf_PduModeType mode;
  CanIf_Arc_ChannelIdType channel = CanIf_Arc_FindHrhChannel( (Can_Arc_HRHType) Hrh);
  if (channel == -1){  /* Invalid HRH */
    return;
  }

  if (CanIf_GetPduMode(channel, &mode) == E_OK){
    if ((mode == CANIF_GET_OFFLINE) || (mode == CANIF_GET_TX_ONLINE) || (mode == CANIF_GET_OFFLINE_ACTIVE)){
      // Receiver path is disabled so just drop it
      return;
    }
  }else{
    return;  // No mode so just return
  }

  uint16 i;
  const CanIf_RxPduConfigType *entry = CanIf_ConfigPtr->InitConfig->CanIfRxPduConfigPtr;

  /* Find the CAN id in the RxPduList */
  for (i = 0; i < CanIf_ConfigPtr->InitConfig->CanIfNumberOfCanRxPduIds; i++){
    if (entry->CanIfCanRxPduHrhRef->CanIfHrhIdSymRef == Hrh){
      // Software filtering
      if (entry->CanIfCanRxPduHrhRef->CanIfHrhType == CAN_ARC_HANDLE_TYPE_BASIC){
        if (entry->CanIfCanRxPduHrhRef->CanIfSoftwareFilterHrh){
          if (entry->CanIfSoftwareFilterType == CANIF_SOFTFILTER_TYPE_MASK){
            if ((CanId & entry->CanIfCanRxPduCanIdMask ) ==
                ( entry->CanIfCanRxPduCanId & entry->CanIfCanRxPduCanIdMask)){
              // We found a pdu so call higher layers
            }
            else{
              entry++;
              continue; // Go to next entry
            }
          }else{
            Det_ReportError(MODULE_ID_CAN, 0, CANIF_RXINDICATION_ID, CANIF_E_PARAM_HRH);
            continue; /* Frame dropped due to unsupported filter type */
          }
        }
      }
      if (CanDlc > entry->CanIfCanRxPduDlc){
        Det_ReportError(CANIF_RXINDICATION_ID, CANIF_E_PARAM_DLC);
        return;
      }
      switch (entry->CanIfRxUserType){
        case CANIF_USER_TYPE_CAN_SPECIAL:
        {
          ( (CanIf_FuncTypeCanSpecial)(entry->CanIfUserRxIndication) )(
            entry->CanIfCanRxPduHrhRef->CanIfCanControllerHrhIdRef,
            entry->CanIfCanRxPduId,
            CanSduPtr,
            CanDlc,
            CanId);

            return;
        }
        break;

        case CANIF_USER_TYPE_CAN_PDUR:
            // Send Can frame to PDU router
#if defined(USE_PDUR)
        	{
        		PduInfoType pduInfo;
        		pduInfo.SduLength = CanDlc;
        		pduInfo.SduDataPtr = (uint8 *)CanSduPtr;
            	PduR_CanIfRxIndication(entry->CanIfCanRxPduId,&pduInfo);
        	}
            return;
#endif
            break;         
      }
    }

    entry++;
  }

  // Did not find the PDU, something is wrong
  VALIDATE_NO_RV(FALSE, CANIF_RXINDICATION_ID, CANIF_E_PARAM_LPDU);
}

#if ( CANIF_TRANSMIT_CANCELLATION == STD_ON )
void CanIf_CancelTxConfirmation(const Can_PduType *PduInfoPtr)
{
  VALIDATE(FALSE, CANIF_CANCELTXCONFIRMATION_ID, CANIF_E_NOK_NOSUPPORT);
  VALIDATE_NO_RV(CanIf_Global.initRun, CANIF_CANCELTXCONFIRMATION_ID, CANIF_E_UNINIT);
  VALIDATE_NO_RV(PduInfoPtr != NULL, CANIF_RXINDICATION_ID, CANIF_E_PARAM_POINTER);

  const CanIf_TxPduConfigType *entry =
    CanIf_ConfigPtr->InitConfig->CanIfTxPduConfigPtr;

  // Not supported

  // Did not find the PDU, something is wrong
  VALIDATE_NO_RV(FALSE, CANIF_TXCONFIRMATION_ID, CANIF_E_PARAM_LPDU);
}
#endif

void CanIf_ControllerBusOff(uint8 Controller)
{
  CanIf_Arc_ChannelIdType channel = 0xff;

  VALIDATE_NO_RV( CanIf_Global.initRun, CANIF_CONTROLLER_BUSOFF_ID, CANIF_E_UNINIT );

  for(int i = 0; i < CANIF_CHANNEL_CNT; i++)
  {
	  if(CanIf_ConfigPtr->Arc_ChannelToControllerMap[i] == Controller)
	  {
		  channel = i;
	  }
  }

  VALIDATE_NO_RV( Controller < CANIF_CHANNEL_CNT, CANIF_CONTROLLER_BUSOFF_ID, CANIF_E_PARAM_CONTROLLER );

  // According to figure 35 in canif spec this should be done in
  // Can driver but it is better to do it here
  CanIf_SetControllerMode(channel, CANIF_CS_STOPPED);

  if (CanIf_ConfigPtr->DispatchConfig->CanIfBusOffNotification != NULL)
  {
    CanIf_ConfigPtr->DispatchConfig->CanIfBusOffNotification(channel);
  }
}
