#include <iostream>
#include <sstream>
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

  	signal(SIGSEGV, handler);   // install our handler
	//window::test();
	Display* d = new Display();
	
	int win_numb = d->newWindow(5,5,0,0);
	d->debugSwitch();
	d->write(win_numb, 'A', 0,0,3);
	d->write(win_numb, 'B', 0,1,1);
	d->write(win_numb, 'C', 0,2,2);
	d->write(win_numb, 'D', 0,3,2);
	d->write(win_numb, 'E', 0,4,1);
	d->write(win_numb, 'F', 0,5,1);


  	debugf.open("/dev/pts/5");
	graphwin.open("/dev/pts/7");

	// block
	d->exit();

	// Time zone set
	tzset();


	// Graph it
	TimeGraph apple(200,40,d);
	//Map apple(50,20,d);
	apple.create();

	// Clear out the verticle labels
	vector<string> newl;
	for(int i = 0; i < apple.getNumberOfYLabels(); i++) {
		string a = "      ";
		newl.push_back(a);
	}

	apple.setLabelY(newl);	
	//apple.setLabelX(bw);
	//apple.setLabelX("hello", 0.0);
	apple.setCoord(0,4);

	// Obtain data
	std::vector<std::tuple<time_t, yahoo::OHLC*> > data = yahoo::getOHLC("AMD");

	//apple.scaleY((double)1/7);
	//apple.scaleX((double)230);
	time_t starttime = get<0>(data[0]);
	double startdata = get<1>(data[0])->close;

	double maxdiff = difftime(get<0>(data[data.size()-1]), starttime);

	// Find the Max/Min stock value
	double max = 0;
	double min = 10000000;
	double maxtime = 1;
	for (int i = 0; i < (signed)data.size(); i++) {
		yahoo::OHLC* point_data = get<1>(data[i]);
		double test = point_data->close-startdata;

		if(test > max) max = test;
		if(test < min) min = test;
		maxtime =  difftime (get<0>(data[i]), starttime);
	}
	//debugf<<"max: "<<max<<endl;
	//adebugf<<"min: "<<min<<endl;

	if(-min > max) max = min;
	apple.scaleY(max);
	//apple.setMinY(min);
	apple.scaleX(19800);  // the difference between 9:30am and 4pm
	
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

		std:string the_hour;
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
	return 0;

	// Very basic and inaccurante way of creating labels
	double add = (max - min)/40;
	vector<std::string> aw;
	for (int i = 0; i < (signed)data.size(); i++) {
		double val = max - (add*i);

		std::ostringstream strs;
		strs << val;
		std::string str = strs.str();

		aw.push_back(str);
	}
	//vector<std::string> aw = {"432.42","bfs","c"};
	//vector<std::string> bw = {"org","app","tag","yam","sto","exch"};



	apple.setLabelY(aw);
	//apple.setLabelX(bw);

	//string fda = "hello"
	//apple.print();
	apple.updateScreen();
	//apple.showDebugScreen();
	d->exit();

	debugf.close();
	graphwin.close();
	return 0;
/* //
	int x[] = {1,2,3,4,5,6,7,8,9,10};
	int y[] = {4,7,3,5,8,3,4,6,7,1};

	int len = 10;
	Map a(11,13);
	CoordinateGrid b(41);
	TimeGraph c(11,13);
	PositiveTimeGraph d(41,24);
	a.create();
	b.create();
	c.create();
	d.create();	

	b.scaleX((double)1/10);
	vector<char> newl;
	for(int i = 0; i < a.getMaxY()-a.getMinY()+1; i++) {
		newl.push_back('A' + i);
	}
	a.setLabelY(newl);

	c.setCoord(0,3);
	d.setCoord(0,0);
	b.setCoord(0,-1);
	b.setCoord(-1,0);
	b.setCoord(0,0);

	for(double i = b.getMinX(); i < b.getMaxX(false); i=i+0.01) {
		if(!i) continue;
		b.setCoord(i,1/i);
	}
	d.scaleX((double)1/10);
	d.scaleY((double)1/10);
	for(double i = 0; i < d.getMaxX(false); i=i+0.1) {
		d.setCoord(i,log(i));
	}
	cout<<a.getMaxX()<<endl;
	for (int i = -25; i < 25; i++) {
		a.setCoord(i,10*sin(i*2));
		c.setCoord(i,10*sin(i*2));
		d.setCoord(i,10*sin(i*2));
	}
	//b.setCoord(0,11);
	a.print();
	cout<<endl;	
	b.print();
	cout<<endl;
	c.print();
	cout<<endl;
	d.print();
	cout<<endl;

	return 0;
*/
}

/* Changelog
	Imporiving graphs: integration with ncurses
	------------------------------------------
	Simplified UpdateScreen(), now all it has to do is write
	 the data in theMap[][]
	Fixed issue where graph would sometimes flatline
	Other display bugs fixed (graph starts at 9:30, y=0 values shown, etc.)

*/