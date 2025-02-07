#ifndef UART_H
#define UART_H

#include "hardware/uart.h"

void uart_init_all(uart_inst_t *uart, uint8_t rx, uint8_t tx, uint16_t baudrate);

#endif //UART_H