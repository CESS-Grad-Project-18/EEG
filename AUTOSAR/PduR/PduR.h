#ifndef PDUR_H
#define PDUR_H

#define PDUR_VENDOR_ID		   VENDOR_ID_MENTOR_GRAPHICS
#define PDUR_MODULE_ID		   5 /* Update */
#define PDUR_AR_MAJOR_VERSION  3
#define PDUR_AR_MINOR_VERSION  1
#define PDUR_AR_PATCH_VERSION  5
#define PDUR_SW_MAJOR_VERSION  2
#define PDUR_SW_MINOR_VERSION  0
#define PDUR_SW_PATCH_VERSION  0



/* ERROR CODES */
#define PDUR_E_CONFIG_PTR_INVALID 		0x06
#define PDUR_E_INVALID_REQUEST 			0x01
#define PDUR_E_PDU_ID_INVALID			0x02
#define PDUR_E_TP_TX_REQ_REJECTED		0x03
#define PDUR_E_DATA_PTR_INVALID			0x05
#define PDUR_E_BUFFER_ERROR				0x06
#define PDUR_E_INIT_FAILED				0x0X /* Check error code */

#include "PduR_Cfg.h"
#include "PduR_Types.h"


extern const PduR_PBConfigType *PduRConfig;

/*  The state of the PDU router. */
extern PduR_StateType PduRState;


/* General PDU Router functionality */
void PduR_Init(const PduR_PBConfigType* ConfigPtr); /* SID: 0x00 */
void PduR_GetVersionInfo(Std_VersionInfoType* versionInfo); /* SID: 0x17 */
uint32 PduR_GetConfigurationId(void); /* SID: 0x18 */


/* CAN Interface functions */
void PduR_CanIfRxIndication(PduIdType CanRxPduId, const uint8* CanSduPtr); /* SID: 0x01 */
void PduR_CanIfTxConfirmation(PduIdType CanTxPduId); /* SID: 0x02 */

/* COM */
Std_ReturnType PduR_ComTransmit(PduIdType ComTxPduId, const PduInfoType *PduInfoPtr); /* SID: 0x15 */


#endif /* PDUR_H */