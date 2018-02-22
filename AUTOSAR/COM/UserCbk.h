#ifndef USERCBK_H_
#define USERCBK_H_

/* Callback functions and Notifications */
Std_ReturnType Com_TriggerTransmit(PduIdType TxPduId, PduInfoType* PduInfoPtr); /*SID 0x41*/
void Com_RxIndication(PduIdType RxPduId, const PduInfoType* PduInfoPtr); /*SID 0x42*/
void Com_TpRxIndication(PduIdType id, Std_ReturnType result); /*SID 0x45*/
void Com_TxConfirmation(PduIdType TxPduId); /*SID 0x40*/
void Com_TpTxConfirmation(PduIdType id, Std_ReturnType result); /*SID 0x48*/
BufReq_ReturnType Com_StartOfReception(PduIdType id, const PduInfoType* info,PduLengthType TpSduLength, PduLengthType* bufferSizePtr); /*SID 0x46*/
BufReq_ReturnType Com_CopyRxData(PduIdType id, const PduInfoType* info, PduLengthType* bufferSizePtr); /*SID 0x44*/
BufReq_ReturnType Com_CopyRxData(PduIdType PduId, const PduInfoType* PduInfoPtr, PduLengthType* RxBufferSizePtr);
BufReq_ReturnType Com_CopyTxData(PduIdType id, const PduInfoType* info, RetryInfoType* retry, PduLengthType* availableDataPtr); /*SID 0x43*/

#endif
