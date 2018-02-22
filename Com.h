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


/* Startup and Control Services*/
void Com_Init(const Com_ConfigType * config); /*SID 0x01*/
void Com_DeInit(void); /*SID 0x02*/
void Com_IpduGroupControl(Com_IpduGroupVector ipduGroupVector, boolean initialize); /*SID 0x03*/
void Com_ReceptionDMControl(Com_IpduGroupVector ipduGroupVector); /*SID 0x06*/
Com_StatusType Com_GetStatus(void) /*SID 0x07, returns COM_INIT or COM_UNINIT*/
void Com_GetVersionInfo(Std_VersionInfoType* versioninfo) /*SID 0x09, Version out*/
void Com_ClearIpduGroupVector(Com_IpduGroupVector ipduGroupVector); /*SID 0x1c*/
void Com_SetIpduGroup(Com_IpduGroupVector ipduGroupVector, Com_IpduGroupIdType ipduGroupId, boolean bitval); /*SID 0x1d */



/* Communication Services */
uint8 Com_SendSignal(Com_SignalIdType SignalId, const void* SignalDataPtr); /*SID 0x0a*/
uint8 Com_SendDynSignal(Com_SignalIdType SignalId, const void* SignalDataPtr, uint16 Length); /*SID 0x21*/
uint8 Com_ReceiveSignal(Com_SignalIdType SignalId, void* SignalDataPtr); /*SID 0x0b*/
uint8 Com_ReceiveDynSignal(Com_SignalIdType SignalId, void* SignalDataPtr, uint16* Length); /*SID 0x22*/
void Com_UpdateShadowSignal(Com_SignalIdType SignalId, const void* SignalDataPtr); /*SID 0x0c*/
uint8 Com_SendSignalGroup(Com_SignalGroupIdType SignalGroupId); /*SID 0x0d */
uint8 Com_ReceiveSignalGroup(Com_SignalGroupIdType SignalGroupId); /*SID 0x0e*/
void Com_ReceiveShadowSignal(Com_SignalIdType SignalId, void* SignalDataPtr); /*SID 0x0f*/
uint8 Com_SendSignalGroupArray(Com_SignalGroupIdType SignalGroupId, const uint8* SignalGroupArrayPtr); /*SID 0x23*/
uint8 Com_ReceiveSignalGroupArray(Com_SignalGroupIdType SignalGroupId, uint8* SignalGroupArrayPtr); /*SID 0x24*/
uint8 Com_InvalidateSignal(Com_SignalIdType SignalId) /*SID 0x10*/
void Com_InvalidateShadowSignal(Com_SignalIdType SignalId) /*SID 0x16*/
uint8 Com_InvalidateSignalGroup(Com_SignalGroupIdType SignalGroupId); /*SID 0x1b*/
Std_ReturnType Com_TriggerIPDUSend(PduIdType PduId); /*SID 0x17*/
Std_ReturnType Com_TriggerIPDUSendWithMetaData(PduIdType PduId, uint8* MetaData); /*SID 0x28*/
void Com_SwitchIpduTxMode(PduIdType PduId, boolean Mode); /*SID 0x27*/



extern ComSignalEndianess_type Com_SystemEndianness;

#define COM_BUSY 0x81
#define COM_SERVICE_NOT_AVAILABLE 0x80
#endif /*COM_H_*/
