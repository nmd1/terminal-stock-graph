#include "yahoo_api.h"
/*
	<------------time----------->
	open					close
			  highs/lows
*/
std::vector<std::tuple<time_t, yahoo::OHLC*> > yahoo::getOHLC(std::string stock) {
	bool use_12_hour_time = true;
	bool is_morning = false;
	std::string api = "https://query1.finance.yahoo.com/v8/finance/chart/"+stock+"?interval=2m";
	json raw_data = web(api);	

    //std::cout << raw_data.dump(4) << std::endl;

    json error = raw_data["chart"]["error"];
    if(!error.empty()) {
    	std::string ecode = error["code"];
    	std::string edes = error["description"];
    	std::cout<<"API Error: "<<ecode<<std::endl<<"\t"<<edes<<std::endl;
    	//TODO: replace this with exception handling 
		std::vector<std::tuple<time_t, yahoo::OHLC*> > a;
	    return a; 
	}

    json data = raw_data["chart"]["result"][0];
    json meta_data = data["meta"];
   	std::vector<std::tuple<time_t, yahoo::OHLC*> > result;
    for (int i = 0; i < data["timestamp"].size(); i++) {

    	// This next part is just parsing time.
    	// It should honestly be in it's own function
    	time_t date = data["timestamp"][i];
    	tm *ltm = new tm();
    	ltm = localtime(&date);

		int year =  1900 + ltm->tm_year;
		int month =  1 + ltm->tm_mon;
		int day =  ltm->tm_mday;
		int hours = ltm->tm_hour;
		int minutes = 1 + ltm->tm_min;
		int seconds =  1 + ltm->tm_sec;
		std::string hour_indicator = "";
		if(use_12_hour_time) {
			if (!(hours > 24) && (hours > 12)) {
				is_morning=false;
				hours-=12;
			} else {
				is_morning=true;
				hour_indicator = "am";
			}
		}
		if(hours==12) is_morning=!is_morning;
		if(is_morning) {
			hour_indicator = "am";
		} else {
			hour_indicator = "pm";			
		}


		//if(i%10)  std::cout<<day<<" "<<hours<<":"<<minutes<<hour_indicator<<std::endl;
		//if(i==0) std::cout<<day<<" "<<hours<<":"<<minutes<<hour_indicator<<std::endl;
		//if(i==data["timestamp"].size()-1) 
		//	std::cout<<day<<" "<<hours<<":"<<minutes<<hour_indicator<<std::endl;
		yahoo::OHLC * ohlc = new yahoo::OHLC();
        json jquote = data["indicators"]["quote"][0];


        if(!jquote["volume"][i].empty())
		    ohlc->volume = jquote["volume"][i];
        if(!jquote["close"][i].empty())
		ohlc->open = jquote["close"][i];
        if(!jquote["open"][i].empty())
            ohlc->high = jquote["open"][i];
        if(!jquote["high"][i].empty())
    		ohlc->low = jquote["high"][i];
        if(!jquote["low"][i].empty())
	       ohlc->close = jquote["low"][i];
		else 

		// Sometimes the api returns 0 for a close value
		// In these situations, just don't add the data point.
		// In the future find a better way to handle this situation
			continue;
		//std::cout<<ltm<<std::endl;
		std::tuple<time_t, yahoo::OHLC*> organized_data(date, ohlc);
		result.push_back(organized_data);

		//std::cout<<dt<<std::endl;

    }
    //std::cout<<result.size()<<std::endl;
    return result;

}

/*
    Source: https://gist.github.com/connormanning/41efa6075515019e499c
*/
json yahoo::web(const std::string url, const int timeout) {
    CURL* curl = curl_easy_init();

    // Set remote URL.
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    // Don't bother trying IPv6, which would increase DNS resolution time.
    curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);

    // Don't wait forever, timeout after some time (default, 10 seconds)
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout);

    // Follow HTTP redirects if necessary.
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    // Response information.
    int httpCode = 0;

    // Hook up data handling function.
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);

    // Hook up data container (will be passed as the last parameter to the
    // callback handling function).  Can be any pointer type, since it will
    // internally be passed as a void pointer.
    std::string * raw_json = new std::string();
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, raw_json);

    // Run our HTTP GET command, capture the HTTP response code, and clean up.
    curl_easy_perform(curl);
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
    curl_easy_cleanup(curl);

    // My modifications
    switch (httpCode) {
    	case (200): {
    		std::cout<<"Got a successful response from " << url << std::endl;
    		//std::cout<<*raw_json<<endl;
    		break;
    	}
    	case 404: {
    		std::cout<<"Error "<<httpCode<<": " << url << " not found" << std::endl;
    		std::cout<<"Check your stock symbol?"<< std::endl;
    		break;
    	}
    	default: {
    		std::cout<<"Something went wrong :("<<std::endl;
    		std::cout<<"Got error "<<httpCode<<" when querying " << url << std::endl;
    		break;
    	}
    }

    json raw_response_json = json::parse(*raw_json);
    delete raw_json;
    return raw_response_json;
    
    // nope
    json error = raw_response_json["quoteResponse"]["error"];
    // "code": "Not Found",
	// "description": "No data found, symbol may be delisted"

    json data = raw_response_json["quoteResponse"]["result"][0];
    return data;
}