#include "map/point.h"

Point& Point::operator+=(const Point& rhs) {
    int dim = this->getDimension();
    if(dim != rhs.getDimension()) return *this;

    // Figure out if rhs contains ints or doubles
    // Then figure out if I am an int or double
    // After that for each coordinate, operate.
    if(rhs.isTypeInteger()) {
        if(isInteger)
            for(int d = 0; d < dim; d++) {this->int_coord[d] += rhs.int_coord[d];}
        else
            for(int d = 0; d < dim; d++) {this->double_coord[d] += rhs.int_coord[d];}
    } else {
        if(isInteger)
            for(int d = 0; d < dim; d++) {this->int_coord[d] += (int)rhs.double_coord[d];}
        else
            for(int d = 0; d < dim; d++) {this->double_coord[d] += rhs.double_coord[d];}
    }

    return *this;
}
Point& Point::operator-=(const Point& rhs) {
    int dim = this->getDimension();
    if(dim != rhs.getDimension()) return *this;

    // Figure out if rhs contains ints or doubles
    // Then figure out if I am an int or double
    // After that for each coordinate, operate.
    if(rhs.isTypeInteger()) {
        if(isInteger)
            for(int d = 0; d < dim; d++) {this->int_coord[d] -= rhs.int_coord[d];}
        else
            for(int d = 0; d < dim; d++) {this->double_coord[d] -= rhs.int_coord[d];}
    } else {
        if(isInteger)
            for(int d = 0; d < dim; d++) {this->int_coord[d] -= (int)rhs.double_coord[d];}
        else
            for(int d = 0; d < dim; d++) {this->double_coord[d] -= rhs.double_coord[d];}
    }
    return *this;
}

Point& Point::operator*=(const Point& rhs) {
    int dim = this->getDimension();
    if(dim != rhs.getDimension()) return *this;

    // Figure out if rhs contains ints or doubles
    // Then figure out if I am an int or double
    // After that for each coordinate, operate.
    if(rhs.isTypeInteger()) {
        if(isInteger)
            for(int d = 0; d < dim; d++) {this->int_coord[d] *= rhs.int_coord[d];}
        else
            for(int d = 0; d < dim; d++) {this->double_coord[d] *= rhs.int_coord[d];}
    } else {
        if(isInteger)
            for(int d = 0; d < dim; d++) {this->int_coord[d] *= (int)rhs.double_coord[d];}
        else
            for(int d = 0; d < dim; d++) {this->double_coord[d] *= rhs.double_coord[d];}
    }
    return *this;
}
Point& Point::operator/=(const Point& rhs) {
    int dim = this->getDimension();
    if(dim != rhs.getDimension()) return *this;

    // Figure out if rhs contains ints or doubles
    // Then figure out if I am an int or double
    // Then check if any rhs coordinate is zero
    // After that for each coordinate, operate.
    if(rhs.isTypeInteger()) {
        for(int d = 0; d < dim; d++) {if(rhs.int_coord[d]==0) return *this;}
        if(isInteger)
            for(int d = 0; d < dim; d++) {this->int_coord[d] /= rhs.int_coord[d];}
        else
            for(int d = 0; d < dim; d++) {this->double_coord[d] /= rhs.int_coord[d];}
    } else {
        for(int d = 0; d < dim; d++) {if(rhs.double_coord[d]==0) return *this;}
        if(isInteger)
            for(int d = 0; d < dim; d++) {this->int_coord[d] /= (int)rhs.double_coord[d];}
        else
            for(int d = 0; d < dim; d++) {this->double_coord[d] /= rhs.double_coord[d];}
    }
    return *this;
}

Point& Point::operator+=(const double vald) {
    if(this->isTypeInteger()) {
        for(int d = 0; d < this->getDimension(); d++) {this->int_coord[d] += (int)vald;}
    } else {
        for(int d = 0; d < this->getDimension(); d++) {this->double_coord[d] += vald;}
    }
    return *this;
}
Point& Point::operator-=(const double vald) {
    if(this->isTypeInteger()) {
        for(int d = 0; d < this->getDimension(); d++) {this->int_coord[d] -= (int)vald;}
    } else {
        for(int d = 0; d < this->getDimension(); d++) {this->double_coord[d] -= vald;}
    }
    return *this;
}
Point& Point::operator*=(const double vald) {
    if(this->isTypeInteger()) {
        for(int d = 0; d < this->getDimension(); d++) {this->int_coord[d] -= (int)vald;}
    } else {
        for(int d = 0; d < this->getDimension(); d++) {this->double_coord[d] -= vald;}
    }
    return *this;
}
Point& Point::operator/=(const double vald) {
    if(vald==0) return *this;
    if(this->isTypeInteger()) {
        for(int d = 0; d < this->getDimension(); d++) {this->int_coord[d] /= vald;}
    } else {
        for(int d = 0; d < this->getDimension(); d++) {this->double_coord[d] /= vald;}
    }
    return *this;
}

Point& Point::operator+=(const int vali) {
    if(this->isTypeInteger()) {
        for(int d = 0; d < this->getDimension(); d++) {this->int_coord[d] += vali;}
    } else {
        for(int d = 0; d < this->getDimension(); d++) {this->double_coord[d] += vali;}
    }
    return *this;
}
Point& Point::operator-=(const int vali) {
    if(this->isTypeInteger()) {
        for(int d = 0; d < this->getDimension(); d++) {this->int_coord[d] -= vali;}
    } else {
        for(int d = 0; d < this->getDimension(); d++) {this->double_coord[d] -= vali;}
    }
    return *this;
}
Point& Point::operator*=(const int vali) {
    if(this->isTypeInteger()) {
        for(int d = 0; d < this->getDimension(); d++) {this->int_coord[d] -= vali;}
    } else {
        for(int d = 0; d < this->getDimension(); d++) {this->double_coord[d] -= vali;}
    }
    return *this;
}
Point& Point::operator/=(const int vali) {
    if(vali==0) return *this;
    if(this->isTypeInteger()) {
        for(int d = 0; d < this->getDimension(); d++) {this->int_coord[d] /= vali;}
    } else {
        for(int d = 0; d < this->getDimension(); d++) {this->double_coord[d] /= vali;}
    }
    return *this;
}



 
Point operator+(Point lhs, const Point &rhs) { lhs += rhs; return lhs; } 
Point operator-(Point lhs, const Point &rhs) { lhs -= rhs; return lhs; } 
Point operator*(Point lhs, const Point &rhs) { lhs *= rhs; return lhs; } 
Point operator/(Point lhs, const Point &rhs) { lhs /= rhs; return lhs; } 

Point operator+(Point rhs, const double d)    { rhs += d; return rhs; } 
Point operator-(Point rhs, const double d)    { rhs -= d; return rhs; } 
Point operator*(Point rhs, const double d)    { rhs *= d; return rhs; } 
Point operator/(Point rhs, const double d)    { rhs /= d; return rhs; } 
 
Point operator+(Point rhs, const int i)       { rhs += i; return rhs; } 
Point operator-(Point rhs, const int i)       { rhs -= i; return rhs; } 
Point operator*(Point rhs, const int i)       { rhs *= i; return rhs; } 
Point operator/(Point rhs, const int i)       { rhs /= i; return rhs; } 

std::ostream& operator<<(std::ostream& os,  Point const& point) {
    int roundDigits=3;    
    os << "(";
    if(point.isTypeInteger()) {
        for(int d = 0; d < point.getDimension(); d++) {
            if(d) os << ",";
            os << point.get((PointType)d);
        }
    } else {
        for(int d = 0; d < point.getDimension(); d++) {
            if(d) os << ",";
            os << roundToPlace(point.get((PointType)d), roundDigits);
        }
    }
    os << ")";

    return os;
}

bool operator==(const Point &lhs, const Point &rhs) { 
    // First check if they're of the same dimension
    int dim = lhs.getDimension();
    if(dim != rhs.getDimension()) return false;
    if(dim<=0) return false;

    // Then check if they have the same type
    if(lhs.isTypeInteger() != rhs.isTypeInteger()) return false;

    // Now check if the values are the same 
    bool check = true;
    if(lhs.isTypeInteger()) {
        for(int d = 0; d < dim; d++) {
            check = check && lhs.getI((PointType)d) == rhs.getI((PointType)d);
        }
    } else {
        for(int d = 0; d < dim; d++) {
            check = check && lhs.get((PointType)d) == rhs.get((PointType)d);
        }
    }

    return check;
}

bool operator!=(const Point &lhs, const Point &rhs) {return !operator==(lhs,rhs);}

double slope(Point& final, Point& initial) {
    double rise = (final.get(_y_) - initial.get(_y_));
    double run = (final.get(_x_) - initial.get(_x_));
    if(run) return rise/run;
    else return std::numeric_limits<double>::infinity();
}

double intercept(Point& final, Point& iniital) {
    double m = slope(final, iniital);
    double inf = std::numeric_limits<double>::infinity();

    // Verticle line
    if(m==inf) {
        if(final.get(_x_)) return NAN;      // Not Y axis
        else return inf;                    // Y axis
    }

    return final.get(_y_)-(m*final.get(_x_));
}

void makePointInteger(Point& p) {
    int dim = p.getDimension();
    Point result;
    if(dim==1) {
        result = Point(p.getDirection(), (int)p.get(p.getDirection()));
    } else if(dim==2) {
        result = Point((int)p.get(_x_), (int)p.get(_y_));
    } else if(dim==3) {
        result = Point((int)p.get(_x_), (int)p.get(_y_), (int)p.get(_z_));
    } else {
        return;
    }
    p = result;
}
void makePointDouble(Point& p) {
    int dim = p.getDimension();
    Point result;
    if(dim==1) {
        result = Point(p.getDirection(), (double)p.get(p.getDirection()));
    } else if(dim==2) {
        result = Point((double)p.get(_x_), (double)p.get(_y_));
    } else if(dim==3) {
        result = Point((double)p.get(_x_), (double)p.get(_y_), (double)p.get(_z_));
    } else {
        return;
    }
    p = result;
}