#include "PduR.h"
#include "../CanIf/CanIf.h"
#include "../COM/Com.h"
#include "../COM/Com_PBCfg.h"
#include "PduR_PBCfg.h"

const Pdu PduR_Pdus[] = {
		{
				//.ComPduIdRef = &ComConfiguration.ComIPdu[COM_SIGNAL_ID_EMOTIONSIGNAL],
				.ComPduIdRef = NULL,
		},
		{
				//.ComPduIdRef = &ComConfiguration.ComIPdu[COM_SIGNAL_ID_SLEEPSIGNAL],
				.ComPduIdRef = NULL,
		},
};

const PduRDestPdu PduR_PduRDestination[] = {
    {
        .DataProvision =  PDUR_DIRECT,
        .PduRDestPduHandleId =  CANIF_SIGNAL_ID_EMOTIONSIGNAL,
        .TxBufferRef =  NULL,
		.DestPduRef = &PduR_Pdus[CANIF_SIGNAL_ID_EMOTIONSIGNAL],
        //.DestModule =  PDUR_CANIF
    },

    {
        .DataProvision = PDUR_DIRECT,
        .PduRDestPduHandleId =  CANIF_SIGNAL_ID_SLEEPSIGNAL,
        .TxBufferRef =  NULL,
		.DestPduRef = &PduR_Pdus[CANIF_SIGNAL_ID_SLEEPSIGNAL],
        //.DestModule =  PDUR_COM
    },

};

const PduRDestPdu * EmotionSignal_PduRDestinations[] = {
	&PduR_PduRDestination[0],
    NULL
};
const PduRDestPdu * SleepSignal_PduRDestinations[] = {
	&PduR_PduRDestination[1],
    NULL
};

const PduRRoutingPath EmotionSignal_PduRRoutingPath = {
    .SduLength =  1,
    //.SrcPduId =  COM_SIGNAL_ID_EMOTIONSIGNAL,
    .PduRDestPdu =  *EmotionSignal_PduRDestinations
};

const PduRRoutingPath SleepSignal_PduRRoutingPath = {
    .SduLength =  1,
    //.SrcPduId =  CANIF_ID_SleepSignal,
    .PduRDestPdu =  *SleepSignal_PduRDestinations
};

const PduRRoutingPath * PduR_RoutingPaths[] = {
	&EmotionSignal_PduRRoutingPath,
	&SleepSignal_PduRRoutingPath,
    NULL
};

const PduRRoutingTable PduR_RoutingTable[] = {
		{
			.PduRRoutingPath = *PduR_RoutingPaths,
		},
		{
			.PduRRoutingPath = NULL
		}
};

const PduR_PBConfigType PduR_Config = {
    .PduR_PBConfigIdType =  0,
    .RoutingTable =  PduR_RoutingTable,

};