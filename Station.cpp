#include "Station.h"
#include <cmath>

using namespace std;

Station::Station()
{
	id = 0;
	name = "Unassigned";
	positionKm = 0;
}

Station::Station(int stationId, const string& stationName, double position)
    : id(0), name("Unassigned"), positionKm(0)
{
	set_id(stationId);
	set_name(stationName);
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
	return positionKm;
}

bool Station::set_id(int stationId)
{
	if (stationId <= 0) return false;
	id = stationId;
	return true;
}

bool Station::set_name(const string& stationName)
{
	if (stationName.find_first_not_of(" \t\r\n") == string::npos) return false;
	name = stationName;
	return true;
}

bool Station::set_position_km(double position)
{
	if (!isfinite(position) || position < 0) return false;
	positionKm = position;
	return true;
}

ostream& operator<<(ostream& output, const Station& station)
{
	return output << station.get_name() << " (" << station.get_position_km() << " km)";
}

istream& operator>>(istream& input, Station& station)
{
	int id;
	double position;
	string name;
	if (input >> id >> position && getline(input >> ws, name)) {
		Station candidate;
		if (candidate.set_id(id) && candidate.set_position_km(position) && candidate.set_name(name))
			station = candidate;
		else
			input.setstate(ios::failbit);
	}
	return input;
}
