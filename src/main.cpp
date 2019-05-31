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
	double startdata = get<1>(data[0])->close;


	double max = 0;
	double min = 10000000;
	for (int i = 0; i < (signed)data.size(); i++) {
		yahoo::OHLC* point_data = get<1>(data[i]);
		double test = point_data->close-startdata;

		if(test > max) max = test;
		if(test < min) min = test;
	}

	//debugf<<"max: "<<max<<endl;
	//debugf<<"min: "<<min<<endl;

	if(-min > max) max = -min;
	debugf<<max<<" "<<min<<endl;

	/*
	apple.setExtremeY(max);
	apple.setMaxY();
	apple.setMinY();


	// start here. 

	for(int i = 0; i < apple.numbofYlabels()/2; i++) {
		apple.setLabelY(name, value);
		apple.setLabelY(name, value);
	}
	*/
	apple.setMinX(get<0>(data[0]));
	apple.setMaxX(get<0>(data[data.size()-1]));  // the difference between 9:30am and 4pm
	
	// Place the points on the Graph
	debugf<<endl;
	for (int i = 0; i < (signed)data.size(); i++) {
		//tie(i_val,ignore,f_val) = tup1; 



		time_t t = get<0>(data[i]);
		yahoo::OHLC* point_data = get<1>(data[i]);
		double tdifference =  difftime (t, starttime);
		double value = point_data->close-startdata;



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


		tm * t_s = localtime(&t);

		std::string the_hour;
		if(t_s->tm_hour > 12) the_hour = std::to_string(t_s->tm_hour-12);
		else the_hour = std::to_string(t_s->tm_hour);

		std::stringstream time_stream;
		time_stream << std::setw (2) << std::setfill('0') << the_hour << ":" << std::setw (2) << std::setfill('0') << std::to_string(t_s->tm_min);
		std::string time = time_stream.str();
 
		//debugf<<"("<<time<<", "<<point_data->close<<")"<<endl;

		// Sets labels as you fill in points
		std::string name = std::to_string(value + startdata); 
		apple.setLabelY(name, value);
		apple.setLabelX(time, tdifference);

		//usleep(100000);
		apple.updateScreen(false);
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
	Fixed Cross Bug (Scaling issues)
	------------------------------------------
	--There's a known bug where if you graph a cross (y=x, y=-x), 
       the x and y values don't exactly line up, but only in the 
	   2 and 4th quadrants of a map. This bug is fixed now.
	--Also fixed major bug where y labels wouldn't show on TimeGraphs 
*/	