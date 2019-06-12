#include "map/base.h"

// Axis getters and setters

void Map::setXaxis(int val) {
	xaxisloc = val;
	yzero = val;
}

void Map::setYaxis(int val) {
	yaxisloc = val;
	xzero = val;
}

void Map::setYLabelSize(int val) {
	// the math is done verbosely here on purpose
	int oldYlabelSize = ylabelsize;
	int shift = val - oldYlabelSize;

	// Set label size
	ylabelsize = val;

	// shift the yaxix
	setYaxis(yaxisloc + shift);

	// Change the length of the window
	length = length + shift;

}



/*

int xaxisloc;
int yaxisloc;
int xzero;
int yzero;
int ylabelsize;
*/