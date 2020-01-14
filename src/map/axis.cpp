#include "map/base.hpp"

// Axis getters and setters

void Map::setXaxis(int val) {
	axisloc.x = val;
	zero.y = val;
}

void Map::setYaxis(int val) {
	axisloc.y = val;
	zero.x = val;
}

void Map::setYLabelSize(int val) {
	// the math is done verbosely here on purpose
	int oldYlabelSize = labelsize.y;
	int shift = val - oldYlabelSize;

	// Set label size
	labelsize.y = val;

	// shift the yaxix
	setYaxis(axisloc.y + shift);

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