#include "Ticket.h"
#include <iostream>
using namespace std;
Ticket::Ticket()
: id(0),passenger_name("Unassigned"),distance(0),fare(0),station_intervals(0)
{
}
Ticket::Ticket(int ticket_id,const string& passenger,const Station& from,
const Station& to,double journey_distance,double ticket_fare,int intervals):Ticket()
{
	id=ticket_id;
	passenger_name=passenger;
	source=from;
	destination=to;
	distance=journey_distance;
	fare=ticket_fare;
	station_intervals=intervals;
}
int Ticket::get_id() const
{
	return id;
}
ostream& operator<<(ostream& output,const Ticket& ticket)
{
	output<<"Ticket ID: "<<ticket.id<<endl<<"Passenger: "<<ticket.passenger_name<<endl<<"From: "<<ticket.source.get_name()<<endl<<"To: "<<ticket.destination.get_name()<<endl<<"Distance: "<<ticket.distance<<" km"<<endl<<"Station intervals: "<<ticket.station_intervals<<endl<<"Fare: INR "<<ticket.fare<<endl;
	return output;
}
