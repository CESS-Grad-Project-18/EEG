#include <stdlib.h>
#include <string.h>
#include "PduR.h"
#include "../COM/Com.h"
#include "../CanIf/CanIf.h"
#include "../COM/PduR_Com.h"
#include "../CanIf/PduR_CanIf.h"
#include "PduR_Types.h"

/*      void Det_ReportError(ModuleId, ApiId, ErrorId) */

/* The state of the PDU router. */


Std_ReturnType PduR_RouteTransmit(const PduRDestPdu *Pdu, const PduInfoType *pduInfo) {
	int err = 0;
	Std_ReturnType retVal = E_NOT_OK;
	switch (Pdu->DestPduRef->ComPduIdRef->IPduOutgoingId) {
	case 0:
		retVal = CanIf_Transmit(Pdu->DestPduRef->ComPduIdRef->IPduOutgoingId, pduInfo);
		break;
	case 1:
		Com_RxIndication(Pdu->DestPduRef->ComPduIdRef->IPduOutgoingId, pduInfo);
		break;
	default:
		retVal = E_NOT_OK;
		break;
	}
	if(err){
		/* TODO: Error reporting here. */
	}
	return retVal;
}

void PduR_RouteTriggeredTrasmit(const PduRDestPdu *Pdu, const PduInfoType *pduInfo) {
	/* @req PDUR160 */
	/* The PDU router module shall transfer an I-PDU without modification in a consistent manner from the source module to the dest module */
	/* @req PDUR661 */
	/* PDUR shall module shall copy the return value from the Com_TriggerTransmit to the lower layer module */
	Std_ReturnType ret = E_OK;
	if(!memcpy(Pdu->DestPduRef->ComPduIdRef->ComIPduDataPtr, pduInfo->SduDataPtr, pduInfo->SduLength)){ /* TODO: check */
		ret |= E_NOT_OK;
	}
	PduR_RouteTransmit(Pdu, pduInfo);
	if(ret != E_OK){
		Det_ReportError(PDUR_E_PDU_INSTANCE_LOST);
	}
}

PduR_StateType PduRState = PDUR_UNINIT;


const PduR_PBConfigType * PduRConfig;


/* Initializes the PDU Router. */
void PduR_Init (const PduR_PBConfigType* ConfigPtr) {
	boolean error = FALSE;
	/* Make sure the PDU Router is uninitialized. If not,  raise an error. */
	if (PduRState != PDUR_UNINIT) {
		// Raise error and return.
		Det_ReportError(PDUR_MODULE_ID, 0x00, PDUR_E_INVALID_REQUEST);
	} else if (ConfigPtr == NULL) {
		Det_ReportError(PDUR_MODULE_ID, 0x00, PDUR_E_CONFIG_PTR_INVALID);
	}else if(error) { /* Read error condition */
		PduRConfig = ConfigPtr;
		PduRState = PDUR_REDUCED;
		//Dem_ReportErrorStatus(PDUR_E_INIT_FAILED, otherParam); /* TODO: Implement or not */
	} else {
		PduRConfig = ConfigPtr;
		PduRState = PDUR_ONLINE;
	}

}


Std_ReturnType PduR_ComTransmit(PduIdType ComTxPduId, const PduInfoType *PduInfoPtr) {
	/* @req PDUR629 */
	/* I-PDU shall not be buffered in the PDU router module in case of PDU transmission from a source upper layer module*/
	/* @req PDUR218 */
	/* If the I-PDU ID represents a group of PDUS and one transmit request returns successfully, it shall return E_OK */
	/* @req PDUR745 */
	/* If the I-PDU is transmitted by an upper layer module the PDU router module shall not check the length of the I-PDU */
	/* @req PDUR625 */
	/* When source upper layer module callse PduR_ComTransmit, tge PDY router shall call CanIf_Transmit for each dest comm*/
	uint8 i;
	Std_ReturnType retVal = E_OK;
	const PduRRoutingPath *route = &PduRConfig->RoutingTable->PduRRoutingPath[ComTxPduId];
	for (i = 0; route->PduRDestPdu[i] != NULL; i++) {
		const PduRDestPdu * DestPdu = &route->PduRDestPdu[i];
		retVal |= PduR_RouteTransmit(DestPdu, PduInfoPtr);
	}
	return retVal;
}

void PduR_CanIfRxIndication(PduIdType PduId, const PduInfoType* PduInfo){
	/* @req PDUR164 */
	/* @req PDUR161 */
	/* @req PDUR303 */
	/* @req PDUR306 */
	/* @req PDUR783 */
	/* @req PDUR683 */
	uint8 i;
	const PduRRoutingPath *route = &PduRConfig->RoutingTable->PduRRoutingPath[PduId];
	for (i = 0; route->PduRDestPdu[i] != NULL; i++) {
		const PduRDestPdu * DestPdu = &route->PduRDestPdu[i];
		if(DestPdu->DestPduRef->ComPduIdRef->IPduOutgoingId == 0){
			if(DestPdu->DataProvision == PDUR_DIRECT){
				PduR_RouteTransmit(DestPdu, PduInfo);
			} else if (DestPdu->DataProvision == PDUR_TRIGGER_TRANSMIT){
				PduR_RouteTriggeredTrasmit(DestPdu, PduInfo);
			}

		}
	}
}

void PduR_CanIfTxConfirmation(PduIdType TxPduId){
	/* @req PDUR627 */
	uint8 i;
	const PduRRoutingPath *route = &PduRConfig->RoutingTable->PduRRoutingPath[TxPduId];
	for (i = 0; route->PduRSrcPdu[i] != NULL; i++) {
		const PduRSrcPdu *SrcPdu = &route->PduRSrcPdu[i];
	}
	/* TODO: Continue */
}