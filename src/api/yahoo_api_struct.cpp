#include "api/yahoo_api_struct.hpp"

/*
void stk::to_json(json& j, const Stock& p) {
    j = json 
    {
    {"language", p.language}, 
    {"region", p.region}, 
    {"quoteType", p.quoteType},
	{"quoteSourceName", p.quoteSourceName},							
	{"currency", p.currency},								
	{"sharesOutstanding", p.sharesOutstanding},						
	{"bookValue", p.bookValue},							
	{"fiftyDayAverage", p.fiftyDayAverage},					
	{"fiftyDayAverageChange", p.fiftyDayAverageChange},				
	{"fiftyDayAverageChangePercent", p.fiftyDayAverageChangePercent},		
	{"fiftyTwoWeekLowChangePercent", p.fiftyTwoWeekLowChangePercent},		
	{"fiftyTwoWeekRange", p.fiftyTwoWeekRange},						
	{"fiftyTwoWeekHighChange", p.fiftyTwoWeekHighChange},				
	{"fiftyTwoWeekHighChangePercent", p.fiftyTwoWeekHighChangePercent},		
	{"fiftyTwoWeekLow", p.fiftyTwoWeekLow},					
	{"fiftyTwoWeekHigh", p.fiftyTwoWeekHigh},					
	{"dividendDate", p.dividendDate},								
	{"earningsTimestamp", p.earningsTimestamp},							
	{"earningsTimestampStart", p.earningsTimestampStart},					
	{"earningsTimestampEnd", p.earningsTimestampEnd},						
	{"trailingAnnualDividendRate", p.trailingAnnualDividendRate},				
	{"trailingPE", p.trailingPE},							
	{"trailingAnnualDividendYield", p.trailingAnnualDividendYield},		
	{"priceHint", p.priceHint},									
	{"twoHundredDayAverage", p.twoHundredDayAverage},
	{"twoHundredDayAverageChange", p.twoHundredDayAverageChange},		
	{"twoHundredDayAverageChangePercent", p.twoHundredDayAverageChangePercent}, 
    {"marketCap", p.marketCap},	
	{"forwardPE", p.forwardPE},							
	{"priceToBook", p.priceToBook},	
	{"sourceInterval", p.sourceInterval},							
	{"exchangeTimezoneName", p.exchangeTimezoneName},
	{"exchangeTimezoneShortName", p.exchangeTimezoneShortName},				
	{"gmtOffSetMilliseconds", p.gmtOffSetMilliseconds},				
	{"esgPopulated", p.esgPopulated},
	{"tradeable", p.tradeable},	
	{"postMarketChangePercent", p.postMarketChangePercent},	
	{"postMarketTime", p.postMarketTime},		
	{"postMarketPrice", p.postMarketPrice},		
	{"postMarketChange", p.postMarketChange},	
	{"regularMarketChangePercent", p.regularMarketChangePercent},
	{"regularMarketDayRange", p.regularMarketDayRange},	
	{"regularMarketPreviousClose", p.regularMarketPreviousClose},
	{"bid", p.bid},		
	{"ask", p.ask},		
	{"bidSize", p.bidSize},	
	{"askSize", p.askSize},		
	{"messageBoardId", p.messageBoardId},		
	{"fullExchangeName", p.fullExchangeName},				
	{"longName", p.longName},		
	{"financialCurrency", p.financialCurrency},	
	{"averageDailyVolume3Month", p.averageDailyVolume3Month},		
	{"averageDailyVolume10Day", p.averageDailyVolume10Day},			
	{"fiftyTwoWeekLowChange", p.fiftyTwoWeekLowChange},	
	{"exchangeDataDelayedBy", p.exchangeDataDelayedBy},			
	{"regularMarketPrice", p.regularMarketPrice},	
	{"regularMarketTime", p.regularMarketTime},			
	{"regularMarketChange", p.regularMarketChange},			
	{"regularMarketOpen", p.regularMarketOpen},				
	{"regularMarketDayHigh", p.regularMarketDayHigh},	
	{"regularMarketDayLow", p.regularMarketDayLow},						
	{"regularMarketVolume", p.regularMarketVolume},				
	{"marketState", p.marketState},
	{"shortName", p.shortName},		
	{"exchange", p.exchange},						
	{"market", p.market},									
	{"epsTrailingTwelveMonths", p.epsTrailingTwelveMonths},	
	{"epsForward", p.epsForward},		
	{"symbol", p.symbol}				
	};
}

void stk::from_json(const json& j, Stock& p) {
    j.at("language").get_to(p.language);
    j.at("region").get_to(p.region);
    j.at("quoteType").get_to(p.quoteType);
    j.at("quoteSourceName").get_to(p.quoteSourceName);							
	j.at("currency").get_to(p.currency);								
	j.at("sharesOutstanding").get_to(p.sharesOutstanding);						
	j.at("bookValue").get_to(p.bookValue);							
	j.at("fiftyDayAverage").get_to(p.fiftyDayAverage);					
	j.at("fiftyDayAverageChange").get_to(p.fiftyDayAverageChange);				
	j.at("fiftyDayAverageChangePercent").get_to(p.fiftyDayAverageChangePercent);		
	j.at("fiftyTwoWeekLowChangePercent").get_to(p.fiftyTwoWeekLowChangePercent);		
	j.at("fiftyTwoWeekRange").get_to(p.fiftyTwoWeekRange);						
	j.at("fiftyTwoWeekHighChange").get_to(p.fiftyTwoWeekHighChange);				
	j.at("fiftyTwoWeekHighChangePercent").get_to(p.fiftyTwoWeekHighChangePercent);		
	j.at("fiftyTwoWeekLow").get_to(p.fiftyTwoWeekLow);					
	j.at("fiftyTwoWeekHigh").get_to(p.fiftyTwoWeekHigh);					
	j.at("dividendDate").get_to(p.dividendDate);								
	j.at("earningsTimestamp").get_to(p.earningsTimestamp);							
	j.at("earningsTimestampStart").get_to(p.earningsTimestampStart);					
	j.at("earningsTimestampEnd").get_to(p.earningsTimestampEnd);						
	j.at("trailingAnnualDividendRate").get_to(p.trailingAnnualDividendRate);				
	j.at("trailingPE").get_to(p.trailingPE);							
	j.at("trailingAnnualDividendYield").get_to(p.trailingAnnualDividendYield);		
	j.at("priceHint").get_to(p.priceHint);									
	j.at("twoHundredDayAverage").get_to(p.twoHundredDayAverage);
	j.at("twoHundredDayAverageChange").get_to(p.twoHundredDayAverageChange);		
	j.at("twoHundredDayAverageChangePercent").get_to(p.twoHundredDayAverageChangePercent);
    j.at("marketCap").get_to(p.marketCap);	
	j.at("forwardPE").get_to(p.forwardPE);							
	j.at("priceToBook").get_to(p.priceToBook);	
	j.at("sourceInterval").get_to(p.sourceInterval);							
	j.at("exchangeTimezoneName").get_to(p.exchangeTimezoneName);
	j.at("exchangeTimezoneShortName").get_to(p.exchangeTimezoneShortName);				
	j.at("gmtOffSetMilliseconds").get_to(p.gmtOffSetMilliseconds);				
	j.at("esgPopulated").get_to(p.esgPopulated);
	j.at("tradeable").get_to(p.tradeable);	
	j.at("postMarketChangePercent").get_to(p.postMarketChangePercent);	
	j.at("postMarketTime").get_to(p.postMarketTime);		
	j.at("postMarketPrice").get_to(p.postMarketPrice);		
	j.at("postMarketChange").get_to(p.postMarketChange);	
	j.at("regularMarketChangePercent").get_to(p.regularMarketChangePercent);
	j.at("regularMarketDayRange").get_to(p.regularMarketDayRange);	
	j.at("regularMarketPreviousClose").get_to(p.regularMarketPreviousClose);
	j.at("bid").get_to(p.bid);		
	j.at("ask").get_to(p.ask);		
	j.at("bidSize").get_to(p.bidSize);	
	j.at("askSize").get_to(p.askSize);		
	j.at("messageBoardId").get_to(p.messageBoardId);		
	j.at("fullExchangeName").get_to(p.fullExchangeName);				
	j.at("longName").get_to(p.longName);		
	j.at("financialCurrency").get_to(p.financialCurrency);	
	j.at("averageDailyVolume3Month").get_to(p.averageDailyVolume3Month);		
	j.at("averageDailyVolume10Day").get_to(p.averageDailyVolume10Day);			
	j.at("fiftyTwoWeekLowChange").get_to(p.fiftyTwoWeekLowChange);	
	j.at("exchangeDataDelayedBy").get_to(p.exchangeDataDelayedBy);			
	j.at("regularMarketPrice").get_to(p.regularMarketPrice);	
	j.at("regularMarketTime").get_to(p.regularMarketTime);			
	j.at("regularMarketChange").get_to(p.regularMarketChange);			
	j.at("regularMarketOpen").get_to(p.regularMarketOpen);				
	j.at("regularMarketDayHigh").get_to(p.regularMarketDayHigh);	
	j.at("regularMarketDayLow").get_to(p.regularMarketDayLow);						
	j.at("regularMarketVolume").get_to(p.regularMarketVolume);				
	j.at("marketState").get_to(p.marketState);
	j.at("shortName").get_to(p.shortName);		
	j.at("exchange").get_to(p.exchange);						
	j.at("market").get_to(p.market);									
	j.at("epsTrailingTwelveMonths").get_to(p.epsTrailingTwelveMonths);	
	j.at("epsForward").get_to(p.epsForward);		
	j.at("symbol").get_to(p.symbol);			
}
*/