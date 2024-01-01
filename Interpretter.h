#ifndef INTERPRETTER_H
#define INTERPRETTER_H

#include "globals.h"
#include "size_enum.h"
#include <stdio.h>
#include "pico/stdlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "command.h"

#define MAX_INPUT_LENGTH 1024

// memory map
#define RAM_START 0x0000
#define RAM_SIZE 0xFFFF

#define VRAM_START 0x0

void parseAndExecuteCommand(char *input);
void handle_escape();

char *reset_buffer(char buffer[]);

#endif // INTERPRETTER_H