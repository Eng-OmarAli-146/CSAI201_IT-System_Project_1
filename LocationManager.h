// ============================================================================
// LocationManager.h
// Dynamic array of locations, indexed by location ID:
//     location ID 1 -> index 0, ID 2 -> index 1, and so on.
// The array doubles its size when it is full.
// ============================================================================
#pragma once
#include "Definitions.h"
#include "Location.h"

class LocationManager
{
private:
    Location** items;       // array of pointers to the locations
    int capacity;           // size of the array
    int count;              // number of locations stored

    void grow();            // doubles the array when it is full

public:
    LocationManager();
    ~LocationManager();

    void addLocation(const Location& location);            // O(1)
    const Location* getLocation(int id) const;             // O(1)
    string getLocationName(int id) const;                  // O(1)
    bool isValid(int id) const;                            // O(1)
    void incrementTicketCount(int id);                     // O(1)
    int  getTicketCount(int id) const;                     // O(1)
    void printCounts(ostream& out) const;                  // O(L)
    int  size() const;
    void clear();                                          // O(L)
};
