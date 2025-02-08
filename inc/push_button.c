#include "push_button.h"
#include "pico/stdlib.h"

#define DEBOUNCE_DELAY_MS 300

volatile bool FIRST_IRQ_USE = true;
volatile gpio_irq_callback_t PB_IRQ_CALLBACK = NULL;
volatile uint32_t PB_DEBOUNCE_LAST_TIME = 0;

void pb_config(uint8_t button_pin, bool pullup)
{
    gpio_init(button_pin);
    if(pullup) gpio_pull_up(button_pin);
}

void pb_set_irq_callback(gpio_irq_callback_t callback) { PB_IRQ_CALLBACK = callback; }

void pb_enable_irq(uint button_pin)
{
    if(FIRST_IRQ_USE) gpio_set_irq_enabled_with_callback(button_pin, GPIO_IRQ_EDGE_FALL, true, PB_IRQ_CALLBACK);
    else gpio_set_irq_enabled(button_pin, GPIO_IRQ_EDGE_FALL, true);    
}

bool pb_is_button_pressed(uint8_t button_pin) { return (!gpio_get(button_pin)); }

bool pb_is_debounce_delay_over()
{
    uint32_t current_time = to_ms_since_boot(get_absolute_time());
    bool debounce_time_elapsed = (current_time - PB_DEBOUNCE_LAST_TIME >= DEBOUNCE_DELAY_MS);
    if(debounce_time_elapsed)
    {
        PB_DEBOUNCE_LAST_TIME = current_time;
        return true;
    }
    return false;
}