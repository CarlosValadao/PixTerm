#include "lite5.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "ws2812b_motion.h"
#include "ws2812b_definitions.h"
#include "pico/stdlib.h"

Command last_executed_cmd = EMPTY_CMD;

static uint8_t hash_color(uint8_t color)
{
    switch (color) {
        case 'r': return 0;  // Red
        case 'g': return 1;  // Green
        case 'b':  return 2;  // Blue
        case 'y': return 3;  // Yellow
        case 'p': return 4;  // Purple
        case 'w': return 5;  // White
        case 'm': return 6;  // Marines
    }
}

Command parse_command(const char *input)
{
    // invalid command
    Command cmd = EMPTY_CMD;
    if(strlen(input) > 5) return cmd;
    cmd.pattern = (input[0] - 48);
    cmd.color = hash_color(input[1]);
    cmd.intensity = atoi(&input[2]);
    return cmd;
}


void execute_command(const ws2812b_t *ws, const Command *cmd)
{
    if(last_executed_cmd.intensity != 0) ws2812b_motion_transition(ws, &last_executed_cmd, cmd);
    else ws2812b_draw(ws, NUMERIC_GLYPHS[cmd->pattern], cmd->color, cmd->intensity);
    last_executed_cmd = *cmd;
}

bool lite5_is_empty_cmd(const Command *cmd)
{
    return (bool) (cmd->pattern != 0 && cmd->color != 0 && cmd->intensity != 0);
}