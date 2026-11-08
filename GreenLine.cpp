#include "GreenLine.h"
using namespace std;
GreenLine::GreenLine():MetroLine("Green Line",9)
{
}
string GreenLine::get_line_name() const
{
	return "Green Line";
}
void GreenLine::configure_route(Station* stations)
{
	const int station_ids[9]={7,19,18,17,16,15,14,2,13};
	for(int i=0;i<9;++i)
	{
		add_station(stations[station_ids[i]-1]);
	}
}
