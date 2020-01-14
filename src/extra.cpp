#include "extra.hpp"

std::string makeTime(time_t t) {
	tm * t_s = localtime(&t);

	std::string the_hour;
	if(t_s->tm_hour > 12) the_hour = std::to_string(t_s->tm_hour-12);
	else the_hour = std::to_string(t_s->tm_hour);

	std::stringstream time_stream;
	time_stream << std::setw (2) << std::setfill('0') << the_hour << ":" << std::setw (2) << std::setfill('0') << std::to_string(t_s->tm_min);
	std::string time = time_stream.str();

	return time;
}

double roundToPlace(const double& x, const int& decimalPlaces) {
    int y=x;
    double z=x-y;
    double m=pow(10,decimalPlaces);
    double q=z*m;
    double r=round(q);

    return static_cast<double>(y)+(1.0/m)*r;
}


double roundToNearest(const double& x, const double& position) {
	if(!position) return x;
	double place = 1/position;
	return round(x*place)/place;
}
bool areSame(double a, double b, double strength)
{
	//debugf<<fabs(a - b)<<endl;
    return fabs(a - b) < strength;
}
