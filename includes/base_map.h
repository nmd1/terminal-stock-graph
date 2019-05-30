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
double roundToPlace(const double&, const int&);
double roundToDPlace(const double&, const double&);
bool areSame(double, double, double=__DBL_EPSILON__);

class Map {

	public:
		Map(int,int, Display*);
		// Initalize everything needed for graph
		void create();
		/* drawing */
		// print to stdout (debug)
		void literalPrint();

		// display in ncurses window (if true, block)
		void updateScreen(bool=true);

		// set a coordinate in the map
		bool setCoord(double x, double y);



		/* labeling */				
		// Set an X label based on it's coordinate
		void setLabelX(std::string, double);
		// Set an Y label based on it's coordinate
		void setLabelY(std::string, double);

		// Auto label based on how many labels we have
		void setLabelX(vector<std::string>);
		void setLabelY(vector<std::string>);

		// Change how many X axis characters you can have before the next spacing 
		void resizeLabelX(int);
		// Change the width of the Ylabel column for labeling
		void resizeLabelY(unsigned int);





		/* MAX/MIN Getters and Setters */
		// Get extremes of a graph in real coordinates
		double getMaxX();
		double getMinX();
		double getMaxY();
		double getMinY();

		// Set max/min value for x/y 
		void setMaxX(double);
		void setMaxY(double);
		void setMinX(double);
		void setMinY(double);

		// Set max and min simultaneously and equally
		void setExtremeX(double);
		void setExtremeY(double);


		// Auto set labels 
		void autoLabelX(double, bool, double=0);
		void autoLabelY(double, bool, double=0);


		/* Setters for the axis (can be removed later?) */
		void setXaxis(int);
		void setYaxis(int);
		void setYLabelSize(int);

		int numbofYlabels() {return width-2;}

	protected:
		// Graph Arrays
		vector< vector<char> > theMap;
		vector<  std::string > Xlabels;
		vector<  std::string > Ylabels;


		// Return where on the map a coordinate would be placed
		bool getRawCoord(double &, double &);
		// Get extremes of a graph:
		//  if true, get it in real coordinates
		//  if false, get it in internal coordinates
		double getMaxX(bool);
		double getMinX(bool);
		double getMaxY(bool);
		double getMinY(bool);
		// Get length of actual drawing area
		int xBoardLength();
		int yBoardLength();



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

		// Extremes for real values 
		double maxxval;
		double maxyval;
		double minxval;
		double minyval;


		// for readability in calling max/min functions
		const bool gM_internal = false;
		const bool gM_real = true;

		// Max char length of labels 
		int ylabelsize;
		int xlabelsize;

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