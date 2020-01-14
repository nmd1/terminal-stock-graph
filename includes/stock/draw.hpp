#ifndef STOCKDRAW_H
#define STOCKDRAW_H

#include <iostream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <tuple>
#include <ctime>

#include "debug.hpp"
#include "map/base.hpp"
#include "map/time.hpp"
#include "api/yahoo.hpp"
#include "render/window.hpp"
#include "signal_handler.hpp"
#include "map/point.hpp"
#include "render/color.hpp"

void stockDraw(std::string);
void stockDrawFull(std::string stock);
void stockDrawWithPast(std::string stock, time_t);
void coolGraphEffect(time_t, double, double, Map*);
std::tuple<yahoo::OHLC, yahoo::OHLC> getOHLCminmax(std::vector<yahoo::OHLC*>);

#endif