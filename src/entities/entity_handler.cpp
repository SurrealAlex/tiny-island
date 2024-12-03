#include "entity_handler.h"
#include "../utils/math_utils.h"
#include "../map/utils_map.h"
#include "../map/map.h"
#include "item/stick.h"
#include <iostream>
#include <algorithm>
#include <math.h>

void EntityHandler::generateEntities(Map &map)
{
    std::vector<std::pair<int, int>> occupiedTiles;

    std::cout << "TINY_ISLAND: Generating trees..." << std::endl;
    int treeCount = 0;
    while (treeCount < TREE_MAX)
    {
        int possibleCol = MathUtils::getRandomInt(0, MAP_COLUMNS - 1);
        int possibleRow = MathUtils::getRandomInt(0, MAP_ROWS - 1);

        if (map.tileMap[{possibleCol, possibleRow}].state != TileState::Grass) {
            continue;
        }

        if (MapUtils::neighborsOfType(map, {possibleCol, possibleRow}, TileState::Sand) > 0) {
            continue;
        }

        bool alreadyOccupied = false;
        for (std::pair<int, int> coords : occupiedTiles) {
            if (coords == std::make_pair(possibleCol, possibleRow)) {
                alreadyOccupied = true;
            }
        }

        if (alreadyOccupied) {continue;}

        int possibleX = (possibleCol * tileSize) + MathUtils::getRandomInt(-tileSize / 3, tileSize / 3) + tileSize;
        int possibleY = (possibleRow * tileSize) + MathUtils::getRandomInt(-tileSize / 3, tileSize / 3) + tileSize;

        if (MapUtils::getTileAtWorldCoords(map, {possibleX, possibleY}).state == TileState::Grass) {
            std::unique_ptr<Tree> thisTree = std::make_unique<Tree>(possibleX - tileSize, possibleY- tileSize); 
            trees.push_back(std::move(thisTree));
            treeCount++;
            occupiedTiles.push_back({possibleCol, possibleRow});
            if (treeCount >= TREE_MAX) {break;}
        }
    }

    std::cout << "TINY_ISLAND: Generating rocks..." << std::endl;
    int rockCount = 0;
    while (rockCount < ROCK_MAX) 
    {
        int possibleCol = MathUtils::getRandomInt(0, MAP_COLUMNS - 1);
        int possibleRow = MathUtils::getRandomInt(0, MAP_ROWS - 1);

        if (map.tileMap[{possibleCol, possibleRow}].state != TileState::Grass) {
            continue;
        }
        bool alreadyOccupied = false;
        for (std::pair<int, int> coords : occupiedTiles) {
            if (coords == std::make_pair(possibleCol, possibleRow)) {
                alreadyOccupied = true;
            }
        }

        if (alreadyOccupied) {continue;}

        int possibleX = (possibleCol * tileSize) + tileSize;
        int possibleY = (possibleRow * tileSize) + tileSize;
        std::unique_ptr<Rock> thisRock = std::make_unique<Rock>(possibleX - tileSize, possibleY- tileSize); 
        rocks.push_back(std::move(thisRock));
        rockCount++;
        occupiedTiles.push_back({possibleCol, possibleRow});
        if (rockCount >= ROCK_MAX) {break;}
    }

}

void EntityHandler::checkEntityCollisions()
{
    for (const auto& entity : visibleEntities) 
    {
        if (dynamic_cast<Player*>(entity)) {
            continue;
        }
        Rectangle newHitBox;
        if (IsKeyDown(KEY_W)) {
            newHitBox = {entity->hitBox.x, entity->hitBox.y + player->sprintSpeed, entity->hitBox.width, entity->hitBox.height};
        }
        if (IsKeyDown(KEY_A)) {
            newHitBox = {entity->hitBox.x + player->sprintSpeed, entity->hitBox.y, entity->hitBox.width, entity->hitBox.height};
        }
        if (IsKeyDown(KEY_S)) {
            newHitBox = {entity->hitBox.x, entity->hitBox.y - player->sprintSpeed, entity->hitBox.width, entity->hitBox.height};
        }
        if (IsKeyDown(KEY_D)) {
            newHitBox = {entity->hitBox.x - player->sprintSpeed, entity->hitBox.y, entity->hitBox.width, entity->hitBox.height};
        }
        if (CheckCollisionRecs(player->hitBox, newHitBox)) {
            player->willCollide = true;
            break;
        }
        else {
            player->willCollide = false;
        }
    }
}

void EntityHandler::checkForInteractableEntity()
{
    for (const auto& entity : visibleEntities)
    {
        if (dynamic_cast<Player*>(entity)) {
            continue;
        }

        int deltaX = entity->centerPoint.x - player->centerPoint.x;
        int deltaY = entity->centerPoint.y - player->centerPoint.y;
        float angle = MathUtils::findAngleinDegrees(deltaX, deltaY);

        if (!((deltaX < NDT && deltaX > -NDT) && (deltaY < NDT && deltaY > -NDT))) {
            continue;
        }

        switch(player->isFacing)
        {
            case Facing::North:
                if (angle < -45 && angle > -135) {
                    player->interactableEntity = entity;
                }
                break;
            case Facing::East:
                if (angle > -45 && angle < 45) {
                    player->interactableEntity = entity;
                }
                break;
            case Facing::South:
                if (angle > 45 && angle < 135) {
                    player->interactableEntity = entity;
                }
                break;
            case Facing::West:
                if (angle > 135 || angle < -135) {
                    player->interactableEntity = entity;
                }
        }
        break;
    }
}

void EntityHandler::checkInteractions()
{
    if (Tree* tree = dynamic_cast<Tree*>(player->interactableEntity)) {
        if (!tree->isBeingShaked) {
            return;
        }
        if (MathUtils::getRandomInt(1, tree->stickDropChance) != tree->stickDropChance) {
            return;
        }
        tree->stickDropChance = tree->stickDropChance * 2;
        if (tree->stickDropChance >= 64) {
            tree->stickDropChance = 2;
        }
        int spawnOffsetX = MathUtils::getRandomInt((TILE_SCALE * 4), tileSize - (TILE_SCALE * 4));
        std::unique_ptr<Stick> newStick = std::make_unique<Stick>(tree->worldX + spawnOffsetX, tree->worldY + 20);
        items.push_back(std::move(newStick));
    }
}

void EntityHandler::checkItemPickups()
{
    for (auto it = visibleEntities.begin(); it != visibleEntities.end(); it++) {
        Entity* entity = *it;

        if (!dynamic_cast<Item*>(entity)) {
            continue;
        }

        if (!CheckCollisionCircleRec({entity->centerPoint.x, entity->centerPoint.y}, 10.0f, player->hitBox)) {
            continue;
        }

        if (player->inventory.isFull()) {
            continue;
        }

        player->inventory.addItem({entity->name, 0}, 1);
        std::cout << "You now have " << player->inventory.storageSlots[0].quantity << " " << player->inventory.storageSlots[0].name << std::endl;

        it = visibleEntities.erase(it);
        for (auto itemIt = items.begin(); itemIt != items.end(); ++itemIt) {
            if (itemIt->get() == entity) {
                items.erase(itemIt);
                break;
            }
        }
        break;
    }
}

bool EntityHandler::entityShouldRender(Map& map, int screenX, int screenY)
{
    if (screenX > GetScreenWidth()) {return false;}
    if (screenX < 0 - tileSize) {return false;}
    if (screenY > GetScreenHeight()) {return false;}
    if (screenY < 0 - tileSize) {return false;}
    return true;
}

void EntityHandler::events(Map &map)
{
    minimap.events();
    checkEntityCollisions();
    checkItemPickups();

    for (const auto& entity : visibleEntities) {
        entity->events(map);
    }
}

void EntityHandler::update(Map &map)
{
    visibleEntities.clear();
    visibleEntities.push_back(std::move(player.get()));
    player->interactableEntity = nullptr;

    for (const auto& tree : trees)
    {
        tree->update(map);
        if (entityShouldRender(map, tree->screenX, tree->screenY)) {
            visibleEntities.push_back(std::move(tree.get()));
        }
    }

    for (const auto& rock : rocks)
    {
        rock->update(map);
        if (entityShouldRender(map, rock->screenX, rock->screenY)) {
            visibleEntities.push_back(std::move(rock.get()));
        }
    }

    for (const auto& item : items)
    {
        item->update(map);
        if (entityShouldRender(map, item->screenX, item->screenY)) {
            visibleEntities.push_back(std::move(item.get()));
        }
    }

    checkForInteractableEntity();
    if (IsKeyPressed(KEY_SPACE) && player->interactableEntity != nullptr) {
        checkInteractions();
    }

    player->update(map);

    std::sort(visibleEntities.begin(), visibleEntities.end(), [](const Entity* a, Entity* b) {
        return a->zIndex < b->zIndex;
    });
}

void EntityHandler::draw(Map &map, Assets &assets)
{
    for (const auto& entity: visibleEntities) {
        entity->draw(map, assets);
    }

    if (SHOW_DEBUG_MENU) {
        DrawRectangle(10, 10, 100, 90, {0, 0, 0, 120});
        DebugTools::drawFramerate();
        player->DEBUG_drawWorldCoords();
        player->DEBUG_drawCurrentTile(map);
    }

    minimap.draw(map, *player);
}
