#ifndef METRO_H
#define METRO_H

#include "Route.h"

using namespace std;

class Metro {
private:
    int trainNumber;
    int capacity;
    bool operating;
public:
    Metro();
    Metro(int number, int passengerCapacity);
    int getTrainNumber() const;
    int getCapacity() const;
    bool isOperating() const;
    bool setTrainNumber(int number);
    bool setCapacity(int passengerCapacity);
    void setOperating(bool status);
    string getType() const;
    string getFeatures() const;
    double calculateFare(double distance) const;
    bool stopsAt(int index, int stationCount) const;
    bool canServe(const Route& route, int sourceId, int destinationId) const;
};

ostream& operator<<(ostream& output, const Metro& metro);

#endif
