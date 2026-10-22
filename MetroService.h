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
        bool readNumber(const string& prompt, int& value) const;
        void displayStations() const;
        void displayMetros() const;
        void bookTicket();
        void displayTicket() const;
        void compareTickets() const;
        int findTicket(int id) const;
    public:
        MetroService();
        void run();
};

#endif
