#ifndef _MAIN_UI_H
#define _MAIN_UI_H

#include "macro_ui.h"

typedef enum active_page
{
    P_DEFAULT          = 0,
    P_HELP             = 1,
    P_CPU_INFO         = 2,
    P_CPU_LOAD         = 3,
    P_INPUT_TIME       = 4,
    P_CPU_CORES_LOAD   = 5,
    P_MEMORY           = 6,
    P_MEMORY_LOAD      = 7
} page_t;


int start_main_ui();

#endif /* _MAIN_UI_H */