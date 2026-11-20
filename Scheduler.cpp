#include "Scheduler.h"

Scheduler::Scheduler(RequestQueue* allRequests, CancellationQueue* allCancellations,
                     WaitingNRQueue* waitingNR, WaitingSRQueue* waitingSR, WaitingURPriorityQueue* waitingUR,
                     InServicePriorityQueue* inService,
                     AvailableTechnicians* availableGT, AvailableTechnicians* availableST,
                     CompletedQueue* completed, TechnicianQueue* technicians,
                     const ProblemConfigurationQueue* configs, CancellationManager* cancelManager)
    : allRequests(allRequests), allCancellations(allCancellations),
      waitingNR(waitingNR), waitingSR(waitingSR), waitingUR(waitingUR),
      inService(inService), availableGT(availableGT), availableST(availableST),
      completed(completed), technicians(technicians),
      configs(configs), cancelManager(cancelManager) {}

// ---------------------------------------------------------------------------
// One minute of the simulation
// ---------------------------------------------------------------------------
void Scheduler::RunMinute(int currentTime)
{
    CompleteServices(currentTime);
    ReleaseRequests(currentTime);
    ProcessCancellations(currentTime);
    AssignTickets(currentTime);
}

// ---------------------------------------------------------------------------
// Step 1: complete the services that are due
// ---------------------------------------------------------------------------
// In_Service is a min-heap on FT, so we only look at the root.
// A technician that finishes at minute t is free again at minute t.
void Scheduler::CompleteServices(int currentTime)
{
    while (!inService->isEmpty() && inService->peek()->getFT() <= currentTime)
    {
        Ticket* t = inService->extractMin();
        t->setStatus(TicketStatus::COMPLETED);
        completed->enqueue(t);

        Technician* tech = technicians->getTechnicianByID(t->getTID());
        if (tech == nullptr) continue;

        tech->addBusyTime(t->getFT() - t->getST());
        tech->releaseTicket();

        if (tech->getType() == TechnicianType::GT)
            availableGT->insert(tech);
        else
            availableST->insert(tech);
    }
}

// ---------------------------------------------------------------------------
// Step 2: release the requests that arrive now
// ---------------------------------------------------------------------------
// The input is sorted by QT, so the request at the front is always the next one.
// We use "<=" (not "==") so a request can never get stuck at the front.
void Scheduler::ReleaseRequests(int currentTime)
{
    while (!allRequests->isEmpty() && allRequests->peek()->getQT() <= currentTime)
    {
        Ticket* t = allRequests->dequeue();
        t->setStatus(TicketStatus::WAITING);

        if (t->getType() == RequestType::NR)       waitingNR->enqueue(t);
        else if (t->getType() == RequestType::SR)  waitingSR->enqueue(t);
        else                                       waitingUR->insert(t);
    }
}

// ---------------------------------------------------------------------------
// Step 3: apply the cancellations that are due
// ---------------------------------------------------------------------------
void Scheduler::ProcessCancellations(int currentTime)
{
    CancellationRequest request;

    while (allCancellations->peek(request) && request.CT <= currentTime)
    {
        allCancellations->dequeue(request);
        cancelManager->CancelTicket(request.RID, currentTime);
    }
}

// ---------------------------------------------------------------------------
// Step 4: assign waiting tickets to available technicians
// ---------------------------------------------------------------------------
// Order: UR first, then SR, then NR
void Scheduler::AssignTickets(int currentTime)
{
    AssignUR(currentTime);
    AssignSR(currentTime);
    AssignNR(currentTime);
}

// UR: highest priority first. Try an available GT, otherwise an available ST.
// All UR use the same technicians, so if the top UR finds nobody, no other UR can: stop.
void Scheduler::AssignUR(int currentTime)
{
    while (!waitingUR->isEmpty())
    {
        Technician* tech = nullptr;

        if (!availableGT->isEmpty())
            tech = availableGT->extractMin();
        else if (!availableST->isEmpty())
            tech = availableST->extractMin();
        else
            break;                       // nobody is free

        Ticket* t = waitingUR->removeHighest();
        AssignTicket(t, tech, currentTime);
    }
}

// SR: first come first served, ST only.
void Scheduler::AssignSR(int currentTime)
{
    while (!waitingSR->isEmpty() && !availableST->isEmpty())
    {
        Technician* tech = availableST->extractMin();
        Ticket* t = waitingSR->dequeue();
        AssignTicket(t, tech, currentTime);
    }
}

// NR: first come first served, GT only.
void Scheduler::AssignNR(int currentTime)
{
    while (!waitingNR->isEmpty() && !availableGT->isEmpty())
    {
        Technician* tech = availableGT->extractMin();
        Ticket* t = waitingNR->dequeue();
        AssignTicket(t, tech, currentTime);
    }
}

// Assignment and service start happen in the same minute: AT = ST = currentTime.
void Scheduler::AssignTicket(Ticket* t, Technician* tech, int currentTime)
{
    int duration = configs->getDuration(t->getPC());

    t->setAT(currentTime);
    t->setST(currentTime);
    t->setFT(currentTime + duration);
    t->setTID(tech->getID());
    t->setStatus(TicketStatus::IN_SERVICE);

    tech->assignTicket(t);
    inService->insert(t);
}
