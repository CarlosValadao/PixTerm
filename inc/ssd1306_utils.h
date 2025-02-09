#ifndef SSD1306_UTILS_H
#define SSD1306_UTILS_H

#include "ssd1306.h"

#define UINT8_T_CONSTANT(value) ((uint8_t) (value))

#define OLED_LINE1 UINT8_T_CONSTANT(0)
#define OLED_LINE2 UINT8_T_CONSTANT(8)
#define OLED_LINE3 UINT8_T_CONSTANT(16)
#define OLED_LINE4 UINT8_T_CONSTANT(24)
#define OLED_LINE5 UINT8_T_CONSTANT(32)
#define OLED_LINE6 UINT8_T_CONSTANT(40)
#define OLED_LINE7 UINT8_T_CONSTANT(48)
#define OLED_LINE8 UINT8_T_CONSTANT(56)

#define OLED_COL1  UINT8_T_CONSTANT(0)
#define OLED_COL2  UINT8_T_CONSTANT(8)
#define OLED_COL3  UINT8_T_CONSTANT(16)
#define OLED_COL4  UINT8_T_CONSTANT(24)
#define OLED_COL5  UINT8_T_CONSTANT(32)
#define OLED_COL6  UINT8_T_CONSTANT(40)
#define OLED_COL7  UINT8_T_CONSTANT(48)
#define OLED_COL8  UINT8_T_CONSTANT(56)
#define OLED_COL9  UINT8_T_CONSTANT(64)
#define OLED_COL10 UINT8_T_CONSTANT(72)
#define OLED_COL11 UINT8_T_CONSTANT(80)
#define OLED_COL12 UINT8_T_CONSTANT(88)
#define OLED_COL13 UINT8_T_CONSTANT(96)
#define OLED_COL14 UINT8_T_CONSTANT(104)
#define OLED_COL15 UINT8_T_CONSTANT(112)
#define OLED_COL16 UINT8_T_CONSTANT(120)

void ssd1306_clear_screen(ssd1306_t *ssd);
void ssd1306_clear_line(ssd1306_t *ssd, uint8_t line);
void ssd1306_print_char(ssd1306_t *ssd, char c, uint8_t x, uint8_t y);
void ssd1306_print_str(ssd1306_t *ssd, const char *str, uint8_t x, uint8_t y);
void ssd1306_init_all(ssd1306_t *ssd, i2c_inst_t *i2c, uint baudrate, uint8_t sda, uint8_t scl);
void ssd1306_auto_write_char(ssd1306_t *ssd, char c);
void ssd1306_set_auto_write_cursor(uint8_t x, uint8_t y);

#endif //SSD1306_UTILS