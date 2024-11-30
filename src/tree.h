#pragma once
#include "entity.h"
#include "assets.h"
#include "map.h"

class Tree : public Entity {
    public:
        Tree(int wrldX, int wrldY);

        void events(Map& map) override;
        void update(Map& map) override;
        void draw(Map& map, Assets& assets) override;
};