#include "TechnicianQueue.h"

TechnicianQueue::TechnicianQueue() : head(nullptr), tail(nullptr), count(0) {}

TechnicianQueue::~TechnicianQueue()
{
    clear();
}

void TechnicianQueue::insertTechnician(const Technician& technician)
{
    Node* node = new Node;
    node->data = technician;
    node->next = nullptr;

    if (tail == nullptr)
    {
        head = node;
        tail = node;
    }
    else
    {
        tail->next = node;
        tail = node;
    }
    count++;
}

// Returns a pointer to the technician stored inside the queue (not a copy).
Technician* TechnicianQueue::getTechnicianByID(int id)
{
    Node* current = head;
    while (current != nullptr)
    {
        if (current->data.getID() == id) return &current->data;
        current = current->next;
    }
    return nullptr;
}

bool TechnicianQueue::updateTechnician(int id, const Technician& technician)
{
    Technician* found = getTechnicianByID(id);
    if (found == nullptr) return false;

    *found = technician;
    return true;
}

void TechnicianQueue::printWorkingTechnicians(const ProblemConfigurationQueue* configs,
                                              const LocationManager* locations) const
{
    bool anyWorking = false;

    Node* current = head;
    while (current != nullptr)
    {
        const Technician& tech = current->data;
        Ticket* t = tech.getCurrentTicket();

        if (t != nullptr)
        {
            anyWorking = true;
            cout << "  " << TechnicianTypeName(tech.getType()) << " " << tech.getID()
                 << " -> " << RequestTypeName(t->getType()) << " " << t->getRID()
                 << " at " << locations->getLocationName(t->getLID())
                 << ", PC " << t->getPC()
                 << " (" << configs->getCategory(t->getPC()) << ")"
                 << ", ST=" << t->getST()
                 << ", FT=" << t->getFT() << "\n";
        }
        current = current->next;
    }

    if (!anyWorking) cout << "  -\n";
}

int TechnicianQueue::countByType(TechnicianType type) const
{
    int result = 0;
    Node* current = head;
    while (current != nullptr)
    {
        if (current->data.getType() == type) result++;
        current = current->next;
    }
    return result;
}

int TechnicianQueue::getTotalBusyTime() const
{
    int total = 0;
    Node* current = head;
    while (current != nullptr)
    {
        total += current->data.getBusyTime();
        current = current->next;
    }
    return total;
}

double TechnicianQueue::getAverageBusyTime() const
{
    if (count == 0) return 0;
    return (double)getTotalBusyTime() / count;
}

void TechnicianQueue::printBusyTimes(ostream& out) const
{
    if (count == 0)
    {
        out << "none";
        return;
    }

    Node* current = head;
    while (current != nullptr)
    {
        out << "technician " << current->data.getID() << " = " << current->data.getBusyTime();
        if (current->next != nullptr) out << "; ";
        current = current->next;
    }
}

int TechnicianQueue::size() const { return count; }

void TechnicianQueue::clear()
{
    while (head != nullptr)
    {
        Node* next = head->next;
        delete head;
        head = next;
    }
    tail = nullptr;
    count = 0;
}
