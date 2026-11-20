#include "CancellationQueue.h"

CancellationQueue::CancellationQueue() : head(nullptr), tail(nullptr), count(0) {}

CancellationQueue::~CancellationQueue()
{
    clear();
}

void CancellationQueue::enqueue(const CancellationRequest& request)
{
    Node* node = new Node;
    node->data = request;
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

// Copies the front record into "request" and removes it from the queue.
bool CancellationQueue::dequeue(CancellationRequest& request)
{
    if (head == nullptr) return false;

    Node* node = head;
    request = node->data;

    head = head->next;
    if (head == nullptr) tail = nullptr;

    delete node;
    count--;
    return true;
}

// Copies the front record into "request" WITHOUT removing it.
bool CancellationQueue::peek(CancellationRequest& request) const
{
    if (head == nullptr) return false;

    request = head->data;
    return true;
}

bool CancellationQueue::isEmpty() const { return count == 0; }

int CancellationQueue::getCount() const { return count; }

void CancellationQueue::print() const
{
    if (head == nullptr)
    {
        cout << "-\n";
        return;
    }

    Node* current = head;
    while (current != nullptr)
    {
        cout << "(CT=" << current->data.CT << ", RID=" << current->data.RID << ")";
        if (current->next != nullptr) cout << " ";
        current = current->next;
    }
    cout << "\n";
}

void CancellationQueue::clear()
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
