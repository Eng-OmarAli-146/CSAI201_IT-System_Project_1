#include "Technician.h"

Technician::Technician(int id, TechnicianType type) : id(id), type(type) {}

int Technician::getID() const { return id; }
TechnicianType Technician::getType() const { return type; }
int Technician::getBusyTime() const { return busyTime; }
bool Technician::isAvailable() const { return available; }
Ticket* Technician::getCurrentTicket() const { return currentTicket; }

void Technician::assignTicket(Ticket* ticket)
{
    currentTicket = ticket;
    available = false;
}

void Technician::releaseTicket()
{
    currentTicket = nullptr;
    available = true;
}

void Technician::addBusyTime(int amount)
{
    if (amount > 0) busyTime += amount;
}
