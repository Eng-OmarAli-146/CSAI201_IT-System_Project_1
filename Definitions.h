// ============================================================================
// Definitions.h
// Shared types used by the whole project.
// Every other file includes this one (directly or through another header),
// so the standard headers and "using namespace std" live here, in ONE place.
// That is why the rest of the code can write string / cout / cin / ofstream
// without the std:: prefix.
// ============================================================================
#pragma once

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

// ---------------------------------------------------------------------------
// Enumerations
// ---------------------------------------------------------------------------
enum class RequestType
{
    NR,     // Normal request   -> served by a General Technician (GT) only
    SR,     // Specialist request -> served by a Specialist Technician (ST) only
    UR      // Urgent request   -> served by a GT first, then an ST
};

enum class TechnicianType
{
    GT,     // General Technician
    ST      // Specialist Technician
};

enum class TicketStatus
{
    NEW,
    WAITING,
    IN_SERVICE,
    COMPLETED,
    CANCELLED
};

// ---------------------------------------------------------------------------
// One cancellation record read from the input file
// ---------------------------------------------------------------------------
struct CancellationRequest
{
    int CT;     // cancellation time
    int RID;    // ID of the request that should be cancelled
};

// ---------------------------------------------------------------------------
// Small helpers that turn an enum into short text (used by the interactive display)
// ---------------------------------------------------------------------------
inline const char* RequestTypeName(RequestType type)
{
    if (type == RequestType::NR) return "NR";
    if (type == RequestType::SR) return "SR";
    return "UR";
}

inline const char* TechnicianTypeName(TechnicianType type)
{
    if (type == TechnicianType::ST) return "ST";
    return "GT";
}
