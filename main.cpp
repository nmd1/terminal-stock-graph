#include <iostream>
#include <vector>
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
class Map {

	public:
		Map(int,int);
		void draw();
		void create();
		void print();
		vector< vector<char> > theMap;

	protected:
		int length;
		int width;
		int xaxisloc;
		int yaxisloc;
};

// This is the map base class
Map::Map(int l, int w) {
	length = l;
	width = w;
	// Shift the center of the Y axis because of the label size
	yaxisloc = (length-2)/2;
	xaxisloc = width/2;
}

void Map::create() {
	for(int i = 0; i < width; i++) {
		vector<char> rowfill;
		for(int j = 0; j < length; j++) {
			if(j==yaxisloc && i != xaxisloc) {
				rowfill.push_back(i + '0');
			} else if(j==yaxisloc+1) {
				rowfill.push_back('|');
			} else {
				if (i==xaxisloc && j==yaxisloc) {
					rowfill.push_back(' ');
				} else if (i==xaxisloc) {
					rowfill.push_back(j + '0');
				} else if(i==xaxisloc-1) {
					rowfill.push_back('_');
				} else {
					rowfill.push_back('.');				
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

class CoordinateGrid : public Map {

public:
	CoordinateGrid(int);

};

CoordinateGrid::CoordinateGrid(int size) : Map(size, size) {
	length = size;
	width = size;
}

class TimeGraph : public Map {
public:
	TimeGraph(int,int);
	void extend();

protected:
	int time;
};

TimeGraph::TimeGraph(int time, int magnitude) : Map(time, magnitude) {
	length = time;
	width = magnitude;
	xaxisloc = width/2;
	yaxisloc = 0;
}

class PositiveTimeGraph : public TimeGraph {

public:
	PositiveTimeGraph(int,int);

};

PositiveTimeGraph::PositiveTimeGraph(int time, int magnitude) : TimeGraph(time, magnitude) {
	length = time;
	width = magnitude;
	xaxisloc = magnitude-1;
	yaxisloc = 0;
}




main() {

	int x[] = {1,2,3,4,5,6,7,8,9,10};
	int y[] = {4,7,3,5,8,3,4,6,7,1};

	int len = 10;
	Map a(30,14);
	CoordinateGrid b(30);
	TimeGraph c(30,14);
	PositiveTimeGraph d(30,14);
	a.create();
	b.create();
	c.create();
	d.create();	
	a.print();
	cout<<endl;	
	b.print();
	cout<<endl;
	c.print();
	cout<<endl;
	d.print();
	cout<<endl;
    
	cout<<endl;

	return 0;
}