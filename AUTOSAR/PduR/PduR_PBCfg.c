#include "PduR.h"
#include "../CanIf/CanIf.h"
#include "../COM/Com.h"
#include "../COM/Com_PBCfg.h"
#include "PduR_PBCfg.h"

const PduRDestPdu PduR_PduRDestination[] = {
    {
        .DataProvision =  PDUR_DIRECT,
        .PduRDestPduHandleId =  CANIF_SIGNAL_ID_EMOTIONSIGNAL,
        .TxBufferRef =  NULL,
        //.DestModule =  PDUR_CANIF
    },

    {
        .DataProvision = PDUR_DIRECT,
        .PduRDestPduHandleId =  CANIF_SIGNAL_ID_SLEEPSIGNAL,
        .TxBufferRef =  NULL,
        //.DestModule =  PDUR_COM
    }

};

const PduRDestPdu * const EmotionSignal_PduRDestinations[] = {
	&PduR_PduRDestination[0],
    NULL
};
const PduRDestPdu * const SleepSignal_PduRDestinations[] = {
	&PduR_PduRDestination[1],
    NULL
};

const PduRRoutingPath EmotionSignal_PduRRoutingPath = {
    .SduLength =  1,
    //.SrcPduId =  COM_SIGNAL_ID_EMOTIONSIGNAL,
    .PduRDestPdu =  EmotionSignal_PduRDestinations
};

const PduRRoutingPath SleepSignal_PduRRoutingPath = {
    .SduLength =  1,
    //.SrcPduId =  CANIF_ID_SleepSignal,
    .PduRDestPdu =  SleepSignal_PduRDestinations
};

const PduRRoutingPath * const PduR_RoutingPaths[] = {
	&EmotionSignal_PduRRoutingPath,
	&SleepSignal_PduRRoutingPath,
    NULL
};

const PduRRoutingTable * const PduR_RoutingTable[] = {
		&PduR_RoutingPaths,
		NULL
};

const PduR_PBConfigType PduR_Config = {
    .PduR_PBConfigIdType =  0,
    .RoutingTable =  PduR_RoutingTable,

};