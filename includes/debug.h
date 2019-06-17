#ifndef DEBUG_H
#define DEBUG_H

#include <fstream>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

#include "map/base.h"
#include "map/time.h"
#include "render/window.h"

extern std::ofstream debugf;
extern std::ofstream graphwin;

void graph_sin();


#endif