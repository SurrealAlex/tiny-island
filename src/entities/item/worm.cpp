#include "worm.h"
#include "../../utils/math_utils.h"
#include <iostream>

Worm::Worm(Map& map, int wrldX, int wrldY)
{
    name = "Worm";
    timeSpawned = GetTime();
    width = tileSize / 4;
    height = tileSize / 4;
    worldX = wrldX;
    worldY = wrldY;
    screenX = -worldX;
    screenY = -worldY;
    centerPoint = {screenX + (width / 2), screenY + (height / 2)};

    isRested = true;
    lastTimeDirectionChanged = 0;
    spawnAnimationCounter = 0;
    speed = 1.0f;
    movingIn = chooseNewDirection(map);
}

void Worm::events(Map &map)
{
    return;
}

void Worm::update(Map &map)
{
    spawnAnimationCounter++;
    if (spawnAnimationCounter < 15) {
        isFlipped = false;
    }
    else {
        isFlipped = true;
    }
    if (spawnAnimationCounter > 30) {
        spawnAnimationCounter = 0;
    }

    TileCoords currentTile;
    switch(movingIn)
    {
        case Direction::North:
            currentTile = MapUtils::getTileCoordsAtWorldCoords(map, {worldX, worldY + (tileSize / 2)});
            break;
        case Direction::South:
            currentTile = MapUtils::getTileCoordsAtWorldCoords(map, {worldX, worldY - (tileSize / 2)});
            break;
        case Direction::East:
            currentTile = MapUtils::getTileCoordsAtWorldCoords(map, {worldX - (tileSize / 2), worldY});
            break;
        case Direction::West:
            currentTile = MapUtils::getTileCoordsAtWorldCoords(map, {worldX + (tileSize / 2), worldY});
            break;
        default:
            break;
    }
     
    if (map.tileMap[MapUtils::getNeighborCoords(currentTile, movingIn)].state != TileState::Sand) {
        movingIn = chooseNewDirection(map);
    }

    switch(movingIn)
    {
        case Direction::North:
            worldY -= speed;
            break;
        case Direction::East:
            worldX += speed;
            break;
        case Direction::South:
            worldY += speed;
            break;
        case Direction::West:
            worldX -= speed;
            break;
        default:
            break;
    }

    screenX = worldX + map.getOffsetX();
    screenY = worldY + map.getOffsetY();
    zIndex = screenY - (tileSize / 2);
    centerPoint = {screenX + (width / 2), screenY + (height / 2)};
}

Direction Worm::chooseNewDirection(Map& map)
{
    TileCoords currentTile = MapUtils::getTileCoordsAtWorldCoords(map, {((float)worldX) + width, ((float)worldY) + height});
    std::vector<Direction> possibleDirections = MapUtils::getDirectionToTileState(map, currentTile, TileState::Sand);
    int index = MathUtils::getRandomInt(0, (int)possibleDirections.size() - 1);
    Direction chosenDirection = possibleDirections[index];
    return chosenDirection;
}

void Worm::draw(Map &map, Assets &assets)
{
    if (!isFlipped) {DrawTexture(*assets.get("Worm"), screenX, screenY, WHITE);}
    else {DrawTexture(*assets.get("Worm2"), screenX, screenY, WHITE);}
}
