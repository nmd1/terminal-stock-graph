#include "render/window.h"

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
Window Display::newWindow(int ncols, int nlines, int x0, int y0) {
    WINDOW * win = newwin(nlines, ncols, y0, x0); 
    keypad(win, TRUE); 
    int result = windows.size();
    windows.push_back(win);
    return result;
}
void Display::resize(Window window, int col, int lines) {
	wresize(windows[window], lines, col);
}
void Display::start(int& cursorx, int& cursory) {
	cursorx = 0;
	cursory = 0;
}
bool Display::next(Window window, char output, int& cursorx, int& cursory, int color_pair_color) {
	place(window, output, cursorx, cursory, color_pair_color);
	return Display::next(window, cursorx, cursory);
}
bool Display::next(Window window, int& cursorx, int& cursory) {
	int h, w;
	cursorx+=1;
	getmaxyx(windows[window], h, w);
	if(!(cursorx<w)) {
		cursorx=0;
		++cursory;
	}
	if(!(cursory<h)) {
		start(cursorx, cursory);
		return false;
	}

	return true;
}
bool Display::isValidCursor(Window window, int cursorx, int cursory) {
	int h, w;
	getmaxyx(windows[window], h, w);

	if(!(cursorx<w)) {
		return false;
	}
	if(!(cursory<h)) {
		return false;
	}

	return true;
}
void Display::place(Window window, char output, int x, int y, int color_pair_color) {
	if(!(window<(signed)windows.size())) return;
	WINDOW * win = windows[window];
   	mvwaddch(win, y, x, output | A_BOLD | COLOR_PAIR(color_pair_color)); 
}
void Display::place(Window window, std::string output, int x, int y, int color_pair_color) {
	if(!(window<(signed)windows.size())) return;
	//printw("This should be printed in black with a red background!\n");
	WINDOW * win = windows[window];
	wattron(win,COLOR_PAIR(color_pair_color));
	wmove(win, y, x);
   	waddstr(win, output.c_str()); 
}

void Display::write(Window window, char output, int x, int y, int color_pair_color) {
	Display::place(window, output, x, y, color_pair_color);
	Display::refresh(window);
}
void Display::write(Window window, std::string output, int x, int y, int color_pair_color) {
	Display::place(window, output, x, y, color_pair_color);
	Display::refresh(window);
}

void Display::refresh() {
	for(auto it = windows.begin(); it!=windows.end(); it++) {
		wrefresh(*it);
	}
}
void Display::refresh(Window win) {
	wrefresh(windows[win]);
}
void Display::debugSwitch() {
	// Let's use iterators, cause why not
	//std::vector<WINDOW*>::iterator it;
	for (auto it = windows.begin(); it != windows.end(); it++) {
    	wborder(*it, 0, 0, 0, 0, 0, 0, 0, 0);
	}
}

void Display::inputBlock(Window win) {
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
}
void Display::blockExit(Window win) {
	Display::inputBlock(win);
	Display::exit();
}
void Display::exit() {
	endwin();
}
Display::~Display() {
	endwin();
}

int Display::addMap(Maps map, Window window) {
	int result = layers.size();
	layers.push_back(std::make_tuple(map,window));
	return result;
}

void Display::draw() { for(int m = 0; m < layers.size(); m++) draw(m); }

void Display::draw(int map) {
	if(map < 0 || map >= layers.size()) return;
	auto theMap = *(std::get<_map_>(layers[map]));
	Window win = std::get<_window_>(layers[map]);
	int i = 0;
	for(auto jt = theMap.begin(); jt != theMap.end(); jt++, i++) {
		auto row = *jt;
		int j = 0;
		for(auto point = row.begin(); point != row.end(); point++, j++) {
			usleep(100);
			if(*point!='X') place(win,*point,j,i,0);
		}
	}
	refresh(win);
}