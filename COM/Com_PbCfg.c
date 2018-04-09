#include "Com_PbCfg.h"
#if defined(USE_PDUR)
#include "PduR.h"
#endif

/* Signal initial values. */
static const uint8 ACTemp_InitValue = 0;
static const uint8 Led1Sts_InitValue = 0;
static const uint8 Led2Sts_InitValue = 0;
static const uint8 Led3Sts_InitValue = 0;
static const uint8 MotorTemp_InitValue = 0;
static const uint8 MotorSpeed_InitValue = 0;



/* I-PDU signal lists. */
static const ComSignal_type * const TxMsgTemp_SignalRefs[] = {
	&ComSignal[COM_SID_ACTemp],
	NULL
};
static const ComSignal_type * const RxMsgAbsInfo_SignalRefs[] = {
	&ComSignal[COM_SID_MotorSpeed],
	&ComSignal[COM_SID_MotorTemp],
	&ComSignal[COM_SID_Led1Stat],
	&ComSignal[COM_SID_Led2Stat],
	&ComSignal[COM_SID_Led3Stat],
	NULL
};
    
    
//I-PDU definitions
static const ComIPdu_type ComIPdu[] = {

    {
        .ComIPduCallout =  NULL,
        .IPduOutgoingId =  PDUR_ID_TxMsgTime,
        .ComIPduSignalProcessing =  DEFERRED,
        .ComIPduSize =  8,
        .ComIPduDirection =  SEND,
        .ComTxIPdu ={
            .ComTxIPduMinimumDelayFactor =  1,
            .ComTxIPduUnusedAreasDefault =  0x55,
            .ComTxModeTrue ={
                .ComTxModeMode =   PERIODIC,
                .ComTxModeNumberOfRepetitions =   0,
                .ComTxModeRepetitionPeriod =   5,
                .ComTxModeTimeOffset =   0,
                .ComTxModeTimePeriod =   50,
            },
        },
        .ComIPduDataPtr =  TxMsgTime_IPduBuffer,
        .ComIPduDeferredDataPtr =  NULL,
        .ComIPduSignalRef =  TxMsgTime_SignalRefs,
        .Com_EOL =  FALSE,
    },

    {
        .ComIPduCallout =  NULL,
        .IPduOutgoingId =  PDUR_ID_RxMsgAbsInfo,
        .ComIPduSignalProcessing =  DEFERRED,
        .ComIPduSize =  8,
        .ComIPduDirection =  RECEIVE,
        .ComTxIPdu ={
            .ComTxIPduMinimumDelayFactor =  1,
            .ComTxIPduUnusedAreasDefault =  0x55,
            .ComTxModeTrue ={
                .ComTxModeMode =   PERIODIC,
                .ComTxModeNumberOfRepetitions =   0,
                .ComTxModeRepetitionPeriod =   8,
                .ComTxModeTimeOffset =   0,
                .ComTxModeTimePeriod =   8,
            },
        },
        .ComIPduDataPtr =  RxMsgAbsInfo_IPduBuffer,
        .ComIPduDeferredDataPtr =  NULL,
        .ComIPduSignalRef =  RxMsgAbsInfo_SignalRefs,
        .Com_EOL =  FALSE,
    },

    {
        .Com_EOL =  TRUE
    }
};

const Com_ConfigType ComConfiguration = {
    .ComIPdu =  ComIPdu,
    .ComSignal =  ComSignal,
    .ComNumOfSignals = 5,
    .ComNumOfIPDUs = 3
};