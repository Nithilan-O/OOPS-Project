#include "MetroService.h"
#include <limits>

using namespace std;

MetroService::MetroService()
    : route("Metro Line", 3), regular(101, 300), ticketCount(0), nextTicketId(1001)
{
	route.add_station(Station(1, "A", 0));
	route.add_station(Station(2, "B", 5));
	route.add_station(Station(3, "C", 10));
}

bool MetroService::read_number(const string& prompt, int& value) const
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

void MetroService::display_stations() const
{
	for (int i = 0; i < route.get_count(); ++i) {
		Station station;
		route.get_station(i, station);
		cout << station << '\n';
	}
}

void MetroService::display_metros() const
{
	cout << "1. " << regular << "Stops: A; B; C\n";
}

void MetroService::book_ticket()
{
	if (ticketCount == 100) {
		cout << "Ticket storage is full.\n";
		return;
	}
	display_stations();
	int sourceId, destinationId;
	if (!read_number("Source station ID (1-3): ", sourceId) ||
		!read_number("Destination station ID (1-3): ", destinationId)) return;
	double distance = route.journey_distance(sourceId, destinationId);
	if (distance < 0) {
		cout << "Choose two valid, distinct stations.\n";
		return;
	}
	if (!regular.can_serve(route, sourceId, destinationId)) {
		cout << "This service cannot serve that journey.\n";
		return;
	}
	cout << "Journey: " << distance << " km, "
		<< route.stations_travelled(sourceId, destinationId) << " station intervals.\n"
		<< "Fare: INR " << regular.calculate_fare(distance) << "\nPassenger name: ";
	string passenger;
	if (!getline(cin, passenger)) return;
	Station from, to;
	route.get_station(route.find_station(sourceId), from);
	route.get_station(route.find_station(destinationId), to);
	Ticket ticket(nextTicketId, passenger, from, to, regular,
		route.stations_travelled(sourceId, destinationId));
	if (!ticket.is_valid()) {
		cout << "Passenger name must not be blank.\n";
		return;
	}
	tickets[ticketCount++] = ticket;
	++nextTicketId;
	cout << "Ticket generated.\n" << ticket;
}

int MetroService::find_ticket(int id) const
{
	for (int i = 0; i < ticketCount; ++i) {
		if (tickets[i].get_id() == id) return i;
	}
	return -1;
}

void MetroService::display_ticket() const
{
	if (ticketCount == 0) {
		cout << "No tickets booked.\n";
		return;
	}
	cout << "Stored tickets:\n";
	for (int i = 0; i < ticketCount; ++i) cout << tickets[i];
}

void MetroService::compare_tickets() const
{
	int firstId, secondId;
	if (ticketCount == 0) {
		cout << "No tickets booked.\n";
		return;
	}
	if (!read_number("First ticket ID: ", firstId) ||
		!read_number("Second ticket ID: ", secondId)) return;
	int first = find_ticket(firstId), second = find_ticket(secondId);
	if (first < 0 || second < 0) {
		cout << "Ticket ID not found.\n";
		return;
	}
	if (tickets[first] == tickets[second]) cout << "These refer to the same ticket.\n";
	else if (tickets[first] < tickets[second]) cout << "First ticket has the lower fare.\n";
	else if (tickets[second] < tickets[first]) cout << "Second ticket has the lower fare.\n";
	else cout << "Different tickets have equal fares.\n";
}

void MetroService::run_service()
{
	cout << "Welcome to Metro Rail Service\n";
	while (true) {
		cout << "\n1. Stations\n2. Metro line\n3. Metro service\n4. Book ticket\n"
			"5. Display tickets\n6. Compare tickets\n0. Exit\n";
		int choice;
		if (!read_number("Choice: ", choice)) {
			if (cin.eof()) break;
			continue;
		}
		if (choice == 0) break;
		if (choice == 1) display_stations();
		else if (choice == 2) cout << route;
		else if (choice == 3) display_metros();
		else if (choice == 4) book_ticket();
		else if (choice == 5) display_ticket();
		else if (choice == 6) compare_tickets();
		else cout << "Invalid menu selection.\n";
		if (cin.eof()) break;
	}
	cout << "Goodbye.\n";
}
