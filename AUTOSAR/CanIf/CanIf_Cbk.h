#ifndef CANIF_CBK_H
#define CANIF_CBK_H

void CanIf_TxConfirmation(PduIdType canTxPduId);
void CanIf_RxIndication(uint8 Hrh, Can_IdType CanId, uint8 CanDlc, const uint8 *CanSduPtr);

#endif /*CANIF_CBK_H*/
