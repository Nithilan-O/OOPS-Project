#ifndef ROUTE_H
#define ROUTE_H

#include "Station.h"

class Route {
private:
    std::string name;
    Station* stations;
    int count;
    int capacity;
public:
    Route();
    Route(const std::string& routeName, int maximumStations);
    Route(const Route& other);
    Route& operator=(const Route& other);
    ~Route();
    const std::string& getName() const;
    int getCount() const;
    bool addStation(const Station& station);
    bool getStation(int index, Station& result) const;
    int findStation(int stationId) const;
    double journeyDistance(int sourceId, int destinationId) const;
    int stationsTravelled(int sourceId, int destinationId) const;
};

std::ostream& operator<<(std::ostream& output, const Route& route);

#endif
