#include "display.h"
#include <ncurses.h>

Optional::Display::Display ()
    : num(0)
{
    int w1_startx, w1_starty, w1_width, w1_height;
    int w2_startx, w2_starty, w2_width, w2_height;
    int w3_startx, w3_starty, w3_width, w3_height;
    int w4_startx, w4_starty, w4_width, w4_height;

    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);
    noecho();

    if (has_colors()) {
        start_color();
        init_pair (1, COLOR_CYAN, COLOR_BLACK);
        init_pair (2, COLOR_WHITE, COLOR_BLACK);
    }

    // Window 1 (half screen, upper).
    w1_height = LINES / 2;
    w1_width  = COLS - 4;
    w1_starty = LINES - (LINES - 1);
    w1_startx = COLS - (COLS - 2);

    // Window 2 (third screen, bottom left).
    w2_height = LINES / 2 - 1;
    w2_width  = COLS / 3 - 2;
    w2_starty = LINES / 2 + 1;
    w2_startx = COLS - (COLS - 2);

    // Window 3 (third screen, bottom middle)
    w3_height = LINES / 2 - 1;
    w3_width  = COLS / 3 - 1;
    w3_starty = LINES / 2 + 1;
    w3_startx = COLS / 3 + 1;

    // Window 4 (third screen, bottom right)
    w4_height = LINES / 2 - 1;
    w4_width  = COLS / 3 - 2;
    w4_starty = LINES / 2 + 1;
    w4_startx = 2 * (COLS / 3) + 1;

    printw("   Hello. Welcome to Optional.");
    refresh();

    window_1 = Optional::Display::create_newwin(w1_height, w1_width, w1_starty, w1_startx);
    mvwprintw(window_1, 0, w1_width - 3, "W1");
    wrefresh(window_1);

    window_2 = Optional::Display::create_newwin(w2_height, w2_width, w2_starty, w2_startx);
    mvwprintw(window_2, 0, w2_width - 3, "W2");
    wrefresh(window_2);

    window_3 = Optional::Display::create_newwin(w3_height, w3_width, w3_starty, w3_startx);
    mvwprintw(window_3, 0, w3_width - 3, "W3");
    wrefresh(window_3);

    window_4 = Optional::Display::create_newwin(w4_height, w4_width, w4_starty, w4_startx);
    mvwprintw(window_4, 0, w4_width - 3, "W4");
    mvwprintw(window_4, 1, 1, "Cash & Sweep: xxx.xx");
    mvwprintw(window_4, 2, 1, "Buying Power: xxx.xx");
    mvwprintw(window_4, 3, 1, "Open P/L    : xx.xx%");
    wrefresh(window_4);
}

void Optional::Display::run_loop() {
    static int window = 0; // move to class

    // Handle user input.
    do {
        switch(this->keypress) {
            case 's':
                printw("s! ");
                break;

            case KEY_UP:
            case KEY_DOWN:
                printw("up/down! ");
                break;

            default:
                break;
        }
    }
    while((this->keypress = getch()) != 'q');
}

Optional::Display::~Display() {
    endwin();
}

WINDOW* Optional::Display::create_newwin(int height, int width, int starty, int startx)
{	WINDOW *local_win;

    local_win = newwin(height, width, starty, startx);
    box(local_win, 0 , 0);
    wrefresh(local_win);

    return local_win;
}

void Optional::Display::destroy_win(WINDOW *local_win)
{	
    wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
    wrefresh(local_win);
    delwin(local_win);
}


