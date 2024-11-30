#include "entity_handler.h"
#include "utilities.h"
#include "map.h"
#include <iostream>
#include <algorithm>

void EntityHandler::generateEntities(Map &map)
{
    std::vector<std::pair<int, int>> occupiedTiles;

    std::cout << "TINY_ISLAND: Generating trees..." << std::endl;
    int treeCount = 0;
    while (treeCount < TREE_MAX)
    {
        int possibleCol = Utilities::getRandomInt(0, MAP_COLUMNS - 1);
        int possibleRow = Utilities::getRandomInt(0, MAP_ROWS - 1);

        if (map.tileMap[{possibleCol, possibleRow}].state != TileState::Grass) {
            continue;
        }

        if (Utilities::neighborsOfType(map.tileMap, {possibleCol, possibleRow}, TileState::Sand) > 0) {
            continue;
        }

        bool alreadyOccupied = false;
        for (std::pair<int, int> coords : occupiedTiles) {
            if (coords == std::make_pair(possibleCol, possibleRow)) {
                alreadyOccupied = true;
            }
        }

        if (alreadyOccupied) {continue;}

        int possibleX = (possibleCol * tileSize) + Utilities::getRandomInt(-tileSize / 2, tileSize / 2) + tileSize;
        int possibleY = (possibleRow * tileSize) + Utilities::getRandomInt(-tileSize / 2, tileSize / 2) + tileSize;

        if (map.getTileAtWorldCoords(possibleX, possibleY) == TileState::Grass) {
            std::unique_ptr<Tree> thisTree = std::make_unique<Tree>(possibleX - tileSize, possibleY- tileSize); 
            trees.push_back(std::move(thisTree));
            treeCount++;
            if (treeCount >= TREE_MAX) {break;}
            occupiedTiles.push_back({possibleCol, possibleRow});
        }
    }

    std::cout << "TINY_ISLAND: Number of trees generated: " << trees.size() <<std::endl;

}

void EntityHandler::checkEntityCollisions()
{
    for (const auto& entity : visibleEntities) {
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

void EntityHandler::events(Map &map)
{
    checkEntityCollisions();

    for (const auto& entity : visibleEntities) {
        entity->events(map);
    }
}

void EntityHandler::update(Map &map)
{
    visibleEntities.clear();
    visibleEntities.push_back(std::move(player.get()));

    for (const auto& tree : trees)
    {
        tree->update(map);
        if (Utilities::entityShouldRender(map, tree->screenX, tree->screenY)) {
            visibleEntities.push_back(std::move(tree.get()));
        }
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
        Utilities::drawFramerate();
        player->DEBUG_drawWorldCoords();
        player->DEBUG_drawCurrentTile(map);
    }
}
