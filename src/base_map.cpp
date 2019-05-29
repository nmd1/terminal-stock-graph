#include "base_map.h"
#include <unistd.h>
#include <iostream>
#include <fstream>

/*
         <---length (j)--->
       /\
       |*******************
       |*******************
       |******************* 
width (i)****************** 
       |*******************
       |******************* 
       |******************* 
       \/
*/

extern ofstream debugf;
extern ofstream graphwin;

Map::Map(int l, int w, Display * dis) {
	length = l;
	width = w;
	display = dis;
	// Shift the center of the Y axis because of the label size
	yaxisloc = (length-1)/2;
	xaxisloc = (width/2);

	// Set where zero is
	xzero = yaxisloc+1;
	yzero = xaxisloc-1;


	// Characters to use in graphs
	space = '.';
	xline = '_';
	yline = '|';
	nothing = ' ';
	point = '#';

	ylabelsize = 1;
	xlabelsize = 1;


	maxxval = xBoardLength()/2;
	minxval = -xBoardLength()/2;
	maxyval = yBoardLength()/2;
	minyval = -yBoardLength()/2;

	// Set up the window
	window = display->newWindow(w,l,0,0);
	
	if(width < 4 || length < 4) throw "Object Failed";

}

void Map::create() {
	std::string temp_char_label = " ";
	for(int i = 0; i < width; i++) {
		vector<char> rowfill;
		for(int j = 0; j < length; j++) {
			if(j==yaxisloc && i != xaxisloc) {
				rowfill.push_back(temp_char_label[0]);
			} else if(j==yaxisloc+1) {
				rowfill.push_back(yline);
			} else {
				if (i==xaxisloc && j==yaxisloc) {
					rowfill.push_back(nothing);
				} else if (i==xaxisloc) {
					rowfill.push_back(' ');
				} else if(i==xaxisloc-1) {
					rowfill.push_back(xline);
				} else {
					rowfill.push_back(space);				
				}
			}
		}
		//std::cout<<"size of row i="<<i<<" is "<<rowfill.size()<<std::endl;
		theMap.push_back(rowfill);
		Ylabels.push_back(temp_char_label);
	}
	//std::cout<<"size of map is "<<theMap.size()<<std::endl;
	return;
}
void Map::literalPrint() {
	graphwin<<endl<<endl;
	for(int i = 0; i < width; i++) {
		for(int j = 0; j < length; j++) {
			graphwin<<theMap[i][j];
		}
		graphwin<<endl;
	}
}


void Map::updateScreen(bool blockexit) {
	for(int i = 0; i < width; i++) {
		for(int j = 0; j < length; j++) {

			if(theMap[i][j]==point) {
				if(i>yzero)
					display->place(window, theMap[i][j],j,i,2);
				else if(i<yzero)
					display->place(window, theMap[i][j],j,i,1);
				else
					display->place(window, theMap[i][j],j,i,0);
				
			} else {
				display->place(window, theMap[i][j],j,i,0);
			}

		}
	}
	display->refresh(window);
	if(blockexit) display->blockExit(window);
}

bool Map::getRawCoord(double &x, double &y) {
	// Rescale down to coords that would fit on the board

	double xscale = maxxval - minxval;
	double yscale = maxyval - minyval; 

	if(xscale!=0) x /= xscale;
	if(yscale!=0) y /= yscale;

	y=y*yBoardLength();
	x=x*xBoardLength();

	//debugf<<x<<" , "<<y<<endl;

	// Skip over labels
	if(x < 0) x-=2;
	if(y < 0) y-=2;

	// Translate to map coordinates
	int finaly = round(yzero-y);
	int finalx = round(xzero+x);

	//debugf<<scalex<<" , "<<scaley<<endl;

	// check bounds 
	if(finaly<0) return false;
	if(finalx<0) return false;
	if(finaly>=(int)theMap.size()) return false;
	if(finalx>=(int)theMap[finaly].size()) return false;

	x = finalx;
	y = finaly;

	return true;

}

// Sets coordinates for generic map
bool Map::setCoord(double x, double y) {
	bool returnval = getRawCoord(x, y);
	int xin = (int)x;
	int yin = (int)y;
	//debugf<<"("<<xin<<","<<yin<<")"<<endl;
	if(returnval) theMap[yin][xin] = point;	
	return returnval;
}


// Auto label based on how many labels we have
void Map::setLabelX(vector<std::string> labels) {
	Xlabels.clear();
	for (unsigned i = 0; i < theMap[yzero+1].size(); i++) {
		if(i < labels.size()) {
			Xlabels.push_back(labels[i]);
		} else {
			Xlabels.push_back(" ");
		}
	}

	// Fill in the map with the labels
	int j = xzero;
	for(unsigned i = 0; i < labels.size(); i++) {
		unsigned k = 0;
		for (; k < labels[i].size(); j++, k++) {
			theMap[yzero+1][j] = labels[i][k];
		}
		theMap[yzero+1][++j] = ' ';
	}
	return; 
}

// Use this for setting labels
void Map::setLabelX(std::string label, double xin) {
	double y = 0;

	if(!getRawCoord(xin, y)) return;
	int x = (int)xin;
	y++;


	if((x)%(xlabelsize)) {return;}
	if(!((x+xlabelsize)< getMaxX(gM_internal) )) {return;}
	// Ensure there's a space between each label
	label[xlabelsize-1] = ' ';

	// Fill in the row with the label
	for (unsigned k =0; k < label.size(); x++, k++) {
		theMap[y][x] = label[k];
	}
}

void Map::setLabelY(std::string label, double yin) {
	double x = 0;
	if(!getRawCoord(x, yin)) return;

	int y = (int)yin;
	x = 0;


	// Fill in the row with the label
	for (unsigned k =0; k < label.size(); x++, k++) {
		if(x>yaxisloc) break;
		theMap[y][x] = label[k];

		//debugf<<"fillin in"<<endl;
	}
}

void Map::resizeLabelX(int s) {
	xlabelsize = ++s; // add one for spacing
}
void Map::resizeLabelY(unsigned int s) {
	//if(Ylabels.size()==0) return; //there are no ylabels....


    unsigned int longest = s; //if it ain't broke don't fix it

    for(unsigned i = 0; i < theMap.size(); i++) {
    	vector<char> row = theMap[i];

		// Split the current row into two vectors,
		// Generate a new vector<char> that is made up
		// of characters from the label, and combine 
		// the three 
    	
    	// Split
    	std::vector<char> result(row.begin(), row.begin() + yaxisloc + 1 - ylabelsize);
		std::vector<char> split_hi(row.begin() + yaxisloc + 1 - ylabelsize + 1, row.end());			
		
		// Create char label vector
		vector<char> alabel;


		// add in blank spaces for x axis to keep rows even
		for (unsigned int k = 0; k < longest; k++) {
			alabel.push_back(' ');
		}

		// add in label, character by character, from Ylables
		// into our approperately sized alabel vector
		int j = 0;
		for(unsigned int k = longest-Ylabels[i].size(); k < longest; k++) {
			if(!Ylabels[i][j]) break;
			alabel[k] = Ylabels[i][j++];
		}


		// Merge 
		result.insert(result.end(), alabel.begin(), alabel.end());
		result.insert(result.end(), split_hi.begin(), split_hi.end());;

		// refresh the map row with this
    	theMap[i] = result;

    }

    // We just fundumentally changed the map, we need to edit some variables
    setYLabelSize(longest);
	display->resize(window, 2*length+longest-2,width);
}



void Map::setLabelY(vector<std::string> labels) {
	Ylabels.clear();


	// find the length of the longest label
    int longest = 0;
    for (const auto& line : labels) {
        if ((int)line.length() > longest) {
            longest = line.length();
        }
    }

    // Fill! the Ylabels vector
    int j = 0;
	for (int i = 0; i < (int)theMap.size(); i++) {
		if(i < (int)labels.size() && i!=yzero+1) {
			Ylabels.push_back(labels[j]);
			j++;
		} else {
			std::string blanks(longest, ' ');
			Ylabels.push_back(blanks);
		}
	}

    cout<<"longest is "<<longest<<endl;

    for(unsigned i = 0; i < theMap.size(); i++) {
    	vector<char> row = theMap[i];

		// Split the current row into two vectors,
		// Generate a new vector<char> that is made up
		// of characters from the label, and combine 
		// the three 
    	
    	// Split
    	std::vector<char> result(row.begin(), row.begin() + yaxisloc + 1 - ylabelsize);
		std::vector<char> split_hi(row.begin() + yaxisloc + 1 - ylabelsize + 1, row.end());			
		
		// Create char label vector
		vector<char> alabel;


		// add in blank spaces for x axis to keep rows even
		for (int k = 0; k < longest; k++) {
			alabel.push_back(' ');
		}

		// add in label, character by character
		j = 0;
		for(int k = longest-Ylabels[i].size(); k < longest; k++) {
			if(!Ylabels[i][j]) break;
			alabel[k] = Ylabels[i][j++];
		}


		// Merge 
		result.insert(result.end(), alabel.begin(), alabel.end());
		result.insert(result.end(), split_hi.begin(), split_hi.end());;

		// refresh the map row with this
    	theMap[i] = result;

    }

    // We just fundumentally changed the map, we need to edit some variables
    setYLabelSize(longest);
	display->resize(window, 2*length+longest-2,width);
}


/*******************************************************************/

CoordinateGrid::CoordinateGrid(int size, Display * dis) : Map(size, size, dis) {
	length = size;
	width = size;

	xzero = yaxisloc+1;
	yzero = xaxisloc-1;

	if(size < 4) throw "Object Failed";

}
