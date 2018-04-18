#include <stdlib.h>
#include <string.h>
#if defined(USE_DET)
#include "Det.h"
#endif
#if defined(USE_DEM)
#include "Dem.h"
#endif
#include "PduR.h"
#include "../COM/Com.h"
#include "../CanIf/CanIf.h"
#include "../COM/PduR_Com.h"
#include "../CanIf/PduR_CanIf.h"

/*      void Det_ReportError(ModuleId, ApiId, ErrorId) */

/* The state of the PDU router. */


Std_ReturnType PduR_RouteTransmit(const PduRDestPdu_type *destination, const PduInfoType *pduInfo) {
	int err = 0;
	Std_ReturnType retVal = E_NOT_OK;
	switch (destination->DestModule) {
	case PDUR_CANIF:
		retVal = CanIf_Transmit(destination->DestPduId, pduInfo);
		break;
	case PDUR_COM:
		Com_RxIndication(destination->DestPduId, pduInfo);
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

	/* Make sure the PDU Router is uninitialized. If not,  raise an error. */
	if (PduRState != PDUR_UNINIT) {
		// Raise error and return.
		Det_ReportError(MODULE_ID_PDUR, PDUR_INSTANCE_ID, 0x00, PDUR_E_INVALID_REQUEST);
	} else if (ConfigPtr == NULL) {
		Det_ReportError(MODULE_ID_PDUR, PDUR_INSTANCE_ID, 0x00, PDUR_E_CONFIG_PTR_INVALID);
	}else if(ERROR) { /* Read error condition */
		PduRConfig = ConfigPtr;
		PduRState = PDUR_REDUCED;
		Dem_ReportErrorStatus(PDUR_E_INIT_FAILED, otherParam); /* TODO: Implement or not */
	}
	} else {
		PduRConfig = ConfigPtr;
		PduRState = PDUR_ONLINE;
	}

}

uint32 PduR_GetConfigurationId (void) {
	return PduRConfig->PduRConfigurationId;
}


Std_ReturnType PduR_ComTransmit(PduIdType ComTxPduId, const PduInfoType *PduInfoPtr) {
	Std_ReturnType retVal = E_OK;
	const PduRRoutingPath_type *route = PduRConfig->RoutingPaths[PduId];
	for (uint8 i = 0; route->PduRDestPdus[i] != NULL; i++) {
		const PduRDestPdu_type * destination = route->PduRDestPdus[i];
		retVal |= PduR_RouteTransmit(destination, PduInfo);
	}
	return retVal;
}