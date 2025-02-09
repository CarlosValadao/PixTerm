#ifndef SSD1306_UTILS_H
#define SSD1306_UTILS_H

#include "ssd1306.h"

#define OLED_LINE1 0
#define OLED_LINE2 1
#define OLED_LINE2 2
#define OLED_LINE2 3
#define OLED_LINE2 4
#define OLED_LINE2 5
#define OLED_LINE2 6
#define OLED_LINE2 7

#define OLED_COL1  0
#define OLED_COL2  8
#define OLED_COL3  16
#define OLED_COL4  24
#define OLED_COL5  32
#define OLED_COL6  40
#define OLED_COL7  48
#define OLED_COL8  56
#define OLED_COL9  64
#define OLED_COL10 72
#define OLED_COL11 80
#define OLED_COL12 88
#define OLED_COL13 96
#define OLED_COL14 104
#define OLED_COL15 112
#define OLED_COL16 120

void ssd1306_clear_screen(const ssd1306_t *ssd);
void ssd1306_clear_line(const ssd1306_t *ssd);
void ssd1306_print_char(const ssd1306_t *ssd, char c, uint8_t x, uint8_t y);
void ssd1306_print_str(const ssd1306_t *ssd, const char *str, uint8_t x, uint8_t y);

#endif //SSD1306_UTILS