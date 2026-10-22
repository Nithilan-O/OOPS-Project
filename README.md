# Metro Rail Service

A beginner C++11 console project with one metro line, three stops (A, B, and C), one Regular metro service, and in-memory ticket booking.

## Compile and run

From the project folder:

```sh
g++ -std=c++11 -Wall -Wextra -Wpedantic Station.cpp Route.cpp Metro.cpp Ticket.cpp MetroService.cpp main.cpp -o metro.exe
```

Run `./metro.exe` to start the application.

## Line and service

The single line is named Metro Line. It runs in both directions between these stops:

| Stop | Position |
| --- | ---: |
| A | 0 km |
| B | 5 km |
| C | 10 km |

The Regular service stops at all three stations. Its fare is INR 10 plus INR 2 per kilometre, rounded to two decimal places. To book a ticket, select `4`, enter the source and destination stop IDs (`1` for A, `2` for B, `3` for C), then enter the passenger name. Select `5` to display tickets and `0` to exit.

All tickets are kept in memory for the current run, up to 100 tickets. IDs start at 1001.
