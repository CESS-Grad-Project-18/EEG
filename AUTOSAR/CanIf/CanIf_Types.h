#ifndef CANIF_TYPES_H
#define CANIF_TYPES_H

#include "../COM/ComStack_Types.h"
#include "../Can/Can_GeneralTypes.h"
#include "../Can/Can_Cfg.h"


#define CANIF_E_PARAM_CANID 			10
#define CANIF_E_PARAM_HOH 				12
#define CANIF_E_PARAM_LPDU 				13
#define CANIF_E_PARAM_CONTROLLER 		14
#define CANIF_E_PARAM_CONTROLLERID 		15
#define CANIF_E_PARAM_WAKEUPSOURCE 		16
#define CANIF_E_PARAM_TRCV 				17
#define CANIF_E_PARAM_TRCVMODE 			18
#define CANIF_E_PARAM_TRCVWAKEUPMODE 	19
#define CANIF_E_PARAM_CTRLMODE 			21
#define CANIF_E_PARAM_PDU_MODE 			22
#define CANIF_E_PARAM_POINTER 			20
#define CANIF_E_UNINIT 					30
#define CANIF_E_INVALID_TXPDUID 		50
#define CANIF_E_INVALID_RXPDUID 		60
#define CANIF_E_INVALID_DLC 			61
#define CANIF_E_DATA_LENGTH_MISMATCH 	62
#define CANIF_E_STOPPED 				70
#define CANIF_E_NOT_SLEEP 				71
#define CANIF_E_INIT_FAILED 			80



/* @req CANIF136 */
typedef enum {
	CANIF_CS_UNINIT = 0, /* Default mode of each CAN controller after power on. */
	CANIF_CS_STOPPED, /* CAN controller is halted and does not operate on the network */	                           
	CANIF_CS_STARTED, /* CAN controller is in full-operational mode.*/
	CANIF_CS_SLEEP /* CAN controller is in SLEEP mode and can be woken up by an internal (SW) request or by a network event */
} CanIf_ControllerModeType;


/* @req CANIF137*/
typedef enum{
	CANIF_OFFLINE = 0, /* Transmit and receive path of the corresponding channel are disabled */
	CANIF_TX_OFFLINE, /* Transmit path of the corresponding channel is disabled. The receive path is enabled */
	CANIF_TX_OFFLINE_ACTIVE, /* Transmit path of the corresponding channel is in offline active mode. The receive path is disabled. CanIfTxOfflineActiveSupport = TRUE */
	CANIF_ONLINE /* Transmit and receive path of the corresponding channel are enabled */
} CanIf_PduChannelModeType;


/* @req CANIF201 */
typedef enum {
	CANIF_NO_NOTIFICATION = 0,	/* No transmit or receive event occurred for the requested L-PDU. */
	CANIF_TX_RX_NOTIFICATION /* The requested Rx/Tx CAN L-PDU was successfully transmitted or received. */
} CanIf_NotifStatusType;



/* @req CANIF619*/
typedef enum {
	BINARY = 0,
	INDEX,
	LINEAR,
	TABLE
} CanIf_PrivateSoftwareFilterType;

/* Type of the upper layer interfacing this module */
typedef enum {
	CAN_TP,
	PDUR,
	CAN_NM,
	J1939TP,
	XCP,
	CDD,
	J1939NM,
	CAN_TSYN
} CanIf_TxPduUserTxConfirmationULType;

/** Notification function for CANIF_USER_TYPE_CAN_SPECIAL */
typedef void (*CanIf_FuncTypeCanSpecial)(uint8 channel, PduIdType pduId, const uint8 *sduPtr, uint8 dlc, Can_IdType canId);

/** Defines if PDU Can id can be changed at runtime. */
typedef enum {
  STATIC,
  DYNAMIC
} CanIf_TxPduType;

/* @req CANIF590 */
/* CAN Identifier of the transmit CAN L-PDU */
typedef enum {
  	EXTENDED_CAN, /*CAN frame with extended identifier (29 bits) */
	EXTENDED_FD_CAN, /* CAN FD frame with extended identifier (29 bits) */
	STANDARD_CAN, /* CAN frame with standard identifier (11 bits) */
	STANDARD_FD_CAN /* CAN FD frame with standard identifier (11 bits) */
} CanIf_TxPduCanIdType;


typedef enum {
	BASIC,
	FULL
} Can_HohType;


/* @req CANIF742 */
typedef enum{
	UINT8_PH,
	UINT16_PH
} CanIf_PublicHandleType;


typedef enum {
	CANIF_CanIfCtrlCfg,
	CANIF_CHANNEL_CNT
} CanIf_ChannelIdType;


typedef enum {
	HWObj_1,
	TX,
	RX,
	NUM_OF_HRHS
} Can_HRHType;


typedef enum {
	HWObj_2,
	NUM_OF_HTHS
} Can_HTHType;


//-------------------------------------------------------------------
/*
 * CanIfHrhRangeConfig container
 */

/** Parameters for configuring Can id ranges. Not supported. */
typedef struct {
	/** Lower CAN Identifier of a receive CAN L-PDU for identifier range
	 *  definition, in which all CAN Ids shall pass the software filtering. Range: 11
     *  Bit for Standard CAN Identifier 29 Bit for Extended CAN Identifer */
	uint32 CanIfRxPduLowerCanId;

	/** Upper CAN Identifier of a receive CAN L-PDU for identifier range
	 *  definition, in which all CAN Ids shall pass the software filtering. Range: 11
	 *  Bit for Standard CAN Identifier 29 Bit for Extended CAN Identifer */
	uint32 CanIfRxPduUpperCanId;
} CanIf_HrhRangeCfgType;


//-------------------------------------------------------------------
/*
 * CanIfInitHrhConfig container
 */
/** Definition of Hardware Receive Handle */
typedef struct {
	/** Defines the HRH type i.e, whether its a BasicCan or FullCan. If BasicCan is
	 *  configured, software filtering is enabled. */
  Can_HohType CanIfHrhType;

	/** Selects the hardware receive objects by using the HRH range/list from
	 *  CAN Driver configuration to define, for which HRH a software filtering has
	 *  to be performed at during receive processing. True: Software filtering is
	 *  enabled False: Software filtering is disabled */
	boolean  CanIfSoftwareFilterHrh;

	/** Reference to controller Id to which the HRH belongs to. A controller can
	 *  contain one or more HRHs. */
	CanIf_ChannelIdType CanIfCanControllerHrhIdRef;

	/** The parameter refers to a particular HRH object in the CAN Driver Module
	 *  configuration. The HRH id is unique in a given CAN Driver. The HRH Ids
	 *  are defined in the CAN Driver Module and hence it is derived from CAN
	 *  Driver Configuration. */
	Can_HRHType CanIfHrhIdSymRef ;

	/** Defines the parameters required for configuraing multiple
	 *  CANID ranges for a given same HRH. */
	const CanIf_HrhRangeCfgType *CanIfHrhRangeConfig;

  /** End Of List. Set to TRUE if this is the last object in the list. */
  boolean CanIf_EOL;
} CanIf_HrhCfgType;

//-------------------------------------------------------------------
/*
 * CanIfInitHthConfig container
 */
/** Definition of Hardware Transmit Handle */
typedef struct {
  /** Defines the HTH type i.e, whether its a BasicCan or FullCan. */
  Can_HohType CanIfHthType;

  /** Reference to controller Id to which the HTH belongs to. A controller
   *  can contain one or more HTHs */
  CanIf_ChannelIdType CanIfCanControllerIdRef;

  /** The parameter refers to a particular HTH object in the CAN Driver Module
   *  configuration. The HTH id is unique in a given CAN Driver. The HTH Ids
   *  are defined in the CAN Driver Module and hence it is derived from CAN
   *  Driver Configuration. */
  Can_HTHType CanIfHthIdSymRef ;

  /** End Of List. Set to TRUE if this is the last object in the list. */
  boolean CanIf_EOL;
} CanIf_HthCfgType;

//-------------------------------------------------------------------
/*
 * CanIfInitHohConfig container
 */
/** Definition of Hardware Object Handle. */
typedef struct {

  /** This container contains contiguration parameters for each hardware receive object. */
  const CanIf_HrhCfgType *CanIfHrhConfig;

  /** This container contains parameters releated to each HTH */
  const CanIf_HthCfgType *CanIfHthConfig;

  /** End Of List. Set to TRUE if this is the last object in the list. */
  boolean CanIf_EOL;
} CanIf_InitHohCfgType;

//-------------------------------------------------------------------
/*
 * CanIfTxPduConfig container
 */

/** Definition of Tx PDU (Protocol Data Unit). */
typedef struct {
	/** ECU wide unique, symbolic handle for transmit CAN L-PDU. The
	 *  CanIfCanTxPduId is configurable at pre-compile and post-built time.
	 *  Range: 0..max. number of CantTxPduIds  	PduIdType 	CanTxPduId; */
	PduIdType CanIfTxPduId;

	/* CAN Identifier of transmit CAN L-PDUs used by the CAN Driver for CAN L-PDU transmission. */
	CanIf_TxPduCanIdType		CanIfTxPduIdCanIdType;

	/* CAN Identifier of transmit CAN L-PDUs used by the CAN Driver for CAN L-PDU transmission (ID)*/
	uint32  CanIfCanTxPduIdCanId;

	/* Data length code (in bytes) of transmit CAN L-PDUs used by the CAN Driver for CAN L-PDU transmission. 0 - 8 bytes. */
	uint8 		CanIfCanTxPduIdDlc;

	/* Defines the type of each transmit CAN L-PDU. DYNAMIC runtime. STATIC compile-time. */
	CanIf_TxPduType		CanIfCanTxPduType;

	/* @req CANIF247 */
	/* Name of target confirmation services to target upper layer (PduR). If not configured then no call-out function is provided by the upper layer for this Tx L-PDU. */
	void (*CanIfUserTxConfirmation)(PduIdType);   

	/** Handle, that defines the hardware object or the pool of hardware objects
	 *  configured for transmission. The parameter refers HTH Id, to which the L-
	 *  PDU belongs to. */
	const CanIf_HthCfgType *CanIfCanTxPduHthRef;

	/** Reference to the "global" Pdu structure to allow harmonization of handle
	 *  IDs in the COM-Stack. */
	void *PduIdRef;
} CanIf_TxPduCfgType;


/** Definition of Rx PDU (Protocol Data Unit). */
typedef struct {
  /** ECU wide unique, symbolic handle for receive CAN L-PDU. The
   *  CanRxPduId is configurable at pre-compile and post-built time. It shall fulfill
   *  ANSI/AUTOSAR definitions for constant defines. Range: 0..max. number
   *  of defined CanRxPduIds */
  PduIdType CanIfCanRxPduId;

  /* CAN Identifier of transmit CAN L-PDUs used by the CAN Driver for CAN L-PDU transmission. */
	CanIf_TxPduCanIdType CanIfRxPduIdCanIdType;

	/* CAN Identifier of transmit CAN L-PDUs used by the CAN Driver for CAN L-PDU transmission (ID)*/
	uint32  CanIfCanRxPduIdCanId;

	/* Data length code (in bytes) of transmit CAN L-PDUs used by the CAN Driver for CAN L-PDU transmission. 0 - 8 bytes. */
	uint8 CanIfCanRxPduIdDlc;

	/* @req CANIF249 */
	/* Name of target confirmation services to target upper layer (PduR). If not configured then no call-out function is provided by the upper layer for this Tx L-PDU. */
	void *CanIfUserRxIndication;

  /** The HRH to which Rx L-PDU belongs to, is referred through this
   *  parameter. */
	const CanIf_HrhCfgType *CanIfCanRxPduHrhRef;

  /** Reference to the "global" Pdu structure to allow harmonization of handle
   *  IDs in the COM-Stack. */
	void *PduIdRef;

  /** Defines the type of software filtering that should be used
   *  for this receive object. */
	CanIf_PrivateSoftwareFilterType CanIfSoftwareFilterType;

  /* Acceptance filters, 1 - Care, 0 - Don't care. */
	uint32 CanIfCanRxPduCanIdMask;

} CanIf_RxPduCfgType;


/** Container used to create channel init configurations.
 *  @see CanIf_ConfigurationIndexType
 *  @see CanIf_ChannelIdType */
typedef struct CanIf_CtrlCfgType{
    /* Not used */
	boolean CanIfCtrlWakeUpSupport;
	uint8 CanIfCtrlId;
	/*Can controller add*/

} CanIf_CtrlCfgType;

//-------------------------------------------------------------------
/*
 * CanIfTransceiverDrvConfig container
 */

typedef struct {
	boolean	TrcvWakeupNotification;
	uint8	TrcvIdRef;
} CanIf_TrcvDrvCfgType;


typedef struct {
	uint32 heck;
} CanIf_TrcvCfgType;

/** Callout functions with respect to the upper layers. This callout functions
 *  defined in this container are common to all configured underlying CAN
 *  Drivers / CAN Transceiver Drivers. */
typedef struct {
	/* Name of target BusOff notification services to target upper layer(PduR). */
	void (*CanIfBusOffNotification)(uint8 Controller);

	/* Name of target wakeup notification services to target upper layer e.g ECU SM. None if 0 */
	void (*CanIfWakeUpNotification)();

	/* Name of target wakeup validation notification services to target upper layer e.g ECU SM. None if 0 */
	void (*CanIfWakeupValidNotification)();


} CanIf_DispatchCfgType;

/* This container contains the references to the configuration setup of each underlying CAN driver. */
typedef struct {
	/* Is this needed?. */
	uint32 CanIfConfigSet;

	/* Size of Rx PDU list. */
	uint32 CanIfNumberOfCanRxPduIds;
	/* Size of Tx PDU list. */
	uint32 CanIfNumberOfCanTXPduIds;
	/* Not used */
	uint32 CanIfNumberOfDynamicCanTXPduIds;

  	/* Hardware Object Handle list */
	const CanIf_InitHohCfgType *CanIfHohConfigPtr;

  	/* Rx PDU's list */
	const CanIf_RxPduCfgType *CanIfRxPduConfigPtr;

  	/* Tx PDU's list */
	const CanIf_TxPduCfgType *CanIfTxPduConfigPtr; /* Remove const? */

} CanIf_InitCfgType;

/* @req CANIF144 */
/* Top level config container of  post build parameters of the CANIF for all underlying CAN drivers. */
typedef struct {
	/* Reference to the list of channel init configurations. */
	const CanIf_CtrlCfgType 	*ControllerConfig;

	/* Callout functions with respect to the upper layers. This callout
	 *  functions defined in this container are common to all
	 *  configured underlying CAN Drivers / CAN Transceiver Drivers */
	const CanIf_DispatchCfgType 	*DispatchConfig;

	/* This container contains the init parameters of the CAN Interface. */
	const CanIf_InitCfgType 		*InitConfig;

	/* Needed? */
	const Can_ControllerIdType			*ChannelToControllerMap;

	const uint8							*ChannelDefaultConfIndex;
} CanIf_ConfigType;


typedef struct{
	/* @req CANIF827 */
	/*  Defines if the buffer element length */	
	boolean CanIfFixedBuffer;

	/* @req CANIF617 */
	/* DLC check enabled or not */		
	boolean CanIfPrivateDlcCheck;

	/* @req CANIF619 */
	/* Filtering mechanism (Reception only) */	
	CanIf_PrivateSoftwareFilterType CanIfPrivateSoftwareFilterType;

	/* @req CANIF675 */
	/* Filtering mechanism (Reception only) */	
	boolean CanIfSupportTTCAN; /* SET TO FALSE ALWAYS */


} CanIf_PrivateCfgType;

/* @req CANIF246 */
typedef struct{
	/* @req CANIF824 */
 	/* Enable support for dynamic ID handling using L-SDU MetaData. */
 	boolean CanIfMetaDataSupport;

	/* @req CANIF522 */
 	/* Enable/disable dummy API for upper layer modules which allows to request the cancellation of an I-PDU */
 	boolean CanIfPublicCancelTransmitSupport; /* Not needed?*/

	/* @req CANIF671 */
 	/* Header files for callback functions */
	char CanIfPublicCddHeaderFile[32]; /* Not needed? */

	/* @req CANIF614 */
 	/* DET ON/OFF */
	boolean CanIfPublicDevErrorDetect; /* Not needed? */

	CanIf_PublicHandleType  CanIfPublicHandle;

	/* @req CANIF839 */
 	/* Pretended network features support */
	boolean CanIfPublicIcomSupport; /* Not needed? */

	/* @req CANIF612 */
 	/* Multiple CAN drivers support */
	boolean CanIfPublicMultipleDrvSupport; 

	/* @req CANIF772 */
	/* Partial network features support */
	boolean CanIfPublicPnSupport; /* Not needed? */

	/* @req CANIF607 */
	/* CanIf_ReadRxPduData enable/disable (Rcvd L-SDUs) */
	boolean CanIfPublicReadRxPduDataApi;

	/* @req CANIF608 */
	/* Reading notification status enable/disable (Rcvd L-PDUs) */
	boolean CanIfPublicReadRxPduNotifyStatusApi;

} CanIf_PublicCfgType;

#endif /*CANIF_TYPES_H*/