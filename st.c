#include <ncurses.h>

int main() {
    initscr(); // Initialize ncurses
    noecho();  // Disable echoing of input
    cbreak();  // Disable line buffering

    // Create a window for our table
    WINDOW *table_win = newwin(10, 30, 1, 1);
    box(table_win, 0, 0); // Add a border

    // Print column headers
    mvwprintw(table_win, 1, 2, "Column 1");
    mvwprintw(table_win, 1, 15, "Column 2");

    // Print data rows
    mvwprintw(table_win, 2, 2, "Row 1");
    mvwprintw(table_win, 3, 2, "Row 2");
    mvwprintw(table_win, 4, 2, "Row 3");

    // Refresh the window
    wrefresh(table_win);

    // Wait for user input
    wgetch(table_win);

    // Clean up
    delwin(table_win);
    endwin(); // Restore terminal settings
    return 0;
}
