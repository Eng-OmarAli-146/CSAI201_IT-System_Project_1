#include "ProblemConfigurationQueue.h"
#include <cctype>

ProblemConfigurationQueue::ProblemConfigurationQueue()
    : head(nullptr), tail(nullptr), count(0) {}

ProblemConfigurationQueue::~ProblemConfigurationQueue()
{
    clear();
}

// Add a new node at the back of the queue.
void ProblemConfigurationQueue::insertConfiguration(const ServiceConfiguration& configuration)
{
    Node* node = new Node;
    node->data = configuration;
    node->next = nullptr;

    if (tail == nullptr)        // queue was empty
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

// Walk the queue until we reach the pc-th row.
const ServiceConfiguration* ProblemConfigurationQueue::getConfigurationByPC(int pc) const
{
    Node* current = head;
    int position = 1;

    while (current != nullptr)
    {
        if (position == pc) return &current->data;
        current = current->next;
        position++;
    }
    return nullptr;     // no such problem code
}

int ProblemConfigurationQueue::getDuration(int pc) const
{
    const ServiceConfiguration* configuration = getConfigurationByPC(pc);
    if (configuration == nullptr) return 0;
    return configuration->getDuration();
}

string ProblemConfigurationQueue::getCategory(int pc) const
{
    const ServiceConfiguration* configuration = getConfigurationByPC(pc);
    if (configuration == nullptr) return "";
    return configuration->getCategory();
}

bool ProblemConfigurationQueue::validateTicket(int pc, RequestType type) const
{
    const ServiceConfiguration* configuration = getConfigurationByPC(pc);
    if (configuration == nullptr) return false;

    string category = configuration->getCategory();
    if (category.empty()) return false;
    char letter = (char)toupper(category[0]);

    if (type == RequestType::SR) return letter == 'H';
    return letter == 'B';               // NR and UR
}

void ProblemConfigurationQueue::print() const
{
    Node* current = head;
    int position = 1;

    while (current != nullptr)
    {
        cout << "PC " << position << ": " << current->data.getCategory()
             << " " << current->data.getDuration() << " minutes\n";
        current = current->next;
        position++;
    }
}

int ProblemConfigurationQueue::size() const { return count; }

void ProblemConfigurationQueue::clear()
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
