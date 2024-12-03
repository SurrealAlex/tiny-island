#include <string>
#include <map>

#include "../settings.h"

enum class ItemTier {Crappy, Copper, Iron, Gold};
enum class ToolType {Spade, Chisel, Axe, Pick};

struct InventoryItem {
    std::string name;
    std::string description;
    int id;
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