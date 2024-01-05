#ifndef GLOBALS_H
#define GLOBALS_H

#define LED_PIN 25
#define MAX_INPUT_LENGTH 1024

#define MIN_MEMORY_ADDRESS 0x20000000
#define MAX_MEMORY_ADDRESS 0x20040000

typedef struct
{
    int pid;
    char name[100];
} Process;

extern Process active_process;

#endif