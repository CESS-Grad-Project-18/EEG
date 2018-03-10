#include "PduR.h"

#if (PDUR_ZERO_COST_OPERATION == STD_OFF) && (PDUR_COM_SUPPORT == STD_ON)

Std_ReturnType PduR_ComTransmit(PduIdType ComTxPduId, const PduInfoType* PduInfoPtr) {
	return PduR_ARC_Transmit(ComTxPduId, PduInfoPtr, 0x15);
}

#endif
