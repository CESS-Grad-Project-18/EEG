#include "Com.h"
#include "Det.h"
#include "Com_MemMap.h"
#include "PduR_Com.h"
#include "SchM_Com.h"
#include "UserCbk.h"

const Com_ConfigType *ComConfig;
ComSignalEndianess_type Com_SystemEndianness;
static Com_StatusType initStatus = COM_UNINIT;
static const uint32_t endian_test  = 0xdeadbeefU;


/* Startup and Control Services*/
void Com_Init(const Com_ConfigType * config){
	if(config == NULL) {
		Det_ReportError(COM_INIT_ID, COM_E_PARAM_POINTER);
		return;
	}
	ComConfig = config;
	uint8 endian_byte = *(const uint8 *)&endian_test; /* Get last byte*/
	if(endian_byte == 0xef ){ 
		Com_SystemEndianness = COM_LITTLE_ENDIAN; 
	}
	else if(endian_byte == 0xde){ 
		Com_SystemEndianness = COM_BIG_ENDIAN;
	}
	else {
		Com_SystemEndianness = COM_OPAQUE;
		assert(0); /* Check */
	}
	if(1){
		initStatus = COM_INIT;
	}
/* TODO: Revise */
} /*SID 0x01*/

void Com_DeInit(void){
	if(initStatus != COM_INIT){
		Det_ReportError(COM_DEINIT_ID, COM_E_UNINIT);
		return;
	}
	/*for ipdu in ipdus{
		clear;
	}
	*/
	initStatus = COM_UNINIT;
/* TODO: Revise */
} /*SID 0x02*/

void Com_IpduGroupControl(Com_IpduGroupVector ipduGroupVector, boolean initialize){
	if(COM_INIT != initStatus) {
		Det_ReportError(COM_IPDUGROUPCONTROL_ID, COM_E_UNINIT);
		return;
	}
    for (uint16 i = 0; !ComConfig->ComIPdu[i].Com_Arc_EOL; i++) {
        const ComIPduGroup_type *const groupRefs = ComConfig->ComIPdu[i].ComIPduGroupRefs;
        uint8 started = FALSE;
        for(uint32 gri=0; (!groupRefs[gri].Com_Arc_EOL && !started); gri++){
            uint8 byteIndex = groupRefs[gri].ComIPduGroupHandleId / 8;
            uint8 bitIndex = groupRefs[gri].ComIPduGroupHandleId % 8;            
            started |= ((ipduGroupVector[byteIndex] >> bitIndex) & 1u);
        }
        Com_Arc_Config.ComIPdu[i].Com_Arc_IpduStarted = started;
    }
}
/* TODO: Revise */
} /*SID 0x03*/

void Com_ReceptionDMControl(Com_IpduGroupVector ipduGroupVector){
/* TODO: Implement */
} /*SID 0x06*/

Com_StatusType Com_GetStatus(void){ 
	return initStatus;
/* TODO: Revise */
}/*SID 0x07, returns COM_INIT or COM_UNINIT*/

void Com_GetVersionInfo(Std_VersionInfoType* versioninfo){
	if(versioninfo != NULL) {
		versioninfo->vendorID =  COM_VENDOR_ID;
		versioninfo->moduleID = COM_MODULE_ID;
		versioninfo->sw_major_version = COM_SW_MAJOR_VERSION;
		versioninfo->sw_minor_version =  COM_SW_MINOR_VERSION;
		versioninfo->sw_patch_version =  COM_SW_PATCH_VERSION;
	}
/* TODO: Revise */
}/*SID 0x09, Version out*/

void Com_ClearIpduGroupVector(Com_IpduGroupVector ipduGroupVector){
	if(initStatus != COM_INIT){
		Det_ReportError(COM_CLEARIPDUGROUPVECTOR_ID, COM_E_UNINIT);
		return;
	}
	memset(ipduGroupVector, 0, sizeof(Com_IpduGroupVector));
/* TODO: Revise */
} /*SID 0x1c*/

void Com_SetIpduGroup(Com_IpduGroupVector ipduGroupVector, Com_IpduGroupIdType ipduGroupId, boolean bitval){
	if(initStatus != COM_INIT){
		Det_ReportError(COM_SETIPDUGROUP_ID, COM_E_UNINIT);
		return;
	}
	uint8 byteIndex = ipduGroupId / 8;
	uint8 bitIndex = ipduGroupId % 8;
	if(bitval){
		ipduGroupVector[byteIndex] |= (1u<<bitIndex);
	}else{
		ipduGroupVector[byteIndex] &= ~(1u<<bitIndex);
	}
}
/* TODO: Revise */
} /*SID 0x1d */



/* Communication Services */
uint8 Com_SendSignal(Com_SignalIdType SignalId, const void* SignalDataPtr){
/* @req COM334 */ /* Shall update buffer if pdu stopped, should not store trigger */
	/* !req COM055 */
	uint8 retVal = E_OK;
	bool dataChanged = FALSE;

	if(Com_GetStatus() != COM_INIT){
		Det_ReportError(COM_SENDSIGNAL_ID, COM_E_UNINIT);
		return COM_SERVICE_NOT_AVAILABLE;
	}

	if(ComConfig->ComNofSignals <= SignalId){
		Det_ReportError(COM_SENDSIGNAL_ID, COM_INVALID_SIGNAL_ID);
		return COM_SERVICE_NOT_AVAILABLE;
	}

	// Store pointer to signal for easier coding.
	const ComSignal_type * Signal = GET_Signal(SignalId);

    if (Signal->ComIPduHandleId == NO_PDU_REFERENCE) {
        /* Return error if signal is not connected to an IPdu*/
        return COM_SERVICE_NOT_AVAILABLE;
    }

    const ComIPdu_type *IPdu = GET_IPdu(Signal->ComIPduHandleId);
    Com_Arc_IPdu_type *Arc_IPdu = GET_ArcIPdu(Signal->ComIPduHandleId);

    if (isPduBufferLocked(getPduId(IPdu))) {
        return COM_BUSY;
    }
	//DEBUG(DEBUG_LOW, "Com_SendSignal: id %d, nBytes %d, BitPosition %d, intVal %d\n", SignalId, nBytes, signal->ComBitPosition, (uint32)*(uint8 *)SignalDataPtr);

    imask_t irq_state;

    Irq_Save(irq_state);
    /* @req COM624 */
    Com_WriteSignalDataToPdu(Signal->ComHandleId, SignalDataPtr, &dataChanged);

    // If the signal has an update bit. Set it!
    /* @req COM061 */
    if (Signal->ComSignalArcUseUpdateBit) {
        SETBIT(Arc_IPdu->ComIPduDataPtr, Signal->ComUpdateBitPosition);
    }

    if( Arc_IPdu->Com_Arc_IpduStarted ) {
        /*
         * If signal has triggered transmit property, trigger a transmission!
         */
        /* @req COM767 */
        /* @req COM734 */
        /* @req COM768 */
        /* @req COM762 *//* Signal with ComBitSize 0 should never be detected as changed */
        if ( (TRIGGERED == Signal->ComTransferProperty) || ( TRIGGERED_WITHOUT_REPETITION == Signal->ComTransferProperty ) ||
                ( ((TRIGGERED_ON_CHANGE == Signal->ComTransferProperty) || ( TRIGGERED_ON_CHANGE_WITHOUT_REPETITION == Signal->ComTransferProperty )) && dataChanged)) {
            /* !req COM625 */
            /* @req COM279 */
            /* @req COM330 */
            /* @req COM467 */ /* Though RetryFailedTransmitRequests not supported. */
            /* @req COM305.1 */

            uint8 nofReps = 0;
            switch(Signal->ComTransferProperty) {
                case TRIGGERED:
                case TRIGGERED_ON_CHANGE:
                    if( 0 == IPdu->ComTxIPdu.ComTxModeTrue.ComTxModeNumberOfRepetitions ) {
                        nofReps = 1;
                    } else {
                        nofReps = IPdu->ComTxIPdu.ComTxModeTrue.ComTxModeNumberOfRepetitions;
                    }
                    break;
                case TRIGGERED_WITHOUT_REPETITION:
                case TRIGGERED_ON_CHANGE_WITHOUT_REPETITION:
                    nofReps = 1;
                    break;
                default:
                    break;
            }
            /* Do not cancel outstanding repetitions triggered by other signals  */
            if( Arc_IPdu->Com_Arc_TxIPduTimers.ComTxIPduNumberOfRepetitionsLeft < nofReps ) {
                Arc_IPdu->Com_Arc_TxIPduTimers.ComTxIPduNumberOfRepetitionsLeft = nofReps;
            }
        }
    } else {
        retVal = COM_SERVICE_NOT_AVAILABLE;
    }
    Irq_Restore(irq_state);

    return retVal;
}
} /*SID 0x0a*/

uint8 Com_SendDynSignal(Com_SignalIdType SignalId, const void* SignalDataPtr, uint16 Length){
/* TODO: Implement */
} /*SID 0x21*/

uint8 Com_ReceiveSignal(Com_SignalIdType SignalId, void* SignalDataPtr){
/* TODO: Implement */
} /*SID 0x0b*/

uint8 Com_ReceiveDynSignal(Com_SignalIdType SignalId, void* SignalDataPtr, uint16* Length){
/* TODO: Implement */
} /*SID 0x22*/

void Com_UpdateShadowSignal(Com_SignalIdType SignalId, const void* SignalDataPtr){
/* TODO: Implement */
} /*SID 0x0c*/

uint8 Com_SendSignalGroup(Com_SignalGroupIdType SignalGroupId){
/* TODO: Implement */
} /*SID 0x0d */

uint8 Com_ReceiveSignalGroup(Com_SignalGroupIdType SignalGroupId){
/* TODO: Implement */
} /*SID 0x0e*/

void Com_ReceiveShadowSignal(Com_SignalIdType SignalId, void* SignalDataPtr){
/* TODO: Implement */
} /*SID 0x0f*/

uint8 Com_SendSignalGroupArray(Com_SignalGroupIdType SignalGroupId, const uint8* SignalGroupArrayPtr){
/* TODO: Implement */
} /*SID 0x23*/

uint8 Com_ReceiveSignalGroupArray(Com_SignalGroupIdType SignalGroupId, uint8* SignalGroupArrayPtr){
/* TODO: Implement */
} /*SID 0x24*/

uint8 Com_InvalidateSignal(Com_SignalIdType SignalId){
/* TODO: Implement */
} /*SID 0x10*/

void Com_InvalidateShadowSignal(Com_SignalIdType SignalId){
/* TODO: Implement */
} /*SID 0x16*/

uint8 Com_InvalidateSignalGroup(Com_SignalGroupIdType SignalGroupId){
/* TODO: Implement */
} /*SID 0x1b*/

Std_ReturnType Com_TriggerIPDUSend(PduIdType PduId){
/* TODO: Implement */
} /*SID 0x17*/

Std_ReturnType Com_TriggerIPDUSendWithMetaData(PduIdType PduId, uint8* MetaData){
/* TODO: Implement */
} /*SID 0x28*/

void Com_SwitchIpduTxMode(PduIdType PduId, boolean Mode){
/* TODO: Implement */
} /*SID 0x27*/



/* Callback functions and Notifications */
Std_ReturnType Com_TriggerTransmit(PduIdType TxPduId, PduInfoType* PduInfoPtr){
/* TODO: Implement */
} /*SID 0x41*/

void Com_RxIndication(PduIdType RxPduId, const PduInfoType* PduInfoPtr){
/* TODO: Implement */
} /*SID 0x42*/

void Com_TpRxIndication(PduIdType id, Std_ReturnType result){
/* TODO: Implement */
} /*SID 0x45*/

void Com_TxConfirmation(PduIdType TxPduId){
/* TODO: Implement */
} /*SID 0x40*/

void Com_TpTxConfirmation(PduIdType id, Std_ReturnType result){
/* TODO: Implement */
} /*SID 0x48*/

BufReq_ReturnType Com_StartOfReception(PduIdType id, const PduInfoType* info,PduLengthType TpSduLength, PduLengthType* bufferSizePtr){
/* TODO: Implement */
} /*SID 0x46*/

BufReq_ReturnType Com_CopyRxData(PduIdType id, const PduInfoType* info, PduLengthType* bufferSizePtr){
/* TODO: Implement */
} /*SID 0x44*/

BufReq_ReturnType Com_CopyRxData(PduIdType PduId, const PduInfoType* PduInfoPtr, PduLengthType* RxBufferSizePtr){
/* TODO: Implement */
}
BufReq_ReturnType Com_CopyTxData(PduIdType id, const PduInfoType* info, RetryInfoType* retry, PduLengthType* availableDataPtr){
/* TODO: Implement */
} /*SID 0x43*/


/* Scheduled Functions*/
void Com_MainFunctionRx(void){
/* TODO: Implement */
} /*SID 0x18*/

void Com_MainFunctionTx(void){
/* TODO: Implement */
} /*SID 0x19*/

void Com_MainFunctionRouteSignals(void){
/* TODO: Implement */
} /*SID 0x1a*/
