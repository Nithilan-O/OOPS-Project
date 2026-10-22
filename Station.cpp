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
	setId(stationId);
	setName(stationName);
	setPositionKm(position);
}

int Station::getId() const
{
	return id;
}

const string& Station::getName() const
{
	return name;
}

double Station::getPositionKm() const
{
	return positionKm;
}

bool Station::setId(int stationId)
{
	if (stationId <= 0) return false;
	id = stationId;
	return true;
}

bool Station::setName(const string& stationName)
{
	if (stationName.find_first_not_of(" \t\r\n") == string::npos) return false;
	name = stationName;
	return true;
}

bool Station::setPositionKm(double position)
{
	if (!isfinite(position) || position < 0) return false;
	positionKm = position;
	return true;
}

ostream& operator<<(ostream& output, const Station& station)
{
	return output << station.getName() << " (" << station.getPositionKm() << " km)";
}

istream& operator>>(istream& input, Station& station)
{
	int id;
	double position;
	string name;
	if (input >> id >> position && getline(input >> ws, name)) {
		Station candidate;
		if (candidate.setId(id) && candidate.setPositionKm(position) && candidate.setName(name))
			station = candidate;
		else
			input.setstate(ios::failbit);
	}
	return input;
}
