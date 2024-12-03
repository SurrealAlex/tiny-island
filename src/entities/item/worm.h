#pragma once
#include "item.h"

class Worm : public Item {
    public:
        float speed;
        float timeSpawned;
        float timeAlive;

        Worm(int wrldX, int wrldY);
        void events(Map& map) override;
        void update(Map& map) override;
        void draw(Map& map, Assets& assets) override;
};