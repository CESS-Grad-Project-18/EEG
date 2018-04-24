#ifndef CALYPSO_H
#define CALYPSO_H
typedef uint8 uint8_t;
typedef volatile uint8 vuint8_t;
typedef volatile uint16 vuint16_t;
typedef volatile uint32 vuint32_t;
#ifdef __cplusplus
extern "C" {
#endif
#ifdef __MWERKS__
#pragma push
#pragma ANSI_strict off
#endif
#ifdef __ghs__
#pragma ghs nowarning 618
#endif
#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#endif

/*******************CAN 0**********************/
typedef union CAN_0_MCR_union_tag {    /* Module Configuration Register */
  vuint32_t R;
  struct {
    vuint32_t MDIS:1;                  /* Module Disable */
    vuint32_t FRZ:1;                   /* Freeze Enable */
    vuint32_t RFEN:1;                  /* Rx FIFO Enable */
    vuint32_t HALT:1;                  /* Halt FlexCAN */
    vuint32_t NOTRDY:1;                /* FlexCAN Not Ready */
    vuint32_t WAKMSK:1;                /* Wake Up Interrupt Mask */
    vuint32_t SOFTRST:1;               /* Soft Reset */
    vuint32_t FRZACK:1;                /* Freeze Mode Acknowledge */
    vuint32_t SUPV:1;                  /* Supervisor Mode */
    vuint32_t SLFWAK:1;                /* Self Wake Up */
    vuint32_t WRNEN:1;                 /* Warning Interrupt Enable */
    vuint32_t LPMACK:1;                /* Low-Power Mode Acknowledge */
    vuint32_t WAKSRC:1;                /* Wake Up Source */
    vuint32_t _unused_18:1;
    vuint32_t SRXDIS:1;                /* Self Reception Disable */
    vuint32_t IRMQ:1;                  /* Individual Rx Masking And Queue Enable */
    vuint32_t DMA:1;                   /* DMA Enable */
    vuint32_t PNET_EN:1;               /* Pretended Networking Enable */
    vuint32_t LPRIOEN:1;               /* Local Priority Enable */
    vuint32_t AEN:1;                   /* Abort Enable */
    vuint32_t FDEN:1;                  /* CAN FD operation enable */
    vuint32_t _unused_10:1;
    vuint32_t IDAM:2;                  /* ID Acceptance Mode */
    vuint32_t _unused_7:1;
    vuint32_t MAXMB:7;                 /* Number Of The Last Message Buffer */
  } B;
} CAN_0_MCR_tag;

typedef union CAN_0_CTRL1_union_tag {  /* Control 1 register */
  vuint32_t R;
  struct {
    vuint32_t PRESDIV:8;               /* Prescaler Division Factor */
    vuint32_t RJW:2;                   /* Resync Jump Width */
    vuint32_t PSEG1:3;                 /* Phase Segment 1 */
    vuint32_t PSEG2:3;                 /* Phase Segment 2 */
    vuint32_t BOFFMSK:1;               /* Bus Off Interrupt Mask */
    vuint32_t ERRMSK:1;                /* Error Interrupt Mask */
    vuint32_t CLKSRC:1;                /* CAN Engine Clock Source */
    vuint32_t LPB:1;                   /* Loop Back Mode */
    vuint32_t TWRNMSK:1;               /* Tx Warning Interrupt Mask */
    vuint32_t RWRNMSK:1;               /* Rx Warning Interrupt Mask */
    vuint32_t _unused_9:1;
    vuint32_t _unused_8:1;
    vuint32_t SMP:1;                   /* CAN Bit Sampling */
    vuint32_t BOFFREC:1;               /* Bus Off Recovery */
    vuint32_t TSYN:1;                  /* Timer Sync */
    vuint32_t LBUF:1;                  /* Lowest Buffer Transmitted First */
    vuint32_t LOM:1;                   /* Listen-Only Mode */
    vuint32_t PROPSEG:3;               /* Propagation Segment */
  } B;
} CAN_0_CTRL1_tag;

typedef union CAN_0_TIMER_union_tag {  /* Free Running Timer */
  vuint32_t R;
  struct {
    vuint32_t _unused_16:16;
    vuint32_t TIMER:16;                /* Timer Value */
  } B;
} CAN_0_TIMER_tag;

typedef union CAN_0_RXMGMASK_union_tag { /* Rx Mailboxes Global Mask Register */
  vuint32_t R;
  struct {
    vuint32_t MG:32;                   /* Rx Mailboxes Global Mask Bits */
  } B;
} CAN_0_RXMGMASK_tag;

typedef union CAN_0_RX14MASK_union_tag { /* Rx 14 Mask register */
  vuint32_t R;
  struct {
    vuint32_t RX14M:32;                /* Rx Buffer 14 Mask Bits */
  } B;
} CAN_0_RX14MASK_tag;

typedef union CAN_0_RX15MASK_union_tag { /* Rx 15 Mask register */
  vuint32_t R;
  struct {
    vuint32_t RX15M:32;                /* Rx Buffer 15 Mask Bits */
  } B;
} CAN_0_RX15MASK_tag;

typedef union CAN_0_ECR_union_tag {    /* Error Counter */
  vuint32_t R;
  struct {
    vuint32_t RXERRCNT_FAST:8;         /* Receive Error Counter for fast bits */
    vuint32_t TXERRCNT_FAST:8;         /* Transmit Error Counter for fast bits */
    vuint32_t RXERRCNT:8;              /* Receive Error Counter */
    vuint32_t TXERRCNT:8;              /* Transmit Error Counter */
  } B;
} CAN_0_ECR_tag;

typedef union CAN_0_ESR1_union_tag {   /* Error and Status 1 register */
  vuint32_t R;
  struct {
    vuint32_t BIT1ERR_FAST:1;          /* Bit1 Error in the Data Phase of CAN FD frames with the BRS bit set */
    vuint32_t BIT0ERR_FAST:1;          /* Bit0 Error in the Data Phase of CAN FD frames with the BRS bit set */
    vuint32_t _unused_29:1;
    vuint32_t CRCERR_FAST:1;           /* Cyclic Redundancy Check Error in the CRC field of CAN FD frames with the BRS bit set */
    vuint32_t FRMERR_FAST:1;           /* Form Error in the Data Phase of CAN FD frames with the BRS bit set */
    vuint32_t STFERR_FAST:1;           /* Stuffing Error in the Data Phase of CAN FD frames with the BRS bit set */
    vuint32_t _unused_22:4;
    vuint32_t ERROVR:1;                /* Error Overrun bit */
    vuint32_t ERRINT_FAST:1;           /* Error Interrupt for errors detected in the Data Phase of CAN FD frames with the BRS bit set */
    vuint32_t BOFFDONEINT:1;           /* Bus Off Done Interrupt */
    vuint32_t SYNCH:1;                 /* CAN Synchronization Status */
    vuint32_t TWRNINT:1;               /* Tx Warning Interrupt Flag */
    vuint32_t RWRNINT:1;               /* Rx Warning Interrupt Flag */
    vuint32_t BIT1ERR:1;               /* Bit1 Error */
    vuint32_t BIT0ERR:1;               /* Bit0 Error */
    vuint32_t ACKERR:1;                /* Acknowledge Error */
    vuint32_t CRCERR:1;                /* Cyclic Redundancy Check Error */
    vuint32_t FRMERR:1;                /* Form Error */
    vuint32_t STFERR:1;                /* Stuffing Error */
    vuint32_t TXWRN:1;                 /* TX Error Warning */
    vuint32_t RXWRN:1;                 /* Rx Error Warning */
    vuint32_t IDLE:1;
    vuint32_t TX:1;                    /* FlexCAN In Transmission */
    vuint32_t FLTCONF:2;               /* Fault Confinement State */
    vuint32_t RX:1;                    /* FlexCAN In Reception */
    vuint32_t BOFFINT:1;               /* Bus Off Interrupt */
    vuint32_t ERRINT:1;                /* Error Interrupt */
    vuint32_t WAKINT:1;                /* Wake-Up Interrupt */
  } B;
} CAN_0_ESR1_tag;

typedef union CAN_0_IMASK2_union_tag { /* Interrupt Masks 2 register */
  vuint32_t R;
  struct {
    vuint32_t BUF63TO32M:32;           /* Buffer MB i Mask */
  } B;
} CAN_0_IMASK2_tag;

typedef union CAN_0_IMASK1_union_tag { /* Interrupt Masks 1 register */
  vuint32_t R;
  struct {
    vuint32_t BUF31TO0M:32;            /* Buffer MB i Mask */
  } B;
} CAN_0_IMASK1_tag;

typedef union CAN_0_IFLAG2_union_tag { /* Interrupt Flags 2 register */
  vuint32_t R;
  struct {
    vuint32_t BUF63TO32I:32;           /* Buffer MB i Interrupt */
  } B;
} CAN_0_IFLAG2_tag;

typedef union CAN_0_IFLAG1_union_tag { /* Interrupt Flags 1 register */
  vuint32_t R;
  struct {
    vuint32_t BUF31TO8I:24;            /* Buffer MBi Interrupt */
    vuint32_t BUF7I:1;                 /* Buffer MB7 Interrupt Or "Rx FIFO Overflow" */
    vuint32_t BUF6I:1;                 /* Buffer MB6 Interrupt Or "Rx FIFO Warning" */
    vuint32_t BUF5I:1;                 /* Buffer MB5 Interrupt Or "Frames available in Rx FIFO" */
    vuint32_t BUF4TO1I:4;              /* Buffer MB i Interrupt Or "reserved" */
    vuint32_t BUF0I:1;                 /* Buffer MB0 Interrupt Or "reserved" */
  } B;
} CAN_0_IFLAG1_tag;

typedef union CAN_0_CTRL2_union_tag {  /* Control 2 register */
  vuint32_t R;
  struct {
    vuint32_t ERRMSK_FAST:1;           /* Error Interrupt Mask for errors detected in the Data Phase of fast CAN FD frames */
    vuint32_t BOFFDONEMSK:1;           /* Bus Off Done Interrupt Mask */
    vuint32_t _unused_29:1;
    vuint32_t _unused_28:1;
    vuint32_t RFFN:4;                  /* Number Of Rx FIFO Filters */
    vuint32_t TASD:5;                  /* Tx Arbitration Start Delay */
    vuint32_t MRP:1;                   /* Mailboxes Reception Priority */
    vuint32_t RRS:1;                   /* Remote Request Storing */
    vuint32_t EACEN:1;                 /* Entire Frame Arbitration Field Comparison Enable For Rx Mailboxes */
    vuint32_t TIMER_SRC:1;             /* Timer Source */
    vuint32_t _unused_14:1;
    vuint32_t _unused_13:1;
    vuint32_t _unused_12:1;
    vuint32_t _unused_11:1;
    vuint32_t _unused_2:9;
    vuint32_t _unused_1:1;
    vuint32_t _unused_0:1;
  } B;
} CAN_0_CTRL2_tag;

typedef union CAN_0_ESR2_union_tag {   /* Error and Status 2 register */
  vuint32_t R;
  struct {
    vuint32_t _unused_23:9;
    vuint32_t LPTM:7;                  /* Lowest Priority Tx Mailbox */
    vuint32_t _unused_15:1;
    vuint32_t VPS:1;                   /* Valid Priority Status */
    vuint32_t IMB:1;                   /* Inactive Mailbox */
    vuint32_t _unused_0:13;
  } B;
} CAN_0_ESR2_tag;

typedef union CAN_0_CRCR_union_tag {   /* CRC Register */
  vuint32_t R;
  struct {
    vuint32_t _unused_23:9;
    vuint32_t MBCRC:7;                 /* CRC Mailbox */
    vuint32_t _unused_15:1;
    vuint32_t TXCRC:15;                /* Transmitted CRC value */
  } B;
} CAN_0_CRCR_tag;

typedef union CAN_0_RXFGMASK_union_tag { /* Rx FIFO Global Mask register */
  vuint32_t R;
  struct {
    vuint32_t FGM:32;                  /* Rx FIFO Global Mask Bits */
  } B;
} CAN_0_RXFGMASK_tag;

typedef union CAN_0_RXFIR_union_tag {  /* Rx FIFO Information Register */
  vuint32_t R;
  struct {
    vuint32_t _unused_9:23;
    vuint32_t IDHIT:9;                 /* Identifier Acceptance Filter Hit Indicator */
  } B;
} CAN_0_RXFIR_tag;

typedef union CAN_0_CBT_union_tag {    /* CAN Bit Timing Register */
  vuint32_t R;
  struct {
    vuint32_t BTF:1;                   /* Bit Timing Format Enable */
    vuint32_t EPRESDIV:10;             /* Extended Prescaler Division Factor */
    vuint32_t _unused_20:1;
    vuint32_t ERJW:4;                  /* Extended Resync Jump Width */
    vuint32_t EPROPSEG:6;              /* Extended Propagation Segment */
    vuint32_t EPSEG1:5;                /* Extended Phase Segment 1 */
    vuint32_t EPSEG2:5;                /* Extended Phase Segment 2 */
  } B;
} CAN_0_CBT_tag;

typedef union CAN_0_IMASK3_union_tag { /* Interrupt Masks 3 Register */
  vuint32_t R;
  struct {
    vuint32_t BUF95TO64M:32;           /* Buffer MB i Mask */
  } B;
} CAN_0_IMASK3_tag;

typedef union CAN_0_IFLAG3_union_tag { /* Interrupt Flags 3 Register */
  vuint32_t R;
  struct {
    vuint32_t BUF95TO64:32;            /* Buffer MB i Interrupt */
  } B;
} CAN_0_IFLAG3_tag;

typedef union CAN_0_RAMn_union_tag {   /* Embedded RAM */
  vuint32_t R;
  struct {
    vuint32_t DATA_BYTE_0:8;           /* Data byte 0 of Rx/Tx frame. */
    vuint32_t DATA_BYTE_1:8;           /* Data byte 1 of Rx/Tx frame. */
    vuint32_t DATA_BYTE_2:8;           /* Data byte 2 of Rx/Tx frame. */
    vuint32_t DATA_BYTE_3:8;           /* Data byte 3 of Rx/Tx frame. */
  } B;
} CAN_0_RAMn_tag;

typedef union CAN_0_RXIMR_union_tag {  /* Rx Individual Mask Registers */
  vuint32_t R;
  struct {
    vuint32_t MI:32;                   /* Individual Mask Bits */
  } B;
} CAN_0_RXIMR_tag;

typedef union CAN_0_CTRL1_PN_union_tag { /* Pretended Networking Control 1 Register */
  vuint32_t R;
  struct {
    vuint32_t _unused_18:14;
    vuint32_t WTOF_MSK:1;              /* Wake Up by Timeout Flag Mask Bit */
    vuint32_t WUMF_MSK:1;              /* Wake Up by Match Flag Mask Bit */
    vuint32_t NMATCH:8;                /* Number of Messages Matching the Same Filtering Criteria */
    vuint32_t _unused_6:2;
    vuint32_t PLFS:2;                  /* Payload Filtering Selection */
    vuint32_t IDFS:2;                  /* ID Filtering Selection */
    vuint32_t FCS:2;                   /* Filtering Combination Selection */
  } B;
} CAN_0_CTRL1_PN_tag;

typedef union CAN_0_CTRL2_PN_union_tag { /* Pretended Networking Control 2 Register */
  vuint32_t R;
  struct {
    vuint32_t _unused_16:16;
    vuint32_t MATCHTO:16;              /* Timeout for No Message Matching the Filtering Criteria */
  } B;
} CAN_0_CTRL2_PN_tag;

typedef union CAN_0_WU_MTC_union_tag { /* Pretended Networking Wake Up Match Register */
  vuint32_t R;
  struct {
    vuint32_t _unused_18:14;
    vuint32_t WTOF:1;                  /* Wake Up by Timeout Flag Bit */
    vuint32_t WUMF:1;                  /* Wake Up by Match Flag Bit */
    vuint32_t MCOUNTER:8;              /* Number of Matches while in Pretended Networking */
    vuint32_t _unused_0:8;
  } B;
} CAN_0_WU_MTC_tag;

typedef union CAN_0_FLT_ID1_union_tag { /* Pretended Networking ID Filter 1 Register */
  vuint32_t R;
  struct {
    vuint32_t _unused_31:1;
    vuint32_t FLT_IDE:1;               /* ID Extended Filter */
    vuint32_t FLT_RTR:1;               /* Remote Transmission Request Filter */
    vuint32_t FLT_ID1:29;              /* ID Filter 1 for Pretended Networking filtering */
  } B;
} CAN_0_FLT_ID1_tag;

typedef union CAN_0_FLT_DLC_union_tag { /* Pretended Networking DLC Filter Register */
  vuint32_t R;
  struct {
    vuint32_t _unused_20:12;
    vuint32_t FLT_DLC_LO:4;            /* Lower Limit for Length of Data Bytes Filter */
    vuint32_t _unused_4:12;
    vuint32_t FLT_DLC_HI:4;            /* Upper Limit for Length of Data Bytes Filter */
  } B;
} CAN_0_FLT_DLC_tag;

typedef union CAN_0_PL1_LO_union_tag { /* Pretended Networking Payload Low Filter 1 Register */
  vuint32_t R;
  struct {
    vuint32_t Data_byte_0:8;           /* Payload Filter 1 low order bits for Pretended Networking payload filtering corresponding to the data byte 0. */
    vuint32_t Data_byte_1:8;           /* Payload Filter 1 low order bits for Pretended Networking payload filtering corresponding to the data byte 1. */
    vuint32_t Data_byte_2:8;           /* Payload Filter 1 low order bits for Pretended Networking payload filtering corresponding to the data byte 2. */
    vuint32_t Data_byte_3:8;           /* Payload Filter 1 low order bits for Pretended Networking payload filtering corresponding to the data byte 3. */
  } B;
} CAN_0_PL1_LO_tag;

typedef union CAN_0_PL1_HI_union_tag { /* Pretended Networking Payload High Filter 1 Register */
  vuint32_t R;
  struct {
    vuint32_t Data_byte_4:8;           /* Payload Filter 1 high order bits for Pretended Networking payload filtering corresponding to the data byte 4. */
    vuint32_t Data_byte_5:8;           /* Payload Filter 1 high order bits for Pretended Networking payload filtering corresponding to the data byte 5. */
    vuint32_t Data_byte_6:8;           /* Payload Filter 1 high order bits for Pretended Networking payload filtering corresponding to the data byte 6. */
    vuint32_t Data_byte_7:8;           /* Payload Filter 1 high order bits for Pretended Networking payload filtering corresponding to the data byte 7. */
  } B;
} CAN_0_PL1_HI_tag;

typedef union CAN_0_FLT_ID2_IDMASK_union_tag { /* Pretended Networking ID Filter 2 Register / ID Mask Register */
  vuint32_t R;
  struct {
    vuint32_t _unused_31:1;
    vuint32_t IDE_MSK:1;               /* ID Extended Mask Bit */
    vuint32_t RTR_MSK:1;               /* Remote Transmission Request Mask Bit */
    vuint32_t FLT_ID2_IDMASK:29;       /* ID Filter 2 for Pretended Networking Filtering / ID Mask Bits for Pretended Networking ID Filtering */
  } B;
} CAN_0_FLT_ID2_IDMASK_tag;

typedef union CAN_0_PL2_PLMASK_LO_union_tag { /* Pretended Networking Payload Low Filter 2 Register / Payload Low Mask Register */
  vuint32_t R;
  struct {
    vuint32_t Data_byte_0:8;           /* Payload Filter 2 low order bits / Payload Mask low order bits for Pretended Networking payload filtering corresponding to the data byte 0. */
    vuint32_t Data_byte_1:8;           /* Payload Filter 2 low order bits / Payload Mask low order bits for Pretended Networking payload filtering corresponding to the data byte 1. */
    vuint32_t Data_byte_2:8;           /* Payload Filter 2 low order bits / Payload Mask low order bits for Pretended Networking payload filtering corresponding to the data byte 2. */
    vuint32_t Data_byte_3:8;           /* Payload Filter 2 low order bits / Payload Mask low order bits for Pretended Networking payload filtering corresponding to the data byte 3. */
  } B;
} CAN_0_PL2_PLMASK_LO_tag;

typedef union CAN_0_PL2_PLMASK_HI_union_tag { /* Pretended Networking Payload High Filter 2 low order bits / Payload High Mask Register */
  vuint32_t R;
  struct {
    vuint32_t Data_byte_4:8;           /* Payload Filter 2 high order bits / Payload Mask high order bits for Pretended Networking payload filtering corresponding to the data byte 4. */
    vuint32_t Data_byte_5:8;           /* Payload Filter 2 high order bits / Payload Mask high order bits for Pretended Networking payload filtering corresponding to the data byte 5. */
    vuint32_t Data_byte_6:8;           /* Payload Filter 2 high order bits / Payload Mask high order bits for Pretended Networking payload filtering corresponding to the data byte 6. */
    vuint32_t Data_byte_7:8;           /* Payload Filter 2 high order bits / Payload Mask high order bits for Pretended Networking payload filtering corresponding to the data byte 7. */
  } B;
} CAN_0_PL2_PLMASK_HI_tag;

typedef union CAN_0_WMB_CS_union_tag { /* Wake Up Message Buffer Register for C/S */
  vuint32_t R;
  struct {
    vuint32_t _unused_23:9;
    vuint32_t SRR:1;                   /* Substitute Remote Request */
    vuint32_t IDE:1;                   /* ID Extended Bit */
    vuint32_t RTR:1;                   /* Remote Transmission Request Bit */
    vuint32_t DLC:4;                   /* Length of Data in Bytes */
    vuint32_t _unused_0:16;
  } B;
} CAN_0_WMB_CS_tag;

typedef union CAN_0_WMB_ID_union_tag { /* Wake Up Message Buffer Register for ID */
  vuint32_t R;
  struct {
    vuint32_t _unused_29:3;
    vuint32_t ID:29;                   /* Received ID under Pretended Networking mode */
  } B;
} CAN_0_WMB_ID_tag;

typedef union CAN_0_WMB_D03_union_tag { /* Wake Up Message Buffer Register for Data 0-3 */
  vuint32_t R;
  struct {
    vuint32_t Data_byte_0:8;           /* Received payload corresponding to the data byte 0 under Pretended Networking mode */
    vuint32_t Data_byte_1:8;           /* Received payload corresponding to the data byte 1 under Pretended Networking mode */
    vuint32_t Data_byte_2:8;           /* Received payload corresponding to the data byte 2 under Pretended Networking mode */
    vuint32_t Data_byte_3:8;           /* Received payload corresponding to the data byte 3 under Pretended Networking mode */
  } B;
} CAN_0_WMB_D03_tag;

typedef union CAN_0_WMB_D47_union_tag { /* Wake Up Message Buffer Register Data 4-7 */
  vuint32_t R;
  struct {
    vuint32_t Data_byte_4:8;           /* Received payload corresponding to the data byte 4 under Pretended Networking mode */
    vuint32_t Data_byte_5:8;           /* Received payload corresponding to the data byte 5 under Pretended Networking mode */
    vuint32_t Data_byte_6:8;           /* Received payload corresponding to the data byte 6 under Pretended Networking mode */
    vuint32_t Data_byte_7:8;           /* Received payload corresponding to the data byte 7 under Pretended Networking mode */
  } B;
} CAN_0_WMB_D47_tag;

typedef struct CAN_0_WMB_struct_tag {
  CAN_0_WMB_CS_tag CS;                 /* Wake Up Message Buffer Register for C/S */
  CAN_0_WMB_ID_tag ID;                 /* Wake Up Message Buffer Register for ID */
  CAN_0_WMB_D03_tag D03;               /* Wake Up Message Buffer Register for Data 0-3 */
  CAN_0_WMB_D47_tag D47;               /* Wake Up Message Buffer Register Data 4-7 */
} CAN_0_WMB_tag;

typedef union CAN_0_FDCTRL_union_tag { /* CAN FD Control Register */
  vuint32_t R;
  struct {
    vuint32_t FDRATE:1;                /* Bit Rate Switch Enable */
    vuint32_t _unused_27:4;
    vuint32_t _unused_25:2;
    vuint32_t _unused_24:1;
    vuint32_t MBDSR2:2;                /* Message Buffer Data Size for Region 2 */
    vuint32_t _unused_21:1;
    vuint32_t MBDSR1:2;                /* Message Buffer Data Size for Region 1 */
    vuint32_t _unused_18:1;
    vuint32_t MBDSR0:2;                /* Message Buffer Data Size for Region 0 */
    vuint32_t TDCEN:1;                 /* Transceiver Delay Compensation Enable */
    vuint32_t TDCFAIL:1;               /* Transceiver Delay Compensation Fail */
    vuint32_t _unused_13:1;
    vuint32_t TDCOFF:5;                /* Transceiver Delay Compensation Offset */
    vuint32_t _unused_6:2;
    vuint32_t TDCVAL:6;                /* Transceiver Delay Compensation Value */
  } B;
} CAN_0_FDCTRL_tag;

typedef union CAN_0_FDCBT_union_tag {  /* CAN FD Bit Timing Register */
  vuint32_t R;
  struct {
    vuint32_t _unused_30:2;
    vuint32_t FPRESDIV:10;             /* Fast Prescaler Division Factor */
    vuint32_t _unused_19:1;
    vuint32_t _unused_18:1;
    vuint32_t FRJW:2;                  /* Fast Resync Jump Width */
    vuint32_t _unused_15:1;
    vuint32_t FPROPSEG:5;              /* Fast Propagation Segment */
    vuint32_t _unused_8:2;
    vuint32_t FPSEG1:3;                /* Fast Phase Segment 1 */
    vuint32_t _unused_3:2;
    vuint32_t FPSEG2:3;                /* Fast Phase Segment 2 */
  } B;
} CAN_0_FDCBT_tag;

typedef union CAN_0_FDCRC_union_tag {  /* CAN FD CRC Register */
  vuint32_t R;
  struct {
    vuint32_t _unused_31:1;
    vuint32_t FD_MBCRC:7;              /* CRC Mailbox Number for FD_TXCRC */
    vuint32_t _unused_21:3;
    vuint32_t FD_TXCRC:21;             /* Extended Transmitted CRC value */
  } B;
} CAN_0_FDCRC_tag;

struct CAN_0_tag {
  CAN_0_MCR_tag MCR;                   /* Module Configuration Register */
  CAN_0_CTRL1_tag CTRL1;               /* Control 1 register */
  CAN_0_TIMER_tag TIMER;               /* Free Running Timer */
  uint8_t CAN_0_reserved0[4];
  CAN_0_RXMGMASK_tag RXMGMASK;         /* Rx Mailboxes Global Mask Register */
  CAN_0_RX14MASK_tag RX14MASK;         /* Rx 14 Mask register */
  CAN_0_RX15MASK_tag RX15MASK;         /* Rx 15 Mask register */
  CAN_0_ECR_tag ECR;                   /* Error Counter */
  CAN_0_ESR1_tag ESR1;                 /* Error and Status 1 register */
  CAN_0_IMASK2_tag IMASK2;             /* Interrupt Masks 2 register */
  CAN_0_IMASK1_tag IMASK1;             /* Interrupt Masks 1 register */
  CAN_0_IFLAG2_tag IFLAG2;             /* Interrupt Flags 2 register */
  CAN_0_IFLAG1_tag IFLAG1;             /* Interrupt Flags 1 register */
  CAN_0_CTRL2_tag CTRL2;               /* Control 2 register */
  CAN_0_ESR2_tag ESR2;                 /* Error and Status 2 register */
  uint8_t CAN_0_reserved1[8];
  CAN_0_CRCR_tag CRCR;                 /* CRC Register */
  CAN_0_RXFGMASK_tag RXFGMASK;         /* Rx FIFO Global Mask register */
  CAN_0_RXFIR_tag RXFIR;               /* Rx FIFO Information Register */
  CAN_0_CBT_tag CBT;                   /* CAN Bit Timing Register */
  uint8_t CAN_0_reserved2[24];
  CAN_0_IMASK3_tag IMASK3;             /* Interrupt Masks 3 Register */
  uint8_t CAN_0_reserved3[4];
  CAN_0_IFLAG3_tag IFLAG3;             /* Interrupt Flags 3 Register */
  uint8_t CAN_0_reserved4[8];
  CAN_0_RAMn_tag RAMn[384];            /* Embedded RAM */
  //CAN_0_RAMn_tag MB[384];               /* Embedded RAM */
  uint8_t CAN_0_reserved5[512];
  CAN_0_RXIMR_tag RXIMR[96];           /* Rx Individual Mask Registers */
  uint8_t CAN_0_reserved6[256];
  CAN_0_CTRL1_PN_tag CTRL1_PN;         /* Pretended Networking Control 1 Register */
  CAN_0_CTRL2_PN_tag CTRL2_PN;         /* Pretended Networking Control 2 Register */
  CAN_0_WU_MTC_tag WU_MTC;             /* Pretended Networking Wake Up Match Register */
  CAN_0_FLT_ID1_tag FLT_ID1;           /* Pretended Networking ID Filter 1 Register */
  CAN_0_FLT_DLC_tag FLT_DLC;           /* Pretended Networking DLC Filter Register */
  CAN_0_PL1_LO_tag PL1_LO;             /* Pretended Networking Payload Low Filter 1 Register */
  CAN_0_PL1_HI_tag PL1_HI;             /* Pretended Networking Payload High Filter 1 Register */
  CAN_0_FLT_ID2_IDMASK_tag FLT_ID2_IDMASK; /* Pretended Networking ID Filter 2 Register / ID Mask Register */
  CAN_0_PL2_PLMASK_LO_tag PL2_PLMASK_LO; /* Pretended Networking Payload Low Filter 2 Register / Payload Low Mask Register */
  CAN_0_PL2_PLMASK_HI_tag PL2_PLMASK_HI; /* Pretended Networking Payload High Filter 2 low order bits / Payload High Mask Register */
  uint8_t CAN_0_reserved7[24];
  CAN_0_WMB_tag WMB[4];
  uint8_t CAN_0_reserved8[128];
  CAN_0_FDCTRL_tag FDCTRL;             /* CAN FD Control Register */
  CAN_0_FDCBT_tag FDCBT;               /* CAN FD Bit Timing Register */
  CAN_0_FDCRC_tag FDCRC;               /* CAN FD CRC Register */
};

/*******************CAN 1**********************/

typedef union CAN_MCR_union_tag {      /* Module Configuration Register */
  vuint32_t R;
  struct {
    vuint32_t MDIS:1;                  /* Module Disable */
    vuint32_t FRZ:1;                   /* Freeze Enable */
    vuint32_t RFEN:1;                  /* Rx FIFO Enable */
    vuint32_t HALT:1;                  /* Halt FlexCAN */
    vuint32_t NOTRDY:1;                /* FlexCAN Not Ready */
    vuint32_t WAKMSK:1;                /* Wake Up Interrupt Mask */
    vuint32_t SOFTRST:1;               /* Soft Reset */
    vuint32_t FRZACK:1;                /* Freeze Mode Acknowledge */
    vuint32_t SUPV:1;                  /* Supervisor Mode */
    vuint32_t SLFWAK:1;                /* Self Wake Up */
    vuint32_t WRNEN:1;                 /* Warning Interrupt Enable */
    vuint32_t LPMACK:1;                /* Low-Power Mode Acknowledge */
    vuint32_t WAKSRC:1;                /* Wake Up Source */
    vuint32_t _unused_18:1;
    vuint32_t SRXDIS:1;                /* Self Reception Disable */
    vuint32_t IRMQ:1;                  /* Individual Rx Masking And Queue Enable */
    vuint32_t DMA:1;                   /* DMA Enable */
    vuint32_t _unused_14:1;
    vuint32_t LPRIOEN:1;               /* Local Priority Enable */
    vuint32_t AEN:1;                   /* Abort Enable */
    vuint32_t FDEN:1;                  /* CAN FD operation enable */
    vuint32_t _unused_10:1;
    vuint32_t IDAM:2;                  /* ID Acceptance Mode */
    vuint32_t _unused_7:1;
    vuint32_t MAXMB:7;                 /* Number Of The Last Message Buffer */
  } B;
} CAN_MCR_tag;

typedef union CAN_CTRL1_union_tag {    /* Control 1 register */
  vuint32_t R;
  struct {
    vuint32_t PRESDIV:8;               /* Prescaler Division Factor */
    vuint32_t RJW:2;                   /* Resync Jump Width */
    vuint32_t PSEG1:3;                 /* Phase Segment 1 */
    vuint32_t PSEG2:3;                 /* Phase Segment 2 */
    vuint32_t BOFFMSK:1;               /* Bus Off Interrupt Mask */
    vuint32_t ERRMSK:1;                /* Error Interrupt Mask */
    vuint32_t CLKSRC:1;                /* CAN Engine Clock Source */
    vuint32_t LPB:1;                   /* Loop Back Mode */
    vuint32_t TWRNMSK:1;               /* Tx Warning Interrupt Mask */
    vuint32_t RWRNMSK:1;               /* Rx Warning Interrupt Mask */
    vuint32_t _unused_9:1;
    vuint32_t _unused_8:1;
    vuint32_t SMP:1;                   /* CAN Bit Sampling */
    vuint32_t BOFFREC:1;               /* Bus Off Recovery */
    vuint32_t TSYN:1;                  /* Timer Sync */
    vuint32_t LBUF:1;                  /* Lowest Buffer Transmitted First */
    vuint32_t LOM:1;                   /* Listen-Only Mode */
    vuint32_t PROPSEG:3;               /* Propagation Segment */
  } B;
} CAN_CTRL1_tag;

typedef union CAN_TIMER_union_tag {    /* Free Running Timer */
  vuint32_t R;
  struct {
    vuint32_t _unused_16:16;
    vuint32_t TIMER:16;                /* Timer Value */
  } B;
} CAN_TIMER_tag;

typedef union CAN_RXMGMASK_union_tag { /* Rx Mailboxes Global Mask Register */
  vuint32_t R;
  struct {
    vuint32_t MG:32;                   /* Rx Mailboxes Global Mask Bits */
  } B;
} CAN_RXMGMASK_tag;

typedef union CAN_RX14MASK_union_tag { /* Rx 14 Mask register */
  vuint32_t R;
  struct {
    vuint32_t RX14M:32;                /* Rx Buffer 14 Mask Bits */
  } B;
} CAN_RX14MASK_tag;

typedef union CAN_RX15MASK_union_tag { /* Rx 15 Mask register */
  vuint32_t R;
  struct {
    vuint32_t RX15M:32;                /* Rx Buffer 15 Mask Bits */
  } B;
} CAN_RX15MASK_tag;

typedef union CAN_ECR_union_tag {      /* Error Counter */
  vuint32_t R;
  struct {
    vuint32_t RXERRCNT_FAST:8;         /* Receive Error Counter for fast bits */
    vuint32_t TXERRCNT_FAST:8;         /* Transmit Error Counter for fast bits */
    vuint32_t RXERRCNT:8;              /* Receive Error Counter */
    vuint32_t TXERRCNT:8;              /* Transmit Error Counter */
  } B;
} CAN_ECR_tag;

typedef union CAN_ESR1_union_tag {     /* Error and Status 1 register */
  vuint32_t R;
  struct {
    vuint32_t BIT1ERR_FAST:1;          /* Bit1 Error in the Data Phase of CAN FD frames with the BRS bit set */
    vuint32_t BIT0ERR_FAST:1;          /* Bit0 Error in the Data Phase of CAN FD frames with the BRS bit set */
    vuint32_t _unused_29:1;
    vuint32_t CRCERR_FAST:1;           /* Cyclic Redundancy Check Error in the CRC field of CAN FD frames with the BRS bit set */
    vuint32_t FRMERR_FAST:1;           /* Form Error in the Data Phase of CAN FD frames with the BRS bit set */
    vuint32_t STFERR_FAST:1;           /* Stuffing Error in the Data Phase of CAN FD frames with the BRS bit set */
    vuint32_t _unused_22:4;
    vuint32_t ERROVR:1;                /* Error Overrun bit */
    vuint32_t ERRINT_FAST:1;           /* Error Interrupt for errors detected in the Data Phase of CAN FD frames with the BRS bit set */
    vuint32_t BOFFDONEINT:1;           /* Bus Off Done Interrupt */
    vuint32_t SYNCH:1;                 /* CAN Synchronization Status */
    vuint32_t TWRNINT:1;               /* Tx Warning Interrupt Flag */
    vuint32_t RWRNINT:1;               /* Rx Warning Interrupt Flag */
    vuint32_t BIT1ERR:1;               /* Bit1 Error */
    vuint32_t BIT0ERR:1;               /* Bit0 Error */
    vuint32_t ACKERR:1;                /* Acknowledge Error */
    vuint32_t CRCERR:1;                /* Cyclic Redundancy Check Error */
    vuint32_t FRMERR:1;                /* Form Error */
    vuint32_t STFERR:1;                /* Stuffing Error */
    vuint32_t TXWRN:1;                 /* TX Error Warning */
    vuint32_t RXWRN:1;                 /* Rx Error Warning */
    vuint32_t IDLE:1;
    vuint32_t TX:1;                    /* FlexCAN In Transmission */
    vuint32_t FLTCONF:2;               /* Fault Confinement State */
    vuint32_t RX:1;                    /* FlexCAN In Reception */
    vuint32_t BOFFINT:1;               /* Bus Off Interrupt */
    vuint32_t ERRINT:1;                /* Error Interrupt */
    vuint32_t WAKINT:1;                /* Wake-Up Interrupt */
  } B;
} CAN_ESR1_tag;

typedef union CAN_IMASK2_union_tag {   /* Interrupt Masks 2 register */
  vuint32_t R;
  struct {
    vuint32_t BUF63TO32M:32;           /* Buffer MB i Mask */
  } B;
} CAN_IMASK2_tag;

typedef union CAN_IMASK1_union_tag {   /* Interrupt Masks 1 register */
  vuint32_t R;
  struct {
    vuint32_t BUF31TO0M:32;            /* Buffer MB i Mask */
  } B;
} CAN_IMASK1_tag;

typedef union CAN_IFLAG2_union_tag {   /* Interrupt Flags 2 register */
  vuint32_t R;
  struct {
    vuint32_t BUF63TO32I:32;           /* Buffer MB i Interrupt */
  } B;
} CAN_IFLAG2_tag;

typedef union CAN_IFLAG1_union_tag {   /* Interrupt Flags 1 register */
  vuint32_t R;
  struct {
    vuint32_t BUF31TO8I:24;            /* Buffer MBi Interrupt */
    vuint32_t BUF7I:1;                 /* Buffer MB7 Interrupt Or "Rx FIFO Overflow" */
    vuint32_t BUF6I:1;                 /* Buffer MB6 Interrupt Or "Rx FIFO Warning" */
    vuint32_t BUF5I:1;                 /* Buffer MB5 Interrupt Or "Frames available in Rx FIFO" */
    vuint32_t BUF4TO1I:4;              /* Buffer MB i Interrupt Or "reserved" */
    vuint32_t BUF0I:1;                 /* Buffer MB0 Interrupt Or "reserved" */
  } B;
} CAN_IFLAG1_tag;

typedef union CAN_CTRL2_union_tag {    /* Control 2 register */
  vuint32_t R;
  struct {
    vuint32_t ERRMSK_FAST:1;           /* Error Interrupt Mask for errors detected in the Data Phase of fast CAN FD frames */
    vuint32_t BOFFDONEMSK:1;           /* Bus Off Done Interrupt Mask */
    vuint32_t _unused_29:1;
    vuint32_t _unused_28:1;
    vuint32_t RFFN:4;                  /* Number Of Rx FIFO Filters */
    vuint32_t TASD:5;                  /* Tx Arbitration Start Delay */
    vuint32_t MRP:1;                   /* Mailboxes Reception Priority */
    vuint32_t RRS:1;                   /* Remote Request Storing */
    vuint32_t EACEN:1;                 /* Entire Frame Arbitration Field Comparison Enable For Rx Mailboxes */
    vuint32_t TIMER_SRC:1;             /* Timer Source */
    vuint32_t _unused_14:1;
    vuint32_t _unused_13:1;
    vuint32_t _unused_12:1;
    vuint32_t _unused_11:1;
    vuint32_t _unused_2:9;
    vuint32_t _unused_1:1;
    vuint32_t _unused_0:1;
  } B;
} CAN_CTRL2_tag;

typedef union CAN_ESR2_union_tag {     /* Error and Status 2 register */
  vuint32_t R;
  struct {
    vuint32_t _unused_23:9;
    vuint32_t LPTM:7;                  /* Lowest Priority Tx Mailbox */
    vuint32_t _unused_15:1;
    vuint32_t VPS:1;                   /* Valid Priority Status */
    vuint32_t IMB:1;                   /* Inactive Mailbox */
    vuint32_t _unused_0:13;
  } B;
} CAN_ESR2_tag;

typedef union CAN_CRCR_union_tag {     /* CRC Register */
  vuint32_t R;
  struct {
    vuint32_t _unused_23:9;
    vuint32_t MBCRC:7;                 /* CRC Mailbox */
    vuint32_t _unused_15:1;
    vuint32_t TXCRC:15;                /* Transmitted CRC value */
  } B;
} CAN_CRCR_tag;

typedef union CAN_RXFGMASK_union_tag { /* Rx FIFO Global Mask register */
  vuint32_t R;
  struct {
    vuint32_t FGM:32;                  /* Rx FIFO Global Mask Bits */
  } B;
} CAN_RXFGMASK_tag;

typedef union CAN_RXFIR_union_tag {    /* Rx FIFO Information Register */
  vuint32_t R;
  struct {
    vuint32_t _unused_9:23;
    vuint32_t IDHIT:9;                 /* Identifier Acceptance Filter Hit Indicator */
  } B;
} CAN_RXFIR_tag;

typedef union CAN_CBT_union_tag {      /* CAN Bit Timing Register */
  vuint32_t R;
  struct {
    vuint32_t BTF:1;                   /* Bit Timing Format Enable */
    vuint32_t EPRESDIV:10;             /* Extended Prescaler Division Factor */
    vuint32_t _unused_20:1;
    vuint32_t ERJW:4;                  /* Extended Resync Jump Width */
    vuint32_t EPROPSEG:6;              /* Extended Propagation Segment */
    vuint32_t EPSEG1:5;                /* Extended Phase Segment 1 */
    vuint32_t EPSEG2:5;                /* Extended Phase Segment 2 */
  } B;
} CAN_CBT_tag;

typedef union CAN_IMASK3_union_tag {   /* Interrupt Masks 3 Register */
  vuint32_t R;
  struct {
    vuint32_t BUF95TO64M:32;           /* Buffer MB i Mask */
  } B;
} CAN_IMASK3_tag;

typedef union CAN_IFLAG3_union_tag {   /* Interrupt Flags 3 Register */
  vuint32_t R;
  struct {
    vuint32_t BUF95TO64:32;            /* Buffer MB i Interrupt */
  } B;
} CAN_IFLAG3_tag;

typedef union CAN_RAMn_union_tag {     /* Embedded RAM */
  vuint32_t R;
  struct {
    vuint32_t DATA_BYTE_0:8;           /* Data byte 0 of Rx/Tx frame. */
    vuint32_t DATA_BYTE_1:8;           /* Data byte 1 of Rx/Tx frame. */
    vuint32_t DATA_BYTE_2:8;           /* Data byte 2 of Rx/Tx frame. */
    vuint32_t DATA_BYTE_3:8;           /* Data byte 3 of Rx/Tx frame. */
  } B;
} CAN_RAMn_tag;

typedef union CAN_RXIMR_union_tag {    /* Rx Individual Mask Registers */
  vuint32_t R;
  struct {
    vuint32_t MI:32;                   /* Individual Mask Bits */
  } B;
} CAN_RXIMR_tag;

typedef union CAN_FDCTRL_union_tag {   /* CAN FD Control Register */
  vuint32_t R;
  struct {
    vuint32_t FDRATE:1;                /* Bit Rate Switch Enable */
    vuint32_t _unused_27:4;
    vuint32_t _unused_25:2;
    vuint32_t _unused_24:1;
    vuint32_t MBDSR2:2;                /* Message Buffer Data Size for Region 2 */
    vuint32_t _unused_21:1;
    vuint32_t MBDSR1:2;                /* Message Buffer Data Size for Region 1 */
    vuint32_t _unused_18:1;
    vuint32_t MBDSR0:2;                /* Message Buffer Data Size for Region 0 */
    vuint32_t TDCEN:1;                 /* Transceiver Delay Compensation Enable */
    vuint32_t TDCFAIL:1;               /* Transceiver Delay Compensation Fail */
    vuint32_t _unused_13:1;
    vuint32_t TDCOFF:5;                /* Transceiver Delay Compensation Offset */
    vuint32_t _unused_6:2;
    vuint32_t TDCVAL:6;                /* Transceiver Delay Compensation Value */
  } B;
} CAN_FDCTRL_tag;

typedef union CAN_FDCBT_union_tag {    /* CAN FD Bit Timing Register */
  vuint32_t R;
  struct {
    vuint32_t _unused_30:2;
    vuint32_t FPRESDIV:10;             /* Fast Prescaler Division Factor */
    vuint32_t _unused_19:1;
    vuint32_t _unused_18:1;
    vuint32_t FRJW:2;                  /* Fast Resync Jump Width */
    vuint32_t _unused_15:1;
    vuint32_t FPROPSEG:5;              /* Fast Propagation Segment */
    vuint32_t _unused_8:2;
    vuint32_t FPSEG1:3;                /* Fast Phase Segment 1 */
    vuint32_t _unused_3:2;
    vuint32_t FPSEG2:3;                /* Fast Phase Segment 2 */
  } B;
} CAN_FDCBT_tag;

typedef union CAN_FDCRC_union_tag {    /* CAN FD CRC Register */
  vuint32_t R;
  struct {
    vuint32_t _unused_31:1;
    vuint32_t FD_MBCRC:7;              /* CRC Mailbox Number for FD_TXCRC */
    vuint32_t _unused_21:3;
    vuint32_t FD_TXCRC:21;             /* Extended Transmitted CRC value */
  } B;
} CAN_FDCRC_tag;

struct CAN_1_7_tag {
  CAN_MCR_tag MCR;                     /* Module Configuration Register */
  CAN_CTRL1_tag CTRL1;                 /* Control 1 register */
  CAN_TIMER_tag TIMER;                 /* Free Running Timer */
  uint8_t CAN_reserved0[4];
  CAN_RXMGMASK_tag RXMGMASK;           /* Rx Mailboxes Global Mask Register */
  CAN_RX14MASK_tag RX14MASK;           /* Rx 14 Mask register */
  CAN_RX15MASK_tag RX15MASK;           /* Rx 15 Mask register */
  CAN_ECR_tag ECR;                     /* Error Counter */
  CAN_ESR1_tag ESR1;                   /* Error and Status 1 register */
  CAN_IMASK2_tag IMASK2;               /* Interrupt Masks 2 register */
  CAN_IMASK1_tag IMASK1;               /* Interrupt Masks 1 register */
  CAN_IFLAG2_tag IFLAG2;               /* Interrupt Flags 2 register */
  CAN_IFLAG1_tag IFLAG1;               /* Interrupt Flags 1 register */
  CAN_CTRL2_tag CTRL2;                 /* Control 2 register */
  CAN_ESR2_tag ESR2;                   /* Error and Status 2 register */
  uint8_t CAN_reserved1[8];
  CAN_CRCR_tag CRCR;                   /* CRC Register */
  CAN_RXFGMASK_tag RXFGMASK;           /* Rx FIFO Global Mask register */
  CAN_RXFIR_tag RXFIR;                 /* Rx FIFO Information Register */
  CAN_CBT_tag CBT;                     /* CAN Bit Timing Register */
  uint8_t CAN_reserved2[24];
  CAN_IMASK3_tag IMASK3;               /* Interrupt Masks 3 Register */
  uint8_t CAN_reserved3[4];
  CAN_IFLAG3_tag IFLAG3;               /* Interrupt Flags 3 Register */
  uint8_t CAN_reserved4[8];
  CAN_RAMn_tag RAMn[384];              /* Embedded RAM */
  uint8_t CAN_reserved5[512];
  CAN_RXIMR_tag RXIMR[96];             /* Rx Individual Mask Registers */
  uint8_t CAN_reserved6[512];
  CAN_FDCTRL_tag FDCTRL;               /* CAN FD Control Register */
  CAN_FDCBT_tag FDCBT;                 /* CAN FD Bit Timing Register */
  CAN_FDCRC_tag FDCRC;                 /* CAN FD CRC Register */
};

/**************************INTC*******************************/
typedef union INTC_BCR_union_tag {     /* INTC Block Configuration Register */
    vuint32_t R;
    struct {
        vuint32_t _unused_13:19;
        vuint32_t _unused_12:1;
        vuint32_t _unused_9:3;
        vuint32_t HVEN2:1;
        vuint32_t _unused_5:3;
        vuint32_t HVEN1:1;
        vuint32_t _unused_1:3;
        vuint32_t HVEN0:1;
    } B;
} INTC_BCR_tag;

typedef union INTC_MPROT_union_tag {   /* INTC Master Protection Register */
    vuint32_t R;
    struct {
        vuint32_t _unused_6:26;
        vuint32_t ID:2;
        vuint32_t _unused_1:3;
        vuint32_t MPROT:1;
    } B;
} INTC_MPROT_tag;

typedef union INTC_CPR_union_tag {     /* INTC Current Priority Register for Processor 0 */
    vuint32_t R;
    struct {
        vuint32_t _unused_4:28;
        vuint32_t PRI:4;
    } B;
} INTC_CPR_tag;

typedef union INTC_IACKR_union_tag {   /* INTC Interrupt Acknowledge Register for Processor 0 */
    vuint32_t R;
    struct {
        vuint32_t VTBA:20;
        vuint32_t INTVEC:10;
        vuint32_t _unused_0:2;
    } B;
} INTC_IACKR_tag;

typedef union INTC_EOIR_union_tag {    /* INTC End Of Interrupt Register for Processor 0 */
    vuint32_t R;
    struct {
        vuint32_t EOI:32;
    } B;
} INTC_EOIR_tag;

typedef union INTC_SSCIR_union_tag {   /* INTC Software Set/Clear Interrupt Register */
    vuint8_t R;
    struct {
        vuint8_t _unused_2:6;
        vuint8_t SET:1;
        vuint8_t CLR:1;
    } B;
} INTC_SSCIR_tag;

typedef union INTC_PSR_union_tag {     /* INTC Priority Select Register */
    vuint16_t R;
    struct {
        vuint16_t PRC_SELN0:1;
        vuint16_t PRC_SELN1:1;
        vuint16_t PRC_SELN2:1;
        vuint16_t _unused_12:1;
        vuint16_t _unused_9:3;
        vuint16_t SWTN:1;
        vuint16_t _unused_4:4;
        vuint16_t PRIN:4;
    } B;
} INTC_PSR_tag;

struct INTC_tag {
    INTC_BCR_tag BCR;                    /* INTC Block Configuration Register */
    INTC_MPROT_tag MPROT;                /* INTC Master Protection Register */
    uint8_t INTC_reserved0[8];
    INTC_CPR_tag CPR[3];                 /* INTC Current Priority Register for Processor 0 */
    uint8_t INTC_reserved1[4];
    INTC_IACKR_tag IACKR[3];             /* INTC Interrupt Acknowledge Register for Processor 0 */
    uint8_t INTC_reserved2[4];
    INTC_EOIR_tag EOIR[3];               /* INTC End Of Interrupt Register for Processor 0 */
    uint8_t INTC_reserved3[4];
    INTC_SSCIR_tag SSCIR[24];            /* INTC Software Set/Clear Interrupt Register */
    uint8_t INTC_reserved4[8];
    INTC_PSR_tag PSR[1024];              /* INTC Priority Select Register */
};

/*************************MC_CGM*****************************/

typedef union MC_CGM_CLKOUT1_SC_union_tag { /* Clockout 1 Select Register */
    vuint32_t R;
    struct {
        vuint32_t _unused_28:4;
        vuint32_t SELCTL:4;                /* CLKOUT1 Source Select */
        vuint32_t _unused_0:24;
    } B;
} MC_CGM_CLKOUT1_SC_tag;

typedef union MC_CGM_CLKOUT1_DC_union_tag { /* CLKOUT1_DC Configuration Register */
    vuint32_t R;
    struct {
        vuint32_t DE:1;                    /* CLKOUT1_DC enable */
        vuint32_t _unused_27:4;
        vuint32_t DIV:11;                  /* Divider */
        vuint32_t _unused_0:16;
    } B;
} MC_CGM_CLKOUT1_DC_tag;

typedef union MC_CGM_AC5_SC_union_tag { /* Auxiliary Clock 5 Select Control Register */
    vuint32_t R;
    struct {
        vuint32_t _unused_25:7;
        vuint32_t SELCTL:1;
        vuint32_t _unused_0:24;
    } B;
} MC_CGM_AC5_SC_tag;

typedef union MC_CGM_AC5_SS_union_tag { /* Auxiliary Clock 5 Select Status Register */
    vuint32_t R;
    struct {
        vuint32_t _unused_25:7;
        vuint32_t SELSTAT:1;
        vuint32_t _unused_0:24;
    } B;
} MC_CGM_AC5_SS_tag;

typedef union MC_CGM_SC_DC6_union_tag { /* System Clock Divider 6 Configuration Register */
    vuint32_t R;
    struct {
        vuint32_t DE:1;
        vuint32_t _unused_19:12;
        vuint32_t DIV:3;                   /* Divider */
        vuint32_t _unused_0:16;
    } B;
} MC_CGM_SC_DC6_tag;

typedef union MC_CGM_AC8_SC_union_tag { /* Auxiliary Clock 8 Select Control Register */
    vuint32_t R;
    struct {
        vuint32_t _unused_25:7;
        vuint32_t SELCTL:1;
        vuint32_t _unused_0:24;
    } B;
} MC_CGM_AC8_SC_tag;

typedef union MC_CGM_AC8_SS_union_tag { /* Auxiliary Clock 8 Select Status Register */
    vuint32_t R;
    struct {
        vuint32_t _unused_25:7;
        vuint32_t SELSTAT:1;
        vuint32_t _unused_0:24;
    } B;
} MC_CGM_AC8_SS_tag;

typedef union MC_CGM_AC9_SC_union_tag { /* Auxiliary Clock 9 Select Control Register */
    vuint32_t R;
    struct {
        vuint32_t _unused_25:7;
        vuint32_t SELCTL:1;
        vuint32_t _unused_0:24;
    } B;
} MC_CGM_AC9_SC_tag;

typedef union MC_CGM_AC9_SS_union_tag { /* Auxiliary Clock 9 Select Status Register */
    vuint32_t R;
    struct {
        vuint32_t _unused_25:7;
        vuint32_t SELSTAT:1;
        vuint32_t _unused_0:24;
    } B;
} MC_CGM_AC9_SS_tag;

typedef union MC_CGM_PCS_SDUR_union_tag { /* PCS Switch Duration Register */
    vuint8_t R;
    struct {
        vuint8_t SDUR:8;
    } B;
} MC_CGM_PCS_SDUR_tag;

typedef union MC_CGM_PCS_DIVC1_union_tag { /* PCS Divider Change Register 1 */
    vuint32_t R;
    struct {
        vuint32_t INIT:16;
        vuint32_t _unused_8:8;
        vuint32_t RATE:8;
    } B;
} MC_CGM_PCS_DIVC1_tag;

typedef union MC_CGM_PCS_DIVE1_union_tag { /* PCS Divider End Register 1 */
    vuint32_t R;
    struct {
        vuint32_t _unused_20:12;
        vuint32_t DIVE:20;
    } B;
} MC_CGM_PCS_DIVE1_tag;

typedef union MC_CGM_PCS_DIVS1_union_tag { /* PCS Divider Start Register 1 */
    vuint32_t R;
    struct {
        vuint32_t _unused_20:12;
        vuint32_t DIVS:20;
    } B;
} MC_CGM_PCS_DIVS1_tag;

typedef union MC_CGM_PCS_DIVC2_union_tag { /* PCS Divider Change Register 2 */
    vuint32_t R;
    struct {
        vuint32_t INIT:16;
        vuint32_t _unused_8:8;
        vuint32_t RATE:8;
    } B;
} MC_CGM_PCS_DIVC2_tag;

typedef union MC_CGM_PCS_DIVE2_union_tag { /* PCS Divider End Register 2 */
    vuint32_t R;
    struct {
        vuint32_t _unused_20:12;
        vuint32_t DIVE:20;
    } B;
} MC_CGM_PCS_DIVE2_tag;

typedef union MC_CGM_PCS_DIVS2_union_tag { /* PCS Divider Start Register 2 */
    vuint32_t R;
    struct {
        vuint32_t _unused_20:12;
        vuint32_t DIVS:20;
    } B;
} MC_CGM_PCS_DIVS2_tag;

typedef union MC_CGM_DIV_UPD_ABRTD_union_tag { /* Divider Update Abort Register */
    vuint32_t R;
    struct {
        vuint32_t _unused_1:31;
        vuint32_t DIV_UPD_ABRTD:1;
    } B;
} MC_CGM_DIV_UPD_ABRTD_tag;

typedef union MC_CGM_SC_DIV_RC_union_tag { /* System Clock Divider Ratio Change Register */
    vuint32_t R;
    struct {
        vuint32_t _unused_2:30;
        vuint32_t HALT_ABORT_DIS:1;
        vuint32_t SYS_DIV_RATIO_CHNG:1;
    } B;
} MC_CGM_SC_DIV_RC_tag;

typedef union MC_CGM_DIV_UPD_TYPE_union_tag { /* Divider Update Type Register */
    vuint32_t R;
    struct {
        vuint32_t SYS_UPD_TYPE:1;          /* System Clock Divider Update Type */
        vuint32_t _unused_7:24;
        vuint32_t _unused_6:1;
        vuint32_t _unused_0:6;
    } B;
} MC_CGM_DIV_UPD_TYPE_tag;

typedef union MC_CGM_DIV_UPD_TRIG_union_tag { /* Divider Update Trigger Register */
    vuint32_t R;
    struct {
        vuint32_t DIV_UPD_TRIGGER:32;
    } B;
} MC_CGM_DIV_UPD_TRIG_tag;

typedef union MC_CGM_DIV_UPD_STAT_union_tag { /* Divider Update Status Register */
    vuint32_t R;
    struct {
        vuint32_t SYS_UPD_STAT:1;          /* System Clock Divider Update Status */
        vuint32_t _unused_7:24;
        vuint32_t _unused_6:1;
        vuint32_t _unused_0:6;
    } B;
} MC_CGM_DIV_UPD_STAT_tag;

typedef union MC_CGM_SC_SS_union_tag { /* System Clock Select Status Register */
    vuint32_t R;
    struct {
        vuint32_t _unused_28:4;
        vuint32_t SELSTAT:4;
        vuint32_t _unused_20:4;
        vuint32_t SWTRG:3;
        vuint32_t SWIP:1;
        vuint32_t _unused_0:16;
    } B;
} MC_CGM_SC_SS_tag;

typedef union MC_CGM_SC_DC0_union_tag { /* System Clock Divider 0 Configuration Register */
    vuint32_t R;
    struct {
        vuint32_t DE:1;
        vuint32_t _unused_19:12;
        vuint32_t DIV:3;
        vuint32_t _unused_0:16;
    } B;
} MC_CGM_SC_DC0_tag;

typedef union MC_CGM_SC_DC1_union_tag { /* System Clock Divider 1 Configuration Register */
    vuint32_t R;
    struct {
        vuint32_t DE:1;
        vuint32_t _unused_19:12;
        vuint32_t DIV:3;
        vuint32_t _unused_0:16;
    } B;
} MC_CGM_SC_DC1_tag;

typedef union MC_CGM_SC_DC2_union_tag { /* System Clock Divider 2 Configuration Register */
    vuint32_t R;
    struct {
        vuint32_t DE:1;
        vuint32_t _unused_20:11;
        vuint32_t DIV:4;
        vuint32_t _unused_0:16;
    } B;
} MC_CGM_SC_DC2_tag;

typedef union MC_CGM_SC_DC3_union_tag { /* System Clock Divider 3 Configuration Register */
    vuint32_t R;
    struct {
        vuint32_t DE:1;
        vuint32_t _unused_18:13;
        vuint32_t DIV:2;
        vuint32_t _unused_0:16;
    } B;
} MC_CGM_SC_DC3_tag;

typedef union MC_CGM_SC_DC4_union_tag { /* System Clock Divider 4 Configuration Register */
    vuint32_t R;
    struct {
        vuint32_t DE:1;
        vuint32_t _unused_18:13;
        vuint32_t DIV:2;
        vuint32_t _unused_0:16;
    } B;
} MC_CGM_SC_DC4_tag;

typedef union MC_CGM_SC_DC5_union_tag { /* System Clock Divider 5 Configuration Register */
    vuint32_t R;
    struct {
        vuint32_t DE:1;
        vuint32_t _unused_19:12;
        vuint32_t DIV:3;
        vuint32_t _unused_0:16;
    } B;
} MC_CGM_SC_DC5_tag;

typedef union MC_CGM_AC2_SC_union_tag { /* Auxiliary Clock 2 Select Control Register */
    vuint32_t R;
    struct {
        vuint32_t _unused_25:7;
        vuint32_t SELCTL:1;
        vuint32_t _unused_0:24;
    } B;
} MC_CGM_AC2_SC_tag;

typedef union MC_CGM_AC2_SS_union_tag { /* Auxiliary Clock 2 Select Status Register */
    vuint32_t R;
    struct {
        vuint32_t _unused_25:7;
        vuint32_t SELSTAT:1;
        vuint32_t _unused_0:24;
    } B;
} MC_CGM_AC2_SS_tag;

typedef union MC_CGM_AC3_SS_union_tag { /* Auxiliary Clock 3 Select Status Register */
    vuint32_t R;
    struct {
        vuint32_t _unused_25:7;
        vuint32_t SELSTAT:1;
        vuint32_t _unused_0:24;
    } B;
} MC_CGM_AC3_SS_tag;

typedef union MC_CGM_AC4_SC_union_tag { /* Auxiliary Clock 4 Select Control Register */
    vuint32_t R;
    struct {
        vuint32_t _unused_25:7;
        vuint32_t SELCTL:1;
        vuint32_t _unused_0:24;
    } B;
} MC_CGM_AC4_SC_tag;

typedef union MC_CGM_AC4_SS_union_tag { /* Auxiliary Clock 4 Select Status Register */
    vuint32_t R;
    struct {
        vuint32_t _unused_25:7;
        vuint32_t SELSTAT:1;
        vuint32_t _unused_0:24;
    } B;
} MC_CGM_AC4_SS_tag;

typedef union MC_CGM_AC6_SC_union_tag { /* Auxiliary Clock 6 Select Control Register */
    vuint32_t R;
    struct {
        vuint32_t _unused_28:4;
        vuint32_t SELCTL:4;
        vuint32_t _unused_0:24;
    } B;
} MC_CGM_AC6_SC_tag;

typedef union MC_CGM_AC6_SS_union_tag { /* Auxiliary Clock 6 Select Status Register */
    vuint32_t R;
    struct {
        vuint32_t _unused_28:4;
        vuint32_t SELSTAT:4;
        vuint32_t _unused_0:24;
    } B;
} MC_CGM_AC6_SS_tag;

typedef union MC_CGM_AC6_DC0_union_tag { /* Aux Clock 6 Divider Configuration 0 for CLKOUT_0 */
    vuint32_t R;
    struct {
        vuint32_t DE:1;
        vuint32_t _unused_21:10;
        vuint32_t DIV:5;
        vuint32_t _unused_0:16;
    } B;
} MC_CGM_AC6_DC0_tag;

struct MC_CGM_tag {
    uint8_t MC_CGM_reserved0[384];
    MC_CGM_CLKOUT1_SC_tag CLKOUT1_SC;    /* Clockout 1 Select Register */
    uint8_t MC_CGM_reserved1[4];
    MC_CGM_CLKOUT1_DC_tag CLKOUT1_DC;    /* CLKOUT1_DC Configuration Register */
    uint8_t MC_CGM_reserved2[52];
    MC_CGM_AC5_SC_tag AC5_SC;            /* Auxiliary Clock 5 Select Control Register */
    MC_CGM_AC5_SS_tag AC5_SS;            /* Auxiliary Clock 5 Select Status Register */
    uint8_t MC_CGM_reserved3[56];
    MC_CGM_SC_DC6_tag SC_DC6;            /* System Clock Divider 6 Configuration Register */
    uint8_t MC_CGM_reserved4[124];
    MC_CGM_AC8_SC_tag AC8_SC;            /* Auxiliary Clock 8 Select Control Register */
    MC_CGM_AC8_SS_tag AC8_SS;            /* Auxiliary Clock 8 Select Status Register */
    uint8_t MC_CGM_reserved5[56];
    MC_CGM_AC9_SC_tag AC9_SC;            /* Auxiliary Clock 9 Select Control Register */
    MC_CGM_AC9_SS_tag AC9_SS;            /* Auxiliary Clock 9 Select Status Register */
    uint8_t MC_CGM_reserved6[1080];
    MC_CGM_PCS_SDUR_tag PCS_SDUR;        /* PCS Switch Duration Register */
    uint8_t MC_CGM_reserved7[3];
    MC_CGM_PCS_DIVC1_tag PCS_DIVC1;      /* PCS Divider Change Register 1 */
    MC_CGM_PCS_DIVE1_tag PCS_DIVE1;      /* PCS Divider End Register 1 */
    MC_CGM_PCS_DIVS1_tag PCS_DIVS1;      /* PCS Divider Start Register 1 */
    MC_CGM_PCS_DIVC2_tag PCS_DIVC2;      /* PCS Divider Change Register 2 */
    MC_CGM_PCS_DIVE2_tag PCS_DIVE2;      /* PCS Divider End Register 2 */
    MC_CGM_PCS_DIVS2_tag PCS_DIVS2;      /* PCS Divider Start Register 2 */
    uint8_t MC_CGM_reserved8[176];
    MC_CGM_DIV_UPD_ABRTD_tag DIV_UPD_ABRTD; /* Divider Update Abort Register */
    MC_CGM_SC_DIV_RC_tag SC_DIV_RC;      /* System Clock Divider Ratio Change Register */
    MC_CGM_DIV_UPD_TYPE_tag DIV_UPD_TYPE; /* Divider Update Type Register */
    MC_CGM_DIV_UPD_TRIG_tag DIV_UPD_TRIG; /* Divider Update Trigger Register */
    MC_CGM_DIV_UPD_STAT_tag DIV_UPD_STAT; /* Divider Update Status Register */
    uint8_t MC_CGM_reserved9[4];
    MC_CGM_SC_SS_tag SC_SS;              /* System Clock Select Status Register */
    MC_CGM_SC_DC0_tag SC_DC0;            /* System Clock Divider 0 Configuration Register */
    MC_CGM_SC_DC1_tag SC_DC1;            /* System Clock Divider 1 Configuration Register */
    MC_CGM_SC_DC2_tag SC_DC2;            /* System Clock Divider 2 Configuration Register */
    MC_CGM_SC_DC3_tag SC_DC3;            /* System Clock Divider 3 Configuration Register */
    MC_CGM_SC_DC4_tag SC_DC4;            /* System Clock Divider 4 Configuration Register */
    MC_CGM_SC_DC5_tag SC_DC5;            /* System Clock Divider 5 Configuration Register */
    uint8_t MC_CGM_reserved10[64];
    MC_CGM_AC2_SC_tag AC2_SC;            /* Auxiliary Clock 2 Select Control Register */
    MC_CGM_AC2_SS_tag AC2_SS;            /* Auxiliary Clock 2 Select Status Register */
    uint8_t MC_CGM_reserved11[28];
    MC_CGM_AC3_SS_tag AC3_SS;            /* Auxiliary Clock 3 Select Status Register */
    uint8_t MC_CGM_reserved12[24];
    MC_CGM_AC4_SC_tag AC4_SC;            /* Auxiliary Clock 4 Select Control Register */
    MC_CGM_AC4_SS_tag AC4_SS;            /* Auxiliary Clock 4 Select Status Register */
    uint8_t MC_CGM_reserved13[56];
    MC_CGM_AC6_SC_tag AC6_SC;            /* Auxiliary Clock 6 Select Control Register */
    MC_CGM_AC6_SS_tag AC6_SS;            /* Auxiliary Clock 6 Select Status Register */
    MC_CGM_AC6_DC0_tag AC6_DC0;          /* Aux Clock 6 Divider Configuration 0 for CLKOUT_0 */
};
/**********************MC_ME**********************************/
typedef union MC_ME_GS_union_tag {     /* Global Status Register */
    vuint32_t R;
    struct {
        vuint32_t S_CURRENT_MODE:4;
        vuint32_t S_MTRANS:1;
        vuint32_t _unused_26:1;
        vuint32_t _unused_24:2;
        vuint32_t S_PDO:1;
        vuint32_t _unused_21:2;
        vuint32_t S_MVR:1;
        vuint32_t _unused_18:2;
        vuint32_t S_FLA:2;
        vuint32_t _unused_9:7;
        vuint32_t S_SXOSC:1;               /* 32 KHz external oscillator status */
        vuint32_t S_SIRCON:1;              /* 128 KHz internal RC oscillator status */
        vuint32_t S_PLLON:1;               /* PLL status */
        vuint32_t S_FXOSC:1;               /* 8-40 MHz crystal oscillator status */
        vuint32_t S_FIRCON:1;
        vuint32_t S_SYSCLK:4;
    } B;
} MC_ME_GS_tag;

typedef union MC_ME_MCTL_union_tag {   /* Mode Control Register */
    vuint32_t R;
    struct {
        vuint32_t TARGET_MODE:4;           /* Target chip mode */
        vuint32_t _unused_16:12;
        vuint32_t KEY:16;
    } B;
} MC_ME_MCTL_tag;

typedef union MC_ME_ME_union_tag {     /* Mode Enable Register */
    vuint32_t R;
    struct {
        vuint32_t _unused_16:16;
        vuint32_t RESET_DEST:1;
        vuint32_t _unused_14:1;
        vuint32_t STANDBY0:1;              /* STANDBY0 mode enable */
        vuint32_t _unused_11:2;
        vuint32_t STOP0:1;
        vuint32_t _unused_9:1;
        vuint32_t _unused_8:1;
        vuint32_t RUN3:1;
        vuint32_t RUN2:1;
        vuint32_t RUN1:1;
        vuint32_t RUN0:1;
        vuint32_t DRUN:1;
        vuint32_t SAFE:1;
        vuint32_t _unused_1:1;
        vuint32_t RESET_FUNC:1;
    } B;
} MC_ME_ME_tag;

typedef union MC_ME_IS_union_tag {     /* Interrupt Status Register */
    vuint32_t R;
    struct {
        vuint32_t _unused_6:26;
        vuint32_t I_ICONF_CC:1;
        vuint32_t _unused_4:1;             /* This field is reserved and can be set to 1 by hardware during some mode transitions. The setting of this bit has no impact on the device. */
        vuint32_t I_ICONF:1;
        vuint32_t I_IMODE:1;
        vuint32_t I_SAFE:1;
        vuint32_t I_MTC:1;
    } B;
} MC_ME_IS_tag;

typedef union MC_ME_IM_union_tag {     /* Interrupt Mask Register */
    vuint32_t R;
    struct {
        vuint32_t _unused_6:26;
        vuint32_t M_ICONF_CC:1;
        vuint32_t _unused_4:1;
        vuint32_t M_ICONF:1;
        vuint32_t M_IMODE:1;
        vuint32_t M_SAFE:1;
        vuint32_t M_MTC:1;
    } B;
} MC_ME_IM_tag;

typedef union MC_ME_IMTS_union_tag {   /* Invalid Mode Transition Status Register */
    vuint32_t R;
    struct {
        vuint32_t _unused_6:26;
        vuint32_t S_MRIG:1;
        vuint32_t S_MTI:1;
        vuint32_t S_MRI:1;
        vuint32_t S_DMA:1;
        vuint32_t S_NMA:1;
        vuint32_t S_SEA:1;
    } B;
} MC_ME_IMTS_tag;

typedef union MC_ME_DMTS_union_tag {   /* Debug Mode Transition Status Register */
    vuint32_t R;
    struct {
        vuint32_t PREVIOUS_MODE:4;
        vuint32_t _unused_24:4;
        vuint32_t MPH_BUSY:1;
        vuint32_t _unused_21:2;
        vuint32_t PMC_PROG:1;
        vuint32_t DBG_MODE:1;
        vuint32_t CCKL_PROG:1;
        vuint32_t PCS_PROG:1;
        vuint32_t SMR:1;
        vuint32_t CDP_PRPH_0_255:1;        /* Clock Disable Process Pending status for Peripherals 0...255 */
        vuint32_t VREG_CSRC_SC:1;
        vuint32_t CSRC_CSRC_SC:1;
        vuint32_t IRC_SC:1;
        vuint32_t SCSRC_SC:1;
        vuint32_t SYSCLK_SW:1;
        vuint32_t _unused_9:1;
        vuint32_t FLASH_SC:1;
        vuint32_t _unused_4:4;
        vuint32_t CDP_PRPH_96_127:1;
        vuint32_t CDP_PRPH_64_95:1;
        vuint32_t CDP_PRPH_32_63:1;
        vuint32_t CDP_PRPH_0_31:1;
    } B;
} MC_ME_DMTS_tag;

typedef union MC_ME_RESET_MC_union_tag { /* RESET Mode Configuration Register */
    vuint32_t R;
    struct {
        vuint32_t _unused_31:1;
        vuint32_t PWRLVL:3;
        vuint32_t _unused_24:4;
        vuint32_t PDO:1;
        vuint32_t _unused_21:2;
        vuint32_t MVRON:1;
        vuint32_t _unused_18:2;
        vuint32_t FLAON:2;
        vuint32_t _unused_9:7;
        vuint32_t SXOSCON:1;               /* 32Khz external oscillator control */
        vuint32_t SIRCON:1;
        vuint32_t PLLON:1;
        vuint32_t FXOSCON:1;
        vuint32_t FIRCON:1;
        vuint32_t SYSCLK:4;
    } B;
} MC_ME_RESET_MC_tag;

typedef union MC_ME_SAFE_MC_union_tag { /* SAFE Mode Configuration Register */
    vuint32_t R;
    struct {
        vuint32_t _unused_31:1;
        vuint32_t PWRLVL:3;
        vuint32_t _unused_24:4;
        vuint32_t PDO:1;
        vuint32_t _unused_21:2;
        vuint32_t MVRON:1;
        vuint32_t _unused_18:2;
        vuint32_t FLAON:2;
        vuint32_t _unused_9:7;
        vuint32_t SXOSCON:1;               /* 32Khz external oscillator control */
        vuint32_t SIRCON:1;
        vuint32_t PLLON:1;
        vuint32_t FXOSCON:1;
        vuint32_t FIRCON:1;
        vuint32_t SYSCLK:4;
    } B;
} MC_ME_SAFE_MC_tag;

typedef union MC_ME_DRUN_MC_union_tag { /* DRUN Mode Configuration Register */
    vuint32_t R;
    struct {
        vuint32_t _unused_31:1;
        vuint32_t PWRLVL:3;
        vuint32_t _unused_24:4;
        vuint32_t PDO:1;
        vuint32_t _unused_21:2;
        vuint32_t MVRON:1;
        vuint32_t _unused_18:2;
        vuint32_t FLAON:2;
        vuint32_t _unused_9:7;
        vuint32_t SXOSCON:1;               /* 32Khz external oscillator control */
        vuint32_t SIRCON:1;
        vuint32_t PLLON:1;
        vuint32_t FXOSCON:1;
        vuint32_t FIRCON:1;
        vuint32_t SYSCLK:4;
    } B;
} MC_ME_DRUN_MC_tag;

typedef union MC_ME_RUN_MC_union_tag { /* RUN0 Mode Configuration Register */
    vuint32_t R;
    struct {
        vuint32_t _unused_31:1;
        vuint32_t PWRLVL:3;
        vuint32_t _unused_24:4;
        vuint32_t PDO:1;
        vuint32_t _unused_21:2;
        vuint32_t MVRON:1;
        vuint32_t _unused_18:2;
        vuint32_t FLAON:2;
        vuint32_t _unused_9:7;
        vuint32_t SXOSCON:1;               /* 32 KHz external oscillator control */
        vuint32_t SIRCON:1;
        vuint32_t PLLON:1;
        vuint32_t FXOSCON:1;
        vuint32_t FIRCON:1;
        vuint32_t SYSCLK:4;
    } B;
} MC_ME_RUN_MC_tag;

typedef union MC_ME_STOP_MC_union_tag { /* STOP0 Mode Configuration Register */
    vuint32_t R;
    struct {
        vuint32_t _unused_31:1;
        vuint32_t PWRLVL:3;
        vuint32_t _unused_24:4;
        vuint32_t PDO:1;
        vuint32_t _unused_21:2;
        vuint32_t MVRON:1;
        vuint32_t _unused_18:2;
        vuint32_t FLAON:2;
        vuint32_t _unused_9:7;
        vuint32_t SXOSCON:1;               /* 32 KHz external oscillator control */
        vuint32_t SIRCON:1;
        vuint32_t PLLON:1;
        vuint32_t FXOSCON:1;
        vuint32_t FIRCON:1;
        vuint32_t SYSCLK:4;
    } B;
} MC_ME_STOP_MC_tag;

typedef union MC_ME_STANDBY_MC_union_tag { /* STANDBY0 Mode Configuration Register */
    vuint32_t R;
    struct {
        vuint32_t _unused_31:1;
        vuint32_t PWRLVL:3;
        vuint32_t _unused_24:4;
        vuint32_t PDO:1;
        vuint32_t _unused_21:2;
        vuint32_t MVRON:1;
        vuint32_t _unused_18:2;
        vuint32_t FLAON:2;
        vuint32_t _unused_9:7;
        vuint32_t SXOSCON:1;               /* 32 KHz external oscillator control */
        vuint32_t SIRCON:1;
        vuint32_t PLLON:1;
        vuint32_t FXOSCON:1;
        vuint32_t FIRCON:1;
        vuint32_t SYSCLK:4;
    } B;
} MC_ME_STANDBY_MC_tag;

typedef union MC_ME_PS0_union_tag {    /* Peripheral Status Register 0 */
    vuint32_t R;
    struct {
        vuint32_t S_IIC_1:1;
        vuint32_t S_IIC_0:1;
        vuint32_t _unused_29:1;
        vuint32_t S_FlexRay:1;             /* Peripheral status - These bits specify the current status of each peripheral which is controlled by the MC_ME. */
        vuint32_t _unused_26:2;
        vuint32_t S_ADC_1:1;               /* Peripheral status - These bits specify the current status of each peripheral which is controlled by the MC_ME. 0: Peripheral is frozen 1: Peripheral is active. */
        vuint32_t S_ADC_0:1;               /* Peripheral status - These bits specify the current status of each peripheral which is controlled by the MC_ME. 0: Peripheral is frozen 1: Peripheral is active */
        vuint32_t _unused_23:1;
        vuint32_t S_ACMP_2:1;              /* Peripheral status - These bits specify the current status of each peripheral which is controlled by the MC_ME. 0: Peripheral is frozen 1: Peripheral is active */
        vuint32_t S_ACMP_1:1;              /* Peripheral status - These bits specify the current status of each peripheral which is controlled by the MC_ME. 0: Peripheral is frozen 1: Peripheral is active */
        vuint32_t S_ACMP_0:1;              /* Peripheral status - These bits specify the current status of each peripheral which is controlled by the MC_ME. 0: Peripheral is frozen 1: Peripheral is active */
        vuint32_t _unused_16:4;
        vuint32_t S_ENET:1;                /* Peripheral status - These bits specify the current status of each peripheral which is controlled by the MC_ME. 0: Peripheral is frozen 1: Peripheral is active */
        vuint32_t _unused_13:2;
        vuint32_t S_SAI_2:1;               /* Peripheral status - These bits specify the current status of each peripheral which is controlled by the MC_ME. 0: Peripheral is frozen 1: Peripheral is active */
        vuint32_t S_SAI_1:1;               /* Peripheral status - These bits specify the current status of each peripheral which is controlled by the MC_ME. 0: Peripheral is frozen 1: Peripheral is active. */
        vuint32_t S_SAI_0:1;               /* Peripheral status - These bits specify the current status of each peripheral which is controlled by the MC_ME. 0: Peripheral is frozen 1: Peripheral is active */
        vuint32_t _unused_8:2;
        vuint32_t S_SDHC:1;                /* Peripheral status - These bits specify the current status of each peripheral which is controlled by the MC_ME. 0: Peripheral is frozen 1: Peripheral is active */
        vuint32_t S_MLB:1;                 /* Peripheral status - These bits specify the current status of each peripheral which is controlled by the MC_ME. 0: Peripheral is frozen 1: Peripheral is active */
        vuint32_t S_USB_SPH:1;             /* Peripheral status - These bits specify the current status of each peripheral which is controlled by the MC_ME. 0: Peripheral is frozen 1: Peripheral is active */
        vuint32_t S_USBOTG:1;
        vuint32_t S_eMIOS_2:1;             /* Peripheral status - These bits specify the current status of each peripheral which is controlled by the MC_ME. */
        vuint32_t S_eMIOS_1:1;             /* Peripheral status - These bits specify the current status of each peripheral which is controlled by the MC_ME. */
        vuint32_t S_eMIOS_0:1;             /* Peripheral status - These bits specify the current status of each peripheral which is controlled by the MC_ME. */
        vuint32_t S_BCTU:1;                /* Peripheral status - These bits specify the current status of each peripheral which is controlled by the MC_ME. 0: Peripheral is frozen 1: Peripheral is active */
    } B;
} MC_ME_PS0_tag;

typedef union MC_ME_PS1_union_tag {    /* Peripheral Status Register 1 */
    vuint32_t R;
    struct {
        vuint32_t S_LIN:14;                /* Peripheral status - These bits specify the current status of each peripheral which is controlled by the MC_ME. 0: Peripheral is frozen 1: Peripheral is active */
        vuint32_t _unused_12:6;
        vuint32_t S_DSPI:4;                /* Peripheral status - These bits specify the current status of each peripheral which is controlled by the MC_ME. 0: Peripheral is frozen 1: Peripheral is active */
        vuint32_t _unused_2:6;
        vuint32_t S_IIC:2;                 /* Peripheral status - These bits specify the current status of each peripheral which is controlled by the MC_ME. 0: Peripheral is frozen 1: Peripheral is active */
    } B;
} MC_ME_PS1_tag;

typedef union MC_ME_PS2_union_tag {    /* Peripheral Status Register 2 */
    vuint32_t R;
    struct {
        vuint32_t _unused_31:1;
        vuint32_t _unused_30:1;
        vuint32_t S_WKPU:1;
        vuint32_t S_LPU_CTL:1;
        vuint32_t S_PIT_RTI_0:1;
        vuint32_t S_DMAMUX:1;              /* Peripheral status - These bits specify the current status of each peripheral which is controlled by the MC_ME. */
        vuint32_t _unused_21:5;
        vuint32_t S_CRC:1;
        vuint32_t S_MEMU_0:1;
        vuint32_t S_JDC:1;
        vuint32_t S_TDM:1;
        vuint32_t _unused_16:1;
        vuint32_t _unused_14:2;
        vuint32_t S_FLEXCAN:8;
        vuint32_t _unused_4:2;
        vuint32_t S_LIN:4;
    } B;
} MC_ME_PS2_tag;

typedef union MC_ME_PS3_union_tag {    /* Peripheral Status Register 3 */
    vuint32_t R;
    struct {
        vuint32_t _unused_10:22;
        vuint32_t S_MEMU_1:1;
        vuint32_t _unused_8:1;
        vuint32_t _unused_7:1;
        vuint32_t S_RTC_API:1;
        vuint32_t S_SPI:6;
    } B;
} MC_ME_PS3_tag;

typedef union MC_ME_RUN_PC_union_tag { /* Run Peripheral Configuration Register */
    vuint32_t R;
    struct {
        vuint32_t _unused_8:24;
        vuint32_t RUN3:1;
        vuint32_t RUN2:1;
        vuint32_t RUN1:1;
        vuint32_t RUN0:1;
        vuint32_t DRUN:1;
        vuint32_t SAFE:1;
        vuint32_t _unused_1:1;
        vuint32_t RESET:1;
    } B;
} MC_ME_RUN_PC_tag;

typedef union MC_ME_LP_PC_union_tag {  /* Low-Power Peripheral Configuration Register */
    vuint32_t R;
    struct {
        vuint32_t _unused_14:18;
        vuint32_t STANDBY0:1;              /* Peripheral control during STANDBY0 */
        vuint32_t _unused_11:2;
        vuint32_t STOP0:1;
        vuint32_t _unused_9:1;
        vuint32_t _unused_8:1;
        vuint32_t _unused_0:8;
    } B;
} MC_ME_LP_PC_tag;

/* Note on PCTL registers: There are only some PCTL implemented         */
/*  In order to make the PCTL easily addressable, these are defined     */
/*  as an array (ie ME.PCTL[x].R). This means you have to be careful    */
/*  when addressing these registers in order not to access a PCTL that  */
/*  is not implemented. Following are available: 0-7, 10-12, 15, 20-25, */
/*  28, 30-33, 40-43, 50-67, 70-77, 80-84, 90-91, 93-94, 96-102, 104    */

typedef union MC_ME_PCTL_union_tag {   /* BCTU Peripheral Control Register */
    vuint8_t R;
    struct {
        vuint8_t _unused_7:1;
        vuint8_t DBG_F:1;
        vuint8_t LP_CFG:3;
        vuint8_t RUN_CFG:3;
    } B;
} MC_ME_PCTL_tag;

typedef union MC_ME_CS_union_tag {     /* Core Status Register */
    vuint32_t R;
    struct {
        vuint32_t _unused_4:28;
        vuint32_t S_CORE3:1;               /* Core3 Status */
        vuint32_t S_CORE2:1;               /* Core2 Status */
        vuint32_t S_CORE1:1;
        vuint32_t _unused_0:1;
    } B;
} MC_ME_CS_tag;

typedef union MC_ME_CCTL_union_tag {
    vuint16_t R;
    struct {
        vuint16_t _unused_15:1;
        vuint16_t STANDBY0:2;
        vuint16_t _unused_11:2;
        vuint16_t STOP0:1;
        vuint16_t _unused_9:1;
        vuint16_t _unused_8:1;
        vuint16_t RUN3:1;
        vuint16_t RUN2:1;
        vuint16_t RUN1:1;
        vuint16_t RUN0:1;
        vuint16_t DRUN:1;
        vuint16_t SAFE:1;
        vuint16_t _unused_1:1;
        vuint16_t RESET:1;
    } B;
} MC_ME_CCTL_tag;

typedef union MC_ME_CADDR_union_tag {
    vuint32_t R;
    struct {
        vuint32_t ADDR:30;
        vuint32_t _unused_1:1;
        vuint32_t RMC:1;                   /* Reset on Mode Change */
    } B;
} MC_ME_CADDR_tag;

struct MC_ME_tag {
    MC_ME_GS_tag GS;                     /* Global Status Register */
    MC_ME_MCTL_tag MCTL;                 /* Mode Control Register */
    MC_ME_ME_tag ME;                     /* Mode Enable Register */
    MC_ME_IS_tag IS;                     /* Interrupt Status Register */
    MC_ME_IM_tag IM;                     /* Interrupt Mask Register */
    MC_ME_IMTS_tag IMTS;                 /* Invalid Mode Transition Status Register */
    MC_ME_DMTS_tag DMTS;                 /* Debug Mode Transition Status Register */
    uint8_t MC_ME_reserved0[4];
    MC_ME_RESET_MC_tag RESET_MC;         /* RESET Mode Configuration Register */
    uint8_t MC_ME_reserved1[4];
    MC_ME_SAFE_MC_tag SAFE_MC;           /* SAFE Mode Configuration Register */
    MC_ME_DRUN_MC_tag DRUN_MC;           /* DRUN Mode Configuration Register */
    MC_ME_RUN_MC_tag RUN_MC[4];          /* RUN0 Mode Configuration Register */
    uint8_t MC_ME_reserved2[8];
    MC_ME_STOP_MC_tag STOP_MC;           /* STOP0 Mode Configuration Register */
    uint8_t MC_ME_reserved3[8];
    MC_ME_STANDBY_MC_tag STANDBY_MC;     /* STANDBY0 Mode Configuration Register */
    uint8_t MC_ME_reserved4[8];
    MC_ME_PS0_tag PS0;                   /* Peripheral Status Register 0 */
    MC_ME_PS1_tag PS1;                   /* Peripheral Status Register 1 */
    MC_ME_PS2_tag PS2;                   /* Peripheral Status Register 2 */
    MC_ME_PS3_tag PS3;                   /* Peripheral Status Register 3 */
    uint8_t MC_ME_reserved5[16];
    MC_ME_RUN_PC_tag RUN_PC[8];          /* Run Peripheral Configuration Register */
    MC_ME_LP_PC_tag LP_PC[8];            /* Low-Power Peripheral Configuration Register */
    MC_ME_PCTL_tag PCTL[104];            /* BCTU Peripheral Control Register */
    uint8_t MC_ME_reserved6[152];
    MC_ME_CS_tag CS;                     /* Core Status Register */
    MC_ME_CCTL_tag CCTL[4];
    uint8_t MC_ME_reserved7[20];
    MC_ME_CADDR_tag CADDR[4];
};

/*********************SIUL2******************************/

typedef union SIUL2_MIDR1_union_tag {  /* SIUL2 MCU ID Register #1 */
  vuint32_t R;
  struct {
    vuint32_t PARTNUM:16;              /* MCU Part Number */
    vuint32_t _unused_15:1;
    vuint32_t PKG:5;                   /* Package Settings */
    vuint32_t _unused_8:2;
    vuint32_t MAJOR_MASK:4;            /* Major Mask Revision */
    vuint32_t MINOR_MASK:4;            /* Minor Mask Revision */
  } B;
} SIUL2_MIDR1_tag;

typedef union SIUL2_MIDR2_union_tag {  /* SIUL2 MCU ID Register #2 */
  vuint32_t R;
  struct {
    vuint32_t _unused_31:1;
    vuint32_t FLASH_SIZE_1:4;          /* Coarse granularity for flash memory size */
    vuint32_t FLASH_SIZE_2:4;          /* Fine granularity for flash memory size */
    vuint32_t _unused_16:7;
    vuint32_t PARTNUM:8;               /* ASCII character in MCU Part Number */
    vuint32_t _unused_0:8;
  } B;
} SIUL2_MIDR2_tag;

typedef union SIUL2_ISR0_union_tag {   /* SIUL2 Interrupt Status Flag Register0 */
  vuint32_t R;
  struct {
    vuint32_t EIF31:1;                 /* External Interrupt Status Flag x */
    vuint32_t EIF30:1;                 /* External Interrupt Status Flag x */
    vuint32_t EIF29:1;                 /* External Interrupt Status Flag x */
    vuint32_t EIF28:1;                 /* External Interrupt Status Flag x */
    vuint32_t EIF27:1;                 /* External Interrupt Status Flag x */
    vuint32_t EIF26:1;                 /* External Interrupt Status Flag x */
    vuint32_t EIF25:1;                 /* External Interrupt Status Flag x */
    vuint32_t EIF24:1;                 /* External Interrupt Status Flag x */
    vuint32_t EIF23:1;                 /* External Interrupt Status Flag x */
    vuint32_t EIF22:1;                 /* External Interrupt Status Flag x */
    vuint32_t EIF21:1;                 /* External Interrupt Status Flag x */
    vuint32_t EIF20:1;                 /* External Interrupt Status Flag x */
    vuint32_t EIF19:1;                 /* External Interrupt Status Flag x */
    vuint32_t EIF18:1;                 /* External Interrupt Status Flag x */
    vuint32_t EIF17:1;                 /* External Interrupt Status Flag x */
    vuint32_t EIF16:1;                 /* External Interrupt Status Flag x */
    vuint32_t EIF15:1;                 /* External Interrupt Status Flag x */
    vuint32_t EIF14:1;                 /* External Interrupt Status Flag x */
    vuint32_t EIF13:1;                 /* External Interrupt Status Flag x */
    vuint32_t EIF12:1;                 /* External Interrupt Status Flag x */
    vuint32_t EIF11:1;                 /* External Interrupt Status Flag x */
    vuint32_t EIF10:1;                 /* External Interrupt Status Flag x */
    vuint32_t EIF9:1;                  /* External Interrupt Status Flag x */
    vuint32_t EIF8:1;                  /* External Interrupt Status Flag x */
    vuint32_t EIF7:1;                  /* External Interrupt Status Flag x */
    vuint32_t EIF6:1;                  /* External Interrupt Status Flag x */
    vuint32_t EIF5:1;                  /* External Interrupt Status Flag x */
    vuint32_t EIF4:1;                  /* External Interrupt Status Flag x */
    vuint32_t EIF3:1;                  /* External Interrupt Status Flag x */
    vuint32_t EIF2:1;                  /* External Interrupt Status Flag x */
    vuint32_t EIF1:1;                  /* External Interrupt Status Flag x */
    vuint32_t EIF0:1;                  /* External Interrupt Status Flag x */
  } B;
} SIUL2_ISR0_tag;

typedef union SIUL2_IRER0_union_tag {  /* SIUL2 Interrupt Request Enable Register0 */
  vuint32_t R;
  struct {
    vuint32_t EIRE31:1;
    vuint32_t EIRE30:1;
    vuint32_t EIRE29:1;
    vuint32_t EIRE28:1;
    vuint32_t EIRE27:1;
    vuint32_t EIRE26:1;
    vuint32_t EIRE25:1;
    vuint32_t EIRE24:1;
    vuint32_t EIRE23:1;
    vuint32_t EIRE22:1;
    vuint32_t EIRE21:1;
    vuint32_t EIRE20:1;
    vuint32_t EIRE19:1;
    vuint32_t EIRE18:1;
    vuint32_t EIRE17:1;
    vuint32_t EIRE16:1;
    vuint32_t EIRE15:1;
    vuint32_t EIRE14:1;
    vuint32_t EIRE13:1;
    vuint32_t EIRE12:1;
    vuint32_t EIRE11:1;
    vuint32_t EIRE10:1;
    vuint32_t EIRE9:1;
    vuint32_t EIRE8:1;
    vuint32_t EIRE7:1;
    vuint32_t EIRE6:1;
    vuint32_t EIRE5:1;
    vuint32_t EIRE4:1;
    vuint32_t EIRE3:1;
    vuint32_t EIRE2:1;
    vuint32_t EIRE1:1;
    vuint32_t EIRE0:1;
  } B;
} SIUL2_IRER0_tag;

typedef union SIUL2_IRSR0_union_tag {  /* SIUL2 Interrupt Request Select Register0 */
  vuint32_t R;
  struct {
    vuint32_t DIRSR31:1;
    vuint32_t DIRSR30:1;
    vuint32_t DIRSR29:1;
    vuint32_t DIRSR28:1;
    vuint32_t DIRSR27:1;
    vuint32_t DIRSR26:1;
    vuint32_t DIRSR25:1;
    vuint32_t DIRSR24:1;
    vuint32_t DIRSR23:1;
    vuint32_t DIRSR22:1;
    vuint32_t DIRSR21:1;
    vuint32_t DIRSR20:1;
    vuint32_t DIRSR19:1;
    vuint32_t DIRSR18:1;
    vuint32_t DIRSR17:1;
    vuint32_t DIRSR16:1;
    vuint32_t DIRSR15:1;
    vuint32_t DIRSR14:1;
    vuint32_t DIRSR13:1;
    vuint32_t DIRSR12:1;
    vuint32_t DIRSR11:1;
    vuint32_t DIRSR10:1;
    vuint32_t DIRSR9:1;
    vuint32_t DIRSR8:1;
    vuint32_t DIRSR7:1;
    vuint32_t DIRSR6:1;
    vuint32_t DIRSR5:1;
    vuint32_t DIRSR4:1;
    vuint32_t DIRSR3:1;
    vuint32_t DIRSR2:1;
    vuint32_t DIRSR1:1;
    vuint32_t DIRSR0:1;
  } B;
} SIUL2_IRSR0_tag;

typedef union SIUL2_IREER0_union_tag { /* SIUL2 Interrupt Rising-Edge Event Enable Register 0 */
  vuint32_t R;
  struct {
    vuint32_t IREE31:1;
    vuint32_t IREE30:1;
    vuint32_t IREE29:1;
    vuint32_t IREE28:1;
    vuint32_t IREE27:1;
    vuint32_t IREE26:1;
    vuint32_t IREE25:1;
    vuint32_t IREE24:1;
    vuint32_t IREE23:1;
    vuint32_t IREE22:1;
    vuint32_t IREE21:1;
    vuint32_t IREE20:1;
    vuint32_t IREE19:1;
    vuint32_t IREE18:1;
    vuint32_t IREE17:1;
    vuint32_t IREE16:1;
    vuint32_t IREE15:1;
    vuint32_t IREE14:1;
    vuint32_t IREE13:1;
    vuint32_t IREE12:1;
    vuint32_t IREE11:1;
    vuint32_t IREE10:1;
    vuint32_t IREE9:1;
    vuint32_t IREE8:1;
    vuint32_t IREE7:1;
    vuint32_t IREE6:1;
    vuint32_t IREE5:1;
    vuint32_t IREE4:1;
    vuint32_t IREE3:1;
    vuint32_t IREE2:1;
    vuint32_t IREE1:1;
    vuint32_t IREE0:1;
  } B;
} SIUL2_IREER0_tag;

typedef union SIUL2_IFEER0_union_tag { /* SIUL2 Interrupt Falling-Edge Event Enable Register 0 */
  vuint32_t R;
  struct {
    vuint32_t IFEE31:1;
    vuint32_t IFEE30:1;
    vuint32_t IFEE29:1;
    vuint32_t IFEE28:1;
    vuint32_t IFEE27:1;
    vuint32_t IFEE26:1;
    vuint32_t IFEE25:1;
    vuint32_t IFEE24:1;
    vuint32_t IFEE23:1;
    vuint32_t IFEE22:1;
    vuint32_t IFEE21:1;
    vuint32_t IFEE20:1;
    vuint32_t IFEE19:1;
    vuint32_t IFEE18:1;
    vuint32_t IFEE17:1;
    vuint32_t IFEE16:1;
    vuint32_t IFEE15:1;
    vuint32_t IFEE14:1;
    vuint32_t IFEE13:1;
    vuint32_t IFEE12:1;
    vuint32_t IFEE11:1;
    vuint32_t IFEE10:1;
    vuint32_t IFEE9:1;
    vuint32_t IFEE8:1;
    vuint32_t IFEE7:1;
    vuint32_t IFEE6:1;
    vuint32_t IFEE5:1;
    vuint32_t IFEE4:1;
    vuint32_t IFEE3:1;
    vuint32_t IFEE2:1;
    vuint32_t IFEE1:1;
    vuint32_t IFEE0:1;
  } B;
} SIUL2_IFEER0_tag;

typedef union SIUL2_IFER0_union_tag {  /* SIUL2 Interrupt Filter Enable Register 0 */
  vuint32_t R;
  struct {
    vuint32_t IFE31:1;
    vuint32_t IFE30:1;
    vuint32_t IFE29:1;
    vuint32_t IFE28:1;
    vuint32_t IFE27:1;
    vuint32_t IFE26:1;
    vuint32_t IFE25:1;
    vuint32_t IFE24:1;
    vuint32_t IFE23:1;
    vuint32_t IFE22:1;
    vuint32_t IFE21:1;
    vuint32_t IFE20:1;
    vuint32_t IFE19:1;
    vuint32_t IFE18:1;
    vuint32_t IFE17:1;
    vuint32_t IFE16:1;
    vuint32_t IFE15:1;
    vuint32_t IFE14:1;
    vuint32_t IFE13:1;
    vuint32_t IFE12:1;
    vuint32_t IFE11:1;
    vuint32_t IFE10:1;
    vuint32_t IFE9:1;
    vuint32_t IFE8:1;
    vuint32_t IFE7:1;
    vuint32_t IFE6:1;
    vuint32_t IFE5:1;
    vuint32_t IFE4:1;
    vuint32_t IFE3:1;
    vuint32_t IFE2:1;
    vuint32_t IFE1:1;
    vuint32_t IFE0:1;
  } B;
} SIUL2_IFER0_tag;

typedef union SIUL2_IFMCR_union_tag {  /* SIUL2 Interrupt Filter Maximum Counter Register */
  vuint32_t R;
  struct {
    vuint32_t _unused_4:28;
    vuint32_t MAXCNT:4;                /* Maximum Interrupt Filter Counter setting */
  } B;
} SIUL2_IFMCR_tag;

typedef union SIUL2_IFCPR_union_tag {  /* SIUL2 Interrupt Filter Clock Prescaler Register */
  vuint32_t R;
  struct {
    vuint32_t _unused_4:28;
    vuint32_t IFCP:4;                  /* Interrupt Filter Clock Prescaler setting */
  } B;
} SIUL2_IFCPR_tag;

typedef union SIUL2_MSCR_union_tag {   /* SIUL2 Multiplexed Signal Configuration Register */
  vuint32_t R;
  struct {
    vuint32_t _unused_30:2;
    vuint32_t SRC:2;                   /* Slew Rate Control */
    vuint32_t _unused_26:2;
    vuint32_t OBE:1;                   /* GPIO Output Buffer Enable */
    vuint32_t ODE:1;                   /* Open Drain Enable */
    vuint32_t SMC:1;                   /* Safe Mode Control */
    vuint32_t APC:1;                   /* Analog Pad Control */
    vuint32_t _unused_21:1;
    vuint32_t _unused_20:1;
    vuint32_t IBE:1;                   /* Input Buffer Enable */
    vuint32_t HYS:1;                   /* Input Hysteresis */
    vuint32_t PUS:1;                   /* Pull Select */
    vuint32_t PUE:1;                   /* Pull Enable */
    vuint32_t _unused_8:8;
    vuint32_t _unused_4:4;
    vuint32_t SSS:4;                   /* Source Signal Select */
  } B;
} SIUL2_MSCR_tag;

typedef union SIUL2_IMCR_union_tag {   /* SIUL2 Input Multiplexed Signal Configuration Register */
  vuint32_t R;
  struct {
    vuint32_t _unused_8:24;
    vuint32_t _unused_4:4;
    vuint32_t SSS:4;                   /* Source Signal Select */
  } B;
} SIUL2_IMCR_tag;

typedef union SIUL2_GPDO_union_tag {   /* SIUL2 GPIO Pad Data Output Register */
    vuint8_t R;
    struct {
      vuint8_t _unused_1:7;
      vuint8_t PDO_4n:1;					     /* Pad Data Out */
    } B;
} SIUL2_GPDO_tag;

typedef union SIUL2_GPDI_union_tag {   /* SIUL2 GPIO Pad Data Input Register */
    vuint8_t R;
    struct {
      vuint8_t _unused_1:7;
      vuint8_t PDI_4n:1;					     /* Pad Data In */
    } B;
} SIUL2_GPDI_tag;

typedef union SIUL2_PGPDO_union_tag {  /* SIUL2 Parallel GPIO Pad Data Out Register */
  vuint16_t R;
  struct {
    vuint16_t PPDO:16;                 /* Parallel Pad Data Out */
  } B;
} SIUL2_PGPDO_tag;

typedef union SIUL2_PGPDI_union_tag {  /* SIUL2 Parallel GPIO Pad Data In Register */
  vuint16_t R;
  struct {
    vuint16_t PPDI:16;                 /* Parallel Pad Data In */
  } B;
} SIUL2_PGPDI_tag;

typedef union SIUL2_MPGPDO_union_tag { /* SIUL2 Masked Parallel GPIO Pad Data Out Register */
  vuint32_t R;
  struct {
    vuint32_t MASK:16;                 /* Mask Field */
    vuint32_t MPPDO:16;                /* Masked Parallel Pad Data Out */
  } B;
} SIUL2_MPGPDO_tag;

struct SIUL2_tag {
  uint8_t SIUL2_reserved0[4];
  SIUL2_MIDR1_tag MIDR1;               /* SIUL2 MCU ID Register #1 */
  SIUL2_MIDR2_tag MIDR2;               /* SIUL2 MCU ID Register #2 */
  uint8_t SIUL2_reserved1[4];
  SIUL2_ISR0_tag ISR0;                 /* SIUL2 Interrupt Status Flag Register0 */
  uint8_t SIUL2_reserved2[4];
  SIUL2_IRER0_tag IRER0;               /* SIUL2 Interrupt Request Enable Register0 */
  uint8_t SIUL2_reserved3[4];
  SIUL2_IRSR0_tag IRSR0;               /* SIUL2 Interrupt Request Select Register0 */
  uint8_t SIUL2_reserved4[4];
  SIUL2_IREER0_tag IREER0;             /* SIUL2 Interrupt Rising-Edge Event Enable Register 0 */
  uint8_t SIUL2_reserved5[4];
  SIUL2_IFEER0_tag IFEER0;             /* SIUL2 Interrupt Falling-Edge Event Enable Register 0 */
  uint8_t SIUL2_reserved6[4];
  SIUL2_IFER0_tag IFER0;               /* SIUL2 Interrupt Filter Enable Register 0 */
  uint8_t SIUL2_reserved7[4];
  SIUL2_IFMCR_tag IFMCR[32];           /* SIUL2 Interrupt Filter Maximum Counter Register */
  SIUL2_IFCPR_tag IFCPR;               /* SIUL2 Interrupt Filter Clock Prescaler Register */
  uint8_t SIUL2_reserved8[380];
  SIUL2_MSCR_tag MSCR[264];            /* SIUL2 Multiplexed Signal Configuration Register */
  uint8_t SIUL2_reserved9[992];
  SIUL2_IMCR_tag IMCR[512];            /* SIUL2 Input Multiplexed Signal Configuration Register */
  uint8_t SIUL2_reserved10[192];
  SIUL2_GPDO_tag GPDO[264];             /* SIUL2 GPIO Pad Data Output Register */
  uint8_t SIUL2_reserved11[248];
  SIUL2_GPDI_tag GPDI[264];             /* SIUL2 GPIO Pad Data Input Register */
  uint8_t SIUL2_reserved12[248];
  SIUL2_PGPDO_tag PGPDO[32];           /* SIUL2 Parallel GPIO Pad Data Out Register */
  SIUL2_PGPDI_tag PGPDI[32];           /* SIUL2 Parallel GPIO Pad Data In Register */
  SIUL2_MPGPDO_tag MPGPDO[32];         /* SIUL2 Masked Parallel GPIO Pad Data Out Register */
};

/*************************PFLASH*****************************/
typedef union PFLASH_PFCR1_union_tag { /* Platform Flash Configuration Register 1 */
    vuint32_t R;
    struct {
        vuint32_t P0_M15PFE:1;
        vuint32_t P0_M14PFE:1;
        vuint32_t P0_M13PFE:1;
        vuint32_t P0_M12PFE:1;
        vuint32_t P0_M11PFE:1;
        vuint32_t P0_M10PFE:1;
        vuint32_t P0_M9PFE:1;
        vuint32_t P0_M8PFE:1;
        vuint32_t P0_M7PFE:1;
        vuint32_t P0_M6PFE:1;
        vuint32_t P0_M5PFE:1;
        vuint32_t P0_M4PFE:1;
        vuint32_t P0_M3PFE:1;
        vuint32_t P0_M2PFE:1;
        vuint32_t P0_M1PFE:1;
        vuint32_t P0_M0PFE:1;
        vuint32_t APC:3;
        vuint32_t RWSC:5;
        vuint32_t _unused_7:1;
        vuint32_t P0_DPFEN:1;
        vuint32_t _unused_5:1;
        vuint32_t P0_IPFEN:1;
        vuint32_t _unused_3:1;
        vuint32_t P0_PFLIM:2;
        vuint32_t P0_BFEN:1;
    } B;
} PFLASH_PFCR1_tag;

typedef union PFLASH_PFCR2_union_tag { /* Platform Flash Configuration Register 2 */
    vuint32_t R;
    struct {
        vuint32_t P1_M15PFE:1;
        vuint32_t P1_M14PFE:1;
        vuint32_t P1_M13PFE:1;
        vuint32_t P1_M12PFE:1;
        vuint32_t P1_M11PFE:1;
        vuint32_t P1_M10PFE:1;
        vuint32_t P1_M9PFE:1;
        vuint32_t P1_M8PFE:1;
        vuint32_t P1_M7PFE:1;
        vuint32_t P1_M6PFE:1;
        vuint32_t P1_M5PFE:1;
        vuint32_t P1_M4PFE:1;
        vuint32_t P1_M3PFE:1;
        vuint32_t P1_M2PFE:1;
        vuint32_t P1_M1PFE:1;
        vuint32_t P1_M0PFE:1;
        vuint32_t _unused_7:9;
        vuint32_t P1_DPFEN:1;
        vuint32_t _unused_5:1;
        vuint32_t P1_IPFEN:1;
        vuint32_t _unused_3:1;
        vuint32_t P1_PFLIM:2;
        vuint32_t P1_BFEN:1;
    } B;
} PFLASH_PFCR2_tag;

typedef union PFLASH_PFCR3_union_tag { /* Platform Flash Configuration Register 3 */
    vuint32_t R;
    struct {
        vuint32_t P0_WCFG:2;
        vuint32_t P1_WCFG:2;
        vuint32_t P2_WCFG:2;
        vuint32_t _unused_21:5;
        vuint32_t _unused_20:1;
        vuint32_t _unused_17:3;
        vuint32_t BAF_DIS:1;
        vuint32_t ARBM:4;
        vuint32_t _unused_1:11;
        vuint32_t _unused_0:1;
    } B;
} PFLASH_PFCR3_tag;

typedef union PFLASH_PFAPR_union_tag { /* Platform Flash Access Protection Register */
    vuint32_t R;
    struct {
        vuint32_t M0AP:2;
        vuint32_t M1AP:2;
        vuint32_t M2AP:2;
        vuint32_t M3AP:2;
        vuint32_t M4AP:2;
        vuint32_t M5AP:2;
        vuint32_t M6AP:2;
        vuint32_t M7AP:2;
        vuint32_t M8AP:2;
        vuint32_t M9AP:2;
        vuint32_t M10AP:2;
        vuint32_t M11AP:2;
        vuint32_t M12AP:2;
        vuint32_t M13AP:2;
        vuint32_t M14AP:2;
        vuint32_t M15AP:2;
    } B;
} PFLASH_PFAPR_tag;

typedef union PFLASH_PFCRCR_union_tag { /* Platform Flash Remap Control Register */
    vuint32_t R;
    struct {
        vuint32_t _unused_9:23;
        vuint32_t SAFE_CAL:1;
        vuint32_t _unused_5:3;
        vuint32_t IRMEN:1;
        vuint32_t _unused_1:3;
        vuint32_t GRMEN:1;
    } B;
} PFLASH_PFCRCR_tag;

typedef union PFLASH_PFCRDE_union_tag { /* Platform Flash Remap Descriptor Enable Register */
    vuint32_t R;
    struct {
        vuint32_t CRD0EN:1;
        vuint32_t CRD1EN:1;
        vuint32_t CRD2EN:1;
        vuint32_t CRD3EN:1;
        vuint32_t CRD4EN:1;
        vuint32_t CRD5EN:1;
        vuint32_t CRD6EN:1;
        vuint32_t CRD7EN:1;
        vuint32_t CRD8EN:1;
        vuint32_t CRD9EN:1;
        vuint32_t CRD10EN:1;
        vuint32_t CRD11EN:1;
        vuint32_t CRD12EN:1;
        vuint32_t CRD13EN:1;
        vuint32_t CRD14EN:1;
        vuint32_t CRD15EN:1;
        vuint32_t _unused_0:16;
    } B;
} PFLASH_PFCRDE_tag;

typedef union PFLASH_PFCR4_union_tag { /* Platform Flash Configuration Register 4 */
    vuint32_t R;
    struct {
        vuint32_t P2_M15PFE:1;
        vuint32_t P2_M14PFE:1;
        vuint32_t P2_M13PFE:1;
        vuint32_t P2_M12PFE:1;
        vuint32_t P2_M11PFE:1;
        vuint32_t P2_M10PFE:1;
        vuint32_t P2_M9PFE:1;
        vuint32_t P2_M8PFE:1;
        vuint32_t P2_M7PFE:1;
        vuint32_t P2_M6PFE:1;
        vuint32_t P2_M5PFE:1;
        vuint32_t P2_M4PFE:1;
        vuint32_t P2_M3PFE:1;
        vuint32_t P2_M2PFE:1;
        vuint32_t P2_M1PFE:1;
        vuint32_t P2_M0PFE:1;
        vuint32_t _unused_7:9;
        vuint32_t P2_DPFEN:1;
        vuint32_t _unused_5:1;
        vuint32_t P2_IPFEN:1;
        vuint32_t _unused_3:1;
        vuint32_t P2_PFLIM:2;
        vuint32_t P2_BFEN:1;
    } B;
} PFLASH_PFCR4_tag;

typedef union PFLASH_PFCRD_Word0_union_tag { /* Platform Flash Calibration Region Descriptor n Word0 */
    vuint32_t R;
    struct {
        vuint32_t LSTARTADDR:28;
        vuint32_t _unused_0:4;
    } B;
} PFLASH_PFCRD_Word0_tag;

typedef union PFLASH_PFCRD_Word1_union_tag { /* Platform Flash Calibration Region Descriptor n Word1 */
    vuint32_t R;
    struct {
        vuint32_t PSTARTADDR:28;
        vuint32_t _unused_0:4;
    } B;
} PFLASH_PFCRD_Word1_tag;

typedef union PFLASH_PFCRD_Word2_union_tag { /* Platform Flash Calibration Region Descriptor n Word2 */
    vuint32_t R;
    struct {
        vuint32_t M0EN:1;
        vuint32_t M1EN:1;
        vuint32_t M2EN:1;
        vuint32_t M3EN:1;
        vuint32_t M4EN:1;
        vuint32_t M5EN:1;
        vuint32_t M6EN:1;
        vuint32_t M7EN:1;
        vuint32_t M8EN:1;
        vuint32_t M9EN:1;
        vuint32_t M10EN:1;
        vuint32_t M11EN:1;
        vuint32_t M12EN:1;
        vuint32_t M13EN:1;
        vuint32_t M14EN:1;
        vuint32_t M15EN:1;
        vuint32_t _unused_5:11;
        vuint32_t CRDSize:5;
    } B;
} PFLASH_PFCRD_Word2_tag;

typedef struct PFLASH_PFCRD_struct_tag {
    PFLASH_PFCRD_Word0_tag Word0;        /* Platform Flash Calibration Region Descriptor n Word0 */
    PFLASH_PFCRD_Word1_tag Word1;        /* Platform Flash Calibration Region Descriptor n Word1 */
    PFLASH_PFCRD_Word2_tag Word2;        /* Platform Flash Calibration Region Descriptor n Word2 */
    uint8_t PFCRD_reserved0[4];
} PFLASH_PFCRD_tag;

struct PFLASH_tag {
    PFLASH_PFCR1_tag PFCR1;              /* Platform Flash Configuration Register 1 */
    PFLASH_PFCR2_tag PFCR2;              /* Platform Flash Configuration Register 2 */
    PFLASH_PFCR3_tag PFCR3;              /* Platform Flash Configuration Register 3 */
    PFLASH_PFAPR_tag PFAPR;              /* Platform Flash Access Protection Register */
    PFLASH_PFCRCR_tag PFCRCR;            /* Platform Flash Remap Control Register */
    PFLASH_PFCRDE_tag PFCRDE;            /* Platform Flash Remap Descriptor Enable Register */
    PFLASH_PFCR4_tag PFCR4;              /* Platform Flash Configuration Register 4 */
    uint8_t PFLASH_reserved0[228];
    PFLASH_PFCRD_tag PFCRD[16];
};


/**********************PLLDIG*****************************/

typedef union PLLDIG_PLLCAL3_union_tag { /* PLL Calibration Register 3 */
    vuint32_t R;
    struct {
        vuint32_t _unused_30:2;
        vuint32_t MFDEN:16;                /* Denominator of fractional loop division factor. */
        vuint32_t _unused_0:14;
    } B;
} PLLDIG_PLLCAL3_tag;

typedef union PLLDIG_PLLCR_union_tag { /* PLLDIG PLL Control Register */
    vuint32_t R;
    struct {
        vuint32_t _unused_11:21;
        vuint32_t _unused_10:1;
        vuint32_t _unused_8:2;
        vuint32_t _unused_7:1;
        vuint32_t _unused_6:1;
        vuint32_t _unused_5:1;
        vuint32_t _unused_4:1;
        vuint32_t LOLIE:1;                 /* Loss-of-lock interrupt enable. */
        vuint32_t LOLRE:1;                 /* Loss-of-lock reset enable. */
        vuint32_t _unused_1:1;
        vuint32_t _unused_0:1;
    } B;
} PLLDIG_PLLCR_tag;

typedef union PLLDIG_PLLSR_union_tag { /* PLLDIG PLL Status Register */
    vuint32_t R;
    struct {
        vuint32_t _unused_10:22;
        vuint32_t ENPHI1:1;                /* PLL PHI1 Output Enable */
        vuint32_t ENPHI:1;                 /* PLL PHI Output Enable */
        vuint32_t EXTPDF:1;
        vuint32_t _unused_6:1;
        vuint32_t _unused_5:1;
        vuint32_t _unused_4:1;
        vuint32_t LOLF:1;                  /* Loss-of-lock flag. */
        vuint32_t LOCK:1;
        vuint32_t _unused_1:1;
        vuint32_t _unused_0:1;
    } B;
} PLLDIG_PLLSR_tag;

typedef union PLLDIG_PLLDV_union_tag { /* PLLDIG PLL Divider Register */
    vuint32_t R;
    struct {
        vuint32_t _unused_31:1;
        vuint32_t RFDPHI1:6;               /* PHI1 reduced frequency divider. */
        vuint32_t _unused_22:3;
        vuint32_t RFDPHI:6;                /* PHI reduced frequency divider. */
        vuint32_t _unused_15:1;
        vuint32_t PREDIV:3;                /* Input clock predivider. */
        vuint32_t _unused_11:1;
        vuint32_t _unused_8:3;
        vuint32_t MFD:8;                   /* Loop multiplication factor divider. */
    } B;
} PLLDIG_PLLDV_tag;

typedef union PLLDIG_PLLFM_union_tag { /* PLLDIG PLL Frequency Modulation Register */
    vuint32_t R;
    struct {
        vuint32_t _unused_31:1;
        vuint32_t SSCGBYP:1;               /* Modulation enable. */
        vuint32_t _unused_29:1;
        vuint32_t _unused_26:3;
        vuint32_t MODPRD:10;               /* Modulation period. */
        vuint32_t _unused_11:5;
        vuint32_t INCSTP:11;               /* Increment step. */
    } B;
} PLLDIG_PLLFM_tag;

typedef union PLLDIG_PLLFD_union_tag { /* PLLDIG PLL Fractional Divide Register */
    vuint32_t R;
    struct {
        vuint32_t _unused_31:1;
        vuint32_t SMDEN:1;                 /* Sigma Delta Modulation Enable */
        vuint32_t SDM2:1;                  /* Second Order Sigma Delta Modulation Select */
        vuint32_t SDM3:1;                  /* Third Order Sigma Delta Modulation Select */
        vuint32_t _unused_22:6;
        vuint32_t DTHRCTL:4;               /* Dither Control. */
        vuint32_t DTHDIS:2;                /* Dither Disable. */
        vuint32_t _unused_15:1;
        vuint32_t MFN:15;
    } B;
} PLLDIG_PLLFD_tag;

typedef union PLLDIG_PLLCAL1_union_tag { /* PLL Calibration Register 1 */
    vuint32_t R;
    struct {
        vuint32_t BYPCAL:1;                /* Bypass calibration block. */
        vuint32_t _unused_0:31;
    } B;
} PLLDIG_PLLCAL1_tag;

struct PLLDIG_tag {
    uint8_t PLLDIG_reserved0[24];
    PLLDIG_PLLCAL3_tag PLLCAL3;          /* PLL Calibration Register 3 */
    uint8_t PLLDIG_reserved1[4];
    PLLDIG_PLLCR_tag PLLCR;              /* PLLDIG PLL Control Register */
    PLLDIG_PLLSR_tag PLLSR;              /* PLLDIG PLL Status Register */
    PLLDIG_PLLDV_tag PLLDV;              /* PLLDIG PLL Divider Register */
    PLLDIG_PLLFM_tag PLLFM;              /* PLLDIG PLL Frequency Modulation Register */
    PLLDIG_PLLFD_tag PLLFD;              /* PLLDIG PLL Fractional Divide Register */
    uint8_t PLLDIG_reserved2[4];
    PLLDIG_PLLCAL1_tag PLLCAL1;          /* PLL Calibration Register 1 */
};

/*****************************PRAMC*********************************/
typedef union PRAMC_PRCR1_union_tag {  /* Platform RAM Configuration Register 1 */
    vuint32_t R;
    struct {
        vuint32_t _unused_10:22;
        vuint32_t _unused_8:2;
        vuint32_t _unused_6:2;
        vuint32_t _unused_1:5;
        vuint32_t FT_DIS:1;                /* Flow through disabled. */
    } B;
} PRAMC_PRCR1_tag;

struct PRAMC_tag {
    PRAMC_PRCR1_tag PRCR1;               /* Platform RAM Configuration Register 1 */
};

/*****Struct locations ****/
#define CAN_0 (*(volatile struct CAN_0_tag *) 0xFFEC0000UL)
#define CAN_1 (*(volatile struct CAN_1_7_tag *) 0xFBEC0000UL)
#define INTC (*(volatile struct INTC_tag *) 0xFC040000UL)
#define MC_CGM (*(volatile struct MC_CGM_tag *) 0xFFFB0000UL)
#define MC_ME (*(volatile struct MC_ME_tag *) 0xFFFB8000UL)
#define SIUL2 (*(volatile struct SIUL2_tag *) 0xFFFC0000UL)
#define PFLASH (*(volatile struct PFLASH_tag *) 0xFC030000UL)
#define PLLDIG (*(volatile struct PLLDIG_tag *) 0xFFFB0080UL)
#define PRAMC_0 (*(volatile struct PRAMC_tag *) 0xFC020000UL)
#define PRAMC_1 (*(volatile struct PRAMC_tag *) 0xFC024000UL)
#define PRAMC_2 (*(volatile struct PRAMC_tag *) 0xFC02C000UL)

/**Defines**/
#define PFLASH_PFCR1_REG PFLASH.PFCR1.R /* PFLASH registers */
#define PFLASH_PFCR2_REG PFLASH.PFCR2.R
#define PFLASH_PFCR3_REG PFLASH.PFCR3.R
#define PFLASH_PFAPR_REG PFLASH.PFAPR.R
#define PFLASH_PFCR4_REG PFLASH.PFCR4.R
#define PFLASH_PFCR1_VALUE_16MHz 0x00152117 /* Flash port p0 configuration: */
/* Port 0 prefetch enables for masters 0,3,5 (core I-busses) only, */
/* APC=1 Pipelined access can be intiazted 1 cyc before prev data valid, */
/* RWSC=1 Read Wait State Control: 1 add'l wait states (16 MHz), */
/* P0_DPFEN=0 No prefetching is triggerd by a data read access, */
/* P0_IPFEN=1 Prefetching may be triggered by any instruction read access*/
/* P0_PFLIM=3 Prefetch on miss or hit, */
/* P0_BFEN=1 Line read buffers are enabled. */
#define PFLASH_PFCR1_VALUE_160MHz 0x00152417 /* Flash port p0 configuration: */
/* RWSC=4 r Read Wait State Control: 4 add'l wait states (160 MHz), */
#define PFLASH_PFCR2_VALUE_BASIC 0x00150017 /* Flash port p1 configuration: */
#define PFLASH_PFCR3_VALUE_BASIC 0x00000000 /* Flash way cfg, arb., BAF dis. */
#define PFLASH_PFAPR_VALUE_BASIC 0xFFFFFFFF /* R/W access to flash array: */
#define PFLASH_PFCR4_VALUE_BASIC 0x00150017
#ifdef __MWERKS__
#pragma pop
#endif
#ifdef __ghs__
#pragma ghs endnowarning
#endif
#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif
#ifdef  __cplusplus
}
#endif
#endif /* ifdef CALYPSO_H */