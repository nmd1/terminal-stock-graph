#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

/*
   <--------------length (j)----------->
/\
| * * * * * * * * * * * * * * * * * * *
| * * * * * * * * * * * * * * * * * * * 
| * * * * * * * * * * * * * * * * * * * 
width (i) * * * * * * * * * * * * * * * 
| * * * * * * * * * * * * * * * * * * * 
| * * * * * * * * * * * * * * * * * * * 
| * * * * * * * * * * * * * * * * * * * 
\/
*/

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
		int getMaxX(bool=true);
		int getMinX(bool=true);
		int getMaxY(bool=true);
		int getMinY(bool=true);

		void scaleX(double);
		void scaleY(double);
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

Map::Map(int l, int w) {
	length = l;
	width = w;
	// Shift the center of the Y axis because of the label size
	yaxisloc = (length-1)/2;
	xaxisloc = width/2;

	// Set where zero is
	xzero = yaxisloc+1;
	yzero = xaxisloc-1;


	// characters to use in graphs
	space = '.';
	xline = '_';
	yline = '|';
	nothing = ' ';
	point = '#';

	scalex = 1;
	scaley = 1;
}

void Map::create() {
	for(int i = 0; i < width; i++) {
		vector<char> rowfill;
		for(int j = 0; j < length; j++) {
			if(j==yaxisloc && i != xaxisloc) {
				rowfill.push_back(i + '0');
			} else if(j==yaxisloc+1) {
				rowfill.push_back(yline);
			} else {
				if (i==xaxisloc && j==yaxisloc) {
					rowfill.push_back(nothing);
				} else if (i==xaxisloc) {
					rowfill.push_back(j + '0');
				} else if(i==xaxisloc-1) {
					rowfill.push_back(xline);
				} else {
					rowfill.push_back(space);				
				}
			}
		}
		theMap.push_back(rowfill);
	}
	return;
}
void Map::print() {
	for(int i = 0; i <= theMap.size(); i++) {
		for(int j = 0; j < theMap[i].size(); j++) {
	    	std::cout << theMap[i][j] << " ";
		}
		if(i != width-1) cout<<endl;
	}
	return;
}

// Sets coordinates for generic map
bool Map::setCoord(double x, double y) {
	//cout<<xzero<<','<<yzero<<endl;

	// Rescale down to coords that would fit on the board
	x = x/scalex;
	y = y/scaley;

	// Skip over labels
	if(x < 0) x-=1;
	if(y < 0) y-=1;

	// Translate to map coordinates
	int finaly = (int)yzero-y;
	int finalx = (int)xzero+x;

	// check bounds 
	if(finaly<0) return false;
	if(finalx<0) return false;
	if(finaly>=theMap.size()) return false;
	if(finalx>=theMap[finaly].size()) return false;

	// Set Coordinate
	theMap[finaly][finalx] = point;	
	return true;
}

void Map::setLabelX(vector<char> labels) {
	int j = 0;
	for(int i = 0; i < theMap.front().size(); i++) {
		if (j>=labels.size()) return;
		if(i !=yaxisloc && i !=yaxisloc+1) {
			theMap[xaxisloc][i] = labels[j];
			j++;
		}
	}
}

void Map::setLabelY(vector<char> labels) {
	int j = 0;
	for(int i = 0; i < theMap.size(); i++) {
		if (j>=labels.size()) return;
		if(i !=xaxisloc) {
			theMap[i][yaxisloc] = labels[j];
			j++;
		}
	}
}

int Map::getMaxX(bool scale) {
	int maxxboard =  (length - 2)/2;
	return scale ? maxxboard*scalex : maxxboard;
}
int Map::getMinX(bool scale) {
	int space = length - 2;
	int minxboard =  (space%2) ? -(space/2)-1 : -(space/2);
	return scale ? minxboard*scalex : minxboard;
}
int Map::getMaxY(bool scale) {
	int maxyboard =  (width - 2)/2;
	return scale ? maxyboard*scaley : maxyboard;
}
int Map::getMinY(bool scale) {
	int space = width - 2;
	int minyboard = (space%2) ? -(space/2)-1 : -(space/2);
	return scale ? minyboard*scaley : minyboard;
}

void Map::scaleX(double value) {
	scalex = value;
}
void Map::scaleY(double value) {
	scaley = value;
}

void Map::setMaxX(double max) {
	scalex = max / getMaxX(false);
}
void Map::setMaxY(double max) {
	scalex = max / getMaxY(false);
}


class CoordinateGrid : public Map {

public:
	CoordinateGrid(int);

};

CoordinateGrid::CoordinateGrid(int size) : Map(size, size) {
	length = size;
	width = size;

	//xzero = (length+1)/2;
	//yzero = (width-2)/2;

	xzero = yaxisloc+1;
	yzero = xaxisloc-1;

}


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

TimeGraph::TimeGraph(int time, int magnitude) : Map(time, magnitude) {
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


class PositiveTimeGraph : public TimeGraph {

public:
	PositiveTimeGraph(int,int);
	bool setCoord(double, double);
	int getMaxY(bool=true);
	int getMinY(bool=true);

};

PositiveTimeGraph::PositiveTimeGraph(int time, int magnitude) : TimeGraph(time, magnitude) {
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


main() {

	int x[] = {1,2,3,4,5,6,7,8,9,10};
	int y[] = {4,7,3,5,8,3,4,6,7,1};

	int len = 10;
	Map a(11,13);
	CoordinateGrid b(41);
	TimeGraph c(11,13);
	PositiveTimeGraph d(41,24);
	a.create();
	b.create();
	c.create();
	d.create();	

	b.scaleX((double)1/10);
	vector<char> newl;
	for(int i = 0; i < a.getMaxY()-a.getMinY()+1; i++) {
		newl.push_back('A' + i);
	}
	a.setLabelY(newl);

	c.setCoord(0,3);
	d.setCoord(0,0);
	b.setCoord(0,-1);
	b.setCoord(-1,0);
	b.setCoord(0,0);

	for(double i = b.getMinX(); i < b.getMaxX(false); i=i+0.01) {
		if(!i) continue;
		b.setCoord(i,1/i);
	}
	d.scaleX((double)1/10);
	d.scaleY((double)1/10);
	for(double i = 0; i < d.getMaxX(false); i=i+0.1) {
		d.setCoord(i,log(i));
	}
	cout<<a.getMaxX()<<endl;
	for (int i = -25; i < 25; i++) {
		a.setCoord(i,10*sin(i*2));
		c.setCoord(i,10*sin(i*2));
		d.setCoord(i,10*sin(i*2));
	}
	//b.setCoord(0,11);
	a.print();
	cout<<endl;	
	b.print();
	cout<<endl;
	c.print();
	cout<<endl;
	d.print();
	cout<<endl;

	return 0;
}

/* Changelog

-added ability to change labels 
-added abiltiy to get min and max y values
-added ability to scale!
-you can scale up to a certain value
-you can set the scale to whatever you want
-coordinates can now be floating point, not just integers

*/