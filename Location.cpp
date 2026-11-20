#include "Location.h"

Location::Location(int id, const string& name) : lid(id), name(name) {}

int Location::getID() const { return lid; }
const string& Location::getName() const { return name; }
int Location::getTicketCount() const { return ticketCount; }
void Location::incrementTicketCount() { ticketCount++; }
