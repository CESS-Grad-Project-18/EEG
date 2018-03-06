#include "PduR.h"

#if (PDUR_ZERO_COST_OPERATION == STD_OFF) && (PDUR_CANIF_SUPPORT == STD_ON)

void PduR_CanIfRxIndication(PduIdType CanRxPduId, const uint8* CanSduPtr) {
	/* PduR_ARC_RxIndication(CanRxPduId, CanSduPtr, 0x01); */
	/* (PduIdType PduId, const PduInfoType* PduInfo, uint8 serviceId)*/
	const PduRRoutingPath_type *route;
	uint8 i;
	PDUR_VALIDATE_INITIALIZED(0x01,);
	PDUR_VALIDATE_PDUPTR(0x01, CanSduPtr,);
	PDUR_VALIDATE_PDUID(0x01, CanRxPduId,);

	route = PduRConfig->RoutingPaths[CanRxPduId];

	for (i = 0; route->PduRDestPdus[i] != NULL; i++) {
		const PduRDestPdu_type * destination = route->PduRDestPdus[i];

		if (PduR_IsUpModule(destination->DestModule)) {
			PduR_ARC_RouteRxIndication(destination, PduInfo);

		} else if (PduR_IsLoModule(destination->DestModule)) {

			if (PduR_IsTpModule(destination->DestModule)) { // TP Gateway
				if (PduR_ARC_ReleaseRxBuffer(PduId) == BUFREQ_BUSY) {
					// Transmit previous rx buffer
					Std_ReturnType status = PduR_ARC_RouteTransmit(destination, PduRTpRouteBuffer(PduId)->pduInfoPtr);
					if(status != E_OK){
						// TODO: do error reporting?
					}
				}

			} else if (destination->DataProvision == PDUR_TRIGGER_TRANSMIT) {
				PduR_ARC_RxIndicationTT(destination, PduInfo, route->SduLength);

			} else if (destination->DataProvision == PDUR_DIRECT) {
				PduR_ARC_RxIndicationDirect(destination, PduInfo);

			} else {
				// Do nothing
			}
		} else {
			// Do nothing
		}
	}
}
}

void PduR_CanIfTxConfirmation(PduIdType CanTxPduId) {
	uint8 dummy = 0;
	PduR_ARC_TxConfirmation(CanTxPduId,dummy,0x02);
}

#endif
