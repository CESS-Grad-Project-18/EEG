#ifndef PDUR_IPDUM_H_
#define PDUR_IPDUM_H_

#include "PduR.h"

#if PDUR_ZERO_COST_OPERATION == STD_OFF

Std_ReturnType PduR_IpdumTransmit(PduIdType IpdumTxPduId, const PduInfoType *PduInfoPtr); /* SID: 0x19 */
void PduR_IpdumTxConfirmation(PduIdType IpdumLoTxPduId) /* SID: 0x1A */
void PduR_IpdumRxIndication(PduIdType IpdumLoRxPduId, const uint8 *IpdumSduPtr); /* SID: 0x1B */

#endif

#endif /* PDUR_IPDUM_H_ */
