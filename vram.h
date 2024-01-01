#ifndef VRAM_H
#define VRAM_H

#define VRAM_SIZE 0x10000

//  0x2003FFFF - VRAM_SIZE
#define VRAM_START 0x20040000

#include <stdio.h>
#include <stdlib.h>

// VRAM ARRAY
extern uint8_t *vram;

// VRAM FUNCTIONS
void alloc_vram();
void write_vram(uint8_t address, uint8_t data);
uint8_t read_vram(uint8_t address);

#endif // VRAM_H