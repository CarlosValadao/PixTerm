#ifndef LITE5_H
#define LITE5_H

#include <stdint.h>

typedef struct {
    uint8_t pattern;
    uint8_t color;
    uint8_t intensity;
} Command;

Command parse_command(const char *input);
void execute_command(const Command *cmd);

#endif //LITE5_H