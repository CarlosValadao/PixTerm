#include "ssd1306_utils.h"

void ssd1306_clear_display(const ssd1306_t *ssd)
{
    ssd1306_fill(ssd, false);
    ssd1306_send_data(ssd);
}

void ssd1306_clear_line(const ssd1306_t *ssd)
{
    return; //TO DO
}

void ssd1306_print_char(const ssd1306_t *ssd, char c, uint8_t x, uint8_t y)
{
    return; //TO DO
}

void ssd1306_print_str(const ssd1306_t *ssd, const char *str, uint8_t x, uint8_t y)
{
    return; //TO DO
}