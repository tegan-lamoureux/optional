#ifndef OPTIONAL_DISPLAY_H
#define OPTIONAL_DISPLAY_H

#include <ncurses.h>
#include <unordered_map>

#include "account.h"

namespace Optional {

class Display
{
public:
    Display(Account& account_in);
    ~Display();

    void run_loop();

private:
    Account& account;
    std::unordered_map<std::string, WINDOW*> windows;

    void initialize_layout_large_top_three_bottom();

    WINDOW *create_newwin(int height, int width, int starty, int startx);
    void destroy_win(WINDOW *local_win);
    void set_window(int window_number);

    void refresh_balances();
};

}

#endif
