#include "time_graph.h"



TimeGraph::TimeGraph(int time, int magnitude, Display * dis) : Map(time, magnitude, dis) {
	length = time;
	width = magnitude;
	xaxisloc = width/2;
	yaxisloc = 0;

	xzero = yaxisloc+1;
	yzero = xaxisloc-1;
}

bool TimeGraph::setCoord(double t, double y) {
	if(t < 0) return false;
	Map::setCoord(t,y);
	return true;
}

int TimeGraph::getMaxX(bool scale) {
	return scale ? (length - 2)*scalex : length - 2;
}
int TimeGraph::getMinX(bool scale) {
	return 0;
}


/**********************************************/

PositiveTimeGraph::PositiveTimeGraph(int time, int magnitude, Display * dis) : TimeGraph(time, magnitude, dis) {
	length = time;
	width = magnitude;
	xaxisloc = magnitude-1;
	yaxisloc = 0;

	xzero = yaxisloc+1;
	yzero = xaxisloc-1;

}


bool PositiveTimeGraph::setCoord(double t, double y) {
	if(y < 0) return false;
	TimeGraph::setCoord(t,y);
	return true;
}

int PositiveTimeGraph::getMaxY(bool scale) {
	return scale ? (width - 2)*scaley : width - 2;
}
int PositiveTimeGraph::getMinY(bool scale) {
	return 0;
}