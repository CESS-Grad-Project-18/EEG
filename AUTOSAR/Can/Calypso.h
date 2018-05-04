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

/*******************CAN 0**********************/

struct CAN_0_tag {
  union {                              /* Module Configuration Register */
    vuint32_t R;
    struct {
      vuint32_t MDIS:1;                /* Module Disable */
      vuint32_t FRZ:1;                 /* Freeze Enable */
      vuint32_t RFEN:1;                /* Rx FIFO Enable */
      vuint32_t HALT:1;                /* Halt FlexCAN */
      vuint32_t NOTRDY:1;              /* FlexCAN Not Ready */
      vuint32_t WAKMSK:1;              /* Wake Up Interrupt Mask */
      vuint32_t SOFTRST:1;             /* Soft Reset */
      vuint32_t FRZACK:1;              /* Freeze Mode Acknowledge */
      vuint32_t SUPV:1;                /* Supervisor Mode */
      vuint32_t SLFWAK:1;              /* Self Wake Up */
      vuint32_t WRNEN:1;               /* Warning Interrupt Enable */
      vuint32_t LPMACK:1;              /* Low-Power Mode Acknowledge */
      vuint32_t WAKSRC:1;              /* Wake Up Source */
      vuint32_t  :1;
      vuint32_t SRXDIS:1;              /* Self Reception Disable */
      vuint32_t IRMQ:1;                /* Individual Rx Masking And Queue Enable */
      vuint32_t DMA:1;                 /* DMA Enable */
      vuint32_t PNET_EN:1;             /* Pretended Networking Enable */
      vuint32_t LPRIOEN:1;             /* Local Priority Enable */
      vuint32_t AEN:1;                 /* Abort Enable */
      vuint32_t FDEN:1;                /* CAN FD operation enable */
      vuint32_t  :1;
      vuint32_t IDAM:2;                /* ID Acceptance Mode */
      vuint32_t  :1;
      vuint32_t MAXMB:7;               /* Number Of The Last Message Buffer */
    } B;
  } MCR;

  union {                              /* Control 1 register */
    vuint32_t R;
    struct {
      vuint32_t PRESDIV:8;             /* Prescaler Division Factor */
      vuint32_t RJW:2;                 /* Resync Jump Width */
      vuint32_t PSEG1:3;               /* Phase Segment 1 */
      vuint32_t PSEG2:3;               /* Phase Segment 2 */
      vuint32_t BOFFMSK:1;             /* Bus Off Interrupt Mask */
      vuint32_t ERRMSK:1;              /* Error Interrupt Mask */
      vuint32_t CLKSRC:1;              /* CAN Engine Clock Source */
      vuint32_t LPB:1;                 /* Loop Back Mode */
      vuint32_t TWRNMSK:1;             /* Tx Warning Interrupt Mask */
      vuint32_t RWRNMSK:1;             /* Rx Warning Interrupt Mask */
      vuint32_t  :1;
      vuint32_t  :1;
      vuint32_t SMP:1;                 /* CAN Bit Sampling */
      vuint32_t BOFFREC:1;             /* Bus Off Recovery */
      vuint32_t TSYN:1;                /* Timer Sync */
      vuint32_t LBUF:1;                /* Lowest Buffer Transmitted First */
      vuint32_t LOM:1;                 /* Listen-Only Mode */
      vuint32_t PROPSEG:3;             /* Propagation Segment */
    } B;
  } CTRL1;

  union {                              /* Free Running Timer */
    vuint32_t R;
    struct {
      vuint32_t  :16;
      vuint32_t TIMER:16;              /* Timer Value */
    } B;
  } TIMER;

  uint8_t CAN_0_reserved0[4];
  union {                              /* Rx Mailboxes Global Mask Register */
    vuint32_t R;
    struct {
      vuint32_t MG:32;                 /* Rx Mailboxes Global Mask Bits */
    } B;
  } RXMGMASK;

  union {                              /* Rx 14 Mask register */
    vuint32_t R;
    struct {
      vuint32_t RX14M:32;              /* Rx Buffer 14 Mask Bits */
    } B;
  } RX14MASK;

  union {                              /* Rx 15 Mask register */
    vuint32_t R;
    struct {
      vuint32_t RX15M:32;              /* Rx Buffer 15 Mask Bits */
    } B;
  } RX15MASK;

  union {                              /* Error Counter */
    vuint32_t R;
    struct {
      vuint32_t RXERRCNT_FAST:8;       /* Receive Error Counter for fast bits */
      vuint32_t TXERRCNT_FAST:8;       /* Transmit Error Counter for fast bits */
      vuint32_t RXERRCNT:8;            /* Receive Error Counter */
      vuint32_t TXERRCNT:8;            /* Transmit Error Counter */
    } B;
  } ECR;

  union {                              /* Error and Status 1 register */
    vuint32_t R;
    struct {
      vuint32_t BIT1ERR_FAST:1;        /* Bit1 Error in the Data Phase of CAN FD frames with the BRS bit set */
      vuint32_t BIT0ERR_FAST:1;        /* Bit0 Error in the Data Phase of CAN FD frames with the BRS bit set */
      vuint32_t  :1;
      vuint32_t CRCERR_FAST:1;         /* Cyclic Redundancy Check Error in the CRC field of CAN FD frames with the BRS bit set */
      vuint32_t FRMERR_FAST:1;         /* Form Error in the Data Phase of CAN FD frames with the BRS bit set */
      vuint32_t STFERR_FAST:1;         /* Stuffing Error in the Data Phase of CAN FD frames with the BRS bit set */
      vuint32_t  :4;
      vuint32_t ERROVR:1;              /* Error Overrun bit */
      vuint32_t ERRINT_FAST:1;         /* Error Interrupt for errors detected in the Data Phase of CAN FD frames with the BRS bit set */
      vuint32_t BOFFDONEINT:1;         /* Bus Off Done Interrupt */
      vuint32_t SYNCH:1;               /* CAN Synchronization Status */
      vuint32_t TWRNINT:1;             /* Tx Warning Interrupt Flag */
      vuint32_t RWRNINT:1;             /* Rx Warning Interrupt Flag */
      vuint32_t BIT1ERR:1;             /* Bit1 Error */
      vuint32_t BIT0ERR:1;             /* Bit0 Error */
      vuint32_t ACKERR:1;              /* Acknowledge Error */
      vuint32_t CRCERR:1;              /* Cyclic Redundancy Check Error */
      vuint32_t FRMERR:1;              /* Form Error */
      vuint32_t STFERR:1;              /* Stuffing Error */
      vuint32_t TXWRN:1;               /* TX Error Warning */
      vuint32_t RXWRN:1;               /* Rx Error Warning */
      vuint32_t IDLE:1;
      vuint32_t TX:1;                  /* FlexCAN In Transmission */
      vuint32_t FLTCONF:2;             /* Fault Confinement State */
      vuint32_t RX:1;                  /* FlexCAN In Reception */
      vuint32_t BOFFINT:1;             /* Bus Off Interrupt */
      vuint32_t ERRINT:1;              /* Error Interrupt */
      vuint32_t WAKINT:1;              /* Wake-Up Interrupt */
    } B;
  } ESR1;

  union {                              /* Interrupt Masks 2 register */
    vuint32_t R;
    struct {
      vuint32_t BUF63TO32M:32;         /* Buffer MB i Mask */
    } B;
  } IMASK2;

  union {                              /* Interrupt Masks 1 register */
    vuint32_t R;
    struct {
      vuint32_t BUF31TO0M:32;          /* Buffer MB i Mask */
    } B;
  } IMASK1;

  union {                              /* Interrupt Flags 2 register */
    vuint32_t R;
    struct {
      vuint32_t BUF63TO32I:32;         /* Buffer MB i Interrupt */
    } B;
  } IFLAG2;

  union {                              /* Interrupt Flags 1 register */
    vuint32_t R;
    struct {
      vuint32_t BUF31TO8I:24;          /* Buffer MBi Interrupt */
      vuint32_t BUF7I:1;               /* Buffer MB7 Interrupt Or "Rx FIFO Overflow" */
      vuint32_t BUF6I:1;               /* Buffer MB6 Interrupt Or "Rx FIFO Warning" */
      vuint32_t BUF5I:1;               /* Buffer MB5 Interrupt Or "Frames available in Rx FIFO" */
      vuint32_t BUF4TO1I:4;            /* Buffer MB i Interrupt Or "reserved" */
      vuint32_t BUF0I:1;               /* Buffer MB0 Interrupt Or "reserved" */
    } B;
  } IFLAG1;

  union {                              /* Control 2 register */
    vuint32_t R;
    struct {
      vuint32_t ERRMSK_FAST:1;         /* Error Interrupt Mask for errors detected in the Data Phase of fast CAN FD frames */
      vuint32_t BOFFDONEMSK:1;         /* Bus Off Done Interrupt Mask */
      vuint32_t ECRWRE:1;              /* Error-correction Configuration Register Write Enable */
      vuint32_t WRMFRZ:1;              /* Write-Access To Memory In Freeze Mode */
      vuint32_t RFFN:4;                /* Number Of Rx FIFO Filters */
      vuint32_t TASD:5;                /* Tx Arbitration Start Delay */
      vuint32_t MRP:1;                 /* Mailboxes Reception Priority */
      vuint32_t RRS:1;                 /* Remote Request Storing */
      vuint32_t EACEN:1;               /* Entire Frame Arbitration Field Comparison Enable For Rx Mailboxes */
      vuint32_t TIMER_SRC:1;           /* Timer Source */
      vuint32_t  :15;
    } B;
  } CTRL2;

  union {                              /* Error and Status 2 register */
    vuint32_t R;
    struct {
      vuint32_t  :9;
      vuint32_t LPTM:7;                /* Lowest Priority Tx Mailbox */
      vuint32_t  :1;
      vuint32_t VPS:1;                 /* Valid Priority Status */
      vuint32_t IMB:1;                 /* Inactive Mailbox */
      vuint32_t  :13;
    } B;
  } ESR2;

  uint8_t CAN_0_reserved1[8];
  union {                              /* CRC Register */
    vuint32_t R;
    struct {
      vuint32_t  :9;
      vuint32_t MBCRC:7;               /* CRC Mailbox */
      vuint32_t  :1;
      vuint32_t TXCRC:15;              /* Transmitted CRC value */
    } B;
  } CRCR;

  union {                              /* Rx FIFO Global Mask register */
    vuint32_t R;
    struct {
      vuint32_t FGM:32;                /* Rx FIFO Global Mask Bits */
    } B;
  } RXFGMASK;

  union {                              /* Rx FIFO Information Register */
    vuint32_t R;
    struct {
      vuint32_t  :23;
      vuint32_t IDHIT:9;               /* Identifier Acceptance Filter Hit Indicator */
    } B;
  } RXFIR;

  union {                              /* CAN Bit Timing Register */
    vuint32_t R;
    struct {
      vuint32_t BTF:1;                 /* Bit Timing Format Enable */
      vuint32_t EPRESDIV:10;           /* Extended Prescaler Division Factor */
      vuint32_t  :1;
      vuint32_t ERJW:4;                /* Extended Resync Jump Width */
      vuint32_t EPROPSEG:6;            /* Extended Propagation Segment */
      vuint32_t EPSEG1:5;              /* Extended Phase Segment 1 */
      vuint32_t EPSEG2:5;              /* Extended Phase Segment 2 */
    } B;
  } CBT;

  uint8_t CAN_0_reserved2[24];
  union {                              /* Interrupt Masks 3 Register */
    vuint32_t R;
    struct {
      vuint32_t BUF95TO64M:32;         /* Buffer MB i Mask */
    } B;
  } IMASK3;

  uint8_t CAN_0_reserved3[4];
  union {                              /* Interrupt Flags 3 Register */
    vuint32_t R;
    struct {
      vuint32_t BUF95TO64:32;          /* Buffer MB i Interrupt */
    } B;
  } IFLAG3;

  uint8_t CAN_0_reserved4[8];
  struct {
    union {                            /* Message Buffer 0 CS Register */
      vuint32_t R;
      struct {
        vuint32_t  :4;
        vuint32_t CODE:4;              /* Message Buffer Code */
        vuint32_t  :1;
        vuint32_t SRR:1;               /* Substitute Remote Request. Contains a fixed recessive bit. */
        vuint32_t IDE:1;               /* ID Extended. One/zero for extended/standard format frame. */
        vuint32_t RTR:1;               /* Remote Transmission Request. One/zero for remote/data frame. */
        vuint32_t DLC:4;               /* Length of the data to be stored/transmitted. */
        vuint32_t TIMESTAMP:16;        /* Free-Running Counter Time stamp. This 16-bit field is a copy of the Free-Running Timer, captured for Tx and Rx frames at the time when the beginning of the Identifier field appears on the CAN bus. */
      } B;
    } CS;
    union {                            /* Message Buffer 0 ID Register */
      vuint32_t R;
      struct {
        vuint32_t PRIO:3;              /* Local Priority */
        vuint32_t ID_STD:11;           /* Frame Identifier Standard */
        vuint32_t ID_EXT:18;           /* Frame Identifier Extended */
      } B;
    } ID;
    union {
      vuint8_t B[8];
      vuint16_t H[4];
      vuint32_t W[2];
    } DATA;
  } MB[96];

  uint8_t CAN_0_reserved5[512];
  union {                              /* Rx Individual Mask Registers */
    vuint32_t R;
    struct {
      vuint32_t MI:32;                 /* Individual Mask Bits */
    } B;
  } RXIMR[96];

  uint8_t CAN_0_reserved6[224];
  union {                              /* Memory Error Control Register */
    vuint32_t R;
    struct {
      vuint32_t ECRWRDIS:1;            /* Error Configuration Register Write Disable */
      vuint32_t  :11;
      vuint32_t HANCEI_MSK:1;          /* Host Access With Non-Correctable Errors Interrupt Mask */
      vuint32_t FANCEI_MSK:1;          /* FlexCAN Access With Non-Correctable Errors Interrupt Mask */
      vuint32_t  :1;
      vuint32_t CEI_MSK:1;             /* Correctable Errors Interrupt Mask */
      vuint32_t HAERRIE:1;             /* Host Access Error Injection Enable */
      vuint32_t FAERRIE:1;             /* FlexCAN Access Error Injection Enable */
      vuint32_t EXTERRIE:1;            /* Extended Error Injection Enable */
      vuint32_t  :3;
      vuint32_t RERRDIS:1;             /* Error Report Disable */
      vuint32_t ECCDIS:1;              /* Error Correction Disable */
      vuint32_t NCEFAFRZ:1;            /* Non-Correctable Errors In FlexCAN Access Put Device In Freeze Mode */
      vuint32_t  :7;
    } B;
  } MECR;

  union {                              /* Error Injection Address Register */
    vuint32_t R;
    struct {
      vuint32_t  :18;
      vuint32_t INJADDR:14;            /* Error Injection Address */
    } B;
  } ERRIAR;

  union {                              /* Error Injection Data Pattern Register */
    vuint32_t R;
    struct {
      vuint32_t DFLIP:32;              /* Data flip pattern */
    } B;
  } ERRIDPR;

  union {                              /* Error Injection Parity Pattern Register */
    vuint32_t R;
    struct {
      vuint32_t  :3;
      vuint32_t PFLIP3:5;              /* Parity Flip Pattern For Byte 3 (most significant) */
      vuint32_t  :3;
      vuint32_t PFLIP2:5;              /* Parity Flip Pattern For Byte 2 */
      vuint32_t  :3;
      vuint32_t PFLIP1:5;              /* Parity Flip Pattern For Byte 1 */
      vuint32_t  :3;
      vuint32_t PFLIP0:5;              /* Parity Flip Pattern For Byte 0 (Least Significant) */
    } B;
  } ERRIPPR;

  union {                              /* Error Report Address Register */
    vuint32_t R;
    struct {
      vuint32_t  :7;
      vuint32_t NCE:1;                 /* Non-Correctable Error */
      vuint32_t  :5;
      vuint32_t SAID:3;
      vuint32_t  :2;
      vuint32_t ERRADDR:14;            /* Address Where The Error Was Detected */
    } B;
  } RERRAR;

  union {                              /* Error Report Data Register */
    vuint32_t R;
    struct {
      vuint32_t RDATA:32;              /* Raw data word read from memory with error */
    } B;
  } RERRDR;

  union {                              /* Error Report Syndrome Register */
    vuint32_t R;
    struct {
      vuint32_t BE3:1;                 /* Byte Enabled For Byte 3 (Most Significant) */
      vuint32_t  :2;
      vuint32_t SYND3:5;               /* Error Syndrome For Byte 3 (Most Significant) */
      vuint32_t BE2:1;                 /* Byte Enabled For Byte 2 */
      vuint32_t  :2;
      vuint32_t SYND2:5;               /* Error Syndrome For Byte 2 */
      vuint32_t BE1:1;                 /* Byte Enabled For Byte 1 */
      vuint32_t  :2;
      vuint32_t SYND1:5;               /* Error Syndrome for Byte 1 */
      vuint32_t BE0:1;                 /* Byte Enabled For Byte 0 (least significant) */
      vuint32_t  :2;
      vuint32_t SYND0:5;               /* Error Syndrome For Byte 0 (least significant) */
    } B;
  } RERRSYNR;

  union {                              /* Error Status Register */
    vuint32_t R;
    struct {
      vuint32_t  :12;
      vuint32_t HANCEIF:1;             /* Host Access With Non-Correctable Error Interrupt Flag */
      vuint32_t FANCEIF:1;             /* FlexCAN Access With Non-Correctable Error Interrupt Flag */
      vuint32_t  :1;
      vuint32_t CEIF:1;                /* Correctable Error Interrupt Flag */
      vuint32_t  :12;
      vuint32_t HANCEIOF:1;            /* Host Access With Non-Correctable Error Interrupt Overrun Flag */
      vuint32_t FANCEIOF:1;            /* FlexCAN Access With Non-Correctable Error Interrupt Overrun Flag */
      vuint32_t  :1;
      vuint32_t CEIOF:1;               /* Correctable Error Interrupt Overrun Flag */
    } B;
  } ERRSR;

  union {                              /* Pretended Networking Control 1 Register */
    vuint32_t R;
    struct {
      vuint32_t  :14;
      vuint32_t WTOF_MSK:1;            /* Wake Up by Timeout Flag Mask Bit */
      vuint32_t WUMF_MSK:1;            /* Wake Up by Match Flag Mask Bit */
      vuint32_t NMATCH:8;              /* Number of Messages Matching the Same Filtering Criteria */
      vuint32_t  :2;
      vuint32_t PLFS:2;                /* Payload Filtering Selection */
      vuint32_t IDFS:2;                /* ID Filtering Selection */
      vuint32_t FCS:2;                 /* Filtering Combination Selection */
    } B;
  } CTRL1_PN;

  union {                              /* Pretended Networking Control 2 Register */
    vuint32_t R;
    struct {
      vuint32_t  :16;
      vuint32_t MATCHTO:16;            /* Timeout for No Message Matching the Filtering Criteria */
    } B;
  } CTRL2_PN;

  union {                              /* Pretended Networking Wake Up Match Register */
    vuint32_t R;
    struct {
      vuint32_t  :14;
      vuint32_t WTOF:1;                /* Wake Up by Timeout Flag Bit */
      vuint32_t WUMF:1;                /* Wake Up by Match Flag Bit */
      vuint32_t MCOUNTER:8;            /* Number of Matches while in Pretended Networking */
      vuint32_t  :8;
    } B;
  } WU_MTC;

  union {                              /* Pretended Networking ID Filter 1 Register */
    vuint32_t R;
    struct {
      vuint32_t  :1;
      vuint32_t FLT_IDE:1;             /* ID Extended Filter */
      vuint32_t FLT_RTR:1;             /* Remote Transmission Request Filter */
      vuint32_t FLT_ID1:29;            /* ID Filter 1 for Pretended Networking filtering */
    } B;
  } FLT_ID1;

  union {                              /* Pretended Networking DLC Filter Register */
    vuint32_t R;
    struct {
      vuint32_t  :12;
      vuint32_t FLT_DLC_LO:4;          /* Lower Limit for Length of Data Bytes Filter */
      vuint32_t  :12;
      vuint32_t FLT_DLC_HI:4;          /* Upper Limit for Length of Data Bytes Filter */
    } B;
  } FLT_DLC;

  union {                              /* Pretended Networking Payload Low Filter 1 Register */
    vuint32_t R;
    struct {
      vuint32_t Data_byte_0:8;         /* Payload Filter 1 low order bits for Pretended Networking payload filtering corresponding to the data byte 0. */
      vuint32_t Data_byte_1:8;         /* Payload Filter 1 low order bits for Pretended Networking payload filtering corresponding to the data byte 1. */
      vuint32_t Data_byte_2:8;         /* Payload Filter 1 low order bits for Pretended Networking payload filtering corresponding to the data byte 2. */
      vuint32_t Data_byte_3:8;         /* Payload Filter 1 low order bits for Pretended Networking payload filtering corresponding to the data byte 3. */
    } B;
  } PL1_LO;

  union {                              /* Pretended Networking Payload High Filter 1 Register */
    vuint32_t R;
    struct {
      vuint32_t Data_byte_4:8;         /* Payload Filter 1 high order bits for Pretended Networking payload filtering corresponding to the data byte 4. */
      vuint32_t Data_byte_5:8;         /* Payload Filter 1 high order bits for Pretended Networking payload filtering corresponding to the data byte 5. */
      vuint32_t Data_byte_6:8;         /* Payload Filter 1 high order bits for Pretended Networking payload filtering corresponding to the data byte 6. */
      vuint32_t Data_byte_7:8;         /* Payload Filter 1 high order bits for Pretended Networking payload filtering corresponding to the data byte 7. */
    } B;
  } PL1_HI;

  union {                              /* Pretended Networking ID Filter 2 Register / ID Mask Register */
    vuint32_t R;
    struct {
      vuint32_t  :1;
      vuint32_t IDE_MSK:1;             /* ID Extended Mask Bit */
      vuint32_t RTR_MSK:1;             /* Remote Transmission Request Mask Bit */
      vuint32_t FLT_ID2_IDMASK:29;     /* ID Filter 2 for Pretended Networking Filtering / ID Mask Bits for Pretended Networking ID Filtering */
    } B;
  } FLT_ID2_IDMASK;

  union {                              /* Pretended Networking Payload Low Filter 2 Register / Payload Low Mask Register */
    vuint32_t R;
    struct {
      vuint32_t Data_byte_0:8;         /* Payload Filter 2 low order bits / Payload Mask low order bits for Pretended Networking payload filtering corresponding to the data byte 0. */
      vuint32_t Data_byte_1:8;         /* Payload Filter 2 low order bits / Payload Mask low order bits for Pretended Networking payload filtering corresponding to the data byte 1. */
      vuint32_t Data_byte_2:8;         /* Payload Filter 2 low order bits / Payload Mask low order bits for Pretended Networking payload filtering corresponding to the data byte 2. */
      vuint32_t Data_byte_3:8;         /* Payload Filter 2 low order bits / Payload Mask low order bits for Pretended Networking payload filtering corresponding to the data byte 3. */
    } B;
  } PL2_PLMASK_LO;

  union {                              /* Pretended Networking Payload High Filter 2 low order bits / Payload High Mask Register */
    vuint32_t R;
    struct {
      vuint32_t Data_byte_4:8;         /* Payload Filter 2 high order bits / Payload Mask high order bits for Pretended Networking payload filtering corresponding to the data byte 4. */
      vuint32_t Data_byte_5:8;         /* Payload Filter 2 high order bits / Payload Mask high order bits for Pretended Networking payload filtering corresponding to the data byte 5. */
      vuint32_t Data_byte_6:8;         /* Payload Filter 2 high order bits / Payload Mask high order bits for Pretended Networking payload filtering corresponding to the data byte 6. */
      vuint32_t Data_byte_7:8;         /* Payload Filter 2 high order bits / Payload Mask high order bits for Pretended Networking payload filtering corresponding to the data byte 7. */
    } B;
  } PL2_PLMASK_HI;

  uint8_t CAN_0_reserved7[24];
  struct {
    union {                            /* Wake Up Message Buffer Register for C/S */
      vuint32_t R;
      struct {
        vuint32_t  :9;
        vuint32_t SRR:1;               /* Substitute Remote Request */
        vuint32_t IDE:1;               /* ID Extended Bit */
        vuint32_t RTR:1;               /* Remote Transmission Request Bit */
        vuint32_t DLC:4;               /* Length of Data in Bytes */
        vuint32_t  :16;
      } B;
    } CS;
    union {                            /* Wake Up Message Buffer Register for ID */
      vuint32_t R;
      struct {
        vuint32_t  :3;
        vuint32_t ID:29;               /* Received ID under Pretended Networking mode */
      } B;
    } ID;
    union {                            /* Wake Up Message Buffer Register for Data 0-3 */
      vuint32_t R;
      struct {
        vuint32_t Data_byte_0:8;       /* Received payload corresponding to the data byte 0 under Pretended Networking mode */
        vuint32_t Data_byte_1:8;       /* Received payload corresponding to the data byte 1 under Pretended Networking mode */
        vuint32_t Data_byte_2:8;       /* Received payload corresponding to the data byte 2 under Pretended Networking mode */
        vuint32_t Data_byte_3:8;       /* Received payload corresponding to the data byte 3 under Pretended Networking mode */
      } B;
    } D03;
    union {                            /* Wake Up Message Buffer Register Data 4-7 */
      vuint32_t R;
      struct {
        vuint32_t Data_byte_4:8;       /* Received payload corresponding to the data byte 4 under Pretended Networking mode */
        vuint32_t Data_byte_5:8;       /* Received payload corresponding to the data byte 5 under Pretended Networking mode */
        vuint32_t Data_byte_6:8;       /* Received payload corresponding to the data byte 6 under Pretended Networking mode */
        vuint32_t Data_byte_7:8;       /* Received payload corresponding to the data byte 7 under Pretended Networking mode */
      } B;
    } D47;
  } WMB[4];

  uint8_t CAN_0_reserved8[128];
  union {                              /* CAN FD Control Register */
    vuint32_t R;
    struct {
      vuint32_t FDRATE:1;              /* Bit Rate Switch Enable */
      vuint32_t  :4;
      vuint32_t  :2;
      vuint32_t  :1;
      vuint32_t MBDSR2:2;              /* Message Buffer Data Size for Region 2 */
      vuint32_t  :1;
      vuint32_t MBDSR1:2;              /* Message Buffer Data Size for Region 1 */
      vuint32_t  :1;
      vuint32_t MBDSR0:2;              /* Message Buffer Data Size for Region 0 */
      vuint32_t TDCEN:1;               /* Transceiver Delay Compensation Enable */
      vuint32_t TDCFAIL:1;             /* Transceiver Delay Compensation Fail */
      vuint32_t  :1;
      vuint32_t TDCOFF:5;              /* Transceiver Delay Compensation Offset */
      vuint32_t  :2;
      vuint32_t TDCVAL:6;              /* Transceiver Delay Compensation Value */
    } B;
  } FDCTRL;

  union {                              /* CAN FD Bit Timing Register */
    vuint32_t R;
    struct {
      vuint32_t  :2;
      vuint32_t FPRESDIV:10;           /* Fast Prescaler Division Factor */
      vuint32_t  :2;
      vuint32_t FRJW:2;                /* Fast Resync Jump Width */
      vuint32_t  :1;
      vuint32_t FPROPSEG:5;            /* Fast Propagation Segment */
      vuint32_t  :2;
      vuint32_t FPSEG1:3;              /* Fast Phase Segment 1 */
      vuint32_t  :2;
      vuint32_t FPSEG2:3;              /* Fast Phase Segment 2 */
    } B;
  } FDCBT;

  union {                              /* CAN FD CRC Register */
    vuint32_t R;
    struct {
      vuint32_t  :1;
      vuint32_t FD_MBCRC:7;            /* CRC Mailbox Number for FD_TXCRC */
      vuint32_t  :3;
      vuint32_t FD_TXCRC:21;           /* Extended Transmitted CRC value */
    } B;
  } FDCRC;
};


/*******************CAN 1**********************/

struct CAN_1_tag {
  union {                              /* Module Configuration Register */
    vuint32_t R;
    struct {
      vuint32_t MDIS:1;                /* Module Disable */
      vuint32_t FRZ:1;                 /* Freeze Enable */
      vuint32_t RFEN:1;                /* Rx FIFO Enable */
      vuint32_t HALT:1;                /* Halt FlexCAN */
      vuint32_t NOTRDY:1;              /* FlexCAN Not Ready */
      vuint32_t WAKMSK:1;              /* Wake Up Interrupt Mask */
      vuint32_t SOFTRST:1;             /* Soft Reset */
      vuint32_t FRZACK:1;              /* Freeze Mode Acknowledge */
      vuint32_t SUPV:1;                /* Supervisor Mode */
      vuint32_t SLFWAK:1;              /* Self Wake Up */
      vuint32_t WRNEN:1;               /* Warning Interrupt Enable */
      vuint32_t LPMACK:1;              /* Low-Power Mode Acknowledge */
      vuint32_t WAKSRC:1;              /* Wake Up Source */
      vuint32_t  :1;
      vuint32_t SRXDIS:1;              /* Self Reception Disable */
      vuint32_t IRMQ:1;                /* Individual Rx Masking And Queue Enable */
      vuint32_t  :1;
      vuint32_t  :1;                   /* Pretended Networking Enable */
      vuint32_t LPRIOEN:1;             /* Local Priority Enable */
      vuint32_t AEN:1;                 /* Abort Enable */
      vuint32_t  :2;
      vuint32_t IDAM:2;                /* ID Acceptance Mode */
      vuint32_t  :1;
      vuint32_t MAXMB:7;               /* Number Of The Last Message Buffer */
    } B;
  } MCR;

  union {                              /* Control 1 register */
    vuint32_t R;
    struct {
      vuint32_t PRESDIV:8;             /* Prescaler Division Factor */
      vuint32_t RJW:2;                 /* Resync Jump Width */
      vuint32_t PSEG1:3;               /* Phase Segment 1 */
      vuint32_t PSEG2:3;               /* Phase Segment 2 */
      vuint32_t BOFFMSK:1;             /* Bus Off Mask */
      vuint32_t ERRMSK:1;              /* Error Mask */
      vuint32_t CLKSRC:1;              /* CAN Engine Clock Source */
      vuint32_t LPB:1;                 /* Loop Back Mode */
      vuint32_t TWRNMSK:1;             /* Tx Warning Interrupt Mask */
      vuint32_t RWRNMSK:1;             /* Rx Warning Interrupt Mask */
      vuint32_t  :2;
      vuint32_t SMP:1;                 /* CAN Bit Sampling */
      vuint32_t BOFFREC:1;             /* Bus Off Recovery */
      vuint32_t TSYN:1;                /* Timer Sync */
      vuint32_t LBUF:1;                /* Lowest Buffer Transmitted First */
      vuint32_t LOM:1;                 /* Listen-Only Mode */
      vuint32_t PROPSEG:3;             /* Propagation Segment */
    } B;
  } CTRL1;

  union {                              /* Free Running Timer */
    vuint32_t R;
    struct {
      vuint32_t  :16;
      vuint32_t TIMER:16;              /* Timer Value */
    } B;
  } TIMER;

  uint8_t CAN_reserved0[4];
  union {                              /* Rx Mailboxes Global Mask Register */
    vuint32_t R;
    struct {
      vuint32_t MG:32;                 /* Rx Mailboxes Global Mask Bits */
    } B;
  } RXMGMASK;

  union {                              /* Rx 14 Mask register */
    vuint32_t R;
    struct {
      vuint32_t RX14M:32;              /* Rx Buffer 14 Mask Bits */
    } B;
  } RX14MASK;

  union {                              /* Rx 15 Mask register */
    vuint32_t R;
    struct {
      vuint32_t RX15M:32;              /* Rx Buffer 15 Mask Bits */
    } B;
  } RX15MASK;

  union {                              /* Error Counter */
    vuint32_t R;
    struct {
      vuint32_t RXERRCNT_FAST:8;       /* Receive Error Counter for fast bits */
      vuint32_t TXERRCNT_FAST:8;       /* Transmit Error Counter for fast bits */
      vuint32_t RXERRCNT:8;            /* Receive Error Counter */
      vuint32_t TXERRCNT:8;            /* Transmit Error Counter */
    } B;
  } ECR;

  union {                              /* Error and Status 1 register */
    vuint32_t R;
    struct {
      vuint32_t BIT1ERR_FAST:1;        /* Bit1 Error in the Data Phase of CAN FD frames with the BRS bit set */
      vuint32_t BIT0ERR_FAST:1;        /* Bit0 Error in the Data Phase of CAN FD frames with the BRS bit set */
      vuint32_t  :1;
      vuint32_t CRCERR_FAST:1;         /* Cyclic Redundancy Check Error in the CRC field of CAN FD frames with the BRS bit set */
      vuint32_t FRMERR_FAST:1;         /* Form Error in the Data Phase of CAN FD frames with the BRS bit set */
      vuint32_t STFERR_FAST:1;         /* Stuffing Error in the Data Phase of CAN FD frames with the BRS bit set */
      vuint32_t  :4;
      vuint32_t ERROVR:1;              /* Error Overrun bit */
      vuint32_t ERRINT_FAST:1;         /* Error Interrupt for errors detected in the Data Phase of CAN FD frames with the BRS bit set */
      vuint32_t BOFFDONEINT:1;         /* Bus Off Done Interrupt */
      vuint32_t SYNCH:1;               /* CAN Synchronization Status */
      vuint32_t TWRNINT:1;             /* Tx Warning Interrupt Flag */
      vuint32_t RWRNINT:1;             /* Rx Warning Interrupt Flag */
      vuint32_t BIT1ERR:1;             /* Bit1 Error */
      vuint32_t BIT0ERR:1;             /* Bit0 Error */
      vuint32_t ACKERR:1;              /* Acknowledge Error */
      vuint32_t CRCERR:1;              /* Cyclic Redundancy Check Error */
      vuint32_t FRMERR:1;              /* Form Error */
      vuint32_t STFERR:1;              /* Stuffing Error */
      vuint32_t TXWRN:1;               /* TX Error Warning */
      vuint32_t RXWRN:1;               /* Rx Error Warning */
      vuint32_t IDLE:1;
      vuint32_t TX:1;                  /* FlexCAN In Transmission */
      vuint32_t FLTCONF:2;             /* Fault Confinement State */
      vuint32_t RX:1;                  /* FlexCAN In Reception */
      vuint32_t BOFFINT:1;             /* Bus Off Interrupt */
      vuint32_t ERRINT:1;              /* Error Interrupt */
      vuint32_t WAKINT:1;              /* Wake-Up Interrupt */
    } B;
  } ESR1;

  union {                              /* Interrupt Masks 2 register */
    vuint32_t R;
    struct {
      vuint32_t BUFHM:32;              /* Buffer MB i Mask */
    } B;
  } IMASK2;

  union {                              /* Interrupt Masks 1 register */
    vuint32_t R;
    struct {
      vuint32_t BUFLM:32;              /* Buffer MB i Mask */
    } B;
  } IMASK1;

  union {                              /* Interrupt Flags 2 register */
    vuint32_t R;
    struct {
      vuint32_t BUFHI:32;              /* Buffer MB i Interrupt */
    } B;
  } IFLAG2;

  union {                              /* Interrupt Flags 1 register */
    vuint32_t R;
    struct {
      vuint32_t BUF31TO8I:24;          /* Buffer MBi Interrupt */
      vuint32_t BUF7I:1;               /* Buffer MB7 Interrupt Or "Rx FIFO Overflow" */
      vuint32_t BUF6I:1;               /* Buffer MB6 Interrupt Or "Rx FIFO Warning" */
      vuint32_t BUF5I:1;               /* Buffer MB5 Interrupt Or "Frames available in Rx FIFO" */
      vuint32_t BUF4TO1I:4;            /* Buffer MB i Interrupt Or "reserved" */
      vuint32_t BUF0I:1;               /* Buffer MB0 Interrupt Or "reserved" */
    } B;
  } IFLAG1;

  union {                              /* Control 2 register */
    vuint32_t R;
    struct {
      vuint32_t  :3;
      vuint32_t WRMFRZ:1;              /* Write-Access To Memory In Freeze Mode */
      vuint32_t RFFN:4;                /* Number Of Rx FIFO Filters */
      vuint32_t TASD:5;                /* Tx Arbitration Start Delay */
      vuint32_t MRP:1;                 /* Mailboxes Reception Priority */
      vuint32_t RRS:1;                 /* Remote Request Storing */
      vuint32_t EACEN:1;               /* Entire Frame Arbitration Field Comparison Enable For Rx Mailboxes */
      vuint32_t  :16;
    } B;
  } CTRL2;

  union {                              /* Error and Status 2 register */
    vuint32_t R;
    struct {
      vuint32_t  :9;
      vuint32_t LPTM:7;                /* Lowest Priority Tx Mailbox */
      vuint32_t  :1;
      vuint32_t VPS:1;                 /* Valid Priority Status */
      vuint32_t IMB:1;                 /* Inactive Mailbox */
      vuint32_t  :13;
    } B;
  } ESR2;

  uint8_t CAN_reserved1[8];
  union {                              /* CRC Register */
    vuint32_t R;
    struct {
      vuint32_t  :9;
      vuint32_t MBCRC:7;               /* CRC Mailbox */
      vuint32_t  :1;
      vuint32_t TXCRC:15;              /* CRC Transmitted */
    } B;
  } CRCR;

  union {                              /* Rx FIFO Global Mask register */
    vuint32_t R;
    struct {
      vuint32_t FGM:32;                /* Rx FIFO Global Mask Bits */
    } B;
  } RXFGMASK;

  union {                              /* Rx FIFO Information Register */
    vuint32_t R;
    struct {
      vuint32_t  :23;
      vuint32_t IDHIT:9;               /* Identifier Acceptance Filter Hit Indicator */
    } B;
  } RXFIR;

  uint8_t CAN_reserved2[48];
  struct {
    union {                            /* Message Buffer 0 CS Register */
      vuint32_t R;
      struct {
        vuint32_t  :4;
        vuint32_t CODE:4;              /* Message Buffer Code */
        vuint32_t  :1;
        vuint32_t SRR:1;               /* Substitute Remote Request. Contains a fixed recessive bit. */
        vuint32_t IDE:1;               /* ID Extended. One/zero for extended/standard format frame. */
        vuint32_t RTR:1;               /* Remote Transmission Request. One/zero for remote/data frame. */
        vuint32_t DLC:4;               /* Length of the data to be stored/transmitted. */
        vuint32_t TIMESTAMP:16;        /* Free-Running Counter Time stamp. This 16-bit field is a copy of the Free-Running Timer, captured for Tx and Rx frames at the time when the beginning of the Identifier field appears on the CAN bus. */
      } B;
    } CS;
    union {                            /* Message Buffer 0 ID Register */
      vuint32_t R;
      struct {
        vuint32_t PRIO:3;              /* Local Priority */
        vuint32_t ID_STD:11;           /* Frame Identifier Standard */
        vuint32_t ID_EXT:18;           /* Frame Identifier Extended */
      } B;
    } ID;
    union {
      vuint8_t B[8];
      vuint16_t H[4];
      vuint32_t W[2];
    } DATA;
  } MB[96];

  uint8_t CAN_reserved3[512];
  union {                              /* Rx Individual Mask Registers */
    vuint32_t R;
    struct {
      vuint32_t MI:32;                 /* Individual Mask Bits */
    } B;
  } RXIMR[96];

  uint8_t CAN_reserved4[512];
  
    union {                              /* CAN FD Control Register */
    vuint32_t R;
    struct {
      vuint32_t FDRATE:1;              /* Bit Rate Switch Enable */
      vuint32_t  :4;
      vuint32_t  :2;
      vuint32_t  :1;
      vuint32_t MBDSR2:2;              /* Message Buffer Data Size for Region 2 */
      vuint32_t  :1;
      vuint32_t MBDSR1:2;              /* Message Buffer Data Size for Region 1 */
      vuint32_t  :1;
      vuint32_t MBDSR0:2;              /* Message Buffer Data Size for Region 0 */
      vuint32_t TDCEN:1;               /* Transceiver Delay Compensation Enable */
      vuint32_t TDCFAIL:1;             /* Transceiver Delay Compensation Fail */
      vuint32_t  :1;
      vuint32_t TDCOFF:5;              /* Transceiver Delay Compensation Offset */
      vuint32_t  :2;
      vuint32_t TDCVAL:6;              /* Transceiver Delay Compensation Value */
    } B;
  } FDCTRL;
  
    union {                              /* CAN FD Bit Timing Register */
    vuint32_t R;
    struct {
      vuint32_t  :2;
      vuint32_t FPRESDIV:10;           /* Fast Prescaler Division Factor */
      vuint32_t  :2;
      vuint32_t FRJW:2;                /* Fast Resync Jump Width */
      vuint32_t  :1;
      vuint32_t FPROPSEG:5;            /* Fast Propagation Segment */
      vuint32_t  :2;
      vuint32_t FPSEG1:3;              /* Fast Phase Segment 1 */
      vuint32_t  :2;
      vuint32_t FPSEG2:3;              /* Fast Phase Segment 2 */
    } B;
  } FDCBT;
  
    union {                              /* CAN FD CRC Register */
    vuint32_t R;
    struct {
      vuint32_t  :1;
      vuint32_t FD_MBCRC:7;            /* CRC Mailbox Number for FD_TXCRC */
      vuint32_t  :3;
      vuint32_t FD_TXCRC:21;           /* Extended Transmitted CRC value */
    } B;
  } FDCRC;  
};

/******************* INTC *********************/

struct INTC_tag {
  union {                              /* INTC Block Configuration Register */
    vuint32_t R;
    struct {
      vuint32_t  :19;
      vuint32_t HVEN3:1;
      vuint32_t  :3;
      vuint32_t HVEN2:1;
      vuint32_t  :3;
      vuint32_t HVEN1:1;
      vuint32_t  :3;
      vuint32_t HVEN0:1;
    } B;
  } BCR;

  union {                              /* INTC Master Protection Register */
    vuint32_t R;
    struct {
      vuint32_t  :26;
      vuint32_t ID:2;
      vuint32_t  :3;
      vuint32_t MPROT:1;
    } B;
  } MPROT;

  uint8_t INTC_reserved0[8];
  union {                              /* INTC Current Priority Register for Processor n */
    vuint32_t R;
    struct {
      vuint32_t  :28;
      vuint32_t PRI:4;
    } B;
  } CPR[3];

  uint8_t INTC_reserved1[4];
  union {                              /* INTC Interrupt Acknowledge Register for Processor n */
    vuint32_t R;
    struct {
      vuint32_t VTBA:20;
      vuint32_t INTVEC:10;
      vuint32_t  :2;
    } B;
  } IACKR[3];

  uint8_t INTC_reserved2[4];
  union {                              /* INTC End Of Interrupt Register for Processor n */
    vuint32_t R;
    struct {
      vuint32_t EOI:32;
    } B;
  } EOIR[3];

  uint8_t INTC_reserved3[4];
  union {                              /* INTC Software Set/Clear Interrupt Register */
    vuint8_t R;
    struct {
      vuint8_t  :6;
      vuint8_t SET:1;
      vuint8_t CLR:1;
    } B;
  } SSCIR[24];

  uint8_t INTC_reserved4[8];
  union {                              /* INTC Priority Select Register */
    vuint16_t R;
    struct {
      vuint16_t PRC_SELN:4;
      vuint16_t  :3;
      vuint16_t SWTN:1;
      vuint16_t  :4;
      vuint16_t PRIN:4;
    } B;
  } PSR[1024];
};

/*******************MC CGM**********************/

struct MC_CGM_tag {
  uint8_t MC_CGM_reserved0[384];
  union {                              /* Clockout 1 Select Register */
    vuint32_t R;
    struct {
      vuint32_t  :4;
      vuint32_t SELCTL:4;              /* CLKOUT1 Source Select */
      vuint32_t  :24;
    } B;
  } CLKOUT1_SC;

  uint8_t MC_CGM_reserved[4];
  
  union {                              /* CLKOUT1_DC Configuration Register */
    vuint32_t R;
    struct {
      vuint32_t DE:1;                  /* CLKOUT1_DC enable */
      vuint32_t  :4;
      vuint32_t DIV:11;                 /* Divider */
      vuint32_t  :16;
    } B;
  } CLKOUT1_DC;

  uint8_t MC_CGM_reserved1[52];
  union {                              /* Auxiliary Clock 5 Select Control Register */
    vuint32_t R;
    struct {
      vuint32_t  :7;
      vuint32_t SELCTL:1;
      vuint32_t  :24;
    } B;
  } AC5_SC;

  union {                              /* Auxiliary Clock 5 Select Status Register */
    vuint32_t R;
    struct {
      vuint32_t  :7;
      vuint32_t SELSTAT:1;
      vuint32_t  :24;
    } B;
  } AC5_SS;

  uint8_t MC_CGM_reserved2[56];
  union {                              /* System Clock Divider 6 Configuration Register */
    vuint32_t R;
    struct {
      vuint32_t DE:1;
      vuint32_t  :12;
      vuint32_t DIV:3;                 /* Divider */
      vuint32_t  :16;
    } B;
  } SC_DC6;

  uint8_t MC_CGM_reserved3[60];
  union {                              /* Auxiliary Clock 7 Select Control Register */
    vuint32_t R;
    struct {
      vuint32_t  :7;
      vuint32_t SELCTL:1;
      vuint32_t  :24;
    } B;
  } AC7_SC;

  union {                              /* Auxiliary Clock 7 Select Status Register */
    vuint32_t R;
    struct {
      vuint32_t  :7;
      vuint32_t SELCTL:1;
      vuint32_t  :24;
    } B;
  } AC7_SS;

  uint8_t MC_CGM_reserved4[56];
  union {                              /* Auxiliary Clock 8 Select Control Register */
    vuint32_t R;
    struct {
      vuint32_t  :7;
      vuint32_t SELCTL:1;
      vuint32_t  :24;
    } B;
  } AC8_SC;

  union {                              /* Auxiliary Clock 8 Select Status Register */
    vuint32_t R;
    struct {
      vuint32_t  :7;
      vuint32_t SELCTL:1;
      vuint32_t  :24;
    } B;
  } AC8_SS;

  uint8_t MC_CGM_reserved5[56];
  union {                              /* Auxiliary Clock 9 Select Control Register */
    vuint32_t R;
    struct {
      vuint32_t  :7;
      vuint32_t SELCTL:1;
      vuint32_t  :24;
    } B;
  } AC9_SC;

  union {                              /* Auxiliary Clock 9 Select Status Register */
    vuint32_t R;
    struct {
      vuint32_t  :7;
      vuint32_t SELCTL:1;
      vuint32_t  :24;
    } B;
  } AC9_SS;

  uint8_t MC_CGM_reserved6[1080];
  union {                              /* PCS Switch Duration Register */
    vuint8_t R;
    struct {
      vuint8_t SDUR:8;
    } B;
  } PCS_SDUR;

  uint8_t MC_CGM_reserved7[3];
  union {                              /* PCS Divider Change Register 1 */
    vuint32_t R;
    struct {
      vuint32_t INIT:16;
      vuint32_t  :8;
      vuint32_t RATE:8;
    } B;
  } PCS_DIVC1;

  union {                              /* PCS Divider End Register 1 */
    vuint32_t R;
    struct {
      vuint32_t  :12;
      vuint32_t DIVE:20;
    } B;
  } PCS_DIVE1;

  union {                              /* PCS Divider Start Register 1 */
    vuint32_t R;
    struct {
      vuint32_t  :12;
      vuint32_t DIVS:20;
    } B;
  } PCS_DIVS1;

  union {                              /* PCS Divider Change Register 2 */
    vuint32_t R;
    struct {
      vuint32_t INIT:16;
      vuint32_t  :8;
      vuint32_t RATE:8;
    } B;
  } PCS_DIVC2;

  union {                              /* PCS Divider End Register 2 */
    vuint32_t R;
    struct {
      vuint32_t  :12;
      vuint32_t DIVE:20;
    } B;
  } PCS_DIVE2;

  union {                              /* PCS Divider Start Register 2 */
    vuint32_t R;
    struct {
      vuint32_t  :12;
      vuint32_t DIVS:20;
    } B;
  } PCS_DIVS2;

  uint8_t MC_CGM_reserved8[176];
  union {                              /* Divider Update Abort Register */
    vuint32_t R;
    struct {
      vuint32_t  :31;
      vuint32_t DIV_UPD_ABRTD:1;
    } B;
  } DIV_UPD_ABRTD;

  union {                              /* System Clock Divider Ratio Change Register */
    vuint32_t R;
    struct {
      vuint32_t  :30;
      vuint32_t HALT_ABORT_DIS:1;
      vuint32_t SYS_DIV_RATIO_CHNG:1;
    } B;
  } SC_DIV_RC;

  union {                              /* Divider Update Type Register */
    vuint32_t R;
    struct {
      vuint32_t SYS_UPD_TYPE:1;        /* System Clock Divider Update Type */
      vuint32_t  :24;
      vuint32_t AUX_UPD_TYPE:1;        /* Auxiliary Clock Divider Update Type */
      vuint32_t  :6;
    } B;
  } DIV_UPD_TYPE;

  union {                              /* Divider Update Trigger Register */
    vuint32_t R;
    struct {
      vuint32_t DIV_UPD_TRIGGER:32;
    } B;
  } DIV_UPD_TRIG;

  union {                              /* Divider Update Status Register */
    vuint32_t R;
    struct {
      vuint32_t SYS_UPD_STAT:1;        /* System Clock Divider Update Status */
      vuint32_t  :24;
      vuint32_t AUX_UPD_STAT:1;        /* Auxiliary Clock Divider Status Type */
      vuint32_t  :6;
    } B;
  } DIV_UPD_STAT;

  uint8_t MC_CGM_reserved9[4];
  union {                              /* System Clock Select Status Register */
    vuint32_t R;
    struct {
      vuint32_t  :4;
      vuint32_t SELSTAT:4;
      vuint32_t  :4;
      vuint32_t SWTRG:3;
      vuint32_t SWIP:1;
      vuint32_t  :16;
    } B;
  } SC_SS;

  union {                              /* System Clock Divider 0 Configuration Register */
    vuint32_t R;
    struct {
      vuint32_t DE:1;
      vuint32_t  :12;
      vuint32_t DIV:3;
      vuint32_t  :16;
    } B;
  } SC_DC0;

  union {                              /* System Clock Divider 1 Configuration Register */
    vuint32_t R;
    struct {
      vuint32_t DE:1;
      vuint32_t  :12;
      vuint32_t DIV:3;
      vuint32_t  :16;
    } B;
  } SC_DC1;

  union {                              /* System Clock Divider 2 Configuration Register */
    vuint32_t R;
    struct {
      vuint32_t DE:1;
      vuint32_t  :11;
      vuint32_t DIV:4;
      vuint32_t  :16;
    } B;
  } SC_DC2;

  union {                              /* System Clock Divider 3 Configuration Register */
    vuint32_t R;
    struct {
      vuint32_t DE:1;
      vuint32_t  :13;
      vuint32_t DIV:2;
      vuint32_t  :16;
    } B;
  } SC_DC3;

  union {                              /* System Clock Divider 4 Configuration Register */
    vuint32_t R;
    struct {
      vuint32_t DE:1;
      vuint32_t  :13;
      vuint32_t DIV:2;
      vuint32_t  :16;
    } B;
  } SC_DC4;

  union {                              /* System Clock Divider 5 Configuration Register */
    vuint32_t R;
    struct {
      vuint32_t DE:1;
      vuint32_t  :12;
      vuint32_t DIV:3;
      vuint32_t  :16;
    } B;
  } SC_DC5;

  uint8_t MC_CGM_reserved10[64];
  union {                              /* Auxiliary Clock 2 Select Control Register */
    vuint32_t R;
    struct {
      vuint32_t  :7;
      vuint32_t SELSTAT:1;
      vuint32_t  :24;
    } B;
  } AC2_SC;

  union {                              /* Auxiliary Clock 2 Select Status Register */
    vuint32_t R;
    struct {
      vuint32_t  :7;
      vuint32_t SELSTAT:1;
      vuint32_t  :24;
    } B;
  } AC2_SS;

  uint8_t MC_CGM_reserved12[24];
  union {                              /* Auxiliary Clock 3 Select Control Register */
    vuint32_t R;
    struct {
      vuint32_t  :7;
      vuint32_t SELCTL:1;
      vuint32_t  :24;
    } B;
  } AC3_SC;

  union {                              /* Auxiliary Clock 3 Select Status Register */
    vuint32_t R;
    struct {
      vuint32_t  :7;
      vuint32_t SELSTAT:1;
      vuint32_t  :24;
    } B;
  } AC3_SS;

  uint8_t MC_CGM_reserved13[24];
  union {                              /* Auxiliary Clock 4 Select Control Register */
    vuint32_t R;
    struct {
      vuint32_t  :7;
      vuint32_t SELCTL:1;
      vuint32_t  :24;
    } B;
  } AC4_SC;

  union {                              /* Auxiliary Clock 4 Select Status Register */
    vuint32_t R;
    struct {
      vuint32_t  :7;
      vuint32_t SELSTAT:1;
      vuint32_t  :24;
    } B;
  } AC4_SS;

  uint8_t MC_CGM_reserved14[56];
  union {                              /* Auxiliary Clock 6 Select Control Register */
    vuint32_t R;
    struct {
      vuint32_t  :4;
      vuint32_t SELCTL:4;
      vuint32_t  :24;
    } B;
  } AC6_SC;

  union {                              /* Auxiliary Clock 6 Select Status Register */
    vuint32_t R;
    struct {
      vuint32_t  :4;
      vuint32_t SELSTAT:4;
      vuint32_t  :24;
    } B;
  } AC6_SS;

  union {                              /* Aux Clock 6 Divider Configuration 0 for CLKOUT_0 */
    vuint32_t R;
    struct {
      vuint32_t DE:1;
      vuint32_t  :10;
      vuint32_t DIV:5;
      vuint32_t  :16;
    } B;
  } AC6_DC0;
};


/*******************MC ME**********************/

struct MC_ME_tag {
  union {                              /* Global Status Register */
    vuint32_t R;
    struct {
      vuint32_t S_CURRENT_MODE:4;
      vuint32_t S_MTRANS:1;
      vuint32_t  :1;
      vuint32_t  :2;
      vuint32_t S_PDO:1;
      vuint32_t  :2;
      vuint32_t S_MVR:1;
      vuint32_t  :2;
      vuint32_t S_FLA:2;
      vuint32_t  :7;
      vuint32_t S_SXOSC:1;             /* 32 KHz external oscillator status */
      vuint32_t S_SIRCON:1;            /* 128 KHz internal RC oscillator status */
      vuint32_t S_PLLON:1;             /* PLL status */
      vuint32_t S_FXOSC:1;             /* 8-40 MHz crystal oscillator status */
      vuint32_t S_FIRCON:1;
      vuint32_t S_SYSCLK:4;
    } B;
  } GS;

  union {                              /* Mode Control Register */
    vuint32_t R;
    struct {
      vuint32_t TARGET_MODE:4;         /* Target chip mode */
      vuint32_t  :12;
      vuint32_t KEY:16;
    } B;
  } MCTL;

  union {                              /* Mode Enable Register */
    vuint32_t R;
    struct {
      vuint32_t  :16;
      vuint32_t RESET_DEST:1;
      vuint32_t  :1;
      vuint32_t STANDBY0:1;            /* STANDBY0 mode enable */
      vuint32_t  :2;
      vuint32_t STOP0:1;
      vuint32_t  :1;
      vuint32_t  :1;
      vuint32_t RUN3:1;
      vuint32_t RUN2:1;
      vuint32_t RUN1:1;
      vuint32_t RUN0:1;
      vuint32_t DRUN:1;
      vuint32_t SAFE:1;
      vuint32_t  :1;
      vuint32_t RESET_FUNC:1;
    } B;
  } ME;

  union {                              /* Interrupt Status Register */
    vuint32_t R;
    struct {
      vuint32_t  :26;
      vuint32_t I_ICONF_CC:1;
      vuint32_t  :1;
      vuint32_t I_ICONF:1;
      vuint32_t I_IMODE:1;
      vuint32_t I_SAFE:1;
      vuint32_t I_MTC:1;
    } B;
  } IS;

  union {                              /* Interrupt Mask Register */
    vuint32_t R;
    struct {
      vuint32_t  :26;
      vuint32_t M_ICONF_CC:1;
      vuint32_t  :1;
      vuint32_t M_ICONF:1;
      vuint32_t M_IMODE:1;
      vuint32_t M_SAFE:1;
      vuint32_t M_MTC:1;
    } B;
  } IM;

  union {                              /* Invalid Mode Transition Status Register */
    vuint32_t R;
    struct {
      vuint32_t  :26;
      vuint32_t S_MRIG:1;
      vuint32_t S_MTI:1;
      vuint32_t S_MRI:1;
      vuint32_t S_DMA:1;
      vuint32_t S_NMA:1;
      vuint32_t S_SEA:1;
    } B;
  } IMTS;

  union {                              /* Debug Mode Transition Status Register */
    vuint32_t R;
    struct {
      vuint32_t PREVIOUS_MODE:4;
      vuint32_t  :4;
      vuint32_t MPH_BUSY:1;
      vuint32_t  :2;
      vuint32_t PMC_PROG:1;
      vuint32_t DBG_MODE:1;
      vuint32_t CCKL_PROG:1;
      vuint32_t PCS_PROG:1;
      vuint32_t SMR:1;
      vuint32_t CDP_PRPH_0_255:1;      /* Clock Disable Process Pending status for Peripherals 0…255 */
      vuint32_t VREG_CSRC_SC:1;
      vuint32_t CSRC_CSRC_SC:1;
      vuint32_t IRC_SC:1;
      vuint32_t SCSRC_SC:1;
      vuint32_t SYSCLK_SW:1;
      vuint32_t  :1;
      vuint32_t FLASH_SC:1;
      vuint32_t  :4;
      vuint32_t CDP_PRPH_96_127:1;
      vuint32_t CDP_PRPH_64_95:1;
      vuint32_t CDP_PRPH_32_63:1;
      vuint32_t CDP_PRPH_0_31:1;
    } B;
  } DMTS;

  uint8_t MC_ME_reserved0[4];
  union {                              /* RESET Mode Configuration Register */
    vuint32_t R;
    struct {
      vuint32_t  :1;
      vuint32_t PWRLVL:3;
      vuint32_t  :4;
      vuint32_t PDO:1;
      vuint32_t  :2;
      vuint32_t MVRON:1;
      vuint32_t  :2;
      vuint32_t FLAON:2;
      vuint32_t  :7;
      vuint32_t SXOSCON:1;             /* 32Khz external oscillator control */
      vuint32_t SIRCON:1;
      vuint32_t PLLON:1;
      vuint32_t FXOSCON:1;
      vuint32_t FIRCON:1;
      vuint32_t SYSCLK:4;
    } B;
  } RESET_MC;

  uint8_t MC_ME_reserved1[4];
  union {                              /* SAFE Mode Configuration Register */
    vuint32_t R;
    struct {
      vuint32_t  :1;
      vuint32_t PWRLVL:3;
      vuint32_t  :4;
      vuint32_t PDO:1;
      vuint32_t  :2;
      vuint32_t MVRON:1;
      vuint32_t  :2;
      vuint32_t FLAON:2;
      vuint32_t  :7;
      vuint32_t SXOSCON:1;             /* 32Khz external oscillator control */
      vuint32_t SIRCON:1;
      vuint32_t PLLON:1;
      vuint32_t FXOSCON:1;
      vuint32_t FIRCON:1;
      vuint32_t SYSCLK:4;
    } B;
  } SAFE_MC;

  union {                              /* DRUN Mode Configuration Register */
    vuint32_t R;
    struct {
      vuint32_t  :1;
      vuint32_t PWRLVL:3;
      vuint32_t  :4;
      vuint32_t PDO:1;
      vuint32_t  :2;
      vuint32_t MVRON:1;
      vuint32_t  :2;
      vuint32_t FLAON:2;
      vuint32_t  :7;
      vuint32_t SXOSCON:1;             /* 32Khz external oscillator control */
      vuint32_t SIRCON:1;
      vuint32_t PLLON:1;
      vuint32_t FXOSCON:1;
      vuint32_t FIRCON:1;
      vuint32_t SYSCLK:4;
    } B;
  } DRUN_MC;

  union {                              /* RUN0 Mode Configuration Register */
    vuint32_t R;
    struct {
      vuint32_t  :1;
      vuint32_t PWRLVL:3;
      vuint32_t  :4;
      vuint32_t PDO:1;
      vuint32_t  :2;
      vuint32_t MVRON:1;
      vuint32_t  :2;
      vuint32_t FLAON:2;
      vuint32_t  :7;
      vuint32_t SXOSCON:1;             /* 32 KHz external oscillator control */
      vuint32_t SIRCON:1;
      vuint32_t PLLON:1;
      vuint32_t FXOSCON:1;
      vuint32_t FIRCON:1;
      vuint32_t SYSCLK:4;
    } B;
  } RUN_MC[4];

  uint8_t MC_ME_reserved2[8];
  union {                              /* STOP0 Mode Configuration Register */
    vuint32_t R;
    struct {
      vuint32_t  :1;
      vuint32_t PWRLVL:3;
      vuint32_t  :4;
      vuint32_t PDO:1;
      vuint32_t  :2;
      vuint32_t MVRON:1;
      vuint32_t  :2;
      vuint32_t FLAON:2;
      vuint32_t  :7;
      vuint32_t SXOSCON:1;             /* 32 KHz external oscillator control */
      vuint32_t SIRCON:1;
      vuint32_t PLLON:1;
      vuint32_t FXOSCON:1;
      vuint32_t FIRCON:1;
      vuint32_t SYSCLK:4;
    } B;
  } STOP_MC;

  uint8_t MC_ME_reserved3[8];
  union {                              /* STANDBY0 Mode Configuration Register */
    vuint32_t R;
    struct {
      vuint32_t  :1;
      vuint32_t PWRLVL:3;
      vuint32_t  :4;
      vuint32_t PDO:1;
      vuint32_t  :2;
      vuint32_t MVRON:1;
      vuint32_t  :2;
      vuint32_t FLAON:2;
      vuint32_t  :7;
      vuint32_t SXOSCON:1;             /* 32 KHz external oscillator control */
      vuint32_t SIRCON:1;
      vuint32_t PLLON:1;
      vuint32_t FXOSCON:1;
      vuint32_t FIRCON:1;
      vuint32_t SYSCLK:4;
    } B;
  } STANDBY_MC;

  uint8_t MC_ME_reserved4[8];
  union {                              /* Peripheral Status Register 0 */
    vuint32_t R;
    struct {
      vuint32_t S_IIC_1:1;
      vuint32_t S_IIC_0:1;
      vuint32_t  :1;
      vuint32_t S_FlexRay:1;           /* Peripheral status - These bits specify the current status of each peripheral which is controlled by the MC_ME. */
      vuint32_t  :2;
      vuint32_t S_ADC_1:1;             /* Peripheral status - These bits specify the current status of each peripheral which is controlled by the MC_ME. 0: Peripheral is frozen 1: Peripheral is active. */
      vuint32_t S_ADC_0:1;             /* Peripheral status - These bits specify the current status of each peripheral which is controlled by the MC_ME. 0: Peripheral is frozen 1: Peripheral is active */
      vuint32_t  :1;
      vuint32_t S_ACMP_2:1;            /* Peripheral status - These bits specify the current status of each peripheral which is controlled by the MC_ME. 0: Peripheral is frozen 1: Peripheral is active */
      vuint32_t S_ACMP_1:1;            /* Peripheral status - These bits specify the current status of each peripheral which is controlled by the MC_ME. 0: Peripheral is frozen 1: Peripheral is active */
      vuint32_t S_ACMP_0:1;            /* Peripheral status - These bits specify the current status of each peripheral which is controlled by the MC_ME. 0: Peripheral is frozen 1: Peripheral is active */
      vuint32_t  :4;
      vuint32_t S_ENET:1;              /* Peripheral status - These bits specify the current status of each peripheral which is controlled by the MC_ME. 0: Peripheral is frozen 1: Peripheral is active */
      vuint32_t  :2;
      vuint32_t S_SAI_2:1;             /* Peripheral status - These bits specify the current status of each peripheral which is controlled by the MC_ME. 0: Peripheral is frozen 1: Peripheral is active */
      vuint32_t S_SAI_1:1;             /* Peripheral status - These bits specify the current status of each peripheral which is controlled by the MC_ME. 0: Peripheral is frozen 1: Peripheral is active. */
      vuint32_t S_SAI_0:1;             /* Peripheral status - These bits specify the current status of each peripheral which is controlled by the MC_ME. 0: Peripheral is frozen 1: Peripheral is active */
      vuint32_t  :2;
      vuint32_t S_SDHC:1;              /* Peripheral status - These bits specify the current status of each peripheral which is controlled by the MC_ME. 0: Peripheral is frozen 1: Peripheral is active */
      vuint32_t S_MLB:1;               /* Peripheral status - These bits specify the current status of each peripheral which is controlled by the MC_ME. 0: Peripheral is frozen 1: Peripheral is active */
      vuint32_t S_USB_SPH:1;           /* Peripheral status - These bits specify the current status of each peripheral which is controlled by the MC_ME. 0: Peripheral is frozen 1: Peripheral is active */
      vuint32_t S_USBOTG:1;
      vuint32_t S_eMIOS_2:1;           /* Peripheral status - These bits specify the current status of each peripheral which is controlled by the MC_ME. */
      vuint32_t S_eMIOS_1:1;           /* Peripheral status - These bits specify the current status of each peripheral which is controlled by the MC_ME. */
      vuint32_t S_eMIOS_0:1;           /* Peripheral status - These bits specify the current status of each peripheral which is controlled by the MC_ME. */
      vuint32_t S_BCTU:1;              /* Peripheral status - These bits specify the current status of each peripheral which is controlled by the MC_ME. 0: Peripheral is frozen 1: Peripheral is active */
    } B;
  } PS0;

  union {                              /* Peripheral Status Register 1 */
    vuint32_t R;
    struct {
      vuint32_t S_LIN:14;              /* Peripheral status - These bits specify the current status of each peripheral which is controlled by the MC_ME. 0: Peripheral is frozen 1: Peripheral is active */
      vuint32_t  :6;
      vuint32_t S_DSPI:4;              /* Peripheral status - These bits specify the current status of each peripheral which is controlled by the MC_ME. 0: Peripheral is frozen 1: Peripheral is active */
      vuint32_t  :6;
      vuint32_t S_IIC:2;               /* Peripheral status - These bits specify the current status of each peripheral which is controlled by the MC_ME. 0: Peripheral is frozen 1: Peripheral is active */
    } B;
  } PS1;

  union {                              /* Peripheral Status Register 2 */
    vuint32_t R;
    struct {
      vuint32_t  :1;
      vuint32_t  :1;
      vuint32_t S_WKPU:1;
      vuint32_t S_LPU_CTL:1;
      vuint32_t S_PIT_RTI_0:1;
      vuint32_t S_DMAMUX:1;            /* Peripheral status - These bits specify the current status of each peripheral which is controlled by the MC_ME. */
      vuint32_t  :5;
      vuint32_t S_CRC:1;
      vuint32_t S_MEMU_0:1;
      vuint32_t S_JDC:1;
      vuint32_t S_TDM:1;
      vuint32_t  :1;
      vuint32_t  :2;
      vuint32_t S_FLEXCAN:8;
      vuint32_t  :2;
      vuint32_t S_LIN:4;
    } B;
  } PS2;

  union {                              /* Peripheral Status Register 3 */
    vuint32_t R;
    struct {
      vuint32_t  :22;
      vuint32_t S_MEMU_1:1;
      vuint32_t  :1;
      vuint32_t  :1;
      vuint32_t S_RTC_API:1;
      vuint32_t S_SPI:6;
    } B;
  } PS3;

  uint8_t MC_ME_reserved5[16];
  union {                              /* Run Peripheral Configuration Register */
    vuint32_t R;
    struct {
      vuint32_t  :24;
      vuint32_t RUN3:1;
      vuint32_t RUN2:1;
      vuint32_t RUN1:1;
      vuint32_t RUN0:1;
      vuint32_t DRUN:1;
      vuint32_t SAFE:1;
      vuint32_t  :1;
      vuint32_t RESET:1;
    } B;
  } RUN_PC[8];

  union {                              /* Low-Power Peripheral Configuration Register */
    vuint32_t R;
    struct {
      vuint32_t  :18;
      vuint32_t STANDBY0:1;            /* Peripheral control during STANDBY0 */
      vuint32_t  :2;
      vuint32_t STOP0:1;
      vuint32_t  :1;
      vuint32_t  :1;
      vuint32_t  :8;
    } B;
  } LP_PC[8];

    /*  There are only some PCTL implemented         */
    /*  In order to make the PCTL easily addressable, these are defined     */
    /*  as an array (ie ME.PCTL[x].R). Following are available: 0-7, 10-12, 15, 20-25, */
    /*  28, 30-33, 40-43, 50-67, 70-77, 80-84, 90-91, 93-94, 96-102, 104    */

  union {                              /* BCTU Peripheral Control Register */
    vuint8_t R;
    struct {
      vuint8_t  :1;
      vuint8_t DBG_F:1;
      vuint8_t LP_CFG:3;
      vuint8_t RUN_CFG:3;
    } B;
  } PCTL[104];

  uint8_t MC_ME_reserved6[152];
  union {                              /* Core Status Register */
    vuint32_t R;
    struct {
      vuint32_t  :28;
      vuint32_t S_CORE3:1;             /* Core3 Status */
      vuint32_t S_CORE2:1;             /* Core2 Status */
      vuint32_t S_CORE1:1;
      vuint32_t  :1;
    } B;
  } CS;

  union {
    vuint16_t R;
    struct {
      vuint16_t  :1;
      vuint16_t STANDBY0:2;
      vuint16_t  :2;
      vuint16_t STOP0:1;
      vuint16_t  :1;
      vuint16_t  :1;
      vuint16_t RUN3:1;
      vuint16_t RUN2:1;
      vuint16_t RUN1:1;
      vuint16_t RUN0:1;
      vuint16_t DRUN:1;
      vuint16_t SAFE:1;
      vuint16_t  :1;
      vuint16_t RESET:1;
    } B;
  } CCTL[4];

  uint8_t MC_ME_reserved7[20];
  union {
    vuint32_t R;
    struct {
      vuint32_t ADDR:30;
      vuint32_t  :1;
      vuint32_t RMC:1;                 /* Reset on Mode Change */
    } B;
  } CADDR[4];
};

/******************* PFLASH **********************/

struct PFLASH_tag {
  union {                              /* Platform Flash Configuration Register 1 */
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
      vuint32_t  :1;
      vuint32_t P0_DPFEN:1;
      vuint32_t  :1;
      vuint32_t P0_IPFEN:1;
      vuint32_t  :1;
      vuint32_t P0_PFLIM:2;
      vuint32_t P0_BFEN:1;
    } B;
  } PFCR1;

  union {                              /* Platform Flash Configuration Register 2 */
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
      vuint32_t  :9;
      vuint32_t P1_DPFEN:1;
      vuint32_t  :1;
      vuint32_t P1_IPFEN:1;
      vuint32_t  :1;
      vuint32_t P1_PFLIM:2;
      vuint32_t P1_BFEN:1;
    } B;
  } PFCR2;

  union {                              /* Platform Flash Configuration Register 3 */
    vuint32_t R;
    struct {
      vuint32_t P0_WCFG:2;
      vuint32_t P1_WCFG:2;
      vuint32_t P2_WCFG:2;
      vuint32_t  :5;
      vuint32_t  :1;
      vuint32_t  :3;
      vuint32_t BAF_DIS:1;
      vuint32_t ARBM:4;                /* Arbitration Mode. This 4-bit field controls the arbitration of concurrent flash access requests from the three AHB ports of the flash memory controller. In both fixed priority or round-robin modes, write requests are prioritized higher than read requests, and read requests are prioritized higher than speculative prefetch requests whenever multiple ports issue concurrent requests. This field is initialized by hardware reset. Specifying a reserved value in this field causes it to default to round-robin arbitration. */
      vuint32_t  :11;
      vuint32_t  :1;
    } B;
  } PFCR3;

  union {                              /* Platform Flash Access Protection Register */
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
  } PFAPR;

  union {                              /* Platform Flash Remap Control Register */
    vuint32_t R;
    struct {
      vuint32_t  :23;
      vuint32_t SAFE_CAL:1;
      vuint32_t  :3;
      vuint32_t IRMEN:1;
      vuint32_t  :3;
      vuint32_t GRMEN:1;
    } B;
  } PFCRCR;

  union {                              /* Platform Flash Remap Descriptor Enable Register */
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
      vuint32_t CRD16EN:1;
      vuint32_t CRD17EN:1;
      vuint32_t CRD18EN:1;
      vuint32_t CRD19EN:1;
      vuint32_t CRD20EN:1;
      vuint32_t CRD21EN:1;
      vuint32_t CRD22EN:1;
      vuint32_t CRD23EN:1;
      vuint32_t CRD24EN:1;
      vuint32_t CRD25EN:1;
      vuint32_t CRD26EN:1;
      vuint32_t CRD27EN:1;
      vuint32_t CRD28EN:1;
      vuint32_t CRD29EN:1;
      vuint32_t CRD30EN:1;
      vuint32_t CRD31EN:1;
    } B;
  } PFCRDE;

  union {                              /* Platform Flash Configuration Register 4 */
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
      vuint32_t  :9;
      vuint32_t P2_DPFEN:1;
      vuint32_t  :1;
      vuint32_t P2_IPFEN:1;
      vuint32_t  :1;
      vuint32_t P2_PFLIM:2;
      vuint32_t P2_BFEN:1;
    } B;
  } PFCR4;

  uint8_t PFLASH_reserved0[228];
  struct {
    union {                            /* Platform Flash Calibration Region Descriptor n Word0 */
      vuint32_t R;
      struct {
        vuint32_t LSTARTADDR:32;
      } B;
    } Word0;
    union {                            /* Platform Flash Calibration Region Descriptor n Word1 */
      vuint32_t R;
      struct {
        vuint32_t PSTARTADDR:32;
      } B;
    } Word1;
    union {                            /* Platform Flash Calibration Region Descriptor n Word2 */
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
        vuint32_t  :11;
        vuint32_t CRDSize:5;
      } B;
    } Word2;
    uint8_t PFCRD_reserved0[4];
  } PFCRD[8];
};

/******************* PLLDIG **********************/

struct PLLDIG_tag {

  uint8_t PLLDIG_reserved0[24];
  union {                              /* PLL Calibration Register 3 */
    vuint32_t R;
    struct {
      vuint32_t  :2;
      vuint32_t MFDEN:16;              /* Denominator fo fractional loop division factor. */
      vuint32_t  :14;
    } B;
  } PLLCAL3;
  uint8_t PLLDIG_reserved1[4];
  
  union {                              /* PLLDIG PLL Control Register */
    vuint32_t R;
    struct {
      vuint32_t  :21;
      vuint32_t  :1;
      vuint32_t  :2;
      vuint32_t EXPDIE:1;              /* External Power Down Cycle Complete indication interrupt enable. */
      vuint32_t  :1;
      vuint32_t  :1;
      vuint32_t  :1;
      vuint32_t LOLIE:1;               /* Loss-of-lock interrupt enable. */
      vuint32_t LOLRE:1;               /* Loss-of-lock reset enable. */
      vuint32_t  :1;
      vuint32_t  :1;
    } B;
  } PLLCR;

  union {                              /* PLLDIG PLL Status Register */
    vuint32_t R;
    struct {
      vuint32_t  :22;
      vuint32_t ENPHI1:1;              /* PLL PHI1 Output Enable */
      vuint32_t ENPHI:1;               /* PLL PHI Output Enable */
      vuint32_t EXTPDF:1;
      vuint32_t  :1;
      vuint32_t  :1;
      vuint32_t  :1;
      vuint32_t LOLF:1;                /* Loss-of-lock flag. */
      vuint32_t LOCK:1;
      vuint32_t  :1;
      vuint32_t  :1;
    } B;
  } PLLSR;

  union {                              /* PLLDIG PLL Divider Register */
    vuint32_t R;
    struct {
      vuint32_t  :1;
      vuint32_t RFDPHI1:6;             /* PHI1 reduced frequency divider. */
      vuint32_t  :3;
      vuint32_t RFDPHI:6;              /* PHI reduced frequency divider. */
      vuint32_t  :1;
      vuint32_t PREDIV:3;              /* Input clock predivider. */
      vuint32_t  :1;
      vuint32_t  :3;
      vuint32_t MFD:8;                 /* Loop multiplication factor divider. */
    } B;
  } PLLDV;

  union {                              /* PLLDIG PLL Frequency Modulation Register */
    vuint32_t R;
    struct {
      vuint32_t  :1;
      vuint32_t SSCGBYP:1;             /* Modulation enable. */
      vuint32_t MODSEL:1;              /* Modulation selection. */
      vuint32_t  :3;
      vuint32_t MODPRD:10;             /* Modulation period. */
      vuint32_t  :5;
      vuint32_t INCSTP:11;             /* Increment step. */
    } B;
  } PLLFM;

  union {                              /* PLLDIG PLL Fractional Divide Register */
    vuint32_t R;
    struct {
      vuint32_t  :1;
      vuint32_t SMDEN:1;               /* Sigma Delta Modulation Enable */
      vuint32_t SDM2:1;                /* Second Order Sigma Delta Modulation Select */
      vuint32_t SDM3:1;                /* Third Order Sigma Delta Modulation Select */
      vuint32_t  :6;
      vuint32_t DTHRCTL:4;             /* Dither Control. */
      vuint32_t DTHDIS:2;              /* Dither Disable. */
      vuint32_t  :1;
      vuint32_t MFN:15;
    } B;
  } PLLFD;
};


/******************* PRAMC **********************/

struct PRAMC_tag {
  union {                              /* Platform RAM Configuration Register 1 */
    vuint32_t R;
    struct {
      vuint32_t  :24;
      vuint32_t  :2;
      vuint32_t  :5;
      vuint32_t FT_DIS:1;              /* Flow through disabled. */
    } B;
  } PRCR1;
};

/******************* SIUL2 **********************/

struct SIUL2_tag {
  uint8_t SIUL2_reserved0[4];
  union {                              /* SIUL2 MCU ID Register #1 */
    vuint32_t R;
    struct {
      vuint32_t PARTNUM:16;            /* MCU Part Number */
      vuint32_t  :1;
      vuint32_t PKG:5;                 /* Package Settings */
      vuint32_t  :2;
      vuint32_t MAJOR_MASK:4;          /* Major Mask Revision */
      vuint32_t MINOR_MASK:4;          /* Minor Mask Revision */
    } B;
  } MIDR1;

  union {                              /* SIUL2 MCU ID Register #2 */
    vuint32_t R;
    struct {
      vuint32_t  :1;
      vuint32_t FLASH_SIZE_1:4;        /* Coarse granularity for flash memory size */
      vuint32_t FLASH_SIZE_2:4;        /* Fine granularity for flash memory size */
      vuint32_t  :7;
      vuint32_t PARTNUM:8;             /* ASCII character in MCU Part Number */
      vuint32_t  :8;
    } B;
  } MIDR2;

  uint8_t SIUL2_reserved1[4];
  union {                              /* SIUL2 Interrupt Status Flag Register0 */
    vuint32_t R;
    struct {
      vuint32_t EIF31:1;               /* External Interrupt Status Flag x */
      vuint32_t EIF30:1;               /* External Interrupt Status Flag x */
      vuint32_t EIF29:1;               /* External Interrupt Status Flag x */
      vuint32_t EIF28:1;               /* External Interrupt Status Flag x */
      vuint32_t EIF27:1;               /* External Interrupt Status Flag x */
      vuint32_t EIF26:1;               /* External Interrupt Status Flag x */
      vuint32_t EIF25:1;               /* External Interrupt Status Flag x */
      vuint32_t EIF24:1;               /* External Interrupt Status Flag x */
      vuint32_t EIF23:1;               /* External Interrupt Status Flag x */
      vuint32_t EIF22:1;               /* External Interrupt Status Flag x */
      vuint32_t EIF21:1;               /* External Interrupt Status Flag x */
      vuint32_t EIF20:1;               /* External Interrupt Status Flag x */
      vuint32_t EIF19:1;               /* External Interrupt Status Flag x */
      vuint32_t EIF18:1;               /* External Interrupt Status Flag x */
      vuint32_t EIF17:1;               /* External Interrupt Status Flag x */
      vuint32_t EIF16:1;               /* External Interrupt Status Flag x */
      vuint32_t EIF15:1;               /* External Interrupt Status Flag x */
      vuint32_t EIF14:1;               /* External Interrupt Status Flag x */
      vuint32_t EIF13:1;               /* External Interrupt Status Flag x */
      vuint32_t EIF12:1;               /* External Interrupt Status Flag x */
      vuint32_t EIF11:1;               /* External Interrupt Status Flag x */
      vuint32_t EIF10:1;               /* External Interrupt Status Flag x */
      vuint32_t EIF9:1;                /* External Interrupt Status Flag x */
      vuint32_t EIF8:1;                /* External Interrupt Status Flag x */
      vuint32_t EIF7:1;                /* External Interrupt Status Flag x */
      vuint32_t EIF6:1;                /* External Interrupt Status Flag x */
      vuint32_t EIF5:1;                /* External Interrupt Status Flag x */
      vuint32_t EIF4:1;                /* External Interrupt Status Flag x */
      vuint32_t EIF3:1;                /* External Interrupt Status Flag x */
      vuint32_t EIF2:1;                /* External Interrupt Status Flag x */
      vuint32_t EIF1:1;                /* External Interrupt Status Flag x */
      vuint32_t EIF0:1;                /* External Interrupt Status Flag x */
    } B;
  } ISR0;

  uint8_t SIUL2_reserved2[4];
  union {                              /* SIUL2 Interrupt Request Enable Register0 */
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
  } IRER0;

  uint8_t SIUL2_reserved3[4];
  union {                              /* SIUL2 Interrupt Request Select Register0 */
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
  } IRSR0;

  uint8_t SIUL2_reserved4[4];
  union {                              /* SIUL2 Interrupt Rising-Edge Event Enable Register 0 */
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
  } IREER0;

  uint8_t SIUL2_reserved5[4];
  union {                              /* SIUL2 Interrupt Falling-Edge Event Enable Register 0 */
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
  } IFEER0;

  uint8_t SIUL2_reserved6[4];
  union {                              /* SIUL2 Interrupt Filter Enable Register 0 */
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
  } IFER0;

  uint8_t SIUL2_reserved7[4];
  union {                              /* SIUL2 Interrupt Filter Maximum Counter Register */
    vuint32_t R;
    struct {
      vuint32_t  :28;
      vuint32_t MAXCNT:4;              /* Maximum Interrupt Filter Counter setting */
    } B;
  } IFMCR[32];

  union {                              /* SIUL2 Interrupt Filter Clock Prescaler Register */
    vuint32_t R;
    struct {
      vuint32_t  :28;
      vuint32_t IFCP:4;                /* Interrupt Filter Clock Prescaler setting */
    } B;
  } IFCPR;

  uint8_t SIUL2_reserved8[380];
  union {                              /* SIUL2 Multiplexed Signal Configuration Register */
    vuint32_t R;
    struct {
      vuint32_t  :2;
      vuint32_t SRC:2;                 /* Slew Rate Control */
      vuint32_t  :2;
      vuint32_t OBE:1;                 /* GPIO Output Buffer Enable */
      vuint32_t ODE:1;                 /* Open Drain Enable */
      vuint32_t SMC:1;                 /* Safe Mode Control */
      vuint32_t APC:1;                 /* Analog Pad Control */
      vuint32_t  :1;
      vuint32_t TTL:1;                 /* TTL/Automotive mode selection */
      vuint32_t IBE:1;                 /* Input Buffer Enable */
      vuint32_t HYS:1;                 /* Input Hysteresis */
      vuint32_t PUS:1;                 /* Pull Select */
      vuint32_t PUE:1;                 /* Pull Enable */
      vuint32_t  :8;
      vuint32_t  :4;
      vuint32_t SSS:4;                 /* Source Signal Select */
    } B;
  } MSCR[264];

  uint8_t SIUL2_reserved9[992];
  union {                              /* SIUL2 Input Multiplexed Signal Configuration Register */
    vuint32_t R;
    struct {
      vuint32_t  :24;
      vuint32_t  :4;
      vuint32_t SSS:4;                 /* Source Signal Select */
    } B;
  } IMCR[512];

  uint8_t SIUL2_reserved10[192];
  union {                              /* SIUL2 GPIO Pad Data Output Register */
    vuint8_t R;
    struct {
      vuint8_t  :7;
      vuint8_t PDO_4n:1;               /* Pad Data Out */
    } B;
  } GPDO[264];

  uint8_t SIUL2_reserved11[248];
  union {                              /* SIUL2 GPIO Pad Data Input Register */
    vuint8_t R;
    struct {
      vuint8_t  :7;
      vuint8_t PDI_4n:1;               /* Pad Data In */
    } B;
  } GPDI[264];

  uint8_t SIUL2_reserved12[248];
  union {                              /* SIUL2 Parallel GPIO Pad Data Out Register */
    vuint16_t R;
    struct {
      vuint16_t PPDO:16;               /* Parallel Pad Data Out */
    } B;
  } PGPDO[32];

  union {                              /* SIUL2 Parallel GPIO Pad Data In Register */
    vuint16_t R;
    struct {
      vuint16_t PPDI:16;               /* Parallel Pad Data In */
    } B;
  } PGPDI[32];

  union {                              /* SIUL2 Masked Parallel GPIO Pad Data Out Register */
    vuint32_t R;
    struct {
      vuint32_t MASK:16;               /* Mask Field */
      vuint32_t MPPDO:16;              /* Masked Parallel Pad Data Out */
    } B;
  } MPGPDO[32];
};

/*****Struct locations ****/

#define SRAM0_START 0x40000000UL;
#define CAN_0 (*(volatile struct CAN_0_tag *) 0xFFEC0000UL)
#define CAN_1 (*(volatile struct CAN_1_tag *) 0xFBEC0000UL)
#define INTC (*(volatile struct INTC_tag *) 0xFC040000UL)
#define MC_CGM (*(volatile struct MC_CGM_tag *) 0xFFFB0000UL)
#define MC_ME (*(volatile struct MC_ME_tag *) 0xFFFB8000UL)
#define PFLASH (*(volatile struct PFLASH_tag *) 0xFC030000UL)
#define PLLDIG (*(volatile struct PLLDIG_tag *) 0xFFFB0080UL)
#define PRAMC_0 (*(volatile struct PRAMC_tag *) 0xFC020000UL)
#define PRAMC_1 (*(volatile struct PRAMC_tag *) 0xFC024000UL)
#define PRAMC_2 (*(volatile struct PRAMC_tag *) 0xFC02C000UL)
#define SIUL2 (*(volatile struct SIUL2_tag *) 0xFFFC0000UL)

#ifdef __MWERKS__
#pragma pop
#endif
#ifdef __ghs__
#pragma ghs endnowarning
#endif
#ifdef  __cplusplus
}
#endif
#endif /* CALYPSO_H */