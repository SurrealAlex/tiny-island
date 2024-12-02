#pragma once

#include "item.h"

#include <map>
#include <vector>

enum class ItemTier {Crappy, Copper, Iron, Gold};

class Craftable : public Item {
    private:
        ItemTier tier;
        std::map<Item, int> craftingRecipe; 
};