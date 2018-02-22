#ifndef COM_H_
#define COM_H_

/*#include "Com_Types.h"*/
#include "ComStack_Types.h"


#define COM_SW_MAJOR_VERSION   1
#define COM_SW_MINOR_VERSION   2
#define COM_SW_PATCH_VERSION   0

#include "Com_Cfg.h"
/*#include "Com_Types.h"
#include "Com_PbCfg.h"
#include "Com_Internal.h
#include "Com_Com.h"
#include "Com_Sched.h"*/

void Com_Init(const Com_ConfigType * config); /*SID 0x01*/
void Com_DeInit(void); /*SID 0x02*/
void Com_IpduGroupControl(Com_IpduGroupVector ipduGroupVector, boolean initialize); /*SID 0x03*/
void Com_ReceptionDMControl(Com_IpduGroupVector ipduGroupVector); /*SID 0x06*/
Com_StatusType Com_GetStatus(void) /*SID 0x07, returns COM_INIT or COM_UNINIT*/
void Com_GetVersionInfo(Std_VersionInfoType* versioninfo) /*SID 0x09, Version out*/
void Com_IpduGroupStart(Com_PduGroupIdType IpduGroupId, boolean Initialize);
void Com_IpduGroupStop(Com_PduGroupIdType IpduGroupId);


BufReq_ReturnType Com_CopyTxData(PduIdType PduId, PduInfoType* PduInfoPtr, RetryInfoType* RetryInfoPtr, PduLengthType* TxDataCntPtr);
BufReq_ReturnType Com_CopyRxData(PduIdType PduId, const PduInfoType* PduInfoPtr, PduLengthType* RxBufferSizePtr);
BufReq_ReturnType Com_StartOfReception(PduIdType ComRxPduId, PduLengthType TpSduLength, PduLengthType* RxBufferSizePtr);
void Com_TpRxIndication(PduIdType PduId, NotifResultType Result);
void Com_TpTxConfirmation(PduIdType PduId, NotifResultType Result);


extern ComSignalEndianess_type Com_SystemEndianness;

#define COM_BUSY 0x81
#define COM_SERVICE_NOT_AVAILABLE 0x80
#endif /*COM_H_*/
