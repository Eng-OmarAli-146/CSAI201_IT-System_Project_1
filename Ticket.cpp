#include "Ticket.h"

Ticket::Ticket(int rid, int qt, int lid, int pc, int pr, RequestType type)
    : rid(rid), qt(qt), lid(lid), pc(pc), pr(pr), type(type) {}

int Ticket::getRID() const { return rid; }
int Ticket::getQT() const { return qt; }
int Ticket::getLID() const { return lid; }
int Ticket::getPC() const { return pc; }
int Ticket::getPR() const { return pr; }
int Ticket::getAT() const { return at; }
int Ticket::getST() const { return st; }
int Ticket::getFT() const { return ft; }
int Ticket::getTID() const { return tid; }
RequestType Ticket::getType() const { return type; }
TicketStatus Ticket::getStatus() const { return status; }

void Ticket::setAT(int value) { at = value; }
void Ticket::setST(int value) { st = value; }
void Ticket::setFT(int value) { ft = value; }
void Ticket::setTID(int value) { tid = value; }
void Ticket::setType(RequestType value) { type = value; }
void Ticket::setStatus(TicketStatus value) { status = value; }
