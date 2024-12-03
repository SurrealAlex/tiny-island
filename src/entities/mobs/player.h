#pragma once
#include "../../assets/assets.h"
#include "mob.h"
#include "../../settings.h"
#include "../../map/map.h"
#include "../../inventory/inventory.h"
#include <raylib.h>

class Player : public Mob {
    public:
        float sprintSpeed;
        Entity* interactableEntity;
        Inventory inventory;

        Player();
        void DEBUG_drawWorldCoords();
        void DEBUG_drawCurrentTile(Map& map);

        bool checkWaterCollision(Map& map, int speed, Facing direction);

        void events(Map& map) override;
        void update(Map& map) override;
        void draw(Map& map, Assets& assets) override;

        void interact();
};