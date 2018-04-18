#ifndef PDUR_TYPES_H
#define PDUR_TYPES_H

#include "../COM/ComStack_Types.h"

/* @req PDUR324 */
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
	uint16 PduR_PBConfigIdType;
	uint16 PduR_RoutingPathGroupIdType;
	PduR_StateType PduR_StateType;
} PduR_PBConfigType;
#endif