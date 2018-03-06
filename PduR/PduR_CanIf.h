#ifndef PDUR_CANIF_H_
#define PDUR_CANIF_H_

#include "PduR.h"

#if PDUR_ZERO_COST_OPERATION == STD_OFF

/* CAN Interface functions */
void PduR_CanIfRxIndication(PduIdType CanRxPduId, const uint8* CanSduPtr); /* SID: 0x01 */
void PduR_CanIfTxConfirmation(PduIdType CanTxPduId); /* SID: 0x02 */

#endif

#endif /* PDUR_CANIF_H_ */
