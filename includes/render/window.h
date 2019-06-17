#ifndef WINDOW_H
#define WINDOW_H

#include <vector>
#include <unistd.h> //for sleeping
#include <curses.h> 
#include <string>
#include <tuple>

namespace window {
	void test();
}

struct point {
	double x;
	double y;
};

typedef int Window;

class Display {
	private:
		typedef const std::vector< std::vector<char> > *  Maps;
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
		int addMap(Maps, Window);
		// refreshes all windows
		void refresh();
		// refreshes a specified window
		void refresh(Window);
		// process input.
		void inputBlock(Window);
		// starts a writer for output 
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
	private:
		void run();
		// list that converts numbers back to the windows they represent
		std::vector<WINDOW*> windows;

		// Stores the references to map object's vectors
		// The window each map should be drawn in, and the color map
		std::vector<std::tuple<Maps, Window> > layers;

		// Used to determine which tuple value to get 
		enum LayerTypes {_map_=0, _window_=1, _color_=2};
};	

#endif 