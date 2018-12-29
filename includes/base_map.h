#ifndef BASE_MAP_H
#define BASE_MAP_H

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;



// This is the map base class
// Every map type extends this class (or a class that extends this class)
// ya know, standard oop stuff
class Map {

	public:
		Map(int,int);
		void draw();
		void create();
		void print();
		bool setCoord(double x, double y);
		void setLabelX(vector<char>);
		void setLabelY(vector<char>);

		// Get extremes of a graph
		int getMaxX(bool=true);
		int getMinX(bool=true);
		int getMaxY(bool=true);
		int getMinY(bool=true);

		// Change scaling factor for graph
		void scaleX(double);
		void scaleY(double);

		// Set scaling factor based on what the max values should be
		void setMaxX(double);
		void setMaxY(double);
	protected:
		vector< vector<char> > theMap;

		// map meta information
		int length;
		int width;
		int xaxisloc;
		int yaxisloc;
		int xzero;
		int yzero;
		double scalex;
		double scaley;

		// characters to use in graphs
		char space;
		char xline;
		char yline;
		char nothing;
		char point;
};

class CoordinateGrid : public Map {

public:
	CoordinateGrid(int);
};

#endif