#include "api/yahoo.hpp"
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
	json data;
	if(globaloptions.loadStockJSON.empty()) {

		// Download JSON from web
		data = downloadStockJSON(stock);

		// Save JSON to disk
		if(globaloptions.saveStockJSONs)
			std::string name = saveJSON(data);
	} else {
		data = loadJSON(globaloptions.loadStockJSON);
	}

	return getOHLCFromJSON(data);
}

/*
    Source: https://gist.github.com/connormanning/41efa6075515019e499c
*/
json yahoo::web(const std::string url, const int timeout) {
	std::stringstream errmsg;
    CURL* curl = curl_easy_init();

	if(!curl) {
		throw std::runtime_error("Could not generate curl object");
	}
	LOG_FILE(logfile, l_TRACE) << "Curl Object Created";
    // Set remote URL.
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    // Don't bother trying IPv6, which would increase DNS resolution time.
    curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);

    // Don't wait forever, timeout after some time (default, 10 seconds)
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout);

    // Follow HTTP redirects if necessary.
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    // Hook up data handling function.
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, cb::callback);

    // Response information.
    int httpCode = 0;

    // Hook up data container (will be passed as the last parameter to the
    // callback handling function).  Can be any pointer type, since it will
    // internally be passed as a void pointer.
    std::string * raw_json_str = new std::string();
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, raw_json_str);

	// Setup error handling
	std::string serror = "";
	curl_easy_setopt(curl,CURLOPT_ERRORBUFFER, serror);

    // Run our HTTP GET command, capture the HTTP response code, and clean up.
    auto ecode = curl_easy_perform(curl);
	LOG_FILE(logfile, l_DEBUG) << "Curl request made";

	if(ecode) {
		errmsg<<"Curl Error "<<ecode<<": "<<serror<<std::endl;
		throw std::runtime_error(errmsg.str());
	}

    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
    curl_easy_cleanup(curl); // leaking memory????????

    // My modifications
    switch (httpCode) {
    	case (200): {
			LOG_BOTH(logfile, l_INFO) << "Got a successful response from " << url;
    		//debugf<<*raw_json_str<<endl;
    		break;
    	}
    	case 404: {
    		errmsg<<"Error "<<httpCode<<": " << url << " not found" << std::endl;
    		errmsg<<"Check your stock symbol?"<< std::endl;
			throw std::runtime_error(errmsg.str());
    		break;
    	}
    	default: {
    		errmsg<<"Something went wrong :("<<std::endl;
    		errmsg<<"Got error "<<httpCode<<" when querying " << url << std::endl;
			throw std::runtime_error(errmsg.str());
			break;
    	}
    }

    json raw_response_json = json::parse(*raw_json_str);
    delete raw_json_str;
	// delete curl;
	//json error = raw_response_json["quoteResponse"]["error"];


    return raw_response_json;
    
    // nope
    // "code": "Not Found",
	// "description": "No data found, symbol may be delisted"

    //json data = raw_response_json["quoteResponse"]["result"][0];
}

json yahoo::downloadStockJSON(std::string stock) {
	std::stringstream errmsg;
	std::string time = "?interval=2m";
	time = "";
	std::string api = "https://query1.finance.yahoo.com/v8/finance/chart/"+stock+time;

	json raw_data = web(api);

	if(raw_data.empty()) {
		throw std::runtime_error("Yahoo Finance data returned empty");
	}
    //debugf << raw_data.dump(4) << std::endl;

    json error = raw_data["chart"]["error"];
    if(!error.empty()) {
    	std::string ecode = error["code"];
    	std::string edes = error["description"];
    	errmsg<<"Yahoo API Error: "<<ecode<<std::endl<<"\t"<<edes<<std::endl;
		throw std::runtime_error(errmsg.str());
	}

    json data = raw_data["chart"]["result"][0];
	if(data.empty()) {
		throw std::runtime_error("Yahoo Finance JSON has no chart data");
	}
	return data;
}
std::vector<yahoo::OHLC*> yahoo::getOHLCFromJSON(json data) {
	bool use_12_hour_time = true;
	bool is_morning = false;
	json meta_data = data["meta"];
	json jquote = data["indicators"]["quote"][0];

	if (meta_data.empty()) {
		throw std::runtime_error("Yahoo Finance JSON has no Metadata");
	}

	if (jquote.empty()) {
		throw std::runtime_error("Yahoo Finance JSON has no data for this quote");
	}

	std::vector<yahoo::OHLC*> result;
	unsigned size = data["timestamp"].size();
    for (unsigned i = 0; i < size; i++) {

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
		


		// This is more common than I thought
		bool all_are_missing =  jquote["volume"][i].empty() &&
								jquote["close"][i].empty()  &&
								jquote["open"][i].empty()   && 
								jquote["high"][i].empty()   &&
								jquote["low"][i].empty()	;

		if(all_are_missing) {
			LOG_BOTH(logfile, l_DEBUG) << "All OHLC values are missing ("<<i<<"/"<<size-1<<") ";
			continue;
		}

		yahoo::OHLC * ohlc = new yahoo::OHLC();
		LOG_BOTH(logfile, l_TRACE) << "New heap OHLC object: OHLC ["<<i<<"]";

		if(date) ohlc->time = date;
		else LOG_BOTH(logfile, l_DEBUG) << "OHLC Date missing ("<<i<<"/"<<size-1<<") ";


        if(!jquote["volume"][i].empty())
		    ohlc->volume = jquote["volume"][i];
		else LOG_BOTH(logfile, l_DEBUG) << "OHLC volume missing ("<<i<<"/"<<size-1<<") ";

        if(!jquote["close"][i].empty())
			ohlc->open = jquote["close"][i];
		else LOG_BOTH(logfile, l_DEBUG) << "OHLC close missing ("<<i<<"/"<<size-1<<") ";

        if(!jquote["open"][i].empty())
            ohlc->high = jquote["open"][i];
		else LOG_BOTH(logfile, l_DEBUG) << "OHLC open missing ("<<i<<"/"<<size-1<<") ";

        if(!jquote["high"][i].empty())
    		ohlc->low = jquote["high"][i];
		else LOG_BOTH(logfile, l_DEBUG) << "OHLC high missing ("<<i<<"/"<<size-1<<") ";

        if(!jquote["low"][i].empty())
	       ohlc->close = jquote["low"][i];
		else LOG_BOTH(logfile, l_DEBUG) << "OHLC low missing ("<<i<<"/"<<size-1<<") ";
		//debugf<<ltm<<std::endl;

		result.push_back(ohlc);
		//debugf<<dt<<std::endl;
    }
    if (result.size() == 0) {
		throw std::runtime_error("OHLC array is empty");
	}
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
	LOG_BOTH(logfile, l_INFO) << "saved JSON "<<filename;
	// Save JSON
	outputfile << data.dump();

	outputfile.close();
	return filename;
}
json yahoo::loadJSON(std::string filename) {
	std::ifstream infile(filename);
	json data = json::parse(infile);
	infile.close();
	LOG_BOTH(logfile, l_INFO) << "loaded JSON " << filename;
	return data;
}

void yahoo::removeOHLC(std::vector<yahoo::OHLC*>* data) {
	unsigned i = 0;
	for (auto ohlcptr : *data) {	
		delete ohlcptr;

		
		LOG_BOTH(logfile, l_TRACE) << "Heap OHLC object destroyed ["<<i<<"]";
		++i;
	}
}