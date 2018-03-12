#ifndef PDUR_J1939TP_H_
#define PDUR_J1939TP_H_

#include "PduR.h"

#if PDUR_ZERO_COST_OPERATION == STD_OFF
void PduR_J1939TpTxConfirmation(PduIdType CanTpTxPduId, NotifResultType Result);
void PduR_J1939TpRxIndication(PduIdType id, NotifResultType Result);

/* autosar 4 api */
BufReq_ReturnType PduR_J1939TpCopyTxData(PduIdType id, PduInfoType* info, RetryInfoType* retry, PduLengthType* availableDataPtr);
BufReq_ReturnType PduR_J1939TpCopyRxData(PduIdType id, PduInfoType* info, PduLengthType* bufferSizePtr);
BufReq_ReturnType PduR_J1939TpStartOfReception(PduIdType id, PduLengthType TpSduLength, PduLengthType* bufferSizePtr);
#endif

#endif /* PDUR_CANTP_H_ */
