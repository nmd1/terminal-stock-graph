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
	Directory restructuring 
	------------------------------------------
	Restructured entire src directory
	Edited Makefile to match changes
		make also only updates headers that affect specific files 
		due to implimented auto dependency generator
*/	