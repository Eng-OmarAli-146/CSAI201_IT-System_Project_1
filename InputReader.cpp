#include "InputReader.h"

InputReader::InputReader(const string& fileName)
    : fileName(fileName), nrTotal(0), srTotal(0), urTotal(0) {}

RequestType InputReader::parseRequestType(const string& value)
{
    if (value == "SR" || value == "sr") return RequestType::SR;
    if (value == "UR" || value == "ur") return RequestType::UR;
    return RequestType::NR;
}

// Reads the five parts of the file in the order of the project description.
bool InputReader::LoadFile()
{
    ifstream input(fileName.c_str());
    if (!input.is_open())
    {
        cout << "Cannot open input file: " << fileName << "\n";
        return false;
    }

    bool ok = LoadLocations(input) &&
              LoadConfigurations(input) &&
              LoadTechnicians(input) &&
              LoadRequests(input) &&
              LoadCancellations(input);

    if (!ok)
        cout << "The input file is not in the expected format: " << fileName << "\n";

    return ok;
}

// L, then L location tokens. The location ID is the row number (1, 2, 3 ...).
bool InputReader::LoadLocations(istream& input)
{
    int count;
    if (!(input >> count) || count < 0) return false;

    for (int i = 0; i < count; ++i)
    {
        string name;
        if (!(input >> name)) return false;
        locations.addLocation(Location(i + 1, name));
    }
    return true;
}

// K, then K rows "category duration". The problem code is the row number.
bool InputReader::LoadConfigurations(istream& input)
{
    int count;
    if (!(input >> count) || count < 0) return false;

    for (int i = 0; i < count; ++i)
    {
        string category;
        int duration;
        if (!(input >> category >> duration)) return false;
        configurations.insertConfiguration(ServiceConfiguration(i + 1, category, duration));
    }
    return true;
}

// One line with the two counts: ST_count GT_count
bool InputReader::LoadTechnicians(istream& input)
{
    int stCount;
    int gtCount;
    if (!(input >> stCount >> gtCount) || stCount < 0 || gtCount < 0) return false;

    // IDs increase: all ST technicians first, then all GT technicians
    int id = 1;
    for (int i = 0; i < stCount; ++i)
        technicians.insertTechnician(Technician(id++, TechnicianType::ST));

    for (int i = 0; i < gtCount; ++i)
        technicians.insertTechnician(Technician(id++, TechnicianType::GT));

    return true;
}

// R, then R rows: TYPE QT RID LID PC   (and PR only for UR)
bool InputReader::LoadRequests(istream& input)
{
    int count;
    if (!(input >> count) || count < 0) return false;

    for (int i = 0; i < count; ++i)
    {
        string type;
        if (!(input >> type)) return false;
        RequestType requestType = parseRequestType(type);

        int qt, rid, lid, pc;
        if (!(input >> qt >> rid >> lid >> pc)) return false;

        int pr = 0;                       // only UR tickets have a priority
        if (requestType == RequestType::UR && !(input >> pr)) return false;

        // NR and UR must use a category B problem code, SR a category H one,
        // and the location must exist. A bad record is skipped with a warning.
        if (!locations.isValid(lid) || !configurations.validateTicket(pc, requestType))
        {
            cout << "Warning: request " << rid << " was skipped "
                 << "(unknown location or problem code that does not fit its type).\n";
            continue;
        }

        allRequests.enqueue(new Ticket(rid, qt, lid, pc, pr, requestType));
        locations.incrementTicketCount(lid);        // for "tickets by location"

        if (requestType == RequestType::NR)      nrTotal++;
        else if (requestType == RequestType::SR) srTotal++;
        else                                     urTotal++;
    }
    return true;
}

// C, then C rows: CT RID
bool InputReader::LoadCancellations(istream& input)
{
    int count;
    if (!(input >> count) || count < 0) return false;

    for (int i = 0; i < count; ++i)
    {
        CancellationRequest request;
        if (!(input >> request.CT >> request.RID)) return false;
        allCancellations.enqueue(request);
    }
    return true;
}

LocationManager*           InputReader::getLocations()      { return &locations; }
ProblemConfigurationQueue* InputReader::getConfigurations() { return &configurations; }
TechnicianQueue*           InputReader::getTechnicians()    { return &technicians; }
RequestQueue*              InputReader::getRequests()       { return &allRequests; }
CancellationQueue*         InputReader::getCancellations()  { return &allCancellations; }

int InputReader::getNRTotal() const { return nrTotal; }
int InputReader::getSRTotal() const { return srTotal; }
int InputReader::getURTotal() const { return urTotal; }
