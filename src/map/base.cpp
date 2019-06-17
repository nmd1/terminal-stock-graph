#include "map/base.h"


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

Map::Map(int l, int w, bool trans) : Map(l,w) {
	if(trans) space = transparent;
}
Map::Map(int l, int w) {
	length = l;
	width = w;
	// Shift the center of the Y axis because of the label size
	axisloc.y = (length)/2;
	axisloc.x = (width-1)/2;

	// Set where zero is
	zero.x = axisloc.y;
	zero.y = axisloc.x;

	quadrantn.x = 2;
	quadrantn.y = 2;

	// Characters to use in graphs
	labelsize.y = 1;
	labelsize.x = 1;


	maxval.x = xBoardLength()/2;
	minval.x = -xBoardLength()/2;
	maxval.y = yBoardLength()/2;
	minval.y = -yBoardLength()/2;

	space = '.';
	defaultempty = '.';
	xline = '_';
	yline = '|';
	nothing = ' ';
	point = '#';
	mark = ',';
	transparent = 'X';

	// Set up the window
	//window = display->newWindow(w,l,0,0);
	
	if(width < 4 || length < 4) throw "Object Failed";

}

void Map::create() {
	std::string temp_char_label = " ";
	for(int i = 0; i < width; i++) {
		std::vector<char> rowfill;
		for(int j = 0; j < length; j++) {
			if(j==axisloc.y-1 && i != axisloc.x) {
				rowfill.push_back(temp_char_label[0]);
			} else if(j==axisloc.y) {
				rowfill.push_back(yline);
			} else {
				if (i==axisloc.x && j==axisloc.y-1) {
					rowfill.push_back(nothing);
				} else if (i==axisloc.x+1) {
					rowfill.push_back(' ');
				} else if(i==axisloc.x) {
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
	graphwin<<std::endl<<std::endl;
	for(int i = 0; i < width; i++) {
		for(int j = 0; j < length; j++) {
			graphwin<<theMap[i][j];
		}
		graphwin<<std::endl;
	}
}


void Map::clear() {
	for(int x = getMinX(gM_internal); x <= getMaxX(gM_internal); x++) {
		for(int y = getMaxY(gM_internal); y <= getMinY(gM_internal); y++) {
			if(y > axisloc.x && y < axisloc.x+2) continue;
			if(x > axisloc.y-labelsize.y-1 && x < axisloc.y) continue;

			if(x==axisloc.y) { theMap[y][x] = yline; continue; }
			if(y==axisloc.x) { theMap[y][x] = xline; continue; }

			theMap[y][x] = space;
		}
	}
}

std::vector< std::vector<char> > const * Map::getMap() {
	return &theMap;
}

bool Map::getRawCoord(double &x, double &y) {
	// Rescale down to coords that would fit on the board

	// Turn on debug print statements
	bool localdebug = true;

	// First, some metadata about what type of graph you are:
	bool timegraph = false;
	bool ptimegraph = false;


	if(getMinX(gM_internal)==labelsize.y) { // we're in a TimeGraph
		timegraph = true;
		if(getMinY(gM_internal)==width-2)  // we're in a PosTimeGraph
			ptimegraph = true;
	}

	///////if(timegraph) yaxisloc+=1; // hack, yaxisloc everywhere else is wrong. Fix later.



	// Calculate Zeros (aka midpoints)
	double realxzero = (getMaxX(gM_real) + getMinX(gM_real))/2;
	double realyzero = (getMaxY(gM_real) + getMinY(gM_real))/2;

	// Calculate Ranges
	double rangex = (getMaxX(gM_real) - getMinX(gM_real));
	double rangey = (getMaxY(gM_real) - getMinY(gM_real));

	// [Balance]
	double x1 = x - realxzero;
	double y1 = y - realyzero;

	debugf<<"xlen rangex: "<<xBoardLength()<<" "<<rangex<<std::endl;
	// [(Negative) Normalization]
	double x2 = ( 1) * (x1 / (rangex/quadrantn.x));
	double y2 = (-1) * (y1 / (rangey/quadrantn.y));

	// [Scale]
	double x3 = x2 * (xBoardLength()/quadrantn.x);
	double y3 = y2 * (yBoardLength()/quadrantn.y);

	//debugf<<"axisloc: "   <<yaxisloc+1<< " , "<<(axisloc.x-1)<<std::endl;

	// [Reposition]
	int reposition_offsetx = axisloc.y;
	int reposition_offsety = axisloc.x;

	if(timegraph) { // we're in a TimeGraph
		reposition_offsetx = -(getMinX(gM_real)-realxzero)*(xBoardLength()/rangex);
		if(localdebug) debugf<<"we're in a timegraph! (offsetx = "<<reposition_offsetx<<")";
		if(ptimegraph) { // we're in a PosTimeGraph
			reposition_offsety = -(getMinY(gM_real)-realyzero)*(yBoardLength()/rangey);
			if(localdebug) debugf<<" A Positive one! (offsety = "<<reposition_offsety<<")";
		}
		if(localdebug) debugf<<std::endl;
	}
	

	double x4 = x3 + reposition_offsetx;
	double y4 = y3 + reposition_offsety;


	
	// Round
	int finaly = round(y4);
	int finalx = round(x4);

	if(localdebug) { 
		debugf<<"Input: "   <<x<< " , "<<y<<std::endl;
		debugf<<"Balance: " <<x1<<" , "<<y1<<std::endl;
		debugf<<"Norm: "    <<x2<<" , "<<y2<<std::endl;
		debugf<<"Scale: "   <<x3<<" , "<<y3<<std::endl;
		debugf<<"Respos: "  <<x4<<" , "<<y4<<std::endl;
		debugf<<std::endl;
		debugf<<"(yaxisl: "<<axisloc.y<<")"<<std::endl;
		debugf<<"(xaxisl: "<<axisloc.x<<")"<<std::endl;
		debugf<<std::endl;
		debugf<<"Round: "   <<finalx<<" , "<<finaly<<std::endl;
	}

	// Skip over labels

	// push y down
	if(!ptimegraph)	if(finaly > axisloc.x) finaly+=1;
	if(timegraph) {
		// push x forward, 
		finalx+=labelsize.y; 
	} else {
		// push x backwards, if past certain point
		if(finalx < axisloc.y) finalx-=labelsize.y;
	}


	////////if(timegraph) axisloc.y-=1; // hack, yaxisloc everywhere else is wrong. Fix later.


	if(localdebug) debugf<<"Final: "   <<finalx<<" , "<<finaly<<std::endl;




	// check bounds 
	if(finaly<0) return false;
	if(finalx<0) return false;
	if(finaly>=(int)theMap.size()) return false;
	if(finalx>=(int)theMap[finaly].size()) return false;

	x = finalx;
	y = finaly;

	if(localdebug) debugf<<"Success!"<<std::endl;
	if(localdebug) debugf<<"--------------------------"<<std::endl;

	return true;

}

// Sets coordinates for generic map
bool Map::setCoord(double x, double y) {
	bool returnval = getRawCoord(x, y);
	int xin = (int)x;
	int yin = (int)y;
	//debugf<<"("<<xin<<","<<yin<<")"<<std::endl;
	if(returnval) theMap[yin][xin] = point;	
	return returnval;
}


// Auto label based on how many labels we have
void Map::setLabelX(std::vector<std::string> labels) {
	Xlabels.clear();
	for (unsigned i = 0; i < theMap[zero.y+1].size(); i++) {
		if(i < labels.size()) {
			Xlabels.push_back(labels[i]);
		} else {
			Xlabels.push_back(" ");
		}
	}

	// Fill in the map with the labels
	int j = zero.x;
	for(unsigned i = 0; i < labels.size(); i++) {
		unsigned k = 0;
		for (; k < labels[i].size(); j++, k++) {
			theMap[zero.y+1][j] = labels[i][k];
		}
		theMap[zero.y+1][++j] = ' ';
	}
	return; 
}

// Use this for setting labels
void Map::setLabelX(std::string label, double xin) {
	double y = 0;

	if(!getRawCoord(xin, y)) return;
	int x = (int)xin;
	y++;

	debugf<<"x: "<<x<<std::endl<<"Result: "<<labelsize.x<<std::endl;

	if((x)%(labelsize.x)) {return;}
	//if(!((x+xlabelsize)< getMaxX(gM_internal) )) {return;}
	// Ensure there's a space between each label
	label[labelsize.x-1] = ' ';

	// Fill in the row with the label
	for (unsigned k =0; k < labelsize.x; x++, k++) {
		theMap[y][x] = label[k];
	}
}

void Map::autoLabelX(double zero, double zeroy, int type, double delta_override) {

	// For positive values
	// this calculation changes depending on what graph you are.
	double delta = ((getMaxX(gM_real)-getMinX(gM_real))) / (xBoardLength());

	debugf<<"del:"<<delta<<std::endl;
	double yin = zeroy, xin = zero;

	//for testing sameness
	std::string prevl = "";
	if(!getRawCoord(xin, yin)) throw "Something Very bad happend - (0,0) Doesn't Exist.";
	int y = axisloc.x+1;
	int x = (int)(xin);
	int wherexiszero = x;
	//the loop
	for(int i = x; i<=(int)getMaxX(gM_internal); i++) {

		// Based on where we are on the graph
		// Calculate what the x value should be
		double dlabel = zero + ( (i-x)*delta);

		// Neatly round off numbers based on delta_override value
		// Default behavior is to give raw calculated values from above
		if(delta_override) {
			double roundedv = roundToNearest(dlabel, delta_override);
			//debugf<<"Value: "<<dlabel<<std::endl<<"Rounded: "<<roundedv<<std::endl<<"["<<areSame(dlabel, roundedv, delta)<<"]"<<std::endl<<std::endl;
			if(areSame(dlabel, roundedv, delta)) {
				dlabel = roundedv;
			} else continue;
		}

		// Round to integer if we only want integer labels
		// Round to size of label otherwise. Either way generate string
		std::string label; 
		switch(type) {
			// Integer
			case 1: {
				label = std::to_string((int)round(dlabel));
				break;
			}

			// Time
			case 2: {
				label = makeTime((time_t)round(dlabel));
				break;
			}

			// Default, normal behavior
			case 0:
			default:
				int roundoff = labelsize.x;
				//roundoff one less if you're negative (b/c sign)
				if(dlabel<0) --roundoff;
				label = std::to_string(roundToPlace(dlabel,roundoff));
				break;
		}


		// skip label if same as last time
		if(label == prevl) continue; 

		// Put label on x axis
		if(i!=wherexiszero) theMap[y-1][i]=mark;
		for (unsigned k =0; k < labelsize.x-1 && i<=(int)getMaxX(gM_internal); i++, k++) {
			if(k<label.size()) theMap[y][i] = label[k];
		}


		prevl = label;

	}
	//the negative loop
	//yin = 0, xin = -1;
	//if(!getRawCoord(xin, yin)) return; //There's no -1, so I assume it's a pos graph
	
	//y = (int)(++yin);
	int xstart = wherexiszero-labelsize.y-1;

	//debugf<<"("<<xstart<<","<<y<<")"<<std::endl<<std::endl;
	bool cleared_for_labeling = false;
	prevl = "";
	int last_valid_i = 0;
	// i loops from 0 --> negative end of graph (real values)
	// xi loops from [where x=-1] --> negative end of graph (internal values)
	for(int xi = xstart, i = 0; xi>getMinX(gM_internal); xi--, i++) {

		// Check if you're gtg for labeling
		// (also fix this check it's logically messy)
		if(!cleared_for_labeling) {
			cleared_for_labeling = ((i-last_valid_i)%labelsize.x)==(labelsize.x-1);
		}
		if(!cleared_for_labeling) continue;



		//debugf<<"Cleared for Labeling!: x="<<xi-xstart-1<<std::endl;
		
		// Based on where we are on the graph
		// Calculate what the x value should be
		double dlabel = zero + ((xi-xstart-1)*delta);

		// Neatly round off numbers based on delta_override value
		// Default behavior is to give raw calculated values from above
		if(delta_override) {
			double roundedv = roundToNearest(dlabel, delta_override);
			if(areSame(dlabel, roundedv, delta)) {
				dlabel = roundedv;
				//debugf<<"Delta Override approved!"<<std::endl;
			} else {
				continue;
			}
		}


		// Round to integer if we only want integer labels
		// Round to size of label otherwise. Either way generate string
		std::string label; 
		switch(type) {
			// Integer
			case 1: {
				label = std::to_string((int)round(dlabel));
				break;
			}

			// Time
			case 2: {
				label = makeTime((time_t)round(dlabel));
				break;
			}

			// Default, normal behavior
			case 0:
			default:
				int roundoff = labelsize.x;
				//roundoff one less if you're negative (b/c sign)
				if(dlabel<0) --roundoff;
				label = std::to_string(roundToPlace(dlabel,roundoff));
				break;
		}



		// skip label if same as last time
		if(label == prevl) continue;

		// Alright, all checks have been done, we're going to label:
		theMap[y-1][xi]=mark;
		for (unsigned k=xi, j=0; j < (labelsize.x-1); k++, j++) {
			//unsigned reverse_k = label.size() - 1 - k;
			//debugf<<"k:"<<k<<" x:"<<(int)k-xstart<<" i:"<<i<<" ("<<label[j]<<")"<<std::endl;
			if(j<label.size()) theMap[y][k] = label[j];
		}
		last_valid_i = i+1;
		// We just labeled, move away to create some space for the new label
		cleared_for_labeling = false; 
		prevl = label;

	}
}


void Map::autoLabelY(double zerox, double zero, int type, double delta_override) {	
	// For positive values

	// TODO: This calculation should change depending on what graph you are
	double delta = ((getMaxY(gM_real)-getMinY(gM_real))) / (yBoardLength());


	double yin = zero, xin = zerox;

	// Test for sameness
	std::string prevl = "";

	if(!getRawCoord(xin, yin)) throw "Something Very bad happend - (0,0) Doesn't Exist.";
	int whereyiszero = (int)(axisloc.x);
	int x = (int)(xin) - labelsize.y;

	// Shift down y values when y is negative
	int shiftwhenneg = 0;
	//the loop (top to bottom)
	for(int i = getMaxY(gM_internal); i<=getMinY(gM_internal); i++) {
		
		// Based on where we are on the graph
		// Calculate what the y value should be
		int y = -(i-whereyiszero);
		//debugf<<"y: "<<y<<std::endl;

		// skip over x axis (maybe put something in middle of map?)
		if(y==-1) shiftwhenneg = 1;
		y = y+shiftwhenneg;

		double dlabel = zero + ( (y)*delta);

		// Neatly round off numbers based on delta_override value
		// Default behavior is to give raw calculated values from above
		if(delta_override) {
			double roundedv = roundToNearest(dlabel, delta_override);
			if(areSame(dlabel, roundedv, delta)) {
				dlabel = roundedv;
			} else continue;
		}

		// Round to integer if we only want integer labels
		// Round to size of label otherwise. Either way generate string
		std::string label; 

		switch(type) {
			// Integer
			case 1: {
				label = std::to_string((int)round(dlabel));
				break;
			}

			// Default, normal behavior
			case 0:
			default:
				int roundoff = labelsize.y;
				//roundoff one less if you're negative (b/c sign)
				if(dlabel<0) --roundoff;
				label = std::to_string(roundToPlace(dlabel,roundoff));
				break;
		}

		// Handle duplicates
		if(label == prevl) {
			if (y < 0) {
				// Clear out the previous label
				for (unsigned k=x; k < x+labelsize.y; k++) 
					theMap[i+1][k] = ' ';
			} else {
				// Clear out this label
				label = "";
			}
			continue;
		}
		// Put label on y axis
		// First write in empty spaces
		int xwrite = x + labelsize.y - label.size();
		// Then write in characters
		for (unsigned k=x, l=0; k < x+labelsize.y; k++) {
			if((int)k<xwrite) {
				theMap[i][k] = ' ';
			} else {
				theMap[i][k] = label[l];
				l++;
			}
		}

		prevl = label;


	}
	return;
}


void Map::setLabelY(std::string label, double yin) {
	double x = 0;
	if(!getRawCoord(x, yin)) return;

	int y = (int)yin;
	x = axisloc.y-labelsize.y;


	// Fill in the row with the label
	for (unsigned k =0; k < label.size(); x++, k++) {
		if(!(x<axisloc.y)) break;
		theMap[y][x] = label[k];

		//debugf<<"fillin in"<<std::endl;
	}
}

void Map::resizeLabelX(int s) {
	labelsize.x = ++s; // add one for spacing
}
void Map::resizeLabelY(unsigned int s) {
	//if(Ylabels.size()==0) return; //there are no ylabels....


    unsigned int longest = s; //if it ain't broke don't fix it

    for(unsigned i = 0; i < theMap.size(); i++) {
    	std::vector<char> row = theMap[i];

		// Split the current row into two vectors,
		// Generate a new vector<char> that is made up
		// of characters from the label, and combine 
		// the three 
    	
    	// Split
    	std::vector<char> result(row.begin(), row.begin() + axisloc.y - labelsize.y);
		std::vector<char> split_hi(row.begin()+axisloc.y, row.end());			
		
		// Create char label vector
		std::vector<char> alabel;


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
	//display->resize(window,length,width);
}



void Map::setLabelY(std::vector<std::string> labels) {
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
		if(i < (int)labels.size() && i!=zero.y+1) {
			Ylabels.push_back(labels[j]);
			j++;
		} else {
			std::string blanks(longest, ' ');
			Ylabels.push_back(blanks);
		}
	}

    std::cout<<"longest is "<<longest<<std::endl;

    for(unsigned i = 0; i < theMap.size(); i++) {
    	std::vector<char> row = theMap[i];

		// Split the current row into two vectors,
		// Generate a new vector<char> that is made up
		// of characters from the label, and combine 
		// the three 
    	
    	// Split
    	std::vector<char> result(row.begin(), row.begin() + axisloc.y + 1 - labelsize.y);
		std::vector<char> split_hi(row.begin() + axisloc.y + 1 - labelsize.y + 1, row.end());			
		
		// Create char label vector
		std::vector<char> alabel;


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
	//display->resize(window, 2*length+longest-2,width);
}

void Map::makeTransparent() {
	for(int x = getMinX(gM_internal); x <= getMaxX(gM_internal); x++) {
		for(int y = getMaxY(gM_internal); y <= getMinY(gM_internal); y++) {
			if(theMap[y][x] == space) theMap[y][x] = transparent;
		}
	}
	space = transparent;
}
void Map::makeOpaque() {
	for(int x = getMinX(gM_internal); x <= getMaxX(gM_internal); x++) {
		for(int y = getMaxY(gM_internal); y <= getMinY(gM_internal); y++) {
			if(theMap[y][x] == transparent) theMap[y][x] = defaultempty;
		}
	}
	space = defaultempty;
}


/*******************************************************************/

CoordinateGrid::CoordinateGrid(int size) : Map(size, size) {
	length = size;
	width = size;

	if(size < 4) throw "Object Failed";

}

CoordinateGrid::CoordinateGrid(int size, bool trans) : CoordinateGrid(size) {
	if(trans) space = transparent;
}

