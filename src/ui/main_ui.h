#ifndef _MAIN_UI_H
#define _MAIN_UI_H

#define MAX_ROWS_COUNT 256
#define MAX_COLS_COUNT 200

typedef enum active_page
{
    P_DEFAULT          = 0,
    P_HELP             = 1,
    P_CPU_INFO         = 2,
    P_CPU_LOAD         = 3,
    P_INPUT_TIME       = 4,
    P_CPU_CORES_LOAD   = 5
} page_t;


int main_window();

#endif /* _MAIN_UI_H */