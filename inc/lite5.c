#include "lite5.h"
#include <string.h>
#include <stdlib.h>

Command parse_command(const char *input)
{
    // invalid command
    Command cmd = {.pattern = 0, .color = 0, .intensity = 0};
    if(strlen(input) > 5) return cmd;
    cmd.pattern = input[0];
    cmd.color = input[1];
    cmd.intensity = atoi(&input[2]);
    return cmd;
}

void execute_command(const Command *cmd)
{
    return; //TO DO
}