#include <iostream>
#include <sstream>
#include "debug.h"
#include "base_map.h"
#include "time_graph.h"
#include "yahoo_api.h"
#include "window.h"
#include "signal_handler.h"

#include <iostream>
#include <fstream>
#include <iomanip>


using namespace std;

ofstream debugf;
ofstream graphwin;

int main() {

	// install our handler
  	signal(SIGSEGV, handler);   
	// Time zone set
	tzset();

	// Set Debug ttys
  	debugf.open("/dev/pts/10");
	graphwin.open("/dev/pts/11");

	graph_sin();
	return 0;
	//window::test();
	Display* d = new Display();
	
	//int win_numb = d->newWindow(5,5,0,0);


	// Graph it
	// Create Graph
	TimeGraph apple(200,40,d);
	apple.create();
	// Set Label Sizes
	apple.resizeLabelX(5);
	apple.resizeLabelY(6);


	// Obtain data
	std::vector<std::tuple<time_t, yahoo::OHLC*> > data = yahoo::getOHLC("AMD");


	// Find the Max/Min stock value
	time_t starttime = get<0>(data[0]);
	//double startdata = get<1>(data[0])->close;


	double max = 0;
	double min = 10000000;
	for (int i = 0; i < (signed)data.size(); i++) {
		yahoo::OHLC* point_data = get<1>(data[i]);
		double test = point_data->close;

		if(test > max) max = test;
		if(test < min) min = test;
	}

	//if(-min > max) max = -min;
	debugf<<max<<" "<<min<<endl;
	double startdata = (max + min) / 2;
	debugf<<"max2: "<<max<<endl;



	max = -10000000;
	min = 10000000;
	for (int i = 0; i < (signed)data.size(); i++) {
		yahoo::OHLC* point_data = get<1>(data[i]);
		double test = point_data->close-startdata;

		if(test > max) max = test;
		if(test < min) min = test;
	}


try{
	apple.setMinX(get<0>(data[0]));
	apple.setMaxX(get<0>(data[data.size()-1]));  // the difference between 9:30am and 4pm
	
	debugf<<"max: "<<startdata+max<<endl;
	debugf<<"min: "<<startdata+min<<endl;

	apple.setMaxY(startdata+max);
	apple.setMinY(startdata+min);
	//apple.setMaxY(max);
	//apple.setMinY(min);

	apple.autoLabelX(starttime, 2, 1);
	apple.autoLabelY(0, 0, 0.001);
} catch (const char * test) {
	debugf<<"ERROR: "<<test<<endl;
}
	// Place the points on the Graph
	debugf<<endl;
	for (int i = 0; i < (signed)data.size(); i++) {
		//tie(i_val,ignore,f_val) = tup1; 



		time_t t = get<0>(data[i]);
		yahoo::OHLC* point_data = get<1>(data[i]);
		double tdifference =  difftime (t, starttime);
		double value = point_data->close;



		apple.setCoord(tdifference, value);

		/*
		// This is for the cool graph effect
		if(value>0) {
			for(double j=value; j > 0; j=j-0.001) {
				apple.setCoord(tdifference, j);
			}
		}
		else
		{
			for(double j=value; j < 0; j=j+0.001) {
				apple.setCoord(tdifference, j);
			}
		}
		*/



 
		//debugf<<"("<<time<<", "<<point_data->close<<")"<<endl;

		// Sets labels as you fill in points
		std::string name = std::to_string(value + startdata); 
		//apple.setLabelY(name, value);
		//apple.setLabelX(time, tdifference);

		//usleep(100000);
		//apple.literalPrint();

	}
	apple.literalPrint();
	apple.updateScreen();
	//while(true);

	d->exit();
	debugf.close();
	graphwin.close();

	return 0;
}

/* Changelog
	New Labeling and old Stocks
	Huge Raw coord overhaul
	------------------------------------------
	--Integrating new labeling system with stock market
	--Now, via switch statement, you can determine how exactly
	  a numeric label should be formatted. Still no string
	--Moved extra functions to it's own file
	--getRawCoord() saw a huge overhaul. how positions are
	  calculated are now more explicit, and conditions are 
	  in place for different types of maps

*/	