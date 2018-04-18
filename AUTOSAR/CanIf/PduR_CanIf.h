#ifndef PDUR_CANIF_H
#define PDUR_CANIF_H

#include "../PduR/PduR.h"

void PduR_CanIfRxIndication(PduIdType CanRxPduId, const uint8* CanSduPtr); /* SID: 0x01 */
void PduR_CanIfTxConfirmation(PduIdType CanTxPduId); /* SID: 0x02 */

#endif /* PDUR_CANIF_H */
