#include "../../cli.h"
#include "ramon.h"

Process ramon_process = {
    .name = "ramon",
    .pid = 0x01,
};

void ramon()
{
    clear_screen();
    add_line_to_history("|------------------------------------------------------|");
    add_line_to_history("| RAMON RAM Monitor                                    |");
    add_line_to_history("| Copyright (c) 2024 Graham Coulby                     |");
    add_line_to_history("|------------------------------------------------------|");
}