#ifndef CLI_H
#define CLI_H

#include <stdint.h>

#define HISTORY_LENGTH 20
#define LINE_LENGTH 70

extern char *history[HISTORY_LENGTH];
extern char current_line[LINE_LENGTH];
extern int current_row;
extern int current_col;

void cli_init(void);

void cli_update(void);

void add_char_to_buffer(char ch);
void remove_char_from_buffer(void);
void add_buffer_to_history(void);
void add_line_to_history(char *line);

#endif // CLI_H