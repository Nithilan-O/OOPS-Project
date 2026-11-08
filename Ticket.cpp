#include "Ticket.h"
#include <iostream>
using namespace std;
Ticket::Ticket()
: id(0),passenger_name("Unassigned"),fare(0),route_details("Unassigned"),extra_stops(0),digital(false)
{
}
Ticket::Ticket(int ticket_id,const string& passenger,const Station& from,
const Station& to,double ticket_fare,const string& journey_route,
int stops,bool digital_ticket):Ticket()
{
	id=ticket_id;
	passenger_name=passenger;
	source=from;
	destination=to;
	fare=ticket_fare;
	route_details=journey_route;
	extra_stops=stops;
	digital=digital_ticket;
}
int Ticket::get_id() const
{
	return id;
}
ostream& operator<<(ostream& output,const Ticket& ticket)
{
	output<<"Ticket ID: "<<ticket.id<<endl<<"Passenger: "<<ticket.passenger_name<<endl<<"From: "<<ticket.source.get_name()<<endl<<"To: "<<ticket.destination.get_name()<<endl<<"Route: "<<ticket.route_details<<endl<<"Extra stops: "<<ticket.extra_stops<<endl<<"Ticket type: "<<(ticket.digital?"Eligible digital":"Counter paper")<<endl;
	ios::fmtflags previous_flags=output.flags();
	streamsize previous_precision=output.precision();
	output.setf(ios::fixed,ios::floatfield);
	output.precision(2);
	output<<"Fare: INR "<<ticket.fare<<endl;
	output.flags(previous_flags);
	output.precision(previous_precision);
	return output;
}
