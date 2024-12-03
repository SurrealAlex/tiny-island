#pragma once

#include <string>
#include <map>

#include "../settings.h"

enum class ItemTier {Crappy, Copper, Iron, Gold};
enum class ToolType {Spade, Chisel, Axe, Pick};

struct InventoryItem {
    std::string name;
    int quantity;
};

struct Craftable : InventoryItem {
    ItemTier tier;
    std::map<int, InventoryItem> craftingRecipe;
};

struct Tool : Craftable {
    ToolType type;
    int maxDurability;
    int nowDurability;
};

class Inventory {
    public:
        InventoryItem storageSlots[INVENTORY_SIZE];
        Tool equipSlots[4];
        void addItem(std::string name, int howMany);
        bool isFull();
        bool isEmpty();
};