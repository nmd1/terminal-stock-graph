#include "debug.h"

#include <iostream>
#include <cmath>
#include <fstream>

#include "time_graph.h"

extern ofstream debugf;


void graph_sin() {
    
    // Make a new display
    Display* d = new Display();

	// Create a graph with that display
	Map sinwave(202,41,d);
    sinwave.create();
    // Set max Y label sizes
    sinwave.resizeLabelY(4);
    sinwave.resizeLabelX(5);
    // Scale 
    sinwave.setExtremeY(20); // go from 1 to -1
    sinwave.setExtremeX(20); // go from 0 to 2*PI
    sinwave.autoLabelX(0, false, 0.5);
    sinwave.autoLabelY(0, false, 0.5);

    for (double x = -20; x <= 20; x=x+0.1) {
        double y = x;
        double y2 = -x;
        sinwave.setCoord(x, y);
        sinwave.setCoord(x, y2);
        //sinwave.setLabelY(std::to_string(y), y);
        //sinwave.setLabelX(std::to_string(x), x);
        sinwave.updateScreen(false);
        usleep(1000);
    }

    sinwave.literalPrint();

    sinwave.updateScreen(true);
    d->exit();
    return;
}