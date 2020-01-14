#include "map/time.hpp"
#include "map/base.hpp"


/******************* Maximum and minimum values on a graph  *******************/
double Map::getMaxX(bool real) {
    return real ? maxval.x : length - 1;
}
double Map::getMinX(bool real) {
    return real ? minval.x : 0;
}
double Map::getMaxY(bool real) {
    return real ? maxval.y : 0;
}
double Map::getMinY(bool real) {
    return real ? minval.y : width - 1;
}

double Map::getMaxX() { return Map::getMaxX(true); }
double Map::getMinX() { return Map::getMinX(true); }
double Map::getMaxY() { return Map::getMaxY(true); }
double Map::getMinY() { return Map::getMinY(true); }

double Map::getScaleX() { return (maxval.x - minval.x)/2; }
double Map::getScaleY() { return (maxval.y - minval.y)/2; }

//////////////////////////////////////

double TimeGraph::getMinX(bool real) {
    return real ? minval.x : labelsize.y;
}
double TimeGraph::getMinX() { return TimeGraph::getMinX(true); }

double TimeGraph::getScaleX() { return 2*Map::getScaleX(); }

//////////////////////////////////////

double PositiveTimeGraph::getMinY(bool real) {
	return real ? minval.y : width-2;
}
double PositiveTimeGraph::getMinY() { return PositiveTimeGraph::getMinY(true); }

double PositiveTimeGraph::getScaleY() {	return 2*Map::getScaleY(); }

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
	maxval.x = max;
}
void Map::setMaxY(double max) {
	maxval.y = max;
}

void Map::setMinX(double min) {
	minval.x = min;
}
void Map::setMinY(double min) {
	minval.y = min;
}

void TimeGraph::setMinX(double min) {
    Map::setMinX(min);
}

void PositiveTimeGraph::setMinY(double min) {
    Map::setMinY(min);
}



/******************* Getting Board Length *******************/
int Map::xBoardLength() {
    return length - labelsize.y - 1;
}
int Map::yBoardLength() {
    return width-2;
}