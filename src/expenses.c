#define curses
#include <ncurses.h>
#include <form.h>
#include <menu.h>
#include "../include/windows.h"
#include "db_functions.h"

WINDOW *my_window; // Rows: 10, Columns: 40, Start position: (5, 10)
MYSQL_RES *res = NULL;
MYSQL_ROW row = NULL;

int main()
{
    char c;
    // Initialize Ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    start_color();

    // Refresh the window
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    init_pair(2, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(3, COLOR_WHITE, COLOR_RED);
    // Create a window
    my_window = newwin(39, 174, 0, 0);
    box(my_window, 0, 0); // Draw a border around the window
    res = sendquery("SELECT * FROM expenses.gas_business");
    int i = 2;

    /* Generate headers*/
    wattron(my_window, COLOR_PAIR(2));
    mvwprintw(my_window, 1, 1, "DATE");
    mvwprintw(my_window, 1, 27, "GALLONS");
    mvwprintw(my_window, 1, 35, "PRICE/G");
    mvwprintw(my_window, 1, 45, "STORE");
    mvwprintw(my_window, 1, 75, "TRANSACTION ID");
    wattroff(my_window, COLOR_PAIR(2));
    while ((row = mysql_fetch_row(res)) != NULL)
    {
        printf("%s\n", row[1]);
        mvwprintw(my_window, i, 1, row[0]);
        mvwprintw(my_window, i, 27, row[1]);
        mvwprintw(my_window, i, 35, row[2]);
        mvwprintw(my_window, i, 45, row[3]);
        mvwprintw(my_window, i, 75, row[4]);
        i++;
        if (i == 38)
        {
            break;
        }
    }

    // Print text inside the window

    wbkgd(my_window, COLOR_PAIR(1));
    display_menu(my_window);
    wrefresh(my_window);
    // Wait for user input

    while ((c = wgetch(my_window)) != KEY_F(1))
    {
        switch (c)
        {
        case 'd':
            menu_driver(menu, REQ_DOWN_ITEM);
            break;
        case 'u':
            menu_driver(menu, REQ_UP_ITEM);
            break;

        case 10:
        /* display entry form*/
            WINDOW *form_window = newwin(20, 57, 2, 80);
            box(form_window, 0, 0);
            wbkgd(form_window, COLOR_PAIR(2));
            show_entry_form(form_window);
            delwin(form_window);
            touchwin(my_window);
            wrefresh(my_window);
            break;
        }
    }
    // Clean up and end Ncurses
    delwin(my_window);
    endwin();

    return 0;
}
