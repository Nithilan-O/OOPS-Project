#include "MetroService.h"
#include <limits>

using namespace std;

MetroService::MetroService()
    : route("Metro Line", 3), regular(101, 300), ticketCount(0), nextTicketId(1001)
{
	route.addStation(Station(1, "A", 0));
	route.addStation(Station(2, "B", 5));
	route.addStation(Station(3, "C", 10));
}

bool MetroService::readNumber(const string& prompt, int& value) const
{
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

void MetroService::displayStations() const
{
	for (int i = 0; i < route.getCount(); ++i) {
		Station station;
		route.getStation(i, station);
		cout << station << '\n';
	}
}

void MetroService::displayMetros() const
{
	cout << "1. " << regular << "Stops: A; B; C\n";
}

void MetroService::bookTicket()
{
	if (ticketCount == 100) {
		cout << "Ticket storage is full.\n";
		return;
	}
	displayStations();
	int sourceId, destinationId;
	if (!readNumber("Source station ID (1-3): ", sourceId) ||
		!readNumber("Destination station ID (1-3): ", destinationId)) return;
	double distance = route.journeyDistance(sourceId, destinationId);
	if (distance < 0) {
		cout << "Choose two valid, distinct stations.\n";
		return;
	}
	if (!regular.canServe(route, sourceId, destinationId)) {
		cout << "This service cannot serve that journey.\n";
		return;
	}
	cout << "Journey: " << distance << " km, "
		<< route.stationsTravelled(sourceId, destinationId) << " station intervals.\n"
		<< "Fare: INR " << regular.calculateFare(distance) << "\nPassenger name: ";
	string passenger;
	if (!getline(cin, passenger)) return;
	Station from, to;
	route.getStation(route.findStation(sourceId), from);
	route.getStation(route.findStation(destinationId), to);
	Ticket ticket(nextTicketId, passenger, from, to, regular,
		route.stationsTravelled(sourceId, destinationId));
	if (!ticket.isValid()) {
		cout << "Passenger name must not be blank.\n";
		return;
	}
	tickets[ticketCount++] = ticket;
	++nextTicketId;
	cout << "Ticket generated.\n" << ticket;
}

int MetroService::findTicket(int id) const
{
	for (int i = 0; i < ticketCount; ++i) {
		if (tickets[i].getId() == id) return i;
	}
	return -1;
}

void MetroService::displayTicket() const
{
	if (ticketCount == 0) {
		cout << "No tickets booked.\n";
		return;
	}
	cout << "Stored tickets:\n";
	for (int i = 0; i < ticketCount; ++i) cout << tickets[i];
}

void MetroService::compareTickets() const
{
	int firstId, secondId;
	if (ticketCount == 0) {
		cout << "No tickets booked.\n";
		return;
	}
	if (!readNumber("First ticket ID: ", firstId) ||
		!readNumber("Second ticket ID: ", secondId)) return;
	int first = findTicket(firstId), second = findTicket(secondId);
	if (first < 0 || second < 0) {
		cout << "Ticket ID not found.\n";
		return;
	}
	if (tickets[first] == tickets[second]) cout << "These refer to the same ticket.\n";
	else if (tickets[first] < tickets[second]) cout << "First ticket has the lower fare.\n";
	else if (tickets[second] < tickets[first]) cout << "Second ticket has the lower fare.\n";
	else cout << "Different tickets have equal fares.\n";
}

void MetroService::run()
{
	cout << "Welcome to Metro Rail Service\n";
	while (true) {
		cout << "\n1. Stations\n2. Metro line\n3. Metro service\n4. Book ticket\n"
			"5. Display tickets\n6. Compare tickets\n0. Exit\n";
		int choice;
		if (!readNumber("Choice: ", choice)) {
			if (cin.eof()) break;
			continue;
		}
		if (choice == 0) break;
		if (choice == 1) displayStations();
		else if (choice == 2) cout << route;
		else if (choice == 3) displayMetros();
		else if (choice == 4) bookTicket();
		else if (choice == 5) displayTicket();
		else if (choice == 6) compareTickets();
		else cout << "Invalid menu selection.\n";
		if (cin.eof()) break;
	}
	cout << "Goodbye.\n";
}
