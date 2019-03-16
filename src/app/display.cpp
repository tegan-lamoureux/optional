#include "display.h"

#include <ncurses.h>
#include <memory>

Optional::Display::Display (Account& account_in)
    : account(account_in)
{
    this->initialize_layout_large_top_three_bottom();
}

Optional::Display::~Display() {
    for (auto window : this->windows) {
        this->destroy_win(window.second);
    }

    endwin();
}

void Optional::Display::run_loop() {
    int keypress;

    // Example printing in window.
//    mvwprintw(window_4, 1, 1, "Cash & Sweep: xxx.xx");
//    mvwprintw(window_4, 2, 1, "Buying Power: xxx.xx");
//    mvwprintw(window_4, 3, 1, "Open P/L    : xx.xx%");
//    wrefresh(window_4);

    // Be nice.
    addstr("   Hello, Welcome to Optional -- Status: ");
    if (this->account.get_authorization_status() == OAuthStatus::Valid) {
        attron(COLOR_PAIR(1));
        addstr("[Connected to Brokerage Account]");
        attroff(COLOR_PAIR(1));
    }
    else {
        attron(COLOR_PAIR(3));
        addstr("[Not Connected]");
        attroff(COLOR_PAIR(3));
    }
    refresh();

    // Handle user input.
    while((keypress = getch()) != 'q')
    {
        switch(keypress) {
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

        this->refresh_balances();
    }
}

void Optional::Display::initialize_layout_large_top_three_bottom() {
    // Ncurses startup cruft.
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);
    noecho();
    timeout(500); // Blocking calls (like getch()), timeout after 500ms.

    // Make it pretty.
    if (has_colors()) {
        start_color();
        init_pair (1, COLOR_CYAN, COLOR_BLACK);
        init_pair (2, COLOR_WHITE, COLOR_BLACK);
        init_pair (3, COLOR_WHITE, COLOR_RED);
    }

    // Display setup location variables.
    // Window 1 (half screen, upper).
    int w_top_startx = COLS - (COLS - 2);
    int w_top_starty = LINES - (LINES - 1);
    int w_top_width  = COLS - 4;
    int w_top_height = LINES / 2;

    // Window 2 (third screen, bottom left).
    int w_bottom_left_startx = COLS - (COLS - 2);
    int w_bottom_left_starty = LINES / 2 + 1;
    int w_bottom_left_width  = COLS / 3 - 2;
    int w_bottom_left_height = LINES / 2 - 1;

    // Window 3 (third screen, bottom middle)
    int w_bottom_middle_startx = COLS / 3 + 1;;
    int w_bottom_middle_starty = LINES / 2 + 1;
    int w_bottom_middle_width  = COLS / 3 - 1;
    int w_bottom_middle_height = LINES / 2 - 1;

    // Window 4 (third screen, bottom right)
    int w_bottom_right_startx = 2 * (COLS / 3) + 1;
    int w_bottom_right_starty = LINES / 2 + 1;
    int w_bottom_right_width  = COLS / 3 - 2;
    int w_bottom_right_height = LINES / 2 - 1;

    refresh();

    // Actually create windows.
    this->windows.emplace("top", this->create_newwin(w_top_height, w_top_width, w_top_starty, w_top_startx));
    wrefresh(this->windows["top"]);

    this->windows.emplace("bottom left", this->create_newwin(w_bottom_left_height, w_bottom_left_width, w_bottom_left_starty, w_bottom_left_startx));
    wrefresh(this->windows["bottom left"]);

    this->windows.emplace("bottom middle", this->create_newwin(w_bottom_middle_height, w_bottom_middle_width, w_bottom_middle_starty, w_bottom_middle_startx));
    wrefresh(this->windows["bottom middle"]);

    this->windows.emplace("bottom right", this->create_newwin(w_bottom_right_height, w_bottom_right_width, w_bottom_right_starty, w_bottom_right_startx));
    wrefresh(this->windows["bottom right"]);

    refresh();
}


WINDOW* Optional::Display::create_newwin(int height, int width, int starty, int startx)
{
    WINDOW *local_win;

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

void Optional::Display::refresh_balances() {
    WINDOW* balances = this->windows["bottom right"];

    std::string available_funds = "Available Trade Funds: ";
    available_funds.append(std::to_string(this->account.current_cash_available_for_trading()));

    werase(balances);
    mvwprintw(balances, 1, 1, available_funds.c_str());
}


