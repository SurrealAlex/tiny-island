#pragma once

#include "../inventory/inventory.h"
#include "../assets/assets.h"

#include <raylib.h>

class GameMenu {
    private:
        bool isOpen;
        const char* headerText = "Inventory";

        float headerGap = 90.0f;
        float slotSize = 90.0f;
        int slotGap = 20;
        int slotsPerRow = 9;
        int slotsPerCol = 4;
        float menuWidth = ((slotSize * slotsPerRow) + ((slotGap * slotsPerRow) + slotGap));
        float menuHeight = (headerGap + (slotSize * slotsPerCol) + ((slotGap * slotsPerCol) + slotGap));
        float menuOffsetX = (GetScreenWidth() / 2) - (menuWidth / 2);
        float menuOffsetY = (GetScreenHeight() / 2) - (menuHeight / 2);
        Rectangle menu = {menuOffsetX, menuOffsetY, menuWidth, menuHeight};
        Color menuColor = {65, 65, 65, 255};
        Color slotLineColor = {76, 139, 212, 255};
        Color slotHoverColor = {85, 85, 85, 255};


    public:
        Inventory& inventory;
        GameMenu(Inventory& inventoryRef) : inventory(inventoryRef) {}
        void events();
        void draw(Assets& assets);
};