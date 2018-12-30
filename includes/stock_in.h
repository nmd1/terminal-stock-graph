#ifndef STOCK_IN_H
#define STOCK_IN_H

#include <iostream>
#include <string>
#include <ctime>
#include <curl/curl.h>
#include <cstdint>
#include <memory>

#include "nlohmann/json.hpp"
#include "stock_struct.h"

using namespace std;
using json = nlohmann::json;

struct max_min {
	double max;
	double min;
};


class Stock_track {
	public:
		Stock_track(string);
		Stock_track(string, string);
		stk::Stock stock;
		json web();
		void update();		
	protected:
		string api;
		string name;
		tm * convertRawTime();
};


#endif