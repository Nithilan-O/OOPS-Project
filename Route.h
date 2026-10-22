#ifndef ROUTE_H
#define ROUTE_H

#include "Station.h"

using namespace std;

class Route {
private:
    string name;
    Station* stations;
    int count;
    int capacity;
public:
    Route();
    Route(const string& routeName, int maximumStations);
    Route(const Route& other);
    Route& operator=(const Route& other);
    ~Route();
    const string& get_name() const;
    int get_count() const;
    bool add_station(const Station& station);
    bool get_station(int index, Station& result) const;
    int find_station(int stationId) const;
    double journey_distance(int sourceId, int destinationId) const;
    int stations_travelled(int sourceId, int destinationId) const;
};

ostream& operator<<(ostream& output, const Route& route);

#endif
