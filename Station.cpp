#include "Station.h"
#include <cmath>

Station::Station() : id(0), name("Unassigned"), positionKm(0) {}

Station::Station(int stationId, const std::string& stationName, double position)
    : id(0), name("Unassigned"), positionKm(0) {
    setId(stationId);
    setName(stationName);
    setPositionKm(position);
}

int Station::getId() const { return id; }
const std::string& Station::getName() const { return name; }
double Station::getPositionKm() const { return positionKm; }
bool Station::setId(int stationId) {
    if (stationId <= 0) return false;
    id = stationId;
    return true;
}
bool Station::setName(const std::string& stationName) {
    if (stationName.find_first_not_of(" \t\r\n") == std::string::npos) return false;
    name = stationName;
    return true;
}
bool Station::setPositionKm(double position) {
    if (!std::isfinite(position) || position < 0) return false;
    positionKm = position;
    return true;
}

std::ostream& operator<<(std::ostream& output, const Station& station) {
    return output << station.getId() << ". " << station.getName()
                  << " (" << station.getPositionKm() << " km)";
}

std::istream& operator>>(std::istream& input, Station& station) {
    int id;
    double position;
    std::string name;
    if (input >> id >> position && std::getline(input >> std::ws, name)) {
        Station candidate;
        if (candidate.setId(id) && candidate.setPositionKm(position) && candidate.setName(name))
            station = candidate;
        else
            input.setstate(std::ios::failbit);
    }
    return input;
}
