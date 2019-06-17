#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>

#include "debug.h"
#include "map/base.h"
#include "map/time.h"
#include "api/yahoo.h"
#include "render/window.h"
#include "signal_handler.h"
#include "stock/draw.h"

std::ofstream debugf;
std::ofstream graphwin;

int main() {

	// install our signal handlers
  	signal(SIGSEGV, segfaultbackTrace);   
    signal(SIGINT, sigintDefault);   

	// Time zone set
	tzset();

	// Set Debug ttys
	debugf.open("/dev/pts/5");
	graphwin.open("/dev/pts/10");

	graph_sin();
	//stockDraw("AMD");
	//stockDrawFull("AMD");
	//stockDrawWithPast("AMD",time(0));
	//stockDraw("SPY");
	//stockDraw("AMD190614C00029000");
	//stockDraw("TSLA");

	return 0;
}


/* Changelog
	Enhanced Display and Map integration
	------------------------------------------
	-- Maps no longer call ncurses to draw their contents; each 
		map is it's own independent entity
	-- one display object can be used to create multiple different 
	  windows
	-- Each window can be associated with a map, so that a map
	  can be drawn within a window
	-- If more than one map is associated with a single window, the 
	  new map gets layered on top of the old one(s)
	-- if more than one window is associated with a map, the map gets
	  drawn among multiple windows

*/	