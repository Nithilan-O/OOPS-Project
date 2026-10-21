#ifndef TICKET_H
#define TICKET_H

#include "Metro.h"

class Ticket {
private:
    int id;
    std::string passengerName;
    Station source;
    Station destination;
    std::string metroType;
    double distance;
    double fare;
    int stationIntervals;
public:
    Ticket();
    Ticket(int ticketId, const std::string& passenger, const Station& from,
           const Station& to, const Metro& metro, int intervals);
    int getId() const;
    double getFare() const;
    bool isValid() const;
    bool operator==(const Ticket& other) const;
    bool operator<(const Ticket& other) const;
    void display(std::ostream& output) const;
};

std::ostream& operator<<(std::ostream& output, const Ticket& ticket);

#endif
