#ifndef STD_TYPES_H
#define STD_TYPES_H

#ifndef 	NULL
#define	NULL	0
#endif
#define FALSE 0
#define TRUE 1
typedef int 	             boolean;
typedef signed char  	     sint8;
typedef unsigned char 	     uint8;
typedef signed short int 	 sint16;
typedef unsigned short int  uint16;
typedef signed int 	         sint32;
typedef unsigned int 	     uint32;
typedef long long 	         sint64;
typedef unsigned long long 	 uint64;
typedef uint32 imask_t;

typedef struct {
	/* Recheck */
	uint16 vendorID;
	uint16 moduleID;
	uint8  instanceID;

	uint8 sw_major_version;    /* Vendor numbers */
	uint8 sw_minor_version;    /* Vendor numbers */
	uint8 sw_patch_version;    /* Vendor numbers */

	uint8 ar_major_version;    /* Autosar spec. numbers */
	uint8 ar_minor_version;    /* Autosar spec. numbers */
	uint8 ar_patch_version;    /* Autosar spec. numbers */
} Std_VersionInfoType;


typedef uint8 Std_ReturnType;

#define E_OK 					(Std_ReturnType)0
#define E_NOT_OK 				(Std_ReturnType)1

#define E_NO_DTC_AVAILABLE		(Std_ReturnType)2
#define E_SESSION_NOT_ALLOWED	(Std_ReturnType)4
#define E_PROTOCOL_NOT_ALLOWED	(Std_ReturnType)5
#define E_REQUEST_NOT_ACCEPTED	(Std_ReturnType)8
#define E_REQUEST_ENV_NOK		(Std_ReturnType)9
#ifndef E_PENDING
#define E_PENDING				(Std_ReturnType)10
#endif
#define E_COMPARE_KEY_FAILED	(Std_ReturnType)11
#define E_FORCE_RCRRP			(Std_ReturnType)12

void Det_ReportError(int a, ...);

#endif
