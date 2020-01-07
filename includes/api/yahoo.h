#ifndef YAHOO_API_H
#define YAHOO_API_H

#include <string>
#include <tuple>
#include <ctime>
#include <iostream>
#include <curl/curl.h>
#include "debug.h"

#include "json.hpp"
using json = nlohmann::json;

namespace yahoo {
	struct OHLC {
		//std::string time; // Add this 
		time_t time;
		double open;
		double high;
		double low;
		double close;
		int volume;
	};
	void getSnapshot(json& data);
	void getSnapshot(json& data, std::string attribute);
	void getSnapshot(json& data, std::vector<std::string> attributes);
	json web(const std::string, const int = 10);
	std::vector<yahoo::OHLC*> getOHLC(const std::string stock);
	json downloadStockJSON(const std::string stock);
	std::vector<yahoo::OHLC*> getOHLCFromJSON(const json);

	void removeOHLC(std::vector<yahoo::OHLC*>*);

	std::string saveJSON(json);
	json loadJSON(std::string);
}

namespace cb
{
    extern std::size_t callback(const char*, std::size_t, std::size_t, std::string*);
}

#endif