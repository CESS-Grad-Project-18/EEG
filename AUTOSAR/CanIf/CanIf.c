//#include "Det.h"
#include "CanIf.h"
#include "CanIf_Cbk.h"
#include <string.h>

#include "../PduR/PduR.h"
#include "CanIf_Cfg.h"
#include "../Can/Can.h"
#include "../COM/ComStack_Types.h"
#include "CanIf_Types.h"
#include "../Can/Can_GeneralTypes.h"
#include "../Can/Can_Cfg.h"
#include "PduR_CanIf.h"

#define CanIf_GetChannelCtrl(channel) (CanIf_ConfigPtr->ChannelToControllerMap[channel])

/* Global configure */
static const CanIf_ConfigType *CanIf_ConfigPtr;

// Struct of controller private data.
typedef struct{
  CanIf_ControllerModeType  ControllerMode;
  CanIf_PduChannelModeType  PduChannelMode;
} CanIf_ChannelPrivateType;

typedef struct {
  boolean initRun;
  CanIf_ChannelPrivateType channelData[CANIF_CHANNEL_CNT]; /* 2? */
} CanIf_GlobalType;

/* Global config */
CanIf_GlobalType CanIf_Global;

void CanIf_Init(const CanIf_ConfigType *ConfigPtr){
  if(ConfigPtr == NULL) {
    Det_ReportError(CANIF_MODULE_ID, 0, CAN_INIT_ID, CAN_E_PARAM_POINTER);
    return;
  }
  uint8 i;
  CanIf_ConfigPtr = ConfigPtr;

  /* CAN controllers and transceivers till remain non operational */
  for (i = 0; i < CANIF_CHANNEL_CNT; i++){
    CanIf_Global.channelData[i].ControllerMode = CANIF_CS_STOPPED;
    CanIf_Global.channelData[i].PduChannelMode = CANIF_OFFLINE;
    /* @req CAN*/
    //CanIf_PreInit_InitController(i, CanIf_ConfigPtr->ChannelDefaultConfIndex[i]);
  }
  CanIf_Global.initRun = TRUE;
}

void CanIf_PreInit_InitController(uint8 Controller, uint8 ConfigurationIndex);

static CanIf_ChannelIdType CanIf_FindHrhChannel(Can_HRHType hrh){
  const CanIf_InitHohCfgType *hohConfig;
  const CanIf_HrhCfgType *hrhConfig;

  // foreach(hoh){ foreach(hrh in hoh) {} }
  hohConfig = CanIf_ConfigPtr->InitConfig->CanIfHohConfigPtr;
  hohConfig--;
  do{
    hohConfig++;
    hrhConfig = hohConfig->CanIfHrhConfig;
    hrhConfig--;
    do{
      hrhConfig++;
      if (hrhConfig->CanIfHrhIdSymRef == hrh){
        return hrhConfig->CanIfCanControllerHrhIdRef;
      }
    } while(!hrhConfig->CanIf_EOL);
  } while(!hohConfig->CanIf_EOL);
  Det_ReportError(CANIF_MODULE_ID, 0, CANIF_RXINDICATION_ID, CANIF_E_PARAM_HRH);
  return (CanIf_ChannelIdType) -1;
}


/* Figure 7.7 CanIf State machine*/
void CanIf_InitController(uint8 Controller, uint8 ConfigurationIndex){
  CanIf_ChannelIdType channel = (CanIf_ChannelIdType) Controller;
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
      Det_ReportError(CANIF_MODULE_ID, 0, CANIF_INIT_CONTROLLER_ID, CANIF_E_PARAM_CONTROLLER_MODE);
      return;
    }
  }
  else{
    Det_ReportError(CANIF_MODULE_ID, 0, CANIF_INIT_CONTROLLER_ID, CANIF_E_PARAM_CONTROLLER_MODE);
    return;
  }

  /* @req CANIF293 */
  /* Subsequently the CAN Interface calls the corresponding CAN Driver initialization services. */

  /* @req CANIF066 */
  /*The CAN Interface has access to the CAN Driver configuration data. All public CAN Driver configuration data are described in [8] Specification of CAN Driver.*/

  /* Grab the configuration from the Can Controller */
  const Can_ControllerType *canConfig;
  const Can_ControllerIdType canControllerId = CanIf_GetChannelCtrl(channel);

  // Validate that the configuration at the index match the right channel
  if(CanIf_ConfigPtr->ControllerConfig[ConfigurationIndex].CanIfCtrlCanCtrlRef.CanControllerId != channel){
    Det_ReportError(CANIF_INIT_CONTROLLER_ID, CANIF_E_PARAM_CONTROLLER);
    return;
  }
  canConfig = &CanIf_ConfigPtr->ControllerConfig[ConfigurationIndex].CanIfCtrlCanCtrlRef;

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

	CanIf_ChannelIdType channel = (CanIf_ChannelIdType) Controller;

	if(channel > CANIF_CHANNEL_CNT){
    Det_ReportError(CANIF_INIT_ID, CANIF_E_PARAM_POINTER);
    return;
  }
	if(ConfigurationIndex > CANIF_CHANNEL_CONFIGURATION_CNT){
    Det_ReportError(CANIF_INIT_ID, CANIF_E_PARAM_POINTER);
    return;
  }



	const Can_ControllerIdType canControllerId = CanIf_GetChannelCtrl(channel);
 /*	// Validate that the configuration at the index match the right channel
	if(CanIf_ConfigPtr->ControllerConfig[ConfigurationIndex].CanIfControllerIdRef != channel){
    Det_ReportError(CANIF_INIT_CONTROLLER_ID, CANIF_E_PARAM_CONTROLLER);    
    return;
  } */
	const Can_ControllerType *canConfig = &CanIf_ConfigPtr->ControllerConfig[ConfigurationIndex].CanIfCtrlCanCtrlRef;
	// Validate that the CanIfControllerConfig points to configuration for the right Can Controller
	if(canConfig->CanControllerId != canControllerId){
    Det_ReportError(CANIF_INIT_CONTROLLER_ID, CANIF_E_PARAM_CONTROLLER);
    return;
  }     

	Can_InitController(canControllerId, canConfig);
}

Std_ReturnType CanIf_SetControllerMode(uint8 Controller, CanIf_ControllerModeType ControllerMode){
  CanIf_ChannelIdType channel = (CanIf_ChannelIdType) Controller;


  CanIf_ControllerModeType oldMode;

  if(!CanIf_Global.initRun){
    Det_ReportError(CANIF_MODULE_ID, 0, CANIF_CONTROLLER_MODE_ID, CANIF_E_UNINIT);
    return E_NOT_OK;
  }
  if(channel > CANIF_CHANNEL_CNT){
    Det_ReportError(CANIF_MODULE_ID, 0, CANIF_CONTROLLER_MODE_ID, CANIF_E_PARAM_CONTROLLER);
    return E_NOT_OK;
  }

  oldMode = CanIf_Global.channelData[channel].ControllerMode;

  if (oldMode == CANIF_CS_UNINIT){
    Det_ReportError(CANIF_MODULE_ID, 0, CANIF_CONTROLLER_MODE_ID, CANIF_E_UNINIT);
    return E_NOT_OK;
  }

  Can_ControllerIdType canControllerId = CanIf_GetChannelCtrl(Controller);
  switch (ControllerMode){
  case CANIF_CS_STARTED: {
      switch (oldMode) {
          case CANIF_CS_SLEEP:
              if (Can_SetControllerMode(canControllerId, CAN_T_STOP) == CAN_NOT_OK) {
                  return E_NOT_OK;
              }
              CanIf_Global.channelData[channel].ControllerMode = CANIF_CS_STOPPED;
              break;
          default:
              break;
      }

      CanIf_SetPduMode(channel, CANIF_ONLINE);
      if (Can_SetControllerMode(canControllerId, CAN_T_START) == CAN_NOT_OK) {
          return E_NOT_OK;
      }
      CanIf_Global.channelData[channel].ControllerMode = CANIF_CS_STARTED;
      break;
  }

  case CANIF_CS_SLEEP:
  {
    switch (oldMode) {
      case CANIF_CS_STARTED:
        if (Can_SetControllerMode(canControllerId, CAN_T_STOP) == CAN_NOT_OK){
          return E_NOT_OK;
        }
        CanIf_Global.channelData[channel].ControllerMode = CANIF_CS_STOPPED;
        break;
      default:
        break;
    }

    if (Can_SetControllerMode(canControllerId, CAN_T_SLEEP) == CAN_NOT_OK){
      return E_NOT_OK;
    }
    CanIf_Global.channelData[channel].ControllerMode = CANIF_CS_SLEEP;
    break;
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
        break;
    }

    CanIf_SetPduMode(channel, CANIF_OFFLINE);
    if (Can_SetControllerMode(canControllerId, CAN_T_STOP) == CAN_NOT_OK){
      return E_NOT_OK;
    }
    CanIf_Global.channelData[channel].ControllerMode = CANIF_CS_STOPPED;
    break;
  }

  case CANIF_CS_UNINIT:
    break;
  }
  return E_OK;
}


Std_ReturnType CanIf_GetControllerMode(uint8 Controller, CanIf_ControllerModeType *ControllerModePtr){
  CanIf_ChannelIdType channel = (CanIf_ChannelIdType) Controller;

  if(!CanIf_Global.initRun){
      Det_ReportError(CANIF_MODULE_ID, 0, CANIF_CONTROLLER_MODE_ID, CANIF_E_UNINIT);
      return E_NOT_OK;
  }
  if(channel > CANIF_CHANNEL_CNT){
      Det_ReportError(CANIF_MODULE_ID, 0, CANIF_CONTROLLER_MODE_ID, CANIF_E_PARAM_CONTROLLER);
      return E_NOT_OK;
  }
  if(ControllerModePtr == NULL){
      Det_ReportError(CANIF_MODULE_ID, 0, CANIF_CONTROLLER_MODE_ID, CANIF_E_PARAM_POINTER);
      return E_NOT_OK;
  }

  *ControllerModePtr = CanIf_Global.channelData[channel].ControllerMode;

  return E_OK;
}


CanIf_TxPduCfgType * CanIf_FindTxPduEntry(PduIdType id){
	if (id >= CanIf_ConfigPtr->InitConfig->CanIfNumberOfCanTXPduIds) {
		return NULL;
	} else {
		return (CanIf_TxPduCfgType *) &CanIf_ConfigPtr->InitConfig->CanIfTxPduConfigPtr[id];
	}
}

CanIf_RxPduCfgType * CanIf_FindRxPduEntry(PduIdType id) {
	if (id >= CanIf_ConfigPtr->InitConfig->CanIfNumberOfCanRxPduIds) {
		return NULL;
	} else {
		return (CanIf_RxPduCfgType *) &CanIf_ConfigPtr->InitConfig->CanIfRxPduConfigPtr[id];
	}
}

Std_ReturnType CanIf_Transmit(PduIdType CanIfTxSduId, const PduInfoType *CanIfTxInfoPtr){
  Can_PduType canPdu;
  const CanIf_TxPduCfgType *txEntry;
  CanIf_ControllerModeType csMode;
  CanIf_PduChannelModeType pduCMode;

  if(!CanIf_Global.initRun){
    Det_ReportError(CANIF_MODULE_ID, 0, CANIF_TRANSMIT_ID, CANIF_E_UNINIT);
    return E_NOT_OK;
  }

  if(CanIfTxInfoPtr == 0){
    Det_ReportError(CANIF_MODULE_ID, 0, CANIF_TRANSMIT_ID, CANIF_E_PARAM_POINTER);
    return E_NOT_OK;
  }

  txEntry = CanIf_FindTxPduEntry(CanIfTxSduId);

  if (txEntry == NULL){
    Det_ReportError(CANIF_MODULE_ID, 0, CANIF_TRANSMIT_ID, CANIF_E_INVALID_TXPDUID);
    return E_NOT_OK;
  }

  CanIf_ChannelIdType channel = txEntry->CanIfCanTxPduHthRef->CanIfCanControllerIdRef;

  if (CanIf_GetControllerMode(channel, &csMode) == E_NOT_OK){
    return E_NOT_OK;
  }

  /* @req CANIF161 */
  if (csMode != CANIF_CS_STARTED){
    return E_NOT_OK;
  }

  // Get and verify the PDU channel mode control
  if (CanIf_GetPduMode(channel, &pduCMode) == E_NOT_OK){
    return E_NOT_OK;
  }

  if (pduCMode != CANIF_ONLINE){
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

/* TODO: check */
Std_ReturnType CanIf_SetPduMode(uint8 Controller, CanIf_PduChannelModeType PduModeRequest){

  CanIf_ChannelIdType channel = (CanIf_ChannelIdType) Controller;

  if(!CanIf_Global.initRun){
    Det_ReportError(CANIF_MODULE_ID, 0, CANIF_SETPDUMODE_ID, CANIF_E_UNINIT);
    return E_NOT_OK;
  }

  if(channel > CANIF_CHANNEL_CNT){
    Det_ReportError(CANIF_MODULE_ID, 0, CANIF_SETPDUMODE_ID, CANIF_E_PARAM_CONTROLLER);
    return E_NOT_OK;
  }

  CanIf_PduChannelModeType oldMode = CanIf_Global.channelData[channel].PduChannelMode;

  switch(PduModeRequest)
  {
  case CANIF_OFFLINE:
      if (oldMode == CANIF_ONLINE){
          CanIf_Global.channelData[channel].PduChannelMode = CANIF_OFFLINE;
      } else if (oldMode == CANIF_TX_OFFLINE_ACTIVE) {
          CanIf_Global.channelData[channel].PduChannelMode = CANIF_OFFLINE;
      } else if (oldMode == CANIF_OFFLINE) {
          CanIf_Global.channelData[channel].PduChannelMode = CANIF_OFFLINE;
      }
    break;

  case CANIF_TX_OFFLINE:
    if (oldMode == CANIF_ONLINE){
      CanIf_Global.channelData[channel].PduChannelMode = CANIF_OFFLINE;
    } else if (oldMode == CANIF_TX_OFFLINE_ACTIVE) {
      CanIf_Global.channelData[channel].PduChannelMode = CANIF_OFFLINE;
    } else if (oldMode == CANIF_OFFLINE) {
      CanIf_Global.channelData[channel].PduChannelMode = CANIF_OFFLINE;
    }
    break;

  case CANIF_ONLINE:
    if (oldMode == CANIF_OFFLINE){
      CanIf_Global.channelData[channel].PduChannelMode = CANIF_ONLINE;
    } else if (oldMode == CANIF_ONLINE) {
      CanIf_Global.channelData[channel].PduChannelMode = CANIF_ONLINE;
    } else if (oldMode == CANIF_TX_OFFLINE_ACTIVE) {
      CanIf_Global.channelData[channel].PduChannelMode = CANIF_ONLINE;
    }
    break;

  case CANIF_TX_OFFLINE_ACTIVE:
    if (oldMode == CANIF_OFFLINE) {
      CanIf_Global.channelData[channel].PduChannelMode = CANIF_TX_OFFLINE_ACTIVE;
    } else if (oldMode == CANIF_ONLINE) {
      CanIf_Global.channelData[channel].PduChannelMode = CANIF_TX_OFFLINE_ACTIVE;
    } else if (oldMode == CANIF_TX_OFFLINE) {
      CanIf_Global.channelData[channel].PduChannelMode = CANIF_TX_OFFLINE_ACTIVE;
    }
    break;
  }

  return E_OK;
}

Std_ReturnType CanIf_GetPduMode(uint8 Controller, CanIf_PduChannelModeType *PduModePtr){
  CanIf_ChannelIdType channel = (CanIf_ChannelIdType) Controller;

  if(!CanIf_Global.initRun){
    Det_ReportError(CANIF_MODULE_ID, 0, CANIF_GETPDUMODE_ID, CANIF_E_UNINIT);
    return E_NOT_OK;
  }

  if(channel > CANIF_CHANNEL_CNT){
    Det_ReportError(CANIF_MODULE_ID, 0, CANIF_GETPDUMODE_ID, CANIF_E_PARAM_CONTROLLER);
    return E_NOT_OK;
  }

  *PduModePtr = CanIf_Global.channelData[channel].PduChannelMode;

  return E_OK;
}


void CanIf_TxConfirmation(PduIdType canTxPduId){
  if(!CanIf_Global.initRun){
    Det_ReportError(CANIF_MODULE_ID, 0, CANIF_TXCONFIRMATION_ID, CANIF_E_UNINIT);
    return;
  }

  if(canTxPduId > CanIf_ConfigPtr->InitConfig->CanIfNumberOfCanTXPduIds){
    Det_ReportError(CANIF_MODULE_ID, 0, CANIF_TXCONFIRMATION_ID, CANIF_E_PARAM_LPDU);
    return;
  }

  const CanIf_TxPduCfgType* entry =
    &CanIf_ConfigPtr->InitConfig->CanIfTxPduConfigPtr[canTxPduId];

      if (entry->CanIfUserTxConfirmation != NULL){
        CanIf_PduChannelModeType mode;
        CanIf_GetPduMode(entry->CanIfCanTxPduHthRef->CanIfCanControllerIdRef, &mode);
        if (mode == CANIF_ONLINE){
          entry->CanIfUserTxConfirmation(entry->CanIfTxPduId);  /* CANIF053 */
        }
      }
      return;
}

void CanIf_RxIndication(const Can_HwType* Mailbox, const PduInfoType* PduInfoPtr){
  if(!CanIf_Global.initRun){
    Det_ReportError(CANIF_MODULE_ID, 0, CANIF_RXINDICATION_ID, CANIF_E_UNINIT);
    return;
  }

  if(PduInfoPtr->SduDataPtr == NULL){
    Det_ReportError(CANIF_MODULE_ID, 0, CANIF_RXINDICATION_ID, CANIF_E_PARAM_POINTER);
    return;
  }

  /* Check PDU mode before continue processing */
  CanIf_PduChannelModeType mode;
  CanIf_ChannelIdType channel = CanIf_FindHrhChannel((Can_HRHType) Mailbox->Hoh);
  if (channel == -1){  /* Invalid HRH */
    return;
  }

  if (CanIf_GetPduMode(channel, &mode) == E_OK){
    if ((mode == CANIF_OFFLINE) || (mode == CANIF_TX_OFFLINE) || (mode == CANIF_TX_OFFLINE_ACTIVE)){
      // Receiver path is disabled so just drop it
      return;
    }
  }else{
    return;  /* No mode, return */
  }

  uint16 i;
  const CanIf_RxPduCfgType *entry = CanIf_ConfigPtr->InitConfig->CanIfRxPduConfigPtr;

  /* Find the CAN id in the RxPduList */
  for (i = 0; i < CanIf_ConfigPtr->InitConfig->CanIfNumberOfCanRxPduIds; i++){
    if (entry->CanIfCanRxPduHrhRef->CanIfHrhIdSymRef == Mailbox->Hoh){
      /* Software filtering */
      if (entry->CanIfCanRxPduHrhRef->CanIfHrhType == BASIC_HOH){
        if (entry->CanIfCanRxPduHrhRef->CanIfSoftwareFilterHrh){
          if (entry->CanIfSoftwareFilterType == MASK){
            if ((Mailbox->CanId & entry->CanIfCanRxPduCanIdMask) ==
                (entry->CanIfCanRxPduIdCanId & entry->CanIfCanRxPduCanIdMask)){
              // We found a pdu so call higher layers
            }
            else{
              entry++;
              continue; // Go to next entry
            }
          }else{
            Det_ReportError(CAN_MODULE_ID, 0, CANIF_RXINDICATION_ID, CANIF_E_PARAM_HRH);
            continue; /* Frame dropped due to unsupported filter type */
          }
        }
      }
      if (PduInfoPtr->SduLength > entry->CanIfCanRxPduDlc){
        Det_ReportError(CANIF_RXINDICATION_ID, CANIF_E_PARAM_DLC);
        return;
      }

       /* entry->CanIfRxUserType */
          /* Send Can frame to PDU router */
        		PduInfoType* pduInfo;
        		pduInfo->SduLength = entry->CanIfCanRxPduIdDlc;
        		pduInfo->SduDataPtr = (uint8 *)entry->PduIdRef; /* TODO: Check*/
            	//PduR_CanIfRxIndication(entry->CanIfCanRxPduId, pduInfo.SduDataPtr);
                PduR_CanIfRxIndication(entry->CanIfCanRxPduId, pduInfo);
    }

    entry++;
  }

  // Did not find the PDU, something is wrong
  Det_ReportError(CANIF_MODULE_ID, 0, CANIF_RXINDICATION_ID, CANIF_E_PARAM_LPDU);
  return;
}

void CanIf_ControllerBusOff(uint8 Controller){
  uint8 i;
  CanIf_ChannelIdType channel = 0xff;

  if(!CanIf_Global.initRun){
    Det_ReportError(CANIF_MODULE_ID, 0, CANIF_CONTROLLER_BUSOFF_ID, CANIF_E_UNINIT);
    return;
  }

  for(i = 0; i < CANIF_CHANNEL_CNT; i++){
	  if(CanIf_ConfigPtr->ChannelToControllerMap[i] == Controller){
		  channel = i;
	  }
  }

  if(Controller > CANIF_CHANNEL_CNT){
    Det_ReportError(CANIF_MODULE_ID, 0, CANIF_CONTROLLER_BUSOFF_ID, CANIF_E_PARAM_CONTROLLER);
    return;
  }

  /* Move to CAN driver? */
  CanIf_SetControllerMode(channel, CANIF_CS_STOPPED);

  if (CanIf_ConfigPtr->DispatchConfig->CanIfBusOffNotification != NULL){
    CanIf_ConfigPtr->DispatchConfig->CanIfBusOffNotification(channel);
  }
}
