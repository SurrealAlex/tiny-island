#pragma once

#include <vector>
#include <memory>
#include "mobs/player.h"
#include "world-objects/tree.h"
#include "world-objects/rock.h"
#include "../gui/minimap.h"
#include "../utils/debug.h"
#include "item/item.h"
#include "item/stick.h"
#include "../gui/game-menu.h"

class EntityHandler {
    private:
        std::vector<std::unique_ptr<Tree>> trees;
        std::vector<std::unique_ptr<Rock>> rocks;
        std::vector<std::unique_ptr<Item>> items;
        std::vector<Entity*> visibleEntities;
        Minimap minimap;
    
    public:
        std::unique_ptr<Player> player = std::make_unique<Player>();
        
        void generateEntities(Map& map);
        void checkEntityCollisions();
        void checkForInteractableEntity();
        void checkInteractions();
        void checkItemPickups();
        void spawnWorm(Map& map);
        bool entityShouldRender(Map& map, int screenX, int screenY);

        void events(Map& map);
        void update(Map& map);
        void draw(Map& map, Assets& assets);
};