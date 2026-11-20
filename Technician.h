// ============================================================================
// Technician.h
// One technician of the centralized IT unit (General or Specialist).
// ============================================================================
#pragma once
#include "Definitions.h"
#include "Ticket.h"

class Technician
{
private:
    int id{};                                   // 1..(ST_count + GT_count)
    TechnicianType type{TechnicianType::GT};
    int busyTime{};                             // total minutes spent on tickets
    bool available{true};                       // true when idle
    Ticket* currentTicket{nullptr};             // ticket being handled (if any)

public:
    Technician() = default;
    Technician(int id, TechnicianType type);

    int getID() const;
    TechnicianType getType() const;
    int getBusyTime() const;
    bool isAvailable() const;
    Ticket* getCurrentTicket() const;

    void assignTicket(Ticket* ticket);   // technician becomes busy
    void releaseTicket();                // technician becomes idle again
    void addBusyTime(int amount);        // ignores zero / negative amounts
};
