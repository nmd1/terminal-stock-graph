#include "map/point.h"

// Default behavior for something like this
Point::Point() {
    x=0;
    y=0;
    dimension=2;
}

Point::Point(double xin) 
: dimension(1), x(xin), y(0), z(0) {}

Point::Point(double xin, double yin) 
: dimension(2), x(xin), y(yin), z(0) {}

Point::Point(double xin, double yin, double zin) 
: dimension(3), x(xin), y(yin), z(zin) {}


void Point::roundoffCoords(int roundoff, PointSelect coordinate) {
    bool doall = coordinate==_bad_;

    if(coordinate==_x_ || doall) x=roundToPlace(x, roundoff);
    if(coordinate==_y_ || doall) y=roundToPlace(y, roundoff);
    if(coordinate==_z_ || doall) z=roundToPlace(z, roundoff);

}

double Point::get(PointSelect coord) const {
    if(coord==_x_) return x;
    if(coord==_y_) return y;
    if(coord==_z_) return z;
    throw "something";
}



void Point::roundoffCoords(double roundoff, PointSelect coordinate) {
    bool doall = coordinate==_bad_;
    if(coordinate==_x_ || doall) x=roundToDPlace(x, roundoff);
    if(coordinate==_y_ || doall) y=roundToDPlace(y, roundoff);
    if(coordinate==_z_ || doall) z=roundToDPlace(z, roundoff);
}

// Getters
bool Point::is1D() const {return dimension==1;}
bool Point::is2D() const {return dimension==2;}
bool Point::is3D() const {return dimension==3;}
int  Point::getDimension() const {return dimension;}

