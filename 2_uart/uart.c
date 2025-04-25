#include "uart.h"
#include "gpio.h"

void uart_init(){ 
	GPIO->PIN_CNF[6] = 1; //TXD (transfer) output
	GPIO->PIN_CNF[8] = 0; //RXD (recieve) input

    UART->PSELTXD = 6; 
    UART->PSELRXD = 8;

    UART->BAUDRATE = 0x00275000;
    UART->PSELRTS = 0xFFFFFFFF;
    UART->PSELCTS = 0xFFFFFFFF;

    UART->ENABLE = 4;
    UART->TASKS_STARTRX = 1;
}

void uart_send(char letter) {
    UART->TASKS_STARTTX = 1;
    UART->TXD = letter; //char oversettes til int?
    while (!(UART->EVENTS_TXDRDY));
    UART->TASKS_STOPTX = 1;
    UART->EVENTS_TXDRDY = 0;
}

char uart_read() {
    char letter;
    if (UART->EVENTS_RXDRDY) {
        letter = UART->RXD;
    } else {
        letter = "\0";
    }
    UART->EVENTS_RXDRDY = 0;
    return letter;
}