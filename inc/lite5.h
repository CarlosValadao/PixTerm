#ifndef LITE5_H
#define LITE5_H

#include <stdint.h>
#include "ws2812b.h"


typedef struct {
    uint8_t pattern;
    uint8_t color;
    uint8_t intensity;
} Command;

extern Command last_executed_cmd;

Command parse_command(const char *input);
void execute_command(const ws2812b_t *ws, const Command *cmd);

#endif //LITE5_H