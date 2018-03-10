#include "PduR.h"
#if defined(USE_DET)
#include "Det.h"
#endif
#include "debug.h"

#if (PDUR_ZERO_COST_OPERATION == STD_OFF) && (PDUR_CANTP_SUPPORT == STD_ON)

BufReq_ReturnType PduR_CanTpProvideRxBuffer(PduIdType CanTpRxPduId, PduLengthType TpSduLength, PduInfoType** PduInfoPtr) {
	return PduR_ARC_ProvideRxBuffer(CanTpRxPduId, TpSduLength, PduInfoPtr, 0x03);
}


void PduR_CanTpRxIndication(PduIdType CanTpRxPduId, NotifResultType Result) {
	PduR_ARC_TpRxIndication(CanTpRxPduId, Result, 0x04);
}

BufReq_ReturnType PduR_CanTpProvideTxBuffer(PduIdType CanTpTxPduId, PduInfoType** PduInfoPtr, uint16 Length) {
	return PduR_ARC_ProvideTxBuffer(CanTpTxPduId, PduInfoPtr, Length, 0x03);
}


void PduR_CanTpTxConfirmation(PduIdType CanTpTxPduId, NotifResultType Result) {
	PduR_ARC_TxConfirmation(CanTpTxPduId, Result, 0x0f);
}

#endif
