#ifndef METROSERVICE_H
#define METROSERVICE_H

#include "Ticket.h"

using namespace std;

class MetroService {
    private:
        Route route;
        Metro regular;
        Ticket tickets[100];
        int ticketCount;
        int nextTicketId;
        bool read_number(const string& prompt, int& value) const;
        void display_stations() const;
        void display_metros() const;
        void book_ticket();
        void display_ticket() const;
        void compare_tickets() const;
        int find_ticket(int id) const;
    public:
        MetroService();
        void run_service();
};

#endif
