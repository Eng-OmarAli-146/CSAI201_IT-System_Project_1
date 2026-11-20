#include "WaitingNRQueue.h"

Ticket* WaitingNRQueue::removeByID(int RID)
{
    Node* previous = nullptr;
    Node* current = head;

    while (current != nullptr)
    {
        if (current->data->getRID() == RID)
        {
            Ticket* found = current->data;

            // skip the node: the one before it now points to the one after it
            if (previous == nullptr) head = current->next;      // it was the first node
            else                     previous->next = current->next;

            if (current == tail) tail = previous;               // it was the last node

            delete current;
            count--;
            return found;
        }
        previous = current;
        current = current->next;
    }
    return nullptr;
}
