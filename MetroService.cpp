#include "MetroService.h"
#include <limits>

using namespace std;

MetroService::MetroService() : route("Blue Line", 7), regular(101, 300, 1),
    express(201, 220, 2), airport(301, 180, 3), ticketCount(0), nextTicketId(1001) {
    route.addStation(Station(1, "Willow Square", 0));
    route.addStation(Station(2, "Museum Gardens", 2));
    route.addStation(Station(3, "Civic Centre", 5));
    route.addStation(Station(4, "Riverside Park", 8));
    route.addStation(Station(5, "Eastgate Interchange", 12));
    route.addStation(Station(6, "Skyview Estate", 17));
    route.addStation(Station(7, "Silverwing Airport", 24));
}
bool MetroService::readNumber(const string& prompt, int& value) const {
    cout << prompt;
    if (!(cin >> value)) {
        if (!cin.eof()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter a whole number.\n";
        }
        return false;
    }
    string remainder;
    getline(cin, remainder);
    if (remainder.find_first_not_of(" \t\r") != string::npos) {
        cout << "Enter one whole number only.\n";
        return false;
    }
    return true;
}
const Metro* MetroService::selectMetro(int choice) const {
    if (choice == 1) return &regular;
    if (choice == 2) return &express;
    if (choice == 3) return &airport;
    return 0;
}
void MetroService::displayStations() const {
    for (int i = 0; i < route.getCount(); ++i) {
        Station station;
        route.getStation(i, station);
        cout << station << '\n';
    }
}
void MetroService::displayMetros() const {
    for (int choice = 1; choice <= 3; ++choice) {
        const Metro* metro = selectMetro(choice);
        cout << choice << ". " << *metro << "Stops: ";
        for (int i = 0; i < route.getCount(); ++i) {
            if (metro->stopsAt(i, route.getCount())) {
                Station station;
                route.getStation(i, station);
                cout << station.getName() << "; ";
            }
        }
        cout << '\n';
    }
}
void MetroService::bookTicket() {
    if (ticketCount == 100) { cout << "Ticket storage is full.\n"; return; }
    displayStations();
    int sourceId, destinationId, metroChoice;
    if (!readNumber("Source station ID: ", sourceId) ||
        !readNumber("Destination station ID: ", destinationId)) return;
    double distance = route.journeyDistance(sourceId, destinationId);
    if (distance < 0) { cout << "Choose two valid, distinct stations.\n"; return; }
    displayMetros();
    if (!readNumber("Metro type (1-3): ", metroChoice)) return;
    const Metro* metro = selectMetro(metroChoice);
    if (!metro) { cout << "Invalid metro type.\n"; return; }
    if (!metro->canServe(route, sourceId, destinationId)) {
        cout << "This service does not stop at both stations or is out of service.\n";
        return;
    }
    cout << "Journey: " << distance << " km, "
        << route.stationsTravelled(sourceId, destinationId) << " station intervals.\n"
        << "Fare: INR " << metro->calculateFare(distance) << "\nPassenger name: ";
    string passenger;
    if (!getline(cin, passenger)) return;
    Station from, to;
    route.getStation(route.findStation(sourceId), from);
    route.getStation(route.findStation(destinationId), to);
    Ticket ticket(nextTicketId, passenger, from, to, *metro,
                  route.stationsTravelled(sourceId, destinationId));
    if (!ticket.isValid()) { cout << "Passenger name must not be blank.\n"; return; }
    tickets[ticketCount++] = ticket;
    ++nextTicketId;
    cout << "Ticket generated.\n" << ticket;
}
int MetroService::findTicket(int id) const {
    for (int i = 0; i < ticketCount; ++i) if (tickets[i].getId() == id) return i;
    return -1;
}
void MetroService::displayTicket() const {
    if (ticketCount == 0) { cout << "No tickets booked.\n"; return; }
    cout << "Stored tickets:\n";
    for (int i = 0; i < ticketCount; ++i) cout << tickets[i];
}
void MetroService::compareTickets() const {
    int firstId, secondId;
    if (ticketCount == 0) { cout << "No tickets booked.\n"; return; }
    if (!readNumber("First ticket ID: ", firstId) ||
        !readNumber("Second ticket ID: ", secondId)) return;
    int first = findTicket(firstId), second = findTicket(secondId);
    if (first < 0 || second < 0) { cout << "Ticket ID not found.\n"; return; }
    if (tickets[first] == tickets[second]) cout << "These refer to the same ticket.\n";
    else if (tickets[first] < tickets[second]) cout << "First ticket has the lower fare.\n";
    else if (tickets[second] < tickets[first]) cout << "Second ticket has the lower fare.\n";
    else cout << "Different tickets have equal fares.\n";
}
void MetroService::run() {
    cout << "Welcome to Metro Rail Service\n";
    while (true) {
        cout << "\n1. Stations\n2. Routes\n3. Trains\n4. Book ticket\n"
                     "5. Display tickets\n6. Compare tickets\n7. Service information\n0. Exit\n";
        int choice;
        if (!readNumber("Choice: ", choice)) {
            if (cin.eof()) break;
            continue;
        }
        if (choice == 0) break;
        if (choice == 1) displayStations();
        else if (choice == 2) cout << route;
        else if (choice == 3 || choice == 7) displayMetros();
        else if (choice == 4) bookTicket();
        else if (choice == 5) displayTicket();
        else if (choice == 6) compareTickets();
        else cout << "Invalid menu selection.\n";
        if (cin.eof()) break;
    }
    cout << "Goodbye.\n";
}
