#include "lite5.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "ws2812b_motion.h"
#include "ws2812b_definitions.h"

static uint8_t hash_color(uint8_t color)
{
    switch (color) {
        case 114: return 0;  // Red
        case 103: return 1;  // Green
        case 98:  return 2;  // Blue
        case 121: return 3;  // Yellow
        case 112: return 4;  // Purple
        case 119: return 6;  // White
        case 109: return 5;  // Marine
    }
}

Command parse_command(const char *input)
{
    // invalid command
    Command cmd = {.pattern = 0, .color = 0, .intensity = 0};
    if(strlen(input) > 5) return cmd;
    cmd.pattern = (input[0] - 48);
    cmd.color = hash_color(input[1]);
    cmd.intensity = atoi(&input[2]);
    return cmd;
}

void execute_command(const ws2812b_t *ws, const Command *cmd)
{
    ws2812b_motion_slide_left(ws, NUMERIC_GLYPHS[cmd->pattern], cmd->color, cmd->intensity);
}