#include "Ticket.h"
#include <cmath>
#include <iomanip>

using namespace std;

Ticket::Ticket()
    : id(0), passengerName("Unassigned"), metroType("Unassigned"),
      distance(0), fare(0), stationIntervals(0)
{
}

Ticket::Ticket(int ticketId, const string& passenger, const Station& from,
               const Station& to, const Metro& metro, int intervals) : Ticket()
{
	double journey = fabs(from.get_position_km() - to.get_position_km());
	if (ticketId <= 0 || passenger.find_first_not_of(" \t\r\n") == string::npos ||
		from.get_id() <= 0 || to.get_id() <= 0 || from.get_id() == to.get_id() ||
		journey <= 0 || intervals <= 0 || !metro.is_operating()) return;
	id = ticketId;
	passengerName = passenger;
	source = from;
	destination = to;
	metroType = metro.get_type();
	distance = journey;
	fare = metro.calculate_fare(distance);
	stationIntervals = intervals;
}

int Ticket::get_id() const
{
	return id;
}

double Ticket::get_fare() const
{
	return fare;
}

bool Ticket::is_valid() const
{
	return id > 0;
}

bool Ticket::operator==(const Ticket& other) const
{
	return is_valid() && other.is_valid() && id == other.id;
}

bool Ticket::operator<(const Ticket& other) const
{
	return fare < other.fare;
}

void Ticket::display_ticket(ostream& output) const
{
	if (!is_valid()) {
		output << "No ticket issued.\n";
		return;
	}
	ios::fmtflags previousFlags = output.flags();
	streamsize previousPrecision = output.precision();
	output << fixed << setprecision(2)
		<< "Ticket ID: " << id << "\nPassenger: " << passengerName
		<< "\nFrom: " << source.get_name() << "\nTo: " << destination.get_name()
		<< "\nMetro type: " << metroType << "\nDistance: " << distance
		<< " km\nStation intervals: " << stationIntervals << "\nFare: INR " << fare << '\n';
	output.flags(previousFlags);
	output.precision(previousPrecision);
}

ostream& operator<<(ostream& output, const Ticket& ticket)
{
	ticket.display_ticket(output);
	return output;
}
