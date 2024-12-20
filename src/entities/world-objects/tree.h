#pragma once

#include "../entity.h"
#include "../../assets/assets.h"
#include "../../map/map.h"

enum class TreeType {Oak, Palm};

class Tree : public Entity {
    private:
        bool shakeDirection;
        int shakeAnimationCounter;
        int shakeCounter;
        int shakeOffset;

    public:
        bool isBeingShaked;
        bool generatingDrop;
        int dropChance;
        TreeType type;

        Tree(TreeType type, int wrldX, int wrldY);
        void events(Map& map) override;
        void update(Map& map) override;
        void draw(Map& map, Assets& assets) override;

        void shake();
};