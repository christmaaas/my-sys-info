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
#define GRAPH_THRESHOLD_VALUE	0.5 // needs to fit accurate data to the graph conditions

#define KiB 1024.0
#define MiB (KiB * KiB)
#define SEC 10

typedef enum color_pairs
{
    PAIR_DEFAULT         = 0,
    PAIR_GREEN_BLACK     = 1,
    PAIR_BLUE_BLACK      = 2,
    PAIR_MAGENDA_BLACK   = 3,
    PAIR_BLACK_RED       = 4,
    PAIR_BLACK_GREEN     = 5,
    PAIR_BLACK_YELLOW    = 6,
    PAIR_BLACK_CYAN      = 7,
    PAIR_BLACK_WHITE     = 8,
    PAIR_BLUE_WHITE      = 9,
	PAIR_RED_WHITE       = 10,
	PAIR_GREEN_WHITE     = 11,
	PAIR_YELLOW_WHITE    = 12,
	PAIR_RED_GREEN		 = 13,
	PAIR_MAGENDA_WHITE	 = 14,
	PAIR_MAGENDA_MAGENDA = 15,
	PAIR_YELLOW_YELLOW	 = 16,
	PAIR_GREEN_GREEN	 = 17,
	PAIR_BLUE_BLUE	     = 18,
	PAIR_WHITE_BLUE	     = 19,
	PAIR_CYAN_BLUE	     = 20,
	PAIR_GREEN_BLUE	     = 21,
	PAIR_RED_BLUE	     = 22,
	PAIR_YELLOW_BLUE	 = 23,
	PAIR_BLUE_YELLOW	 = 24,
	PAIR_RED_RED		 = 25,
	PAIR_CYAN_CYAN		 = 26,
	PAIR_WHITE_RED		 = 27,
	PAIR_WHITE_CYAN		 = 28
} color_t;

#define mvwprintw_clr(win, y, x, ...) \
{ \
	mvwprintw(win, y, x, __VA_ARGS__); \
	wclrtoeol(win); \
}

#define PAGE_TITLE(page_name) \
{ \
	wattrset(main_page, COLOR_PAIR(PAIR_DEFAULT)); \
	mvprintw(0, PAGE_TITLE_OFFSET, page_name); \
	wnoutrefresh(stdscr); \
}

#endif /* _COMMON_UI_H */