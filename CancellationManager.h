// ============================================================================
// CancellationManager.h
// Applies ONE cancellation record. Rules:
//   - only NR tickets can be cancelled
//   - a waiting NR is removed from Waiting_NR (the others keep their order)
//   - an assigned NR (service not finished) is removed from In_Service and its
//     technician is released immediately
//   - SR, UR, completed, already cancelled and unknown IDs are ignored
// ============================================================================
#pragma once
#include "Definitions.h"
#include "Ticket.h"
#include "Technician.h"
#include "TechnicianQueue.h"
#include "WaitingNRQueue.h"
#include "InServicePriorityQueue.h"
#include "AvailableTechnicians.h"
#include "CancelledQueue.h"

class CancellationManager
{
private:
    WaitingNRQueue*         waitingNR;
    InServicePriorityQueue* inService;
    AvailableTechnicians*   availableGT;
    AvailableTechnicians*   availableST;
    TechnicianQueue*        technicians;
    CancelledQueue*         cancelled;

public:
    CancellationManager(WaitingNRQueue* waitingNR, InServicePriorityQueue* inService,
                        AvailableTechnicians* availableGT, AvailableTechnicians* availableST,
                        TechnicianQueue* technicians, CancelledQueue* cancelled);

    bool CancelTicket(int RID, int currentTime);        // true if the cancellation was accepted
    bool CancelWaitingNR(int RID);
    bool CancelAssignedNR(int RID, int currentTime);
};
