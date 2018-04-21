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
	uint8 i;
	Std_ReturnType retVal = E_OK;
	const PduRRoutingPath *route = &PduRConfig->RoutingTable->PduRRoutingPath[ComTxPduId];
	for (i = 0; route->PduRDestPdu[i] != NULL; i++) {
		const PduRDestPdu * DestPdu = &route->PduRDestPdu[i];
		retVal |= PduR_RouteTransmit(DestPdu, PduInfoPtr);
	}
	return retVal;
}