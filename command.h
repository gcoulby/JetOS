#ifndef COMMAND_H
#define COMMAND_H

#include "size_enum.h" // Include the Size enum definition
#include "globals.h"
#include <stdint.h>

typedef struct
{
    char *commandName;
    char *helpString;
} Command;

int parseSize(char *sizeString);
// Function declarations
void ledOn();
void ledOff();
void reboot();
void poke(uint32_t address, uint32_t value, Size size);
uint32_t peek(uint32_t address, Size size);

void handleCommand(char *commandName, char *args[], int argCount);

extern Command commands[6];

#endif // COMMAND_H
