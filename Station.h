#ifndef STATION_H
#define STATION_H

#include <iostream>
#include <string>

using namespace std;

class Station {
private:
    int id;
    string name;
    double positionKm;
public:
    Station();
    Station(int stationId, const string& stationName, double position);
    int getId() const;
    const string& getName() const;
    double getPositionKm() const;
    bool setId(int stationId);
    bool setName(const string& stationName);
    bool setPositionKm(double position);
};

ostream& operator<<(ostream& output, const Station& station);
istream& operator>>(istream& input, Station& station);

#endif
