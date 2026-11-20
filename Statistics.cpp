#include "Statistics.h"

Statistics::Statistics(Ticket** completed, int completedCount, int cancelledCount,
                       int nrTotal, int srTotal, int urTotal,
                       TechnicianQueue* technicians, const LocationManager* locations,
                       int totalTime)
{
    this->completed = completed;
    this->completedCount = completedCount;
    this->cancelledCount = cancelledCount;
    this->nrTotal = nrTotal;
    this->srTotal = srTotal;
    this->urTotal = urTotal;
    this->technicians = technicians;
    this->locations = locations;
    this->totalTime = totalTime;
}

// ---------------------------------------------------------------------------
// Averages (cancelled tickets are never counted here)
// ---------------------------------------------------------------------------

// WT = ST - QT
double Statistics::CalculateAverageWT()
{
    if (completedCount == 0) return 0;

    double sum = 0;
    for (int i = 0; i < completedCount; i++)
        sum += completed[i]->getST() - completed[i]->getQT();

    return sum / completedCount;
}

// resolution time = FT - QT
double Statistics::CalculateAverageRT()
{
    if (completedCount == 0) return 0;

    double sum = 0;
    for (int i = 0; i < completedCount; i++)
        sum += completed[i]->getFT() - completed[i]->getQT();

    return sum / completedCount;
}

double Statistics::CalculateBusyTime()
{
    return technicians->getTotalBusyTime();
}

double Statistics::CalculateAverageBusyTime()
{
    return technicians->getAverageBusyTime();
}

double Statistics::CalculateUtilization()
{
    int technicianCount = technicians->size();

    if (technicianCount == 0 || totalTime <= 0) return 0;
    return CalculateBusyTime() * 100.0 / (technicianCount * totalTime);
}

// ---------------------------------------------------------------------------
// Counters
// ---------------------------------------------------------------------------

int Statistics::CountRequests(RequestType type)
{
    if (type == RequestType::NR) return nrTotal;
    if (type == RequestType::SR) return srTotal;
    return urTotal;
}

int Statistics::CountCompleted(RequestType type)
{
    int count = 0;
    for (int i = 0; i < completedCount; i++)
        if (completed[i]->getType() == type) count++;

    return count;
}

int Statistics::CountTechnicians(TechnicianType type)
{
    return technicians->countByType(type);
}

int Statistics::CountByLocation(int lid)
{
    return locations->getTicketCount(lid);
}

// ---------------------------------------------------------------------------
// The report (same text goes to the output file and to the screen)
// ---------------------------------------------------------------------------
void Statistics::GenerateReport(ostream& out)
{
    int requestCount = nrTotal + srTotal + urTotal;

    out << "Requests: " << requestCount
        << " [NR: " << CountRequests(RequestType::NR)
        << ", SR: " << CountRequests(RequestType::SR)
        << ", UR: " << CountRequests(RequestType::UR) << "]\n";

    out << "Completed: " << completedCount
        << " [NR: " << CountCompleted(RequestType::NR)
        << ", SR: " << CountCompleted(RequestType::SR)
        << ", UR: " << CountCompleted(RequestType::UR) << "]\n";

    out << "Cancelled: " << cancelledCount << "\n";
    out << "Locations: " << locations->size() << "\n";
    out << "Technicians: " << technicians->size()
        << " [Specialist: " << CountTechnicians(TechnicianType::ST)
        << ", General: " << CountTechnicians(TechnicianType::GT) << "]\n";

    // every average and percentage is printed with two decimals
    out << fixed << setprecision(2);
    out << "Average waiting time: "    << CalculateAverageWT() << "\n";
    out << "Average resolution time: " << CalculateAverageRT() << "\n";
    out << "Average busy time: "       << CalculateAverageBusyTime() << "\n";
    out << "Simulation time: "         << totalTime << "\n";
    out << "Average utilisation: "     << CalculateUtilization() << "%\n";

    out << "Individual busy times: ";
    technicians->printBusyTimes(out);
    out << ". Total = " << technicians->getTotalBusyTime() << " minutes.\n";

    // ticket counts by location
    if (locations->size() > 0)
    {
        out << "\nTickets by location:\n";
        locations->printCounts(out);
    }
}

void Statistics::GenerateReport()
{
    GenerateReport(cout);
}
