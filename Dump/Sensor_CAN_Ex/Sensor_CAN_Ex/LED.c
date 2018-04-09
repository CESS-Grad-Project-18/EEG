
#include <avr/io.h>
#include "LED.h"

void LED_Reg_Write(uint8_t val) {
	LEDPORT = ~val;
}

void LED_set(uint8_t LED) {
	LEDPORT &= ~(1 << LED);
}

void LED_clr(uint8_t LED) {
	LEDPORT |= (1 << LED);
}

void LED_toggle(uint8_t LED) {
	LEDPORT ^= (1 << LED);
}