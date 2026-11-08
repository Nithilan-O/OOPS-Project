#ifndef TICKET_H
#define TICKET_H
#include "Station.h"
using namespace std;
class Ticket
{
	private:
		int id;
		string passenger_name;
		Station source;
		Station destination;
		double fare;
		string route_details;
		int extra_stops;
		bool digital;
	public:
		Ticket();
		Ticket(int ticket_id,const string& passenger,const Station& from,
			const Station& to,double ticket_fare,const string& journey_route,
			int stops,bool digital_ticket);
		int get_id() const;
		friend ostream& operator<<(ostream& output,const Ticket& ticket);
};
ostream& operator<<(ostream& output,const Ticket& ticket);
#endif
