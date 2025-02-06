#include "pico/stdlib.h"
#include "inc/rgb.h"
#include "inc/push_button.h"
#include "inc/ws2812b.h"
#include "inc/ssd1306.h"
#include <stdlib.h>

int main()
{
    set_sys_clock_khz(128000, false);
    while(true);
    return EXIT_SUCCESSFUL;
}