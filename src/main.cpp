#include <iostream>
#include <sstream>
#include "base_map.h"
#include "time_graph.h"
#include "yahoo_api.h"
#include "window.h"
#include "signal_handler.h"
using namespace std;


int main() {

  	signal(SIGSEGV, handler);   // install our handler
	//window::test();
	Display* d = new Display();
	/*
	int win_numb = d->newWindow(5,5,0,0);
	d->debugSwitch();
	d->write(win_numb, 'A', 0,0,3);
	d->write(win_numb, 'B', 0,1,1);
	d->write(win_numb, 'C', 0,2,2);
	d->write(win_numb, 'D', 0,3,2);
	d->write(win_numb, 'E', 0,4,1);
	d->write(win_numb, 'F', 0,5,1);


*/
	// block
	d->exit();
	std::vector<std::tuple<time_t, yahoo::OHLC*> > data = yahoo::getOHLC("SP");

	TimeGraph apple(100,40,d);
	apple.create();
	

	apple.scaleY((double)1/7);
	apple.scaleX((double)230);
	time_t starttime = get<0>(data[0]);
	double startdata = get<1>(data[0])->close;
	double maxdiff = difftime(get<0>(data[data.size()-1]), starttime);
	cout<<"maxdiff: "<<maxdiff<<endl;

	double max = 0;
	double min = 10000000;

	for (int i = 0; i < (signed)data.size(); i++) {
		//tie(i_val,ignore,f_val) = tup1; 
		time_t t = get<0>(data[i]);
		yahoo::OHLC* point_data = get<1>(data[i]);
		double difference =  difftime (t, starttime);
		apple.setCoord(difference, point_data->close-startdata);
		
		double test = point_data->close;
		if(test > max) max = test;
		if(test < min) min = test;
	}

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
	vector<std::string> bw = {"org","app","tag","yam","sto","exch"};



	apple.setLabelY(aw);
	apple.setLabelX(bw);
	//apple.print();
	apple.updateScreen();
	d->exit();
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
	Added simple way to generate label values (for debug purposes)
	Added coloring for points: green if positive, red if negative
*/