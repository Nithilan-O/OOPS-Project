#ifndef METROSERVICE_H
#define METROSERVICE_H
#include "Ticket.h"
#include "Metro.h"
using namespace std;
class MetroService
{
	private:
		Route route;
		Metro regular;
		Ticket tickets[100];
		int ticket_count;
		int next_ticket_id;
		void read_no(const string& prompt,int& value) const;
		void display_stations() const;
		void display_metros() const;
		void book_ticket();
		void display_ticket() const;
	public:
		MetroService();
		void run_service();
};
#endif
