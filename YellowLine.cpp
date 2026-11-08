#include "YellowLine.h"
using namespace std;
YellowLine::YellowLine():MetroLine("Yellow Line",7)
{
}
string YellowLine::get_line_name() const
{
	return "Yellow Line";
}
void YellowLine::configure_route(Station* stations)
{
	const int station_ids[7]={25,24,23,22,21,20,15};
	for(int i=0;i<7;++i)
	{
		add_station(stations[station_ids[i]-1]);
	}
}
