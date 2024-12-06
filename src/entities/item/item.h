#pragma once

#include "../entity.h"

class Item : public Entity {
    public:
        bool isRested;
        int spawnAnimationCounter;
        float speed;
        float timeSpawned;
        float timeAlive;

        virtual ~Item() = default;
        virtual void events(Map& map) = 0;
        virtual void update(Map& map) = 0;
        virtual void draw(Map& map, Assets& assets) = 0;
};