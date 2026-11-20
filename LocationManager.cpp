#include "LocationManager.h"

LocationManager::LocationManager() : items(nullptr), capacity(0), count(0) {}

LocationManager::~LocationManager()
{
    clear();
}

// Make a bigger array, copy the old pointers into it, free the old array.
void LocationManager::grow()
{
    int newCapacity = (capacity == 0) ? 4 : capacity * 2;
    Location** bigger = new Location*[newCapacity];

    for (int i = 0; i < count; i++)
        bigger[i] = items[i];

    delete[] items;
    items = bigger;
    capacity = newCapacity;
}

void LocationManager::addLocation(const Location& location)
{
    if (count == capacity) grow();

    items[count] = new Location(location.getID(), location.getName());
    count++;
}

// ID -> index is simply (id - 1)
const Location* LocationManager::getLocation(int id) const
{
    if (!isValid(id)) return nullptr;
    return items[id - 1];
}

string LocationManager::getLocationName(int id) const
{
    const Location* location = getLocation(id);
    if (location == nullptr) return "";
    return location->getName();
}

bool LocationManager::isValid(int id) const
{
    return id >= 1 && id <= count;
}

void LocationManager::incrementTicketCount(int id)
{
    if (isValid(id)) items[id - 1]->incrementTicketCount();
}

int LocationManager::getTicketCount(int id) const
{
    if (!isValid(id)) return 0;
    return items[id - 1]->getTicketCount();
}

void LocationManager::printCounts(ostream& out) const
{
    for (int id = 1; id <= count; id++)
        out << "Location " << id << ": " << items[id - 1]->getTicketCount() << "\n";
}

int LocationManager::size() const { return count; }

void LocationManager::clear()
{
    for (int i = 0; i < count; i++)
        delete items[i];

    delete[] items;
    items = nullptr;
    capacity = 0;
    count = 0;
}
