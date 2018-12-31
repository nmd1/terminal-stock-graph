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

	ylabelsize = 1;

	scalex = 1;
	scaley = 1;
}

void Map::create() {
	for(int i = 0; i < width; i++) {
		vector<char> rowfill;
		for(int j = 0; j < length; j++) {
			if(j==yaxisloc && i != xaxisloc) {
				rowfill.push_back('L');
			} else if(j==yaxisloc+1) {
				rowfill.push_back(yline);
			} else {
				if (i==xaxisloc && j==yaxisloc) {
					rowfill.push_back(nothing);
				} else if (i==xaxisloc) {
					rowfill.push_back('X');
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
	int x_label_char_count = 0;
	int k = 0;
	for(int i = 0; i < theMap.size(); i++) {
		for(int j = 0; j < theMap[i].size(); j++) {
			//std::cout <<i<<":"<<j<<std::endl;

			// Don't add space if you're a yaxis  label
			if(yaxisloc-ylabelsize < j && j <= yaxisloc) {
		    	std::cout << theMap[i][j];			
			} else if (i==xaxisloc) {
				if (theMap[i][j]!=' ') {
					std::cout << theMap[i][j];
					++x_label_char_count;
				} else {
					for(int k=0;k<x_label_char_count-1;k++)
						cout<<" ";
					x_label_char_count=0;
				}
			} else if (i==xaxisloc-1) {
		    	std::cout << theMap[i][j] << "_";
			} else {
		    	std::cout << theMap[i][j] << " ";
			}

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

// Auto label based on how many labels we have
void Map::setLabelX(vector<std::string> labels) {
	int len = labels.size();
	if(len<1) return; // Throw error: no labels
	double result = (double)1/len;
	Map::setLabelX(labels, result);
}
// Set X label spacing as a percentage of the total length
void Map::setLabelX(vector<std::string> labels, double percentage) {
	if (percentage > 1) return; //TODO: throw error: not a percent
	int result = percentage*length;
	Map::setLabelX(labels, result);
}

void Map::setLabelX(vector<std::string> labels, int spacing) {
	signed int j = -1, k = -1;
	vector<char> axis;
	bool writing = false;
	cout<<labels.size()<<endl;
	axis.push_back(' ');
	for(int i = 0; i < theMap[xaxisloc].size(); i++) {
		// End if we ran out of labels
		if(j>=(signed)labels.size()) break;

		// Every certain amount of chars start drawing a label
		if(i%spacing==0) {
			k=0;
			j++;
		}

		// draw a label, only if we're in drawing mode (k!=-1)
		if(k>=0) {
			axis.push_back(labels[j][k]);
			k++;
		// if not drawing, place an empty space
		} else {
			axis.push_back(' ');
		}

		// if there are no more chars in a word, exit label drawing
		if(k>labels[j].length()) k=-1;
	}
	theMap[xaxisloc] = axis;
}

void Map::setLabelY(vector<std::string> labels) {
	int j = 0;

	// find the length of the longest label
    int longest = 0;
    for (const auto& line : labels) {
        if (line.length() > longest) {
            longest = line.length();
        }
    }

    for(int i = 0; i < theMap.size(); i++) {
    	vector<char> row = theMap[i];
		if(j>=labels.size()) break;


		// Split the current row into two vectors,
		// Generate a new vector<char> that is made up
		// of characters from the label, and combine 
		// the three 
    	
    	// Split
    	std::vector<char> result(row.begin(), row.begin() + yaxisloc + 1 - ylabelsize);
		std::vector<char> split_hi(row.begin() + yaxisloc + 1 - ylabelsize + 1, row.end());			
		
		// Create char label vector
		vector<char> alabel;


		if(i !=xaxisloc) {
			// add in blank spaces to keep rows even
			for (int k = 0; k < longest-labels[j].length(); k++) {
				alabel.push_back(' ');
			}
			// fill rest of label vector with label
			for(int k = 0; k < labels[j].length(); k++) {
				alabel.push_back(labels[j][k]);
			}
			// indicate that you should move on to the next label
			++j;

		} else {

			// add in blank spaces for x axis to keep rows even
			for (int k = 0; k < longest; k++) {
				alabel.push_back(' ');
			}
		}

		// Merge 
		result.insert(result.end(), alabel.begin(), alabel.end());
		result.insert(result.end(), split_hi.begin(), split_hi.end());;

		// refresh the map row with this
    	theMap[i] = result;

    }

    // We just fundumentally changed the map, we need to edit some variables
    yaxisloc = yaxisloc + longest - ylabelsize;
 	ylabelsize = longest;
 	xzero = yaxisloc-1;

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
