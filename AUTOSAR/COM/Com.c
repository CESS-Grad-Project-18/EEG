#include "Com.h"
#include "Det.h"
#include "Com_MemMap.h"
#include "PduR_Com.h"
#include "SchM_Com.h"
#include "UserCbk.h"

#define Com_GetSignal(SignalId) (&ComConfig->ComSignal[SignalId])
#define Com_GetPDUId(IPdu) ((PduIdType)(IPdu - (ComConfig->ComIPdu)))
#define Com_GetIPDU(IPduId) (&ComConfig->ComIPdu[IPduId])
#define Com_TestBit(data, bit)	(*((uint8 *) data  + (bit / 8)) &  (uint8)(1u << (bit % 8)))
#define Com_SetBit(data, bit)	(*((uint8 *) data    + (bit / 8)) |= (uint8)(1u << (bit % 8)))
#define Com_ClearBit(data, bit) (*((uint8 *) data + (bit / 8)) &= (uint8)~(uint8)(1u << (bit % 8)))


const Com_ConfigType *ComConfig;
ComSignalEndianess_type Com_SystemEndianness;
static Com_StatusType initStatus = COM_UNINIT;
static const uint32_t endian_test  = 0xDEADBEEFu;


/* Startup and Control Services*/
void Com_Init(const Com_ConfigType * config){
	/* @req COM328 */ /* Shall not enable inter-ECU communication */
	/* @req COM128 */ /* Com_Init shall initialize all internal data that is not yet initialized by the start-up code*/
	/* @req COM217 */ /* COM module shall initialize each I-PDU during execution of Com_Init, firstly byte wise with the ComTxIPduUnusedAreasDefault value 
	and then bit wise according to initial values (ComSignalInitValue) of the contained signals and the update-bits */
	/* @req COM772 */ /* If timeout set to 0 */

	uint8 err = 0;
    /* @req COM433 */
	if(config == NULL) {
		Det_ReportError(COM_INIT_ID, COM_E_PARAM_POINTER);
		return;
	}
	uint32 firstTimeout;
	boolean dataChanged = FALSE;
	ComConfig = config;
	uint8 endian_byte = *(const uint8 *)&endian_test; /* Get last byte*/
	if(endian_byte == 0xEF ){ 
		Com_SystemEndianness = COM_LITTLE_ENDIAN; 
	}
	else if(endian_byte == 0xDE){ 
		Com_SystemEndianness = COM_BIG_ENDIAN;
	}
	else {
		Com_SystemEndianness = COM_OPAQUE;
		assert(0); /* Check */
	}
	const ComSignal_type *Signal;
	const ComGroupSignal_type *GroupSignal;
	uint16 bufferIndex = 0, i, j;
	for (i = 0; !ComConfig->ComIPdu[i].Com_EOL; i++) {
	    boolean pduHasGroupSignal = FALSE;
		const ComIPdu_type *IPdu = Com_GetIPDU(i);
		Com_Arc_IPdu_type *Arc_IPdu = GET_ArcIPdu(i);

		if (ComConfig->ComNumOfIPDUs <= i) {
			Det_ReportError(COM_INIT_ID ,COM_E_TOO_MANY_IPDU);
			err = 1;
			break;
		}
		/* Set the data pointer for this PDU */
		IPdu->ComIPduDataPtr = (void *)&Com_Arc_Buffer[bufferIndex];
		bufferIndex += IPdu->ComIPduSize;
		/* If this is a TX and cyclic I-PDU, configure the first deadline. */
		if ((IPdu->ComIPduDirection == SEND) &&
				((IPdu->ComTxIPdu.ComTxModeTrue.ComTxModeMode == PERIODIC) || (IPdu->ComTxIPdu.ComTxModeTrue.ComTxModeMode == MIXED))){
			Arc_IPdu->Com_Arc_TxIPduTimers.ComTxModeTimePeriodTimer = IPdu->ComTxIPdu.ComTxModeTrue.ComTxModeTimeOffset;
		}

		/* Reset firstTimeout. */
		firstTimeout = 0xFFFFFFFFu;

		/* Initialize the memory with the default value. */
		/* @req COM015 */
		if (IPdu->ComIPduDirection == SEND) {
			memset((void *)IPdu->ComIPduDataPtr, IPdu->ComTxIPdu.ComTxIPduUnusedAreasDefault, IPdu->ComIPduSize);
		}

		/* For each signal in this PDU. */
		for (j = 0; (IPdu->ComIPduSignalRef != NULL) && (IPdu->ComIPduSignalRef[j] != NULL) ; j++) {
			Signal = IPdu->ComIPduSignalRef[j];
			Com_Arc_Signal_type * Arc_Signal = GET_ArcSignal(Signal->ComHandleId);

			// Configure signal deadline monitoring if used.
			/* @req COM333 */ /* If timeout set to 0 */
			if (Signal->ComTimeoutFactor > 0) {
				if (Signal->ComSignalUseUpdateBit) {
					/* @req COM292 */ /* Signals with update bit shall have their own deadline monitoring */
					Arc_Signal->Com_Arc_DeadlineCounter = Signal->ComFirstTimeoutFactor; // Configure the deadline counter

				} else {
					// This signal does not use an update bit, and should therefore use per I-PDU deadline monitoring.
					if (Signal->ComFirstTimeoutFactor < firstTimeout) {
						firstTimeout = Signal->ComFirstTimeoutFactor;
					}
				}
			}

			/* @req COM117 */ /* COM module shall clear all update-bits during initialization */
			if (Signal->ComSignalUseUpdateBit) {
				Com_ClearBit(IPdu->ComIPduDataPtr, Signal->ComUpdateBitPosition);
			}
				/* Initialize signal data. */
				/* @req COM098 */
				Com_WriteSignalDataToPdu(Signal->ComHandleId, Signal->ComSignalInitValue, &dataChanged);
			}
		}
		if (IPdu->ComIPduDirection == RECEIVE && IPdu->ComIPduSignalProcessing == DEFERRED) {
			/* Copy the initialized I-PDU to deferred buffer */
			memcpy(IPdu->ComIPduDeferredDataPtr, IPdu->ComIPduDataPtr,IPdu->ComIPduSize);
		}
		/* Configure per I-PDU based deadline monitoring. */
		for (j = 0; (IPdu->ComIPduSignalRef != NULL) && (IPdu->ComIPduSignalRef[j] != NULL); j++) {
			Signal = IPdu->ComIPduSignalRef[j];
			Com_Arc_Signal_type * Arc_Signal = GET_ArcSignal(Signal->ComHandleId);

			/* @req COM333 */ /* If timeout set to 0 */
			if ( (Signal->ComTimeoutFactor > 0) && (!Signal->ComSignalUseUpdateBit) ) {
				/* @req COM290 */
				Arc_Signal->Com_Arc_DeadlineCounter = firstTimeout;
			}
		}
	for (i = 0; i < ComConfig->ComNumOfIPDUs; i++) {
		Com_BufferPduState[i].index = 0;
		Com_BufferPduState[i].isLocked = false;
	}

	/* Check if an error has occurred. */
	if (err) {
		/* */
	} else {
		initStatus = COM_INIT;
	}
/* TODO: Revise */
} /*SID 0x01*/

void Com_DeInit(void){
	if(initStatus != COM_INIT){
		Det_ReportError(COM_DEINIT_ID, COM_E_UNINIT);
		return;
	}
	/* @req COM129 */ /* Com_DeInit shall stop all started I-PDU groups */
	uint16 i;
	for (i = 0; !ComConfig->ComIPdu[i].Com_EOL; i++) {
		ComConfig.ComIPdu[i].isStarted = 0; /* TODO: Check correct action */
	}
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
	bool dataChanged = FALSE;

	if(Com_GetStatus() != COM_INIT){
		Det_ReportError(COM_SENDSIGNAL_ID, COM_E_UNINIT);
		return COM_SERVICE_NOT_AVAILABLE;
	}

	if(ComConfig->ComNumOfSignals <= SignalId){
		Det_ReportError(COM_SENDSIGNAL_ID, COM_INVALID_SIGNAL_ID);
		return COM_SERVICE_NOT_AVAILABLE;
	}

	/* Store pointer to signal for easier coding. */
	const ComSignal_type * Signal = Com_GetSignal(SignalId);

    if (Signal->ComIPduHandleId == NO_PDU_REFERENCE) {
        /* Return error if signal is not connected to an IPdu*/
        return COM_SERVICE_NOT_AVAILABLE;
    }

    const ComIPdu_type *IPdu = Com_GetIPDU(Signal->ComIPduHandleId);

    if (Com_BufferLocked(Com_GetPDUId(IPdu))) {
        return COM_BUSY;
    }

    imask_t irq_state;

    Irq_Save(irq_state);
    /* @req COM624 */
    /*Com_SendSignal shall update the signal object identifed by SignalId with the signal reference by the SignalDataPtr param */
    Com_WriteToPDU(Signal->ComHandleId, SignalDataPtr, &dataChanged); /* Helper function*/

    /* @req COM061 */
    /* Set bit if signal has an update bit */
    if (Signal->ComSignalUseUpdateBit) {
        Com_SetBit(IPdu->ComIPduDataPtr, Signal->ComUpdateBitPosition);
    }

        /* If signal has triggered transmit property, trigger a transmission! */
        /* @req COM767 */
        /* Signal with ComTransferProperty TRIGGERED_WITHOUT_REPETITION assigned to I-PDU  wtih ComTxModeMode DIRECT or MIXED shall be transmitted once 
         * if the new value of the signal is different from local 
         */        
        /* @req COM734 */
        /* Signal with ComTransferProperty TRIGGERED_ON_CHANGE assigned to I-PDU  wtih ComTxModeMode DIRECT or MIXED shall be transmitted once 
         *if the new value of the signal is different from local 
         */        
        /* @req COM768 */ 
        /* Signal with ComTransferProperty TRIGGERED_ON_CHANGE_WITHOUT_REPETITION assigned to I-PDU  wtih ComTxModeMode DIRECT or MIXED shall be transmitted once 
         * if the new value of the signal is different from local 
         */
        /* @req COM762 */
        /* Signal with ComBitSize 0 should never be detected as changed */
        if ( (TRIGGERED == Signal->ComTransferProperty) || ( TRIGGERED_WITHOUT_REPETITION == Signal->ComTransferProperty ) ||
                ( ((TRIGGERED_ON_CHANGE == Signal->ComTransferProperty) || ( TRIGGERED_ON_CHANGE_WITHOUT_REPETITION == Signal->ComTransferProperty )) && dataChanged)) {
            /* !req COM625 */
            /* @req COM279 */
            /* @req COM330 */
            /* @req COM467 */ /* Though RetryFailedTransmitRequests not supported. */
            /* @req COM305.1 */
            uint8 numOfReps = 0;
            switch(Signal->ComTransferProperty) {
                case TRIGGERED:
                case TRIGGERED_ON_CHANGE:
                    if(IPdu->ComTxIPdu.ComTxModeTrue.ComTxModeNumberOfRepetitions == 0){
                        numOfReps = 1;
                    }else{
                        numOfReps = IPdu->ComTxIPdu.ComTxModeTrue.ComTxModeNumberOfRepetitions;
                    }
                    break;
                case TRIGGERED_WITHOUT_REPETITION:
                case TRIGGERED_ON_CHANGE_WITHOUT_REPETITION:
                    numOfReps = 1;
                    break;
                default:
                    break;
            }
            /* Do not cancel outstanding repetitions triggered by other signals  */
            if(IPdu->Com_Arc_TxIPduTimers.ComTxIPduNumberOfRepetitions < numOfReps){
                IPdu->Com_Arc_TxIPduTimers.ComTxIPduNumberOfRepetitions = numOfReps;
            }
    }else{
        return COM_SERVICE_NOT_AVAILABLE;
    }
    Irq_Restore(irq_state);
    return E_OK;
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
	if(Com_GetStatus() != COM_INIT) {
		Det_ReportError(COM_RXINDICATION_ID, COM_E_UNINIT);
		return;
	}
	if(ComConfig->ComNumOfIPDUs <= RxPduId) {
		Det_ReportError(COM_RXINDICATION_ID, COM_INVALID_PDU_ID);
		return;
	}
	const ComIPdu_type *IPdu = Com_GetIPDU(RxPduId);
	Com_Arc_IPdu_type *Arc_IPdu = GET_ArcIPdu(RxPduId);
	imask_t state;
	Irq_Save(state);
	/* @req COM649 */ /* Interrups disabled */
	/* If I-PDU is stopped */
	/* @req COM684 */
	if (!Arc_IPdu->Com_Arc_IpduStarted) {
		Irq_Restore(state);
		return;
	}
	/* Check callout status */
	/* @req COM555 */ /* Notification (Class 1) called immediately after the message has been stored in the receiving message object */
	/* @req COM700 */ /* The I-PDU callout on receiver side can be configured to implement user-defined receive filtering mechanisms. */
	/* @req COM381 */ /* COM shall not support that other AUTOSAR COM module’s APIs than Com_TriggerIPDUSend, Com_TriggerIPDUSendWithMetaData called out of an I-PDU callout */
	/* ComRetryFailedTransmitRequests */
	/* @req COM780 */ /* Retry of failed transmission requests is enabled */
	if ((IPdu->ComRxIPduCallout != COM_NO_FUNCTION_CALLOUT) && (ComRxIPduCallouts[IPdu->ComRxIPduCallout] != NULL)) {
		if (!ComRxIPduCallouts[IPdu->ComRxIPduCallout](RxPduId, PduInfoPtr->SduDataPtr)) {
			/* Det_ReportError(); */
			/* !req COM738 */ /* COM module shall restart the reception deadline monitoring timer also in case of receiving an invalid value */
			Irq_Restore(state);
			return;
		}
	}
	/* !req COM574 */ /* When unpacking an I-PDU, COM module shall check the received data length (PduInfoPtr->SduLength) and unpack and notify only completely received signals via ComNotification. */
	/* Copy IPDU data */
	memcpy(IPdu->ComIPduDataPtr, PduInfoPtr->SduDataPtr, IPdu->ComIPduSize);
	Com_RxProcessSignals(IPdu);
	Irq_Restore(state);
	return;
} /*SID 0x42*/

void Com_TpRxIndication(PduIdType id, Std_ReturnType result){
/* TODO: Implement */
} /*SID 0x45*/

void Com_TxConfirmation(PduIdType TxPduId){
	/* @req COM305 */ /* IMPORTANT */
	/* @req COM469 */ /* ComMinimumDelayTime of an I-PDU is configured greater than 0, COM module shall (re-)load the already running minimum
	 delay time counter with ComMinimumDelayTime for that I-PDU when Com_TxConfirmation is invoked and the minimum delay time counter started at PduR_ComTransmit of that I-PDU is not already elapsed */
	/* @req COM577 */ /* ComTxIPduClearUpdateBit of an I-PDU is configured to Confirmation, 
	COM module shall clear all update-bits of all contained signals after this I-PDU was sent out via PduR_ComTransmit, PduR_ComTransmit returned E_OK and the I-PDU was successfully confirmed*/
	if(Com_GetStatus() != COM_INIT) {
		Det_ReportError(COM_TXCONFIRMATION_ID, COM_E_UNINIT);
		return;
	}
	if( TxPduId >= ComConfig->ComNofIPdus ) {
		Det_ReportError(COM_TXCONFIRMATION_ID, COM_INVALID_PDU_ID);
		return;
	}

    /* @req COM468 */ /* Call all notifications for the I-PDU */
    const ComIPdu_type *IPdu = Com_GetIPDU(TxPduId);

    if (IPdu->ComIPduDirection == RECEIVE) {
        Det_ReportError(COM_TXCONFIRMATION_ID, COM_INVALID_PDU_ID);
    }
    else if (IPdu->ComIPduSignalProcessing == IMMEDIATE) {
        /* If immediate, call the notification functions  */
        for (uint8 i = 0; IPdu->ComIPduSignalRef[i] != NULL; i++) {
            const ComSignal_type *Signal = IPdu->ComIPduSignalRef[i];
            if ((Signal->ComNotification != COM_NO_FUNCTION_CALLOUT) &&
                (ComNotificationCallouts[Signal->ComNotification] != NULL) ) {
                ComNotificationCallouts[Signal->ComNotification]();
            }
        }
    }
    else {
        /* If deferred, set status and let the main function call the notification function */
        const ComSignal_type *Signal = IPdu->ComIPduSignalRef[0];
    	if (Signal != NULL) {

		}
	}
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


/* Helper functions */
void Com_WriteData(uint8 *pdu, uint8 *pduSignalMask, const uint8 *signalDataPtr, uint8 destByteLength,
		Com_BitPositionType segmStartBitOffset, uint8 segmBitLength) {
	Com_BitPositionType pduEndBitOffset = segmStartBitOffset + segmBitLength - 1;
	uint8 pduStartByte = segmStartBitOffset / 8;
	uint8 pduEndByte = (pduEndBitOffset) / 8;
	uint8 pduByteLength = pduEndByte - pduStartByte;

	uint8 segmStartBitOffsetInsideByte = segmStartBitOffset % 8;
	uint8 pduStartByteMask = (0xFFu >> segmStartBitOffsetInsideByte);

	uint8 pduAlignmentShift = 7 - (pduEndBitOffset % 8);
	uint8 segmByteLength = 1 + (segmBitLength - 1) / 8;
	uint8 pduByteNr = 0;
	uint8 signalByteNr = 0;

	uint16 shiftReg = 0;
	uint16 clearReg = 0;

	/* clear pduSignalMask all the way from 0 */
	memset(pduSignalMask, 0x00, pduEndByte);

	/* setup to point to end (LSB) of buffers */
	pdu += pduEndByte;
	pduSignalMask += pduEndByte;
	signalDataPtr += destByteLength - 1;

	/* Process one byte (source) on per iteration */
	do {
		shiftReg = *(signalDataPtr - signalByteNr) & 0x00FFu;
		clearReg = 0x00FF;
		shiftReg <<= pduAlignmentShift;
		clearReg <<= pduAlignmentShift;
		if (pduByteNr == pduByteLength) {
			shiftReg &= pduStartByteMask;
			clearReg &= pduStartByteMask;
		}
		*(pdu - pduByteNr) &= (uint16)~(clearReg & 0x00FFu);
		*(pduSignalMask - pduByteNr) |= (uint16) (clearReg & 0x00FFu);
		*(pdu - pduByteNr) |= shiftReg & 0x00FFu;

		pduByteNr++;
		if ((pduAlignmentShift != 0) && (pduByteNr <= pduByteLength)) {
			shiftReg = *(signalDataPtr - signalByteNr) & 0x00FFu;
			clearReg = 0x00FF;
			shiftReg <<= pduAlignmentShift;
			clearReg <<= pduAlignmentShift;
			shiftReg >>= 8;
			clearReg >>= 8;
			if (pduByteNr == pduByteLength) {
				shiftReg &= pduStartByteMask;
				clearReg &= pduStartByteMask;
			}
			*(pdu - pduByteNr) &= (uint16)~(clearReg & 0x00FFu);
			*(pduSignalMask - pduByteNr) |= (uint16) (clearReg & 0x00FFu);
			*(pdu - pduByteNr) |= shiftReg & 0x00FFu;
		}
		signalByteNr++;
	} while (signalByteNr < segmByteLength);
}

boolean Com_BufferLocked(PduIdType id) {
	imask_t state;
	Irq_Save(state);
	boolean locked = Com_BufferState[id].isLocked;
	Irq_Restore(state);
	if (locked) {
		return true;
	} else {
		return false;
	}
}


void Com_RxSignalProcess(const ComIPdu_type *IPdu){
	/* !req COM053 */
	/* @req COM055 */
	/* !req COM396 */ /* Neither invalidation nor filtering supported */
	/* !req COM352 */
	const ComSignal_type *Signal;
	for (uint8 i = 0; IPdu->ComIPduSignalRef[i] != NULL; i++) {
		Signal = IPdu->ComIPduSignalRef[i];
		/* Signal = Signal->ComHandleId*/

		/* If this signal uses an update bit, then it is only considered if this bit is set. */
		/* @req COM324 */
		/* @req COM067 */
		if ((!Signal->ComSignalArcUseUpdateBit) ||
			((Signal->ComSignalArcUseUpdateBit) && (Com_TestBit(IPdu->ComIPduDataPtr, Signal->ComUpdateBitPosition)) ) ) {
			/* If reception deadline monitoring is used. */
			if (Signal->ComTimeoutFactor > 0) { 
				/* Reset the deadline monitoring timer. */
				/* @req COM715 */
				/* DeadlineCounter = Signal->ComTimeoutFactor; */
			}

			/* Check signal processing mode. */
			if (IPdu->ComIPduSignalProcessing == IMMEDIATE) {
				/* If signal processing mode is IMMEDIATE, notify the signal callback. */
				/* @req COM300 */
				/* @req COM301 */
				if ((IPdu->ComIPduSignalRef[i]->ComNotification != COM_NO_FUNCTION_CALLOUT) &&
					(ComNotificationCallouts[IPdu->ComIPduSignalRef[i]->ComNotification] != NULL) ) {
					ComNotificationCallouts[IPdu->ComIPduSignalRef[i]->ComNotification]();
				}
			} else {
				/* Signal processing mode is DEFERRED, mark the signal as updated. */
				/* Signal->ComSignalUpdated = TRUE; */
			}

		} else {
			/* Nothing? */
		}
	}
}

void Com_WriteToPDU(const Com_SignalIdType signalId, const void *signalData, boolean *dataChanged){
	/* @req COM221 */ /* COM module shall perform endianness conversion before the I-PDU callout on sender side. */
	const ComSignal_type * Signal =  Com_GetSignal(signalId);
	Com_SignalType signalType = Signal->ComSignalType;
	uint8 signalLength = Signal->ComSizeInfo->ComBitSize / 8;
	Com_BitPositionType bitPosition = Signal->ComBitPosition;
	uint8 bitSize = Signal->ComBitSize;
	ComSignalEndianess_type endianness = Signal->ComSignalEndianess;

	uint8 signalBufferSize = Com_SignalTypeToSize(signalType, signalLength);
	uint8 pduSignalMask[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	uint8 signalDataBytesArray[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	const uint8 *signalDataBytes = (const uint8 *)signalData;
	imask_t irq_state;

	Irq_Save(irq_state);
	if (endianness == COM_OPAQUE || signalType == UINT8_N){
		/* @req COM472 */
		/* COM interprets opaque data as uint8[n] andshall always map it to an n-bytes sized signal */
		uint8 *pduBufferBytes = (uint8 *)pduBuffer;
		uint8 startFromPduByte = bitPosition / 8;
		if(memcmp(pduBufferBytes + startFromPduByte, signalDataBytes, signalLength) != 0){
		    *dataChanged = TRUE;
		}
		memcpy(pduBufferBytes + startFromPduByte, signalDataBytes, signalLength);
	}else{
		if (Com_SystemEndianness == COM_BIG_ENDIAN){
			uint8 i;
			for (i = 0; i < signalBufferSize; i++){
				signalDataBytesArray[i] = signalDataBytes[i];
			}

		} else if (Com_SystemEndianness == COM_LITTLE_ENDIAN){
			/* Swap copying */
			uint8 i;
			for (i = 0; i < signalBufferSize; i++){
				signalDataBytesArray[(signalBufferSize - 1) - i] = signalDataBytes[i];
			}
		} else {
			/* TODO: ?*/
		}
		uint8 i;
		uint8 pduBufferByteEnd[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
        if (endianness == COM_BIG_ENDIAN){
            Com_BitPositionType startBitOffset = Com_GetByteOffset(bitPosition % 8);
			Com_WriteData(pduBufferByteEnd, pduSignalMask, signalDataBytesArray, signalBufferSize, startBitOffset, bitSize);
            uint8 *pduBufferBytes = ((uint8 *)pduBuffer) + (bitPosition/8);
            for (i = 0; i < 8; i++) {
                if(pduBufferByteEnd[i] != (pduBufferBytes[i]  & pduSignalMask[i])){
                    *dataChanged = TRUE;
                }
                pduBufferBytes[i] &= ~pduSignalMask[i];
                pduBufferBytes[i] |= pduBufferByteEnd[i];
            }

        } else {
            uint8 startBitOffset = 64 - ((bitPosition % 8) + bitSize); /* 8 bytes = 64 bit*/
            Com_WriteData(pduBufferByteEnd, pduSignalMask, signalDataBytesArray, signalBufferSize, startBitOffset, bitSize);
            uint8 *pduBufferBytes = ((uint8 *)pduBuffer) + (bitPosition / 8);
            /* TODO: Check bytes written and iterate through them only */
            for (i = 0; i < 8; i++){
                if(pduBufferByteEnd[7 - i] != (pduBufferBytes[i] & (pduSignalMask[7 - i]))){
                    *dataChanged = TRUE;
                }
                pduBufferBytes[i] &= ~pduSignalMask[7 - i];
                pduBufferBytes[i] |= pduBufferByteEnd[7 - i];
            }
        }
	}
	Irq_Restore(irq_state);
}

Com_BitPositionType Com_GetByteOffset(Com_BitPositionType BitNumber){
	uint8 byte = BitNumber / 8;
	Com_BitPositionType byteStartOffset = (Com_BitPositionType) (byte * 8u);
	Com_BitPositionType byteOffset = BitNumber % 8;
	return (Com_BitPositionType) (byteStartOffset + (7u - byteOffset));
}