#ifndef curses
#define curses
#include <ncurses.h>
#include <string.h>

#include <form.h>
#include "db_functions.h"
#endif
#include <menu.h>
#include "utils.h"

MENU *menu;
WINDOW *my_window; 


void show_entry_form(WINDOW *form_window);
void display_menu(WINDOW *main_window);
void show_report_by_date_form(WINDOW *form_window);
void initialize_screen();
void create_main_window();
