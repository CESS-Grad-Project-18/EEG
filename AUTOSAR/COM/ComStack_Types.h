#ifndef COMSTACK_TYPES_H
#define COMSTACK_TYPES_H

#define ECUC_SW_MAJOR_VERSION   1
#define ECUC_SW_MINOR_VERSION   0
#define ECUC_SW_PATCH_VERSION   0

#include "Std_Types.h"

typedef uint16 PduIdType;
typedef uint8 PduLengthType;
typedef struct PduInfoType {
	uint8 *SduDataPtr;			/* Payload */
	PduLengthType SduLength;	/* Length of SDU */
} PduInfoType;

typedef enum TpDataStateType {
	TP_DATACONF,
	TP_DATARETRY,
	TP_CONFPENDING,
	TP_NORETRY,
} TpDataStateType;

typedef struct RetryInfoType {
	TpDataStateType TpDataState;
	PduLengthType TxTpDataCnt;
} RetryInfoType;


typedef enum BufReq_ReturnType {
	BUFREQ_OK=0,
	BUFREQ_NOT_OK,
	BUFREQ_BUSY,
	BUFREQ_OVFL
} BufReq_ReturnType;


typedef uint8 NotifResultType;

#define NTFRSLT_OK						0x00
#define NTFRSLT_E_NOT_OK				0x01
#define NTFRSLT_E_CANCELATION_NOT_OK	0x0C
#define NTFRSLT_E_WRONG_SN 				0x05
#define NTFRSLT_E_NO_BUFFER 			0x09


typedef uint8 BusTrcvErrorType;


#define BUSTRCV_NO_ERROR	0x00
#define BUSBUSTRCV_E_ERROR	0x01


#define COMSTACKTYPE_AR_MINOR_VERSION		1
#define COMSTACKTYPE_AR_MAJOR_VERSION		0
#define COMSTACKTYPE_AR_PATCH_VERSION		0

typedef uint8 NetworkHandleType;

#endif /*COMSTACK_TYPES_H*/
