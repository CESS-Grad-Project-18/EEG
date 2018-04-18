#include "Can.h"
#include "Calypso.h"
#include "../CanIf/CanIf_Cbk.h"
#include <stdlib.h>
#include <string.h>

uint32  MsgCode;              /* Received message buffer code */
uint32  MsgId;                /* Received message ID */
uint32  MsgLen;            /* Recieved message number of data bytes */
uint8   MsgData[8];           /* Received message data string*/
uint32  MsgTs;         /* Received message time */

typedef enum {
    CAN_UNINIT = 0,
    CAN_READY
} Can_DriverStateType;


Can_ReturnType Can_SetControllerMode(uint8 controller, Can_StateTransitionType transition) {
    imask_t state;
    CAN_HW_t *canHw;
    Can_ReturnType rv = CAN_OK;
    VALIDATE((controller < GET_CONTROLLER_CNT()), 0x3, CAN_E_PARAM_CONTROLLER);
    Can_UnitType *canUnit = GET_PRIVATE_DATA(controller);
    VALIDATE((canUnit->state != CANIF_CS_UNINIT), 0x3, CAN_E_UNINIT);
    canHw = GetController(controller);
    switch (transition) {
        case CAN_T_START:
            canUnit->state = CANIF_CS_STARTED;
            Irq_Save(state);
            if (canUnit->lock_cnt == 0) {   // REQ CAN196
                Can_EnableControllerInterrupts(controller);
            }
            Irq_Restore(state);
            break;
        case CAN_T_WAKEUP:
            VALIDATE(canUnit->state == CANIF_CS_SLEEP, 0x3, CAN_E_TRANSITION);
            canUnit->state = CANIF_CS_STOPPED;
            break;
        /* @req CAN258 */
        /* @req CAN290 */
        case CAN_T_SLEEP:
            VALIDATE(canUnit->state == CANIF_CS_STOPPED, 0x3, CAN_E_TRANSITION);
            /* Enable wake up irq */
            canUnit->state = CANIF_CS_SLEEP;
            break;
        case CAN_T_STOP:
            canUnit->state = CANIF_CS_STOPPED;
            Can_AbortTx(canHw, canUnit); // CANIF282
            break;
        default:
            // Should be reported to DEM but DET is the next best
            VALIDATE(canUnit->state == CANIF_CS_STOPPED, 0x3, CAN_E_TRANSITION);
            break;
    }
    return rv;
}

void Can_DisableControllerInterrupts(uint8 controller) {
}

void Can_EnableControllerInterrupts(uint8 controller) {
}

Can_ReturnType Can_Write(Can_HTHType hth, Can_PduType *pduInfo) {
    Can_ReturnType rv = CAN_OK;
    CAN_HW_t *canHw;
    const Can_HardwareObjectType *hohObj;
    const Can_ControllerConfigType *canHwConfig;
    uint32 controller;
    imask_t state;

    if(Can_Global.initRun != CAN_READY){
        Det_ReportError(0x6, CAN_E_UNINIT);
        return CAN_NOT_OK;
    }
    if(pduInfo == NULL){
        Det_ReportError(0x6, CAN_E_PARAM_POINTER);
        return CAN_NOT_OK;
    }
    if(pduInfo->length > 8){
        Det_ReportError(0x6, CAN_E_PARAM_DLC);
        return CAN_NOT_OK;
    }
    if(hth > NUM_OF_HTHS){
        Det_ReportError(0x6, CAN_E_PARAM_HANDLE);
        return CAN_NOT_OK;
    }

    hohObj = Can_FindHoh(hth, &controller);
    if (hohObj == NULL)
        return CAN_NOT_OK;

    Can_UnitType *canUnit = Can_GetPrivateData(controller);

    canHw = GetController(controller);
    Irq_Save(state);

    // check for any free box
    if ((canHw->TIER & BM_TX0) == 0u) {

        canHwConfig = Can_GetControllerConfig(Can_Global.channelMap[controller]);

        /* Copy data to Msg Box Start */
        canHw->txMsg[0].id = pduInfo->id;
        canHw->txMsg[0].dlc = pduInfo->length;
        assert(pduInfo->length <= 8);
        memcpy(canHw->txMsg[0].data, pduInfo->sdu, pduInfo->length);
        /* Copy data to Msg Box End */
        if ((canHwConfig->CanTxProcessing == INTERRUPT) &&
            (canUnit->lock_cnt == 0)) {
            /* Turn on the tx interrupt mailboxes */
            canHw->TIER = BM_TX0; // We only use TX0
            Can_SocketTriggerTx(controller);
        }
        /* Store pdu handle in unit to be used by TxConfirmation */
        canUnit->swPduHandle = pduInfo->swPduHandle;

    } else {
        rv = CAN_BUSY;
    }
    Irq_Restore(state);

    return rv;
}

void Can_MainFunction_Write_0(void) {
    uint8 i;
    const uint8_t TxData[] = {"Test"}; /* Transmit string*/
    CAN_0.MB[0].CS.B.IDE = 0; /* Use standard ID length */
    CAN_0.MB[0].ID.B.ID_STD = 0x555;/* Transmit ID is 0x555 */
    CAN_0.MB[0].CS.B.RTR = 0; /* Data frame, not remote Tx request frame */
    CAN_0.MB[0].CS.B.DLC = sizeof(TxData) - 1; /*#bytes to transmit excluding null*/
    for (i = 0; i < sizeof(TxData); i++) {
        CAN_0.MB[0].DATA.B[i] = TxData[i]; /* Data to be transmitted */
    }
    CAN_0.MB[0].CS.B.SRR = 1; /* Tx frame (not req'd for standard frame)*/
    CAN_0.MB[0].CS.B.CODE = 0xC; /* Activate msg. buf. to transmit data frame */
}

void Can_MainFunction_Write_1(void) {
    uint8 i;
    const uint8 TxData[] = {"Test"}; /* Transmit string*/
    CAN_1.MB[0].CS.B.IDE = 0; /* Use standard ID length */
    CAN_1.MB[0].ID.B.ID_STD = 0x555;/* Transmit ID is 0x555 */
    CAN_1.MB[0].CS.B.RTR = 0; /* Data frame, not remote Tx request frame */
    CAN_1.MB[0].CS.B.DLC = sizeof(TxData) - 1; /*#bytes to transmit excluding null*/
    for (i = 0; i < sizeof(TxData); i++) {
        CAN_1.MB[0].DATA.B[i] = TxData[i]; /* Data to be transmitted */
    }
    CAN_1.MB[0].CS.B.SRR = 1; /* Tx frame (not req'd for standard frame)*/
    CAN_1.MB[0].CS.B.CODE = 0xC; /* Activate msg. buf. to transmit data frame */
}

void Can_MainFunction_Read_0(void) {
    uint8 i;
    uint32 timer;
    while (CAN_0.IFLAG1.B.BUF4TO1I != 8) {}; /* Wait for CAN 0 MB 4 flag */
    RxCODE = CAN_0.MB[4].CS.B.CODE; /* Read CODE, ID, LENGTH, DATA, TIMESTAMP*/
    RxID = CAN_0.MB[4].ID.B.ID_STD;
    RxLENGTH = CAN_0.MB[4].CS.B.DLC;
    for (i = 0; i < RxLENGTH; i++) {
        RxDATA[i] = CAN_0.MB[4].DATA.B[i];
    }
    RxTIMESTAMP = CAN_0.MB[4].CS.B.TIMESTAMP;
    timer = CAN_0.TIMER.R; /* Read TIMER to unlock message buffers */
    CAN_0.IFLAG1.R = 0x00000010; /* Clear CAN 1 MB 4 flag */
}

void Can_MainFunction_Read_1(void) {
    uint8 i;
    uint32 timer;
    while (CAN_1.IFLAG1.B.BUF4TO1I != 8) {}; /* Wait for CAN 1 MB 4 flag */
    RxCODE = CAN_1.MB[4].CS.B.CODE; /* Read CODE, ID, LENGTH, DATA, TIMESTAMP*/
    RxID = CAN_1.MB[4].ID.B.ID_STD;
    RxLENGTH = CAN_1.MB[4].CS.B.DLC;
    for (i = 0; i < RxLENGTH; i++) {
        RxDATA[i] = CAN_1.MB[4].DATA.B[i];
    }
    RxTIMESTAMP = CAN_1.MB[4].CS.B.TIMESTAMP;
    timer = CAN_1.TIMER.R; /* Read TIMER to unlock message buffers */
    CAN_1.IFLAG1.R = 0x00000010; /* Clear CAN 1 MB 4 flag */
}


void Can_Init(const Can_ConfigType *Config) {
    // Do initial configuration of layer here
}

void Can_InitController(uint8 controller, const Can_ControllerConfigType *config) {
    uint8 i;
    switch (controller) {
        case 0: /* Used for transmission */
            CAN_0.MCR.B.MDIS = 1; /* Disable module before selecting clock source*/
            CAN_0.CTRL1.B.CLKSRC = 0; /* Clock Source = oscillator clock (40 MHz) */
            CAN_0.MCR.B.MDIS = 0; /* Enable module for config. (Sets FRZ, HALT)*/
            while (!CAN_0.MCR.B.FRZACK); /* Wait for freeze acknowledge to set */
            CAN_0.CTRL1.R = 0x04DB0086; /* CAN bus: 40 MHz clksrc, 500K bps with 16 tq */
            for (i = 0; i < 96; i++) { /* MPC574xG has 96 buffers after rev 0 */
                CAN_0.MB[i].CS.B.CODE = 0; /* Deactivate all message buffers */
            }
            CAN_0.MB[0].CS.B.CODE = 8; /* Message Buffer 0 set to TX INACTIVE */
            SIUL2.MSCR[16].B.SSS = 1; /* Pad PB0: Source signal is CAN0_TX */
            SIUL2.MSCR[16].B.OBE = 1; /* Pad PB0: Output Buffer Enable */
            SIUL2.MSCR[16].B.SRC = 3; /* Pad PB0: Maximum slew rate */
            SIUL2.MSCR[17].B.IBE = 1; /* Pad PB1: Enable pad for input - CAN0_RX */
            SIUL2.IMCR[188].B.SSS = 2; /* CAN0_RX: connected to pad PB1 */
            CAN_0.MCR.R = 0x0000003F; /* Negate FlexCAN 0 halt state for 64 MB */
            while (CAN_0.MCR.B.FRZACK & CAN_0.MCR.B.NOTRDY); /* Wait to clear */
            break;
        case 1: /* Used for reception */
            CAN_1.MCR.B.MDIS = 1; /* Disable module before selecting clock source*/
            CAN_1.CTRL1.B.CLKSRC = 0; /* Clock Source = oscillator clock (40 MHz) */
            CAN_1.MCR.B.MDIS = 0; /* Enable module for config. (Sets FRZ, HALT)*/
            while (!CAN_1.MCR.B.FRZACK); /* Wait for freeze acknowledge to set */
            CAN_1.CTRL1.R = 0x04DB0086; /* Can bus: Same as CAN_0*/
            for (i = 0; i < 96; i++) { /* MPC574xG has 96 buffers after rev 0 */
                CAN_1.MB[i].CS.B.CODE = 0; /* Deactivate all message buffers */
            }
            CAN_1.MB[4].CS.B.IDE = 0; /* Message Buffer 4 will look for a standard ID */
            CAN_1.MB[4].ID.B.ID_STD = 0x555; /* Message Buffer 4 will look for ID = 0x555 */
            CAN_1.MB[4].CS.B.CODE = 4; /* Message Buffer 4 set to RX EMPTY */
            CAN_1.RXMGMASK.R = 0x1FFFFFFF; /* Global acceptance mask */
            SIUL2.MSCR[42].B.SSS = 1; /* Pad PC10: Source signal is CAN1_TX */
            SIUL2.MSCR[42].B.SRC = 3; /* Pad PC10: Maximum slew rate */
            SIUL2.MSCR[42].B.OBE = 1; /* Pad PC10: Output Buffer Enable */
            SIUL2.MSCR[43].B.IBE = 1; /* Pad PC11: Enable pad for input -CAN1_RX */
            SIUL2.IMCR[189].B.SSS = 3; /* CAN1_RX : connected to pad PC11 */
            CAN_1.MCR.R = 0x0000003F; /* Negate FlexCAN 1 halt state for 64 MBs */
            while (CAN_1.MCR.B.FRZACK & CAN_1.MCR.B.NOTRDY); /* Wait to clear */
            break;
    }
}

Can_ReturnType Can_SetControllerMode(uint8 Controller, Can_StateTransitionType transition) {
    // Turn on off controller here depending on transition
    return E_OK;
}

Can_ReturnType Can_Write(Can_HwHandleType Hth, Can_PduType *pduInfo) {

    return E_OK;
}

void Can_DisableControllerInterrupts(uint8 controller) {
}

void Can_EnableControllerInterrupts(uint8 controller) {
}


void Can_MCSysInit(void) {
    MC_ME.ME.R = 0x000005FF;
    MC_ME.RUN_PC[0].R = 0x000000FE;
    /* Connect XOSC to PLL */
    MC_CGM.AC5_SC.B.SELCTL = 1;
    /* Configure PLL0 Dividers - 160MHz from 40Mhx XOSC */
    PLLDIG.PLLDV.B.PREDIV = 2;
    PLLDIG.PLLDV.B.MFD = 32;
    PLLDIG.PLLDV.B.RFDPHI = 1;
    PLLDIG.PLLCAL3.R = 0x09C3C000;
    PLLDIG.PLLFD.B.SMDEN = 1;       /* Sigma delta modulation disabled */
    /* switch to PLL */
    MC_ME.DRUN_MC.R = 0x00130172;    /* FLASH in normal mode, PLLON, FXOSC ON, Use PLL_PHI_0 */
    MC_ME.MCTL.R = 0x30005AF0;    /* DRUN target mode + KEY */
    MC_ME.MCTL.R = 0x3000A50F;    /* DRUN target mode + KEY Inverted */
    while (MC_ME.GS.B.S_MTRANS == 1); /* Wait for mode transition complete */
    /* Enable CLKOUT signal */
    /* System clock (160MHz divided by 20 = 8MHz) will be visible on pin PG[7] */
    /* Pin PG[7] is configured in SIUL2_Init() function */
    MC_CGM.AC6_DC0.B.DE = 1;        /* Enable output clock devided */
    MC_CGM.AC6_DC0.B.DIV = 0x13;    /* Divide output clock by 20 */
    MC_CGM.AC6_SC.B.SELCTL = 0xA;    /* PLL_CLKOUT1 */
    SIUL2.MSCR[103].R = 0x02000000 | 0x03;  //PG[7] - ODC_PUSH_PULL and SSS_PF8_SYSCLK0
}