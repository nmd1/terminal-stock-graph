#ifndef STOCKDRAW_H
#define STOCKDRAW_H

#include <iostream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <tuple>
#include <ctime>

#include "debug.h"
#include "map/base.h"
#include "map/time.h"
#include "api/yahoo.h"
#include "render/window.h"
#include "signal_handler.h"
#include "map/point.h"
#include "render/color.h"

void stockDraw(std::string);
void stockDrawFull(std::string stock);
void stockDrawWithPast(std::string stock, time_t);
void coolGraphEffect(time_t, double, double, Map*);
std::tuple<yahoo::OHLC, yahoo::OHLC> getOHLCminmax(std::vector<yahoo::OHLC*>);

#endif