#ifndef CLI_H
#define CLI_H

#include <stdint.h>
#include <stdbool.h>
#include "globals.h"

#define STACK_SIZE 41
#define HISTORY_LENGTH 41
#define LINE_LENGTH 70

extern Process cli_process;

extern char *history[HISTORY_LENGTH];
extern char current_line[LINE_LENGTH];
extern int current_row;
extern int current_col;

void cli_init(void);

void cli_update(void);

void add_char_to_buffer(char ch, bool inc);
void remove_char_from_buffer(void);
void add_buffer_to_history(void);
void add_line_to_history(char *line);
void clear_screen(void);
bool process_input();

#endif // CLI_H