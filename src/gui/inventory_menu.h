#pragma once
#include <raylib.h>
#include "../inventory/inventory.h"
#include "../assets/assets.h"

class InventoryMenu {
    private:
        bool isOpen = false;
        Rectangle overlay = {0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()};
        Color overlayColor = {25, 25, 25, 225};

        Color slotColor = {83, 194, 186, 255};
        Color slotColorHover = {45, 45, 45, 225};

        int inventoryRows = 4;
        int inventoryCols = 9;
        float squareSize = 100;
        float squareGap = 25;
        int menuRowWidth = (squareSize + squareGap) * inventoryCols;
        int menuColHeight = (squareSize + squareGap) * inventoryRows;
        int menuOffsetX = GetScreenWidth() / 2 - menuRowWidth / 2;
        int menuOffsetY = GetScreenHeight() / 2 - menuColHeight / 2;

    public:
        Inventory& inventory;
        InventoryMenu(Inventory& inventoryRef) : inventory(inventoryRef) {}
        void events();
        void update();
        void draw(Assets& assets);
};