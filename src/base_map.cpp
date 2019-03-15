#include "base_map.h"
#include <unistd.h>

#include <iostream>
#include <fstream>

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

Map::Map(int l, int w, Display * dis) {
	length = l;
	width = w;
	display = dis;
	// Shift the center of the Y axis because of the label size
	yaxisloc = (length-1)/2;
	xaxisloc = width/2;

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

	scalex = 1;
	scaley = 1;

	padding=1;
	// Set up the window
	window = display->newWindow(2*w,2*l,0,0);


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

void Map::updateScreen() {
	Map::drawaxisX();
	Map::drawaxisY();

  	ofstream myfile;
  	myfile.open ("/dev/pts/4");

	display->inputBlock(window);

	//int x_label_char_count = 0;
	//int k = 0;
	int x, y;
	display->start(x, y);

	for(unsigned int i = 0; i < theMap.size(); i++) {
		x = (yaxisloc-ylabelsize)+1;
		for(int j = (yaxisloc-ylabelsize)+1; j < theMap[i].size(); j++) {
			myfile<<"\n("<<j<<","<<i<<")\n{"<<std::endl;

			if(x==xzero-1) {
				x=xzero;
				myfile<<"Condition 1"<<std::endl;
			}
			// Skip labeling completely, let the label functions handle that.
			if(i==xaxisloc && j==yaxisloc-1) {
				myfile<<"Condition 2"<<std::endl;
				++i;
				j=0;
				x=yaxisloc-6;//yaxisloc-1;
				y=i; //++i;
				//display->next(window,x,y);
				myfile<<"("<<x<<","<<y<<") -> "<<theMap[i][j]<<"\n}"<<std::endl;
				continue;
			}

			if(yaxisloc-ylabelsize+1 <= j && j <= yaxisloc) {
				myfile<<"Condition 3"<<std::endl;
				display->next(window,x,y);
				//display->next(window, '-',x,y,1);
				myfile<<"("<<x<<","<<y<<") -> "<<theMap[i][j]<<"\n}"<<std::endl;
				continue;
			}

			//cout<<i<<","<<j<<endl;

			//display->next(window,x,y);
			usleep(1000);

			// Coloring 
			myfile<<"("<<x<<","<<y<<") -> "<<theMap[i][j]<<std::endl;
			if(theMap[i][j]==point) {
				if(i>yzero)
					display->next(window, theMap[i][j],x,y,2);
				else if(i<yzero)
					display->next(window, theMap[i][j],x,y,1);
			} else {
				display->next(window, theMap[i][j],x,y,0);
			}
		 	//display->refresh(window);
			//usleep(10000);
			display->next(window, ' ',x,y,1); //gives controversial extra space
			display->refresh(window);

			myfile<<"}"<<std::endl;
			//display->inputBlock(window);

			//display->blockExit(window);
			//display->place(window, ' ',j,i,0);
		}
	}
	Map::drawLabelY();
	Map::drawLabelX();
	Map::drawaxisX();
	Map::drawaxisY();


  	myfile.close();

	display->refresh(window);
	display->inputBlock(window);
	return;
}

void Map::showDebugScreen() {
	Map::drawaxisX();
	Map::drawaxisY();

	for(int i = 0; i < theMap[0].size(); i++) {
		for(int j = 0; j < theMap.size(); j++) {
			if(i==yaxisloc)
				display->place(window, '|', i, j, 2);
			if(i==xzero)
				display->place(window, 'X', i, j, 1);
			if(j==xaxisloc)
				display->place(window, '_', i, j, 2);
			if(j==yzero)
				display->place(window, 'Y', i, j, 1);
		}
	}
	Map::drawLabelY();
	Map::drawLabelX();

	display->refresh(window);
	display->inputBlock(window);
}

// Sets coordinates for generic map
bool Map::setCoord(double x, double y) {
	//cout<<xzero<<','<<yzero<<endl;

	// Rescale down to coords that would fit on the board

	x = x/scalex;
	y = y/scaley;

	//cout<<x<<" , "<<y<<endl;

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

void Map::drawLabelX() {
	int x = yaxisloc+4;
	int y = xaxisloc;
	int spacing=1;
	for(auto it = Xlabels.begin(); it != Xlabels.end(); it++) {
		display->place(window, *it, x, y, 0);
		std::string a = *it;
		x = x + a.length() +1+spacing;
		if(!display->isValidCursor(window, x,y)) break;
	}


}
void Map::drawLabelY() {
	int x = yaxisloc-ylabelsize+1;
	int y = 0;
	for(auto it = Ylabels.begin(); it != Ylabels.end(); it++) {
		std::string a = *it;
		display->place(window, *it, x, y, 0);
		++y;
		if(!display->isValidCursor(window, x,y)) break;
	}

}
void Map::drawaxisX() {
	//draw axis cause why not
	int x = ylabelsize+2;
	int y = yzero;
	for (int i = 0; i < theMap[xaxisloc].size()-ylabelsize-1; i++) {
		display->next(window, '_',x,y,1);
		display->next(window, '_',x,y,1);
	}
}
void Map::drawaxisY() {
	//draw axis cause why not
	int x = ylabelsize+1;
	int y = 0;
	for (int i = 0; i < theMap.size(); i++) {
		display->place(window, '|',x,y,1);
		y++;
	}
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
	Xlabels.clear();
	for (int i = 0; i < theMap[xaxisloc].size(); i++) {
		if(i < labels.size()) {
			Xlabels.push_back(labels[i]);
		} else {
			Xlabels.push_back(" ");
		}
	}
	return; 

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
	Ylabels.clear();
	for (int i = 0; i < theMap.size(); i++) {
		if(i < labels.size()) {
			Ylabels.push_back(labels[i]);
		} else {
			Ylabels.push_back("");
		}
	}
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


		// add in blank spaces for x axis to keep rows even
		for (int k = 0; k < longest; k++) {
			alabel.push_back(' ');
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
	display->resize(window, 2*length+longest-2,width);
 	length = length + longest -1;

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

CoordinateGrid::CoordinateGrid(int size, Display * dis) : Map(size, size, dis) {
	length = size;
	width = size;

	xzero = yaxisloc+1;
	yzero = xaxisloc-1;

}
