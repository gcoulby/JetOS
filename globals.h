#ifndef GLOBALS_H
#define GLOBALS_H

#define LED_PIN 25

typedef struct
{
    int pid;
    char name[100];
} Process;

extern Process active_process;

#endif