#include "PduR.h"
#if defined(USE_DET)
#include "Det.h"
#endif
#include "debug.h"

#if (PDUR_ZERO_COST_OPERATION == STD_OFF) && (PDUR_SOAD_SUPPORT == STD_ON)

BufReq_ReturnType PduR_SoAdTpProvideRxBuffer(PduIdType dcmRxPduId, PduLengthType sduLength, PduInfoType **pduInfoPtr) {
    return PduR_ARC_ProvideRxBuffer(dcmRxPduId, sduLength, pduInfoPtr, 0x03);
}

void PduR_SoAdTpRxIndication(PduIdType dcmRxPduId, NotifResultType result) {
	PduR_ARC_TpRxIndication(dcmRxPduId, result, 0x04);
}

BufReq_ReturnType PduR_SoAdTpProvideTxBuffer(PduIdType dcmTxPduId, PduInfoType **pduInfoPtr, PduLengthType length)
{
	return PduR_ARC_ProvideTxBuffer(dcmTxPduId, pduInfoPtr, length, 0x03);
}

void PduR_SoAdTpTxConfirmation(PduIdType dcmTxPduId, NotifResultType Result)
{
	PduR_ARC_TxConfirmation(dcmTxPduId, Result, 0x0f);
}


/* PduR_SoAd interface API implementation */
void PduR_SoAdIfRxIndication(PduIdType RxPduId, const uint8* SduPtr) {
	PduInfoType PduInfo = {
		.SduDataPtr = (uint8 *)SduPtr
	};
	PduR_ARC_RxIndication(RxPduId, &PduInfo, 0x01);
}

void PduR_SoAdIfTxConfirmation(PduIdType ComTxPduId) {
	uint8 dummy = 0;
	PduR_ARC_TxConfirmation(ComTxPduId, dummy, 0x02);
}

void PduR_SoAdIfTriggerTransmit(PduIdType TxPduId, uint8 *SduPtr) {
	PduInfoType PduInfo = {
		.SduDataPtr = SduPtr
	};
	PduR_ARC_TriggerTransmit(TxPduId, &PduInfo, 0x10);
}

#endif
