#include <ncurses.h>
#include <panel.h>
#include <stdlib.h>
#include <string.h>

#define MAX_OPTIONS       11
#define MAX_OPTION_LENGTH 25

#define PAIR_WHITE_BLUE 30

#define CENTERING_DIVIDER 2.3

PANEL* create_options_panel(const int start_y, const int start_x, const int height, const int width)
{
    WINDOW* win = newwin(height, width, start_y, start_x);
    wbkgd(win, COLOR_PAIR(PAIR_WHITE_BLUE));

    box(win, 0, 0);
    wattron(win, A_BOLD);
    mvwprintw(win, 0, getmaxx(win) / CENTERING_DIVIDER, "Menu");
    wattroff(win, A_BOLD);

    PANEL* pan = new_panel(win);
    update_panels();

    return pan;
}

void draw_option(WINDOW* win, const char* option, const int index, const int selected_index) 
{
    if (index == selected_index) 
    {
        wattron(win, A_REVERSE);
        mvwprintw(win, index + 1, 1, "%s", option);
        wattroff(win, A_REVERSE);
    } 
    else
        mvwprintw(win, index + 1, 1, "%s", option);

    wrefresh(win);
}

int select_option(PANEL* pan, const char* options[], const int num_options) 
{
    int selected_index = 0;
    int ch;

    WINDOW* win = panel_window(pan);

    while (true) 
    {
        for (int i = 0; i < num_options; i++)
            draw_option(win, options[i], i, selected_index);

        ch = getch();
        switch (ch) 
        {
            case KEY_UP:
            {
                selected_index = (selected_index - 1 + num_options) % num_options;
                break;
            }
            case KEY_DOWN:
            {
                selected_index = (selected_index + 1) % num_options;
                break;
            }
            case '\n':
            {
                return selected_index;
            }
        }
    }
}

void destroy_options_panel(PANEL* pan) 
{
    WINDOW* win = panel_window(pan);
    del_panel(pan);
    delwin(win);
    update_panels();
    doupdate();
}

int select_page_menu() 
{
    noecho();
    keypad(stdscr, TRUE);
    wclear(stdscr);

    init_pair((short)PAIR_WHITE_BLUE, (short)COLOR_WHITE, (short)COLOR_BLUE);

    const char* options[MAX_OPTIONS] = 
    {
        "1. Help",
        "2. CPU Info",
        "3. CPU Total Usage",
        "4. Set Refresh time",
        "5. CPU Each Usage",
        "6. Memory Info",
        "7. Memory Usage",
        "8. Network Stats",
        "9. Generate Report",
        "10.PCI Devices Info",
        "11.Sensors Info"
    };

    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    int win_height  = MAX_OPTIONS + 2;
    int win_width   = MAX_OPTION_LENGTH + 2;
    int win_start_y = (max_y - win_height) / 2;
    int win_start_x = (max_x - win_width) / 2;

    PANEL* options_pan = create_options_panel(win_start_y, win_start_x, win_height, win_width);

    int selected_option = select_option(options_pan, options, MAX_OPTIONS);

    destroy_options_panel(options_pan);

    return selected_option;
}
