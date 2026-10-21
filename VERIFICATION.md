# Verification

Verified on 21 October 2026 on Windows x86-64.

## Compiler and build

No GCC, Clang, or Visual C++ compiler was installed on the command path or in the common locations checked. Downloaded the official portable Zig 0.13.0 toolchain from `https://ziglang.org/download/0.13.0/zig-windows-x86_64-0.13.0.zip` into this workspace. Its Clang C++ frontend compiled all application translation units together in C++11 mode.

Both final app and test builds succeeded with:

```text
-std=c++11 -Wall -Wextra -Wpedantic -Werror
```

There were no project-source warnings or errors. On its initial run the toolchain emitted attribute warnings while building its own bundled libunwind runtime; those are outside this project's source. Subsequent final builds completed without diagnostics. GCC commands are provided in README.md; GCC itself was not available for execution on this machine.

The compiled application is `build/metro.exe`; the test executable is `build/metro-tests.exe`.

## Automated test result

```text
All metro tests passed.
```

The test process exited with status 0. Assertions were enabled. The tests cover:

- Default and parameterized objects, including unassigned stations/tickets and route fallback capacity.
- Station and Ticket value copying; Route deep-copy construction, assignment into existing storage, safe self-assignment, and use after the original owner is destroyed.
- Independent route-array mutations after copying, route capacity, duplicate IDs, invalid indices, and station ordering.
- Station setter rejection of invalid IDs, blank names, negative positions, infinity, and NaN.
- Successful and failed Station input extraction without partially overwriting the destination; output for Station, Route, Metro, and Ticket; preservation of output precision by Ticket.
- Runtime fare dispatch through base pointers for all three train types. Expected fares for 24 km: Regular 58.00, Express 87.00, Airport 146.00.
- Invalid fare distances, invalid stop indices, train setters, and an out-of-service train.
- Forward/reverse distances and interval counts, invalid station IDs, identical endpoints, and unsupported express stops.
- Ticket generation, copying, display, identity comparison, both directions of fare comparison, equal fares on different tickets, and unknown ticket IDs.
- All menu selections, invalid menu choices, invalid numeric text and trailing tokens, blank passenger names, and invalid train choices.
- Failed booking followed by a successful booking without an ID gap.
- Storage limit of 100 tickets, successful final ID 1100, and rejection of a 101st booking.
- Immediate end-of-input, interrupted booking, and ordinary exit.

These tests exercise destruction and independent storage behavior. No external heap profiler or sanitizer was run.

## Executable sample sessions

The actual application executable was also run with each of these input files; all three runs exited successfully:

| Input | Saved console output |
| --- | --- |
| `samples/regular-input.txt` | `samples/regular-output.txt` |
| `samples/services-input.txt` | `samples/services-output.txt` |
| `samples/invalid-input.txt` | `samples/invalid-output.txt` |

Example replay in PowerShell:

```powershell
Get-Content samples/regular-input.txt | ./build/metro.exe
```

The transcript files contain program output; piped input is recorded separately rather than echoed.

## Restriction check

Scanned project `.h` and `.cpp` files, excluding downloaded tools and caches, for source comments and the restricted keywords `enum`, `union`, `try`, `catch`, `throw`, and `template`. No matches were found. Source inspection also confirms array-based storage, no smart pointers, no lambda expressions, and no global application state.
