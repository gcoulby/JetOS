#include "ram.h"
#include <stdio.h>
#include <stdlib.h>

RAM create_ram(uint16_t size)
{
    RAM ram;
    ram.size = size;
    ram.data = (uint8_t *)malloc(size);
    if (ram.data == NULL)
    {
        printf("Error allocating memory\n");
        exit(1);
    }
    // initialize vram
    for (int i = 0; i < size; i++)
    {
        ram.data[i] = 0;
    }

    return ram;
}

void write_ram(RAM ram, uint16_t address, uint8_t data)
{
    if (address >= ram.size || address < 0)
    {
        printf("\nError: Address out of range\n");
        return;
    }
    else if (ram.data == NULL)
    {
        printf("\nError: VRAM not allocated\n");
        return;
    }
    // write data to vram
    ram.data[address] = data;
}

uint8_t read_ram(RAM ram, uint16_t address)
{
    if (address >= ram.size || address < 0)
    {
        printf("\nError: Address out of range\n");
        return 0;
    }
    else if (ram.data == NULL)
    {
        printf("\nError: VRAM not allocated\n");
        return 0;
    }
    // read data from vram
    return ram.data[address];
}