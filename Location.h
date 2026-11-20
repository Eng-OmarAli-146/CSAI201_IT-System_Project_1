// ============================================================================
// Location.h
// One university location (department, lab, office ...).
// It also keeps a counter of how many tickets were reported from it, which is
// used by the "ticket counts by location" statistic.
// ============================================================================
#pragma once
#include "Definitions.h"

class Location
{
private:
    int lid{};              // location ID (1..L)
    string name;            // code / name, e.g. CSAI
    int ticketCount{};      // tickets reported from this location

public:
    Location() = default;
    Location(int id, const string& name);

    int getID() const;
    const string& getName() const;
    int getTicketCount() const;
    void incrementTicketCount();
};
