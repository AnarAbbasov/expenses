#ifndef curses
#define curses
#include <ncurses.h>
#include <string.h>

#include <form.h>
#include "db_functions.h"
#endif
#include <menu.h>
#include "utils.h"



#define WHITE_BLUE(window)  (wattron(window, COLOR_PAIR(1)));
#define WHITE_MAGENTA(window)  (wattron(window, COLOR_PAIR(2)));
#define WHITE_RED(window)  (wattron(window, COLOR_PAIR(3)));
#define WHITE_GREEN(window)  (wattron(window, COLOR_PAIR(4)));
#define WHITE_RED_COLOR (COLOR_PAIR(3))



MENU *menu;
WINDOW *my_window; 


void show_entry_form(WINDOW *form_window);
void display_menu(WINDOW *main_window);
void show_report_by_date_form(WINDOW *form_window);
void initialize_screen();
void create_main_window();
