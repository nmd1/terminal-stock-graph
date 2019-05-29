#include "time_graph.h"
#include "base_map.h"


/******************* Maximum and minimum values on a graph  *******************/
double Map::getMaxX(bool real) {
    return real ? maxxval : length - 1;
}
double Map::getMinX(bool real) {
    return real ? minxval : 0;
}
double Map::getMaxY(bool real) {
    return real ? maxyval : 0;
}
double Map::getMinY(bool real) {
    return real ? minyval : width - 1;
}

double Map::getMaxX() { return Map::getMaxX(true); }
double Map::getMinX() { return Map::getMinX(true); }
double Map::getMaxY() { return Map::getMaxY(true); }
double Map::getMinY() { return Map::getMinY(true); }

//////////////////////////////////////

double TimeGraph::getMinX(bool real) {
    return real ? 0 : ylabelsize;
}
double TimeGraph::getMinX() { return TimeGraph::getMinX(true); }

//////////////////////////////////////

double PositiveTimeGraph::getMinY(bool real) {
	return real ? 0 : width-2;
}
double PositiveTimeGraph::getMinY() { return PositiveTimeGraph::getMinY(true); }

////////////////////////////////////
/*
double NegativeTimeGraph::getMaxX(bool real) {
    return real ? maxxval : length-1;
}
double NegativeTimeGraph::getMinX(bool real) {
    return real ? 0 : ylabelsize;
}
double NegativeTimeGraph::getMaxY(bool real) {
    return real ? 0 : 1;
}
double NegativeTimeGraph::getMinY(bool real) {
	return real ? minyval : width-1;
}
double NegativeTimeGraph::getMaxX() { NegativeTimeGraph::getMaxX(true); }
double NegativeTimeGraph::getMinX() { NegativeTimeGraph::getMinX(true); }
double NegativeTimeGraph::getMaxY() { NegativeTimeGraph::getMaxY(true); }
double NegativeTimeGraph::getMinY() { NegativeTimeGraph::getMinY(true); }
*/




/******************* "Scaling" *******************/
void Map::setExtremeX(double value) {
	Map::setMaxX(value);
    Map::setMinX(-value);
}
void Map::setExtremeY(double value) {
	Map::setMaxY(value);
    Map::setMinY(-value);
}

//////////////////////////////////////

void TimeGraph::setExtremeX(double value) {
	Map::setMaxX(value);
}

//////////////////////////////////////
void PositiveTimeGraph::setExtremeY(double value) {
	PositiveTimeGraph::setMaxY(value);
}



/******************* Setting Maximum and Minimum *******************/
void Map::setMaxX(double max) {
	maxxval = max ;// getMaxX(false);
}
void Map::setMaxY(double max) {
	maxyval = max ;// getMaxY(false);
}

void Map::setMinX(double min) {
	minxval = min ;// getMinX(false);
}
void Map::setMinY(double min) {
	minyval = min ;// getMinY(false);
}

void TimeGraph::setMinX(double min) {
    Map::setMinX(min);
}

void PositiveTimeGraph::setMinY(double min) {
    Map::setMinY(min);
}



/******************* Getting Board Length *******************/
int Map::xBoardLength() {
    return length - ylabelsize - 1;
}
int Map::yBoardLength() {
    return width -2;
}