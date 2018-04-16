#ifndef CAN_H_
#define CAN_H_


#define CAN_VENDOR_ID			    /* TODO: Add value */
#define CAN_MODULE_ID			    /* TODO: Add value */

#define CAN_SW_MAJOR_VERSION	1
#define CAN_SW_MINOR_VERSION 	0
#define CAN_SW_PATCH_VERSION	0

#define CAN_E_PARAM_POINTER    		0x01
#define CAN_E_PARAM_HANDLE     		0x02
#define CAN_E_PARAM_DLC        		0x03
#define CAN_E_PARAM_CONTROLLER 		0x04
#define CAN_E_UNINIT           		0x05
#define CAN_E_TRANSITION       		0x06
#define CAN_E_DATALOST         		0x07
#define CAN_E_PARAM_BAUDRATE   		0x08
#define CAN_E_ICOM_CONFIG_INVALID   0x09
#define CAN_E_INIT_FAILED   		0x0A

#define CAN_INIT_SERVICE_ID                         0x00
#define CAN_MAINFUNCTION_WRITE_SERVICE_ID           0x01
#define CAN_INITCONTROLLER_SERVICE_ID               0x02
#define CAN_SETCONTROLLERMODE_SERVICE_ID            0x03
#define CAN_DISABLECONTROLLERINTERRUPTS_SERVICE_ID  0x04
#define CAN_ENABLECONTROLLERINTERRUPTS_SERVICE_ID   0x05
#define CAN_WRITE_SERVICE_ID                        0x06
#define CAN_GETVERSIONINFO_SERVICE_ID               0x07
#define CAN_MAINFUNCTION_READ_SERVICE_ID            0x08
#define CAN_MAINFUNCTION_BUSOFF_SERVICE_ID          0x09
#define CAN_MAINFUNCTION_WAKEUP_SERVICE_ID          0x0A
#define CAN_CBK_CHECKWAKEUP_SERVICE_ID              0x0B


#if defined(CFG_PPC)

/* HOH flags */
#define CAN_HOH_FIFO_MASK           (1UL<<0)


/* Controller flags */
#define CAN_CTRL_RX_PROCESSING_INTERRUPT        (1UL<<0)
#define CAN_CTRL_RX_PROCESSING_POLLING          0
#define CAN_CTRL_TX_PROCESSING_INTERRUPT        (1UL<<1)
#define CAN_CTRL_TX_PROCESSING_POLLING          0
#define CAN_CTRL_WAKEUP_PROCESSING_INTERRUPT    (1UL<<2)
#define CAN_CTRL_WAKEUP_PROCESSING_POLLING      0
#define CAN_CTRL_BUSOFF_PROCESSING_INTERRUPT    (1UL<<3)
#define CAN_CTRL_BUSOFF_PROCESSING_POLLING      0
#define CAN_CTRL_ACTIVATION                     (1UL<<4)

#define CAN_CTRL_LOOPBACK                       (1UL<<5)
#define CAN_CTRL_FIFO                           (1UL<<6)

#define CAN_CTRL_ERROR_PROCESSING_INTERRUPT    (1UL<<7)
#define CAN_CTRL_ERROR_PROCESSING_POLLING      0

#endif

#include "Std_Types.h"
#include "CanIf_Types.h"
#include "ComStack_Types.h"
#include "Can_Cfg.h"


typedef struct{
	union{
        uint16 ID;  /* Standard 11 bit ID */
        uint32 IDE; /* Extended 29 bit ID */
    };
    uint8 Length;
    boolean Extended;
    boolean Error;
    boolean Remote;
    uint8* Sdu;
    /* SignalInfo* Signals; */
} Can_PduType;


/* Services affecting the complete hardware unit */
void Can_Init(const Can_ConfigType *Config); /* SID: 0x00 */
void Can_DeInit(void); /* TODO: check if needed */
void Can_GetVersionInfo(Std_VersionInfoType* versioninfo); /* SID: 0x07 */
Std_ReturnType Can_CheckBaudrate(uint8 Controller, uint16 Baudrate); /* SID: 0x0E */


/* Services affecting one single CAN Controller */
Std_ReturnType Can_ChangeBaudrate(uint8 Controller, uint16 Baudrate); /* SID: 0x0D */
Std_ReturnType Can_SetBaudrate(uint8 Controller, uint16 BaudRateConfigID); /* SID: 0x0F */
Can_ReturnType Can_SetControllerMode(uint8 Controller, Can_StateTransitionType Transition); /* SID: 0x03 */
void Can_DisableControllerInterrupts(uint8 Controller); /* SID: 0x04 */
void Can_EnableControllerInterrupts(uint8 Controller); /* SID: 0x05 */
void Can_CheckWakeup(uint8 Controller); /* SID: 0x0B */

void Can_InitController(uint8 Controller, const Can_ControllerConfigType *Config); /* TODO: check if needed */


/* Services affecting a Hardware Handle */
Can_ReturnType Can_Write(Can_HwHandleType Hth, const Can_PduType* PduInfo); /* SID: 0x06*/

/* 8.5 Scheduled functions */
void Can_MainFunction_Write(void); /* SID: 0x01 */
void Can_MainFunction_Read(void); /* SID: 0x08 */
void Can_MainFunction_BusOff(void) /* SID: 0x09 */
void Can_MainFunction_Wakeup(void); /* SID: 0x0A */
void Can_MainFunction_Mode(void); /* SID: 0x0C */

#endif


#endif /*CAN_H_*/
