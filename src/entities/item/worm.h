#pragma once
#include "item.h"
#include "../../map/utils_map.h"

class Worm : public Item {
    public:
        bool isFlipped;
        float lastTimeDirectionChanged;
        Direction movingIn;
        Worm(Map& map, int wrldX, int wrldY);
        void events(Map& map) override;
        void update(Map& map) override;
        Direction chooseNewDirection(Map& map);
        void draw(Map& map, Assets& assets) override;
};