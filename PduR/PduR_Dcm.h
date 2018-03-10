#ifndef PDUR_DCM_H_
#define PDUR_DCM_H_

#include "PduR.h"

#if PDUR_ZERO_COST_OPERATION == STD_OFF

Std_ReturnType PduR_DcmTransmit(PduIdType DcmTxPduId, const PduInfoType* PduInfoPtr);

#endif

#endif /*PDUR_DCM_H_*/



