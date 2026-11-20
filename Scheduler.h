// ============================================================================
// Scheduler.h
// The coordinator of one simulation minute (as described in the Phase 1.1
// report). It uses the lists but does not own them (Simulation owns them).
//
// Order of work in every minute (project rules):
//   1. CompleteServices      finished tickets leave In_Service, technicians are released
//   2. ReleaseRequests       tickets with QT = now enter their waiting list
//   3. ProcessCancellations  cancellations with CT = now are applied
//   4. AssignTickets         UR first, then SR, then NR
// ============================================================================
#pragma once
#include "Definitions.h"
#include "Ticket.h"
#include "Technician.h"
#include "TechnicianQueue.h"
#include "RequestQueue.h"
#include "CancellationQueue.h"
#include "WaitingNRQueue.h"
#include "WaitingSRQueue.h"
#include "WaitingURPriorityQueue.h"
#include "InServicePriorityQueue.h"
#include "AvailableTechnicians.h"
#include "CompletedQueue.h"
#include "ProblemConfigurationQueue.h"
#include "CancellationManager.h"

class Scheduler
{
private:
    RequestQueue*            allRequests;
    CancellationQueue*       allCancellations;
    WaitingNRQueue*          waitingNR;
    WaitingSRQueue*          waitingSR;
    WaitingURPriorityQueue*  waitingUR;
    InServicePriorityQueue*  inService;
    AvailableTechnicians*    availableGT;
    AvailableTechnicians*    availableST;
    CompletedQueue*          completed;
    TechnicianQueue*         technicians;
    const ProblemConfigurationQueue* configs;
    CancellationManager*     cancelManager;

public:
    Scheduler(RequestQueue* allRequests, CancellationQueue* allCancellations,
              WaitingNRQueue* waitingNR, WaitingSRQueue* waitingSR, WaitingURPriorityQueue* waitingUR,
              InServicePriorityQueue* inService,
              AvailableTechnicians* availableGT, AvailableTechnicians* availableST,
              CompletedQueue* completed, TechnicianQueue* technicians,
              const ProblemConfigurationQueue* configs, CancellationManager* cancelManager);

    void RunMinute(int currentTime);            // runs the 4 steps above in order

    void CompleteServices(int currentTime);
    void ReleaseRequests(int currentTime);
    void ProcessCancellations(int currentTime);

    void AssignTickets(int currentTime);
    void AssignUR(int currentTime);
    void AssignSR(int currentTime);
    void AssignNR(int currentTime);
    void AssignTicket(Ticket* t, Technician* tech, int currentTime);
};
