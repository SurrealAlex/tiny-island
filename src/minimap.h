#pragma once
#include "map.h"
#include "player.h"

class Minimap {
    public:
        bool showing = false;
        int startingX = screenWidth - (MAP_COLUMNS * MINIMAP_SCALE) + MINIMAP_OFFSET_X;
        int startingY = MINIMAP_OFFSET_Y;

        void events();
        void draw(Map& map, Player& player);
};