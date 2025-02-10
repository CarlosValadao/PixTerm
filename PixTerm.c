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

// Configuração da comunicação UART
#define UART_ID uart0
#define BAUDRATE 115200
#define UART_TX 0
#define UART_RX 1

// Pino de controle para a matriz de LEDs WS2812B
#define WS2812B_PIN 7

// Pino do botão do joystick
#define JOYSTICK_SW 22

// Intensidade padrão do LED RGB
#define LED_RGB_DEFAULT_INTENSITY 10

// Definições dos pinos do LED RGB
#define LED_RED_PIN   13
#define LED_GREEN_PIN 11
#define LED_BLUE_PIN  12

// Definições do barramento I2C para o display OLED SSD1306
#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define DISPLAY_ADDR 0x3C  // Endereço I2C do display SSD1306

// Macros para verificar se os botões foram pressionados
#define JOYSTICK_SW_PRESSED gpio == JOYSTICK_SW
#define BUTTON_A_PRESSED gpio == BUTTON_A
#define BUTTON_B_PRESSED gpio == BUTTON_B

// Atalho para reinicializar no modo BOOTSEL (para programação via USB)
#define set_bootsel_mode() reset_usb_boot(0, 0)

// Converte um caractere numérico para seu valor inteiro correspondente
#define CHAR_TO_NUM(value) ((uint8_t) (value-48))

// Estrutura para armazenar o estado dos LEDs
typedef struct {
    bool green_led;
    bool blue_led;
} LEDState;

// Variável global para armazenar o estado dos LEDs
static LEDState led_state = {.green_led = false, .blue_led = false};

// Ponteiro global para acessar o display OLED
static ssd1306_t *ssd_global;

// Protótipos das funções
void on_button_press(uint gpio, uint32_t event);
void toggle_led(uint gpio, bool *led_state, const char *label);

// Definição das cores para exibição na matriz de LEDs WS2812B
static const uint8_t COLORS[] = {PURPLE, GREEN, BLUE_MARINE, RED, YELLOW, BLUE, GREEN, BLUE, YELLOW};

int main()
{
    // Inicializa a comunicação padrão (printf via USB)
    stdio_init_all();

    // Configura o clock do sistema para 128 MHz
    set_sys_clock_khz(128000, false);

    // Declaração do objeto para a matriz de LEDs WS2812B
    ws2812b_t *ws;

    // Configuração dos pinos do LED RGB
    rgb_t rgb_pins = {.red = LED_RED_PIN, .blue = LED_BLUE_PIN, .green = LED_GREEN_PIN};
    rgb_init(&rgb_pins);

    // Variáveis para controle da posição do display OLED
    int16_t curr_display_row = 0, curr_display_col = 112;

    // Inicializa a matriz de LEDs WS2812B
    ws = init_ws2812b(pio0, WS2812B_PIN);

    // Configuração dos botões físicos
    pb_config_btn_a();
    pb_config_btn_b();
    pb_config(JOYSTICK_SW, true);

    // Associa a função de interrupção aos botões
    pb_set_irq_callback(&on_button_press);
    pb_enable_irq(BUTTON_A);
    pb_enable_irq(BUTTON_B);
    pb_enable_irq(JOYSTICK_SW);

    // Inicializa o display OLED SSD1306 via I2C
    ssd1306_t ssd;
    ssd1306_init_all(&ssd, I2C_PORT, 400000, I2C_SDA, I2C_SCL, DISPLAY_ADDR);

    // Armazena a referência global para o display
    ssd_global = &ssd;

    // Define o cursor inicial do display
    ssd1306_set_auto_write_cursor(OLED_COL1, OLED_LINE5);

    // Loop principal do programa
    char c;
    while(true)
    {
        // Captura um caractere enviado via USB (UART)
        c = uart_usb_blocking_getc();

        // Exibe o caractere capturado no display OLED
        ssd1306_auto_write_char(&ssd, c);

        // Se o caractere for um número, exibe um símbolo correspondente na matriz WS2812B
        if (isdigit(c)) ws2812b_draw(ws, NUMERIC_GLYPHS[CHAR_TO_NUM(c)], COLORS[CHAR_TO_NUM(c)], 1);
    }

    return EXIT_SUCCESS;
}

// Função para alternar o estado de um LED RGB
void toggle_led(uint gpio, bool *led_state, const char* label)
{
    // Liga ou desliga o LED correspondente
    if(!(*led_state)) rgb_turn_on_by_gpio(gpio, LED_RGB_DEFAULT_INTENSITY);
    else turn_off_led_by_gpio(gpio);

    // Exibe mensagem no console
    printf("%s\n", label);

    // Atualiza o estado do LED
    *led_state = !(*led_state);
}

// Função chamada ao pressionar um botão
void on_button_press(uint gpio, uint32_t event)
{
    // Verifica se o tempo de debounce já passou para evitar leituras erradas
    if(pb_is_debounce_delay_over())
    {
        // Se o botão do joystick foi pressionado, entra no modo BOOTSEL
        if(JOYSTICK_SW_PRESSED) set_bootsel_mode();
        
        // Se o botão A foi pressionado, alterna o LED verde
        else if(BUTTON_A_PRESSED) {
            // Define a mensagem correspondente ao estado do LED verde
            const char *green_led_msg = led_state.green_led ? "Green LED off" : "Green LED on";

            // Limpa a linha do display OLED onde a mensagem será exibida
            ssd1306_clear_line(ssd_global, OLED_LINE1);
            ssd1306_print_str(ssd_global, green_led_msg, OLED_COL1, OLED_LINE1);

            // Alterna o estado do LED verde
            toggle_led(LED_GREEN_PIN, &led_state.green_led, green_led_msg);
        } 
        
        // Se o botão B foi pressionado, alterna o LED azul
        else {
            // Define a mensagem correspondente ao estado do LED azul
            const char *blue_led_msg = led_state.blue_led ? "Blue LED off" : "Blue LED on";

            // Limpa a linha do display OLED onde a mensagem será exibida
            ssd1306_clear_line(ssd_global, OLED_LINE3);
            ssd1306_print_str(ssd_global, blue_led_msg, OLED_COL1, OLED_LINE3);

            // Alterna o estado do LED azul
            toggle_led(LED_BLUE_PIN, &led_state.blue_led, blue_led_msg);
        }
    }
}
