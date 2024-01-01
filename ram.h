#ifndef RAM_H
#define RAM_H

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    uint16_t size;
    uint8_t *data;
} RAM;

RAM create_ram(uint16_t size);
void write_ram(RAM ram, uint16_t address, uint8_t data);
uint8_t read_ram(RAM ram, uint16_t address);

#endif // RAM_H
