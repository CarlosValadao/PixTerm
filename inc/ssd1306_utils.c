#include "ssd1306_utils.h"

static uint8_t cursor_col = 0;
static uint8_t cursor_row = 0;
static uint8_t aux_col = 0;
static uint8_t aux_row = 0;

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

void ssd1306_init_all(ssd1306_t *ssd, i2c_inst_t *i2c, uint baudrate, uint8_t sda, uint8_t scl, uint8_t address)
{
    i2c_init(i2c, baudrate);
    gpio_set_function(sda, GPIO_FUNC_I2C);
    gpio_set_function(scl, GPIO_FUNC_I2C);
    gpio_pull_up(sda);
    gpio_pull_up(scl);
    ssd1306_init(ssd, WIDTH, HEIGHT, false, address, i2c);
    ssd1306_config(ssd);
    ssd1306_send_data(ssd);
}

void ssd1306_auto_write_char(ssd1306_t *ssd, char c)
{
    if (aux_col == WIDTH) {
        aux_col = OLED_COL1;
        aux_row += 8;
        if(aux_row == HEIGHT) {
            aux_col = cursor_col;
            aux_row = cursor_row;
        }
    }
    ssd1306_print_char(ssd, c, aux_col, aux_row);
    aux_col += 8;
}

void ssd1306_set_auto_write_cursor(uint8_t col, uint8_t line)
{
    cursor_col = col;
    cursor_row = line;
    aux_col = cursor_col;
    aux_row = cursor_row;
}