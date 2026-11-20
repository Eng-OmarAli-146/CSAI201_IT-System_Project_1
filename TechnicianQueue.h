// ============================================================================
// TechnicianQueue.h
// Linked FIFO queue that OWNS every technician of the IT unit.
// Technicians are inserted in increasing ID order (all ST first, then all GT).
// The other lists (available heaps) only keep pointers to these objects.
// ============================================================================
#pragma once
#include "Definitions.h"
#include "Technician.h"
#include "ProblemConfigurationQueue.h"
#include "LocationManager.h"

class TechnicianQueue
{
private:
    struct Node
    {
        Technician data;
        Node* next;
    };

    Node* head;
    Node* tail;
    int count;

public:
    TechnicianQueue();
    ~TechnicianQueue();

    void        insertTechnician(const Technician& technician);            // O(1)
    Technician* getTechnicianByID(int id);                                 // O(T)
    bool        updateTechnician(int id, const Technician& technician);    // O(T)

    // interactive mode: prints every working technician with its ticket
    void printWorkingTechnicians(const ProblemConfigurationQueue* configs,
                                 const LocationManager* locations) const;  // O(T)

    // statistics helpers
    int    countByType(TechnicianType type) const;                         // O(T)
    int    getTotalBusyTime() const;                                       // O(T)
    double getAverageBusyTime() const;                                     // O(T)
    void   printBusyTimes(ostream& out) const;     // "technician 1 = 5; technician 2 = 3"

    int  size() const;
    void clear();                                                          // O(T)
};
