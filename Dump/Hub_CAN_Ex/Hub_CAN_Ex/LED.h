
#ifndef LED_H_
#define LED_H_

#define LEDPORT PORTB
#define LED0 0
#define LED1 1
#define LED2 2
#define LED3 3
#define LED4 4
#define LED5 5
#define LED6 6
#define LED7 7

void LED_Reg_Write(uint8_t val);
void LED_set(uint8_t LED);
void LED_clr(uint8_t LED);
void LED_toggle(uint8_t LED);



#endif /* LED_H_ */