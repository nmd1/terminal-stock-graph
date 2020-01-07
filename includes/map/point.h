#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <vector>
#include <limits>
#include "extra.h"

typedef struct Point_i {
    int x;
    int y;
} Pointi;

typedef struct Point_d {
    double x;
    double y;
} Pointd;

typedef enum {_x_=0,_y_=1,_z_=2,_bad_} PointType;

class Point {
    public:

        // Constructors
        Point();
        Point(double);
        Point(double, double);
        Point(double, double, double);
        Point(PointType, double);

        Point(int);
        Point(int, int);
        Point(int, int, int);
        Point(PointType, int);

        
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

        Point& operator+=(const int);
        Point& operator-=(const int);
        Point& operator*=(const int);
        Point& operator/=(const int);

        // Getters
        bool is1D() const; 
        bool is2D() const;
        bool is3D() const;
        int getDimension() const;
        double get(PointType) const;
        int getI(PointType) const;
        bool isTypeInteger() const; 
        bool isTypeDouble() const;
        PointType getDirection() const;

        // Setters
        void set(double);
        void set(double, double);
        void set(double, double, double);
        void set(PointType, double);

        void set(int);
        void set(int, int);
        void set(int, int, int);
        void set(PointType, int);

        // Internally rounds off the number
        // only makes sense for double
        void roundoffCoords(int, PointType=_bad_);
        void roundoffCoords(double, PointType=_bad_);


    private:
        

        // C Unions only use POD
        // and using Boost varient feels like overkill
        std::vector<double> double_coord;
        std::vector<int> int_coord;
        
        // The concept of direction is used to distiguish 
        // Certain types of 1D points from others
        // If 2D or 3D, by default this makes no sense
        PointType direction=_bad_;

        // What type of point class is this?
        bool isInteger = false;

};

void makePointInteger(Point& p);
void makePointDouble(Point& p);

// Operator overloads
Point operator+(Point, const Point &);
Point operator-(Point, const Point &);
Point operator*(Point, const Point &);
Point operator/(Point, const Point &);

Point operator+(Point,  const double);
Point operator-(Point,  const double);
Point operator*(Point,  const double);
Point operator/(Point,  const double);

Point operator+(Point,  const int   );
Point operator-(Point,  const int   );
Point operator*(Point,  const int   );
Point operator/(Point,  const int   );


std::ostream& operator<<(std::ostream&, Point const&);

bool operator==(const Point&, const Point&);
bool operator!=(const Point&, const Point&);


// Operations on multiple points
double slope(Point&, Point&);
double intercept(Point&, Point&);

#endif