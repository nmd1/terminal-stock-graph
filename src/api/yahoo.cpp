#include "api/yahoo.h"
/*
	<------------time----------->
	open					close
			  highs/lows
*/

namespace cb
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



std::vector<yahoo::OHLC*> yahoo::getOHLC(std::string stock) {
	json data = downloadStockJSON(stock);
	// Uncomment to save/load to/from disk
	//std::string name = saveJSON(data);
	//data = loadJSON(name);
	return getOHLCFromJSON(data);
}

/*
    Source: https://gist.github.com/connormanning/41efa6075515019e499c
*/
json yahoo::web(const std::string url, const int timeout) {
	json failed;
    CURL* curl = curl_easy_init();
	if(!curl) {
		std::cout<<"Looks like we found the problem"<<std::endl;
		return failed;
	}
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
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, cb::callback);

    // Hook up data container (will be passed as the last parameter to the
    // callback handling function).  Can be any pointer type, since it will
    // internally be passed as a void pointer.
    std::string * raw_json = new std::string();
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, raw_json);

	// Setup error handling
	std::string serror = "";
	curl_easy_setopt(curl,CURLOPT_ERRORBUFFER, serror);

    // Run our HTTP GET command, capture the HTTP response code, and clean up.
    auto ecode = curl_easy_perform(curl);
	debugf<<"Curl Handle: "<<curl<<std::endl;
	if(ecode){
		debugf<<"Error "<<ecode<<": "<<serror<<std::endl;
		return failed;
	}

    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
	debugf<<"Before the cleanup "<<curl<<std::endl;
    curl_easy_cleanup(curl); // leaking memory????????

    // My modifications
    switch (httpCode) {
    	case (200): {
    		debugf<<"Got a successful response from " << url << std::endl;
    		//debugf<<*raw_json<<endl;
    		break;
    	}
    	case 404: {
    		debugf<<"Error "<<httpCode<<": " << url << " not found" << std::endl;
    		debugf<<"Check your stock symbol?"<< std::endl;
    		break;
    	}
    	default: {
    		debugf<<"Something went wrong :("<<std::endl;
    		debugf<<"Got error "<<httpCode<<" when querying " << url << std::endl;
    		break;
    	}
    }

    json raw_response_json = json::parse(*raw_json);
    delete raw_json;
	// delete curl;
	debugf<<"Are we stil going wtf???"<<std::endl;
    return raw_response_json;
    
    // nope
    json error = raw_response_json["quoteResponse"]["error"];
    // "code": "Not Found",
	// "description": "No data found, symbol may be delisted"

    json data = raw_response_json["quoteResponse"]["result"][0];
    return data;
}


json yahoo::downloadStockJSON(std::string stock) {
	json empty;
	std::string time = "?interval=2m";
	time = "";
	std::string api = "https://query1.finance.yahoo.com/v8/finance/chart/"+stock+time;

	debugf<<"Opening new connection"<<std::endl;
	json raw_data = web(api);
	if(raw_data.empty()) return empty;	
	debugf<<"Closing our new connection"<<std::endl;

    //debugf << raw_data.dump(4) << std::endl;

    json error = raw_data["chart"]["error"];
    if(!error.empty()) {
    	std::string ecode = error["code"];
    	std::string edes = error["description"];
    	debugf<<"API Error: "<<ecode<<std::endl<<"\t"<<edes<<std::endl;
    	//TODO: replace this with exception handling 
	    return empty; 
	}

    json data = raw_data["chart"]["result"][0];
	return data;
}
std::vector<yahoo::OHLC*> yahoo::getOHLCFromJSON(json data) {
	bool use_12_hour_time = true;
	bool is_morning = false;
	json meta_data = data["meta"];

	std::vector<yahoo::OHLC*> result;
    for (unsigned i = 0; i < data["timestamp"].size(); i++) {

    	// This next part is just parsing time.
    	// It should honestly be in it's own function
    	time_t date = data["timestamp"][i];
    	tm *ltm = localtime(&date);

		//int year =  1900 + ltm->tm_year;
		//int month =  1 + ltm->tm_mon;
		//int day =  ltm->tm_mday;
		//
		//int minutes = 1 + ltm->tm_min;
		//int seconds =  1 + ltm->tm_sec;

		int hours = ltm->tm_hour;

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


		//if(i%10)  debugf<<day<<" "<<hours<<":"<<minutes<<hour_indicator<<std::endl;
		//if(i==0) debugf<<day<<" "<<hours<<":"<<minutes<<hour_indicator<<std::endl;
		//if(i==data["timestamp"].size()-1) 
		//	debugf<<day<<" "<<hours<<":"<<minutes<<hour_indicator<<std::endl;
		yahoo::OHLC * ohlc = new yahoo::OHLC();
        json jquote = data["indicators"]["quote"][0];

		if(date) ohlc->time = date;
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
		//debugf<<ltm<<std::endl;

		result.push_back(ohlc);
		//debugf<<dt<<std::endl;
    }
    //debugf<<result.size()<<std::endl;
    return result;

}

std::string yahoo::saveJSON(json data) {
	// Use current time as file name 
	auto t = std::time(NULL);
    auto tm = *std::localtime(&t);

	// Get name of stock
	std::string name = data["meta"]["symbol"];

	// decide name of directory
	std::string dirname = "stocksnapshots/";
	std::stringstream fnbuild;
	fnbuild << dirname << std::put_time(&tm, "%d-%m-%Y_%H-%M-%S")
		<< "." << name << ".stock";
	std::string filename = fnbuild.str();

    std::ofstream outputfile(filename);

	// Save JSON
	outputfile << data.dump();

	outputfile.close();
	return filename;
}
json yahoo::loadJSON(std::string filename) {
	std::ifstream infile(filename);
	json data = json::parse(infile);
	infile.close();
	return data;
}

void yahoo::removeOHLC(std::vector<yahoo::OHLC*>* data) {
	for (auto ohlcptr : *data) {
		delete ohlcptr;
	}
}