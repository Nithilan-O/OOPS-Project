#include "Route.h"
#include <cmath>

using namespace std;

Route::Route()
{
	name = "Unnamed route";
	stations = new Station[10];
	count = 0;
	capacity = 10;
}

Route::Route(const string& routeName, int maximumStations)
{
	name = routeName.empty() ? "Unnamed route" : routeName;
	capacity = maximumStations > 0 ? maximumStations : 10;
	stations = new Station[capacity];
	count = 0;
}

Route::Route(const Route& other)
{
	name = other.name;
	stations = new Station[other.capacity];
	count = other.count;
	capacity = other.capacity;
	for (int i = 0; i < count; ++i) stations[i] = other.stations[i];
}

Route& Route::operator=(const Route& other)
{
	if (this != &other) {
		Station* replacement = new Station[other.capacity];
		for (int i = 0; i < other.count; ++i) replacement[i] = other.stations[i];
		delete[] stations;
		stations = replacement;
		name = other.name;
		count = other.count;
		capacity = other.capacity;
	}
	return *this;
}

Route::~Route()
{
	delete[] stations;
}

const string& Route::get_name() const
{
	return name;
}

int Route::get_count() const
{
	return count;
}

bool Route::add_station(const Station& station)
{
	if (count == capacity || station.get_id() <= 0 || find_station(station.get_id()) >= 0) return false;
	if (count > 0 && station.get_position_km() <= stations[count - 1].get_position_km()) return false;
	stations[count++] = station;
	return true;
}

bool Route::get_station(int index, Station& result) const
{
	if (index < 0 || index >= count) return false;
	result = stations[index];
	return true;
}

int Route::find_station(int stationId) const
{
	for (int i = 0; i < count; ++i) {
		if (stations[i].get_id() == stationId) return i;
	}
	return -1;
}

double Route::journey_distance(int sourceId, int destinationId) const
{
	int source = find_station(sourceId);
	int destination = find_station(destinationId);
	if (source < 0 || destination < 0 || source == destination) return -1;
	return fabs(stations[source].get_position_km() - stations[destination].get_position_km());
}

int Route::stations_travelled(int sourceId, int destinationId) const
{
	int source = find_station(sourceId);
	int destination = find_station(destinationId);
	if (source < 0 || destination < 0 || source == destination) return -1;
	return source > destination ? source - destination : destination - source;
}

ostream& operator<<(ostream& output, const Route& route)
{
	output << route.get_name() << " (both directions)\n";
	for (int i = 0; i < route.get_count(); ++i) {
		Station station;
		route.get_station(i, station);
		output << station;
		if (i + 1 < route.get_count()) output << " -> ";
	}
	return output << '\n';
}
