#include "CancellationManager.h"

CancellationManager::CancellationManager(WaitingNRQueue* waitingNR, InServicePriorityQueue* inService,
                                         AvailableTechnicians* availableGT, AvailableTechnicians* availableST,
                                         TechnicianQueue* technicians, CancelledQueue* cancelled)
    : waitingNR(waitingNR), inService(inService),
      availableGT(availableGT), availableST(availableST),
      technicians(technicians), cancelled(cancelled) {}

// Try the two places an NR can be in. If neither has it, the cancellation is ignored.
bool CancellationManager::CancelTicket(int RID, int currentTime)
{
    if (CancelWaitingNR(RID))
        return true;

    return CancelAssignedNR(RID, currentTime);
}

// Case 1: the NR is still waiting -> just remove it from the waiting queue.
bool CancellationManager::CancelWaitingNR(int RID)
{
    Ticket* t = waitingNR->removeByID(RID);
    if (t == nullptr) return false;

    t->setStatus(TicketStatus::CANCELLED);
    cancelled->enqueue(t);
    return true;
}

// Case 2: the NR is already assigned but not finished -> free the technician.
bool CancellationManager::CancelAssignedNR(int RID, int currentTime)
{
    Ticket* t = inService->getByID(RID);
    if (t == nullptr) return false;                         // finished or unknown ID
    if (t->getType() != RequestType::NR) return false;      // SR and UR are ignored

    inService->removeByID(RID);

    Technician* tech = technicians->getTechnicianByID(t->getTID());
    if (tech != nullptr)
    {
        // the technician was busy from AT until the cancellation minute
        tech->addBusyTime(currentTime - t->getAT());
        tech->releaseTicket();

        // back to the idle list that matches its type
        if (tech->getType() == TechnicianType::GT)
            availableGT->insert(tech);
        else
            availableST->insert(tech);
    }

    t->setStatus(TicketStatus::CANCELLED);
    cancelled->enqueue(t);
    return true;
}
