#ifndef METROSERVICE_H
#define METROSERVICE_H
#include "Ticket.h"
#include "Regular.h"
using namespace std;
class MetroService
{
	private:
		static const int station_capacity=25;
		static const int line_count=3;
		Station stations[station_capacity];
		Route routes[line_count];
		Regular regular;
		Ticket tickets[100];
		int ticket_count;
		int next_ticket_id;
		bool read_no(const string& prompt,int& value) const;
		void display_stations() const;
		void display_routes() const;
		void display_metros() const;
		int find_station_index(int station_id) const;
		bool determine_route(int source_id,int destination_id,string& route_details,
			int& extra_stops) const;
		void book_ticket();
		void display_ticket() const;
	public:
		MetroService();
		void run_service();
};
#endif
