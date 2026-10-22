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
	setTrainNumber(number);
	setCapacity(passengerCapacity);
}

int Metro::getTrainNumber() const
{
	return trainNumber;
}

int Metro::getCapacity() const
{
	return capacity;
}

bool Metro::isOperating() const
{
	return operating;
}

bool Metro::setTrainNumber(int number)
{
	if (number <= 0) return false;
	trainNumber = number;
	return true;
}

bool Metro::setCapacity(int passengerCapacity)
{
	if (passengerCapacity <= 0) return false;
	capacity = passengerCapacity;
	return true;
}

void Metro::setOperating(bool status)
{
	operating = status;
}

string Metro::getType() const
{
	return "Regular";
}

string Metro::getFeatures() const
{
	return "Stops at A, B, and C; fare = 10 + 2 per km";
}

double Metro::calculateFare(double distance) const
{
	if (!isfinite(distance) || distance <= 0) return -1;
	return round((10.0 + 2.0 * distance) * 100.0) / 100.0;
}

bool Metro::stopsAt(int index, int stationCount) const
{
	return index >= 0 && index < stationCount;
}

bool Metro::canServe(const Route& route, int sourceId, int destinationId) const
{
	return operating && route.journeyDistance(sourceId, destinationId) > 0 &&
		stopsAt(route.findStation(sourceId), route.getCount()) &&
		stopsAt(route.findStation(destinationId), route.getCount());
}

ostream& operator<<(ostream& output, const Metro& metro)
{
	return output << metro.getType() << " | Train " << metro.getTrainNumber()
		<< " | Capacity: " << metro.getCapacity() << " | "
		<< (metro.isOperating() ? "Operating" : "Out of service") << '\n'
		<< metro.getFeatures() << '\n';
}
