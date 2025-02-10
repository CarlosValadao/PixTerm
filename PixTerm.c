#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/clocks.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "pico/bootrom.h"
#include "inc/lite5.h"
#include "inc/rgb.h"
#include "inc/push_button.h"
#include "inc/ws2812b.h"
#include "inc/ssd1306_utils.h"
#include "inc/uart_usb.h"



#define UART_ID uart0
#define BAUDRATE 115200
#define UART_TX 0
#define UART_RX 1

#define WS2812B_PIN 7

#define JOYSTICK_SW 22

#define LED_RGB_DEFAULT_INTENSITY 10

#define LED_RED_PIN   13
#define LED_GREEN_PIN 11
#define LED_BLUE_PIN  12

#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define DISPLAY_ADDR 0x3C

#define JOYSTICK_SW_PRESSED gpio == JOYSTICK_SW
#define BUTTON_A_PRESSED gpio == BUTTON_A
#define BUTTON_B_PRESSED gpio == BUTTON_B

#define set_bootsel_mode() reset_usb_boot(0, 0)
#define CHAR_TO_NUM(value) ((uint8_t) (value-48))

typedef struct {
    bool green_led;
    bool blue_led;
} LEDState;

static LEDState led_state = {.green_led = false, .blue_led = false};
static ssd1306_t *ssd_global;

void on_button_press(uint gpio, uint32_t event);
void toggle_led(uint gpio, bool *led_state, const char *label);

static const uint8_t COLORS[] = {PURPLE, GREEN, BLUE_MARINE, RED, YELLOW, BLUE, GREEN, BLUE, YELLOW};

int main()
{
    stdio_init_all();
    set_sys_clock_khz(128000, false);
    ws2812b_t *ws;
    rgb_t rgb_pins = {.red = LED_RED_PIN, .blue = LED_BLUE_PIN, .green = LED_GREEN_PIN};
    rgb_init(&rgb_pins);
    int16_t curr_display_row = 0, curr_display_col = 112;
    Command cmd;

    ws = init_ws2812b(pio0, WS2812B_PIN);
    pb_config_btn_a();
    pb_config_btn_b();
    pb_config(JOYSTICK_SW, true);
    pb_set_irq_callback(&on_button_press);
    pb_enable_irq(BUTTON_A);
    pb_enable_irq(BUTTON_B);
    pb_enable_irq(JOYSTICK_SW);
    
    ssd1306_t ssd;
    ssd1306_init_all(&ssd, I2C_PORT, 400000, I2C_SDA, I2C_SCL, DISPLAY_ADDR);

    ssd_global = &ssd;
    char c;
    ssd1306_set_auto_write_cursor(OLED_COL1, OLED_LINE5);

    while(true)
    {
        c = uart_usb_blocking_getc();
        ssd1306_auto_write_char(&ssd, c);
        if (isdigit(c)) ws2812b_draw(ws, NUMERIC_GLYPHS[CHAR_TO_NUM(c)], COLORS[CHAR_TO_NUM(c)], 1);
    }
    return EXIT_SUCCESS;
}

void toggle_led(uint gpio, bool *led_state, const char* label)
{
    if(!(*led_state)) rgb_turn_on_by_gpio(gpio, LED_RGB_DEFAULT_INTENSITY);
    else turn_off_led_by_gpio(gpio);
    printf("%s\n", label);
    *led_state = !(*led_state);
}

void on_button_press(uint gpio, uint32_t event)
{
    if(pb_is_debounce_delay_over())
    {
        if(JOYSTICK_SW_PRESSED) set_bootsel_mode();
        else if(BUTTON_A_PRESSED) {
            const char *green_led_msg = led_state.green_led ? "Green LED off" : "Green LED on";
            ssd1306_clear_line(ssd_global, OLED_LINE1);
            ssd1306_print_str(ssd_global, green_led_msg, OLED_COL1, OLED_LINE1);
            toggle_led(LED_GREEN_PIN, &led_state.green_led, green_led_msg);
        } 
        else {
            const char *blue_led_msg = led_state.blue_led ? "Blue LED off" : "Blue LED on";
            ssd1306_clear_line(ssd_global, OLED_LINE3);
            ssd1306_print_str(ssd_global, blue_led_msg, OLED_COL1, OLED_LINE3);
            toggle_led(LED_BLUE_PIN, &led_state.blue_led, blue_led_msg);
        }
    }
}