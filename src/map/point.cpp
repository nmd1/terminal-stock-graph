#include "map/point.h"

// Default behavior for something like this
Point::Point() : isInteger(true) {
    int_coord = std::vector<int> (2); 
    int_coord[_x_] = 0;
    int_coord[_y_] = 0;
}

Point::Point(double xin) : isInteger(false) {
    double_coord = std::vector<double> (1); 
    double_coord[_x_] = xin;
    direction=_x_;
}

Point::Point(double xin, double yin) : isInteger(false) {
    double_coord = std::vector<double> (2); 
    double_coord[_x_] = xin;
    double_coord[_y_] = yin;
}

Point::Point(double xin, double yin, double zin) : isInteger(false) {
    double_coord = std::vector<double> (3); 
    double_coord[_x_] = xin;
    double_coord[_y_] = yin;
    double_coord[_z_] = zin;
}

Point::Point(PointType sel,double val) : isInteger(false) {
    if(sel!=_x_ && sel != _y_ && sel != _z_) sel = _x_; // set default
    double_coord = std::vector<double> (1); 
    double_coord[sel] = val;
    direction = sel;
}

Point::Point(int xin) : isInteger(true) {
    int_coord = std::vector<int> (1); 
    int_coord[_x_] = xin;
    direction=_x_;
}

Point::Point(int xin, int yin) : isInteger(true) {
    int_coord = std::vector<int> (2); 
    int_coord[_x_] = xin;
    int_coord[_y_] = yin;
}

Point::Point(int xin, int yin, int zin) : isInteger(true) {
    int_coord = std::vector<int> (3); 
    int_coord[_x_] = xin;
    int_coord[_y_] = yin;
    int_coord[_z_] = zin;
}

Point::Point(PointType sel,int val) : isInteger(true) {
    if(sel!=_x_ && sel != _y_ && sel != _z_) sel = _x_; // set default
    int_coord = std::vector<int> (1); 
    int_coord[sel] = val;
    direction = sel;
}



void Point::roundoffCoords(int roundoff, PointType coordinate) {
    bool doall = coordinate==_bad_;
    if(isTypeInteger()) return;
    for(int d = 0; d < getDimension(); d++) {
        if(d==coordinate || doall) {
            double_coord[d]=roundToPlace(double_coord[d], roundoff);
        }
    }
}

void Point::roundoffCoords(double roundoff, PointType coordinate) {
    bool doall = coordinate==_bad_;
    if(isTypeInteger()) return;
    for(int d = 0; d < getDimension(); d++) {
        if(d==coordinate || doall) {
            double_coord[d]=roundToPlace(double_coord[d], roundoff);
        }
    }
}

// Getters
bool Point::is1D() const {return getDimension()==1;}
bool Point::is2D() const {return getDimension()==2;}
bool Point::is3D() const {return getDimension()==3;}

int  Point::getDimension() const {
    if(isInteger) return int_coord.size();
    else return double_coord.size();
}

PointType Point::getDirection() const {return direction;}

bool Point::isTypeDouble()  const {return !isInteger;}
bool Point::isTypeInteger() const {return isInteger;}

double Point::get(PointType type) const {
    if(type<0 || type > getDimension()) return 0;

    if(isInteger) return int_coord[type];
    else return double_coord[type];
}

int Point::getI(PointType type) const {
    if(type<0 || type > getDimension()) return 0;

    if(isInteger) return int_coord[type];
    else return (int)double_coord[type];
}


void Point::set(int x) {
    if(getDimension()!=1) return;
    if(isInteger) {
        int_coord[direction] = x;
    } else {
        double_coord[direction] = x;
    }
}
void Point::set(int x, int y) {
    if(getDimension()!=2) return;
    if(isInteger) {
        int_coord[_x_] = x;
        int_coord[_y_] = y;
    } else {
        double_coord[_x_] = x;
        double_coord[_y_] = y;
    }
}
void Point::set(int x, int y, int z) {
    if(getDimension()!=3) return;
    if(isInteger) {
        int_coord[_x_] = x;
        int_coord[_y_] = y;
        int_coord[_z_] = z;
    } else {
        double_coord[_x_] = x;
        double_coord[_y_] = y;
        double_coord[_z_] = z;
    }
}
void Point::set(PointType type, int val) {
    if(type<0 || type > getDimension()) return;

    if(isInteger) int_coord[type] = val;
    else double_coord[type] = val;
}



void Point::set(double x) {
    if(getDimension()!=1) return;
    if(isInteger) {
        int_coord[direction] = (int)x;
    } else {
        double_coord[direction] = x;
    }
}
void Point::set(double x, double y) {
    if(getDimension()!=2) return;
    if(isInteger) {
        int_coord[_x_] = (int)x;
        int_coord[_y_] = (int)y;
    } else {
        double_coord[_x_] = x;
        double_coord[_y_] = y;
    }
}
void Point::set(double x, double y, double z) {
    if(getDimension()!=3) return;
    if(isInteger) {
        int_coord[_x_] = (int)x;
        int_coord[_y_] = (int)y;
        int_coord[_z_] = (int)z;
    } else {
        double_coord[_x_] = x;
        double_coord[_y_] = y;
        double_coord[_z_] = z;
    }
}
void Point::set(PointType type, double val) {
    if(type<0 || type > getDimension()) return;

    if(isInteger) int_coord[type] = val;
    else double_coord[type] = val;
}
