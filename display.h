#ifndef OPTIONAL_DISPLAY_H
#define OPTIONAL_DISPLAY_H

#include <ncurses.h>

namespace Optional {

class Display
{
public:
    Display();
    ~Display();

    void run_loop();

private:
    int num;
    int keypress;

    // TODO: These need to be in a structure. List/Vect?
    // Also I need to abstract a window out to a separate class.
    WINDOW* window_1;
    WINDOW* window_2;
    WINDOW* window_3;
    WINDOW* window_4;

    WINDOW *create_newwin(int height, int width, int starty, int startx);
    void destroy_win(WINDOW *local_win);
    void set_window(int window_number);
};

}

#endif
