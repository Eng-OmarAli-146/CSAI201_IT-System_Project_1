#include "WaitingURPriorityQueue.h"

WaitingURPriorityQueue::WaitingURPriorityQueue()
    : items(nullptr), count(0), capacity(0) {}

WaitingURPriorityQueue::~WaitingURPriorityQueue()
{
    clear();
}

// The comparison rule: bigger PR first, then smaller QT, then smaller RID
bool WaitingURPriorityQueue::isBetter(Ticket* a, Ticket* b) const
{
    if (a->getPR() != b->getPR())
        return a->getPR() > b->getPR();

    if (a->getQT() != b->getQT())
        return a->getQT() < b->getQT();

    return a->getRID() < b->getRID();
}

void WaitingURPriorityQueue::grow()
{
    int newCapacity = (capacity == 0) ? 4 : capacity * 2;
    Ticket** bigger = new Ticket*[newCapacity];

    for (int i = 0; i < count; i++)
        bigger[i] = items[i];

    delete[] items;
    items = bigger;
    capacity = newCapacity;
}

void WaitingURPriorityQueue::siftUp(int index)
{
    while (index > 0)
    {
        int parent = (index - 1) / 2;

        if (isBetter(items[index], items[parent]))
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

void WaitingURPriorityQueue::siftDown(int index)
{
    while (true)
    {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int best = index;

        if (leftChild < count && isBetter(items[leftChild], items[best])) best = leftChild;
        if (rightChild < count && isBetter(items[rightChild], items[best])) best = rightChild;

        if (best == index) break;

        Ticket* temp = items[index];
        items[index] = items[best];
        items[best] = temp;
        index = best;
    }
}

void WaitingURPriorityQueue::insert(Ticket* t)
{
    if (count == capacity) grow();

    items[count] = t;
    siftUp(count);
    count++;
}

Ticket* WaitingURPriorityQueue::removeHighest()
{
    if (count == 0) return nullptr;

    Ticket* best = items[0];

    count--;
    items[0] = items[count];
    if (count > 0) siftDown(0);

    return best;
}

Ticket* WaitingURPriorityQueue::peekHighest() const
{
    if (count == 0) return nullptr;
    return items[0];
}

bool WaitingURPriorityQueue::isEmpty() const { return count == 0; }

int WaitingURPriorityQueue::getCount() const { return count; }

// A heap is NOT sorted inside the array, so to print the IDs in scheduling
// order we copy the tickets into a temporary heap and remove them one by one.
// The real heap is never changed.
void WaitingURPriorityQueue::printIDs() const
{
    if (count == 0)
    {
        cout << "-\n";
        return;
    }

    WaitingURPriorityQueue copy;
    for (int i = 0; i < count; i++)
        copy.insert(items[i]);

    while (!copy.isEmpty())
    {
        cout << copy.removeHighest()->getRID();
        if (!copy.isEmpty()) cout << " ";
    }
    cout << "\n";
}

void WaitingURPriorityQueue::clear()
{
    delete[] items;
    items = nullptr;
    capacity = 0;
    count = 0;
}
