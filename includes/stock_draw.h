#ifndef STOCKDRAW_H
#define STOCKDRAW_H

#include <iostream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <tuple>
#include <ctime>

#include "debug.h"
#include "base_map.h"
#include "time_graph.h"
#include "yahoo_api.h"
#include "window.h"
#include "signal_handler.h"

void stockDraw(std::string);
void stockDrawFull(std::string stock);
void stockDrawWithPast(std::string stock, time_t);
void coolGraphEffect(time_t, double, double, Map*);
std::tuple<yahoo::OHLC, yahoo::OHLC> getOHLCminmax(std::vector<yahoo::OHLC*>);

#endif