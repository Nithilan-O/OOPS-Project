#include "MetroService.h"
#include <cassert>
#include <cmath>
#include <limits>
#include <sstream>

bool closeTo(double a, double b) { return std::fabs(a - b) < 0.001; }

std::string runSession(const std::string& commands) {
    std::istringstream input(commands);
    std::ostringstream output;
    std::streambuf* previousInput = std::cin.rdbuf(input.rdbuf());
    std::streambuf* previousOutput = std::cout.rdbuf(output.rdbuf());
    std::cin.clear();
    MetroService service;
    service.run();
    std::cin.rdbuf(previousInput);
    std::cout.rdbuf(previousOutput);
    std::cin.clear();
    return output.str();
}

int main() {
    Station empty;
    assert(empty.getId() == 0);
    Station first(1, "Willow Square", 0), middle(2, "Museum Gardens", 2), last(3, "Civic Centre", 5);
    Station copied(first);
    assert(copied.getName() == "Willow Square");
    assert(!copied.setId(-1) && !copied.setName("  ") && !copied.setPositionKm(-1));
    assert(!copied.setPositionKm(std::numeric_limits<double>::infinity()));
    assert(!copied.setPositionKm(std::numeric_limits<double>::quiet_NaN()));
    std::istringstream stationInput("4 8 Riverside Park\n");
    stationInput >> copied;
    assert(copied.getId() == 4 && copied.getName() == "Riverside Park");
    std::istringstream badInput("-1 -3 Invalid\n");
    badInput >> copied;
    assert(badInput.fail() && copied.getId() == 4);
    std::istringstream malformedInput("abc\n");
    malformedInput >> copied;
    assert(malformedInput.fail() && copied.getId() == 4);
    std::ostringstream stationOutput;
    stationOutput << first;
    assert(stationOutput.str().find("Willow Square") != std::string::npos);

    Route defaultRoute;
    assert(defaultRoute.getCount() == 0);
    Route route("Test line", 4);
    assert(route.addStation(first) && route.addStation(middle) && route.addStation(last));
    assert(!route.addStation(first));
    assert(!route.addStation(Station(4, "Wrong order", 1)));
    assert(!route.addStation(empty));
    assert(closeTo(route.journeyDistance(1, 3), 5));
    assert(closeTo(route.journeyDistance(3, 1), 5));
    assert(route.stationsTravelled(3, 1) == 2);
    assert(route.journeyDistance(1, 1) == -1 && route.journeyDistance(1, 99) == -1);
    assert(route.stationsTravelled(99, 1) == -1);
    assert(!route.getStation(-1, copied) && !route.getStation(3, copied));
    Route deepCopy(route);
    Route assigned;
    assigned = route;
    Route* sameRoute = &assigned;
    assigned = *sameRoute;
    assert(route.addStation(Station(4, "Riverside Park", 8)));
    assert(!route.addStation(Station(5, "Overflow", 12)));
    assert(deepCopy.getCount() == 3 && assigned.getCount() == 3);
    assert(deepCopy.addStation(Station(5, "Independent copy", 9)));
    assert(assigned.addStation(Station(6, "Independent assignment", 10)));
    assert(route.findStation(5) == -1 && route.findStation(6) == -1);
    assert(deepCopy.findStation(6) == -1 && assigned.findStation(5) == -1);
    {
        Route temporary("Temporary", 2);
        temporary.addStation(Station(8, "Survives owner", 0));
        assigned = temporary;
    }
    assert(assigned.getStation(0, copied) && copied.getId() == 8);
    Route fallback("", -1);
    assert(fallback.addStation(first));
    std::ostringstream routeOutput;
    routeOutput << route;
    assert(routeOutput.str().find("Test line") != std::string::npos);

    Metro base;
    Metro configured(55, 123);
    assert(base.getCapacity() == 200 && configured.getTrainNumber() == 55);
    assert(!configured.setTrainNumber(0) && !configured.setCapacity(-1));
    RegularMetro regular;
    ExpressMetro express;
    AirportMetro airport;
    const Metro* trains[3] = { &regular, &express, &airport };
    const double expected[3] = { 58, 87, 146 };
    for (int i = 0; i < 3; ++i) {
        assert(closeTo(trains[i]->calculateFare(24), expected[i]));
        assert(trains[i]->calculateFare(0) == -1 && trains[i]->calculateFare(-2) == -1);
        assert(trains[i]->calculateFare(std::numeric_limits<double>::infinity()) == -1);
        assert(!trains[i]->stopsAt(-1, 7) && !trains[i]->stopsAt(7, 7));
        std::ostringstream trainOutput;
        trainOutput << *trains[i];
        assert(trainOutput.str().find(trains[i]->getType()) != std::string::npos);
    }
    assert(regular.canServe(route, 1, 2));
    assert(!express.canServe(route, 1, 2) && express.canServe(route, 1, 3));
    assert(airport.stopsAt(0, 7) && airport.stopsAt(4, 7) && airport.stopsAt(6, 7));
    assert(!airport.stopsAt(2, 7));
    regular.setOperating(false);
    assert(!regular.canServe(route, 1, 3));
    regular.setOperating(true);
    Ticket unissued;
    assert(!unissued.isValid());
    Ticket ticket(1001, "Asha Rao", first, last, regular, 2);
    Ticket ticketCopy(ticket), ticketAssigned;
    ticketAssigned = ticket;
    assert(ticket.isValid() && ticketCopy == ticket && ticketAssigned == ticket);
    Ticket premium(1002, "Ben", first, last, express, 2);
    assert(ticket < premium && !(ticket == premium));
    assert(!Ticket(1, " ", first, last, regular, 2).isValid());
    assert(!Ticket(1, "A", first, first, regular, 0).isValid());
    std::ostringstream ticketOutput;
    ticketOutput.precision(4);
    ticketOutput << ticket;
    assert(ticketOutput.precision() == 4);
    assert(ticketOutput.str().find("Fare: INR 20.00") != std::string::npos);

    std::string navigation = runSession("1\n2\n3\n5\n6\n7\nx\n999\n2oops\n0\n");
    assert(navigation.find("Blue Line") != std::string::npos);
    assert(navigation.find("Enter a whole number") != std::string::npos);
    assert(navigation.find("Invalid menu selection") != std::string::npos);
    assert(navigation.find("Enter one whole number only") != std::string::npos);
    assert(navigation.find("Goodbye.") != std::string::npos);
    std::string booking = runSession("4\n1\n7\n1\nAsha Rao\n4\n7\n1\n2\nBen Lee\n4\n1\n7\n3\nCara Ray\n5\n6\n1001\n1002\n6\n1001\n1001\n6\n9999\n1001\n0\n");
    assert(booking.find("Ticket ID: 1003") != std::string::npos);
    assert(booking.find("Fare: INR 58.00") != std::string::npos);
    assert(booking.find("Fare: INR 87.00") != std::string::npos);
    assert(booking.find("Fare: INR 146.00") != std::string::npos);
    assert(booking.find("First ticket has the lower fare") != std::string::npos);
    assert(booking.find("same ticket") != std::string::npos);
    assert(booking.find("Ticket ID not found") != std::string::npos);
    std::string invalid = runSession("4\n1\n1\n4\n99\n1\n4\n1\n2\n2\n4\n1\n7\n9\n4\n1\n7\n1\n   \n0\n");
    assert(invalid.find("valid, distinct") != std::string::npos);
    assert(invalid.find("does not stop") != std::string::npos);
    assert(invalid.find("Invalid metro type") != std::string::npos);
    assert(invalid.find("must not be blank") != std::string::npos);
    assert(invalid.find("Ticket generated") == std::string::npos);
    std::string comparison = runSession("4\n1\n7\n2\nBen\n4\n1\n7\n1\nAsha\n4\n7\n1\n1\nCara\n6\n1001\n1002\n6\n1002\n1003\n0\n");
    assert(comparison.find("Second ticket has the lower fare") != std::string::npos);
    assert(comparison.find("Different tickets have equal fares") != std::string::npos);
    std::string failedThenSuccess = runSession("4\n1\n7\n1\n   \n4\n1\n7\n1\nAsha\n0\n");
    assert(failedThenSuccess.find("Ticket ID: 1001") != std::string::npos);
    assert(failedThenSuccess.find("Ticket ID: 1002") == std::string::npos);
    assert(runSession("").find("Goodbye.") != std::string::npos);
    assert(runSession("4\n1\n").find("Goodbye.") != std::string::npos);
    assert(runSession("4\n1\n7\n1\n").find("Ticket generated") == std::string::npos);
    std::string manyBookings;
    for (int i = 0; i < 101; ++i) manyBookings += "4\n1\n7\n1\nPassenger\n";
    manyBookings += "0\n";
    std::string full = runSession(manyBookings);
    assert(full.find("Ticket ID: 1100") != std::string::npos);
    assert(full.find("Ticket ID: 1101") == std::string::npos);
    assert(full.find("Ticket storage is full") != std::string::npos);
    std::cout << "All metro tests passed.\n";
    return 0;
}
