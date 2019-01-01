#include "window.h"

void window::test() {
	initscr();

	// Begin the colors
	start_color();

	// Special keys
    keypad(stdscr, TRUE); 

    // Declare and create a window
    int nlines = 20;
    int ncols = 20;

    WINDOW * win = newwin(nlines, ncols, 0, 0); 
   	WINDOW * all = stdscr;

   	// Move Cursor 
   	int x = 0, y = 0;
   	wmove(win, y, x);
   	//move(x,y) 

    wborder(all, 0, 0, 0, 0, 0, 0, 0, 0);

   	// Define a new color pair
   	init_pair(1,COLOR_RED,COLOR_BLACK);
   	mvwaddch(win, y, x, ACS_VLINE | A_UNDERLINE | COLOR_PAIR(1)); 
   	
   	// Define what colors you want 
	//init_color(short n, short r, short g, short b);

   	// Refresh the screen
	wrefresh(win);

	// Sleep for a couple of seconds
	unsigned int seconds = 3;
	usleep(seconds * 1000000);
	// before leaving:
	endwin();    
	return;
}

Display::Display() : positive_color(1), negative_color(2) {
	initscr();
	start_color();
	//positive_color=1;
	//negative_color=2;
	use_default_colors();
   	init_pair(positive_color,COLOR_GREEN,-1);
   	init_pair(negative_color,COLOR_RED,-1);
   	init_pair(3,-1,-1);

   	windows.push_back(stdscr);
}
int Display::newWindow(int nlines, int ncols, int x0, int y0) {
    WINDOW * win = newwin(nlines, ncols, y0, x0); 
    keypad(win, TRUE); 
    int result = windows.size();
    windows.push_back(win);
    return result;
}
void Display::place(int window, char output, int x, int y, int color_pair_color) {
	if(!(window<(signed)windows.size())) return;
	WINDOW * win = windows[window];
   	mvwaddch(win, y, x, output | A_BOLD | COLOR_PAIR(color_pair_color)); 
}
void Display::write(int window, char output, int x, int y, int color_pair_color) {
	Display::place(window, output, x, y, color_pair_color);
	Display::refresh(window);
}

void Display::refresh() {
	for(auto it = windows.begin(); it!=windows.end(); it++) {
		wrefresh(*it);
	}
}
void Display::refresh(int win) {
	wrefresh(windows[win]);
}
void Display::debugSwitch() {
	// Let's use iterators, cause why not
	//std::vector<WINDOW*>::iterator it;
	for (auto it = windows.begin(); it != windows.end(); it++) {
    	wborder(*it, 0, 0, 0, 0, 0, 0, 0, 0);
	}
}
void Display::inputBlock(int win) {
	int ch = wgetch(windows[win]);
	switch (ch) {
		case KEY_BACKSPACE: { 
			break;
		}
		case KEY_UP: { 
			break; 
		}
		case KEY_DOWN: { 
			break; 
		}
		case KEY_ENTER:	{ 
			break;
		}
		default: {
			break;
		}
	}
	exit();
}
void Display::exit() {
	endwin();
}
Display::~Display() {
	endwin();
}