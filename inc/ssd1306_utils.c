#include "ssd1306_utils.h"

static uint8_t cursor_x = 0;
static uint8_t cursor_y = 0;

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
    ssd1306_draw_string(ssd, str, x, y);
    ssd1306_send_data(ssd);
}

void i2c_init_all(ssd1306_t *ssd, i2c_inst_t *i2c, uint baudrate, uint8_t sda, uint8_t scl)
{
    return; //TO DO
}

void ssd1306_auto_write_char(ssd1306_t *ssd, char c)
{
    return; //TO DO
}

void ssd1306_set_auto_write_cursor(uint8_t x, uint8_t y)
{
    return; //TO DO
}