#include "MetroLine.h"
using namespace std;
MetroLine::MetroLine(const string& line_name,int maximum_stations)
: route(line_name,maximum_stations)
{
}
MetroLine::~MetroLine()
{
}
bool MetroLine::add_station(Station& station)
{
	return route.add_station(station);
}
const Route& MetroLine::get_route() const
{
	return route;
}
ostream& operator<<(ostream& output,const MetroLine& line)
{
	return output<<line.get_route();
}
