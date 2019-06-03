#ifndef EXTRA_FUNCTIONS_H
#define EXTRA_FUNCTIONS_H

#include <sstream>
#include <iomanip>
#include <cmath>

double roundToPlace(const double&, const int&);
double roundToDPlace(const double&, const double&);
bool areSame(double, double, double=__DBL_EPSILON__);
std::string makeTime(time_t);


#endif