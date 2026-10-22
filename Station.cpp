#include "Station.h"
#include <cmath>
using namespace std;
Station::Station()
{
	id=0;
	name="Unassigned";
	position_km=0;
}
Station::Station(int station_id,const string& station_name,double position)
	:id(0),name("Unassigned"),position_km(0)
	{
		set_id(station_id);
		set_name(station_name);
		set_position_km(position);
	}
int Station::get_id() const
{
	return id;
}
const string& Station::get_name() const
{
	return name;
}
double Station::get_position_km() const
{
	return position_km;
}
bool Station::set_id(int station_id)
{
	if(station_id<=0)
	{
		return false;
	}
	id=station_id;
	return true;
}
bool Station::set_name(const string& station_name)
{
	if(station_name.find_first_not_of(" \t\r\n")==string::npos)
	{
		return false;
	}
	name=station_name;
	return true;
}
bool Station::set_position_km(double position)
{
	if(not isfinite(position) or position<0)
	{
		return false;
	}
	position_km=position;
	return true;
}
ostream& operator<<(ostream& output,const Station& station)
{
	return output<<station.get_name()<<" ("<<station.get_position_km()<<" km)";
}
istream& operator>>(istream& input,Station& station)
{
	input>>station.id>>station.position_km;
	getline(input>>ws,station.name);
	return input;
}
