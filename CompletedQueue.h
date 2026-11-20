// ============================================================================
// CompletedQueue.h  (Completed_List)
// Finished tickets, append only. Tickets leave In_Service in (FT, RID) order,
// so this list is ALREADY sorted by FT then RID, and the output file can be
// written with one traversal and no sorting.
// ============================================================================
#pragma once
#include "TicketQueue.h"

class CompletedQueue : public TicketQueue
{
    // nothing to add
};
