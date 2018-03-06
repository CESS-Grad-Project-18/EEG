#ifndef PDUR_TYPES_H
#define PDUR_TYPES_H

#include "ComStack_Types.h"

/* PduR_StateType defines the states of which the PDU router can be in */
typedef enum {
	PDUR_UNINIT, /* PDU Router is not initialized. */
	PDUR_ONLINE, /* PDU Router initialized successfully. */
	PDUR_REDUCED /* PDU Router initialization did not succeed. Only minimum routing is provided. */
} PduR_StateType;

typedef struct {
	/* Link-time data configuration of PDU router, implemented in PduR_Lcfg.c */
} PduR_LConfigType;

typedef struct {
	/* post-build-time data configuration of PDU router, implemented in PduR_PBcfg.c */
	uint8 PduRConfigurationId;
	uint8 NRoutingPaths;

	/* The routing table of this PDU router configuration. */
	const PduRRoutingPath_type * const*RoutingPaths;
	PduRTpBufferInfo_type *TpBuffers;
	PduRTpBufferInfo_type **TpRouteBuffers;

} PduR_PBConfigType;
#endif