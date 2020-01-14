#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>

#include "debug.hpp"
#include "map/base.hpp"
#include "map/time.hpp"
#include "api/yahoo.hpp"
#include "render/window.hpp"
#include "signal_handler.hpp"
#include "stock/draw.hpp"
#include "log.hpp"


int main(int argc, char *argv[]) {

	signal_setup();
	// Time zone set
	tzset();

	log_setup();


	// Set Debug ttys
	debugf.open("old_debug.log");
	graphwin.open("graphwin.log");

	//graph_sin();
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