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
} Com_StatusType

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
	const uint8 ComConfigurationId; /*The ID of this configuration. This is returned by Com_GetConfigurationId(); */
	/*
	 * Signal Gateway mappings.
	 * Not Implemented yet.
	ComGwMapping_type ComGwMapping[];
	 */
	const ComIPdu_type *ComIPdu; /* IPDU definitions */
	const ComIPduGroup_type *ComIPduGroup; /* IPDU group definitions */
	const ComSignal_type *ComSignal; /* Signal definitions */
	const ComGroupSignal_type *ComGroupSignal; /* Group signal definitions */

} Com_ConfigType;

typedef enum {
	IMMEDIATE,
	DEFERRED
} Com_IPduSignalProcessingMode;

typedef enum {
	RECEIVE,
	SEND
} Com_IPduDirection;

typedef enum {
	BOOLEAN,
	UINT8,
	UINT16,
	UINT32,
	UINT8_N,
	UINT8_DYN,
	SINT8,
	SINT16,
	SINT32
} Com_SignalType;

#define COM_SIGNALTYPE_UNSIGNED  FALSE
#define COM_SIGNALTYPE_SIGNED    TRUE

typedef enum {
	PENDING,
	TRIGGERED
} ComTransferProperty_type;

typedef enum {
	DIRECT,
	MIXED,
	NONE,
	PERIODIC
} ComTxModeMode_type;


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

typedef enum {
	COM_BIG_ENDIAN,
	COM_LITTLE_ENDIAN,
	COM_OPAQUE
} ComSignalEndianess_type;

typedef enum {
	COM_TIMEOUT_DATA_ACTION_NONE,
	COM_TIMEOUT_DATA_ACTION_REPLACE
} ComRxDataTimeoutAction_type;

/*
typedef enum {

} ComTransmissionMode_type;
*/

// Shortcut macros
#define M_BOOLEAN boolean
#define M_UINT8 uint8
#define M_UINT16 uint16
#define M_UINT32 uint32
#define M_UINT8_N uint8
#define M_SINT8 sint8
#define M_SINT16 sint16
#define M_SINT32 sint32

#define SignalTypeToSize(type,length) \
	(type == UINT8   ? sizeof(uint8) : \
	type == UINT16  ? sizeof(uint16) : \
	type == UINT32  ? sizeof(uint32) : \
	type == UINT8_N  ? sizeof(uint8) * length : \
	type == SINT8   ? sizeof(sint8) : \
	type == SINT16  ? sizeof(sint16) : \
	type == SINT32  ? sizeof(sint32) : sizeof(boolean)) \

#define SignalTypeSignedness(type) \
		(( (type == SINT8) || (type == SINT16) || (type == SINT32) ) ? \
				COM_SIGNALTYPE_SIGNED : COM_SIGNALTYPE_UNSIGNED)

/** Filter configuration type.
 * NOT SUPPORTED
 */
typedef struct {
	/** The algorithm that this filter uses. */
	ComFilterAlgorithm_type ComFilterAlgorithm;
	/** Filter mask. */
	uint32 ComFilterMask;
	/** Max value for filter. */
	uint32 ComFilterMax;
	/** Min value for filter. */
	uint32 ComFilterMin;
	/** Offset for filter. */
	uint32 ComFilterOffset;
	uint32 ComFilterPeriodFactor;
	uint32 ComFilterX;
	uint32 ComFilterArcN;
	uint32 ComFilterArcNewValue;
	uint32 ComFilterArcOldValue;

} ComFilter_type;

/** Configuration structure for group signals */
typedef struct {
	/** Starting position (bit) of the signal within the IPDU.
	 * Range 0 to 63.
	 */
	const Com_BitPositionType ComBitPosition;

	/** The size of the signal in bits.
	 * Range 0 to 64.
	 */
	const uint8 ComBitSize;

	/** Identifier for the signal.
	 * Should be the same value as the index in the COM signal array.
	 */
	const uint8 ComHandleId;

	/** Defines the endianess of the signal's network representation. */
	const ComSignalEndianess_type ComSignalEndianess;

	/** Value used to initialize this signal. */
	const void *ComSignalInitValue;

	/** Defines the type of the signal. */
	const Com_SignalType ComSignalType;


	/** Filter for this signal.
	 * NOT SUPPORTED
	 */
	//const ComFilter_type ComFilter;

	/* Pointer to the shadow buffer of the signal group that this group signal is contained in.
	 *
	 * This is initialized by Com_Init() and should not be configured.
	 */
	//void *Com_Arc_ShadowBuffer;

	/* Callback function used when an invalid signal is received. */
	// ComInvalidNotification;
	//uint8 ComSignalDataInvalidValue;

	/* IPDU id of the IPDU that this signal belongs to.
	 *
	 * This is initialized by Com_Init() and should not be configured.
	 */

	//const uint8 ComIPduHandleId;
	//const uint8 ComSignalUpdated;

	/** Marks the end of list for the configuration array. */
	const uint8 Com_Arc_EOL;
} ComGroupSignal_type;


/** Configuration structure for signals and signal groups. */
typedef struct {
#if defined(__GTK__)
	uint8 name[64];
#endif

	/** Starting position (bit) of the signal within the IPDU.
	 * Range 0 to 2031.
	 */
	const Com_BitPositionType ComBitPosition;

	/** The size of the signal in bits.
	 * Range 0 to 63.
	 * Range 0 to 4095 for uint8_n signal types
	 */
	const uint16 ComBitSize;

	/** Notification function for error notification. */
	void (*ComErrorNotification) (void);

	/** First timeout period for deadline monitoring. */
	const uint32 ComFirstTimeoutFactor;

	/** Identifier for the signal.
	 * Should be the same value as the index in the COM signal array.
	 */
	const uint16 ComHandleId;

	/** Tx and Rx notification function. */
	void (*ComNotification) (void);

	/** Action to be performed when a reception timeout occurs. */
	const ComRxDataTimeoutAction_type ComRxDataTimeoutAction;

	/** Defines the endianess of the signal's network representation. */
	const ComSignalEndianess_type ComSignalEndianess;

	/** Value used to initialized this signal. */
	const void *ComSignalInitValue;

	/** The number of bytes if the signal has type UINT8_N;
	 * Range 1 to 8.
	 */
	//const uint8 ComSignalLength;

	/** Defines the type of the signal. */
	const Com_SignalType ComSignalType;

	/** Timeout period for deadline monitoring. */
	const uint32 ComTimeoutFactor;

	/** Timeout notification function. */
	void (*ComTimeoutNotification) (void);

	const ComTransferProperty_type ComTransferProperty;

	/** The bit position in the PDU for this signal's update bit.
	 * Range 0 to 2031.
	 * Only applicable if an update bit is used. NULL otherwise.
	 */
	const Com_BitPositionType ComUpdateBitPosition;

	/** Marks if this signal uses an update bit.
	 * Should be set to one if an update bit is used.
	 */
	const uint8 ComSignalArcUseUpdateBit;

	/** Filter for this signal.
	 * NOT SUPPORTED.
	 */
	//const ComFilter_type ComFilter;

	/** Marks if this signal is a signal group.
	 * Should be set to 1 if the signal is a signal group.
	 */
	const uint8 Com_Arc_IsSignalGroup;

	/** Array of group signals.
	 * Only applicable if this signal is a signal group.
	 */
	const ComGroupSignal_type * const *ComGroupSignal;


	const void *Com_Arc_ShadowBuffer;
	const uint8 *Com_Arc_ShadowBuffer_Mask;
	//void *Com_Arc_IPduDataPtr;

	/* Pointer to the data storage of this signals IPDU.
	 * This is initialized by Com_Init() and should not be configured.
	 */
	//const void *ComIPduDataPtr;

	/* IPDU id of the IPDU that this signal belongs to.
	 * This is initialized by Com_Init() and should not be configured.
	 */

	const uint16 ComIPduHandleId;
	//const uint8 ComSignalUpdated;

	/* Callback function used when an invalid signal is received.
	 */
	// ComInvalidNotification;

	//uint8 ComSignalDataInvalidValue;

	/* Action to be taken if an invalid signal is received.
	 */
	// ComDataInvalidAction;

	/** Marks the end of list for the signal configuration array. */
	const uint8 Com_Arc_EOL;
} ComSignal_type;



/** Configuration structure for Tx-mode for I-PDUs. */
typedef struct {

	/** Transmission mode for this IPdu. */
	const ComTxModeMode_type ComTxModeMode;

	/** Defines the number of times this IPdu will be sent in each IPdu cycle.
	 * Should be set to 0 for DIRECT transmission mode and >0 for DIRECT/N-times mode.
	 */
	const uint8 ComTxModeNumberOfRepetitions;

	/** Defines the period of the transmissions in DIRECT/N-times and MIXED transmission modes. */
	const uint32 ComTxModeRepetitionPeriodFactor;

	/** Time before first transmission of this IPDU. (i.e. between the ipdu group start and this IPDU is sent for the first time. */
	const uint32 ComTxModeTimeOffsetFactor;

	/** Period of cyclic transmission. */
	const uint32 ComTxModeTimePeriodFactor;
} ComTxMode_type;

/** Extra configuration structure for Tx I-PDUs. */
typedef struct {

	/** Minimum delay between successive transmissions of the IPdu. */
	const uint32 ComTxIPduMinimumDelayFactor;

	/** COM will fill unused areas within an IPdu with this bit patter.
	 */
	const uint8 ComTxIPduUnusedAreasDefault;

	/** Transmission modes for the IPdu.
	 * TMS is not implemented so only one static transmission mode is supported.
	 */
	const ComTxMode_type ComTxModeTrue;

	//ComTxMode_type ComTxModeFalse;
} ComTxIPdu_type;


/** Configuration structure for I-PDU groups */
typedef struct ComIPduGroup_type {
	/** ID of this group.
	 * Range 0 to 31.
	 */
	const uint8 ComIPduGroupHandleId;

	// reference to the group that this group possibly belongs to.
	//struct ComIPduGroup_type *ComIPduGroupRef;

	/** Marks the end of list for the I-PDU group configuration array. */
	const uint8 Com_Arc_EOL;
} ComIPduGroup_type;


/** Configuration structure for an I-PDU. */
typedef struct {
#if defined(__GTK__)
	uint8 name[64];
#endif
	/** Callout function of this IPDU.
	 * The callout function is an optional function used both on sender and receiver side.
	 * If configured, it determines whether an IPdu is considered for further processing. If
	 * the callout return false the IPdu will not be received/sent.
	 */
	boolean (*ComIPduCallout)(PduIdType PduId, const uint8 *IPduData);


	/** The outgoing PDU id. For polite PDU id handling. */
	const uint8 ArcIPduOutgoingId;

	/** Signal processing mode for this IPDU. */
	const Com_IPduSignalProcessingMode ComIPduSignalProcessing;

	/** Size of the IPDU in bytes.
	 * Range 0-8 for CAN and LIN and 0-256 for FlexRay.
	 */
	const uint8 ComIPduSize;

	/** The direction of the IPDU. Receive or Send. */
	const Com_IPduDirection ComIPduDirection;

	/** Reference to the IPDU group that this IPDU belongs to. */
	const uint8 ComIPduGroupRef;

	/** Container of transmission related parameters. */
	const ComTxIPdu_type ComTxIPdu;

	/** Reference to the actual pdu data storage */
	void *const ComIPduDataPtr;
	void *const ComIPduDeferredDataPtr;

	/** References to all signals and signal groups contained in this IPDU.
	 * It probably makes little sense not to define at least one signal or signal group for each IPDU.
	 */
	const ComSignal_type * const *ComIPduSignalRef;

	const ComSignal_type * const ComIPduDynSignalRef;

	/*
	 * The following two variables are used to control the per I-PDU based Rx/Tx-deadline monitoring.
	 */
	//const uint32 Com_Arc_DeadlineCounter;
	//const uint32 Com_Arc_TimeoutFactor;

	/* Transmission related timers and parameters.
	 * These are internal variables and should not be configured.
	 */
	//ComTxIPduTimer_type Com_Arc_TxIPduTimers;

	/** Marks the end of list for this configuration array. */
	const uint8 Com_Arc_EOL;

} ComIPdu_type;



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
