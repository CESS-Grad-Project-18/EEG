#ifndef CAN_H
#define CAN_H


#define CAN_VENDOR_ID			5   /* TODO: Add value */
#define CAN_MODULE_ID			4   /* TODO: Add value */

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

#include "../CanIf/CanIf_Types.h"
#include "../COM/ComStack_Types.h"
#include "Can_Cfg.h"
#include "Can_GeneralTypes.h"


/* Services affecting the complete hardware unit */
void Can_Init(const Can_ConfigType *Config); /* SID: 0x00 */


/* Services affecting one single CAN Controller */
Can_ReturnType Can_SetControllerMode(uint8 Controller, Can_StateTransitionType Transition); /* SID: 0x03 */
void Can_DisableControllerInterrupts(uint8 Controller); /* SID: 0x04 */
void Can_EnableControllerInterrupts(uint8 Controller); /* SID: 0x05 */
void Can_CheckWakeup(uint8 Controller); /* SID: 0x0B */

void Can_InitController(uint8 controller, const Can_ControllerType *config);


/* Services affecting a Hardware Handle */
Can_ReturnType Can_Write(Can_HwHandleType Hth, const Can_PduType* PduInfo); /* SID: 0x06*/

/* 8.5 Scheduled functions */
void Can_MainFunction_Write_0(void); /* SID: 0x01 */
void Can_MainFunction_Read_0(void); /* SID: 0x08 */
void Can_MainFunction_Write_1(void); /* SID: 0x01 */
void Can_MainFunction_Read_1(void); /* SID: 0x08 */


#endif /* CAN_H */