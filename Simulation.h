// ============================================================================
// Simulation.h
// The main driver. It owns the working lists (waiting, in service, available,
// completed, cancelled), runs the minute loop, shows the interactive screens
// and creates the output file. The real work of each minute is done by the
// Scheduler.
// ============================================================================
#pragma once
#include "Definitions.h"
#include "InputReader.h"
#include "Ticket.h"
#include "Technician.h"
#include "TechnicianQueue.h"
#include "RequestQueue.h"
#include "CancellationQueue.h"
#include "WaitingNRQueue.h"
#include "WaitingSRQueue.h"
#include "WaitingURPriorityQueue.h"
#include "InServicePriorityQueue.h"
#include "AvailableTechnicians.h"
#include "CompletedQueue.h"
#include "CancelledQueue.h"
#include "ProblemConfigurationQueue.h"
#include "LocationManager.h"
#include "CancellationManager.h"
#include "Scheduler.h"

class Simulation
{
private:
    int    CurrentTime;                 // the simulation clock (starts at minute 1)
    bool   interactive;                 // true = Interactive, false = Silent
    string outputFileName;

    // lists loaded by the InputReader (owned by the reader)
    RequestQueue*              allRequests;
    CancellationQueue*         allCancellations;
    TechnicianQueue*           technicians;
    ProblemConfigurationQueue* configs;
    LocationManager*           locations;

    int nrTotal;                        // input requests by type (for the statistics)
    int srTotal;
    int urTotal;
    int stCount;                        // technicians by type
    int gtCount;

    // lists owned by the simulation
    // (declaration order matters: the two objects below use their addresses)
    WaitingNRQueue          waitingNR;
    WaitingSRQueue          waitingSR;
    WaitingURPriorityQueue  waitingUR;
    InServicePriorityQueue  inService;
    AvailableTechnicians    availableGT;
    AvailableTechnicians    availableST;
    CompletedQueue          completed;
    CancelledQueue          cancelled;

    CancellationManager cancelManager;
    Scheduler           scheduler;

    bool CannotBeServed();              // safety check, see Run()

public:
    Simulation(InputReader* reader, bool interactive, const string& outputFileName);
    ~Simulation();

    void Run();
    void Display();                     // interactive screen for the current minute
    bool Finished();                    // true when the simulation must stop
};
