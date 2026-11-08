# On Track

A beginner C++11 console project with Blue, Green, and operational Yellow metro lines, shared interchange stations, and in-memory ticket booking.

## Compile and run

From the project folder:

```sh
g++ -std=c++11 -Wall -Wextra -Wpedantic Station.cpp Route.cpp Metro.cpp MetroLine.cpp BlueLine.cpp GreenLine.cpp YellowLine.cpp Ticket.cpp MetroService.cpp main.cpp -o OnTrack.exe
```

Run `./OnTrack.exe` to start the application.

## Lines and stations

The application displays the station sequence for each line in both directions. Chennai Central and Alandur are shared by the Blue and Green Lines. Vadapalani is shared by the Green and Yellow Lines. Each shared station has one station ID and one `Station` object referenced by both routes.

`MetroLine` is the abstract base class for `BlueLine`, `GreenLine`, and `YellowLine`. `MetroService` uses `MetroLine` pointers to configure, display, and search the line routes. 

The Yellow Line includes only the operational Poonamallee Bypass to Vadapalani section. Station IDs are assigned consecutively to the stops currently included in the routes.

Select `4` to book a ticket. The application lists station IDs and line memberships; enter the source and destination IDs, then choose `1` for a counter paper ticket or `2` for eligible digital ticketing. Select `5` to display tickets and `0` to exit. Tickets are kept in memory for the current run, up to 100 tickets. IDs start at 1001.

## Fares

Counter paper fare is INR 20 plus INR 5 for each intermediate station stop between the selected source and destination. A same-station or adjacent-station journey has no extra stops and costs INR 20. Eligible digital tickets retain the 20% discount, applied once to the calculated fare.
