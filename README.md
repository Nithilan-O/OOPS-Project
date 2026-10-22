# Metro Rail Service

A beginner C++11 console project with a fictional seven-station Blue Line, three train types, and in-memory ticket booking. The application uses standard C++ only, has no source-code comments, and needs no database or external runtime library.

## Files

```text
Metro/
  Station.h          Station.cpp
  Route.h            Route.cpp
  Metro.h            Metro.cpp
  Ticket.h           Ticket.cpp
  MetroService.h     MetroService.cpp
  main.cpp
  README.md
  VERIFICATION.md
```

## Compile and run with GCC

From the project folder:

```sh
g++ -std=c++11 -Wall -Wextra -Wpedantic Station.cpp Route.cpp Metro.cpp Ticket.cpp MetroService.cpp main.cpp -o metro.exe
```

On Windows PowerShell, run `./metro.exe`. On Linux or macOS, use the same command with `-o metro`, then run `./metro`.

Run `./metro.exe` to start the application.

## Using the app

The menu displays stations, the route, trains, booking, stored tickets, comparison, service information, and exit. Select `4`, enter source and destination IDs, select a train type, and enter the passenger's full name. A completed booking immediately prints its ticket. Select `5` to display every issued ticket and `6` to compare two IDs. Select `0` to exit. End-of-input also exits cleanly.

| ID | Station | Position from start |
| --- | --- | --- |
| 1 | Willow Square | 0 km |
| 2 | Museum Gardens | 2 km |
| 3 | Civic Centre | 5 km |
| 4 | Riverside Park | 8 km |
| 5 | Eastgate Interchange | 12 km |
| 6 | Skyview Estate | 17 km |
| 7 | Silverwing Airport | 24 km |

The route supports travel in both directions. Distance is the absolute difference between station positions. Station intervals count adjacent route segments crossed, including stations that an express train passes without stopping.

| Train | Stops (station IDs) | Fare in INR |
| --- | --- | --- |
| Regular, 101 | All | 10 + 2 × distance in km |
| Express, 201 | 1, 3, 5, 7 | 1.5 × regular fare |
| Airport, 301 | 1, 5, 7 | 2 × regular fare + 30 |

Airport service permits journeys between any two of its stops, including Willow Square to Eastgate Interchange. Both ends must be stops of the chosen train. Fares are rounded to two decimal places; tickets display both decimal places.

## Classes and relationships

| Class | Responsibility |
| --- | --- |
| `Station` | Holds a positive ID, a nonblank name, and a finite, nonnegative position in km. Setters reject invalid changes. The default ID of zero represents an unassigned station. |
| `Route` | Owns an ordered dynamic array of stations. Rejects duplicate IDs, non-increasing positions, and additions beyond capacity. Looks up stations and calculates journey distance and intervals. |
| `Metro` | Holds train number, informational passenger capacity, operating status, and service type. Fare, stopping, and display behavior use the configured service type. |
| `Ticket` | Stores a passenger name and independent copies of the source, destination, service type, distance, intervals, and quoted fare. Default construction represents an unissued ticket. |
| `MetroService` | Composes the sample route, three train objects, and an ordinary array of up to 100 tickets. Handles the menu and coordinates booking validation. |

## OOP mapping

| Requirement | Implementation |
| --- | --- |
| Encapsulation | All data members are private. Validated station/train setters and route insertion protect state. Route access returns a station copy instead of exposing its array. Ticket data is read-only after construction. |
| Composition | Route owns stations; Ticket contains journey stations; MetroService contains route, trains, and tickets. A separate passenger class is unnecessary for a single name. |
| Train services | Regular, Express, and Airport trains are ordinary `Metro` objects configured with a service type. There is no inheritance or runtime polymorphism. |
| Abstraction | Callers use `journeyDistance`, `canServe`, `calculateFare`, and the booking operation without manipulating route storage or fare formulas. No abstract base class is needed. |
| Constructors | Station, Route, and Metro provide default and parameterized constructors. Ticket has default and parameterized construction. Route explicitly implements a deep-copy constructor; value-only classes use compiler-generated copy constructors. |
| Destructors | Route deletes its station array. Other classes need only automatic value-member destruction. |
| Dynamic memory | Only Route directly owns dynamically allocated memory, using matched `new[]` and `delete[]`. |
| Assignment | Route's assignment allocates and copies replacement storage, releases old storage, and handles self-assignment. Value-only classes safely use ordinary member-wise assignment. |
| Stream output | Free `operator<<` functions output Station, Route, Metro, and Ticket through `ostream&`. |
| Stream input | `operator>>(istream&, Station&)` reads ID, position, then the rest of the line as the station name. A candidate object prevents partially changing the target on invalid input. Failure sets the standard stream failure state. |
| Comparison | Ticket `==` checks issued-ticket identity by ID. Ticket `<` compares fare. Different IDs may have the same fare. |

Example station input for `>>`: `8 28 North Terminal`. The supplied network is predefined, so the booking menu reads station IDs rather than creating new stations. Ordinary interactive input/output uses `cin` and `cout`.

## Design decisions and limits

- All network data lives in the MetroService constructor. Change station positions/names there; adjust its route capacity when adding more stations. Fare formulas and stopping rules live in Metro.cpp. Airport index 4 is a deliberately simple interchange rule and must be updated if the route ordering changes.
- One linear route keeps distance calculation explainable. Transfers, branching networks, scheduling, payments, cancellations, seat reservations, and persistence are outside this project.
- Capacity describes a train; it does not model occupancy. Tickets do not reserve seats or departures.
- Tickets persist only while this app runs. At most 100 can be stored. IDs start at 1001 for each service session and increase only after successful booking. Ticket identity comparisons assume tickets belong to the same session.
- MetroService validates the complete route and stopping pattern before constructing a ticket. Ticket's public constructor validates basic journey fields but does not receive a Route and cannot independently check its stop membership.
- Numeric menu input accepts exactly one integer per line. Invalid text, fractional values, extra tokens, and out-of-range integer input are rejected. A failed booking returns to the main menu.
- Standard strings own their own text storage. Raw dynamic allocation is limited to the Route array to keep ownership easy to explain.
- There are no enums, unions, exception handlers, custom templates, STL containers as core storage, smart pointers, lambdas, or global application state. Strings and standard stream interfaces are used as required.
- Ordinary allocation failure is left to the C++ runtime; the project intentionally adds no exception handling.

See VERIFICATION.md for the actual compiler and checks used on this machine.
