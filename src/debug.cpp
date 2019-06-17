#include "debug.h"

void graph_sin() {
    
    // Make a new display
    Display d;
    // Make a new window
    Window w = d.newWindow(101,21,0,0);
    // Make a new map
    Window w2 = d.newWindow(101,21,101,0);
    // Make a new map
    Window w3 = d.newWindow(101,21,0,21);
    // Make a new map
    Window w4 = d.newWindow(101,21,101,21);
    // Make a new map
    Map sinwave(100,21, false);
    Map coswave(100,21, true);   // makes it transparent
    Map line(100,21);
    PositiveTimeGraph logg(100,21);

    // Associate map with window
    int sinwaveid = d.addMap(logg.getMap(), w);
    int sinwaveid2 = d.addMap(line.getMap(), w2);
    int sinwaveid3 = d.addMap(line.getMap(), w3);
    int sinwaveid4 = d.addMap(sinwave.getMap(), w4);
    int sinwaveid5 = d.addMap(coswave.getMap(), w4);

    coswave.create();
    // Set max Y label sizes
    coswave.resizeLabelY(5);
    coswave.resizeLabelX(4);
    // Scale 
    coswave.setExtremeY(1); // go from 1 to -1
    coswave.setExtremeX(2*M_PI); // go from 0 to 2*PI
    coswave.autoLabelX(0, 0, 0.5);
    coswave.autoLabelY(0, 0, 0.5);


    sinwave.create();
    // Set max Y label sizes
    sinwave.resizeLabelY(5);
    sinwave.resizeLabelX(4);
    // Scale 
    sinwave.setExtremeY(1); // go from 1 to -1
    sinwave.setExtremeX(2*M_PI); // go from 0 to 2*PI
    sinwave.autoLabelX(0, 0, 0.5);
    sinwave.autoLabelY(0, 0, 0.5);


    line.create();
    // Set max Y label sizes
    line.resizeLabelY(5);
    line.resizeLabelX(4);
    // Scale 
    line.setExtremeY(20); // go from 1 to -1
    line.setExtremeX(20); // go from 0 to 2*PI
    line.autoLabelX(0, 0, 0.5);
    line.autoLabelY(0, 0, 0.5);


    logg.create();
    // Set max Y label sizes
    logg.resizeLabelY(5);
    logg.resizeLabelX(4);
    // Scale 
    logg.setExtremeY(20); // go from 1 to -1
    logg.setExtremeX(20); // go from 0 to 2*PI
    logg.autoLabelX(0, 0, 0.5);
    logg.autoLabelY(0, 0, 0.5);

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
        double y3 = sin(x);
        double y4 = cos(x);
        double y5 = 4*log(x);

        sinwave.setCoord(x, y3);
        coswave.setCoord(x, y4);
        line.setCoord(x, y);
        line.setCoord(x, y2);
        logg.setCoord(x, y5);
        //sinwave.setLabelY(std::to_string(y), y);
        //sinwave.setLabelX(std::to_string(x), x);

        //usleep(1000);
    }

    d.draw();
    d.inputBlock(w);

    d.exit();
    return;
}