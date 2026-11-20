#include "Simulation.h"
#include "Statistics.h"
#include "OutputWriter.h"

Simulation::Simulation(InputReader* reader, bool interactive, const string& outputFileName)
    : CurrentTime(1), interactive(interactive), outputFileName(outputFileName),
      allRequests(reader->getRequests()),
      allCancellations(reader->getCancellations()),
      technicians(reader->getTechnicians()),
      configs(reader->getConfigurations()),
      locations(reader->getLocations()),
      nrTotal(reader->getNRTotal()), srTotal(reader->getSRTotal()), urTotal(reader->getURTotal()),
      stCount(0), gtCount(0),
      cancelManager(&waitingNR, &inService, &availableGT, &availableST, technicians, &cancelled),
      scheduler(allRequests, allCancellations, &waitingNR, &waitingSR, &waitingUR,
                &inService, &availableGT, &availableST, &completed, technicians,
                configs, &cancelManager)
{
    // At the start every technician is idle: put each one in the available
    // heap that matches its type. Technician IDs are 1, 2, 3, ... T.
    for (int id = 1; id <= technicians->size(); id++)
    {
        Technician* tech = technicians->getTechnicianByID(id);

        if (tech->getType() == TechnicianType::GT)
        {
            availableGT.insert(tech);
            gtCount++;
        }
        else
        {
            availableST.insert(tech);
            stCount++;
        }
    }
}

// Every ticket is in exactly one list at the end, so we delete them list by list.
Simulation::~Simulation()
{
    allRequests->clearAndDeleteTickets();       // requests that were never released
    waitingNR.clearAndDeleteTickets();
    waitingSR.clearAndDeleteTickets();
    completed.clearAndDeleteTickets();
    cancelled.clearAndDeleteTickets();

    while (!waitingUR.isEmpty()) delete waitingUR.removeHighest();
    while (!inService.isEmpty()) delete inService.extractMin();
}

// ---------------------------------------------------------------------------
// The main loop: one pass = one minute
// ---------------------------------------------------------------------------
void Simulation::Run()
{
    if (!interactive)
    {
        cout << "Silent Mode\n";
        cout << "Simulation Starts...\n";
    }

    bool stopped = false;

    while (!Finished())
    {
        scheduler.RunMinute(CurrentTime);   // complete, release, cancel, assign
        Display();                          // only prints in interactive mode

        // Safety: a waiting ticket whose technician type does not exist at all
        // can never be served, so we must not loop forever.
        if (CannotBeServed())
        {
            cout << "\nWarning: no suitable technician exists for a waiting ticket, "
                    "so the simulation stops at minute " << CurrentTime << ".\n";
            stopped = true;
            break;
        }

        CurrentTime++;
    }

    // The final simulation minute T is the last minute that was processed.
    // (A file with no requests ends at minute 1.)
    int finalTime = CurrentTime - 1;
    if (finalTime < 1) finalTime = 1;
    if (stopped) finalTime = CurrentTime;

    int completedCount = 0;
    Ticket** completedTickets = completed.toArray(completedCount);

    Statistics stats(completedTickets, completedCount, cancelled.getCount(),
                     nrTotal, srTotal, urTotal,
                     technicians, locations, finalTime);

    OutputWriter writer(completedTickets, completedCount, &stats, outputFileName);

    if (interactive)
        cout << "\n";

    bool written = writer.WriteOutputFile();

    if (!written)
    {
        cout << "Output file could not be created: " << outputFileName << "\n";
    }
    else
    {
        if (interactive)
            stats.GenerateReport();             // same report on the screen

        cout << "Simulation ends, Output file created.\n";
    }

    delete[] completedTickets;                  // the array copy is no longer needed
}

// ---------------------------------------------------------------------------
// Stop conditions
// ---------------------------------------------------------------------------

// A waiting ticket can never be served if its technician type does not exist.
bool Simulation::CannotBeServed()
{
    if (gtCount == 0 && !waitingNR.isEmpty()) return true;
    if (stCount == 0 && !waitingSR.isEmpty()) return true;
    if (stCount + gtCount == 0 && !waitingUR.isEmpty()) return true;
    return false;
}

// Termination rule: all request and cancellation records are consumed, all
// waiting lists are empty and every technician is idle (nothing in service).
bool Simulation::Finished()
{
    return allRequests->isEmpty() &&
           allCancellations->isEmpty() &&
           waitingNR.isEmpty() && waitingSR.isEmpty() &&
           waitingUR.isEmpty() && inService.isEmpty();
}

// ---------------------------------------------------------------------------
// Interactive screen
// ---------------------------------------------------------------------------
void Simulation::Display()
{
    if (!interactive) return;

    cout << "\nMinute " << CurrentTime << "\n";

    // waiting tickets, each list in its own scheduling order
    cout << "Waiting UR (priority, QT, RID): ";
    waitingUR.printIDs();
    cout << "Waiting SR (FCFS): ";
    waitingSR.printIDs();
    cout << "Waiting NR (FCFS): ";
    waitingNR.printIDs();

    // available technicians by type
    cout << "Available technicians: ST=" << availableST.getCount()
         << " GT=" << availableGT.getCount() << "\n";

    // working technicians with the ticket each one is handling
    cout << "Working technicians:\n";
    technicians->printWorkingTechnicians(configs, locations);

    // completed tickets, in FT then RID order
    cout << "Completed (FT, RID): ";
    completed.printIDs();

    // accepted cancellations
    cout << "Accepted cancellations: " << cancelled.getCount() << " -> ";
    cancelled.printIDs();

    cout << "Press Enter to advance to the next minute.";
    cin.get();
}
