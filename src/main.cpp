#include <iostream>
#include "base_map.h"
#include "time_graph.h"
#include "yahoo_api.h"
#include "window.h"
using namespace std;


int main() {

	std::vector<std::tuple<time_t, yahoo::OHLC*> > data = yahoo::getOHLC("AAPL");

	TimeGraph apple(100,40);
	apple.create();

	apple.scaleY((double)1/7);
	apple.scaleX((double)230);
	time_t starttime = get<0>(data[0]);
	double startdata = get<1>(data[0])->close;
	double maxdiff = difftime(get<0>(data[data.size()-1]), starttime);
	cout<<"maxdiff: "<<maxdiff<<endl;


	for (int i = 0; i < (signed)data.size(); i++) {
		//tie(i_val,ignore,f_val) = tup1; 
		time_t t = get<0>(data[i]);
		yahoo::OHLC* point_data = get<1>(data[i]);
		double difference =  difftime (t, starttime);
		apple.setCoord(difference, point_data->close-startdata);
	}
	vector<std::string> aw = {"432.42","bfs","c"};
	vector<std::string> bw = {"org","app","tag","yam","sto","exch"};
	apple.setLabelY(aw);
	apple.setLabelX(bw);
	apple.print();
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
	Variable length labels in the yaxis has been implimented
	Variable length labels in the xaxis has been implimented	
		Various ways to set those labels
	Removed stock_in files
*/