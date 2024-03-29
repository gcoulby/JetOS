#include "command.h"
#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "pico/bootrom.h"
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include "vram.h"
#include "cli.h"
#include "programs/ramon/ramon.h"

Command commands[] = {
    {"ON", "Turns the LED on"},
    {"OFF", "Turns the LED off"},
    {"REBOOT", "Boots the device into programming mode"},
    {"HELP", "Prints this help message"},
    {"WRITE_VRAM", "Writes a byte to the VRAM"},
    {"READ_VRAM", "Reads a byte from the VRAM"},
    {"RAMON", "Starts the memory monitor"},
    {"CLEAR", "Clears the screen"},
    {"EXIT", "Exits the current process"}
    // Add more commands as needed
};

void cleanString(char *string)
{
    for (int i = 0; i < strlen(string); i++)
    {
        if (string[i] == '\n')
        {
            string[i] = '\0';
            return;
        }
    }
}

void printAndRenderLine(char *format, ...)
{
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    char buffer[1024];
    vsprintf(buffer, format, args);
    cleanString(buffer);
    add_line_to_history(buffer);
}

void printAndRender(char *format, ...)
{
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    char buffer[1024];
    vsprintf(buffer, format, args);
    cleanString(buffer);
    add_to_history(buffer);
}

void printHelp()
{
    printAndRenderLine("Available commands:\n");
    for (int i = 0; i < sizeof(commands) / sizeof(Command); i++)
    {
        printAndRenderLine("%s: %s\n", commands[i].commandName, commands[i].helpString);
    }
}

void ledOn()
{
    printAndRenderLine("Turning LED on\n");
    gpio_put(LED_PIN, 1);
}

void ledOff()
{
    printAndRenderLine("Turning LED off\n");
    gpio_put(LED_PIN, 0);
}

void reboot()
{
    printAndRenderLine("Booting device into programming mode\n");
    reset_usb_boot(0, 0);
}

void poke(uint32_t address, uint32_t value, Size size)
{
    if (address + size > MAX_MEMORY_ADDRESS)
    {
        // Handle error: Address out of range
        return;
    }

    switch (size)
    {
    case BYTE:
        *(uint8_t *)address = (uint8_t)value;
        break;
    case HALFWORD:
        *(uint16_t *)address = (uint16_t)value;
        break;
    case WORD:
        *(uint32_t *)address = value;
        break;
    default:
        // Handle error: Invalid size
        break;
    }
}

int parseSize(char *sizeString)
{
    if (strcmp(sizeString, "BYTE") == 0)
    {
        return BYTE;
    }
    else if (strcmp(sizeString, "HALFWORD") == 0)
    {
        return HALFWORD;
    }
    else if (strcmp(sizeString, "WORD") == 0)
    {
        return WORD;
    }
    else
    {
        // Handle error: Invalid size
        return 0; // Return zero or appropriate error value
    }
}

void handleCommand(char *commandName, char *args[], int argCount)
{
    if (strcmp(commandName, "HELP") == 0)
    {
        printHelp();
    }
    else if (strcmp(commandName, "CLEAR") == 0)
    {
        clear_screen();
    }
    else if (strcmp(commandName, "ON") == 0)
    {
        ledOn();
    }
    else if (strcmp(commandName, "OFF") == 0)
    {
        ledOff();
    }
    else if (strcmp(commandName, "REBOOT") == 0)
    {
        reboot();
    }
    // else if (strcmp(commandName, "POKE") == 0)
    // {
    //     if (argCount >= 3)
    //     {
    //         // Parse size from args[0]
    //         Size size = parseSize(args[0]);
    //         uint32_t address = strtoul(args[1], NULL, 0);
    //         uint32_t value = strtoul(args[2], NULL, 0);
    //         poke(address, value, size);
    //         printAndRender("Wrote value %08X to address %08X\n", value, address);
    //     }
    //     else
    //     {
    //         printAndRender("Insufficient arguments for POKE\n");
    //     }
    // }
    // else if (strcmp(commandName, "PEEK") == 0)
    // {
    //     if (argCount >= 2)
    //     {
    //         // Parse size from args[0]
    //         Size size = parseSize(args[0]);
    //         uint32_t address = strtoul(args[1], NULL, 0);
    //         uint32_t value = peek(address, size);
    //         printAndRender("Value at address %08X: %08X\n", address, value);
    //     }
    //     else
    //     {
    //         printAndRender("Insufficient arguments for PEEK\n");
    //     }
    // }
    else if (strcmp(commandName, "WRITE_RAM") == 0)
    {
        if (argCount >= 2)
        {
            uint16_t address = strtoul(args[0], NULL, 0);
            uint8_t value = strtoul(args[1], NULL, 0);
            write_vram(address, value);
            printAndRenderLine("Wrote value %08X to address %08X\n", value, address);
        }
        else
        {
            printAndRenderLine("Insufficient arguments for WRITE_VRAM\n");
        }
    }
    else if (strcmp(commandName, "READ_RAM") == 0)
    {
        if (argCount >= 1)
        {
            uint16_t address = strtoul(args[0], NULL, 0);
            uint8_t value = read_vram(address);
            printAndRenderLine("Value at address %08X: %08X\n", address, value);
        }
        else
        {
            printAndRenderLine("Insufficient arguments for READ_VRAM\n");
        }
    }
    else if (strcmp(commandName, "RAMON") == 0)
    {
        printAndRenderLine("Starting memory monitor\n");
        // active_process = ramon_process;
        // ramon();
        ramon_init();
    }
    else if (strcmp(commandName, "EXIT") == 0)
    {
        printAndRenderLine("Exiting process\n");
        active_process = cli_process;
        clear_screen();
    }
    else
    {
        printAndRenderLine("Unknown command\n");
    }
    // Add more commands as needed
}

CommandWithArgs parseCommand(char *input)
{
    // strip the last character
    input[strlen(input) - 1] = '\0';

    char *args[20]; // Adjust size as needed
    int argCount = 0;

    // Tokenize the input string
    char *token = strtok(input, " ");
    char *commandName = token; // First token is the command name
    token = strtok(NULL, " ");

    while (token != NULL && argCount < 10)
    {
        args[argCount++] = token;
        token = strtok(NULL, " ");
    }

    // Execute the matching command
    for (int i = 0; i < sizeof(commands) / sizeof(Command); i++)
    {
        if (strcmp(commands[i].commandName, commandName) == 0)
        {
            CommandWithArgs commandWithArgs = {
                .commandName = commands[i].commandName,
                .args = args,
                .argCount = argCount,
                .registered = true,
            };
            return commandWithArgs;
            // handleCommand(commandName, args, argCount);
            // return;
        }
    }

    // if (strcmp(commandName, "") == 0)
    // {
    // }
    printf("\nUnknown command: %s\n", commandName);

    return (CommandWithArgs){
        .commandName = commandName,
        .args = args,
        .argCount = argCount,
        .registered = false,
    };
}