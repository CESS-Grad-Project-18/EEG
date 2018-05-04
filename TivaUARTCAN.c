#define CR 0x0D /* Carriage return */
#define LF 0x0A /* Line Feed */
#define BS 0x08 /* Backspace */

/* CAN 0 */
#define CAN0_CTL_R              (*((volatile unsigned long *) 0x40040000))
#define CAN0_STS_R              (*((volatile unsigned long *) 0x40040004))
#define CAN0_ERR_R              (*((volatile unsigned long *) 0x40040008))
#define CAN0_BIT_R              (*((volatile unsigned long *) 0x4004000C))
#define CAN0_INT_R              (*((volatile unsigned long *) 0x40040010))
#define CAN0_TST_R              (*((volatile unsigned long *) 0x40040014))
#define CAN0_BRPE_R             (*((volatile unsigned long *) 0x40040018))
#define CAN0_IF1CRQ_R           (*((volatile unsigned long *) 0x40040020))
#define CAN0_IF1CMSK_R          (*((volatile unsigned long *) 0x40040024))
#define CAN0_IF1MSK1_R          (*((volatile unsigned long *) 0x40040028))
#define CAN0_IF1MSK2_R          (*((volatile unsigned long *) 0x4004002C))
#define CAN0_IF1ARB1_R          (*((volatile unsigned long *) 0x40040030))
#define CAN0_IF1ARB2_R          (*((volatile unsigned long *) 0x40040034))
#define CAN0_IF1MCTL_R          (*((volatile unsigned long *) 0x40040038))
#define CAN0_IF1DA1_R           (*((volatile unsigned long *) 0x4004003C))
#define CAN0_IF1DA2_R           (*((volatile unsigned long *) 0x40040040))
#define CAN0_IF1DB1_R           (*((volatile unsigned long *) 0x40040044))
#define CAN0_IF1DB2_R           (*((volatile unsigned long *) 0x40040048))
#define CAN0_IF2CRQ_R           (*((volatile unsigned long *) 0x40040080))
#define CAN0_IF2CMSK_R          (*((volatile unsigned long *) 0x40040084))
#define CAN0_IF2MSK1_R          (*((volatile unsigned long *) 0x40040088))
#define CAN0_IF2MSK2_R          (*((volatile unsigned long *) 0x4004008C))
#define CAN0_IF2ARB1_R          (*((volatile unsigned long *) 0x40040090))
#define CAN0_IF2ARB2_R          (*((volatile unsigned long *) 0x40040094))
#define CAN0_IF2MCTL_R          (*((volatile unsigned long *) 0x40040098))
#define CAN0_IF2DA1_R           (*((volatile unsigned long *) 0x4004009C))
#define CAN0_IF2DA2_R           (*((volatile unsigned long *) 0x400400A0))
#define CAN0_IF2DB1_R           (*((volatile unsigned long *) 0x400400A4))
#define CAN0_IF2DB2_R           (*((volatile unsigned long *) 0x400400A8))
#define CAN0_TXRQ1_R            (*((volatile unsigned long *) 0x40040100))
#define CAN0_TXRQ2_R            (*((volatile unsigned long *) 0x40040104))
#define CAN0_NWDA1_R            (*((volatile unsigned long *) 0x40040120))
#define CAN0_NWDA2_R            (*((volatile unsigned long *) 0x40040124))
#define CAN0_MSG1INT_R          (*((volatile unsigned long *) 0x40040140))
#define CAN0_MSG2INT_R          (*((volatile unsigned long *) 0x40040144))
#define CAN0_MSG1VAL_R          (*((volatile unsigned long *) 0x40040160))
#define CAN0_MSG2VAL_R          (*((volatile unsigned long *) 0x40040164))

/* Run Mode Clock Gating Control (UART) */
#define SYSCTL_RCGCUART_R   (*((volatile unsigned long *) 0x400FE618))

#define SYSCTL_RCGC0_R          (*((volatile unsigned long *)0x400FE100))

/* Run Mode Clock Gating Control Register 2 (GPIO) */
#define SYSCTL_R_RCGC2_R        (*((volatile unsigned long *) 0x400FE108))

#define SYSCTL_RCGCGPIO_R       (*((volatile unsigned long *) 0x400FE608))

/* UART0 */
#define UART0_CTL_R             (*((volatile unsigned long *) 0x4000C030))
#define UART0_IBRD_R            (*((volatile unsigned long *) 0x4000C024))
#define UART0_FBRD_R            (*((volatile unsigned long *) 0x4000C028))
#define UART0_LCRH_R            (*((volatile unsigned long *) 0x4000C02C))
#define UART0_FR_R              (*((volatile unsigned long *) 0x4000C018))
#define UART0_DR_R              (*((volatile unsigned long *) 0x4000C000))
#define UART0_CC_R              (*((volatile unsigned long *) 0x4000CFC8))

/* UART5 */
#define UART5_CTL_R                 (*((volatile unsigned long *) 0x40011030))
#define UART5_IBRD_R                (*((volatile unsigned long *) 0x40011024))
#define UART5_FBRD_R                (*((volatile unsigned long *) 0x40011028))
#define UART5_LCRH_R                (*((volatile unsigned long *) 0x4001102C))
#define UART5_FR_R                  (*((volatile unsigned long *) 0x40011018))
#define UART5_DR_R                  (*((volatile unsigned long *) 0x40011000))

/* UART RX/TX Flags */
#define UART_FR_RXFE                0x00000010
#define UART_FR_TXFF                0x00000020

/* GPIO Port E */
#define GPIO_PORTE_AMSEL_R  (*((volatile unsigned long *)0x40024528))
#define GPIO_PORTE_PCTL_R   (*((volatile unsigned long *)0x4002452C))
#define GPIO_PORTE_AFSEL_R  (*((volatile unsigned long *)0x40024420))
#define GPIO_PORTE_DEN_R        (*((volatile unsigned long *)0x4002451C))

/* GPIO Port A */
#define GPIO_PORTA_AMSEL_R      (*((volatile unsigned long *)0x40004528))
#define GPIO_PORTA_PCTL_R       (*((volatile unsigned long *)0x4000452C))
#define GPIO_PORTA_AFSEL_R      (*((volatile unsigned long *)0x40004420))
#define GPIO_PORTA_DEN_R        (*((volatile unsigned long *)0x4000451C))

/* GPIO Port B */
#define GPIO_PORTB_DIR_R        (*((volatile unsigned long *)0x40005400))
#define GPIO_PORTB_AFSEL_R      (*((volatile unsigned long *)0x40005420))
#define GPIO_PORTB_DEN_R        (*((volatile unsigned long *)0x4000551C))
#define GPIO_PORTB_CR_R         (*((volatile unsigned long *)0x40005524))
#define GPIO_PORTB_AMSEL_R      (*((volatile unsigned long *)0x40005528))
#define GPIO_PORTB_PCTL_R       (*((volatile unsigned long *)0x4000552C))

#define STCTL_R             (*((volatile unsigned long *)0xE000E010))
#define STRELOAD_R      (*((volatile unsigned long *)0xE000E014))
#define STCURRENT_R     (*((volatile unsigned long *)0xE000E018))
#define STCTL_COUNT     0x00010000


#define SYSCTL_RIS_R            (*((volatile unsigned long *)0x400FE050))
#define SYSCTL_RCC_R            (*((volatile unsigned long *)0x400FE060))
#define SYSCTL_RCC2_R           (*((volatile unsigned long *)0x400FE070))
#define PLL_READY                   0x00000040

/* U5Rx (receive) connected to PE4 */
/* U5Tx (transmit) connected to PE5 */

/* PortF */
#define GPIO_PORTF_DATA_R           (*((volatile unsigned long *) 0x400253FC))
#define GPIO_PORTF_AMSEL_R          (*((volatile unsigned long *) 0x40025528))
#define GPIO_PORTF_PCTL_R           (*((volatile unsigned long *) 0x4002552C))
#define GPIO_PORTF_DIR_R            (*((volatile unsigned long *) 0x40025400))
#define GPIO_PORTF_DEN_R            (*((volatile unsigned long *) 0x4002551C))
#define GPIO_PORTF_AFSEL_R          (*((volatile unsigned long *) 0x40025420))
#define SYSCTL_RCGC2_R              (*((volatile unsigned long *) 0x400FE108))
#define SYSCTL_RCGC2_GPIOF          0x00000020

void PLL_Init_50MHz(void) {
    SYSCTL_RCC2_R |= 0x80000000; // 1) use RCC2
    SYSCTL_RCC2_R |= 0x00000800; // 2) set BYPASS2 as 1 to bypass PLL
    SYSCTL_RCC_R = (SYSCTL_RCC_R & ~0x00000FC0) + 0x00000540; // 3) set XTAL as 10101 and select main oscillator
    SYSCTL_RCC2_R &= ~0x00000070;
    SYSCTL_RCC2_R &= ~0x00002000; // 4) set PWRDN2 as 0 to activate PLL
    SYSCTL_RCC2_R |= 0x40000000; // 5) as we want to make system run at 50 MHz
    SYSCTL_RCC2_R = (SYSCTL_RCC2_R & ~0x1FC00000) + (7 << 22); // set SYSDIV2 as 7
    while ((SYSCTL_RIS_R & PLL_READY) == 0) {} // 6) wait PLL to be ready
    SYSCTL_RCC2_R &= ~0x00000800; // 7) set BYPASS2 as 0 to use PLL
}

void CAN0_Init(void){
  SYSCTL_RCGC0_R |= 0x01000000;     /* 1) Provide clock to Enable Clock for CAN0 Module */
  SYSCTL_R_RCGC2_R |= 0x00000002;   /* 2) Provide clock to Port B (clock gating control) */
  GPIO_PORTB_CR_R |= 0x30;          /* 3) Allow changes to PB4-5 */
  GPIO_PORTB_DIR_R |= 0x20;          /* 4) Direction Output for PB5 and Input for PB4 */
  GPIO_PORTB_AMSEL_R &= 0x00;       /* 5) Disable analog functionality on PB */
  GPIO_PORTB_AFSEL_R |= 0x30;       /* 6) Enable alt func on PB4-5 */
  GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R & 0xFF00FFFF) + 0x00880000; /* 7) Set PCTL Register PMC5 and PMC4 to 0x08 for CAN functionality */
  GPIO_PORTB_DEN_R |= 0x30;         /* 8) Enable Digital I/O Pins */
}

void UART0_Init(void){
  SYSCTL_RCGCUART_R |= 0x00000001;      /* 1) Provide clock to UART0 */
  SYSCTL_R_RCGC2_R |= 0x00000001;       /* 2) provide clock to Port A */
  //SYSCTL_RCGCGPIO_R |= 0x00000001;       /* 2) Provide clock to Port A */
  //SYSCTL_RCGCGPIO_R |= 0x00000020;       /* 2) Provide clock to Port A */
  UART0_CTL_R &= ~0x00000001;           /* 3) Disable UART */
  UART0_IBRD_R = 325;                    /* 4) Integer */
  UART0_FBRD_R = 33;                     /* 5) Fractional */
  UART0_LCRH_R = 0x0000070;             /* 6) 8 bit word length (no parity bits, one stop bit, FIFOs)s */
  UART0_CTL_R |= 0x00000300;            /* 7) Enable transmitter and receiver for UART0 */
  UART0_CTL_R |= 0x00000001;            /* 8) Enable UART */
  /*--- GPIO --- */  
  GPIO_PORTA_AMSEL_R &= ~0x03;          /* 9) Disable analog functionality on PA */
  GPIO_PORTA_AFSEL_R |= 0x03;           /* 10) Enable alt func on PA1-0 */
  GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & 0xFFFFFF00) + 0x00000011; /*  11) Configure PA1-0 as UART */
  GPIO_PORTA_DEN_R |= 0x03;             /* 12) Enable digital I/O on PA1-0 */
}

/*
* U5Rx --> PE4
* U5Tx --> PE5
*/
void UART5_Init(void){
    /*--- UART ---*/
    SYSCTL_RCGCUART_R |= 0x00000020; /* 1) Provide clock to UART5 */
    SYSCTL_R_RCGC2_R |= 0x00000010; /* 2) Provide clock to Port E */
    UART5_CTL_R &= ~0x00000001; /* 3) Disable UART5 during initialization */
    UART5_IBRD_R = 325; /* 4) Write the integer portion to UART5_IBRD_R */
    UART5_FBRD_R = 33; /* 5) Write the fractional */
    UART5_LCRH_R = 0x0000070; /* 6) frame: start, 8 data bits, stop; enable FIFO */
    UART5_CTL_R |= 0x00000300; /* 7) Enable transmitter and receiver for UART5 */
    UART5_CTL_R |= 0x00000001; /* 8) Enable UART5 */
    /*--- GPIO --- */
    GPIO_PORTE_AMSEL_R &= ~0x30; /* 9) Disable analog function for PE5 and PE4 */
    GPIO_PORTE_AFSEL_R |= 0x30; /* 10) Enable alternate functions for PE5 and PE4 */
    GPIO_PORTE_PCTL_R = (GPIO_PORTE_PCTL_R & ~0x00FF0000) + 0x00110000; /* 11) Choose UART function for PE5 and PE4 using PCTL register */
    GPIO_PORTE_DEN_R |= 0x30; /* 12) Enable digital I/O on PE4-5 */
}

// 0: No input data
// 1: input data available

unsigned char UART0_Available(void){
    return (((UART0_FR_R &= UART_FR_RXFE) != 0) ? 0 : 1);
}

void UART0_WriteChar(unsigned char data){
    while ((UART0_FR_R &= UART_FR_TXFF) != 0) {}
    UART0_DR_R = data;
}

unsigned char UART0_ReadChar(void){
    while((UART0_FR_R &= UART_FR_RXFE) != 0) {}
    return ((unsigned char)(UART0_DR_R & 0xFF));
}

void UART0_ReadString(char *bufPtr, unsigned short maxLength){
    char inputChar;
    unsigned short length = 0;
    inputChar = UART0_ReadChar();
    while (inputChar != CR){
        /* in case of backspace */
        if (inputChar == BS){
            if (length){
                length--;
                bufPtr--;
                UART0_WriteChar(BS);
            }
        }
        else if (length < maxLength){
            *bufPtr = inputChar;
            length++;
            bufPtr++;
            UART0_WriteChar(inputChar);
        }
        inputChar = UART0_ReadChar();
    }
    *bufPtr = '\0';
}

void UART0_WriteString(char * data){
    while(*data != '\0'){
        UART0_WriteChar(*data);
        data++;
    }
}

unsigned char UART5_Available(void){
    return (((UART5_FR_R &= UART_FR_RXFE) != 0) ? 0 : 1);
}

void UART5_WriteChar(unsigned char data){
    while ((UART5_FR_R &= UART_FR_TXFF) != 0) {}
    UART5_DR_R = data;
}

unsigned char UART5_ReadChar(void){
    while((UART5_FR_R &= UART_FR_RXFE) != 0) {}
    return ((unsigned char)(UART5_DR_R & 0xFF));
}

void UART5_ReadString(char *bufPtr, unsigned short maxLength){
    char inputChar;
    unsigned short length = 0;
    inputChar = UART5_ReadChar();
    while (inputChar != CR){
        /* in case of backspace */
        if (inputChar == BS){
            if (length){
                length--;
                bufPtr--;
                UART5_WriteChar(BS);
            }
        }
        else if (length < maxLength){
            *bufPtr = inputChar;
            length++;
            bufPtr++;
            UART5_WriteChar(inputChar);
        }
        inputChar = UART5_ReadChar();
    }
    *bufPtr = '\0';
}

void UART5_WriteString(char * data){
    while(*data != '\0'){
        UART5_WriteChar(*data);
        data++;
    }
}

void SysTick_Init(void){
    STCTL_R = 0x00000000; /* disable SysTick during setup */
    STCTL_R = 0x00000005; /* enable SysTick. No interrupt and using system clock */
}

/*
* total wait = delay * bus_cycle = delay * (1 / system clock frequency)
*/
void SysTick_Wait(unsigned long delay){
    /* writing zero to STCURRENT_R will clear the counter and COUNT flag */
    STCURRENT_R = 0;
    STRELOAD_R = delay - 1;
    while ((STCTL_R & 0x00010000) == 0){} /* wait for count flag */
}

/*
* system clock: 50 MHz
*/
void SysTick_Wait10ms(unsigned long delay){
    unsigned long i;
    for (i = 0; i < delay; i++) {
        // 500000 * 20 ns = 10 ms
        SysTick_Wait(500000);
    }
}

/* Initialize PortF */
void PortF_Init(void) {
    volatile unsigned long delay;
    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF; // 1) activate clock for GPIO PortF */
    delay = SYSCTL_RCGC2_R;
    GPIO_PORTF_AMSEL_R = 0x00; /* 2) disable analog function */
    GPIO_PORTF_PCTL_R &= 0xFFFF000F; /* 3) PCTL */
    GPIO_PORTF_DEN_R |= 0x0E; /* 4) digital enable */
    GPIO_PORTF_DIR_R |= 0x0E; /* 5) direction */
    GPIO_PORTF_AFSEL_R &= ~0x0E; /* 6) alternate function */
}

void OutCRLF(int chnl){
    if(chnl == 0){
        UART0_WriteChar(CR);
        UART0_WriteChar(LF);
    }
    if(chnl == 5){
        UART5_WriteChar(CR);
        UART5_WriteChar(LF);
    }
}

/* Prepare recieve message object*/
void CAN0_ReadSet(int msgObjNo){
    while(CAN0_IF2CRQ_R & 0x00008000); /* Wait while CAN0 Module is BUSY */
    CAN0_IF2CMSK_R = 0xD3; /* WRNRD, CONTROL, MASK, DATAA, DATAB bits set */
    CAN0_IF2ARB1_R = 0x00; /* DIR bit set */
    CAN0_IF2CMSK_R |= 0x20; /* ARB bit set */
    CAN0_IF2ARB1_R |= 0x00; 
    CAN0_IF2MSK1_R = 0x00;
    CAN0_IF2MSK2_R = 0x00;
    CAN0_IF2ARB2_R = 0x8000; /* MSG Valid bit set in ARB2 reg */
    CAN0_IF2MCTL_R = 0x1088; /* Set # of data bytes, EOB and UMASK */
    CAN0_IF2CRQ_R = msgObjNo; /* Message object number */
    while(CAN0_IF2CRQ_R & 0x00008000); /* Wait while CAN0 Module is BUSY */
}

/* Prepare trasnmit message object */
void CAN0_WriteSet(int msgObjNo){
    while(CAN0_IF1CRQ_R & 0x00008000); /* Wait while CAN0 Module is BUSY */
    CAN0_IF1DA1_R = 0x5453; /* Actual Data to be sent (Not required here, can be ignored) */
    CAN0_IF1DA2_R = 0x5241; /* This is the first message sent. */
    CAN0_IF1DB1_R = 0x0054;
    CAN0_IF1DB2_R = 0x0000;
    CAN0_IF1CMSK_R = 0x93; /* WRNRD, CONTROL, DATAA, DATAB bits set */
    CAN0_IF1MCTL_R = 0x100; /* TXRQST bit set */
    CAN0_IF1ARB2_R = 0x2000; /* DIR bit set */
    CAN0_IF1CMSK_R |= 0x20; /* ARB bit set */
    CAN0_IF1ARB2_R |= 0x04; /* MSG ID set to 0x01*/
    CAN0_IF1ARB2_R |= 0x8000; /* MSG Valid bit set in ARB2 reg */
    CAN0_IF1MSK1_R = 0x00;
    CAN0_IF1MSK2_R = 0x00;
    CAN0_IF1ARB1_R = 0x00;
    CAN0_IF1MCTL_R |= 0x88; /* Set # of data bytes */
    CAN0_IF1CRQ_R = msgObjNo; /* Message object number */
}

void CAN0_Write(int msgObjNo, char data[8], int debug){
    int i;
    char buffer[10];
    CAN0_IF1CMSK_R &= ~0x30; /* Clear ARB and CONTROL bits in CMSK reg */
    CAN0_IF1CMSK_R |= 0x83; /* Set WRNRD, DATAA, DATAB bits in CMSK */
    /* Data */
    CAN0_IF1DA1_R = ((data[1] << 8) + data[0]); 
    CAN0_IF1DA2_R = ((data[3] << 8) + data[2]);
    CAN0_IF1DB1_R = ((data[5] << 8) + data[4]);
    CAN0_IF1DB2_R = ((data[7] << 8) + data[6]);
 
    CAN0_IF1CMSK_R |= 0x87; /* Set the NEWDAT and TXRQST bit in CMSK reg */
    CAN0_IF1CRQ_R = msgObjNo; /* Message object number */
    while(CAN0_IF1CRQ_R & 0x00008000); /* Wait for BUSY bit to clear */
    
    /* Send debug messages to UART0 */
    if(debug){
      UART0_WriteString("Sending Data: ");
      for(i = 0; i < 8; i++){
          sprintf(buffer,"%c",data[i]);
          UART0_WriteString(buffer);
          UART0_WriteChar(' ');
      }
      OutCRLF(0);
    }
} 

//char* CAN0_Read(int msgObjNo, int debug){
void CAN0_Read(int msgObjNo, char* data, int debug){
    int i = 0, ArbReg1 = 0, MsgCtrl = 0;
    //char data[8], buffer[10];        
    char buffer[10];        
 
    CAN0_IF2CMSK_R = 0x73; /* ARB, CONTROL, MASK, DATAA, DATAB bits set */
    CAN0_IF2CRQ_R = msgObjNo; /* Message object number */
 
    while(CAN0_IF2CRQ_R & 0x00008000); /* Wait while CAN0 Module is BUSY */
 
    /* MaskReg0 = CAN0_IF2MSK1_R; 
    MaskReg1 = CAN0_IF2MSK2_R;
    ArbReg0 = CAN0_IF2ARB1_R; */
    /* Get data from registers */
    ArbReg1 = CAN0_IF2ARB2_R;
    MsgCtrl = CAN0_IF2MCTL_R;
 
     /* If NEWDAT bit is set (new data in reg) */
    if(MsgCtrl & 0x8000){
        data[0] = (0x00FF & CAN0_IF2DA1_R); //Get this new data.
        data[1] = ((0xFF00 & CAN0_IF2DA1_R) >> 8);
        data[2] = (0x00FF & CAN0_IF2DA2_R);
        data[3] = ((0xFF00 & CAN0_IF2DA2_R) >> 8);
        data[4] = (0x00FF & CAN0_IF2DB1_R);
        data[5] = ((0xFF00 & CAN0_IF2DB1_R) >> 8);
        data[6] = (0x00FF & CAN0_IF2DB2_R);
        data[7] = ((0xFF00 & CAN0_IF2DB2_R) >> 8);
        CAN0_IF2CMSK_R |= 0x04; /* Set NEWDAT in CMSK to Clear the NEWDAT bit in MCTL */
    }
    /* If MSGLST bit is set (message lost) */
    if(MsgCtrl & 0x4000) {
        MsgCtrl &= ~0x4000; /* Clear the MSGLST bit */
        CAN0_IF2MCTL_R = MsgCtrl; /* Clear the MSGLST bit */
        if(debug)
          UART0_WriteString("Message lost\n");
    }
 
    CAN0_IF2CRQ_R = msgObjNo;
    if(debug){  
      UART0_WriteString("Received Message: ");
      UART0_WriteString("ID: ");
      sprintf(buffer, "%d", ((ArbReg1 & 0x1FFF) >> 3));
      UART0_WriteString(buffer);
      UART0_WriteString("RTR 0: ");
      UART0_WriteString("DLC: ");
      sprintf(buffer, "%d", (MsgCtrl & 0xF));
      UART0_WriteString(buffer); 
      
      /* Send debug messages to UART0 */
      UART0_WriteString("Data: ");
      for(i = 0; i < 8; i++){
          sprintf(buffer, "%d", data[i]);
          UART0_WriteString(buffer);
          UART0_WriteChar(' ');
      }
      OutCRLF(0);
    }
    //return data;
}

int UART_Comm(int num){
    UART5_WriteString("r - For Red LED");
    OutCRLF(5);
    UART5_WriteString("b - For Blue LED");
    OutCRLF(5);
    UART5_WriteString("g - turn Green LED");
    OutCRLF(5);
    UART5_WriteString("Please input a character: ");
    OutCRLF(5);
    for(;;){
        if (UART5_Available()){
            unsigned char recvChar = UART5_ReadChar();
            UART5_WriteString("Received Char: ");
            UART5_WriteChar(recvChar);
            OutCRLF(5);
            switch (recvChar){
                case 'r':
                    GPIO_PORTF_DATA_R = 0x02;
                    break;
                case 'b':
                    GPIO_PORTF_DATA_R = 0x04;
                    break;
                case 'g':
                    GPIO_PORTF_DATA_R = 0x08;
                    break;
                default:
                    GPIO_PORTF_DATA_R = 0x00;
                    break;
            }
        }
    }
}

int main(void){
    PLL_Init_50MHz();
    CAN0_Init();
    UART0_Init();
    UART5_Init();
    PortF_Init();
    GPIO_PORTF_DATA_R = 0x00;
    UART5_WriteString("r - For Red LED");
    UART0_WriteString("r - For Red LED");
    OutCRLF(5);
    OutCRLF(0);
    UART5_WriteString("b - For Blue LED");
    UART0_WriteString("b - For Blue LED");
    OutCRLF(5);
    OutCRLF(0);
    UART5_WriteString("g - turn Green LED");
    UART0_WriteString("g - turn Green LED");
    OutCRLF(5);
    OutCRLF(0);
    UART5_WriteString("Please input a character: ");
    UART0_WriteString("Please input a character: ");
    OutCRLF(5);
    OutCRLF(0);
    for(;;){
        if (UART5_Available()){
            unsigned char recvChar = UART5_ReadChar();
            UART5_WriteString("Received Char: ");
            UART5_WriteChar(recvChar);
            OutCRLF(5);
            switch (recvChar){
                case 'r':
                    GPIO_PORTF_DATA_R = 0x02;
                    break;
                case 'b':
                    GPIO_PORTF_DATA_R = 0x04;
                    break;
                case 'g':
                    GPIO_PORTF_DATA_R = 0x08;
                    break;
                default:
                    GPIO_PORTF_DATA_R = 0x00;
                    break;
            }
        }
        if (UART0_Available()){
                    unsigned char recvChar = UART0_ReadChar();
                    UART0_WriteString("Received Char: ");
                    UART0_WriteChar(recvChar);
                    OutCRLF(0);
                    switch (recvChar){
                        case 'r':
                            GPIO_PORTF_DATA_R = 0x02;
                            break;
                        case 'b':
                            GPIO_PORTF_DATA_R = 0x04;
                            break;
                        case 'g':
                            GPIO_PORTF_DATA_R = 0x08;
                            break;
                        default:
                            GPIO_PORTF_DATA_R = 0x00;
                            break;
                    }
        }
    }
}