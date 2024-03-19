#include "main_ui.h"
#include "../logic/sys.h"

#include <ncurses.h>
#include <panel.h>
#include <stdlib.h>
#include <string.h>

#define NUM_TABS 4

// Массив названий вкладок
const char *tab_names[NUM_TABS] = {"Devices", "Stats", "Monitoring", "Info"};

// Функция для отображения верхней панели с названием программы
void display_title(int max_x) {
    attron(A_REVERSE); // Включаем реверсивный режим для фона и текста
    mvprintw(0, (max_x - 18) / 2, " My Awesome App "); // Выводим название программы по центру
    attroff(A_REVERSE); // Выключаем реверсивный режим
}

// Функция для создания вкладок в виде меню
void create_tabs(int max_x, int max_y, int current_tab_index) {
    int tab_width = max_x / NUM_TABS; // Вычисляем ширину одной вкладки

    for (int i = 0; i < NUM_TABS; ++i) {
        if (i == current_tab_index) {
            attron(A_REVERSE); // Включаем реверсивный режим для активной вкладки
        }
        mvprintw(max_y - 1, i * tab_width, "%-*s", tab_width, tab_names[i]); // Выводим название вкладки
        attroff(A_REVERSE); // Выключаем реверсивный режим
    }
}

void main_window() 
{
     // Инициализация ncurses
    initscr();
    // Включение цветового режима
    start_color();
    // Отключение отображения вводимых символов
    noecho();
    // Включение режима чтения функциональных клавиш
    keypad(stdscr, TRUE);

    // Определение цветовых пар
    init_pair(1, COLOR_WHITE, COLOR_BLUE); // Цветовая пара для панели (белый текст на синем фоне)
    init_pair(2, COLOR_BLACK, COLOR_WHITE); // Цветовая пара для основного окна (черный текст на белом фоне)

    // Получение размеров экрана
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    // Отображение названия программы
    display_title(max_x);

    // Установка начальной активной вкладки
    int current_tab_index = 0;

    // Отображение вкладок
    create_tabs(max_x, max_y, current_tab_index);

    // Ожидание выбора вкладки
    int ch;
    while ((ch = getch()) != 'q') {
        switch (ch) {
            case KEY_LEFT:
                if (current_tab_index > 0) {
                    current_tab_index--;
                }
                break;
            case KEY_RIGHT:
                if (current_tab_index < NUM_TABS - 1) {
                    current_tab_index++;
                }
                break;
            default:
                break;
        }
        // Очистка экрана перед перерисовкой
        clear();
        // Отображение названия программы
        display_title(max_x);
        // Отображение вкладок
        create_tabs(max_x, max_y, current_tab_index);
        // Обновление экрана
        refresh();
    }

    // Завершение ncurses
    endwin();
}
