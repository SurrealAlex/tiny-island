#pragma once

#include "../settings.h"

#include <raylib.h>

class Hud {
    private:
        char itemTriangleSelection;
        Rectangle itemTriangle[4] = {
            {GetScreenWidth() - 216.0f, GetScreenHeight() - 216.0f, 100, 100}, //i slot
            {GetScreenWidth() - 324.0f, GetScreenHeight() - 108.0f, 100, 100}, //j slot
            {GetScreenWidth() - 216.0f, GetScreenHeight() - 108.0f, 100, 100}, //k slot
            {GetScreenWidth() - 108.0f, GetScreenHeight() - 108.0f, 100, 100} //l slot
        };

    public:
        void events();
        void update();
        void draw();
};