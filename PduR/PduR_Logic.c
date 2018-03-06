/* -------------------------------- Arctic Core ------------------------------
 * Arctic Core - the open source AUTOSAR platform http://arccore.com
 *
 * Copyright (C) 2009  ArcCore AB <contact@arccore.com>
 *
 * This source code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by the
 * Free Software Foundation; See <http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * -------------------------------- Arctic Core ------------------------------*/

//lint -emacro(904,PDUR_VALIDATE_INITIALIZED,PDUR_VALIDATE_PDUPTR,PDUR_VALIDATE_PDUID) //904 PC-Lint exception to MISRA 14.7 (validate macros).
//lint -emacro(506,PDUR_VALIDATE_PDUPTR,PDUR_VALIDATE_PDUID) //PC-Lint exception Misra 13.7, 14.1 Allow configuration variables in boolean expression.
//lint -emacro(774,PDUR_VALIDATE_PDUPTR,PDUR_VALIDATE_PDUID) //PC-Lint exception Misra 13.7, 14.1 Allow configuration variables in boolean expression.





#include "PduR.h"

#include <string.h>
#include "debug.h"
#if defined(USE_DET)
#include "Det.h"
#endif
#if defined(USE_DEM)
#include "Dem.h"
#endif

#if PDUR_ZERO_COST_OPERATION == STD_OFF

#define PduRTpBuffer(_id) (&PduRConfig->TpBuffers[_id])
#define PduRTpRouteBuffer(_id) (PduRConfig->TpRouteBuffers[_id])

#define HAS_BUFFER_STATUS(_pduId, _status)  (_pduId < PDUR_N_TP_ROUTES_WITH_BUFFER && PduRTpRouteBuffer(_pduId) != NULL && PduRTpRouteBuffer(_pduId)->status == _status)
#define REPORT_BUFFER_ERROR(_serviceId) PDUR_DET_REPORTERROR(MODULE_ID_PDUR, PDUR_INSTANCE_ID, _serviceId, PDUR_E_BUFFER_ERROR);

BufReq_ReturnType PduR_ARC_AllocateUpRxBuffer(PduIdType PduId, PduInfoType** PduInfoPtr) {
	BufReq_ReturnType retVal = BUFREQ_BUSY;
	for (uint8 i = 0; i < PDUR_N_TP_BUFFERS; i++) {
		if (PduRTpBuffer(i)->status == PDUR_BUFFER_NOT_ALLOCATED_FROM_UP_MODULE) {
			PduRTpRouteBuffer(PduId) = PduRTpBuffer(i);
			PduRTpRouteBuffer(PduId)->pduInfoPtr = *PduInfoPtr;
			PduRTpRouteBuffer(PduId)->status = PDUR_BUFFER_ALLOCATED_FROM_UP_MODULE;
			retVal = BUFREQ_OK;
			break;
		}
	}
	return retVal;
}


BufReq_ReturnType PduR_ARC_AllocateRxBuffer(PduIdType PduId, PduLengthType TpSduLength) {
	BufReq_ReturnType retVal = BUFREQ_BUSY;
	for (uint8 i = 0; i < PDUR_N_TP_BUFFERS; i++) {
		if (PduRTpBuffer(i)->status == PDUR_BUFFER_FREE) {
			if (PduRTpBuffer(i)->bufferSize < TpSduLength) {
				retVal = BUFREQ_OVFL;
			} else {
				PduRTpRouteBuffer(PduId) = PduRTpBuffer(i);
				PduRTpBuffer(i)->pduInfoPtr->SduLength = TpSduLength;
				PduRTpRouteBuffer(PduId)->status = PDUR_BUFFER_RX_BUSY;
				retVal = BUFREQ_OK;
				break;
			}
		}
	}
	return retVal;
}

BufReq_ReturnType PduR_ARC_AllocateTxBuffer(PduIdType PduId, uint16 length) {
	BufReq_ReturnType retVal;
	if (PduRTpRouteBuffer(PduId)->status == PDUR_BUFFER_TX_READY) {
		if ((length >= PduRTpRouteBuffer(PduId)->pduInfoPtr->SduLength) || (length == 0)) {
			PduRTpRouteBuffer(PduId)->status = PDUR_BUFFER_TX_BUSY;
			PduRTpRouteBuffer(PduId)->nAcc = 0;
			retVal = BUFREQ_OK;
		} else {
			retVal = BUFREQ_NOT_OK;
		}
	} else if (PduRTpRouteBuffer(PduId)->status == PDUR_BUFFER_TX_BUSY) {
		retVal = BUFREQ_OK;

	} else {
		retVal = BUFREQ_BUSY;
	}
	return retVal;
}

BufReq_ReturnType PduR_ARC_ReleaseRxBuffer(PduIdType PduId) {
	BufReq_ReturnType retVal;
	if (PduId >= PDUR_N_TP_ROUTES_WITH_BUFFER) {
		retVal = BUFREQ_NOT_OK;
	} else if (PduRTpRouteBuffer(PduId) == NULL) {
		retVal = BUFREQ_OK;
	} else if (PduRTpRouteBuffer(PduId)->status == PDUR_BUFFER_ALLOCATED_FROM_UP_MODULE) {
		PduRTpRouteBuffer(PduId)->status = PDUR_BUFFER_NOT_ALLOCATED_FROM_UP_MODULE;
		retVal = BUFREQ_BUSY;
	} else if (PduRTpRouteBuffer(PduId)->status == PDUR_BUFFER_RX_BUSY) {
		PduRTpRouteBuffer(PduId)->status = PDUR_BUFFER_TX_READY;
		retVal = BUFREQ_BUSY;
	} else {
		retVal = BUFREQ_OK;
	}
	return retVal;
}

BufReq_ReturnType PduR_ARC_ReleaseTxBuffer(PduIdType PduId) {
	BufReq_ReturnType retVal = BUFREQ_NOT_OK;
	if (PduRTpRouteBuffer(PduId)->status == PDUR_BUFFER_TX_BUSY) {
		PduRTpRouteBuffer(PduId)->status = PDUR_BUFFER_FREE;
		PduRTpRouteBuffer(PduId)->nAcc = 0;
		PduRTpRouteBuffer(PduId) = NULL;
		retVal = BUFREQ_OK;
	}
	return retVal;
}

Std_ReturnType PduR_ARC_Transmit(PduIdType PduId, const PduInfoType* PduInfo, uint8 serviceId) {
	PDUR_VALIDATE_INITIALIZED(serviceId,E_NOT_OK);
	PDUR_VALIDATE_PDUPTR(serviceId, PduInfo, E_NOT_OK);
	PDUR_VALIDATE_PDUID(serviceId, PduId, E_NOT_OK);

	Std_ReturnType retVal = E_OK;
	const PduRRoutingPath_type *route = PduRConfig->RoutingPaths[PduId];
	for (uint8 i = 0; route->PduRDestPdus[i] != NULL; i++) {
		const PduRDestPdu_type * destination = route->PduRDestPdus[i];

		retVal |= PduR_ARC_RouteTransmit(destination, PduInfo);
	}
	return retVal;
}

void PduR_ARC_RxIndicationTT(const PduRDestPdu_type * destination, const PduInfoType *PduInfo, uint16 BufferLength) {
	Std_ReturnType retVal = E_OK;

	uint16 bytesToCopy = 0;
	if (PduInfo->SduLength > BufferLength){ bytesToCopy = BufferLength;}
	else {bytesToCopy = PduInfo->SduLength;}

	if (!memcpy(destination->TxBufferRef, PduInfo->SduDataPtr, bytesToCopy)){ retVal |= E_NOT_OK;}
	retVal |= PduR_ARC_RouteTransmit(destination, PduInfo);

	if (retVal != E_OK) {
#if defined(USE_DEM)
		Dem_ReportErrorStatus(PDUR_E_PDU_INSTANCE_LOST, DEM_EVENT_STATUS_FAILED);
#endif
	}
	/*
	// This is a gateway request which uses trigger transmit data provision. PDUR255
	if (destination->TxBufferRef->TxConfP) { // Transfer confirmation pending.
		// Enqueue the new I-PDU. This will flush the buffer if it is full according to the buffer specification.
		PduR_BufferQueue(destination->TxBufferRef, PduInfo->SduDataPtr);
		// TODO report PDUR_E_PDU_INSTANCE_LOST to DEM if needed.
	}

	if (destination->TxBufferRef->TxConfP) { // No transfer confirmation pending (anymore).
		uint8 val[PduInfo->SduLength];
		PduInfoType NewPduInfo = {
			.SduDataPtr = val,
			.SduLength = PduInfo->SduLength
		};
		PduR_BufferDeQueue(destination->TxBufferRef, val);
		PduR_BufferQueue(destination->TxBufferRef, PduInfo->SduDataPtr);
		retVal = PduR_ARC_RouteTransmit(destination, &NewPduInfo);
		if (retVal == E_OK) {
			setTxConfP(destination->TxBufferRef);
		}
	}
	*/
}

void PduR_ARC_RxIndicationDirect(const PduRDestPdu_type * destination, const PduInfoType *PduInfo) {
	Std_ReturnType retVal = PduR_ARC_RouteTransmit(destination, PduInfo);
	if (retVal != E_OK) {
#if defined(USE_DEM)
		Dem_ReportErrorStatus(PDUR_E_PDU_INSTANCE_LOST, DEM_EVENT_STATUS_FAILED);
#endif
	}
}

static void PduR_ARC_RxIndicationWithUpBuffer(PduIdType PduId, const PduInfoType* PduInfo, uint8 serviceId) {
	const PduRRoutingPath_type *route = PduRConfig->RoutingPaths[PduId];
	const PduRDestPdu_type * destination = route->PduRDestPdus[0];

	// Save current buffer
	PduInfoType *upBuffer = PduRTpRouteBuffer(PduId)->pduInfoPtr;
	BufReq_ReturnType retVal = PduR_ARC_ReleaseRxBuffer(PduId);
	if (retVal != BUFREQ_BUSY) {
		REPORT_BUFFER_ERROR(serviceId);
		return;
	}

	// Get a new PduR buffer
	retVal = PduR_ARC_AllocateRxBuffer(PduId, upBuffer->SduLength);
	if (retVal != BUFREQ_OK) {
		REPORT_BUFFER_ERROR(serviceId);
		return;
	}

	// Copy the data from old buffer to new.
	memcpy(PduRTpRouteBuffer(PduId)->pduInfoPtr->SduDataPtr, upBuffer->SduDataPtr, PduRTpRouteBuffer(PduId)->pduInfoPtr->SduLength);

	// notify upper module
	PduR_ARC_RouteRxIndication(destination, PduInfo);

	// Then first transmit to all other destinations.
	for (uint8 i = 1; route->PduRDestPdus[i] != NULL; i++) {
		const PduRDestPdu_type * d = route->PduRDestPdus[i];
		Std_ReturnType status = PduR_ARC_RouteTransmit(d, PduRTpRouteBuffer(PduId)->pduInfoPtr);
		if(status!=E_OK){
			// TODO: do error reporting?
		}
	}

}

void PduR_ARC_TpRxIndication(PduIdType PduId, NotifResultType Result, uint8 serviceId) {
	PDUR_VALIDATE_INITIALIZED(serviceId);
	PDUR_VALIDATE_PDUID(serviceId, PduId);

	PduInfoType PduInfo = {
		.SduDataPtr = &Result,
		.SduLength = 0 // To fix PC-Lint 785
	};

	if (Result != NTFRSLT_OK) {
		// There was an error in the lower layer while receiving the PDU.
		// Release any buffers and notify upper layers
		PduR_ARC_ReleaseRxBuffer(PduId);
		for (uint8 i = 0; PduRConfig->RoutingPaths[PduId]->PduRDestPdus[i] != NULL; i++) {
			const PduRDestPdu_type * destination = PduRConfig->RoutingPaths[PduId]->PduRDestPdus[i];
			if (PduR_IsUpModule(destination->DestModule)) {
				PduR_ARC_RouteRxIndication(destination, &PduInfo);
			}
		}

	} else {
		PduR_ARC_RxIndication(PduId, &PduInfo, serviceId);
	}
}

void PduR_ARC_RxIndication(PduIdType PduId, const PduInfoType* PduInfo, uint8 serviceId) {
	PDUR_VALIDATE_INITIALIZED(serviceId);
	PDUR_VALIDATE_PDUPTR(serviceId, PduInfo);
	PDUR_VALIDATE_PDUID(serviceId, PduId);

	const PduRRoutingPath_type *route = PduRConfig->RoutingPaths[PduId];

	/* Do not route incoming PDUs out again unless specified */
    if (route != NULL && !PduR_IsLoModule(route->SrcModule)) {
    	return;
    }

	if (HAS_BUFFER_STATUS(PduId, PDUR_BUFFER_ALLOCATED_FROM_UP_MODULE)) {
		PduR_ARC_RxIndicationWithUpBuffer(PduId, PduInfo, serviceId);

	} else {

		for (uint8 i = 0; route->PduRDestPdus[i] != NULL; i++) {
			const PduRDestPdu_type * destination = route->PduRDestPdus[i];

			if (PduR_IsUpModule(destination->DestModule)) {
				PduR_ARC_RouteRxIndication(destination, PduInfo);

			} else if (PduR_IsLoModule(destination->DestModule)) {

				if (PduR_IsTpModule(destination->DestModule)) { // TP Gateway
					if (HAS_BUFFER_STATUS(PduId, PDUR_BUFFER_RX_BUSY)) {
						// Transmit previous rx buffer
						Std_ReturnType status = PduR_ARC_RouteTransmit(destination, PduRTpRouteBuffer(PduId)->pduInfoPtr);
						if(status!=E_OK){
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

	PduR_ARC_ReleaseRxBuffer(PduId);
}

void PduR_ARC_TxConfirmation(PduIdType PduId, uint8 result, uint8 serviceId) {
	PDUR_VALIDATE_INITIALIZED(serviceId);
	PDUR_VALIDATE_PDUID(serviceId, PduId);

	const PduRRoutingPath_type *route = PduRConfig->RoutingPaths[PduId];

	if (PduR_IsUpModule(route->SrcModule)) {
		PduR_ARC_RouteTxConfirmation(route, result);

	} else if (PduR_IsLoModule(route->SrcModule) && HAS_BUFFER_STATUS(PduId, PDUR_BUFFER_TX_BUSY)) {
		PduRTpRouteBuffer(PduId)->nAcc++;

		uint8 nDests = 0;
		for (uint8 i = 0; route->PduRDestPdus[i] != NULL; i++) {
			if (!PduR_IsUpModule(route->PduRDestPdus[i]->DestModule)) nDests++;
		}

		if (PduRTpRouteBuffer(PduId)->nAcc >= nDests) {
			BufReq_ReturnType status = PduR_ARC_ReleaseTxBuffer(PduId);
			if (status != BUFREQ_OK) {
				REPORT_BUFFER_ERROR(serviceId);
			}
		}
	} else {
		// Do nothing
	}
}

Std_ReturnType PduR_ARC_TriggerTransmit(PduIdType PduId, PduInfoType* PduInfo, uint8 serviceId) {
	/*lint -esym(613,PduInfo)*/ /* PC-Lint 613 misunderstanding: PduInfo is not null since it is validated in PDUR_VALIDATE_PDUPTR */
	PDUR_VALIDATE_INITIALIZED(serviceId, E_NOT_OK);
	PDUR_VALIDATE_PDUPTR(serviceId, PduInfo, E_NOT_OK);
	PDUR_VALIDATE_PDUID(serviceId, PduId, E_NOT_OK);

	Std_ReturnType retVal = E_OK;
	const PduRRoutingPath_type *route = PduRConfig->RoutingPaths[PduId];
	const PduRDestPdu_type * destination = route->PduRDestPdus[0];

	if (PduR_IsUpModule(route->SrcModule)) {
		retVal |= PduR_ARC_RouteTriggerTransmit(route, PduInfo);

	} else if (PduR_IsLoModule(route->SrcModule)) {
		if (destination->DataProvision == PDUR_TRIGGER_TRANSMIT) {
			uint16 bytesToCopy = 0;
			if (PduInfo->SduLength > route->SduLength){ bytesToCopy = route->SduLength;}
			else {bytesToCopy = PduInfo->SduLength;}

			if (!memcpy((void *)PduInfo->SduDataPtr, (void *)destination->TxBufferRef, bytesToCopy)) {
				retVal = E_NOT_OK;
			}
		}
	} else {
		// TODO: Do nothing???? or retVal = E_OK or E_NOT_OK?
	}
	return retVal;
}

BufReq_ReturnType PduR_ARC_ProvideRxBuffer(PduIdType PduId, PduLengthType TpSduLength, PduInfoType** PduInfoPtr, uint8 serviceId) {
	PDUR_VALIDATE_INITIALIZED(serviceId,BUFREQ_NOT_OK);
	PDUR_VALIDATE_PDUPTR(serviceId, PduInfoPtr, BUFREQ_NOT_OK);
	PDUR_VALIDATE_PDUID(serviceId, PduId, BUFREQ_NOT_OK);

	BufReq_ReturnType retVal;
	const PduRRoutingPath_type *route = PduRConfig->RoutingPaths[PduId];
	const PduRDestPdu_type * destination = route->PduRDestPdus[0];

	if (PduR_IsUpModule(destination->DestModule)) {
		retVal = PduR_ARC_RouteProvideRxBuffer(destination, TpSduLength, PduInfoPtr);

		if (route->PduRDestPdus[1] != NULL && retVal == BUFREQ_OK && PduR_IsTpModule(route->PduRDestPdus[1]->DestModule)) {
			// We have multiple destinations. Make sure they use the rx buffer provided by the upper module.
			retVal = PduR_ARC_AllocateUpRxBuffer(PduId, PduInfoPtr);
		}

	} else if (PduR_IsLoModule(destination->DestModule)) {
		if (PduR_ARC_ReleaseRxBuffer(PduId) == BUFREQ_BUSY) {
			// Transmit previous rx buffer
			Std_ReturnType status=PduR_ARC_RouteTransmit(destination, PduRTpRouteBuffer(PduId)->pduInfoPtr);
			if(status!=E_OK){
			// TODO: do something?
			}
		}

		retVal = PduR_ARC_AllocateRxBuffer(PduId, TpSduLength);
		if (retVal == BUFREQ_OK) {
			/*lint -esym(613,PduInfoPtr)*/ /* PC-Lint 613 misunderstanding: PduInfoPtr is not null since it is validated in PDUR_VALIDATE_PDUPTR */
			*PduInfoPtr = PduRTpRouteBuffer(PduId)->pduInfoPtr;
		}
	} else {
		retVal = BUFREQ_NOT_OK;
	}
	if (retVal != BUFREQ_OK) REPORT_BUFFER_ERROR(serviceId);
	return retVal;
}

BufReq_ReturnType PduR_ARC_ProvideTxBuffer(PduIdType PduId, PduInfoType** PduInfoPtr, uint16 Length, uint8 serviceId) {
	PDUR_VALIDATE_INITIALIZED(serviceId,BUFREQ_NOT_OK);
	PDUR_VALIDATE_PDUPTR(serviceId, PduInfoPtr, BUFREQ_NOT_OK);
	PDUR_VALIDATE_PDUID(serviceId, PduId, BUFREQ_NOT_OK);

	BufReq_ReturnType retVal;
	const PduRRoutingPath_type *route = PduRConfig->RoutingPaths[PduId];

	if (PduR_IsUpModule(route->SrcModule)) {
		retVal = PduR_ARC_RouteProvideTxBuffer(route, Length, PduInfoPtr);

	} else if (PduR_IsLoModule(route->SrcModule)) {
		retVal = PduR_ARC_AllocateTxBuffer(PduId, Length);
		if (retVal == BUFREQ_OK) {
			/*lint -esym(613,PduInfoPtr)*/ /* PC-Lint 613 misunderstanding: PduInfoPtr is not null since it is validated in PDUR_VALIDATE_PDUPTR */
			*PduInfoPtr = PduRTpRouteBuffer(PduId)->pduInfoPtr;
		}
	} else {
		retVal = BUFREQ_NOT_OK;
	}
	return retVal;
}



#endif
