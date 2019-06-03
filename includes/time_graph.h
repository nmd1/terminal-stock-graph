#ifndef TIME_GRAPH_H
#define TIME_GRAPH_H

#include "base_map.h"

class Display;

class TimeGraph : public Map {
public:
	TimeGraph(int,int, Display*);
	bool setCoord(double, double);

	// Get extremes of a graph in real coordinates
	double getMinX();
	// Prevent negative x vals from being set
	void setMinX(double);
	// Set max and min simultaneously and equally
	void setExtremeX(double);
	// Get scale of graph
	virtual double getScaleX();

protected:
	virtual double getMinX(bool=true);
	int time;
};


/***********************************/

class PositiveTimeGraph : public TimeGraph {

public:
	PositiveTimeGraph(int,int, Display*);
	bool setCoord(double, double);
	
	// Get extremes of a graph in real coordinates
	double getMinY();
	// Set max/min value for x/y 
	void setMinY(double);
	// Set max and min simultaneously and equally
	void setExtremeY(double);
	// Get scale of graph
	double getScaleY();
protected:
	/* MAX/MIN Getters and Setters */
	// Get extremes of a graph in real coordinates
	virtual double getMinY(bool=true);

};

#endif