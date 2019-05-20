#ifndef BASE_MAP_H
#define BASE_MAP_H

#include <iostream>
#include <vector>
#include <cmath>
#include "window.h"

using namespace std;


// This is the map base class
// Every map type extends this class (or a class that extends this class)
// ya know, standard oop stuff

class Map {

	public:
		Map(int,int, Display*);
		void draw();
		void create();
		// print to stdout
		void print();

		// display in ncurses window
		void updateScreen();

		// display skelington in ncurses window
		void showDebugScreen();

		// set a coordinate in the map
		bool setCoord(double x, double y);

		// labeling
		// Auto label based on how many labels we have
		void setLabelX(vector<std::string>);
		// Set X label spacing as a percentage of the whole width
		void setLabelX(vector<std::string>, double);
		// Set X label spacing as int many spaces between each label
		void setLabelX(vector<std::string>, int);
		// Set an X label based on it's coordinate
		void setLabelX(std::string, double);
		// Set an Y label based on it's coordinate

		void setLabelY(std::string, double);
		void setLabelY(vector<std::string>);

		// Draw labels on ncurses window
		void drawLabelX();
		void drawLabelY();

		// Draw axis
		void drawaxisX();
		void drawaxisY();

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

			// Set scaling factor based on what the min values should be
		void setMinX(double);
		void setMinY(double);

		// Setters for the axis (can be removed later?)
		void setXaxis(int);
		void setYaxis(int);
		void setYLabelSize(int);
		void literalPrint();
		int getNumberOfYLabels();
	protected:
		// Return where on the map a coordinate would be placed
		bool getRawCoord(double &, double &);
		// Graph Arrays
		vector< vector<char> > theMap;
		vector<  std::string > Xlabels;
		vector<  std::string > Ylabels;

		// ncurses display data
		Display * display;
		int window;

		// map meta information
		int length;
		int width;
		int xaxisloc;
		int yaxisloc;
		int xzero;
		int yzero;
		double scalex;
		double scaley;
		int ylabelsize;
		int padding;

		// characters to use in graphs
		char space;
		char xline;
		char yline;
		char nothing;
		char point;
};

class CoordinateGrid : public Map {

public:
	CoordinateGrid(int, Display*);
};

#endif