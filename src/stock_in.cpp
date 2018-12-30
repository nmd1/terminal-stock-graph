#include "stock_in.h"

Stock_track::Stock_track(string stock_name) {
	name = stock_name;
	api = "https://query1.finance.yahoo.com/v7/finance/quote?lang=en-US&region=US&corsDomain=finance.yahoo.com";
}

/*
	Source: https://gist.github.com/connormanning/41efa6075515019e499c
*/
json Stock_track::web() {

	string urlbuilder = api+"&symbols="+name;

	const std::string url(urlbuilder);

    CURL* curl = curl_easy_init();

    // Set remote URL.
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    // Don't bother trying IPv6, which would increase DNS resolution time.
    curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);

    // Don't wait forever, time out after 10 seconds.
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);

    // Follow HTTP redirects if necessary.
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    // Response information.
    int httpCode = 0;
    std::unique_ptr<std::string> httpData(new std::string());

    // Hook up data handling function.
    //scurl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);

    // Hook up data container (will be passed as the last parameter to the
    // callback handling function).  Can be any pointer type, since it will
    // internally be passed as a void pointer.
    string * raw_json = new string();
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
    		cout<<"Check your stock symbol?"<<endl;
    		break;
    	}
    	default: {
    		cout<<"Something went wrong :("<<endl;
    		std::cout<<"Got error "<<httpCode<<" when querying " << url << std::endl;
    		break;
    	}
    }

    json raw_response_json = json::parse(*raw_json);
    delete raw_json;
    json error = raw_response_json["quoteResponse"]["error"];

    json data = raw_response_json["quoteResponse"]["result"][0];
    return data;

    //std::cout << data.dump(4) << std::endl;
   	
   	//stk::Stock p2 = data.get<stk::Stock>();
   	//cout<<p2.region<<endl;
   	//return;

	//for (json::iterator it = data.begin(); it != data.end(); ++it) {
	//	std::cout << it.key() << " : " << it.value() << endl;
	//}

    //std::cout << j.dump(4) << std::endl;
    /*
    if (httpCode == 200)
    {
        std::cout << "\nGot successful response from " << url << std::endl;

        // Response looks good - done using Curl now.  Try to parse the results
        // and print them out.
        Json::Value jsonData;
        Json::Reader jsonReader;

        if (jsonReader.parse(*httpData.get(), jsonData))
        {
            std::cout << "Successfully parsed JSON data" << std::endl;
            std::cout << "\nJSON data received:" << std::endl;
            std::cout << jsonData.toStyledString() << std::endl;

            const std::string dateString(jsonData["date"].asString());
            const std::size_t unixTimeMs(
                    jsonData["milliseconds_since_epoch"].asUInt64());
            const std::string timeString(jsonData["time"].asString());

            std::cout << "Natively parsed:" << std::endl;
            std::cout << "\tDate string: " << dateString << std::endl;
            std::cout << "\tUnix timeMs: " << unixTimeMs << std::endl;
            std::cout << "\tTime string: " << timeString << std::endl;
            std::cout << std::endl;
        }
        else
        {
            std::cout << "Could not parse HTTP data as JSON" << std::endl;
            std::cout << "HTTP data was:\n" << *httpData.get() << std::endl;
            return 1;
        }
    }
    else
    {
        std::cout << "Couldn't GET from " << url << " - exiting" << std::endl;
        return 1;
    }
    */
}
