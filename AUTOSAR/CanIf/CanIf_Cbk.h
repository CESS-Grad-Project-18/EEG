#ifndef CANIF_CBK_H_
#define CANIF_CBK_H_

void CanIf_TxConfirmation(PduIdType canTxPduId);
void CanIf_RxIndication(uint8 Hrh, Can_IdType CanId, uint8 CanDlc, const uint8 *CanSduPtr);

void CanIf_ControllerBusOff(uint8 Controller);
void CanIf_SetWakeupEvent(uint8 Controller);

#endif /*CANIF_CBK_H_*/
