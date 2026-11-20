// ============================================================================
// Statistics.h
// Computes and prints everything the project asks for at the end of a run.
// ============================================================================
#pragma once
#include "Definitions.h"
#include "Ticket.h"
#include "TechnicianQueue.h"
#include "LocationManager.h"

class Statistics
{
private:
    Ticket**     completed;         // completed tickets, in FT then RID order
    int          completedCount;
    int          cancelledCount;    // accepted cancellations
    int          nrTotal;           // input requests of each type
    int          srTotal;
    int          urTotal;
    TechnicianQueue*       technicians;
    const LocationManager* locations;
    int          totalTime;         // final simulation minute (T)

public:
    Statistics(Ticket** completed, int completedCount, int cancelledCount,
               int nrTotal, int srTotal, int urTotal,
               TechnicianQueue* technicians, const LocationManager* locations,
               int totalTime);

    // averages and percentages
    double CalculateAverageWT();            // sum(ST - QT) / completed
    double CalculateAverageRT();            // sum(FT - QT) / completed
    double CalculateBusyTime();             // total busy time of all technicians
    double CalculateAverageBusyTime();      // total busy time / technician count
    double CalculateUtilization();          // 100 * total busy / (technicians * T)

    // counters
    int CountRequests(RequestType type);
    int CountCompleted(RequestType type);
    int CountTechnicians(TechnicianType type);
    int CountByLocation(int lid);

    int getCompletedCount() { return completedCount; }
    int getCancelledCount() { return cancelledCount; }

    void GenerateReport(ostream& out);      // writes the report to any stream (file or screen)
    void GenerateReport();                  // writes the report to the screen
};
