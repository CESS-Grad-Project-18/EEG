#ifndef COM_H_
#define COM_H_

#include "Com_Cfg.h"
#include "ComStack_Types.h"


#define COM_SW_MAJOR_VERSION   1
#define COM_SW_MINOR_VERSION   2
#define COM_SW_PATCH_VERSION   0

#ifndef COM_TYPES_H_
#define COM_TYPES_H_


#include "ComStack_Types.h"

typedef uint16 Com_BitPositionType;

typedef enum{
	COM_UNINIT,
	COM_INIT
} Com_StatusType;

/* @req COM119 */
typedef enum {
	IMMEDIATE,
	DEFERRED
} Com_IPduSignalProcessing;

/* @req COM493 */
typedef enum {
	RECEIVE,
	SEND
} Com_IPduDirection;

/* @req COM232 */
typedef enum {
	PENDING, /* Transmission not triggered */
	TRIGGERED, /* Can be triggered by I-PDU */
	TRIGGERED_ON_CHANGE, /* Triggered if value is different than stored */
	TRIGGERED_ON_CHANGE_WITHOUT_REPETITION, /* Triggered once if value is different than stored */
	TRIGGERED_WITHOUT_REPETITION /* Can be triggered by I-PDU but once */
} ComTransferProperty_type;

/* @req COM137 */
typedef enum {
	DIRECT,
	MIXED,
	NONE,
	PERIODIC
} ComTxModeMode_type;

/* @req COM602 */
/* Filtering mechanisms used on sender side for Transmission Mode Conditions (TMC) but shall not filter out signals on sender side.*/
typedef enum {
	ALWAYS,
	MASKED_NEW_DIFFERS_MASKED_OLD,
	MASKED_NEW_DIFFERS_X,
	MASKED_NEW_EQUALS_X,
	NEVER,
	NEW_IS_OUTSIDE,
	NEW_IS_WITHIN,
	ONE_EVERY_N
} ComFilterAlgorithm_type;

/* @req COM157 */
typedef enum {
	COM_BIG_ENDIAN,
	COM_LITTLE_ENDIAN,
	COM_OPAQUE
} ComSignalEndianness_type;

/* @req COM291 */
/* reception deadline monitoring of the I-PDU using the smallest configured non zero timeout parameter */
typedef enum {
	COM_TIMEOUT_DATA_ACTION_NONE,
	COM_TIMEOUT_DATA_ACTION_REPLACE
} ComRxDataTimeoutAction_type;

typedef uint16 Com_SignalIdType;
typedef uint16 Com_SignalGroupIdType;
typedef uint16 Com_IpduGroupIdType;
typedef uint8:1 Com_IpduGroupVector; /*Check*/
typedef uint8 Com_ServiceIdType;

#DEFINE COMServiceId_Init 0x01 
#DEFINE COMServiceId_DeInit 0x02 
#DEFINE COMServiceId_IpduGroupControl 0x03 
#DEFINE COMServiceId_ReceptionDMControl 0x06 
#DEFINE COMServiceId_GetStatus 0x07 
#DEFINE COMServiceId_GetVersionInfo 0x09 
#DEFINE COMServiceId_SendSignal 0x0A 
#DEFINE COMServiceId_ReceiveSignal 0x0B 
#DEFINE COMServiceId_UpdateShadowSignal 0x0C 
#DEFINE COMServiceId_SendSignalGroup 0x0D 
#DEFINE COMServiceId_ReceiveSignalGroup 0x0E 
#DEFINE COMServiceId_ReceiveShadowSignal 0x0F 
#DEFINE COMServiceId_InvalidateSignal 0x10 
#DEFINE COMServiceId_InvalidateShadowSignal 0x16 
#DEFINE COMServiceId_TriggerIPDUSend 0x17 
#DEFINE COMServiceId_MainFunctionRx 0x18 
#DEFINE COMServiceId_MainFunctionTx 0x19 
#DEFINE COMServiceId_MainFunctionRouteSignals 0x1A 
#DEFINE COMServiceId_InvalidateSignalGroup 0x1B
#DEFINE COMServiceId_ClearIpduGroupVector 0x1C 
#DEFINE COMServiceId_SetIpduGroup 0x1D 
#DEFINE COMServiceId_SendDynSignal 0x21 
#DEFINE COMServiceId_ReceiveDynSignal 0x22 
#DEFINE COMServiceId_SendSignalGroupArray 0x23 
#DEFINE COMServiceId_ReceiveSignalGroupArray 0x24 
#DEFINE COMServiceId_SwitchIpduTxMode 0x27 
#DEFINE COMServiceId_TriggerIPDUSendWithMetaData 0x28 
#DEFINE COMServiceId_TxConfirmation 0x40 
#DEFINE COMServiceId_TriggerTransmit 0x41 
#DEFINE COMServiceId_RxIndication 0x42 
#DEFINE COMServiceId_CopyTxData 0x43 
#DEFINE COMServiceId_CopyRxData 0x44 
#DEFINE COMServiceId_TpRxIndication 0x45 
#DEFINE COMServiceId_StartOfReception 0x46 
#DEFINE COMServiceId_TpTxConfirmation 0x48



/* Top-level configuration container for COM. Exists once per configuration. */
typedef struct {
	const ComIPdu_type *ComIPdu; /* IPDU definitions */
	const ComSignal_type *ComSignal; /* Signal definitions */
	const uint8 ComNumOfSignals; /* Number of signals */
	const uint8 ComNumOfIPDUs; /* Number of I-PDUs */
} Com_ConfigType;


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


/* Helper functions */
void Com_WriteToPDU(const Com_SignalIdType signalId, const void *signalData,boolean * dataChanged);

extern ComSignalEndianess_type Com_SystemEndianness;

#define COM_BUSY 0x81
#define COM_SERVICE_NOT_AVAILABLE 0x80
#endif /*COM_H_*/
