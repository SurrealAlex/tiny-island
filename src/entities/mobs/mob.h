#pragma once
#include "../entity.h"
#include "../../map/map.h"

enum class Facing {North, East, South, West};
enum class SpriteState {Idle, Walk1, Walk2};

class Mob : public Entity {
    public:
        float speed;
        bool willCollide;
        bool isMoving;
        Facing isFacing;
        SpriteState spriteState;
        TileState isStandingOn;
        int spriteCounter;

        virtual ~Mob() {};
        virtual void events(Map& map) = 0;
        virtual void update(Map& map) override = 0;
        virtual void draw(Map& map, Assets& assets) override = 0;
};