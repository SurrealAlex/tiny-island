#pragma once
#include "map.h"
#include "assets.h"
#include <vector>
#include <raylib.h>

enum class Facing {Up, Left, Down, Right};

class Entity {
    public:
        float width, height;
        int worldX, worldY;
        float screenX, screenY;
        int zIndex;
        Rectangle hitBox;

        virtual ~Entity() = default;
        virtual void events(Map& map) = 0;
        virtual void update(Map& map) = 0;
        virtual void draw(Map& map, Assets& assets) = 0;
};