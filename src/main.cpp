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
	Map uses xy structs 
	Expanded point class
	------------------------------------------
	Realized Point class was an overengineered problem for 
		storing variables for the map class. I instead used structs.
		However, the point class will remain as it can be very useful to 
		store points

	--Point class now differentiates between different types of 1D coordinates
	--"using namespace std;" Removed everywhere
	--Point class has full support for integers (not well tested!)
	--Map how has xy structs to store data that has an x and y component
	

*/	