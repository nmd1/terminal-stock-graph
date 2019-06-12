#include "map/point.h"

Point& Point::operator+=(const Point& rhs) {
    int dim = this->getDimension();
    if(dim != rhs.getDimension()) return *this;

    if(dim>0) this->x += rhs.x;
    if(dim>1) this->y += rhs.y;
    if(dim>2) this->z += rhs.z;
    return *this;
}
Point& Point::operator-=(const Point& rhs) {
    int dim = this->getDimension();
    if(dim != rhs.getDimension()) return *this;

    if(dim>0) this->x -= rhs.x;
    if(dim>1) this->y -= rhs.y;
    if(dim>2) this->z -= rhs.z;
    return *this;
}
Point& Point::operator*=(const Point& rhs) {
    int dim = this->getDimension();
    if(dim != rhs.getDimension()) return *this;

    if(dim>0) this->x *= rhs.x;
    if(dim>1) this->y *= rhs.y;
    if(dim>2) this->z *= rhs.z;
    return *this;
}
Point& Point::operator/=(const Point& rhs) {
    int dim = this->getDimension();
    if(dim != rhs.getDimension()) return *this;

    if(dim>0) {if(rhs.x!=0) this->x /= rhs.x; else return *this;}
    if(dim>1) {if(rhs.y!=0) this->y /= rhs.y; else return *this;}
    if(dim>2) {if(rhs.z!=0) this->z /= rhs.z; else return *this;}
    return *this;
}

Point& Point::operator+=(const double d) {
    int dim = this->getDimension();
    if(dim>0) this->x += d;
    if(dim>1) this->y += d;
    if(dim>2) this->z += d;
    return *this;
}
Point& Point::operator-=(const double d) {
    int dim = this->getDimension();
    if(dim>0) this->x -= d;
    if(dim>1) this->y -= d;
    if(dim>2) this->z -= d;
    return *this;
}
Point& Point::operator*=(const double d) {
    int dim = this->getDimension();
    if(dim>0) this->x *= d;
    if(dim>1) this->y *= d;
    if(dim>2) this->z *= d;
    return *this;
}
Point& Point::operator/=(const double d) {
    int dim = this->getDimension();
    if(d==0) return *this;
    if(dim>0) this->x /= d;
    if(dim>1) this->y /= d;
    if(dim>2) this->z /= d;
    return *this;
}

 
Point operator+(Point lhs, const Point &rhs) { lhs += rhs; return lhs; } 
Point operator-(Point lhs, const Point &rhs) { lhs -= rhs; return lhs; } 
Point operator*(Point lhs, const Point &rhs) { lhs *= rhs; return lhs; } 
Point operator/(Point lhs, const Point &rhs) { lhs /= rhs; return lhs; } 

Point operator+(Point rhs, const double d) { rhs += d; return rhs; } 
Point operator-(Point rhs, const double d) { rhs -= d; return rhs; } 
Point operator*(Point rhs, const double d) { rhs *= d; return rhs; } 
Point operator/(Point rhs, const double d) { rhs /= d; return rhs; } 
 
std::ostream& operator<<(std::ostream& os,  Point const& point) {
    int roundDigits=3;

    double x = roundToPlace(point.get(_x_), roundDigits);
    double y = roundToPlace(point.get(_y_), roundDigits);
    double z = roundToPlace(point.get(_z_), roundDigits);

    if(point.is1D()) os << "(" << x << ")";
    if(point.is2D()) os << "(" << x << "," << y << ")";
    if(point.is3D()) os << "(" << x << "," << y << "," << z << ")";
    return os;
    
}

bool operator==(const Point &lhs, const Point &rhs) { 
    // First check if they're of the smae dimension
    int dim = lhs.getDimension();
    if(dim != rhs.getDimension()) return false;
    if(dim<=0) return false;

    // Now check if the values are the same 
    bool check = true;
    if(dim>0) check = check && lhs.get(_x_) == rhs.get(_x_); 
    if(dim>1) check = check && lhs.get(_y_) == rhs.get(_y_);
    if(dim>2) check = check && lhs.get(_z_) == rhs.get(_z_);

    return check;
}

bool operator!=(const Point &lhs, const Point &rhs) {return !operator==(lhs,rhs);}
