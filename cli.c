#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "cli.h"
#include "gfx/vec2.h"
#include "gfx/renderer.h"

#define BORDER_THICKNESS 40

char *history[HISTORY_LENGTH] = {0};
char current_line[LINE_LENGTH];
int current_row = 4;
int current_col = 0;

static void draw(void);
void write_string_to_row(char *string, int row);
void write_char_to_row(char character, int row, int col);
void write_lines(void);

void cli_init(void)
{
    // reset_game();
    renderer_init(draw);
    add_char_to_buffer('>');
    add_char_to_buffer(' ');
}

void cli_update(void)
{
    renderer_run();
    write_lines();
}

void write_string_to_row(char *string, int row)
{
    renderer_draw_string(BORDER_THICKNESS, BORDER_THICKNESS + (row * 12), 1, string, JUSTIFY_LEFT);
}

void write_char_to_row(char character, int row, int col)
{
    renderer_draw_character(BORDER_THICKNESS + (col * 10), BORDER_THICKNESS + (row * 10), 1, character);
}

void write_lines(void)
{
    for (int i = 0; i < HISTORY_LENGTH; i++)
    {
        if (history[i] != NULL && strlen(history[i]) > 0)
        {

            write_string_to_row(history[i], i);
        }
    }
}

// void add_char_to_line(char ch)
// {
//     history[current_row][current_col] = ch;
//     printf("Adding character %c to line\n", ch);
//     printf("History: %s\n", history[current_row]);
//     // current_line[current_col] = ch;
//     current_col++;
// }

void add_char_to_buffer(char ch)
{
    // Allocate or resize the current line if necessary
    if (history[current_row] == NULL)
    {
        // Allocate initial memory for the line
        history[current_row] = malloc(LINE_LENGTH);
        if (history[current_row] == NULL)
        {
            perror("Failed to allocate memory");
            return;
        }
        history[current_row][0] = '\0'; // Null-terminate the new string
    }
    else if (current_col >= LINE_LENGTH - 1)
    {
        // do not allow the line to grow beyond LINE_LENGTH
        return;
    }

    // Add the new character and null-terminate the string
    history[current_row][current_col] = ch;
    history[current_row][current_col + 1] = '\0';

    current_col++;
}

void remove_char_from_buffer(void)
{
    printf("Removing character from line\n");
    if (current_col == 0)
    {
        return;
    }
    current_col--;
    history[current_row][current_col] = '\0';
}

void add_buffer_to_history(void)
{
    printf("Adding line to history\n");
    current_row++;
    current_col = 0;
    add_char_to_buffer('>');
    add_char_to_buffer(' ');
}

void add_line_to_history(char *line)
{
    printf("Adding line to history\n");
    history[current_row] = strdup(line);
    current_row++;
    current_col = 0;
    add_char_to_buffer('>');
    add_char_to_buffer(' ');
}

void remove_line_from_history(void)
{
    printf("Removing line from history\n");
    printf("Current row: %d\n", current_row);
    free(history[current_row]);
    history[current_row] = NULL;
    current_row--;
    current_col = 0;
    if (current_row < 2)
    {
        current_row = 2;
    }
    // init current_line
    for (int i = 0; i < LINE_LENGTH; i++)
    {
        current_line[i] = '\0';
    }
}

void draw(void)
{
    write_string_to_row("|------------------------------------------------------|", 0);
    write_string_to_row("| JetOS v0.1                                           |", 1);
    write_string_to_row("| Copyright (c) 2024 Graham Coulby                     |", 2);
    write_string_to_row("|------------------------------------------------------|", 3);

    // Draw top border
    renderer_draw_rect(0, 0, renderer_screen_width, BORDER_THICKNESS);
    // Draw bottom border
    renderer_draw_rect(0, renderer_screen_height - BORDER_THICKNESS, renderer_screen_width, BORDER_THICKNESS);
    // Draw left border
    renderer_draw_rect(0, 0, BORDER_THICKNESS, renderer_screen_height);
    // Draw right border
    renderer_draw_rect(renderer_screen_width - BORDER_THICKNESS, 0, BORDER_THICKNESS, renderer_screen_height);

    // Draw history
    write_lines();

    // Draw current line
    write_string_to_row(current_line, current_row);
}