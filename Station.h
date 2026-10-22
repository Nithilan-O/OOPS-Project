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
    int get_id() const;
    const string& get_name() const;
    double get_position_km() const;
    bool set_id(int stationId);
    bool set_name(const string& stationName);
    bool set_position_km(double position);
};

ostream& operator<<(ostream& output, const Station& station);
istream& operator>>(istream& input, Station& station);

#endif
