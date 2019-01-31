#ifndef TEGAN_DISPLAY_H
#define TEGAN_DISPLAY_H

#include <ncurses.h>

namespace Tegan {

class Display
{
	public:
		Display();
		~Display();

		void run_loop();

	private:
		int num;
		int keypress;

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
