#include "game-menu.h"

void GameMenu::events()
{
    if (IsWindowResized()) {
        menuOffsetX = (GetScreenWidth() / 2) - (menuWidth / 2);
        menuOffsetY = (GetScreenHeight() / 2) - (menuHeight / 2);
        menu = {menuOffsetX, menuOffsetY, menuWidth, menuHeight};
    }

    if (IsKeyPressed(KEY_E)) {
        if (!isOpen) {isOpen = true;}
        else {isOpen = false;}
    }
}

void GameMenu::draw(Assets& assets)
{
    if (!isOpen) {return;}
    DrawRectangleRec(menu, menuColor);
    DrawText(headerText, menuOffsetX + slotGap, menuOffsetY + slotGap, 60, WHITE);

    int i = 0;
    float x = menuOffsetX + slotGap;
    float y = menuOffsetY + slotGap + headerGap;

    for (int row = 0; row < slotsPerCol; row++)
    {
        for (int col = 0; col < slotsPerRow; col++)
        {
            Rectangle thisSlot = {x, y, slotSize, slotSize};
            if (col == slotsPerRow - 1) {
                DrawRectangleLinesEx(thisSlot, 2.0f, RED);
            }
            else {
                DrawRectangleLinesEx(thisSlot, 2.0f, slotLineColor);
            }
            if (!inventory.storageSlots[i].name.empty()) {
                DrawTexture(*assets.get(inventory.storageSlots[i].name), thisSlot.x + (thisSlot.width / 4), thisSlot.y + (thisSlot.height / 4), WHITE);
                std::string quantityStr = std::to_string(inventory.storageSlots[i].quantity); 
                const char* c_quantityStr = quantityStr.c_str(); 
                DrawText(c_quantityStr, (thisSlot.x + slotSize - 35), (thisSlot.y + slotSize - 35), 28, WHITE);
            }
            x += slotSize + slotGap;
            i++;
        }
        x = menuOffsetX + slotGap;
        y += slotSize + slotGap;
    }
}
