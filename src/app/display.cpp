#include "display.h"

#include <ncurses.h>
#include <memory>

Optional::Display::Display (Account& account_in)
    : account(account_in)
{
    this->initialize_layout_large_top_three_bottom();
}

Optional::Display::~Display() {
    for (auto it : this->windows) {
        this->destroy_win(it.second.window());
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
    addstr("   Hello, Welcome to ");
    attron(COLOR_PAIR(5));
    addstr("Optional");
    attroff(COLOR_PAIR(5));
    addstr("-- Status: ");
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

    if (this->account.refresh_account()) {
        this->refresh_balances();
    }

    // Handle user input.
    do {
        switch(keypress) {
            case 'r':
                if (this->account.refresh_account()) {
                    this->refresh_balances();
                }
                break;

            case KEY_UP:
            case KEY_DOWN:
                printw("up/down! ");
                break;

            default:
                break;
        }
    }
    while((keypress = getch()) != 'q');
}

void Optional::Display::initialize_layout_large_top_three_bottom() {
    // Ncurses startup cruft.
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);
    noecho();
    timeout(100); // Blocking calls (like getch()), timeout after 100ms.

    // Make it pretty.
    if (has_colors()) {
        start_color();
        init_pair (1, COLOR_CYAN, COLOR_BLACK);
        init_pair (2, COLOR_WHITE, COLOR_BLACK);
        init_pair (3, COLOR_WHITE, COLOR_RED);
        init_pair (4, COLOR_GREEN, COLOR_BLACK);
        init_pair (5, COLOR_MAGENTA, COLOR_BLACK);
    }

    refresh();

    // Window 1 (half screen, upper).
    int w_top_startx = COLS - (COLS - 2);
    int w_top_starty = LINES - (LINES - 1);
    int w_top_width  = COLS - 4;
    int w_top_height = LINES / 2;

    Window top(this->create_newwin(w_top_height, w_top_width, w_top_starty, w_top_startx),
           w_top_height,
           w_top_width,
           w_top_starty,
           w_top_startx);
    this->windows.emplace("top", top);

    wattron(top.window(), A_BOLD);
    wattron(top.window(), COLOR_PAIR(5));
    mvwprintw(top.window(), 1, 1, "Symbol Information & Option Chains");
    wattroff(top.window(), A_BOLD);
    wattroff(top.window(), COLOR_PAIR(5));
    wrefresh(this->windows["top"].window());


    // Window 2 (third screen, bottom left).
    int w_bottom_left_startx = COLS - (COLS - 2);
    int w_bottom_left_starty = LINES / 2 + 1;
    int w_bottom_left_width  = COLS / 3 - 2;
    int w_bottom_left_height = LINES / 2 - 1;

    Window bottom_left(this->create_newwin(w_bottom_left_height, w_bottom_left_width, w_bottom_left_starty, w_bottom_left_startx),
           w_bottom_left_height,
           w_bottom_left_width,
           w_bottom_left_starty,
           w_bottom_left_startx);
    this->windows.emplace("bottom left", bottom_left);

    wattron(bottom_left.window(), A_BOLD);
    wattron(bottom_left.window(), COLOR_PAIR(5));
    mvwprintw(bottom_left.window(), 1, 1, "Orders");
    wattroff(bottom_left.window(), A_BOLD);
    wattroff(bottom_left.window(), COLOR_PAIR(5));
    wrefresh(this->windows["bottom left"].window());


    // Window 3 (third screen, bottom middle)
    int w_bottom_middle_startx = COLS / 3 + 1;;
    int w_bottom_middle_starty = LINES / 2 + 1;
    int w_bottom_middle_width  = COLS / 3 - 1;
    int w_bottom_middle_height = LINES / 2 - 1;

    Window bottom_middle(this->create_newwin(w_bottom_middle_height, w_bottom_middle_width, w_bottom_middle_starty, w_bottom_middle_startx),
           w_bottom_middle_height,
           w_bottom_middle_width,
           w_bottom_middle_starty,
           w_bottom_middle_startx);
    this->windows.emplace("bottom middle", bottom_middle);

    wattron(bottom_middle.window(), A_BOLD);
    wattron(bottom_middle.window(), COLOR_PAIR(5));
    mvwprintw(bottom_middle.window(), 1, 1, "Positions");
    wattroff(bottom_middle.window(), A_BOLD);
    wattroff(bottom_middle.window(), COLOR_PAIR(5));
    wrefresh(this->windows["bottom middle"].window());


    // Window 4 (third screen, bottom right)
    int w_bottom_right_startx = 2 * (COLS / 3) + 1;
    int w_bottom_right_starty = LINES / 2 + 1;
    int w_bottom_right_width  = COLS / 3 - 2;
    int w_bottom_right_height = LINES / 2 - 1;

    Window bottom_right(this->create_newwin(w_bottom_right_height, w_bottom_right_width, w_bottom_right_starty, w_bottom_right_startx),
           w_bottom_right_height,
           w_bottom_right_width,
           w_bottom_right_starty,
           w_bottom_right_startx);
    this->windows.emplace("bottom right", bottom_right);
    wrefresh(this->windows["bottom right"].window());

    refresh();
}


WINDOW* Optional::Display::create_newwin(int height, int width, int starty, int startx) {
    WINDOW *local_win;

    local_win = newwin(height, width, starty, startx);
    box(local_win, 0 , 0);
    wrefresh(local_win);

    return local_win;
}

void Optional::Display::destroy_win(WINDOW *window) {
    wborder(window, ' ', ' ', ' ',' ',' ',' ',' ',' ');
    wrefresh(window);
    delwin(window);
}

void Optional::Display::clear_and_redraw_window(WINDOW *window) {
    werase(window);
    box(window, 0, 0);
    wrefresh(window);
}

void Optional::Display::refresh_balances() {
    WINDOW* balances = this->windows["bottom right"].window();
    int width = this->windows["bottom right"].width();
    int height = this->windows["bottom right"].height();

    clear_and_redraw_window(balances);

    wattron(balances, A_BOLD);
    wattron(balances, COLOR_PAIR(5));
    mvwprintw(balances, 1, 1, "Margin Account Balances");
    wattroff(balances, A_BOLD);
    wattroff(balances, COLOR_PAIR(5));

    std::string available_funds = std::to_string(this->account.initial_available_funds_non_marginable_trade());
    std::string stock_buying_power = (std::to_string(this->account.initial_buying_power()));
    std::string options_buying_power = (std::to_string(this->account.initial_cash_balance()));
    std::string long_stock = (std::to_string(this->account.initial_long_stock_value()));
    std::string maint_requirement = (std::to_string(this->account.initial_maintenance_requirement()));
    std::string margin_balance = (std::to_string(this->account.initial_margin()));
    std::string margin_equity = (std::to_string(this->account.initial_margin_equity()));
    std::string net_liquid = (std::to_string(this->account.initial_liquidation_value()));


    mvwprintw(balances, 3, 1, "Options Buying Power: ");
    mvwprintw(balances, 4, 1, "Stock Buying Power");
    mvwprintw(balances, 5, 1, "Cash & Sweep");
    mvwprintw(balances, 6, 1, "Long Stock Value");
    mvwprintw(balances, 7, 1, "Maitenance Requirement");
    mvwprintw(balances, 8, 1, "Margin Balance");
    mvwprintw(balances, 9, 1, "Margin Equity");
    mvwprintw(balances, height - 2, 1, "Net Liquidating Value");

    wattron(balances, COLOR_PAIR(4));
    mvwprintw(balances, 3, width - 1 - available_funds.length(), available_funds.c_str());
    mvwprintw(balances, 4, width - 1 - stock_buying_power.length(), stock_buying_power.c_str());
    mvwprintw(balances, 5, width - 1 - options_buying_power.length(), options_buying_power.c_str());
    mvwprintw(balances, 6, width - 1 - long_stock.length(), long_stock.c_str());
    mvwprintw(balances, 7, width - 1 - maint_requirement.length(), maint_requirement.c_str());
    mvwprintw(balances, 8, width - 1 - margin_balance.length(), margin_balance.c_str());
    mvwprintw(balances, 9, width - 1 - margin_equity.length(), margin_equity.c_str());
    mvwprintw(balances, height - 2, width - 1 - net_liquid.length(), net_liquid.c_str());
    wattroff(balances, COLOR_PAIR(4));

    wrefresh(balances);
}


