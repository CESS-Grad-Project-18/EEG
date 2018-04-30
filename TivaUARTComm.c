#define CR 0x0D /* Carriage return */
#define LF 0x0A /* Line Feed */
#define BS 0x08 /* Backspace */

/* CAN 0 */
#define CAN0_CTL_R              (*((volatile unsigned long *)0x40040000))
#define CAN0_STS_R              (*((volatile unsigned long *)0x40040004))
#define CAN0_ERR_R              (*((volatile unsigned long *)0x40040008))
#define CAN0_BIT_R              (*((volatile unsigned long *)0x4004000C))
#define CAN0_INT_R              (*((volatile unsigned long *)0x40040010))
#define CAN0_TST_R              (*((volatile unsigned long *)0x40040014))
#define CAN0_BRPE_R             (*((volatile unsigned long *)0x40040018))
#define CAN0_IF1CRQ_R           (*((volatile unsigned long *)0x40040020))
#define CAN0_IF1CMSK_R          (*((volatile unsigned long *)0x40040024))
#define CAN0_IF1MSK1_R          (*((volatile unsigned long *)0x40040028))
#define CAN0_IF1MSK2_R          (*((volatile unsigned long *)0x4004002C))
#define CAN0_IF1ARB1_R          (*((volatile unsigned long *)0x40040030))
#define CAN0_IF1ARB2_R          (*((volatile unsigned long *)0x40040034))
#define CAN0_IF1MCTL_R          (*((volatile unsigned long *)0x40040038))
#define CAN0_IF1DA1_R           (*((volatile unsigned long *)0x4004003C))
#define CAN0_IF1DA2_R           (*((volatile unsigned long *)0x40040040))
#define CAN0_IF1DB1_R           (*((volatile unsigned long *)0x40040044))
#define CAN0_IF1DB2_R           (*((volatile unsigned long *)0x40040048))
#define CAN0_IF2CRQ_R           (*((volatile unsigned long *)0x40040080))
#define CAN0_IF2CMSK_R          (*((volatile unsigned long *)0x40040084))
#define CAN0_IF2MSK1_R          (*((volatile unsigned long *)0x40040088))
#define CAN0_IF2MSK2_R          (*((volatile unsigned long *)0x4004008C))
#define CAN0_IF2ARB1_R          (*((volatile unsigned long *)0x40040090))
#define CAN0_IF2ARB2_R          (*((volatile unsigned long *)0x40040094))
#define CAN0_IF2MCTL_R          (*((volatile unsigned long *)0x40040098))
#define CAN0_IF2DA1_R           (*((volatile unsigned long *)0x4004009C))
#define CAN0_IF2DA2_R           (*((volatile unsigned long *)0x400400A0))
#define CAN0_IF2DB1_R           (*((volatile unsigned long *)0x400400A4))
#define CAN0_IF2DB2_R           (*((volatile unsigned long *)0x400400A8))
#define CAN0_TXRQ1_R            (*((volatile unsigned long *)0x40040100))
#define CAN0_TXRQ2_R            (*((volatile unsigned long *)0x40040104))
#define CAN0_NWDA1_R            (*((volatile unsigned long *)0x40040120))
#define CAN0_NWDA2_R            (*((volatile unsigned long *)0x40040124))
#define CAN0_MSG1INT_R          (*((volatile unsigned long *)0x40040140))
#define CAN0_MSG2INT_R          (*((volatile unsigned long *)0x40040144))
#define CAN0_MSG1VAL_R          (*((volatile unsigned long *)0x40040160))
#define CAN0_MSG2VAL_R          (*((volatile unsigned long *)0x40040164))


/* Run Mode Clock Gating Control (UART) */
#define SYSCTL_RCGCUART_R   (*((volatile unsigned long *) 0x400FE618))

/* Run Mode Clock Gating Control Register 2 (GPIO) */
#define SYSCTL_R_RCGC2_R        (*((volatile unsigned long *) 0x400FE108))

/* UART0 */
#define UART0_CTL_R             (*((volatile unsigned long *)0x4000C030))
#define UART0_IBRD_R            (*((volatile unsigned long *)0x4000C024))
#define UART0_FBRD_R            (*((volatile unsigned long *)0x4000C028))
#define UART0_LCRH_R            (*((volatile unsigned long *)0x4000C02C))
#define UART0_FR_R              (*((volatile unsigned long *)0x4000C018))
#define UART0_DR_R              (*((volatile unsigned long *)0x4000C000))

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

/* GPIO */
#define GPIO_PORTE_AMSEL_R  (*((volatile unsigned long *)0x40024528))
#define GPIO_PORTE_PCTL_R   (*((volatile unsigned long *)0x4002452C))
#define GPIO_PORTE_AFSEL_R  (*((volatile unsigned long *)0x40024420))
#define GPIO_PORTE_DEN_R        (*((volatile unsigned long *)0x4002451C))

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
#define GPIO_PORTF_DATA_R           (*((volatile unsigned long *)0x400253FC))
#define GPIO_PORTF_AMSEL_R          (*((volatile unsigned long *)0x40025528))
#define GPIO_PORTF_PCTL_R           (*((volatile unsigned long *)0x4002552C))
#define GPIO_PORTF_DIR_R            (*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_DEN_R            (*((volatile unsigned long *)0x4002551C))
#define GPIO_PORTF_AFSEL_R          (*((volatile unsigned long *)0x40025420))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
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

void UART0_Init(void){
  SYSCTL_RCGCUART_R |= 0x00000001;            // 1) activate UART0
  SYSCTL_RCGCGPIO_R |= 0x00000001;            // 2) activate port A
  while((SYSCTL_PRGPIO_R & 0x0000001) == 0);
  UART0_CTL_R &= ~0x00000001;           // 3) disable UART
  UART0_IBRD_R = 27;                    // 4) IBRD = int(50,000,000 / (16 * 115,200)) = int(27.1267)
  UART0_FBRD_R = 8;                     // 5) FBRD = int(0.1267 * 64 + 0.5) = 8
  UART0_LCRH_R = (UART_LCRH_WLEN_8|UART_LCRH_FEN); // 6) 8 bit word length (no parity bits, one stop bit, FIFOs)s
  UART0_CTL_R |= UART_CTL_UARTEN;       // 7) enable UART
  /*--- GPIO --- */
  GPIO_PORTA_AMSEL_R &= ~0x03;          // 8) disable analog functionality on PA
  GPIO_PORTA_AFSEL_R |= 0x03;           // 9) enable alt funct on PA1-0
  GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & 0xFFFFFF00) + 0x00000011; //10) configure PA1-0 as UART
  GPIO_PORTA_DEN_R |= 0x03;             // 11) enable digital I/O on PA1-0
}

/*
* U5Rx --> PE4
* U5Tx --> PE5
*/
void UART5_Init(void){
    /*--- UART ---*/
    SYSCTL_RCGCUART_R |= 0x00000020; /* 1) provide clock to UART5 */
    SYSCTL_R_RCGC2_R |= 0x00000010; /* 2) provide clock to PortE */
    UART5_CTL_R &= ~0x00000001; /* 3) disable UART5 during initialization */
    UART5_IBRD_R = 325; /* 4) write the integer portion to UART5_IBRD_R */
    UART5_FBRD_R = 33; /* 5) write the fractional */
    UART5_LCRH_R = 0x0000070; /* 6) frame: start, 8 data bits, stop; enable FIFO */
    UART5_CTL_R |= 0x00000300; /* 7) enable transmitter and receiver for UART5 */
    UART5_CTL_R |= 0x00000001; /* 8) enable UART5 */
    /*--- GPIO --- */
    GPIO_PORTE_AMSEL_R &= ~0x30; /* 9) Disable analog function for PE5 and PE4 */
    GPIO_PORTE_AFSEL_R |= 0x30; /* 10) enable alternate functions for PE5 and PE4 */
    GPIO_PORTE_PCTL_R = (GPIO_PORTE_PCTL_R & ~0x00FF0000) + 0x00110000; /* 11) choose UART function for PE5 and PE4 using PCTL register */
    GPIO_PORTE_DEN_R |= 0x30; /* 12) make PE5 and PE4 as digital IO */
}

// 0: No input data
// 1: input data available

unsigned char UART0_Available(void){
    return (((UART0_FR_R &= UART_FR_RXFE) != 0) ? 0 : 1);
}

void UART0_WriteChar(unsigned char data){
    while ((UART0_FR_R &= UART_FR_TXFF) != 0) {}
    UART5_DR_R = data;
}

unsigned char UART0_ReadChar(void){
    while((UART0_FR_R &= UART_FR_RXFE) != 0) {}
    return ((unsigned char)(UART0_DR_R & 0xFF));
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
    GPIO_PORTF_PCTL_R &= 0xFFFF000F; // 3) PCTL */
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

int main(void){
    PLL_Init_50MHz();
    UART5_Init();
    UART0_Init();
    PortF_Init();
    GPIO_PORTF_DATA_R = 0x00;
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
            OutCRLF();
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
