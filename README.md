# IT System — University IT Support Management System (CSAI 201)

A discrete-time simulation of a centralized university IT support unit.
Tickets arrive at a request time (QT), wait in a list, and are assigned to
available technicians by fixed rules:

* **NR** (normal) -> General Technician (GT) only, FCFS
* **SR** (specialist, hardware) -> Specialist Technician (ST) only, FCFS
* **UR** (urgent) -> GT first, then ST, higher priority (PR) first

Only NR tickets can be cancelled (while waiting, or after assignment but before they finish).

## Structure

Every list is a hand-written data structure (no STL containers), chosen in the Phase 1.1 report.

| Report list | Class | Data structure |
|---|---|---|
| All_Requests | `RequestQueue` | linked FIFO queue (derived from `TicketQueue`) |
| All_Cancellations | `CancellationQueue` | linked FIFO queue |
| Locations | `LocationManager` (+ `Location`) | dynamic array indexed by LID, with a ticket counter per location |
| Problem_Configurations | `ProblemConfigurationQueue` (+ `ServiceConfiguration`) | linked FIFO queue, PC = position |
| All_Technicians | `TechnicianQueue` (+ `Technician`) | linked FIFO queue, owns the technicians |
| Available_ST / Available_GT | `AvailableTechnicians` (two objects) | array min-heap on technician ID |
| Waiting_NR | `WaitingNRQueue` | `TicketQueue` + `removeByID` |
| Waiting_SR | `WaitingSRQueue` | `TicketQueue` |
| Waiting_UR | `WaitingURPriorityQueue` | array max-heap (PR, then QT, then RID) |
| In_Service | `InServicePriorityQueue` | array min-heap on (FT, RID) + `removeByID` |
| Completed_List | `CompletedQueue` | `TicketQueue` (already sorted by FT, RID) |
| Cancelled_List | `CancelledQueue` | `TicketQueue` |

| Layer | Files |
|---|---|
| Shared types, `using namespace std` | `Definitions.h` |
| Entities | `Ticket`, `Technician`, `Location`, `ServiceConfiguration` |
| Base queue | `TicketQueue` |
| Engine | `Scheduler` (runs each minute), `CancellationManager`, `Simulation` (driver, screens) |
| I/O | `InputReader`, `OutputWriter`, `Statistics` |
| Entry point | `main.cpp` |

### One simulation minute (done by `Scheduler::RunMinute`)

1. complete the services whose FT is due and release the technicians
2. release the requests with QT = now
3. process the cancellations with CT = now
4. assign tickets: UR first, then SR, then NR

Then the state is displayed (interactive mode) and the clock advances.

## Build

Plain C++, only a g++ compiler is needed:

```bash
g++ -std=c++11 -Wall -Wextra *.cpp -o it_system
```

Or with the included Makefile (it runs exactly the same command):

```bash
make          # build
make run      # build + run
make clean    # remove the executable
```

## Run

```bash
./it_system
```

The program asks for three things (press Enter to accept the default):

```
Choose mode [I=Interactive, S=Silent]: I
Enter input file name [input.txt]: input.txt
Enter output file name [output.txt]: output.txt
```

Interactive mode prints the state of the IT unit at every minute and waits for
Enter. Silent mode prints only `Silent Mode`, `Simulation Starts...` and
`Simulation ends, Output file created.` Both modes write exactly the same output file.

## Input format (`input.txt`)

```
<L>                          number of university locations
<name> ...                   L location codes/names (one token each; LID = row number)
<K>                          number of problem configurations
<category> <duration>        K rows; category is B or H (PC = row number, starting at 1)
<ST_count> <GT_count>        technicians of the centralized IT unit
<R>                          number of requests
<TYPE> <QT> <RID> <LID> <PC> [<PR>]
<C>                          number of cancellations
<CT> <RID>
```

* `TYPE` is `NR`, `SR` or `UR`; only `UR` records carry the extra priority `PR`.
* Technician IDs are assigned automatically: all ST technicians first, then all GT.
* Records are sorted by time (QT / CT) and keep file order for equal times.
* NR/UR must use a category `B` problem code, SR a category `H` one. A request with an
  unknown location or a code that does not fit its type is skipped with a warning.
* Only NR tickets can be cancelled; SR, UR, completed and unknown IDs are ignored.

## Output format (`output.txt`)

A table of completed tickets sorted by ascending `FT`, then `RID`, followed by the statistics:

```
FT RID QT WT ST AT TID LID
4 1 1 0 1 1 3 1
4 3 1 0 1 1 2 3
6 2 1 0 1 1 1 2
Requests: 4 [NR: 2, SR: 1, UR: 1]
Completed: 3 [NR: 1, SR: 1, UR: 1]
Cancelled: 1
Locations: 3
Technicians: 3 [Specialist: 1, General: 2]
Average waiting time: 0.00
Average resolution time: 3.67
Average busy time: 3.67
Simulation time: 6
Average utilisation: 61.11%
Individual busy times: technician 1 = 5; technician 2 = 3; technician 3 = 3. Total = 11 minutes.

Tickets by location:
Location 1: 1
Location 2: 2
Location 3: 1
```

`WT = ST - QT` and resolution time = `FT - QT`; cancelled tickets are excluded from both.
Averages and percentages use two decimals. Averages are `0.00` when nothing completed,
and utilisation is `0.00` when there are no technicians.
