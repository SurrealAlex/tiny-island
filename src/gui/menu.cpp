#include "menu.h"

void Menu::events()
{
    if (IsKeyPressed(KEY_E)) {
        if (isOpen) {isOpen = false;}
        else {isOpen = true;}
    }
}

void Menu::update() {
    return;
}

void Menu::draw() {
    if (!isOpen) {
        return;
    }

    DrawRectangle(overlay.x, overlay.y, overlay.width, overlay.height, overlayColor);
}