#include "globals.h"
#include "size_enum.h"
#include <stdio.h>
#include "pico/stdlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "command.h"
// #include "ram.h"
#include "Interpretter.h"

// RAM ram;

// void parseAndExecuteCommand(char *input)
// {
//     // strip the last character
//     input[strlen(input) - 1] = '\0';

//     char *args[10]; // Adjust size as needed
//     int argCount = 0;

//     // Tokenize the input string
//     char *token = strtok(input, " ");
//     char *commandName = token; // First token is the command name
//     token = strtok(NULL, " ");

//     while (token != NULL && argCount < 10)
//     {
//         args[argCount++] = token;
//         token = strtok(NULL, " ");
//     }

//     // Execute the matching command
//     for (int i = 0; i < sizeof(commands) / sizeof(Command); i++)
//     {
//         if (strcmp(commands[i].commandName, commandName) == 0)
//         {
//             handleCommand(commandName, args, argCount);
//             return;
//         }
//     }

//     if (strcmp(commandName, "") == 0)
//     {
//         return;
//     }

//     printf("\nUnknown command: %s\n", commandName);
// }

// char *reset_buffer(char buffer[])
// {
//     for (int i = 0; i < MAX_INPUT_LENGTH; i++)
//     {
//         buffer[i] = '\0';
//     }
//     return buffer;
// }

// void handle_escape()
// {
//     char ch = getchar();
//     if (ch == '[')
//     {
//         ch = getchar();
//         if (ch == 'A')
//         {
//             printf("UP\n");
//         }
//         else if (ch == 'B')
//         {
//             printf("DOWN\n");
//         }
//         else if (ch == 'C')
//         {
//             printf("RIGHT\n");
//         }
//         else if (ch == 'D')
//         {
//             printf("LEFT\n");
//         }
//         else if (ch == '2')
//         {
//             ch = getchar();

//             if (ch == '~')
//             {
//                 printf("INSERT\n");
//             }
//             else if (ch == '5')
//             {
//                 ch = getchar();
//                 if (ch == '~')
//                 {
//                     // Put this here because my push-to-talk key is F13 and it sends ESC [25~
//                 }
//             }
//         }
//         else
//         {
//             for (int i = 0; i <= 4; i++)
//             {
//                 getchar();
//             }
//             sleep_ms(10);
//         }
//     }
// }

// int main()
// {
//     stdio_init_all();

//     // create ram
//     ram = create_ram(0xFFFF);

//     // move cursor to top left
//     printf("\033[0;0H");
//     // clear screen
//     printf("\033[2J");

//     printf("|-------------------------------------|\n");
//     printf("| JetOS v0.1                          |\n");
//     printf("| (c) Graham Coulby 2023              |\n");
//     printf("|-------------------------------------|\n");
//     printf("> ");

//     char buffer[MAX_INPUT_LENGTH];

//     gpio_init(LED_PIN);
//     gpio_set_dir(LED_PIN, GPIO_OUT);
//     int index = 0;

//     while (1)
//     {
//         // Read a character as an int to handle EOF
//         int ch = getchar();

//         // Handle different types of newline characters
//         if (ch == '\n' || ch == '\r')
//         {
//             // printf("\n");
//             if (index == 0 && ch == '\n')
//             {
//                 // This handles the case where '\r' is followed by '\n'
//                 continue;
//             }

//             // Null-terminate the string
//             buffer[index] = '\0';

//             // Parse the command
//             parseAndExecuteCommand(buffer);

//             // Reset for next command
//             index = 0;
//             reset_buffer(buffer);
//             printf("\n> ");
//         }
//         else if (ch == '\b' || ch == 127)
//         {
//             // Handle backspace
//             if (index > 0)
//             {
//                 putchar('\b');
//                 putchar(' ');
//                 putchar('\b');
//                 buffer[index--] = '\0';
//             }
//         }
//         else
//         {
//             if (ch == 27)
//             {
//                 handle_escape();
//             }
//             // if valid character, add to buffer
//             else if (index < MAX_INPUT_LENGTH - 1 && ch >= 32 && ch <= 126)
//             {
//                 // Echo the character
//                 putchar(ch);
//                 // Store the character
//                 buffer[index++] = ch;
//             }
//         }
//     }
//     return 0;
// }
