#ifndef WINDOW_H
#define WINDOW_H

#include <vector>
#include <unistd.h> //for sleeping
#include <curses.h> 
#include <string>
#include <sstream>
#include <tuple>

#include "render/color.h"
#include "map/base.h"
#include "debug.h"

namespace window {
	void test();
}

struct point {
	double x;
	double y;
};

typedef int Window;

void makeColors();
void makeColorFromHex(Color, int, int, int);
class Display {
	private:
		//typedef const std::vector< std::vector<char> > * Maps;
		//typedef const std::vector< std::vector<Color> > * CMaps;

	public:
		Display();
		// create a new window
		Window newWindow(int, int, int, int);
		// turns on borders for all windows
		void debugSwitch();
		// places a char/string without refreshing
		void place(Window, char, int, int, int=0);
		void place(Window, std::string, int, int, int=0);
		// places a char/string then refreshes
		void write(Window, char, int, int, int=0);
		void write(Window, std::string, int, int, int=0);
		// Draw all maps in order
		void draw();
		// Draws a specific map
		void draw(int);
		// Adds a map to this display class
		int addMap(Map*, Window);
		// refreshes all windows
		void refresh();
		// refreshes a specified window
		void refresh(Window);
		// process input.
		void inputBlock(Window);
		// starts a writer for output 
		void drawLine(Window, bool, int,int);
		// Draws a line (true for h, false for v)
		void resize(Window, int, int);
		// advances writer and places character
		void start(int&, int&);
		// resize wrapper
		bool next(Window, char, int&, int&, int=0);
		// Advances writer
		bool next(Window, int&, int&);
		// checks validiity of cursor
		bool isValidCursor(Window, int, int);
		// will exit upon input
		void blockExit(Window);
		// exit the display
		void exit();
		~Display();
		const int positive_color;
		const int negative_color;

		// Marks a point on the window. Can be controlled via keys
		void marker(Window); 
		// Gets id in the layer vector where a window is found
		std::vector<int> getLayerIdsFromWindow(Window win);
		// Checks if a point is within bounds
		bool isWithinBounds(Window , int , int);
		void horizontalMarker(Window, int, int);
		void verticleMarker(Window, int, int);
		void setTitle(Window, std::string);
		void clearLine(Window ,int );

	private:
		void run();
		// list that converts numbers back to the windows they represent
		std::vector<WINDOW*> windows;

		// Stores the references to map object's vectors
		// The window each map should be drawn in, and the color map
		std::vector<std::tuple<Map*, Window> > layers;

		// Used to determine which tuple value to get 
		enum LayerTypes {_mapObject_=0, _window_=1};
};	

#endif 