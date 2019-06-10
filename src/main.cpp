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
	Fixed the axisloc problem
	------------------------------------------
	-- There is no difference between yaxisloc and the actual
	   location of the yaxis (same with xaxisloc and xaxis)
*/	