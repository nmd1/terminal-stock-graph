#include "debug.h"

void graph_sin() {
    
    // Make a new display
    Display* d = new Display();

	// Create a graph with that display
	//Map sinwave(202,41,d);
    Map sinwave(202,42,d);
    sinwave.create();
    // Set max Y label sizes
    sinwave.resizeLabelY(5);
    sinwave.resizeLabelX(4);
    // Scale 
    sinwave.setExtremeY(20); // go from 1 to -1
    sinwave.setExtremeX(20); // go from 0 to 2*PI
    sinwave.autoLabelX(0, 0, 0.5);
    sinwave.autoLabelY(0, 0, 0.5);

    double max = 20;
    /*
    sinwave.setCoord(0, 0);
    sinwave.setCoord(-max, max);
    sinwave.setCoord(max, max);
    sinwave.setCoord(-max, -max);
    sinwave.setCoord(max, -max);
*/


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