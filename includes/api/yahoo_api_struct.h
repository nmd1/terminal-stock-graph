#ifndef STOCK_STRUCT_H
#define STOCK_STRUCT_H

#include <iostream>
#include <string>

#include "json.hpp"

using json = nlohmann::json;

namespace stk {
	struct Stock {
		std::string language;								//	"en-US"
		std::string region;									//	"US"
		std::string quoteType;								//	"EQUITY"
		std::string quoteSourceName;							//	"Delayed Quote"
		std::string currency;								//	"USD"
		long sharesOutstanding;							//	4745399808
		long double bookValue;							//	22.534
		long double fiftyDayAverage;					//	173.84088
		long double fiftyDayAverageChange;				//	-17.610886
		long double fiftyDayAverageChangePercent;		//	-0.10130463
		long double fiftyTwoWeekLowChangePercent;		//	0.06576165
		std::string fiftyTwoWeekRange;						//	"146.59 - 233.47"
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
		std::string exchangeTimezoneName;					//	"America/New_York"
		std::string exchangeTimezoneShortName;				//	"EST"
		long int gmtOffSetMilliseconds;					//	-18000000
		bool esgPopulated;								//	false
		bool tradeable;									//	true
		long double postMarketChangePercent;			//	0.09601815
		tm * postMarketTime;							//	1546045182
		double postMarketPrice;							//	156.38
		long double postMarketChange;					//	0.15000916
		long double regularMarketChangePercent;			//	0.051233962
		std::string regularMarketDayRange;					//	"154.55 - 158.51"
		double regularMarketPreviousClose;				//	156.15
		double bid;										//	156.32
		double ask;										//	156.39
		int bidSize;									//	9
		int askSize;									//	9
		std::string messageBoardId;							//	"finmb_24937"
		std::string fullExchangeName;						//	"NasdaqGS"
		std::string longName;								//	"Apple Inc."
		std::string financialCurrency;						//	"USD"
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
		std::string marketState;								//	"CLOSED"
		std::string shortName;								//	"Apple Inc."
		std::string exchange;								//	"NMS"
		std::string market;									//	"us_market"
		double epsTrailingTwelveMonths;					//	11.91
		double epsForward;								//	14.64
		std::string symbol;									//	"AAPL"
	};

	struct Stock2 {
		std::string language;								//	"en-US"
		std::string region;									//	"US"
		std::string quoteType;								//	"EQUITY"
		std::string quoteSourceName;							//	"Delayed Quote"
		std::string currency;								//	"USD"
		int sharesOutstanding;							//	4745399808
		double bookValue;							//	22.534
		double fiftyDayAverage;					//	173.84088
		double fiftyDayAverageChange;				//	-17.610886
		double fiftyDayAverageChangePercent;		//	-0.10130463
		double fiftyTwoWeekLowChangePercent;		//	0.06576165
		std::string fiftyTwoWeekRange;						//	"146.59 - 233.47"
		double fiftyTwoWeekHighChange;				//	-77.240005
		double fiftyTwoWeekHighChangePercent;		//	-0.3308348
		double fiftyTwoWeekLow;					//	146.59
		double fiftyTwoWeekHigh;					//	233.47
		std::string dividendDate;								//	1542240000
		int earningsTimestamp;							//	1541102400
		int earningsTimestampStart;					//	1548882000
		int earningsTimestampEnd;						//	1549314000
		double trailingAnnualDividendRate;				//	2.72
		double trailingPE;							//	13.117548
		double trailingAnnualDividendYield;		//	0.017419148
		int priceHint;									//	2
		double twoHundredDayAverage;				//	199.86957
		double twoHundredDayAverageChange;			//	-43.639572
		double twoHundredDayAverageChangePercent;  //-0.21834025
		int marketCap;									//	741373771776
		double forwardPE;							//	10.671448
		double priceToBook;								//	6.933079
		int sourceInterval;								//	15
		std::string exchangeTimezoneName;					//	"America/New_York"
		std::string exchangeTimezoneShortName;				//	"EST"
		int gmtOffSetMilliseconds;					//	-18000000
		bool esgPopulated;								//	false
		bool tradeable;									//	true
		double postMarketChangePercent;			//	0.09601815
		int postMarketTime;							//	1546045182
		double postMarketPrice;							//	156.38
		double postMarketChange;					//	0.15000916
		double regularMarketChangePercent;			//	0.051233962
		std::string regularMarketDayRange;					//	"154.55 - 158.51"
		double regularMarketPreviousClose;				//	156.15
		double bid;										//	156.32
		double ask;										//	156.39
		int bidSize;									//	9
		int askSize;									//	9
		std::string messageBoardId;							//	"finmb_24937"
		std::string fullExchangeName;						//	"NasdaqGS"
		std::string longName;								//	"Apple Inc."
		std::string financialCurrency;						//	"USD"
		int averageDailyVolume3Month;				//	41502779
		int averageDailyVolume10Day;				//	57238028
		double fiftyTwoWeekLowChange;				//	9.639999
		int exchangeDataDelayedBy;					//	0
		double regularMarketPrice;						//	156.23
		int regularMarketTime;							//	1546030801
		double regularMarketChange;				//	0.08000183
		double regularMarketOpen;						//	157.5
		double regularMarketDayHigh;					//	158.51
		double regularMarketDayLow;						//	154.55
		int regularMarketVolume;					//	42291424
		std::string marketState;								//	"CLOSED"
		std::string shortName;								//	"Apple Inc."
		std::string exchange;								//	"NMS"
		std::string market;									//	"us_market"
		double epsTrailingTwelveMonths;					//	11.91
		double epsForward;								//	14.64
		std::string symbol;									//	"AAPL"
	};

	void to_json(json& j, const Stock& p);
	void from_json(const json& j, Stock& p);

}



#endif