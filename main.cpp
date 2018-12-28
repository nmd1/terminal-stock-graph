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
		bool setCoord(int x, int y);

	protected:
		vector< vector<char> > theMap;
		// map meta information
		int length;
		int width;
		int xaxisloc;
		int yaxisloc;
		int xzero;
		int yzero;


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
bool Map::setCoord(int x, int y) {
	//cout<<xzero<<','<<yzero<<endl;
	// Skip over labels
	if(x < 0) x-=1;
	if(y < 0) y-=1;

	// Translate to map coordinates
	int finaly = yzero-y;
	int finalx = xzero+x;

	// check bounds 
	if(finaly<0) return false;
	if(finalx<0) return false;
	if(finaly>=theMap.size()) return false;
	if(finalx>=theMap[finaly].size()) return false;

	// Set Coordinate
	theMap[finaly][finalx] = point;	
	return true;
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
	bool setCoord(int, int);

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

bool TimeGraph::setCoord(int t, int y) {
	if(t < 0) return false;
	Map::setCoord(t,y);
	return true;
}

class PositiveTimeGraph : public TimeGraph {

public:
	PositiveTimeGraph(int,int);
	bool setCoord(int, int);

};

PositiveTimeGraph::PositiveTimeGraph(int time, int magnitude) : TimeGraph(time, magnitude) {
	length = time;
	width = magnitude;
	xaxisloc = magnitude-1;
	yaxisloc = 0;

	xzero = yaxisloc+1;
	yzero = xaxisloc-1;

}


bool PositiveTimeGraph::setCoord(int t, int y) {
	if(y < 0) return false;
	TimeGraph::setCoord(t,y);
	return true;
}


main() {

	int x[] = {1,2,3,4,5,6,7,8,9,10};
	int y[] = {4,7,3,5,8,3,4,6,7,1};

	int len = 10;
	Map a(11,13);
	CoordinateGrid b(40);
	TimeGraph c(11,13);
	PositiveTimeGraph d(11,13);
	a.create();
	b.create();
	c.create();
	d.create();	

	c.setCoord(0,3);
	d.setCoord(0,0);
	b.setCoord(0,-1);
	b.setCoord(-1,0);
	b.setCoord(0,0);

	for (int i = -23; i < 25; i++) {
		a.setCoord(i,10*sin(i*2));
		b.setCoord(i,10*sin(i*2));
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