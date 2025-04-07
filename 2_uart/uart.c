#include "uart.h"
#include "gpio.h"

void button_init(){ 
	GPIO->PIN_CNF[6] = (3 << 2); //TXD (transfer)
	GPIO->PIN_CNF[8] = (3 << 2); //RXD (recieve)

    GPIO->DIRSET = (1 << 6);
    GPIO->OUTSET = (1 << 6);

    GPIO->DIRSET = (1 << 8);
    GPIO->OUTSET = (1 << 8);
}