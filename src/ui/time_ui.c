#include "time_ui.h"

#include <ncurses.h>
#include <panel.h>
#include <stdlib.h>

#define MAX_INPUT_LENGTH 3

#define MAX_REFRESH_TIME     100
#define DEFAULT_REFRESH_TIME 1
#define MIN_REFRESH_TIME     0
#define CENTERING_DIVIDER    3.3

#define PAIR_BLUE_GREEN 29

#define DRAW_WIN_FRAME() \
	{ \
		box(win, 0, 0); \
		mvwprintw(win, 0, getmaxx(win) / CENTERING_DIVIDER, "Refresh Time"); \
	}

WINDOW* create_input_window(const int start_y, const int start_x, const int height, const int width) 
{
    WINDOW* win;
    win = newwin(height, width, start_y, start_x);

    wbkgd(win, COLOR_PAIR(PAIR_BLUE_GREEN));

    DRAW_WIN_FRAME(); 

    wrefresh(win);
    return win;
}

void init_color_pairs() 
{
    start_color();
    init_pair((short)PAIR_BLUE_GREEN, (short)COLOR_BLUE, (short)COLOR_GREEN);
}

PANEL* create_input_panel(WINDOW* win) 
{
    PANEL* pan;
    pan = new_panel(win);
    
    update_panels();
    return pan;
}

void destroy_input_panel(WINDOW* win, PANEL* pan) 
{
    del_panel(pan);
    delwin(win);
    update_panels();
    doupdate();
}

void draw_input_prompt(WINDOW* win) 
{
    wattron(win, A_BOLD);
    mvwprintw(win, 1, 1, "Min - 1ms | Max - 100ms");
    wattroff(win, A_BOLD);
    wrefresh(win);
}

void draw_input_field(WINDOW* win, const int input_length, char* input_buffer) 
{
    mvwprintw(win, 3, 1, "Enter ms: %s", input_buffer);
    wclrtoeol(win);
    DRAW_WIN_FRAME();
    wmove(win, 3, 11 + input_length);
    wrefresh(win);
}

int input_refresh_time() 
{
    noecho();
    keypad(stdscr, TRUE);
    wclear(stdscr);

    init_color_pairs();

    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    WINDOW* input_win = create_input_window(max_y / 2 - 2, max_x / 2 - 15, 5, 30);
    PANEL* input_pan = create_input_panel(input_win);

    char input_buffer[MAX_INPUT_LENGTH + 1] = ""; 
    int input_length = 0;

    draw_input_prompt(input_win);
    draw_input_field(input_win, input_length, input_buffer);

    int ch;
    while ((ch = getch()) != '\n') 
    {
        switch (ch) 
        {
            case KEY_BACKSPACE:
            case 127:
            {
                if (input_length > 0) {
                    input_buffer[--input_length] = '\0';
                    draw_input_field(input_win, input_length, input_buffer);
                }
                break;
            }
            default:
            {
                if (ch >= '0' && ch <= '9' && input_length < MAX_INPUT_LENGTH) {
                    input_buffer[input_length++] = ch;
                    input_buffer[input_length] = '\0';
                    draw_input_field(input_win, input_length, input_buffer);
                }
                break;
            }
        }
    }

    int refresh_time = atoi(input_buffer);

    if (refresh_time == MIN_REFRESH_TIME)
        refresh_time = DEFAULT_REFRESH_TIME; 
    else if (refresh_time > MAX_REFRESH_TIME)
        refresh_time = MAX_REFRESH_TIME;
    
    destroy_input_panel(input_win, input_pan);

    return refresh_time;
}