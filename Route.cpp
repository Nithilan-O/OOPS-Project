#include "Route.h"
#include <cmath>

using namespace std;

Route::Route() : name("Unnamed route"), stations(new Station[10]), count(0), capacity(10) {}
Route::Route(const string& routeName, int maximumStations)
    : name(routeName.empty() ? "Unnamed route" : routeName),
      stations(new Station[maximumStations > 0 ? maximumStations : 10]),
      count(0), capacity(maximumStations > 0 ? maximumStations : 10) {}
Route::Route(const Route& other)
    : name(other.name), stations(new Station[other.capacity]), count(other.count), capacity(other.capacity) {
    for (int i = 0; i < count; ++i) stations[i] = other.stations[i];
}
Route& Route::operator=(const Route& other) {
    if (this != &other) {
        Station* replacement = new Station[other.capacity];
        for (int i = 0; i < other.count; ++i) replacement[i] = other.stations[i];
        delete[] stations;
        stations = replacement;
        name = other.name;
        count = other.count;
        capacity = other.capacity;
    }
    return *this;
}
Route::~Route() { delete[] stations; }
const string& Route::getName() const { return name; }
int Route::getCount() const { return count; }
bool Route::addStation(const Station& station) {
    if (count == capacity || station.getId() <= 0 || findStation(station.getId()) >= 0) return false;
    if (count > 0 && station.getPositionKm() <= stations[count - 1].getPositionKm()) return false;
    stations[count++] = station;
    return true;
}
bool Route::getStation(int index, Station& result) const {
    if (index < 0 || index >= count) return false;
    result = stations[index];
    return true;
}
int Route::findStation(int stationId) const {
    for (int i = 0; i < count; ++i)
        if (stations[i].getId() == stationId) return i;
    return -1;
}
double Route::journeyDistance(int sourceId, int destinationId) const {
    int source = findStation(sourceId);
    int destination = findStation(destinationId);
    if (source < 0 || destination < 0 || source == destination) return -1;
    return fabs(stations[source].getPositionKm() - stations[destination].getPositionKm());
}
int Route::stationsTravelled(int sourceId, int destinationId) const {
    int source = findStation(sourceId);
    int destination = findStation(destinationId);
    if (source < 0 || destination < 0 || source == destination) return -1;
    return source > destination ? source - destination : destination - source;
}
ostream& operator<<(ostream& output, const Route& route) {
    output << route.getName() << " (both directions)\n";
    for (int i = 0; i < route.getCount(); ++i) {
        Station station;
        route.getStation(i, station);
        output << station;
        if (i + 1 < route.getCount()) output << " -> ";
    }
    return output << '\n';
}
