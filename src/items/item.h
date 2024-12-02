#include <string>

enum class ItemType {Basic, Tool, Placeable};

class Item {
    std::string name;
    std::string description;
    int quantity;
    bool isPlaceable;
};