// ============================================================================
// ServiceConfiguration.h
// One row of the support-service table: a problem category (B or H) and the
// fixed service duration in minutes. The problem code (pc) is the row number.
// ============================================================================
#pragma once
#include "Definitions.h"

class ServiceConfiguration
{
private:
    int pc{};               // problem code (1, 2, 3, ...)
    string category;        // "B" = basic problem, "H" = hardware problem
    int duration{};         // service duration in minutes

public:
    ServiceConfiguration() = default;
    ServiceConfiguration(int pc, const string& category, int duration);

    int getPC() const;
    const string& getCategory() const;
    int getDuration() const;
};
