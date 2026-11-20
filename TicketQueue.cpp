#include "TicketQueue.h"

TicketQueue::TicketQueue() : head(nullptr), tail(nullptr), count(0) {}

TicketQueue::~TicketQueue()
{
    clear();
}

void TicketQueue::enqueue(Ticket* t)
{
    Node* node = new Node;
    node->data = t;
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

Ticket* TicketQueue::dequeue()
{
    if (head == nullptr) return nullptr;

    Node* node = head;
    Ticket* t = node->data;

    head = head->next;
    if (head == nullptr) tail = nullptr;    // queue became empty

    delete node;
    count--;
    return t;
}

Ticket* TicketQueue::peek() const
{
    if (head == nullptr) return nullptr;
    return head->data;
}

bool TicketQueue::isEmpty() const { return count == 0; }

int TicketQueue::getCount() const { return count; }

void TicketQueue::printIDs() const
{
    if (head == nullptr)
    {
        cout << "-\n";
        return;
    }

    Node* current = head;
    while (current != nullptr)
    {
        cout << current->data->getRID();
        if (current->next != nullptr) cout << " ";
        current = current->next;
    }
    cout << "\n";
}

Ticket** TicketQueue::toArray(int& size) const
{
    Ticket** items = new Ticket*[count > 0 ? count : 1];

    int i = 0;
    Node* current = head;
    while (current != nullptr)
    {
        items[i] = current->data;
        i++;
        current = current->next;
    }

    size = count;
    return items;
}

void TicketQueue::clear()
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

void TicketQueue::clearAndDeleteTickets()
{
    while (head != nullptr)
    {
        Node* next = head->next;
        delete head->data;
        delete head;
        head = next;
    }
    tail = nullptr;
    count = 0;
}
