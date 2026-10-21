#ifndef METRO_H
#define METRO_H

#include "Route.h"

class Metro {
private:
    int trainNumber;
    int capacity;
    bool operating;
public:
    Metro();
    Metro(int number, int passengerCapacity);
    virtual ~Metro();
    int getTrainNumber() const;
    int getCapacity() const;
    bool isOperating() const;
    bool setTrainNumber(int number);
    bool setCapacity(int passengerCapacity);
    void setOperating(bool status);
    virtual std::string getType() const;
    virtual std::string getFeatures() const;
    virtual double calculateFare(double distance) const;
    virtual bool stopsAt(int index, int stationCount) const;
    bool canServe(const Route& route, int sourceId, int destinationId) const;
};

class RegularMetro : public Metro {
public:
    RegularMetro();
    std::string getType() const;
    std::string getFeatures() const;
};

class ExpressMetro : public Metro {
public:
    ExpressMetro();
    std::string getType() const;
    std::string getFeatures() const;
    double calculateFare(double distance) const;
    bool stopsAt(int index, int stationCount) const;
};

class AirportMetro : public Metro {
public:
    AirportMetro();
    std::string getType() const;
    std::string getFeatures() const;
    double calculateFare(double distance) const;
    bool stopsAt(int index, int stationCount) const;
};

std::ostream& operator<<(std::ostream& output, const Metro& metro);

#endif
