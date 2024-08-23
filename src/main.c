#include "utils/opt.h"

#include "ui/main.h"

#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>

#define MAIN_UI_FINISHED 0
#define UI_EXEC_ERROR   -2

int main(int argc, char **argv) 
{
    int opt;
    while ((opt = getopt(argc, argv, "h")) != -1) 
    {
        switch (opt) 
        {
            case 'h': { print_opt_help(); exit(0); }
            default: break;
        }
    }
    if (start_main_ui() != MAIN_UI_FINISHED)
        exit(UI_EXEC_ERROR);

    return 0;
}
