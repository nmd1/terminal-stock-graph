#ifndef DEBUG_H
#define DEBUG_H

#include <fstream>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

#include "map/base.hpp"
#include "map/time.hpp"
#include "render/window.hpp"

extern std::ofstream debugf;
extern std::ofstream graphwin;

void graph_sin();


#endif