#include "InServicePriorityQueue.h"

InServicePriorityQueue::InServicePriorityQueue() : items(nullptr), count(0), capacity(0) {}

InServicePriorityQueue::~InServicePriorityQueue()
{
    clear();
}

// Order: smaller FT first, then smaller RID
bool InServicePriorityQueue::isBefore(Ticket* a, Ticket* b) const
{
    if (a->getFT() != b->getFT())
        return a->getFT() < b->getFT();

    return a->getRID() < b->getRID();
}

void InServicePriorityQueue::grow()
{
    int newCapacity = (capacity == 0) ? 4 : capacity * 2;
    Ticket** bigger = new Ticket*[newCapacity];

    for (int i = 0; i < count; i++)
        bigger[i] = items[i];

    delete[] items;
    items = bigger;
    capacity = newCapacity;
}

void InServicePriorityQueue::siftUp(int index)
{
    while (index > 0)
    {
        int parent = (index - 1) / 2;

        if (isBefore(items[index], items[parent]))
        {
            Ticket* temp = items[index];
            items[index] = items[parent];
            items[parent] = temp;
            index = parent;
        }
        else
        {
            break;
        }
    }
}

void InServicePriorityQueue::siftDown(int index)
{
    while (true)
    {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int first = index;

        if (leftChild < count && isBefore(items[leftChild], items[first])) first = leftChild;
        if (rightChild < count && isBefore(items[rightChild], items[first])) first = rightChild;

        if (first == index) break;

        Ticket* temp = items[index];
        items[index] = items[first];
        items[first] = temp;
        index = first;
    }
}

// Linear scan: the heap is ordered by FT, not by RID, so we must look at every ticket.
int InServicePriorityQueue::findIndex(int RID) const
{
    for (int i = 0; i < count; i++)
        if (items[i]->getRID() == RID) return i;

    return -1;
}

void InServicePriorityQueue::insert(Ticket* t)
{
    if (count == capacity) grow();

    items[count] = t;
    siftUp(count);
    count++;
}

Ticket* InServicePriorityQueue::peek() const
{
    if (count == 0) return nullptr;
    return items[0];
}

Ticket* InServicePriorityQueue::extractMin()
{
    if (count == 0) return nullptr;

    Ticket* first = items[0];

    count--;
    items[0] = items[count];
    if (count > 0) siftDown(0);

    return first;
}

Ticket* InServicePriorityQueue::getByID(int RID) const
{
    int index = findIndex(RID);
    if (index < 0) return nullptr;
    return items[index];
}

// Remove a ticket from the middle of the heap, then repair the heap order.
Ticket* InServicePriorityQueue::removeByID(int RID)
{
    int index = findIndex(RID);
    if (index < 0) return nullptr;

    Ticket* removed = items[index];

    count--;
    items[index] = items[count];    // the last ticket takes the empty place

    if (index < count)
    {
        siftUp(index);      // the moved ticket may belong higher ...
        siftDown(index);    // ... or lower in the heap
    }

    return removed;
}

bool InServicePriorityQueue::isEmpty() const { return count == 0; }

int InServicePriorityQueue::getCount() const { return count; }

void InServicePriorityQueue::clear()
{
    delete[] items;
    items = nullptr;
    capacity = 0;
    count = 0;
}
