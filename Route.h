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
    const string& getName() const;
    int getCount() const;
    bool addStation(const Station& station);
    bool getStation(int index, Station& result) const;
    int findStation(int stationId) const;
    double journeyDistance(int sourceId, int destinationId) const;
    int stationsTravelled(int sourceId, int destinationId) const;
};

ostream& operator<<(ostream& output, const Route& route);

#endif
