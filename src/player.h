#pragma once
#include "assets.h"
#include "entity.h"
#include "settings.h"
#include "map.h"
#include <raylib.h>

enum class SpriteState {Idle, Walk1, Walk2};

class Player : public Entity {

    private:
        bool isMoving;
        Facing facing;
        SpriteState spriteState;
        int spriteCounter;
        TileState standingOn;
    
    public:
        int speed, sprintSpeed;
        bool willCollide;

        Player();
        void DEBUG_drawWorldCoords();
        void DEBUG_drawCurrentTile(Map& map);

        bool checkWaterCollision(Map& map, int speed, Facing direction);

        void events(Map& map) override;
        void update(Map& map) override;
        void draw(Map& map, Assets& assets) override;
};