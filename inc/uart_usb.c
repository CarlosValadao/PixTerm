#include "uart_usb.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


char uart_usb_blocking_getc()
{
    char recvd_char;
    scanf("%c", &recvd_char);
    fflush(stdin);
    return recvd_char;
}

char *uart_usb_blocking_gets()
{
    uint8_t buffer_size = 5;
    char *buffer = malloc(sizeof(char) * buffer_size + 1);
    fgets(buffer, buffer_size + 1, stdin);
    fflush(stdin);
    return buffer;
}