#include "MetroLine.h"
#include <stdexcept>
using namespace std;
MetroLine::MetroLine(const string& line_name,int maximum_stations)
: route(line_name,maximum_stations)
{
}
MetroLine::~MetroLine()
{
}
void MetroLine::add_station(Station& station)
{
	if(not route.add_station(station))
	{
		throw logic_error("Invalid station while configuring "+route.get_name());
	}
}
const Route& MetroLine::get_route() const
{
	return route;
}
ostream& operator<<(ostream& output,const MetroLine& line)
{
	return output<<line.get_route();
}
