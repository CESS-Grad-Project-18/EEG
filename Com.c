#include "Com.h"
#include "Det.h"
#include "Com_MemMap.h"
#include "PduR_Com.h"
#include "SchM_Com.h"
#include "UserCbk.h"

const Com_ConfigType *ComConfig;
ComSignalEndianess_type Com_SystemEndianness;
static const uint32_t endian_test  = 0xdeadbeefU;


/* Startup and Control Services*/
void Com_Init(const Com_ConfigType * config){
	ComConfig = config;
	uint8 endian_byte = *(const uint8 *)&endian_test; /* Get last byte*/
	if(endian_byte == 0xef ){ 
		Com_SystemEndianness = COM_LITTLE_ENDIAN; 
	}
	else if(endian_byte == 0xde){ 
		Com_SystemEndianness = COM_BIG_ENDIAN;
	}
	else {
		Com_SystemEndianness = COM_OPAQUE;
		assert(0); /* Check */
	}
/* TODO: Implement */
} /*SID 0x01*/

void Com_DeInit(void){
/* TODO: Implement */
} /*SID 0x02*/

void Com_IpduGroupControl(Com_IpduGroupVector ipduGroupVector, boolean initialize){
/* TODO: Implement */
} /*SID 0x03*/

void Com_ReceptionDMControl(Com_IpduGroupVector ipduGroupVector){
/* TODO: Implement */
} /*SID 0x06*/

Com_StatusType Com_GetStatus(void){ 
	return ComConfig->ComStatus; /* Check */
/* TODO: Implement */
}/*SID 0x07, returns COM_INIT or COM_UNINIT*/

void Com_GetVersionInfo(Std_VersionInfoType* versioninfo){
/* TODO: Implement */
}/*SID 0x09, Version out*/

void Com_ClearIpduGroupVector(Com_IpduGroupVector ipduGroupVector){
/* TODO: Implement */
} /*SID 0x1c*/

void Com_SetIpduGroup(Com_IpduGroupVector ipduGroupVector, Com_IpduGroupIdType ipduGroupId, boolean bitval){
/* TODO: Implement */
} /*SID 0x1d */



/* Communication Services */
uint8 Com_SendSignal(Com_SignalIdType SignalId, const void* SignalDataPtr){
/* TODO: Implement */
} /*SID 0x0a*/

uint8 Com_SendDynSignal(Com_SignalIdType SignalId, const void* SignalDataPtr, uint16 Length){
/* TODO: Implement */
} /*SID 0x21*/

uint8 Com_ReceiveSignal(Com_SignalIdType SignalId, void* SignalDataPtr){
/* TODO: Implement */
} /*SID 0x0b*/

uint8 Com_ReceiveDynSignal(Com_SignalIdType SignalId, void* SignalDataPtr, uint16* Length){
/* TODO: Implement */
} /*SID 0x22*/

void Com_UpdateShadowSignal(Com_SignalIdType SignalId, const void* SignalDataPtr){
/* TODO: Implement */
} /*SID 0x0c*/

uint8 Com_SendSignalGroup(Com_SignalGroupIdType SignalGroupId){
/* TODO: Implement */
} /*SID 0x0d */

uint8 Com_ReceiveSignalGroup(Com_SignalGroupIdType SignalGroupId){
/* TODO: Implement */
} /*SID 0x0e*/

void Com_ReceiveShadowSignal(Com_SignalIdType SignalId, void* SignalDataPtr){
/* TODO: Implement */
} /*SID 0x0f*/

uint8 Com_SendSignalGroupArray(Com_SignalGroupIdType SignalGroupId, const uint8* SignalGroupArrayPtr){
/* TODO: Implement */
} /*SID 0x23*/

uint8 Com_ReceiveSignalGroupArray(Com_SignalGroupIdType SignalGroupId, uint8* SignalGroupArrayPtr){
/* TODO: Implement */
} /*SID 0x24*/

uint8 Com_InvalidateSignal(Com_SignalIdType SignalId){
/* TODO: Implement */
} /*SID 0x10*/

void Com_InvalidateShadowSignal(Com_SignalIdType SignalId){
/* TODO: Implement */
} /*SID 0x16*/

uint8 Com_InvalidateSignalGroup(Com_SignalGroupIdType SignalGroupId){
/* TODO: Implement */
} /*SID 0x1b*/

Std_ReturnType Com_TriggerIPDUSend(PduIdType PduId){
/* TODO: Implement */
} /*SID 0x17*/

Std_ReturnType Com_TriggerIPDUSendWithMetaData(PduIdType PduId, uint8* MetaData){
/* TODO: Implement */
} /*SID 0x28*/

void Com_SwitchIpduTxMode(PduIdType PduId, boolean Mode){
/* TODO: Implement */
} /*SID 0x27*/



/* Callback functions and Notifications */
Std_ReturnType Com_TriggerTransmit(PduIdType TxPduId, PduInfoType* PduInfoPtr){
/* TODO: Implement */
} /*SID 0x41*/

void Com_RxIndication(PduIdType RxPduId, const PduInfoType* PduInfoPtr){
/* TODO: Implement */
} /*SID 0x42*/

void Com_TpRxIndication(PduIdType id, Std_ReturnType result){
/* TODO: Implement */
} /*SID 0x45*/

void Com_TxConfirmation(PduIdType TxPduId){
/* TODO: Implement */
} /*SID 0x40*/

void Com_TpTxConfirmation(PduIdType id, Std_ReturnType result){
/* TODO: Implement */
} /*SID 0x48*/

BufReq_ReturnType Com_StartOfReception(PduIdType id, const PduInfoType* info,PduLengthType TpSduLength, PduLengthType* bufferSizePtr){
/* TODO: Implement */
} /*SID 0x46*/

BufReq_ReturnType Com_CopyRxData(PduIdType id, const PduInfoType* info, PduLengthType* bufferSizePtr){
/* TODO: Implement */
} /*SID 0x44*/

BufReq_ReturnType Com_CopyRxData(PduIdType PduId, const PduInfoType* PduInfoPtr, PduLengthType* RxBufferSizePtr){
/* TODO: Implement */
}
BufReq_ReturnType Com_CopyTxData(PduIdType id, const PduInfoType* info, RetryInfoType* retry, PduLengthType* availableDataPtr){
/* TODO: Implement */
} /*SID 0x43*/


/* Scheduled Functions*/
void Com_MainFunctionRx(void){
/* TODO: Implement */
} /*SID 0x18*/

void Com_MainFunctionTx(void){
/* TODO: Implement */
} /*SID 0x19*/

void Com_MainFunctionRouteSignals(void){
/* TODO: Implement */
} /*SID 0x1a*/
