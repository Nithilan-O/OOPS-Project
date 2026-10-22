#include "Metro.h"
#include <cmath>

using namespace std;

Metro::Metro()
{
	trainNumber = 1;
	capacity = 200;
	operating = true;
}

Metro::Metro(int number, int passengerCapacity)
{
	trainNumber = 1;
	capacity = 200;
	operating = true;
	set_train_number(number);
	set_capacity(passengerCapacity);
}

int Metro::get_train_number() const
{
	return trainNumber;
}

int Metro::get_capacity() const
{
	return capacity;
}

bool Metro::is_operating() const
{
	return operating;
}

bool Metro::set_train_number(int number)
{
	if (number <= 0) return false;
	trainNumber = number;
	return true;
}

bool Metro::set_capacity(int passengerCapacity)
{
	if (passengerCapacity <= 0) return false;
	capacity = passengerCapacity;
	return true;
}

void Metro::set_operating(bool status)
{
	operating = status;
}

string Metro::get_type() const
{
	return "Regular";
}

string Metro::get_features() const
{
	return "Stops at A, B, and C; fare = 10 + 2 per km";
}

double Metro::calculate_fare(double distance) const
{
	if (!isfinite(distance) || distance <= 0) return -1;
	return round((10.0 + 2.0 * distance) * 100.0) / 100.0;
}

bool Metro::stops_at(int index, int stationCount) const
{
	return index >= 0 && index < stationCount;
}

bool Metro::can_serve(const Route& route, int sourceId, int destinationId) const
{
	return operating && route.journey_distance(sourceId, destinationId) > 0 &&
		stops_at(route.find_station(sourceId), route.get_count()) &&
		stops_at(route.find_station(destinationId), route.get_count());
}

ostream& operator<<(ostream& output, const Metro& metro)
{
	return output << metro.get_type() << " | Train " << metro.get_train_number()
		<< " | Capacity: " << metro.get_capacity() << " | "
		<< (metro.is_operating() ? "Operating" : "Out of service") << '\n'
		<< metro.get_features() << '\n';
}
