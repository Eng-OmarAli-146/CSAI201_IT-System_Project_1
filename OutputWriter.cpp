#include "OutputWriter.h"

// The completed list is ALREADY in ascending FT, then ascending RID order
// (tickets leave In_Service in that order), so we just write it from the start
// to the end. No sorting is needed.
void OutputWriter::WriteCompletedTickets()
{
    out << "FT RID QT WT ST AT TID LID\n";

    for (int i = 0; i < completedCount; i++)
    {
        Ticket* t = completed[i];

        out << t->getFT() << " " << t->getRID() << " " << t->getQT() << " "
            << t->getST() - t->getQT() << " "       // WT = ST - QT
            << t->getST() << " " << t->getAT() << " "
            << t->getTID() << " " << t->getLID() << "\n";
    }
}

void OutputWriter::WriteStatistics()
{
    stats->GenerateReport(out);
}

bool OutputWriter::WriteOutputFile()
{
    out.open(fileName.c_str());
    if (!out.is_open()) return false;

    WriteCompletedTickets();
    WriteStatistics();
    out.close();
    return true;
}
