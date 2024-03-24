#ifndef _MAIN_UI_H
#define _MAIN_UI_H

#include <ncurses.h>

#define MAX_ROWS_COUNT 256
#define MAX_COLS_COUNT 150

typedef enum active_page
{
    P_DEFAULT    = 0,
    P_HELP       = 1,
    P_CPU_INFO   = 2
} page_t;


void main_window();

#endif /* _MAIN_UI_H */