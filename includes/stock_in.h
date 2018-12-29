#ifndef STOCK_IN_H
#define STOCK_IN_H

#include <iostream>
#include <string>
#include <ctime>
#include <curl/curl.h>
#include <cstdint>
#include <memory>

#include "nlohmann/json.hpp"


using namespace std;
using json = nlohmann::json;

struct Stock {
	string language;								//	"en-US"
	string region;									//	"US"
	string quoteType;								//	"EQUITY"
	string quoteSourceName;							//	"Delayed Quote"
	string currency;								//	"USD"
	long sharesOutstanding;							//	4745399808
	long double bookValue;							//	22.534
	long double fiftyDayAverage;					//	173.84088
	long double fiftyDayAverageChange;				//	-17.610886
	long double fiftyDayAverageChangePercent;		//	-0.10130463
	long double fiftyTwoWeekLowChangePercent;		//	0.06576165
	string fiftyTwoWeekRange;						//	"146.59 - 233.47"
	long double fiftyTwoWeekHighChange;				//	-77.240005
	long double fiftyTwoWeekHighChangePercent;		//	-0.3308348
	long double fiftyTwoWeekLow;					//	146.59
	long double fiftyTwoWeekHigh;					//	233.47
	tm * dividendDate;								//	1542240000
	tm * earningsTimestamp;							//	1541102400
	tm * earningsTimestampStart;					//	1548882000
	tm * earningsTimestampEnd;						//	1549314000
	double trailingAnnualDividendRate;				//	2.72
	long double trailingPE;							//	13.117548
	long double trailingAnnualDividendYield;		//	0.017419148
	int priceHint;									//	2
	long double twoHundredDayAverage;				//	199.86957
	long double twoHundredDayAverageChange;			//	-43.639572
	long double twoHundredDayAverageChangePercent;  //-0.21834025
	long marketCap;									//	741373771776
	long double forwardPE;							//	10.671448
	double priceToBook;								//	6.933079
	int sourceInterval;								//	15
	string exchangeTimezoneName;					//	"America/New_York"
	string exchangeTimezoneShortName;				//	"EST"
	long int gmtOffSetMilliseconds;					//	-18000000
	bool esgPopulated;								//	false
	bool tradeable;									//	true
	long double postMarketChangePercent;			//	0.09601815
	tm * postMarketTime;							//	1546045182
	double postMarketPrice;							//	156.38
	long double postMarketChange;					//	0.15000916
	long double regularMarketChangePercent;			//	0.051233962
	string regularMarketDayRange;					//	"154.55 - 158.51"
	double regularMarketPreviousClose;				//	156.15
	double bid;										//	156.32
	double ask;										//	156.39
	int bidSize;									//	9
	int askSize;									//	9
	string messageBoardId;							//	"finmb_24937"
	string fullExchangeName;						//	"NasdaqGS"
	string longName;								//	"Apple Inc."
	string financialCurrency;						//	"USD"
	long int averageDailyVolume3Month;				//	41502779
	long int averageDailyVolume10Day;				//	57238028
	long double fiftyTwoWeekLowChange;				//	9.639999
	double exchangeDataDelayedBy;					//	0
	double regularMarketPrice;						//	156.23
	tm * regularMarketTime;							//	1546030801
	long double regularMarketChange;				//	0.08000183
	double regularMarketOpen;						//	157.5
	double regularMarketDayHigh;					//	158.51
	double regularMarketDayLow;						//	154.55
	long int regularMarketVolume;					//	42291424
	string marketState;								//	"CLOSED"
	string shortName;								//	"Apple Inc."
	string exchange;								//	"NMS"
	string market;									//	"us_market"
	double epsTrailingTwelveMonths;					//	11.91
	double epsForward;								//	14.64
	string symbol;									//	"AAPL"
};

struct max_min {
	double max;
	double min;
};

namespace
{
    std::size_t callback(
            const char* in,
            std::size_t size,
            std::size_t num,
            std::string* out)
    {
        const std::size_t totalBytes(size * num);
        out->append(in, totalBytes);
        return totalBytes;
    }
}

class Stock_track {
	public:
		Stock_track(string);
		Stock_track(string, string);
		Stock stock;
		void web();
		void update();		
	protected:
		string api;
		string name;
		tm * convertRawTime();
};


#endif