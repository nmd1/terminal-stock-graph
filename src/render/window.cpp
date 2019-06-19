#include "render/window.h"

void window::test() {
	setlocale(LC_ALL, "");
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
	init_color(12, 700, 0, 0);
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

	// hide the cursor
	curs_set(0);
	start_color();
	//positive_color=1;
	//negative_color=2;
	use_default_colors();
	makeColors();

   	init_pair(positive_color,COLOR_GREEN,COLOR_TRANSPARENT);
   	init_pair(negative_color,COLOR_RED,COLOR_TRANSPARENT);

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
bool Display::isWithinBounds(Window window, int cursorx, int cursory) {
	int h, w;
	getmaxyx(windows[window], h, w);
	if(!(cursorx >= 0 && cursorx<w)) {
		return false;
	}
	if(!(cursory >= 0 && cursory<h)) {
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

std::vector<int> Display::getLayerIdsFromWindow(Window win) { 
	std::vector<int> results;
	for(int map = 0; map < layers.size(); map++) {
		Window window = std::get<_window_>(layers[map]);
		if(win == window) results.push_back(map);
	}
	return results;
}

void Display::horizontalMarker(Window win, int xstart, int yloc) {
	std::vector<int> markTheseMaps = getLayerIdsFromWindow(win);
	auto mapObject = std::get<_mapObject_>(layers[markTheseMaps[0]]);
	
	int xzero = 0;
	int yzero = 0;

	mapObject->getZeroLocation(xzero, yzero);
	int x = xstart;
	while(x > xzero) {
		x--;
		if(!mapObject->isValidPoint(x,yloc)) return;
		place(win,'_',x,yloc,Colors::light_green);
	}
	while(x < xzero) {
		x++;
		if(!mapObject->isValidPoint(x,yloc)) return;
		place(win,'_',x,yloc,Colors::light_green);
	}

	//place(win,'_',x,y,Colors::light_green);

}
void Display::verticleMarker(Window win, int xloc, int ystart) {
	std::vector<int> markTheseMaps = getLayerIdsFromWindow(win);
	auto mapObject = std::get<_mapObject_>(layers[markTheseMaps[0]]);
	
	int xzero = 0;
	int yzero = 0;

	mapObject->getZeroLocation(xzero, yzero);
	int y = ystart;
	while(y < yzero) {
		y++;
		if(!mapObject->isValidPoint(xloc,y)) return;
		place(win,'|',xloc,y,Colors::light_green);
	}
	while(y > yzero) {
		y--;
		if(!mapObject->isValidPoint(xloc,y)) return;
		place(win,'|',xloc,y,Colors::light_green);
	}

}

void Display::marker(Window win) {
	int stop = false;
	int x = 0;
	int y = 0;
	const bool getx = true;
	const bool gety = false;
	std::vector<int> markTheseMaps = getLayerIdsFromWindow(win);
	auto mObj = std::get<_mapObject_>(layers[markTheseMaps[0]]);
	mObj->getZeroLocation(x, y);
	place(win,'*',x,y,Colors::light_green);
	while(!stop) {
		refresh(win);
		int ch = wgetch(windows[win]);
		place(win,'X',x,y,Colors::light_green);

		for (auto map : markTheseMaps) {
			Display::draw(map);
		}
		switch (ch) {
			case KEY_BACKSPACE: { 
				break;
			}
			case KEY_UP: { 
				if(isWithinBounds(win,x,y-1)) y=mObj->addToCoord(gety, y,-1);
				place(win,'*',x,y,Colors::light_green);
				break; 
			}
			case KEY_DOWN: { 
				if(isWithinBounds(win,x,y+1)) y=mObj->addToCoord(gety, y,1);
				place(win,'*',x,y,Colors::light_green);
				break; 
			}
			case KEY_LEFT: {
				if(isWithinBounds(win,x-1,y)) x=mObj->addToCoord(getx, x,-1);
				place(win,'*',x,y,Colors::light_green);
				break;
			}
			case KEY_RIGHT: {
				if(isWithinBounds(win,x+1,y)) x=mObj->addToCoord(getx, x,1);
				place(win,'*',x,y,Colors::light_green);
				break;
			}
			case '\n':	{
				debugf<<"stopping "<<std::endl;
				stop = true;
				break;
			}
			default: {
				break;
			}
		}
		verticleMarker(win,x,y);
		horizontalMarker(win,x,y);

		for (auto map : markTheseMaps) {
			double valx = x;
			double valy = y;
			auto mapObj = std::get<_mapObject_>(layers[map]);
			mapObj->getRealValFromCoord(valx,valy);
			std::stringstream build;
			build<<"("<<valx<<","<<valy<<")"<<std::endl;
			setTitle(win, build.str());

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

void Display::clearLine(Window win,int yin) {
	int y, x;            // to store where you are
	getyx(windows[win], y, x); // save current pos
	move(yin, 0);          // move to begining of line
	clrtoeol();          // clear line
	move(y, x);          // move back to where you were
}

void Display::setTitle(Window win, std::string title) {
	int len = title.length();
	int max_x = windows[win]->_maxx;
	int y = windows[win]->_maxy;

	int center = (max_x+1)/2;
	int writeBegin = center - (len/2);

	clearLine(win ,y);
	place(win, title, writeBegin, y, Colors::pink);

}


int Display::addMap(Map* map, Window window) {
	int result = layers.size();
	layers.push_back(std::make_tuple(map, window));
	return result;
}

void Display::draw() { for(int m = 0; m < layers.size(); m++) draw(m); }

void Display::draw(int map) {
	int xoffset = 0;
	int yoffset = 0;
	if(map < 0 || map >= layers.size()) return;
	auto theMap = (std::get<_mapObject_>(layers[map]))->getMap();
	auto colorMap = (std::get<_mapObject_>(layers[map]))->getColorMap();

	Window win = std::get<_window_>(layers[map]);
	// First passthrough to draw initial graph
	int i = 0;
	for(auto jt = theMap->begin(); jt != theMap->end(); jt++, i++) {
		auto row = *jt;
		int j = 0;

		for(auto point = row.begin(); point != row.end(); point++, j++) {
			int x = j+xoffset;
			int y = i+yoffset;
			if(*point!='X') place(win,*point,x,y,(*colorMap)[i][j]);
		}

	}

	// Second optional passthrough for special effects
	if(false) {
		i=0;
		for(auto row : *theMap) {
			int j = 0;
			for(auto point : row) {
				int x = j+xoffset;
				int y = i+yoffset;
				if(point=='#') verticleMarker(win,x,y);
				j++;
			}
			i++;
		}
	}
	refresh(win);
}



void makeColorFromHex(Color c, int r, int g, int b) {

	double partial = r/255.0;
	r = (int) (partial*1000);
	partial = g/255.0;
	g = (int) (partial*1000);
	partial = b/255.0;
	b = (int) (partial*1000);
	init_color(c, r,g,b);
	init_pair(c, c, COLOR_TRANSPARENT);
	return;
}
void makeColors() {
    
	//init_pair(4,Colors::light_grey,COLOR_TRANSPARENT);
	//init_pair(50,7,COLOR_TRANSPARENT);

    // Reds
    makeColorFromHex(Colors::orange_red,  255,69,0);
    makeColorFromHex(Colors::dark_red,    139,0,0);
    makeColorFromHex(Colors::light_red,   240,128,128);
    makeColorFromHex(Colors::pink,  	  255,20,147);
    makeColorFromHex(Colors::light_pink, 255,192,203);

    // Greens
    makeColorFromHex(Colors::light_green, 124,252,0);
    makeColorFromHex(Colors::green,       50,205,50);
    makeColorFromHex(Colors::dark_green,  0,100,50);

    //Blues
    makeColorFromHex(Colors::night,       0,0,128);
    makeColorFromHex(Colors::sky_blue,    0,191,255);

    //Shades
    makeColorFromHex(Colors::white,       255,250,250);
    makeColorFromHex(Colors::grey,        169,169,169);
    makeColorFromHex(Colors::dark_grey,   128,128,128);
    makeColorFromHex(Colors::light_grey,  240,240,240);
    makeColorFromHex(Colors::black,       20,20,20);

/*
    A_NORMAL        Normal display (no highlight)
    A_STANDOUT      Best highlighting mode of the terminal.
    A_UNDERLINE     Underlining
    A_REVERSE       Reverse video
    A_BLINK         Blinking
    A_DIM           Half bright
    A_BOLD          Extra bright or bold
    A_PROTECT       Protected mode
    A_INVIS         Invisible or blank mode
    A_ALTCHARSET    Alternate character set
    A_CHARTEXT      Bit-mask to extract a character
    COLOR_PAIR(n)   Color-pair number n 

    COLOR_INVS   -1
    COLOR_BLACK   0
    COLOR_RED     1
    COLOR_GREEN   2
    COLOR_YELLOW  3
    COLOR_BLUE    4
    COLOR_MAGENTA 5
    COLOR_CYAN    6
    COLOR_WHITE   7

*/
}
