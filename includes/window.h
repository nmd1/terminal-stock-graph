#ifndef WINDOW_H
#define WINDOW_H

#include <vector>
#include <unistd.h> //for sleeping
#include <curses.h> 

namespace window {
	void test();
}

class Display {
	public:
		Display();
		// create a new window
		int newWindow(int, int, int, int);
		// turns on borders
		void debugSwitch();
		// places a char without refreshing
		void place(int, char, int, int, int=0);
		// places a char then refreshes
		void write(int, char, int, int, int=0);
		// refreshes all windows
		void refresh();
		// refreshes a specified window
		void refresh(int);
		// process input. for now just exit
		void inputBlock(int);
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