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
void show_entry_form(WINDOW *form_window);
void display_menu(WINDOW *main_window);

