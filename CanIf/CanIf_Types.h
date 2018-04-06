#ifndef CANIF_TYPES_H_
#define CANIF_TYPES_H_

#include "ComStack_Types.h"


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
} CanIf_PduModeType;


/* @req CANIF201 */
typedef enum {
	CANIF_NO_NOTIFICATION = 0,	/* No transmit or receive event occurred for the requested L-PDU. */
	CANIF_TX_RX_NOTIFICATION /* The requested Rx/Tx CAN L-PDU was successfully transmitted or received. */
} CanIf_NotifStatusType;


/********************************************/

/* @req CANIF619*/
typedef enum {
	BINARY = 0,
	INDEX,
	LINEAR,
	TABLE
} CanIfPrivateSoftwareFilterType;

/** Type of the upper layer interfacing this module */
typedef enum {
	CANIF_USER_TYPE_CAN_NM,
	CANIF_USER_TYPE_CAN_TP,
	CANIF_USER_TYPE_CAN_PDUR,
	CANIF_USER_TYPE_J1939TP,
	CANIF_USER_TYPE_XCP,
	CANIF_USER_TYPE_CAN_SPECIAL
} CanIf_UserTypeType;

/** Notification function for CANIF_USER_TYPE_CAN_SPECIAL */
typedef void (*CanIf_FuncTypeCanSpecial)(uint8 channel, PduIdType pduId, const uint8 *sduPtr, uint8 dlc, Can_IdType canId);

/** Defines if PDU Can id can be changed at runtime. */
typedef enum {
  CANIF_PDU_TYPE_STATIC = 0,
  CANIF_PDU_TYPE_DYNAMIC       /**< Not supported */
} CanIf_PduTypeType;

/* @req CANIF590 */
/* CAN Identifier of the transmit CAN L-PDU */
typedef enum {
  	EXTENDED_CAN, /*CAN frame with extended identifier (29 bits) */
	EXTENDED_FD_CAN, /* CAN FD frame with extended identifier (29 bits) */
	STANDARD_CAN, /* CAN frame with standard identifier (11 bits) */
	STANDARD_FD_CAN /* CAN FD frame with standard identifier (11 bits) */
} CanIfTxPduCanIdType;

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
} CanIf_HrhRangeConfigType;


//-------------------------------------------------------------------
/*
 * CanIfInitHrhConfig container
 */
/** Definition of Hardware Receive Handle */
typedef struct {
	/** Defines the HRH type i.e, whether its a BasicCan or FullCan. If BasicCan is
	 *  configured, software filtering is enabled. */
  Can_Arc_HohType CanIfHrhType;

	/** Selects the hardware receive objects by using the HRH range/list from
	 *  CAN Driver configuration to define, for which HRH a software filtering has
	 *  to be performed at during receive processing. True: Software filtering is
	 *  enabled False: Software filtering is disabled */
	boolean  CanIfSoftwareFilterHrh;

	/** Reference to controller Id to which the HRH belongs to. A controller can
	 *  contain one or more HRHs. */
	CanIf_Arc_ChannelIdType CanIfCanControllerHrhIdRef;

	/** The parameter refers to a particular HRH object in the CAN Driver Module
	 *  configuration. The HRH id is unique in a given CAN Driver. The HRH Ids
	 *  are defined in the CAN Driver Module and hence it is derived from CAN
	 *  Driver Configuration. */
	Can_Arc_HRHType CanIfHrhIdSymRef ;

	/** Defines the parameters required for configuraing multiple
	 *  CANID ranges for a given same HRH. */
	const CanIf_HrhRangeConfigType *CanIfHrhRangeConfig;

  /** End Of List. Set to TRUE if this is the last object in the list. */
  boolean CanIf_Arc_EOL;
} CanIf_HrhConfigType;

//-------------------------------------------------------------------
/*
 * CanIfInitHthConfig container
 */
/** Definition of Hardware Transmit Handle */
typedef struct {
  /** Defines the HTH type i.e, whether its a BasicCan or FullCan. */
  Can_Arc_HohType CanIfHthType;

  /** Reference to controller Id to which the HTH belongs to. A controller
   *  can contain one or more HTHs */
  CanIf_Arc_ChannelIdType CanIfCanControllerIdRef;

  /** The parameter refers to a particular HTH object in the CAN Driver Module
   *  configuration. The HTH id is unique in a given CAN Driver. The HTH Ids
   *  are defined in the CAN Driver Module and hence it is derived from CAN
   *  Driver Configuration. */
  Can_Arc_HTHType CanIfHthIdSymRef ;

  /** End Of List. Set to TRUE if this is the last object in the list. */
  boolean CanIf_Arc_EOL;
} CanIf_HthConfigType;

//-------------------------------------------------------------------
/*
 * CanIfInitHohConfig container
 */
/** Definition of Hardware Object Handle. */
typedef struct {
  /** Reference to the CAN Driver controller config. */
  const Can_ConfigSetType   *CanConfigSet;

  /** This container contains contiguration parameters for each hardware receive object. */
  const CanIf_HrhConfigType *CanIfHrhConfig;

  /** This container contains parameters releated to each HTH */
  const CanIf_HthConfigType *CanIfHthConfig;

  /** End Of List. Set to TRUE if this is the last object in the list. */
  boolean CanIf_Arc_EOL;
} CanIf_InitHohConfigType;

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

	/** CAN Identifier of transmit CAN L-PDUs used by the CAN Driver for CAN L-
	 *  PDU transmission. Range: 11 Bit For Standard CAN Identifier ... 29 Bit For
	 *  Extended CAN identifier */
	uint32  CanIfCanTxPduIdCanId;

	/** Data length code (in bytes) of transmit CAN L-PDUs used by the CAN
	 *  Driver for CAN L-PDU transmission. The data area size of a CAN L-Pdu
	 *  can have a range from 0 to 8 bytes. */
	uint8 		CanIfCanTxPduIdDlc;

	/** Defines the type of each transmit CAN L-PDU.
	 *  DYNAMIC  CAN ID is defined at runtime.
	 *  STATIC  CAN ID is defined at compile-time. */
	CanIf_PduTypeType		CanIfCanTxPduType;

#if ( CANIF_READTXPDU_NOTIFY_STATUS_API == STD_ON )
	/** Enables and disables transmit confirmation for each transmit CAN L-PDU
	 *  for reading its notification status. True: Enabled False: Disabled */
	boolean		CanIfReadTxPduNotifyStatus;
#endif

	/** CAN Identifier of transmit CAN L-PDUs used by the CAN Driver for CAN L-
	 *  PDU transmission.
	 *  EXTENDED_CAN  The CANID is of type Extended (29 bits).
	 *  STANDARD_CAN  The CANID is of type Standard (11 bits). */
	CanIf_CanIdTypeType		CanIfTxPduIdCanIdType;

	/** Name of target confirmation services to target upper layers (PduR, CanNm
	 *  and CanTp. If parameter is not configured then no call-out function is
	 *  provided by the upper layer for this Tx L-PDU. */
	void (*CanIfUserTxConfirmation)(PduIdType);   /* CANIF 109 */

	/** Handle, that defines the hardware object or the pool of hardware objects
	 *  configured for transmission. The parameter refers HTH Id, to which the L-
	 *  PDU belongs to. */
	const CanIf_HthConfigType *CanIfCanTxPduHthRef;

	/** Reference to the "global" Pdu structure to allow harmonization of handle
	 *  IDs in the COM-Stack. */
	void *PduIdRef;
} CanIf_TxPduConfigType;

//-------------------------------------------------------------------
/*
 * CanIfRxPduConfig container
 */


/** Definition of Rx PDU (Protocol Data Unit). */
typedef struct {
  /** ECU wide unique, symbolic handle for receive CAN L-PDU. The
   *  CanRxPduId is configurable at pre-compile and post-built time. It shall fulfill
   *  ANSI/AUTOSAR definitions for constant defines. Range: 0..max. number
   *  of defined CanRxPduIds */
  PduIdType CanIfCanRxPduId;

  /** CAN Identifier of Receive CAN L-PDUs used by the CAN Interface. Exa:
   *  Software Filtering. Range: 11 Bit For Standard CAN Identifier ... 29 Bit For
   *  Extended CAN identifier */
	uint32 		CanIfCanRxPduCanId;

  /** Data Length code of received CAN L-PDUs used by the CAN Interface.
   *  Exa: DLC check. The data area size of a CAN L-PDU can have a range
   *  from 0 to 8 bytes.  	uint8 		CanIfCanRxPduDlc; */
	uint8		CanIfCanRxPduDlc;

#if ( CANIF_CANPDUID_READDATA_API == STD_ON )
  /** Enables and disables the Rx buffering for reading of received L-PDU data.
   *  True: Enabled False: Disabled */
	boolean		CanIfReadRxPduData;
#endif

#if ( CANIF_READRXPDU_NOTIF_STATUS_API == STD_ON )
  /** CanIfReadRxPduNotifyStatus {CANIF_READRXPDU_NOTIFY_STATUS}
   *  Enables and disables receive indication for each receive CAN L-PDU for
   *  reading its' notification status. True: Enabled False: Disabled */
	boolean		CanIfReadRxPduNotifyStatus;
#endif

  /** CAN Identifier of receive CAN L-PDUs used by the CAN Driver for CAN L-
   *  PDU transmission.
   *  EXTENDED_CAN  The CANID is of type Extended (29 bits)
   *  STANDARD_CAN  The CANID is of type Standard (11 bits) */
	CanIf_CanIdTypeType	CanIfRxPduIdCanIdType;

  /** This parameter defines the type of the receive indication call-outs called to
   *  the corresponding upper layer the used TargetRxPduId belongs to. */
	CanIf_UserTypeType  CanIfRxUserType;

  /** Name of target indication services to target upper layers (PduRouter,
   *  CanNm, CanTp and ComplexDeviceDrivers). If parameter is 0 no call-out
   *  function is configured. */
	void *CanIfUserRxIndication;

  /** The HRH to which Rx L-PDU belongs to, is referred through this
   *  parameter. */
	const CanIf_HrhConfigType *CanIfCanRxPduHrhRef;

  /** Reference to the "global" Pdu structure to allow harmonization of handle
   *  IDs in the COM-Stack. */
	void *PduIdRef;

  /** Defines the type of software filtering that should be used
   *  for this receive object. */
	CanIf_SoftwareFilterTypeType CanIfSoftwareFilterType;

  /** Acceptance filters, 1 - care, 0 - don't care.
   *  Is enabled by the CanIfSoftwareFilterMask in CanIf_HrhConfigType
   *  ArcCore exension */
	uint32 CanIfCanRxPduCanIdMask;

} CanIf_RxPduConfigType;

//-------------------------------------------------------------------

/*
 * CanIfControllerConfig container
 */
/** Not supported. */
typedef enum {
	CANIF_WAKEUP_SUPPORT_CONTROLLER,
	CANIF_WAKEUP_SUPPORT_NO_WAKEUP,
	CANIF_WAKEUP_SUPPORT_TRANSCEIVER
} CanIf_WakeupSupportType;


/** Container used to create channel init configurations.
 *  @see CanIf_Arc_ConfigurationIndexType
 *  @see CanIf_Arc_ChannelIdType */
typedef struct {
    /** Not used */
	/* CanIf_WakeupSupportType WakeupSupport; */

	/** CanIf-specific id of the controller */
	CanIf_Arc_ChannelIdType CanIfControllerIdRef;

	/** Not used */
	/* const char CanIfDriverNameRef[8]; */

	/** Reference to */
	const Can_ControllerConfigType *CanIfInitControllerRef;
} CanIf_ControllerConfigType;

//-------------------------------------------------------------------
/*
 * CanIfTransceiverDrvConfig container
 */

typedef struct {
	boolean	TrcvWakeupNotification;
	uint8	TrcvIdRef;
} CanIf_TransceiverDrvConfigType;


typedef struct {
	uint32 todo;
} CanIf_TransceiverConfigType;

/** Callout functions with respect to the upper layers. This callout functions
 *  defined in this container are common to all configured underlying CAN
 *  Drivers / CAN Transceiver Drivers. */
typedef struct {
	/** Name of target BusOff notification services to target upper layers
	 *  (PduRouter, CanNm, CanTp and ComplexDeviceDrivers). */
	void (*CanIfBusOffNotification)(uint8 Controller);

	/** Name of target wakeup notification services to target upper layers
	 *  e.g Ecu_StateManager. If parameter is 0
	 *  no call-out function is configured. */
	void (*CanIfWakeUpNotification)();

	/** Name of target wakeup validation notification services to target upper
	 *  layers (ECU State Manager). If parameter is 0 no call-out function is
	 *  configured. */
	void (*CanIfWakeupValidNotification)();

	/** ArcCore ext. */
	void (*CanIfErrorNotificaton)(uint8,Can_Arc_ErrorType);

} CanIf_DispatchConfigType;

/** This container contains the references to the configuration setup of each
 *  underlying CAN driver. */
typedef struct {
	/** Not used. */
	uint32 CanIfConfigSet;

	/** Size of Rx PDU list. */
	uint32 CanIfNumberOfCanRxPduIds;
	/** Size of Tx PDU list. */
	uint32 CanIfNumberOfCanTXPduIds;
	/** Not used */
	uint32 CanIfNumberOfDynamicCanTXPduIds;

	//
	// Containers
	//

  /** Hardware Object Handle list */
	const CanIf_InitHohConfigType *CanIfHohConfigPtr;

  /** Rx PDU's list */
	const CanIf_RxPduConfigType *CanIfRxPduConfigPtr;

  /** Tx PDU's list */
#if (CANIF_ARC_RUNTIME_PDU_CONFIGURATION == STD_OFF)
	const CanIf_TxPduConfigType *CanIfTxPduConfigPtr;
#else
	CanIf_TxPduConfigType *CanIfTxPduConfigPtr;
#endif

} CanIf_InitConfigType;

/* @req CANIF144 */
/* Top level config container. */
typedef struct {
	/* Reference to the list of channel init configurations. */
	const CanIf_ControllerConfigType 	*ControllerConfig;

	/** Callout functions with respect to the upper layers. This callout
	 *  functions defined in this container are common to all
	 *  configured underlying CAN Drivers / CAN Transceiver Drivers */
	const CanIf_DispatchConfigType 	*DispatchConfig;

	/** This container contains the init parameters of the CAN Interface. */
	const CanIf_InitConfigType 		*InitConfig;

	/** Not used */
	const CanIf_TransceiverConfigType *TransceiverConfig;

	/** ArcCore: Contains the mapping from CanIf-specific Channels to Can Controllers */
	const CanControllerIdType			*Arc_ChannelToControllerMap;

	const uint8							*Arc_ChannelDefaultConfIndex;
} CanIf_ConfigType;

#endif /*CANIF_TYPES_H_*/