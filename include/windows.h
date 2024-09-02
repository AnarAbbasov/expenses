#ifndef curses
#define curses
#include <ncurses.h>
#include <form.h>
#include "db_functions.h"
#endif
#include <menu.h>

MENU *menu;

void show_entry_form(WINDOW *form_window);
void display_menu(WINDOW *main_window);

