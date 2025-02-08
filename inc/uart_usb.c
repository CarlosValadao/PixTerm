#include "uart_usb.h"
#include <stdio.h>


char uart_usb_blocking_getc()
{
    char recvd_char;
    scanf("%c", &recvd_char);
    fflush(stdin);
    return recvd_char;
}

char *uart_usb_blocking_gets()
{
    return '\0'; //TO DO
}