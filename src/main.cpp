#include <iostream>
#include "base_map.h"
#include "time_graph.h"
using namespace std;


main() {

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
}

/* Changelog
	refactored repository
*/