#include "uart.h"
#include "gpio.h"

void button_init(){ 
	GPIO->PIN_CNF[13] = (3 << 2); //Button1
	GPIO->PIN_CNF[14] = (3 << 2); //Button2
	
	// Configure LED Matrix
	for(int i = 17; i <= 20; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTSET = (1 << i);
	}
}

int main() {
	button_init();
    uart_init();

	int sleep = 0;
	while(1){

		/* Check if button 1 is pressed;
		 * turn on LED matrix if it is. */
		if (!(GPIO->IN & (1 << 13))) {
			uart_send("A");
		}

		/* Check if button 2 is pressed;
		 * turn off LED matrix if it is. */
		if (!(GPIO->IN & (1 << 14))) {
			uart_send("B");
		}

		if (uart_read() != "\0") {
			if (GPIO->IN & (1 << 17)) {
				for(int i = 17; i <= 20; i++){
					GPIO->OUTSET = (1 << i);
				}
			} else {
				for(int i = 17; i <= 20; i++){
					GPIO->OUTCLR = (1 << i);
				}
			}
		}

		sleep = 10000;
		while(--sleep); // Delay
    }
    return 0;
}