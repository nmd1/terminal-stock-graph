#include "time_graph.h"



TimeGraph::TimeGraph(int time, int magnitude, Display * dis) : Map(time, magnitude, dis) {
	length = time;
	width = magnitude;
	xaxisloc = width/2;
	yaxisloc = 0; // !!! Should be 1! Fix program when you make this change!!!

	xzero = yaxisloc;
	yzero = xaxisloc;

	maxxval = xBoardLength();
	minxval = 0;
	maxyval = yBoardLength()/2;
	minyval = -yBoardLength()/2;

	if(width < 4 || length < 3) throw "Object Failed";
}

bool TimeGraph::setCoord(double t, double y) {
	if(t < 0) return false;
	Map::setCoord(t,y);
	return true;
}






/**********************************************/

PositiveTimeGraph::PositiveTimeGraph(int time, int magnitude, Display * dis) : TimeGraph(time, magnitude, dis) {
	length = time;
	width = magnitude;
	xaxisloc = magnitude-1;
	yaxisloc = 0; // !!! Should be 1! Fix program when you make this change!!!

	xzero = yaxisloc+1;
	yzero = xaxisloc-1;

	maxxval = xBoardLength();
	minxval = 0;
	maxyval = yBoardLength();
	minyval = 0;

	if(width < 3 || length < 3) throw "Object Failed";

}



bool PositiveTimeGraph::setCoord(double t, double y) {
	if(y < 0) return false;
	TimeGraph::setCoord(t,y);
	return true;
}

