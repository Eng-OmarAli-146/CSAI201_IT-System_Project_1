// ============================================================================
// ProblemConfigurationQueue.h
// Linked FIFO queue of the service configurations (category + duration).
// The problem code (PC) is the POSITION of the row in this queue (1, 2, 3 ...),
// so reading a configuration means walking the queue until that position.
// ============================================================================
#pragma once
#include "Definitions.h"
#include "ServiceConfiguration.h"

class ProblemConfigurationQueue
{
private:
    struct Node
    {
        ServiceConfiguration data;
        Node* next;
    };

    Node* head;
    Node* tail;
    int count;

public:
    ProblemConfigurationQueue();
    ~ProblemConfigurationQueue();

    void insertConfiguration(const ServiceConfiguration& configuration);   // O(1)
    const ServiceConfiguration* getConfigurationByPC(int pc) const;        // O(K)
    int    getDuration(int pc) const;                                      // O(K)
    string getCategory(int pc) const;                                      // O(K)

    // true if the problem code exists and its category fits the request type:
    //   NR and UR need category B, SR needs category H
    bool validateTicket(int pc, RequestType type) const;                   // O(K)

    void print() const;                                                    // O(K)
    int  size() const;
    void clear();                                                          // O(K)
};
