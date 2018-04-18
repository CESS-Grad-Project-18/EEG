#include "PduR.h"
#include "../CanIf/CanIf.h"
#include "../COM/Com.h"
#include "../COM/Com_PBCfg.h"

const PduRDestPdu PduR_PduRDestination[] = {
    {
        .PduRDestPduDataProvision =  PDUR_DIRECT,
        .PduRDestPduHandleId =  CANIF_SIGNAL_ID_EMOTIONSIGNAL,
        .PduRDestTxBufferRef =  NULL,
        .DestModule =  PDUR_CANIF
    },

    {
        .PduRDestPduDataProvision = PDUR_DIRECT,
        .PduRDestPduHandleId =  CANIF_SIGNAL_ID_SLEEPSIGNAL,
        .PduRDestTxBufferRef =  NULL,
        .DestModule =  PDUR_COM
    }

};

const PduRDestPdu * const EmotionSignal_PduRDestinations[] =
{
	&PduR_PduRDestination[0]
};
const PduRDestPdu * const SleepSignal_PduRDestinations[] =
{
	&PduR_PduRDestination[1]
};

const PduRRoutingPath EmotionSignal_PduRRoutingPath = {
    .SduLength =  1,
    .SrcPduId =  COM_SIGNAL_ID_EMOTIONSIGNAL,
    .SrcModule =  PDUR_COM,
    .PduRDestPdu =  EmotionSignal_PduRDestinations
};

const PduRRoutingPath SleepSignal_PduRRoutingPath = {
    .SduLength =  1,
    .SrcPduId =  CANIF_ID_SleepSignal,
    .SrcModule =  PDUR_CANIF,
    .PduRDestPdu =  SleepSignal_PduRDestinations
};

const PduRRoutingPath * const PduRRoutingPaths[] = {
	&EmotionSignal_PduRRoutingPath,
	&SleepSignal_PduRRoutingPath,
    NULL
};  

const PduR_PBConfigType PduR_Config = {
    .PduR_PBConfigIdType =  0,
    .NRoutingPaths =  2,
    .RoutingPaths =  PduRRoutingPaths
};