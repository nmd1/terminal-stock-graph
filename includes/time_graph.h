#ifndef TIME_GRAPH_H
#define TIME_GRAPH_H

#include "base_map.h"

class TimeGraph : public Map {
public:
	TimeGraph(int,int);
	void extend();
	bool setCoord(double, double);
	int getMaxX(bool=true);
	int getMinX(bool=true);


protected:
	int time;
};





class PositiveTimeGraph : public TimeGraph {

public:
	PositiveTimeGraph(int,int);
	bool setCoord(double, double);
	int getMaxY(bool=true);
	int getMinY(bool=true);

};

#endif