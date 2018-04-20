#include "Com_PbCfg.h"
#include "../PduR/PduR.h"

const uint8 Com_SignalInitValue_EmotionSignal[1] = {0x0};
const uint8 Com_SignalInitValue_SleepSignal[1] = {0x0};
static uint8 SleepSignal_IPduBuffer[1];
static uint8 EmotionSignal_IPduBuffer[1];
/* I-PDU signal lists. */
static ComSignal_type ComSignal[] = {


    { /* Emotion Signal? */
        .ComHandleId                = COM_SIGNAL_ID_EMOTIONSIGNAL,
        .ComIPduHandleId            = COM_PDU_ID_EMOTIONPDU,
        .ComFirstTimeoutFactor      = 0,
        .ComNotification            = COM_NO_FUNCTION_CALLOUT,
        .ComTimeoutFactor           = 0,
        .ComTimeoutNotification     = COM_NO_FUNCTION_CALLOUT,
        .ComErrorNotification       = COM_NO_FUNCTION_CALLOUT,
        .ComTransferProperty        = PENDING,
        .ComUpdateBitPosition       = 0,
        .ComSignalUseUpdateBit      = FALSE,
        .ComSignalInitValue         = Com_SignalInitValue_EmotionSignal,
        .ComBitPosition             = 0,
        .ComBitSize                 = 4,
        .ComSignalEndianess         = COM_BIG_ENDIAN,
        .ComSignalType              = UINT8,
        .ComRxDataTimeoutAction     = NONE,
        .Com_EOL                    = FALSE
    },

    { /* Sleep Signal? */
        .ComHandleId                = COM_SIGNAL_ID_SLEEPSIGNAL,
        .ComIPduHandleId            = COM_PDU_ID_SLEEPPDU,
        .ComFirstTimeoutFactor      = 0,
        .ComNotification            = COM_NO_FUNCTION_CALLOUT,
        .ComTimeoutFactor           = 0,
        .ComTimeoutNotification     = COM_NO_FUNCTION_CALLOUT,
        .ComErrorNotification       = COM_NO_FUNCTION_CALLOUT,
        .ComTransferProperty        = PENDING,
        .ComUpdateBitPosition       = 0,
        .ComSignalUseUpdateBit      = FALSE,
        .ComSignalInitValue         = Com_SignalInitValue_SleepSignal,
        .ComBitPosition             = 0,
        .ComBitSize                 = 4,
        .ComSignalEndianess         = COM_BIG_ENDIAN,
        .ComSignalType              = UINT8,
        .ComRxDataTimeoutAction     = NONE,
        .Com_EOL                    = FALSE
    },

    {
        .Com_EOL                = TRUE
    }
};

/* Signal References */
static const ComSignal_type * const EmotionSignal_SignalRef[]={
        &ComSignal[COM_SIGNAL_ID_EMOTIONSIGNAL],
        NULL
};

static const ComSignal_type * const SleepSignal_SignalRef[]={
        &ComSignal[COM_SIGNAL_ID_SLEEPSIGNAL],
        NULL
};

    
/* I-PDU definitions */
static ComIPdu_type ComIPdu[] = {

    {
        .ComIPduCallout =  NULL,
        .IPduOutgoingId =  COM_PDU_ID_EMOTIONPDU,
        .ComIPduSignalProcessing =  DEFERRED,
        .ComIPduSize =  1,
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
        .ComIPduDataPtr =  EmotionSignal_IPduBuffer,
        .ComIPduDeferredDataPtr =  NULL,
        .ComIPduSignalRef =  EmotionSignal_SignalRef,
        .Com_EOL =  FALSE,
    },

    {
        .ComIPduCallout =  NULL,
        .IPduOutgoingId =  COM_PDU_ID_SLEEPPDU,
        .ComIPduSignalProcessing =  DEFERRED,
        .ComIPduSize =  1,
        .ComIPduDirection =  SEND,
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
        .ComIPduDataPtr =  SleepSignal_IPduBuffer,
        .ComIPduDeferredDataPtr =  NULL,
        .ComIPduSignalRef =  SleepSignal_SignalRef,
        .Com_EOL =  FALSE,
    },

    {
        .Com_EOL =  TRUE
    }
};

const Com_ConfigType ComConfiguration = {
    .ComIPdu =  ComIPdu,
    .ComSignal =  ComSignal,
    .ComNumOfSignals = 2,
    .ComNumOfIPDUs = 3
};