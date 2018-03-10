#ifndef PDUR_SOAD_H_
#define PDUR_SOAD_H_

#include "PduR.h"

#if PDUR_ZERO_COST_OPERATION == STD_OFF

/* SoAd acts as transport protocol module */
BufReq_ReturnType PduR_SoAdTpProvideRxBuffer(PduIdType dcmRxPduId, PduLengthType sduLength, PduInfoType **pduInfoPtr);
void PduR_SoAdTpRxIndication(PduIdType dcmRxPduId, NotifResultType result);
BufReq_ReturnType PduR_SoAdTpProvideTxBuffer(PduIdType dcmTxPduId, PduInfoType **pduInfoPtr, PduLengthType length);
void PduR_SoAdTpTxConfirmation(PduIdType dcmTxPduId, NotifResultType result);

/* SoAd acts as interface module */
void PduR_SoAdIfRxIndication(PduIdType RxPduId, const uint8* SduPtr);
void PduR_SoAdIfTxConfirmation(PduIdType ComTxPduId);
void PduR_SoAdIfTriggerTransmit(PduIdType TxPduId, uint8 *SduPtr);

#endif

#endif /* PDUR_SOAD_H_ */
