#ifndef CANIF_CBK_H
#define CANIF_CBK_H

void CanIf_TxConfirmation(PduIdType canTxPduId);
void CanIf_RxIndication(const Can_HwType* Mailbox, const PduInfoType* PduInfoPtr);

#endif /*CANIF_CBK_H*/
