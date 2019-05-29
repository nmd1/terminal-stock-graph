#ifndef WINDOW_H
#define WINDOW_H

#include <vector>
#include <unistd.h> //for sleeping
#include <curses.h> 
#include <string>

namespace window {
	void test();
}

struct point {
	double x;
	double y;
};

class Display {
	public:
		Display();
		// create a new window
		int newWindow(int, int, int, int);
		// turns on borders for all windows
		void debugSwitch();
		// places a char/string without refreshing
		void place(int, char, int, int, int=0);
		void place(int, std::string, int, int, int=0);
		// places a char/string then refreshes
		void write(int, char, int, int, int=0);
		void write(int, std::string, int, int, int=0);
		// refreshes all windows
		void refresh();
		// refreshes a specified window
		void refresh(int);
		// process input.
		void inputBlock(int);
		// starts a writer for output 
		void resize(int, int, int);
		// advances writer and places character
		void start(int&, int&);
		// resize wrapper
		bool next(int, char, int&, int&, int=0);
		// Advances writer
		bool next(int, int&, int&);
		// checks validiity of cursor
		bool isValidCursor(int, int, int);
		// will exit upon input
		void blockExit(int);
		// exit the display
		void exit();
		~Display();
		const int positive_color;
		const int negative_color;
	private:
		void run();
		std::vector<WINDOW*> windows;
};

#endif 