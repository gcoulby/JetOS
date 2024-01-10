#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pico/stdlib.h"
#include <math.h>
#include "cli.h"
#include "gfx/vec2.h"
#include "gfx/renderer.h"
// #include "Interpretter.h"

#define BORDER_THICKNESS 40

Process cli_process = {
    .name = "idle",
    .pid = 0x00,
};

char *history[HISTORY_LENGTH] = {0};
char current_line[LINE_LENGTH];
int current_row = 0;
int current_col = 0;

static void draw(void);
void write_string_to_row(char *string, int row);
void write_char_to_row(char character, int row, int col);
void write_lines(void);

void cli_init(void)
{
    // reset_game();
    renderer_init(draw);

    add_line_to_history("|------------------------------------------------------|");
    add_line_to_history("| JetOS v0.1                                           |");
    add_line_to_history("| Copyright (c) 2024 Graham Coulby                     |");
    add_line_to_history("|------------------------------------------------------|");
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

void add_char_to_buffer(char ch, bool inc, bool includeCaret)
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

    if (inc)
    {
        current_col++;
        if (includeCaret)
        {
            add_char_to_buffer(0x80, false, false);
        }
    }
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
    add_char_to_buffer(0x80, false, true);
}

void shift_history_up(void)
{
    printf("Shifting buffer up\n");
    for (int i = 0; i < HISTORY_LENGTH - 1; i++)
    {
        history[i] = history[i + 1];
    }
    history[HISTORY_LENGTH - 1] = '\0';
    current_row--;
}

void add_buffer_to_history(bool includeCaret)
{
    printf("Adding line to history\n");
    current_row++;
    if (current_row >= HISTORY_LENGTH)
    {
        shift_history_up();
    }
    current_col = 0;
    if (includeCaret)
    {
        add_char_to_buffer(0x80, false, true);
    }
}

void add_line_to_history(char *line)
{
    printf("Adding line to history\n");
    history[current_row] = strdup(line);
    current_row++;
    if (current_row >= HISTORY_LENGTH)
    {
        shift_history_up();
    }

    current_col = 0;
    add_char_to_buffer(0x80, false, true);
}

void add_to_history(char *text)
{
    printf("Adding each char to history\n");
    for (int i = 0; i < strlen(text); i++)
    {
        add_char_to_buffer(text[i], true, false);
    }
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

void clear_screen(void)
{
    printf("Clearing history\n");
    for (int i = 0; i < HISTORY_LENGTH; i++)
    {
        if (history[i] != NULL)
        {
            free(history[i]);
            history[i] = NULL;
        }
    }
    current_row = 0;
    current_col = 0;
    // init current_line
    for (int i = 0; i < LINE_LENGTH; i++)
    {
        current_line[i] = '\0';
    }
    add_char_to_buffer(0x80, false, true);
}

void draw(void)
{
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

bool process_input()
{
    char ch = (char)getchar();
    printf("%c", ch);

    if (ch == '\n' || ch == '\r' || ch == '\0')
    {
        if (current_col == 0)
        {
            // This handles the case where '\r' is followed by '\n'
            return false;
        }
        printf("\nReturn\n");
        add_buffer_to_history(true);
        if (current_row > 0)
        {
            return true;
        }
    }
    else if (current_col > LINE_LENGTH - 3)
    {
        printf("\nAuto moving to new line\n");
        add_buffer_to_history(true);
        add_char_to_buffer(ch, true, true);
    }
    // if backspace, remove last character from line
    else if (ch == '\b' || ch == 127)
    {
        printf("\b");
        remove_char_from_buffer();
    }
    else
    {
        if (ch == 27)
        {
            handle_escape();
        }
        // if valid character, add to buffer
        else if (current_col < LINE_LENGTH - 1 && ch >= 32 && ch <= 126)
        {
            add_char_to_buffer(ch, true, true);
        }
    }
    return false;
}

char *reset_buffer(char buffer[])
{
    for (int i = 0; i < MAX_INPUT_LENGTH; i++)
    {
        buffer[i] = '\0';
    }
    return buffer;
}

void handle_escape()
{
    char ch = getchar();
    if (ch == '[')
    {
        ch = getchar();
        if (ch == 'A')
        {
            printf("UP\n");
        }
        else if (ch == 'B')
        {
            printf("DOWN\n");
        }
        else if (ch == 'C')
        {
            printf("RIGHT\n");
        }
        else if (ch == 'D')
        {
            printf("LEFT\n");
        }
        else if (ch == '2')
        {
            ch = getchar();

            if (ch == '~')
            {
                printf("INSERT\n");
            }
            else if (ch == '5')
            {
                ch = getchar();
                if (ch == '~')
                {
                    // Put this here because my push-to-talk key is F13 and it sends ESC [25~
                }
            }
        }
        else
        {
            for (int i = 0; i <= 4; i++)
            {
                getchar();
            }
            sleep_ms(10);
        }
    }
}