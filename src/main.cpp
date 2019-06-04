#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>

#include "debug.h"
#include "base_map.h"
#include "time_graph.h"
#include "yahoo_api.h"
#include "window.h"
#include "signal_handler.h"
#include "stock_draw.h"

using namespace std;

std::ofstream debugf;
std::ofstream graphwin;

int main() {

	// install our signal handlers
  	signal(SIGSEGV, segfaultbackTrace);   
    signal(SIGINT, sigintDefault);   

	// Time zone set
	tzset();

	// Set Debug ttys
  	debugf.open("/dev/pts/10");
	graphwin.open("/dev/pts/11");

	//graph_sin();
	stockDraw("AMD");
	stockDrawFull("AMD");
	//stockDrawWithPast("AMD",time(0));
	//stockDraw("SPY");
	//stockDraw("AMD190614C00029000");
	//stockDraw("TSLA");

	return 0;
}


/* Changelog
	Stocks, Live!
	------------------------------------------
	-- Wrong autolabel values for maps that had negative x/y quadrants fixed
	-- Finally changed that weird vector of tuples of time and ohlc with a vector of ohlc structs
	   Time was added as a struct value
	-- Centralized the debug file output streams declarations in the debug.h file
	-- autolabels can't assume where zero is (yet), so dummy info had to be added
	-- Stocks now continuously update!! woo! (very simplistic)
	-- stockDraw and stockDrawFull work fine
	-- stockDrawWithPast broken, which is indicative of deeper issues with the 
	-- map library that I'll be working on for the next commit 
*/	