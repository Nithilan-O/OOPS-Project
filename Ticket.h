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
		double distance;
		double fare;
		int station_intervals;
	public:
		Ticket();
		Ticket(int ticket_id,const string& passenger,const Station& from,
			const Station& to,double journey_distance,double ticket_fare,int intervals);
		int get_id() const;
		friend ostream& operator<<(ostream& output,const Ticket& ticket);
};
ostream& operator<<(ostream& output,const Ticket& ticket);
#endif
