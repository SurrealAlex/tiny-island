#include "inventory.h"

void Inventory::addItem(std::string name, int howMany)
{
    for (auto& slot : storageSlots)
    {
        if (isFull()) {
            return;
        }
        if (slot.name.empty()) {
            slot.name = name;
            slot.quantity = howMany;
            return;
        }
        else if (slot.name == name) {
            if (slot.quantity >= 25) {
                slot.quantity = 25;
                continue;
            }
            slot.quantity += howMany;
            return;
        }
    }
}

bool Inventory::isFull()
{
    for (const auto& slot : storageSlots)
    {
        if (slot.name.empty()) {
            return false;
        }
    }
    return true;
}

bool Inventory::isEmpty()
{
    for (const auto& slot : storageSlots)
    {
        if (!slot.name.empty()) {
            return false;
        }
    }

    return true;
}
