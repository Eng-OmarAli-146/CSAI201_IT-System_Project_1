// ============================================================================
// InputReader.h
// Reads the input file and keeps every record in the structure that suits it.
// The Simulation later gets pointers to these structures.
// ============================================================================
#pragma once
#include "Definitions.h"
#include "LocationManager.h"
#include "ProblemConfigurationQueue.h"
#include "TechnicianQueue.h"
#include "Ticket.h"
#include "RequestQueue.h"
#include "CancellationQueue.h"

class InputReader
{
private:
    string fileName;

    LocationManager           locations;
    ProblemConfigurationQueue configurations;
    TechnicianQueue           technicians;
    RequestQueue              allRequests;
    CancellationQueue         allCancellations;

    // how many input requests of each type were accepted (used by the statistics)
    int nrTotal;
    int srTotal;
    int urTotal;

    static RequestType parseRequestType(const string& value);

public:
    explicit InputReader(const string& fileName);

    bool LoadFile();                                // false if reading failed
    bool LoadLocations(istream& input);
    bool LoadConfigurations(istream& input);
    bool LoadTechnicians(istream& input);
    bool LoadRequests(istream& input);
    bool LoadCancellations(istream& input);

    LocationManager*           getLocations();
    ProblemConfigurationQueue* getConfigurations();
    TechnicianQueue*           getTechnicians();
    RequestQueue*              getRequests();
    CancellationQueue*         getCancellations();

    int getNRTotal() const;
    int getSRTotal() const;
    int getURTotal() const;
};
