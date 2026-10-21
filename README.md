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
  tests/tests.cpp
  README.md
  VERIFICATION.md
  samples/
```

## Compile and run with GCC

From the project folder:

```sh
g++ -std=c++11 -Wall -Wextra -Wpedantic Station.cpp Route.cpp Metro.cpp Ticket.cpp MetroService.cpp main.cpp -o metro.exe
```

On Windows PowerShell, run `./metro.exe`. On Linux or macOS, use the same command with `-o metro`, then run `./metro`.

Build the tests separately because they have their own `main` function:

```sh
g++ -std=c++11 -Wall -Wextra -Wpedantic -I. Station.cpp Route.cpp Metro.cpp Ticket.cpp MetroService.cpp tests/tests.cpp -o metro-tests.exe
```

Run `./metro-tests.exe`. Keep assertions enabled; do not use `-DNDEBUG` for this test executable. No test framework is required.

A local portable Zig 0.13.0 compiler is also stored in `.tools` for verification on this machine. It supplies Clang and the C++ standard library at build time. The application does not depend on Zig. In PowerShell:

```powershell
$env:ZIG_GLOBAL_CACHE_DIR = "$PWD\.tools\cache"
$env:ZIG_LOCAL_CACHE_DIR = "$PWD\.zig-cache"
$compiler = '.\.tools\zig-windows-x86_64-0.13.0\zig.exe'
& $compiler c++ -std=c++11 -Wall -Wextra -Wpedantic Station.cpp Route.cpp Metro.cpp Ticket.cpp MetroService.cpp main.cpp -o build/metro.exe
& $compiler c++ -std=c++11 -Wall -Wextra -Wpedantic -I. Station.cpp Route.cpp Metro.cpp Ticket.cpp MetroService.cpp tests/tests.cpp -o build/metro-tests.exe
./build/metro-tests.exe
./build/metro.exe
```

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
| `Metro` | Holds train number, informational passenger capacity, and operating status. Supplies virtual fare, stop, type, and feature functions, plus a journey eligibility check. |
| `RegularMetro` | Uses the base fare and all-station stopping behavior. |
| `ExpressMetro` | Changes fare and stops at even zero-based indices plus the final station. |
| `AirportMetro` | Changes fare and stops at the first station, index 4, and the final station. |
| `Ticket` | Stores a passenger name and independent copies of the source, destination, service type, distance, intervals, and quoted fare. Default construction represents an unissued ticket. |
| `MetroService` | Composes the sample route, three train objects, and an ordinary array of up to 100 tickets. Handles the menu and coordinates booking validation. |

## OOP mapping

| Requirement | Implementation |
| --- | --- |
| Encapsulation | All data members are private. Validated station/train setters and route insertion protect state. Route access returns a station copy instead of exposing its array. Ticket data is read-only after construction. |
| Composition | Route owns stations; Ticket contains journey stations; MetroService contains route, trains, and tickets. A separate passenger class is unnecessary for a single name. |
| Inheritance | Three service classes publicly derive from Metro using ordinary C++ inheritance. |
| Runtime polymorphism | MetroService selects a non-owning `const Metro*`. Calls to fares, stopping rules, service type, and features dispatch to the actual train class. Train output through `const Metro&` also uses those virtual functions. |
| Abstraction | Callers use `journeyDistance`, `canServe`, `calculateFare`, and the booking operation without manipulating route storage or fare formulas. No abstract base class is needed. |
| Constructors | Station, Route, and Metro provide default and parameterized constructors. Ticket has default and parameterized construction. Route explicitly implements a deep-copy constructor; value-only classes use compiler-generated copy constructors. |
| Destructors | Route deletes its station array. Metro has a virtual destructor for safe destruction through a base pointer. Other classes need only automatic value-member destruction. |
| Dynamic memory | Only Route directly owns dynamically allocated memory, using matched `new[]` and `delete[]`. |
| Assignment | Route's assignment allocates and copies replacement storage, releases old storage, and handles self-assignment. Value-only classes safely use ordinary member-wise assignment. |
| Stream output | Free `operator<<` functions output Station, Route, Metro (including derived services), and Ticket through `std::ostream&`. |
| Stream input | `operator>>(std::istream&, Station&)` reads ID, position, then the rest of the line as the station name. A candidate object prevents partially changing the target on invalid input. Failure sets the standard stream failure state. |
| Comparison | Ticket `==` checks issued-ticket identity by ID. Ticket `<` compares fare. Different IDs may have the same fare. |

Example station input for `>>`: `8 28 North Terminal`. The supplied network is predefined, so the booking menu reads station IDs rather than creating new stations. Automated tests exercise the station input operator. Ordinary interactive input/output uses `std::cin` and `std::cout`.

## Sample sessions

Each input below is one line typed at the next prompt. Full generated transcripts are stored in `samples`.

### Regular booking and ticket history

Input: `4`, `1`, `7`, `1`, `Asha Rao`, `5`, `0`.

Ticket output:

```text
Ticket generated.
Ticket ID: 1001
Passenger: Asha Rao
From: Willow Square
To: Silverwing Airport
Metro type: Regular
Distance: 24.00 km
Station intervals: 6
Fare: INR 58.00
```

### Three services and comparison

Input: `4`, `1`, `7`, `1`, `Asha Rao`, `4`, `7`, `1`, `2`, `Ben Lee`, `4`, `1`, `7`, `3`, `Cara Ray`, `6`, `1001`, `1002`, `0`.

The issued tickets are 1001 (Regular, INR 58.00), 1002 (Express, INR 87.00), and 1003 (Airport, INR 146.00). Comparison prints `First ticket has the lower fare.` Reverse travel has the same distance and fare.

### Invalid input

Input: `x`, `4`, `1`, `1`, `4`, `1`, `2`, `2`, `0`.

The app prints `Enter a whole number.`, then `Choose two valid, distinct stations.`, then `This service does not stop at both stations or is out of service.` It returns to the menu after each rejected action, and issues no ticket.

## Design decisions and limits

- All network data lives in the MetroService constructor. Change station positions/names there; adjust its route capacity when adding more stations. Fare formulas and stopping rules live in Metro.cpp. Airport index 4 is a deliberately simple interchange rule and must be updated if the route ordering changes.
- One linear route keeps distance calculation explainable. Transfers, branching networks, scheduling, payments, cancellations, seat reservations, and persistence are outside this project.
- Capacity describes a train; it does not model occupancy. Tickets do not reserve seats or departures.
- Tickets persist only while this app runs. At most 100 can be stored. IDs start at 1001 for each service session and increase only after successful booking. Ticket identity comparisons assume tickets belong to the same session.
- MetroService validates the complete route and stopping pattern before constructing a ticket. Ticket's public constructor validates basic journey fields but does not receive a Route and cannot independently check its stop membership.
- Numeric menu input accepts exactly one integer per line. Invalid text, fractional values, extra tokens, and out-of-range integer input are rejected. A failed booking returns to the main menu.
- Standard strings own their own text storage. Raw dynamic allocation is limited to the Route array to keep ownership easy to explain. The service's train pointers borrow existing member objects and must never be deleted.
- There are no enums, unions, exception handlers, custom templates, STL containers as core storage, smart pointers, lambdas, or global application state. `std::string` and standard stream interfaces are used as required.
- Ordinary allocation failure is left to the C++ runtime; the project intentionally adds no exception handling.

See VERIFICATION.md for the actual compiler and checks used on this machine.
