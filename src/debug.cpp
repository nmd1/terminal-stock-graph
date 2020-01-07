#include "debug.h"

std::ofstream debugf;
std::ofstream graphwin;

void makeStockGraph() {

}
void graph_sin()
{

    // Make a new display
    Display d;
    // Make a new window
    Window w = d.newWindow(101, 21, 0, 0);
    // Make a new map
    Window w2 = d.newWindow(101, 21, 102, 0);
    // Make a new map
    Window w3 = d.newWindow(101, 21, 0, 22);
    // Make a new map
    Window w4 = d.newWindow(101, 21, 102, 22);
    // Make a new map
    Map sinwave(100, 20, false);
    Map coswave(100, 20, true); // makes it transparent
    Map line(100, 20);
    TimeGraph parabola(100, 20);
    PositiveTimeGraph logg(96, 20);

    // Associate map with window
    int sinwaveid = d.addMap(&logg, w);
    int sinwaveid2 = d.addMap(&line, w2);
    int sinwaveid3 = d.addMap(&parabola, w3);
    int sinwaveid4 = d.addMap(&sinwave, w4);
    int sinwaveid5 = d.addMap(&coswave, w4);

    coswave.create();
    // Set max Y label sizes
    coswave.resizeLabelY(5);
    coswave.resizeLabelX(4);
    // Scale
    coswave.setExtremeY(1);        // go from 1 to -1
    coswave.setExtremeX(2 * M_PI); // go from 0 to 2*PI
    coswave.autoLabelX(0, 0, 0.5);
    coswave.autoLabelY(0, 0, 0.5);


    sinwave.create();
    // Set max Y label sizes
    sinwave.resizeLabelY(5);
    sinwave.resizeLabelX(4);
    // Scale
    sinwave.setExtremeY(1);        // go from 1 to -1
    sinwave.setExtremeX(2 * M_PI); // go from 0 to 2*PI
    sinwave.autoLabelX(0, 0, 0.5);
    sinwave.autoLabelY(0, 0, 0.5);


    parabola.create();
    // Set max Y label sizes
    parabola.resizeLabelY(5);
    parabola.resizeLabelX(4);
    // Scale
    parabola.setExtremeY(5); // go from 1 to -1
    parabola.setExtremeX(20); // go from 0 to 2*PI
    parabola.autoLabelX(0, 0, 0.5);
    parabola.autoLabelY(0, 0, 0.5);


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

    for (double x = -20; x <= 20; x = x + 0.1)
    {
        double y = x;
        double y2 = -x;
        double y3 = sin(x);
        double y4 = cos(x);
        double y5 = 4 * log(x);
        double y6 = sqrt(x);
        sinwave.setCoord(x, y3,Colors::orange_red);
        coswave.setCoord(x, y4,Colors::sky_blue);
        line.setCoord(x, y, Colors::dark_green);
        line.setCoord(x, y2, Colors::dark_red);
        logg.setCoord(x, y5, Colors::night);
        parabola.setCoord(x, y6, Colors::pink);
        parabola.setCoord(x, -y6, Colors::pink);

        //usleep(1000);
    }

    d.draw();
    d.setTitle(w,"Hello World!");

    d.marker(w);
    d.marker(w2);
    d.marker(w3);
    d.marker(w4);
    //d.inputBlock(w);

    d.exit();
    return;
}