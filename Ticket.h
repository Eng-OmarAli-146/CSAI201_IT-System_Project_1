// ============================================================================
// Ticket.h
// One support request. A ticket is created ONCE when the input file is read,
// and every list in the project stores a POINTER to it, so moving a ticket
// from one list to another never copies any data.
// ============================================================================
#pragma once
#include "Definitions.h"

class Ticket
{
private:
    // ---- data that comes from the input file (never changes) ----
    int rid{};          // request ID (unique)
    int qt{};           // request time
    int lid{};          // location ID where the problem was reported
    int pc{};           // problem code (row number in the configuration table)
    int pr{};           // priority (only UR tickets have one, others keep 0)
    RequestType type{RequestType::NR};

    // ---- data filled in by the scheduler during the simulation ----
    int at{-1};         // assignment time
    int st{-1};         // service start time (always equal to AT)
    int ft{-1};         // service finish time = ST + duration
    int tid{-1};        // ID of the technician handling the ticket
    TicketStatus status{TicketStatus::NEW};

public:
    Ticket() = default;
    Ticket(int rid, int qt, int lid, int pc, int pr, RequestType type);

    // getters
    int getRID() const;
    int getQT() const;
    int getLID() const;
    int getPC() const;
    int getPR() const;
    int getAT() const;
    int getST() const;
    int getFT() const;
    int getTID() const;
    RequestType getType() const;
    TicketStatus getStatus() const;

    // setters (only the values that change during the simulation)
    void setAT(int value);
    void setST(int value);
    void setFT(int value);
    void setTID(int value);
    void setType(RequestType value);
    void setStatus(TicketStatus value);
};
