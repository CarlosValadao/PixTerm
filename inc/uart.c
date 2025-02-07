#include "uart.h"
#include "pico/stdlib.h"

void uart_init_all(uart_inst_t *uart, uint8_t rx, uint8_t tx, uint16_t baudrate)
{
    uart_init(uart, baudrate);
    gpio_set_function(rx, GPIO_FUNC_UART);
    gpio_set_function(tx, GPIO_FUNC_UART);
}