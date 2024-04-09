#ifndef _MACRO_UI_H
#define _MACRO_UI_H

#include <ncurses.h>

#define MAX_ROWS_COUNT 256
#define MAX_COLS_COUNT 200

#define PAGE_TITLE_OFFSET 7

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


#endif /* _MACRO_UI_H */