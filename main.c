#include <stdio.h>
#include "pico/stdlib.h"
#include <stdlib.h>
#include "pico/multicore.h"
#include "hardware/timer.h"
#include "hardware/gpio.h"
#include "gfx/connections.h"
#include "cli.h"
#include "Interpretter.h"
#include "programs/ramon/ramon.h"

// const char *history[64];
// int current_row = 4;
// int current_col = 0;

void core1_main()
{
  cli_init();
  while (1)
  {
    cli_update();
  }
}

int main()
{
  // Defaults: UART 0, TX pin 0, RX pin 1, baud rate 115200
  stdio_init_all();
  gpio_set_function(SERIAL_RX_PIN, GPIO_FUNC_UART);
  gpio_set_function(SERIAL_TX_PIN, GPIO_FUNC_UART);

  multicore_launch_core1(core1_main);

  while (1)
  {
    switch (active_process.pid)
    {
    case 0x00:
      if (process_input())
      {
        parseAndExecuteCommand(history[current_row - 1]);
      }
      break;
    case 0x01:
      if (process_input())
      {
        ramon();
      }
      break;
    default:
      break;
    }

    // char ch = (char)getchar();
    // printf("%c", ch);

    // if (ch == '\n' || ch == '\r' || ch == '\0')
    // {
    //   if (current_col == 0)
    //   {
    //     // This handles the case where '\r' is followed by '\n'
    //     continue;
    //   }
    //   printf("\nReturn\n");
    //   add_buffer_to_history();
    //   if (current_row > 0)
    //   {
    //     switch (active_process.pid)
    //     {
    //     case 0x00:
    //       parseAndExecuteCommand(history[current_row - 1]);
    //       break;
    //     case 0x01:
    //       ramon();
    //       // process_ramon();
    //       break;
    //     default:
    //       break;
    //     }
    //   }
    // }
    // else if (current_col > LINE_LENGTH - 3)
    // {
    //   printf("\nAuto moving to new line\n");
    //   add_buffer_to_history();
    //   add_char_to_buffer(ch, true);
    // }
    // // if backspace, remove last character from line
    // else if (ch == '\b' || ch == 127)
    // {
    //   printf("\b");
    //   remove_char_from_buffer();
    // }
    // else
    // {
    //   if (ch == 27)
    //   {
    //     handle_escape();
    //   }
    //   // if valid character, add to buffer
    //   else if (current_col < LINE_LENGTH - 1 && ch >= 32 && ch <= 126)
    //   {
    //     add_char_to_buffer(ch, true);
    //   }
    // }
  }

  return 0;
}
