#include "vram.h"
#include <stdio.h>
#include <stdlib.h>

uint8_t *vram = NULL;

void alloc_vram()
{
    // allocate vram
    vram = (uint8_t *)malloc(VRAM_SIZE);
    if (vram == NULL)
    {
        printf("\nError: Could not allocate VRAM\n");
        return;
    }

    // initialize vram
    for (int i = 0; i < VRAM_SIZE; i++)
    {
        vram[i] = 0;
    }
}

void write_vram(uint8_t address, uint8_t data)
{
    if (address >= VRAM_SIZE || address < 0)
    {
        printf("\nError: Address out of range\n");
        return;
    }
    else if (vram == NULL)
    {
        printf("\nError: VRAM not allocated\n");
        return;
    }
    // write data to vram
    vram[address] = data;
}

uint8_t read_vram(uint8_t address)
{
    if (address >= VRAM_SIZE || address < 0)
    {
        printf("\nError: Address out of range\n");
        return 0;
    }
    else if (vram == NULL)
    {
        printf("\nError: VRAM not allocated\n");
        return 0;
    }
    // read data from vram
    return vram[address];
}