#include "stock/draw.h"

bool stopdrawing = false;


void stopListening(int sig) {
    stopdrawing = true;
    sigintDefault(sig); // I don't think this is a paticularly good idea..
}


void stockDraw(std::string stock) {
    // Get a new display
    Display* d = new Display();
    
    // Create a Map
    TimeGraph sgraph(200,40,d);
    sgraph.create();

    // Set Label Sizes (for now...)
	sgraph.resizeLabelX(5);
	sgraph.resizeLabelY(6);
    stopdrawing = false;
    signal(SIGINT, stopListening);   
    while(!stopdrawing) {
        // Get your stock data 
        std::vector<yahoo::OHLC*> sdata = yahoo::getOHLC(stock);
        

        // Preprocessing 

        yahoo::OHLC max, min, average;

        // Lots of lambdas ahead
        auto result = getOHLCminmax(sdata);
        max = std::get<0>(result);
        min = std::get<1>(result);

        double addby = std::max(ceil(max.close)-max.close, min.close - floor(min.close));
        int top = ceil(max.close);
        int bot = floor(min.close);
        sgraph.setMaxY(top);
        sgraph.setMinY(bot);



        sgraph.setMaxX(max.time);
        sgraph.setMinX(min.time);

        debugf<<"maxY: "<<max.close<<" top: "<<top<<std::endl;
        debugf<<"minY: "<<min.close<<" bot: "<<bot<<std::endl;
        debugf<<"realdif: "<<(max.close+min.close)/2<<std::endl;
        debugf<<"tbdif: "<<(top+bot)/2<<std::endl;
        debugf<<std::endl;



        int zerox = sdata[0]->time;
        double zeroy = (top+bot)/2;

        try{

        sgraph.autoLabelY(zerox,zeroy,0,0.001);
        sgraph.autoLabelX(zerox,zeroy,2);

        } catch (const char * error) {
            debugf<<"ERROR: "<<error<<std::endl;
        }
        for(std::vector<yahoo::OHLC*>::iterator it = sdata.begin(); 
            it != sdata.end(); it++) 
        {
            yahoo::OHLC* point = *it;
            sgraph.setCoord(point->time, point->close);
            //coolGraphEffect(point->time, point->close, zeroy, &sgraph);
        }
        
        sgraph.updateScreen(false);
        usleep(60*1000*1000);
    }
    signal(SIGINT, sigintDefault);   
    d->exit();
}

void stockDrawFull(std::string stock) {
    // Get a new display
    Display* d = new Display();
    
    // Create a Map
    PositiveTimeGraph sgraph(200,40,d);
    sgraph.create();

    // Set Label Sizes (for now...)
	sgraph.resizeLabelX(5);
	sgraph.resizeLabelY(6);

    // Get your stock data 
	std::vector<yahoo::OHLC*> sdata = yahoo::getOHLC(stock);
    

    // Preprocessing 

    yahoo::OHLC max, min, average;

    // Lots of lambdas ahead
    auto result = getOHLCminmax(sdata);
    max = std::get<0>(result);
    min = std::get<1>(result);

    double addby = std::max(ceil(max.close)-max.close, min.close - floor(min.close));
    debugf<<"addbye::::"<<addby<<std::endl;
    double top = (max.close);
    double bot = (min.close);
    sgraph.setMaxY(top);
    sgraph.setMinY(bot);



    sgraph.setMaxX(max.time);
    sgraph.setMinX(min.time);

    debugf<<"maxY: "<<max.close<<" top: "<<top<<std::endl;
    debugf<<"minY: "<<min.close<<" bot: "<<bot<<std::endl;
    debugf<<"realdif: "<<(max.close+min.close)/2<<std::endl;
    debugf<<"tbdif: "<<(top+bot)/2<<std::endl;
    debugf<<std::endl;



    int zerox = sdata[0]->time;
    double zeroy = (bot);

    try{
    sgraph.autoLabelY(zerox,zeroy,0,0.001);
    sgraph.autoLabelX(zerox,zeroy,2);
    } catch (const char * error) {
        debugf<<"ERROR: "<<error<<std::endl;
    }
    
    for(std::vector<yahoo::OHLC*>::iterator it = sdata.begin(); 
        it != sdata.end(); it++) 
    {
        yahoo::OHLC* point = *it;
        sgraph.setCoord(point->time, point->close);
        //coolGraphEffect(point->time, point->close, zeroy, &sgraph);

    }
    sgraph.updateScreen();

    d->exit();
}

void stockDrawWithPast(std::string stock, time_t center) {
    // Get a new display
    Display* d = new Display();
    
    // Create a Map
    TimeGraph sgraph(200,40,d);
    sgraph.create();

    // Set Label Sizes (for now...)
	sgraph.resizeLabelX(5);
	sgraph.resizeLabelY(6);

    // Get your stock data 
    std::vector<yahoo::OHLC*> sdata = yahoo::getOHLC(stock);
    

    // Preprocessing 

    yahoo::OHLC max, min, average;

    // Lots of lambdas ahead
    auto result = getOHLCminmax(sdata);
    max = std::get<0>(result);
    min = std::get<1>(result);

    double addby = std::max(ceil(max.close)-max.close, min.close - floor(min.close));
    int top = ceil(max.close);
    int bot = floor(min.close);
    sgraph.setMaxY(top);
    sgraph.setMinY(bot);



    sgraph.setMaxX(max.time);
    sgraph.setMinX(min.time);

    debugf<<"maxY: "<<max.close<<" top: "<<top<<std::endl;
    debugf<<"minY: "<<min.close<<" bot: "<<bot<<std::endl;
    debugf<<"realdif: "<<(max.close+min.close)/2<<std::endl;
    debugf<<"tbdif: "<<(top+bot)/2<<std::endl;
    debugf<<std::endl;



    int zerox = center;
    double zeroy = (top+bot)/2;

    try{
        sgraph.autoLabelY(zerox,zeroy,0,0.001);
        sgraph.autoLabelX(zerox,zeroy,2);
    } catch (const char * error) {
        debugf<<"ERROR: "<<error<<std::endl;
    }

    for(std::vector<yahoo::OHLC*>::iterator it = sdata.begin(); 
        it != sdata.end(); it++) 
    {
        yahoo::OHLC* point = *it;
        sgraph.setCoord(point->time, point->close);
        //coolGraphEffect(point->time, point->close, zeroy, &sgraph);
    }
    
    sgraph.updateScreen();
    
    d->exit();
}


void coolGraphEffect(time_t x, double y, double min, Map * map) {
    // This is for the cool graph effect
    if(y>min) {
        for(double j=y; j > min; j=j-0.01) {
            map->setCoord(x, j);
        }
    }
    else
    {
        for(double j=y; j < min; j=j+0.01) {
            map->setCoord(x, j);
        }
    }
}




// Get Maxs and mins
std::tuple<yahoo::OHLC, yahoo::OHLC> getOHLCminmax(std::vector<yahoo::OHLC*> data) {
    yahoo::OHLC max, min;
    std::vector<yahoo::OHLC*>::iterator minpoint, maxpoint;

    maxpoint = std::max_element(std::begin(data), std::end(data),
        [](const yahoo::OHLC* a, const yahoo::OHLC* b) {return a->open < b->open;}); 
    minpoint = std::min_element(std::begin(data), std::end(data),
        [](const yahoo::OHLC* a, const yahoo::OHLC* b) {return a->open < b->open;}); 
    max.open = (*maxpoint)->open;
    min.open = (*minpoint)->open;

    maxpoint = std::max_element(std::begin(data), std::end(data),
        [](const yahoo::OHLC* a, const yahoo::OHLC* b) {return a->high < b->high;}); 
    minpoint = std::min_element(std::begin(data), std::end(data),
        [](const yahoo::OHLC* a, const yahoo::OHLC* b) {return a->high < b->high;}); 
    max.high = (*maxpoint)->high;
    min.high = (*minpoint)->high;

    maxpoint = std::max_element(std::begin(data), std::end(data),
        [](const yahoo::OHLC* a, const yahoo::OHLC* b) {return a->low < b->low;}); 
    minpoint = std::min_element(std::begin(data), std::end(data),
        [](const yahoo::OHLC* a, const yahoo::OHLC* b) {return a->low < b->low;}); 
    max.low = (*maxpoint)->low;
    min.low = (*minpoint)->low;
    
    maxpoint = std::max_element(std::begin(data), std::end(data),
        [](const yahoo::OHLC* a, const yahoo::OHLC* b) {return a->close < b->close;}); 
    minpoint = std::min_element(std::begin(data), std::end(data),
        [](const yahoo::OHLC* a, const yahoo::OHLC* b) {return a->close < b->close;}); 
    max.close = (*maxpoint)->close;
    min.close = (*minpoint)->close;
    
    maxpoint = std::max_element(std::begin(data), std::end(data),
        [](const yahoo::OHLC* a, const yahoo::OHLC* b) {return a->time < b->time;}); 
    minpoint = std::min_element(std::begin(data), std::end(data),
        [](const yahoo::OHLC* a, const yahoo::OHLC* b) {return a->time < b->time;}); 
    max.time = (*maxpoint)->time;
    min.time = (*minpoint)->time;

    maxpoint = std::max_element(std::begin(data), std::end(data),
        [](const yahoo::OHLC* a, const yahoo::OHLC* b) {return a->volume < b->volume;}); 
    minpoint = std::min_element(std::begin(data), std::end(data),
        [](const yahoo::OHLC* a, const yahoo::OHLC* b) {return a->volume < b->volume;}); 
    max.volume = (*maxpoint)->volume;
    min.volume = (*minpoint)->volume;

    return std::tie(max,min);
}

