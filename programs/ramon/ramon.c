#include "../../cli.h"
#include "ramon.h"
#include <string.h>
#include <stdio.h>
#include "../../size_enum.h"
#include "../../command.h"
#include <stdlib.h>

Process ramon_process = {
    .name = "ramon",
    .pid = 0x01,
};

void ramon_init()
{
    clear_screen();
    add_line_to_history("|------------------------------------------------------|");
    add_line_to_history("| RAMON RAM Monitor                                    |");
    add_line_to_history("|------------------------------------------------------|");

    active_process = ramon_process;
}

void parse_ramon_input(char *input)
{
    input[strlen(input) - 1] = '\0';
}

uint8_t peek(uint32_t address)
{
    if (address > MAX_MEMORY_ADDRESS)
    {
        // Handle error: Address out of range
        return 0; // Return zero or appropriate error value
    }
    return *(uint8_t *)address;
}

// uint32_t peek(uint32_t address)
// {
//     if (address + size > MAX_MEMORY_ADDRESS)
//     {
//         // Handle error: Address out of range
//         return 0; // Return zero or appropriate error value
//     }

//     switch (size)
//     {
//     case BYTE:
//         return *(uint8_t *)address;
//     case HALFWORD:
//         return *(uint16_t *)address;
//     case WORD:
//         return *(uint32_t *)address;
//     default:
//         // Handle error: Invalid size
//         return 0; // Return zero or appropriate error value
//     }
// }

void handleRamonCommand(char *commandName, char *args[], int argCount)
{
    printf("Handling command: %s\n", commandName);
    if (strcmp(commandName, "EXIT") == 0)
    {
        printf("Exiting process\n");
        active_process = cli_process;
        clear_screen();
        return;
    }

    if (argCount == 0)
    {
        printAndRender("");
        uint32_t address = MIN_MEMORY_ADDRESS;
        char addressString[10] = {'0', 'x', '2', '0', '0', '0', '0', '0', '0', '0'};

        if (strlen(commandName) > 6)
        {
            printAndRender("Address out of range\n");
            return;
        }

        for (int i = 0; i < strlen(commandName); i++)
        {
            addressString[i + 2 + (8 - strlen(commandName))] = commandName[i];
        }

        address = strtoul(addressString, NULL, 0);

        printf("Address: %08X\n", address);

        if (address < MIN_MEMORY_ADDRESS || address > MAX_MEMORY_ADDRESS)
        {
            printAndRender("Address out of range\n");
            return;
        }
        // uint8_t value = (uint8_t)peek(address);
        uint8_t value = *(uint8_t *)address;

        printAndRender("%08X: %02X\n", address, value);

        printf("No arguments provided - initiating peek at the address specified in the last command\n");
    }
}