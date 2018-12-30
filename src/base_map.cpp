#include "base_map.h"

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
		//std::cout<<"size of row i="<<i<<" is "<<rowfill.size()<<std::endl;
		theMap.push_back(rowfill);
	}
	//std::cout<<"size of map is "<<theMap.size()<<std::endl;
	return;
}
void Map::print() {
	for(int i = 0; i < theMap.size(); i++) {
		for(int j = 0; j < theMap[i].size(); j++) {
			//std::cout <<i<<":"<<j<<std::endl;
	    	std::cout << theMap[i][j] << " ";

		}
		if(i != width-1) cout<<endl;
	}
	std::cout<<std::endl;
	return;
}

// Sets coordinates for generic map
bool Map::setCoord(double x, double y) {
	//cout<<xzero<<','<<yzero<<endl;

	// Rescale down to coords that would fit on the board

	x = x/scalex;
	y = y/scaley;

	cout<<x<<" , "<<y<<endl;

	// Skip over labels
	if(x < 0) x-=1;
	if(y < 0) y-=1;

	// Translate to map coordinates
	int finaly = (int)yzero-y;
	int finalx = (int)xzero+x;

	//cout<<scalex<<" , "<<scaley<<endl;

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
	scaley = max / getMaxY(false);
}


/*******************************************************************/

CoordinateGrid::CoordinateGrid(int size) : Map(size, size) {
	length = size;
	width = size;

	xzero = yaxisloc+1;
	yzero = xaxisloc-1;

}
