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



int main(int argc, char *argv[]) {

	signal_setup();

	// Time zone set
	tzset();

	// Set Debug ttys
	debugf.open("/dev/pts/9");
	graphwin.open("/dev/pts/10");

	//graph_sin();
	graphwin<<argc<<std::endl;
	if(argc > 1) {
		stockDraw(argv[1]);

	} else {
		stockDraw("AMD");
	}
	//stockDrawFull("AMD");
	//stockDrawWithPast("AMD",time(0));
	//stockDraw("SPY");
	//stockDraw("AMD190614C00029000");
	//stockDraw("TSLA");

	return 0;
}