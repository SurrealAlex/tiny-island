#pragma once

#include "../entity.h"
#include "../../assets/assets.h"
#include "../../map/map.h"

class Tree : public Entity {
    private:
        bool shakeDirection;
        int shakeAnimationCounter;
        int shakeCounter;
        int shakeOffset;
    public:
        bool isBeingShaked;
        bool generatingStick;
        int stickDropChance;
        Tree(int wrldX, int wrldY);

        void events(Map& map) override;
        void update(Map& map) override;
        void draw(Map& map, Assets& assets) override;

        void shake();
};