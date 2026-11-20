// ============================================================================
// AvailableTechnicians.h  (Available_ST and Available_GT)
// Array based MIN-HEAP of idle technicians, keyed on the technician ID.
// The project needs TWO lists (idle specialists, idle generals), so the
// Simulation creates TWO objects of this class.
//
// Why a heap? Technicians come back to the idle pool in arbitrary order
// (different finish times, cancellations), so a plain FIFO queue would break
// the rule "always take the smallest eligible technician ID".
// The root of the heap always holds the smallest ID.
// ============================================================================
#pragma once
#include "Definitions.h"
#include "Technician.h"

class AvailableTechnicians
{
private:
    Technician** items;     // the heap is stored in this dynamic array
    int count;              // technicians currently in the heap
    int capacity;           // size of the array

    void grow();                    // doubles the array when it is full
    void siftUp(int index);         // moves a technician up while its ID is smaller than its parent's
    void siftDown(int index);       // moves a technician down while a child has a smaller ID

public:
    AvailableTechnicians();
    ~AvailableTechnicians();

    void        insert(Technician* t);      // technician becomes idle      O(log T)
    Technician* peekMin() const;            // smallest ID, not removed     O(1)
    Technician* extractMin();               // smallest ID, removed         O(log T)
    bool        isEmpty() const;            // O(1)
    int         getCount() const;           // O(1)
    void        print() const;              // IDs in heap order (not sorted)   O(T)
    void        clear();                    // O(1)
};
