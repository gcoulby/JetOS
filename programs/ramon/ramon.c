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

uint32_t getAddress(char *commandName)
{
    char addressString[10] = {'0', 'x', '2', '0', '0', '0', '0', '0', '0', '0'};
    for (int i = 0; i < strlen(commandName); i++)
    {
        addressString[i + 2 + (8 - strlen(commandName))] = commandName[i];
    }

    return strtoul(addressString, NULL, 0);
}

void checkAddress(uint32_t address)
{
    if (address < MIN_MEMORY_ADDRESS || address > MAX_MEMORY_ADDRESS)
    {
        // Handle error: Address out of range
        return;
    }
}

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
        printAndRenderLine("");

        // if length of commandName is greater than 6 and does not contain '..' then return
        if (strlen(commandName) > 8 && strstr(commandName, "..") == NULL)
        {
            printAndRenderLine("Invalid input\n");
            return;
        }

        if (strstr(commandName, "..") != NULL)
        {
            // split string by '..'
            char *startAddressString = strtok(commandName, "..");
            char *endAddressString = strtok(NULL, "..");

            uint32_t startAddress = getAddress(startAddressString);
            uint32_t endAddress = getAddress(endAddressString);

            if (startAddress > endAddress)
            {
                printAndRenderLine("Start address must be less than end address\n");
                return;
            }
            else if (startAddress < MIN_MEMORY_ADDRESS)
            {
                printAndRenderLine("Start address out of range\n");
                return;
            }
            else if (endAddress > MAX_MEMORY_ADDRESS)
            {
                printAndRenderLine("End address out of range\n");
                return;
            }

            printAndRender("%08X:", startAddress);
            // Calculate the number of bytes to skip at the beginning
            uint32_t skipCount = startAddress % 0x10;

            // Print -- for each skipped byte
            for (uint32_t i = 0; i < skipCount; i++)
            {
                printAndRender(" --");
            }

            for (uint32_t address = startAddress; address <= endAddress; address++)
            {
                uint8_t value = *(uint8_t *)address;
                printAndRender(" %02X", value);

                if (address % 0x10 == 0x0F)
                {
                    add_buffer_to_history(false);
                    if (address != endAddress)
                    {
                        printAndRender("%08X:", address + 1);
                    }
                }
            }
            return;
        }
        else
        {
            uint32_t address = getAddress(commandName);
            checkAddress(address);
            uint8_t value = *(uint8_t *)address;
            printAndRenderLine("%08X: %02X\n", address, value);
            return;
        }
    }
}