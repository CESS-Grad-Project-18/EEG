#ifndef PDUR_CANIF_H
#define PDUR_CANIF_H

#include "../PduR/PduR.h"

void PduR_CanIfRxIndication(PduIdType PduId, const PduInfoType* PduInfo); /* SID: 0x01 */
void PduR_CanIfTxConfirmation(PduIdType TxPduId); /* SID: 0x02 */

#endif /* PDUR_CANIF_H */
