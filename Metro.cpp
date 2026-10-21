#include "Metro.h"
#include <cmath>

Metro::Metro() : trainNumber(1), capacity(200), operating(true) {}
Metro::Metro(int number, int passengerCapacity) : trainNumber(1), capacity(200), operating(true) {
    setTrainNumber(number);
    setCapacity(passengerCapacity);
}
Metro::~Metro() {}
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
std::string Metro::getType() const { return "Metro"; }
std::string Metro::getFeatures() const { return "Standard passenger service"; }
double Metro::calculateFare(double distance) const {
    if (!std::isfinite(distance) || distance <= 0) return -1;
    return std::round((10.0 + 2.0 * distance) * 100.0) / 100.0;
}
bool Metro::stopsAt(int index, int stationCount) const { return index >= 0 && index < stationCount; }
bool Metro::canServe(const Route& route, int sourceId, int destinationId) const {
    return operating && route.journeyDistance(sourceId, destinationId) > 0 &&
        stopsAt(route.findStation(sourceId), route.getCount()) &&
        stopsAt(route.findStation(destinationId), route.getCount());
}
RegularMetro::RegularMetro() : Metro(101, 300) {}
std::string RegularMetro::getType() const { return "Regular"; }
std::string RegularMetro::getFeatures() const { return "All stations; fare = 10 + 2 per km"; }
ExpressMetro::ExpressMetro() : Metro(201, 220) {}
std::string ExpressMetro::getType() const { return "Express"; }
std::string ExpressMetro::getFeatures() const { return "Every second station and terminus; fare = 1.5 x regular fare"; }
double ExpressMetro::calculateFare(double distance) const {
    double base = Metro::calculateFare(distance);
    return base < 0 ? -1 : std::round(base * 1.5 * 100.0) / 100.0;
}
bool ExpressMetro::stopsAt(int index, int stationCount) const {
    return Metro::stopsAt(index, stationCount) && (index % 2 == 0 || index == stationCount - 1);
}
AirportMetro::AirportMetro() : Metro(301, 180) {}
std::string AirportMetro::getType() const { return "Airport"; }
std::string AirportMetro::getFeatures() const { return "Limited stops and luggage space; fare = 2 x regular fare + 30"; }
double AirportMetro::calculateFare(double distance) const {
    double base = Metro::calculateFare(distance);
    return base < 0 ? -1 : std::round((base * 2.0 + 30.0) * 100.0) / 100.0;
}
bool AirportMetro::stopsAt(int index, int stationCount) const {
    return Metro::stopsAt(index, stationCount) && (index == 0 || index == 4 || index == stationCount - 1);
}
std::ostream& operator<<(std::ostream& output, const Metro& metro) {
    return output << metro.getType() << " | Train " << metro.getTrainNumber()
        << " | Capacity: " << metro.getCapacity() << " | "
        << (metro.isOperating() ? "Operating" : "Out of service") << '\n'
        << metro.getFeatures() << '\n';
}
