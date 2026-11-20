// ============================================================================
// OutputWriter.h
// Writes the output file: the table of completed tickets, then the statistics.
// ============================================================================
#pragma once
#include "Definitions.h"
#include "Ticket.h"
#include "Statistics.h"

class OutputWriter
{
private:
    ofstream    out;
    Ticket**    completed;          // completed tickets, already sorted by FT then RID
    int         completedCount;
    Statistics* stats;
    string      fileName;

public:
    OutputWriter(Ticket** completed, int completedCount,
                 Statistics* stats, const string& fileName)
        : completed(completed), completedCount(completedCount),
          stats(stats), fileName(fileName) {}

    void WriteCompletedTickets();
    void WriteStatistics();
    bool WriteOutputFile();         // false if the file could not be created
};
