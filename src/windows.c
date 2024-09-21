#include "../include/windows.h"

/*
initialise ncurses mode and set colorpairs
-------------------------------------------
*/


void initialize_screen()
{
      initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  start_color();
  // Refresh the window
  init_pair(1, COLOR_WHITE, COLOR_BLUE);
  init_pair(2, COLOR_WHITE, COLOR_MAGENTA);
  init_pair(3, COLOR_WHITE, COLOR_RED);
  init_pair(4, COLOR_WHITE, COLOR_GREEN);
}


/*
Create Main window and print initial data
-------------------------------------------
*/

void create_main_window()
{
 my_window = newwin(39, 174, 0, 0);
 box(my_window, 0, 0); // Draw a border around the window
 res = sendquery("SELECT * FROM expenses.gas_business");
 int i = 2;
 /* Generate headers*/
 WHITE_BLUE(my_window);
 //wattron(my_window, COLOR_PAIR(2));
 mvwprintw(my_window, 1, 1, "DATE");
 mvwprintw(my_window, 1, 27, "GALLONS");
 mvwprintw(my_window, 1, 35, "PRICE/G");
 mvwprintw(my_window, 1, 45, "STORE");
 mvwprintw(my_window, 1, 75, "TRANSACTION ID");
 wattroff(my_window, COLOR_PAIR(2));
 while ((row = mysql_fetch_row(res)) != NULL)
 {
    
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
 mysql_free_result(res);
 mysql_close(conn);
 wbkgd(my_window, COLOR_PAIR(1));
 display_menu(my_window);
 wrefresh(my_window);
}


/* 
----------------------------------------------
shows alert inside desired window *mainwin,
and displays *message
-----------------------------------------------
*/
void show_alert(WINDOW *mainwin, char *message)
{
    WINDOW *mysubwin = derwin(mainwin, 10, 35, 3, 3);
    wclear(mysubwin);
    box(mysubwin, 0, 0); // Draw a box around the subwindow

    mvwprintw(mysubwin, 4, 5, message);
    wbkgd(mysubwin, COLOR_PAIR(1));
    wrefresh(mysubwin); // Refresh the subwindow to show the box
    wrefresh(mainwin);

    wgetch(mysubwin);

    delwin(mysubwin);
    // touchwin(mainwin);

    // refresh(my_window);
}






void show_entry_form(WINDOW *form_window)
{
    FIELD *fields[5];
    fields[0] = new_field(1, 20, 3, 2, 0, 0); // Label purshase date
    fields[1] = new_field(1, 20, 6, 2, 0, 0);
    fields[2] = new_field(1, 20, 9, 2, 0, 0);
    fields[3] = new_field(1, 20, 3, 29, 0, 0);
    fields[4] = NULL;
    set_field_opts(fields[0], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_back(fields[0], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_back(fields[1], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_back(fields[2], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    // Display the form
    FORM *my_form = new_form(fields);

    // set_form_sub(my_form, form_window);

    set_form_sub(my_form, derwin(form_window, 10, 55, 1, 1));
    wrefresh(form_window);
    post_form(my_form);
    mvwprintw(form_window, 3, 3, "DATE OF PURCHASE");
    mvwprintw(form_window, 6, 3, "GALLONS");
    mvwprintw(form_window, 9, 3, "PRICE/GALLON");
    mvwprintw(form_window, 3, 30, "STORE ADDRESS");
    mvwprintw(form_window, 13, 3, "PgUP/PdDn(Navigation)");
    wattron(form_window, WHITE_RED_COLOR | A_BOLD);
   

    mvwprintw(form_window, 14, 3, "Enter to insert transaction");

    wrefresh(form_window);
    keypad(form_window, TRUE);
    char ch;

    while ((ch = wgetch(form_window)) != KEY_F(1))
    {
        switch (ch)

        {
        case 82:

            /* Go to next field */

            form_driver(my_form, REQ_NEXT_FIELD);
            /* Go to the end of the present buffer */
            /* Leaves nicely at the last character */
            form_driver(my_form, REQ_END_LINE);
            break;
        case 83:
            /* Go to previous field */
            form_driver(my_form, REQ_PREV_FIELD);
            form_driver(my_form, REQ_END_LINE);
            break;
        case 10:
            /* Go to previous field */
            form_driver(my_form, REQ_END_LINE);
            if (validate_datetime(field_buffer(fields[0], 0)) == 0 && validate_number(field_buffer(fields[1], 0)) == 0 && validate_number(field_buffer(fields[2], 0)) == 0)
            {

                make_insert_data(field_buffer(fields[0], 0), field_buffer(fields[1], 0), field_buffer(fields[2], 0), field_buffer(fields[3], 0));
                add_gas_expense(sql_insert_data.Date, sql_insert_data.gallons, sql_insert_data.price, sql_insert_data.address);

                show_alert(form_window, "inserted");
                wrefresh(form_window);
                return;
            }
            // mvwprintw(form_window, 9, 13, "Please fix errors on fields!");
            else
            {
                show_alert(form_window, "errors on entrance");
                // wclear(form_window);
                return;
            }
            break;
        case 7:
            form_driver(my_form, REQ_DEL_PREV);
            break;
        case 27:
            // delwin(form_window);
            return;
        default:
            /* If this is a normal character, it gets */
            /* Printed				  */
            form_driver(my_form, ch);

            break;
        }
    }
}

void display_menu(WINDOW *main_window)
{
    ITEM *items[3];
    items[0] = new_item("Add Expense", "(Add gas expenses)");
    items[1] = new_item("Get Report", "(Get report by date)");
    items[2] = NULL;
    menu = new_menu(items);

    set_menu_sub(menu, derwin(main_window, 6, 38, 3, 100));

    post_menu(menu);

    wrefresh(main_window);
}

void show_report_by_date_form(WINDOW *form_window)
{
    FIELD *fields[3];
    fields[0] = new_field(1, 20, 3, 2, 0, 0); //
    fields[1] = new_field(1, 20, 6, 2, 0, 0);
    fields[2] = NULL;
    set_field_opts(fields[0], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);

    set_field_back(fields[1], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);

    FORM *my_form = new_form(fields);
    set_form_sub(my_form, derwin(form_window, 10, 55, 1, 1));
    wrefresh(form_window);
    post_form(my_form);
    mvwprintw(form_window, 3, 3, "DATE BEGIN");
    mvwprintw(form_window, 6, 3, "DATE END");
    mvwprintw(form_window, 14, 3, "Enter to insert transaction");
    wrefresh(form_window);
    keypad(form_window, TRUE);
    char ch;
    while ((ch = wgetch(form_window)) != KEY_F(1))
    {
        switch (ch)
        {
        case 82:
            form_driver(my_form, REQ_NEXT_FIELD);
            /* Go to the end of the present buffer */
            /* Leaves nicely at the last character */
            form_driver(my_form, REQ_END_LINE);
            break;

        case 83:
            /* Go to previous field */
            form_driver(my_form, REQ_PREV_FIELD);
            form_driver(my_form, REQ_END_LINE);
            break;
        case 7:
            form_driver(my_form, REQ_DEL_PREV);
            break;
        case 27:
            // delwin(form_window);
            return;
        
        case 10:
            /* Go to previous field */
            form_driver(my_form, REQ_END_LINE);
             if (validate_datetime(field_buffer(fields[0], 0)) == 0 && validate_datetime(field_buffer(fields[1], 0)) == 0)
             {
                 show_alert(form_window, "valid");
                 wrefresh(form_window);
             }
              else
 {
     show_alert(form_window, "errors on entrance");
     // wclear(form_window);
     return;
 }
 break;

        default:
            /* If this is a normal character, it gets
            /* Printed				  */
            form_driver(my_form, ch);
            break;
        }
    }
}