#include "Ticket.h"
#include <cmath>
#include <iomanip>

Ticket::Ticket() : id(0), passengerName("Unassigned"), metroType("Unassigned"),
    distance(0), fare(0), stationIntervals(0) {}
Ticket::Ticket(int ticketId, const std::string& passenger, const Station& from,
               const Station& to, const Metro& metro, int intervals) : Ticket() {
    double journey = std::fabs(from.getPositionKm() - to.getPositionKm());
    if (ticketId <= 0 || passenger.find_first_not_of(" \t\r\n") == std::string::npos ||
        from.getId() <= 0 || to.getId() <= 0 || from.getId() == to.getId() ||
        journey <= 0 || intervals <= 0 || !metro.isOperating()) return;
    id = ticketId;
    passengerName = passenger;
    source = from;
    destination = to;
    metroType = metro.getType();
    distance = journey;
    fare = metro.calculateFare(distance);
    stationIntervals = intervals;
}
int Ticket::getId() const { return id; }
double Ticket::getFare() const { return fare; }
bool Ticket::isValid() const { return id > 0; }
bool Ticket::operator==(const Ticket& other) const { return isValid() && other.isValid() && id == other.id; }
bool Ticket::operator<(const Ticket& other) const { return fare < other.fare; }
void Ticket::display(std::ostream& output) const {
    if (!isValid()) { output << "No ticket issued.\n"; return; }
    std::ios::fmtflags previousFlags = output.flags();
    std::streamsize previousPrecision = output.precision();
    output << std::fixed << std::setprecision(2)
        << "Ticket ID: " << id << "\nPassenger: " << passengerName
        << "\nFrom: " << source.getName() << "\nTo: " << destination.getName()
        << "\nMetro type: " << metroType << "\nDistance: " << distance
        << " km\nStation intervals: " << stationIntervals << "\nFare: INR " << fare << '\n';
    output.flags(previousFlags);
    output.precision(previousPrecision);
}
std::ostream& operator<<(std::ostream& output, const Ticket& ticket) {
    ticket.display(output);
    return output;
}
