#include "display.h"
#include <ncurses.h>

Tegan::Display::Display () 
	: num(0)
{
	WINDOW *window_1;
	WINDOW *window_2;
	WINDOW *window_3;
	WINDOW *window_4;
	
	int w1_startx, w1_starty, w1_width, w1_height;
	int w2_startx, w2_starty, w2_width, w2_height;
	int w3_startx, w3_starty, w3_width, w3_height;
	int w4_startx, w4_starty, w4_width, w4_height;
	
	initscr();
	cbreak();
	keypad(stdscr, TRUE);
	curs_set(0);

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
	
	//printw("   Hello. Welcome to Optional.");
	//mvprintw(LINES-1, 0, "   Cash & Sweep: xxx.xx | Buying Power: xxx.xx | Open P/L: xx.xx%");
	refresh();

	window_1 = Tegan::Display::create_newwin(w1_height, w1_width, w1_starty, w1_startx);
	mvwprintw(window_1, 1, 1, "W1");
	wrefresh(window_1);
	
	window_2 = Tegan::Display::create_newwin(w2_height, w2_width, w2_starty, w2_startx);
	mvwprintw(window_2, 1, 1, "W2");
	wrefresh(window_2);
	
	window_3 = Tegan::Display::create_newwin(w3_height, w3_width, w3_starty, w3_startx);
	mvwprintw(window_3, 1, 1, "W3");
	wrefresh(window_3);
	
	window_4 = Tegan::Display::create_newwin(w4_height, w4_width, w4_starty, w4_startx);
	mvwprintw(window_4, 1, 1, "W4");
	wrefresh(window_4);
}

void Tegan::Display::run_loop() {
	while((this->keypress = getch()) != 'q')
	{	
		switch(this->keypress)
		{	
			case KEY_LEFT:
				//destroy_win(my_win);
				//my_win = create_newwin(height, width, starty,--startx);
				break;
			case KEY_RIGHT:
				//destroy_win(my_win);
				//my_win = create_newwin(height, width, starty,++startx);
				break;
			case KEY_UP:
				//destroy_win(my_win);
				//my_win = create_newwin(height, width, --starty,startx);
				break;
			case KEY_DOWN:
				//destroy_win(my_win);
				//my_win = create_newwin(height, width, ++starty,startx);
				break;	
		}
	}
}

Tegan::Display::~Display() {
	endwin();
}

WINDOW* Tegan::Display::create_newwin(int height, int width, int starty, int startx)
{	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	box(local_win, 0 , 0);		/* 0, 0 gives default characters 
					 * for the vertical and horizontal
					 * lines			*/
	wrefresh(local_win);		/* Show that box 		*/

	return local_win;
}

void Tegan::Display::destroy_win(WINDOW *local_win)
{
	wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');

	wrefresh(local_win);
	delwin(local_win);
}

