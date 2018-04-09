
#ifndef TIMER_H_
#define TIMER_H_

extern volatile uint8_t CTC_flag;

void timer_init(void);
void delay_us(uint16_t us);
void delay_ms(uint16_t ms);

#endif /* TIMER_H_ */