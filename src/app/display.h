#ifndef OPTIONAL_DISPLAY_H
#define OPTIONAL_DISPLAY_H

#include <ncurses.h>
#include <unordered_map>

#include "account.h"

namespace Optional {

class Window
{
public:
    Window()
        : c_window(0)
        , c_height(0)
        , c_width(0)
        , c_starty(0)
        , c_startx(0)
    {}

    Window(WINDOW* window_in, int height_in, int width_in, int starty_in, int startx_in)
        : c_window(window_in)
        , c_height(height_in)
        , c_width(width_in)
        , c_starty(starty_in)
        , c_startx(startx_in)
    {}

    WINDOW* window() { return this->c_window; }
    int startx() { return this->c_startx; }
    int starty() { return this->c_starty; }
    int width()  { return this->c_width;  }
    int height() { return this->c_height; }

private:
    //Window() = delete;

    WINDOW *c_window;
    int c_startx;
    int c_starty;
    int c_width;
    int c_height;
};

class Display
{
public:
    Display(Account& account_in);
    ~Display();

    void run_loop();

private:
    Account& account;
    std::unordered_map<std::string, Window> windows;

    void initialize_layout_large_top_three_bottom();

    WINDOW *create_newwin(int height, int width, int starty, int startx);
    void destroy_win(WINDOW *local_win);
    void set_window(int window_number);

    void clear_and_redraw_window(WINDOW* window, std::string title);

    void refresh_balances();
    void refresh_positions();
    void refresh_orders();
    void refresh_symbol();

    std::string popup_get_symbol_name();
};

}

#endif
