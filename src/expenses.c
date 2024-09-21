#define curses
#include <ncurses.h>
#include <form.h>
#include <menu.h>
#include "../include/windows.h"
#include "db_functions.h"
#include <string.h>

// Rows: 10, Columns: 40, Start position: (5, 10)
MYSQL_RES *res = NULL;


int main()
{
    char c;
    
    initialize_screen();    
    create_main_window();         


    // Wait for user input

    while ((c = wgetch(my_window)) != 27)
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

            ITEM *cur_item = current_item(menu);
            if (strcmp(item_name(cur_item), "Get Report") == 0)
            {
                /*if report selected*/
                printf(item_name(cur_item));
                WINDOW *form_window = newwin(20, 57, 2, 80);
                box(form_window, 0, 0);
                wbkgd(form_window, COLOR_PAIR(4));
                show_report_by_date_form(form_window);
                delwin(form_window);
                touchwin(my_window);
                wrefresh(my_window);
                break;
            }
            else
            { /*if entry form selected*/
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
    }
    // Clean up and end Ncurses
    delwin(my_window);
    endwin();

    return 0;
}
