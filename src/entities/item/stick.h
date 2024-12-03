#pragma once
#include "item.h"

class Stick : public Item {
    public:
        Stick(int wrldX, int wrldY);
        void events(Map& map) override;
        void update(Map& map) override;
        void draw(Map& map, Assets& assets) override;
};