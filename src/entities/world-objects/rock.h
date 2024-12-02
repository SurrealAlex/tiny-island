#pragma once
#include "../entity.h"
#include "../../assets/assets.h"
#include "../../map/map.h"

class Rock : public Entity {
    public:
        Rock(int wrldX, int wrldY);

        void events(Map& map) override;
        void update(Map& map) override;
        void draw(Map& map, Assets& assets) override;
};