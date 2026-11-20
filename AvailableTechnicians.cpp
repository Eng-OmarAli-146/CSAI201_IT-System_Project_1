#include "AvailableTechnicians.h"

AvailableTechnicians::AvailableTechnicians() : items(nullptr), count(0), capacity(0) {}

AvailableTechnicians::~AvailableTechnicians()
{
    clear();
}

void AvailableTechnicians::grow()
{
    int newCapacity = (capacity == 0) ? 4 : capacity * 2;
    Technician** bigger = new Technician*[newCapacity];

    for (int i = 0; i < count; i++)
        bigger[i] = items[i];

    delete[] items;
    items = bigger;
    capacity = newCapacity;
}

// Heap index rules:  parent = (i - 1) / 2,  children = 2i + 1 and 2i + 2
void AvailableTechnicians::siftUp(int index)
{
    while (index > 0)
    {
        int parent = (index - 1) / 2;

        if (items[index]->getID() < items[parent]->getID())
        {
            Technician* temp = items[index];
            items[index] = items[parent];
            items[parent] = temp;
            index = parent;
        }
        else
        {
            break;      // the heap rule is already satisfied
        }
    }
}

void AvailableTechnicians::siftDown(int index)
{
    while (true)
    {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int smallest = index;

        if (leftChild < count && items[leftChild]->getID() < items[smallest]->getID())
            smallest = leftChild;
        if (rightChild < count && items[rightChild]->getID() < items[smallest]->getID())
            smallest = rightChild;

        if (smallest == index) break;       // no child is smaller: done

        Technician* temp = items[index];
        items[index] = items[smallest];
        items[smallest] = temp;
        index = smallest;
    }
}

void AvailableTechnicians::insert(Technician* t)
{
    if (count == capacity) grow();

    items[count] = t;       // put it at the end ...
    siftUp(count);          // ... then move it up to its place
    count++;
}

Technician* AvailableTechnicians::peekMin() const
{
    if (count == 0) return nullptr;
    return items[0];
}

Technician* AvailableTechnicians::extractMin()
{
    if (count == 0) return nullptr;

    Technician* smallest = items[0];

    count--;
    items[0] = items[count];        // move the last one to the root ...
    if (count > 0) siftDown(0);     // ... then move it down to its place

    return smallest;
}

bool AvailableTechnicians::isEmpty() const { return count == 0; }

int AvailableTechnicians::getCount() const { return count; }

void AvailableTechnicians::print() const
{
    if (count == 0)
    {
        cout << "-\n";
        return;
    }

    for (int i = 0; i < count; i++)
    {
        cout << items[i]->getID();
        if (i < count - 1) cout << " ";
    }
    cout << "\n";
}

void AvailableTechnicians::clear()
{
    delete[] items;     // the technicians themselves belong to TechnicianQueue
    items = nullptr;
    capacity = 0;
    count = 0;
}
