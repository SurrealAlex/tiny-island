#include "inventory_menu.h"

void InventoryMenu::events()
{
    if (IsKeyPressed(KEY_E)) {
        if (isOpen) {isOpen = false;}
        else {isOpen = true;}
    }
}

void InventoryMenu::update()
{
    if (!IsWindowResized()) {
        return;
    }
    overlay = {0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()};
    menuOffsetX = GetScreenWidth() / 2 - menuRowWidth / 2;
    menuOffsetY = GetScreenHeight() / 2 - menuColHeight / 2;
}

void InventoryMenu::draw(Assets& assets)
{
    if (!isOpen) {
        return;
    }

    DrawRectangle(overlay.x, overlay.y, overlay.width, overlay.height, overlayColor);
    float x = 0 + menuOffsetX;
    float y = 0 + menuOffsetY;
    int slotIndex = 0;
    
    for (int row = 0; row < inventoryRows; row++)
    {
        for (int col = 0; col < inventoryCols; col++)
        {
            Rectangle thisSquare = {x, y, squareSize, squareSize};
            bool isHovering = CheckCollisionPointRec({(float)GetMouseX(), (float)GetMouseY()}, thisSquare);

            if (isHovering) {
                DrawRectangleRec(thisSquare, slotColorHover);
            }
            DrawRectangleLinesEx(thisSquare, 2.0f, slotColor);

            if (!inventory.storageSlots[slotIndex].name.empty()) {
                DrawTexture(*assets.get(inventory.storageSlots[slotIndex].name), thisSquare.x + 25, thisSquare.y + 25, WHITE);
                std::string quantityStr = std::to_string(inventory.storageSlots[slotIndex].quantity); 
                const char* c_quantityStr = quantityStr.c_str(); 
                DrawText(c_quantityStr, (thisSquare.x + squareSize - 30), (thisSquare.y + squareSize - 30), 24, WHITE);
            }

            x += squareSize + squareGap;
            slotIndex++;
        }
    x = 0 + menuOffsetX;
    y += squareSize + squareGap;
    }
}
