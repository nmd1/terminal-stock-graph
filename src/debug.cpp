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
	TimeGraph sinwave(200,39,d);
    sinwave.create();
    // Set max Y label sizes
    sinwave.resizeLabelY(6);
    sinwave.resizeLabelX(6);
    // Scale 
    sinwave.setExtremeY(1); // go from 1 to -1
    sinwave.setExtremeX(2*M_PI); // go from 0 to 2*PI


    for (double x = 0; x < sinwave.getMaxX(); x=x+0.01) {
        double y = sin(x);
        sinwave.setCoord(x, y);
        sinwave.setLabelY(std::to_string(y), y);
        sinwave.setLabelX(std::to_string(x), x);

    }

    debugf<<sinwave.getMaxX()<<endl;
    sinwave.literalPrint();

    sinwave.updateScreen(true);
    d->exit();
    return;
}