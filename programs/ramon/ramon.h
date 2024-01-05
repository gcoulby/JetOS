#ifndef RAMON_H
#define RAMON_H

#include "../../globals.h"

extern Process ramon_process;

void ramon_init();
void parse_ramon_input();
void handleRamonCommand(char *commandName, char *args[], int argCount);

#endif // RAMON_H