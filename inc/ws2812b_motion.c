#include "ws2812b_motion.h"
#include "ws2812b.h"
#include "ws2812b_definitions.h"
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include <string.h>
#include <stdlib.h>


static void fliplr(uint8_t *glyph) {
    uint8_t temp;
    temp = glyph[5];
    glyph[5] = glyph[9]; glyph[9] = temp;
    temp = glyph[6];
    glyph[6] = glyph[8]; glyph[8] = temp;
    temp = glyph[15];
    glyph[15] = glyph[19]; glyph[19] = temp;
    temp = glyph[16];
    glyph[16] = glyph[18]; glyph[18] = temp;
}

static void right_shift(uint8_t *arr)
{
    uint8_t i;
    for(i = 4; i > 0; i--) arr[i] = arr[i-1];
    arr[0] = 0;
}

static void left_shift(uint8_t *arr)
{
    uint8_t i;
    for(i = 0; i < 4; i++) arr[i] = arr[i+1];
    arr[4] = 0;
}

// realiza a transposta de arr, sendo ele um array
// de 25 posicoes (5x5)
static void transpose(uint8_t *arr)
{
    uint8_t temp;
    uint8_t i;
    uint8_t j;
    for(i = 0; i < 5; i++)
    {
        for(j=i+1; j < 5; j++)
        {
            temp = arr[i * 5 + j];
            arr[i * 5 + j] = arr[j * 5 + i];
            arr[j * 5 + i] = temp;
        }
    }
}

void ws2812b_motion_shift_left(uint8_t *glyph, uint8_t *shifted_glyph)
{
    uint8_t i;
    memcpy(shifted_glyph, glyph, 25 * sizeof(uint8_t));
    fliplr(shifted_glyph);
    for(i = 0; i < 5; i++) left_shift(&(shifted_glyph[5 * i]));
    fliplr(shifted_glyph);
}

void ws2812b_motion_shift_right(uint8_t *glyph, uint8_t *shifted_glyph)
{
    uint8_t i;
    memcpy(shifted_glyph, glyph, 25 * sizeof(uint8_t));
    fliplr(shifted_glyph);
    for(i = 0; i < 5; i++) right_shift(&(shifted_glyph[5 * i]));
    fliplr(shifted_glyph);
}


void ws2812b_motion_slide_left(const ws2812b_t *ws, const uint8_t *glyph, uint8_t color, uint8_t intensity)
{
    uint8_t i;
    uint8_t *shifted_glyph = malloc(25 * sizeof(uint8_t));
    uint8_t *aux_glyph = malloc(25 * sizeof(uint8_t));
    memcpy(aux_glyph, glyph, 25 * sizeof(uint8_t));
    ws2812b_draw(ws, glyph, color, intensity);
    sleep_ms(500);
    //ws2812b_turn_off_all(ws);
    sleep_ms(50);
    for(i = 0; i < 4; i++)
    {
        ws2812b_motion_shift_left(aux_glyph, shifted_glyph);
        ws2812b_draw(ws, shifted_glyph, color, intensity);
        memcpy(aux_glyph, shifted_glyph, 25 * sizeof(uint8_t));
        sleep_ms(500);
        //ws2812b_turn_off_all(ws);
        sleep_ms(50);
    }
    sleep_ms(20);
    ws2812b_draw(ws, glyph, color, intensity);
    sleep_ms(200);
    free(shifted_glyph);
    free(aux_glyph);
}

void ws2812b_motion_slide_right(const ws2812b_t *ws, const uint8_t *glyph, uint8_t color, uint8_t intensity)
{
    uint8_t i;
    uint8_t *shifted_glyph = malloc(25 * sizeof(uint8_t));
    uint8_t *aux_glyph = malloc(25 * sizeof(uint8_t));
    memcpy(aux_glyph, glyph, 25 * sizeof(uint8_t));
    ws2812b_draw(ws, glyph, color, intensity);
    sleep_ms(500);
    //ws2812b_turn_off_all(ws);
    sleep_ms(50);
    for(i = 0; i < 4; i++)
    {
        ws2812b_motion_shift_right(aux_glyph, shifted_glyph);
        ws2812b_draw(ws, shifted_glyph, color, intensity);
        memcpy(aux_glyph, shifted_glyph, 25 * sizeof(uint8_t));
        sleep_ms(500);
        //ws2812b_turn_off_all(ws);
        sleep_ms(50);
    }
    sleep_ms(20);
    ws2812b_draw(ws, glyph, color, intensity);
    sleep_ms(200);
    free(shifted_glyph);
    free(aux_glyph);
}
