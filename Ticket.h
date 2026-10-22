#ifndef TICKET_H
#define TICKET_H

#include "Metro.h"

using namespace std;

class Ticket {
private:
    int id;
    string passengerName;
    Station source;
    Station destination;
    string metroType;
    double distance;
    double fare;
    int stationIntervals;
public:
    Ticket();
    Ticket(int ticketId, const string& passenger, const Station& from,
           const Station& to, const Metro& metro, int intervals);
    int getId() const;
    double getFare() const;
    bool isValid() const;
    bool operator==(const Ticket& other) const;
    bool operator<(const Ticket& other) const;
    void display(ostream& output) const;
};

ostream& operator<<(ostream& output, const Ticket& ticket);

#endif
