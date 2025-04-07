#include "uart.h"

int main() {
    // Configure LED Matrix
	for(int i = 17; i <= 20; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTSET = (1 << i);
	}

	// Configure buttons -> see button_init()
	button_init();

	int sleep = 0;
	while(1){

		/* Check if button 1 is pressed;
		 * turn on LED matrix if it is. */
		if (!(GPIO->IN & (1 << 13))) {
			for(int i = 17; i <= 20; i++){
				GPIO->OUTCLR = (1 << i);
			}
		}

		/* Check if button 2 is pressed;
		 * turn off LED matrix if it is. */
		if (!(GPIO->IN & (1 << 14))) {
			for(int i = 17; i <= 20; i++){
				GPIO->OUTSET = (1 << i);
			}
		}

		sleep = 10000;
		while(--sleep); // Delay
    }
    return 0;
}