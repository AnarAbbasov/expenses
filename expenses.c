#include <ncurses.h>
#include <form.h>
#include "db_functions.c"
#include <menu.h>
WINDOW *my_window; // Rows: 10, Columns: 40, Start position: (5, 10)
MYSQL_RES *res = NULL;
MYSQL_ROW row = NULL;

void show_entry_form()
{
    FIELD *fields[2];
    fields[0] = new_field(1, 20, 2, 2, 0, 0);
    fields[1] = new_field(2, 20, 2, 2, 0, 0);
    fields[2] = NULL;
    set_field_opts(fields[0], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_back(fields[0], A_UNDERLINE);
    set_field_back(fields[1], A_UNDERLINE);
    // Display the form
    FORM *my_form = new_form(fields);

    wrefresh(my_window);
    set_form_win(my_form, my_window);
    set_form_sub(my_form, derwin(my_window, 30, 30, 2, 2));
    post_form(my_form);
}

void display_menu(WINDOW * main_window)
{
   ITEM *items[3];
    items[0] = new_item("Option 1", "Description for Option 1");
    items[1] = new_item("Option 2", "Description for Option 2");
    items[2] = NULL;

 MENU *menu = new_menu(items);

  set_menu_sub(menu,derwin(main_window, 6, 38, 3, 100));



  post_menu(menu);

    wrefresh(main_window);













}




int main()
{
    // Initialize Ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    start_color();

    // Refresh the window
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    init_pair(2, COLOR_WHITE, COLOR_MAGENTA);
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
        if (i==38)
        {break;}
    }

    // Print text inside the window

    wbkgd(my_window, COLOR_PAIR(1));
display_menu(my_window);
    wrefresh(my_window);
    // Wait for user input
  
    wgetch(my_window);

    // Clean up and end Ncurses
    delwin(my_window);
    endwin();

    return 0;
}
