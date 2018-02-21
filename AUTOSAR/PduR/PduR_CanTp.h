#ifndef PDUR_CANTP_H_
#define PDUR_CANTP_H_

#include "PduR.h"

#if PDUR_ZERO_COST_OPERATION == STD_OFF

BufReq_ReturnType PduR_CanTpProvideRxBuffer(PduIdType CanTpRxPduId, PduLengthType TpSduLength, PduInfoType **PduInfoPtr); /* SID: 0x03 */
void PduR_CanTpRxIndication(PduIdType CanTpRxPduId, NotifResultType Result); /* SID: 0x04 */
BufReq_ReturnType PduR_CanTpProvideTxBuffer(PduIdType CanTpTxPduId, PduInfoType **PduInfoPtr, uint16 Length); /* SID: 0x05 */
void PduR_CanTpTxConfirmation(PduIdType CanTpTxPduId, NotifResultType Result); /* SID: 0x06*/

#endif

#endif /* PDUR_CANTP_H_ */
