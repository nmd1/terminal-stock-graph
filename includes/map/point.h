#ifndef POINT_H
#define POINT_H

#include <iostream>
#include "extra.h"

typedef enum {_x_,_y_,_z_,_bad_} PointSelect;

class Point {
    public:

        // Constructors
        Point();
        Point(double);
        Point(double, double);
        Point(double, double, double);


        
        // Arithmatic operator overloads
        // only operated on the amount of
        // dimensions that exist
        Point& operator+=(const Point&);
        Point& operator-=(const Point&);
        Point& operator*=(const Point&);
        Point& operator/=(const Point&);

        Point& operator+=(const double);
        Point& operator-=(const double);
        Point& operator*=(const double);
        Point& operator/=(const double);


        // Getters
        double get(PointSelect) const;
        bool is1D() const; 
        bool is2D() const;
        bool is3D() const;
        int getDimension() const;

        // Internally rounds off the number
        void roundoffCoords(int, PointSelect=_bad_);
        void roundoffCoords(double, PointSelect=_bad_);


    private:
        double x;
        double y;
        double z;
        int dimension;


};

// Operator overloads
Point operator+(Point, const Point &);
Point operator-(Point, const Point &);
Point operator*(Point, const Point &);
Point operator/(Point, const Point &);

Point operator+(Point,  const double);
Point operator-(Point,  const double);
Point operator*(Point,  const double);
Point operator/(Point,  const double);

std::ostream& operator<<(std::ostream&, Point const&);

bool operator==(const Point&, const Point&);
bool operator!=(const Point&, const Point&);

#endif