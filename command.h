#ifndef COMMAND_H
#define COMMAND_H

#include "size_enum.h" // Include the Size enum definition
#include "globals.h"
#include <stdint.h>
#include <stdbool.h>

#define COMMAND_COUNT 9

typedef struct
{
    char *commandName;
    char *helpString;
} Command;

typedef struct
{
    char *commandName;
    char *args[20];
    int argCount;
    bool registered;
    // void (*function)(char *args[], int argCount);
} CommandWithArgs;

int parseSize(char *sizeString);
// Function declarations
void ledOn();
void ledOff();
void reboot();
void poke(uint32_t address, uint32_t value, Size size);

void printAndRender(char *format, ...);

CommandWithArgs parseCommand(char *input);
void handleCommand(char *commandName, char *args[], int argCount);

extern Command commands[COMMAND_COUNT];

#endif // COMMAND_H
