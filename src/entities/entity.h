#pragma once
#include "../map/map.h"
#include "../assets/assets.h"
#include <vector>
#include <raylib.h>

struct ScreenCoords {
    float x, y;
};

class Entity {
    public:
        std::string name;
        float width, height;
        int worldX, worldY;
        float screenX, screenY;
        ScreenCoords centerPoint;
        int zIndex;
        Rectangle hitBox;

        virtual ~Entity() = default;
        virtual void events(Map& map) = 0;
        virtual void update(Map& map) = 0;
        virtual void draw(Map& map, Assets& assets) = 0;
};