#ifndef STATION_H
#define STATION_H

#include <iostream>
#include <string>

class Station {
private:
    int id;
    std::string name;
    double positionKm;
public:
    Station();
    Station(int stationId, const std::string& stationName, double position);
    int getId() const;
    const std::string& getName() const;
    double getPositionKm() const;
    bool setId(int stationId);
    bool setName(const std::string& stationName);
    bool setPositionKm(double position);
};

std::ostream& operator<<(std::ostream& output, const Station& station);
std::istream& operator>>(std::istream& input, Station& station);

#endif
