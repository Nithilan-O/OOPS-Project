#include "Metro.h"
#include <cmath>

using namespace std;

Metro::Metro() : trainNumber(1), capacity(200), operating(true), serviceType(0) {}
Metro::Metro(int number, int passengerCapacity, int type)
    : trainNumber(1), capacity(200), operating(true), serviceType(type) {
    setTrainNumber(number);
    setCapacity(passengerCapacity);
}
int Metro::getTrainNumber() const { return trainNumber; }
int Metro::getCapacity() const { return capacity; }
bool Metro::isOperating() const { return operating; }
bool Metro::setTrainNumber(int number) {
    if (number <= 0) return false;
    trainNumber = number;
    return true;
}
bool Metro::setCapacity(int passengerCapacity) {
    if (passengerCapacity <= 0) return false;
    capacity = passengerCapacity;
    return true;
}
void Metro::setOperating(bool status) { operating = status; }
string Metro::getType() const {
    if (serviceType == 1) return "Regular";
    if (serviceType == 2) return "Express";
    if (serviceType == 3) return "Airport";
    return "Metro";
}
string Metro::getFeatures() const {
    if (serviceType == 1) return "All stations; fare = 10 + 2 per km";
    if (serviceType == 2) return "Every second station and terminus; fare = 1.5 x regular fare";
    if (serviceType == 3) return "Limited stops and luggage space; fare = 2 x regular fare + 30";
    return "Standard passenger service";
}
double Metro::calculateFare(double distance) const {
    if (!isfinite(distance) || distance <= 0) return -1;
    double base = round((10.0 + 2.0 * distance) * 100.0) / 100.0;
    if (serviceType == 2) return round(base * 1.5 * 100.0) / 100.0;
    if (serviceType == 3) return round((base * 2.0 + 30.0) * 100.0) / 100.0;
    return base;
}
bool Metro::stopsAt(int index, int stationCount) const {
    if (index < 0 || index >= stationCount) return false;
    if (serviceType == 2) return index % 2 == 0 || index == stationCount - 1;
    if (serviceType == 3) return index == 0 || index == 4 || index == stationCount - 1;
    return true;
}
bool Metro::canServe(const Route& route, int sourceId, int destinationId) const {
    return operating && route.journeyDistance(sourceId, destinationId) > 0 &&
        stopsAt(route.findStation(sourceId), route.getCount()) &&
        stopsAt(route.findStation(destinationId), route.getCount());
}
ostream& operator<<(ostream& output, const Metro& metro) {
    return output << metro.getType() << " | Train " << metro.getTrainNumber()
        << " | Capacity: " << metro.getCapacity() << " | "
        << (metro.isOperating() ? "Operating" : "Out of service") << '\n'
        << metro.getFeatures() << '\n';
}
