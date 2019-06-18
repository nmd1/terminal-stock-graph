#include "map/time.h"



TimeGraph::TimeGraph(int time, int magnitude) : Map(time, magnitude) {
	length = time;
	width = magnitude;
	axisloc.x = (width-1)/2;
	axisloc.y = 1; // !!! Should be 1! Fix program when you make this change!!!

	quadrantn.x = 1;
	quadrantn.y = 2;

	maxval.x = xBoardLength();
	minval.x = 0;
	maxval.y = yBoardLength()/2;
	minval.y = -yBoardLength()/2;

	if(width < 4 || length < 3) throw "Object Failed";
}

bool TimeGraph::setCoord(double x, double y) {
	return TimeGraph::setCoord(x,y,defaultColor);
}

bool TimeGraph::setCoord(double t, double y, Color color) {
	if(t < 0) return false;
	Map::setCoord(t,y,color);
	return true;
}



TimeGraph::TimeGraph(int size,int mag, bool trans) : TimeGraph(size, mag) {
	if(trans) space = transparent;
}


/**********************************************/

PositiveTimeGraph::PositiveTimeGraph(int time, int magnitude) : TimeGraph(time, magnitude) {
	length = time;
	width = magnitude;
	axisloc.x = magnitude-2;
	axisloc.y = 1; // !!! Should be 1! Fix program when you make this change!!!

	quadrantn.x = 1;
	quadrantn.y = 1;

	maxval.x = xBoardLength();
	minval.x = 0;
	maxval.y = yBoardLength();
	minval.y = 0;

	if(width < 3 || length < 3) throw "Object Failed";

}


bool PositiveTimeGraph::setCoord(double x, double y) {
	return PositiveTimeGraph::setCoord(x,y,defaultColor);
}
bool PositiveTimeGraph::setCoord(double t, double y, Color color) {
	if(y < 0) return false;
	TimeGraph::setCoord(t,y,color);
	return true;
}


PositiveTimeGraph::PositiveTimeGraph(int size,int mag, bool trans) : PositiveTimeGraph(size, mag) {
	if(trans) space = transparent;
}
