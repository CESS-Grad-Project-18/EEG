#ifndef PDUR_COM_H_
#define PDUR_COM_H_

#include "PduR.h"

#if PDUR_ZERO_COST_OPERATION == STD_OFF

Std_ReturnType PduR_ComTransmit(PduIdType ComTxPduId, const PduInfoType* PduInfoPtr);

#endif

#endif /* PDUR_COM_H_ */
