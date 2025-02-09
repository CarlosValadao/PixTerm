#include "ssd1306_utils.h"

void ssd1306_clear_display(ssd1306_t *ssd)
{
    ssd1306_fill(ssd, false);
    ssd1306_send_data(ssd);
}

void ssd1306_clear_line(ssd1306_t *ssd, uint8_t line)
{
// Itera por todas as posições do display
    for(uint8_t l = line; l <= line + 8; l++)
    {
        for (uint8_t x = 0; x < ssd->width; ++x) {
            ssd1306_pixel(ssd, x, l, 0);
        }
    }
}

void ssd1306_print_char(ssd1306_t *ssd, char c, uint8_t x, uint8_t y)
{
    ssd1306_draw_char(ssd, c, x, y);
    ssd1306_send_data(ssd);
}

void ssd1306_print_str(ssd1306_t *ssd, const char *str, uint8_t x, uint8_t y)
{
    return; //TO DO
}