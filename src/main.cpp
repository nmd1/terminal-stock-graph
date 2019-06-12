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
#include "map/point.h"

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

	Point p(1,1);
	Point q(2,2);
	q.roundoffCoords(1);
	debugf<<(p+q)<<endl;

	//graph_sin();
	//stockDraw("AMD");
	//stockDrawFull("AMD");
	//stockDrawWithPast("AMD",time(0));
	//stockDraw("SPY");
	//stockDraw("AMD190614C00029000");
	//stockDraw("TSLA");

	return 0;
}


/* Changelog
	Point Class
	------------------------------------------
	Should make it much easier to handle coordinates
*/	