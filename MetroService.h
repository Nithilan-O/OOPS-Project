#ifndef METROSERVICE_H
#define METROSERVICE_H

#include "Ticket.h"

using namespace std;

class MetroService {
    private:
        Route route;
        Metro regular;
        Metro express;
        Metro airport;
        Ticket tickets[100];
        int ticketCount;
        int nextTicketId;
        bool readNumber(const string& prompt, int& value) const;
        const Metro* selectMetro(int choice) const;
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
