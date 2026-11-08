#include "BlueLine.h"
using namespace std;
BlueLine::BlueLine():MetroLine("Blue Line",12)
{
}
string BlueLine::get_line_name() const
{
	return "Blue Line";
}
void BlueLine::configure_route(Station* stations)
{
	const int station_ids[12]={12,11,10,9,8,7,6,5,4,3,2,1};
	for(int i=0;i<12;++i)
	{
		add_station(stations[station_ids[i]-1]);
	}
}
