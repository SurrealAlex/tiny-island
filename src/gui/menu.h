#pragma once
#include <raylib.h>

class Menu {
    private:
        bool isOpen = false;
        Rectangle overlay = {0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()};
        Color overlayColor = {25, 25, 25, 175};

    public:
        void events();
        void update();
        void draw();
};