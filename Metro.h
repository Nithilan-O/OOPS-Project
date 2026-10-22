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
    int get_train_number() const;
    int get_capacity() const;
    bool is_operating() const;
    bool set_train_number(int number);
    bool set_capacity(int passengerCapacity);
    void set_operating(bool status);
    string get_type() const;
    string get_features() const;
    double calculate_fare(double distance) const;
    bool stops_at(int index, int stationCount) const;
    bool can_serve(const Route& route, int sourceId, int destinationId) const;
};

ostream& operator<<(ostream& output, const Metro& metro);

#endif
