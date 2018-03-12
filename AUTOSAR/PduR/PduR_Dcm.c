#include "PduR.h"

#if (PDUR_ZERO_COST_OPERATION == STD_OFF) && (PDUR_DCM_SUPPORT == STD_ON)

Std_ReturnType PduR_DcmTransmit(PduIdType DcmTxPduId, const PduInfoType* PduInfoPtr) {
	return PduR_ARC_Transmit(DcmTxPduId, PduInfoPtr, 0x16);
}

#endif
