#ifndef _COMMON_UI_H
#define _COMMON_UI_H

#include <ncurses.h>

#define MAX_ROWS_COUNT 256
#define MAX_COLS_COUNT 200

#define PAGE_TITLE_OFFSET 7

#define GRAPH_POINT_OFFSET 	 	6
#define GRAPH_DELIM_LINE_OFFSET 4
#define GRAPH_BOTTOM_BOUND  	20
#define GRAPH_RIGHT_BOUNDARY 	8
#define GRAPH_CORRECTION		0.5

#define KB 	1024.0
#define MB 	(KB * KB)
#define SEC 10

#define PAGE(page_name) \
	{ \
		wattrset(main_page, COLOR_PAIR(0)); \
		mvprintw(0, PAGE_TITLE_OFFSET, page_name); \
		wnoutrefresh(stdscr); \
	}

#define mvwprintw_clr(win, y, x, ...) \
	{ \
		mvwprintw(win, y, x, __VA_ARGS__); \
		wclrtoeol(win); \
	}

#endif /* _COMMON_UI_H */