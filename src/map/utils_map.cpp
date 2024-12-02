#include "../utils/math_utils.h"
#include "utils_map.h"
#include <iostream>

bool MapUtils::tileWithinNthPerimeter(Map &map, TileCoords coords, int n)
{
    if (coords.col <= n - 1 || coords.row <= n - 1) {
        return true;
    }
    if (coords.col >= map.cols - n || coords.row >= map.rows - n) {
        return true;
    }
    return false;
}

TileCoords MapUtils::getNeighborCoords(TileCoords coords, Direction direction)
{
    switch(direction) {
        case Direction::Northwest:
            return {coords.col - 1, coords.row - 1};
            break;
        case Direction::North:
            return {coords.col, coords.row - 1};
            break;
        case Direction::Northeast:
            return {coords.col + 1, coords.row - 1};
            break;
        case Direction::East:
            return {coords.col + 1, coords.row};
            break;
        case Direction::Southeast:
            return {coords.col + 1, coords.row + 1};
            break;
        case Direction::South:
            return {coords.col, coords.row + 1};
            break;
        case Direction::Southwest:
            return {coords.col - 1, coords.row + 1};
            break;
        case Direction::West:
            return {coords.col - 1, coords.row};
            break;
        default:
            std::cout << "TINY_ISLAND: Error in retrieving tile neighbor coords. Returned original coords.\n";
            return {coords.col, coords.row};
            break;
    }
}

TileCoords MapUtils::getRandomOrthogonalNeighborCoords(TileCoords coords)
{
    int rand = MathUtils::getRandomInt(1, 4);
    switch(rand)
    {
        case 1:
            return getNeighborCoords(coords, Direction::North);
            break;
        case 2:
            return getNeighborCoords(coords, Direction::East);
            break;
        case 3:
            return getNeighborCoords(coords, Direction::South);
            break;
        default:
            return getNeighborCoords(coords, Direction::West);
            break;
    }
}

int MapUtils::neighborsOfType(Map &map, TileCoords coords, TileState stateToCheck)
{
    Direction directions[8] = { Direction::Northwest, Direction::North, Direction::Northeast, Direction::East, Direction::Southeast, Direction::South, Direction::Southwest, Direction::West};
    int neighborsOfType = 0;

    for (Direction direction : directions) {
        if (map.tileMap[getNeighborCoords(coords, direction)].state == stateToCheck) {
            neighborsOfType++;
        }
    }

    return neighborsOfType;
}

WorldCoords MapUtils::getTileWorldCoords(TileCoords coords)
{
    int worldX = -(coords.col * tileSize);
    int worldY = -(coords.row * tileSize);
    return {worldX, worldY};
}

TileCoords MapUtils::getTileCoordsAtWorldCoords(Map &map, WorldCoords coords)
{
    int col = coords.x / tileSize;
    int row = coords.y / tileSize;
    return {col, row};
    return TileCoords();
}

Tile MapUtils::getTileAtWorldCoords(Map& map, WorldCoords coords)
{
    TileCoords tileCoords = getTileCoordsAtWorldCoords(map, coords);
    return map.tileMap[tileCoords];
}

TileCoords MapUtils::selectLandingTile(Map &map)
{
    while (true)
    {
        for (int col = 0; col < map.cols; col++)
        {
            for (int row = 0; row < map.rows; row++)
            {
                if (map.tileMap[{col, row}].state != TileState::Sand) {continue;}
                if (neighborsOfType(map, {col, row}, TileState::Grass) < 3) {continue;}
                if (MathUtils::getRandomInt(1, map.size) != map.size) {continue;}
                return {col, row};
            }
        }
    }
}

void MapUtils::centerCameraOnTile(Map& map, TileCoords coords)
{
    int camOffsetX = (tileSize * (CAMERA_COLUMNS / 2));
    int camOffsetY = (tileSize * (CAMERA_ROWS / 2));
    WorldCoords tileOffsetPos = getTileWorldCoords(coords);
    map.setOffsetX(tileOffsetPos.x + camOffsetX);
    map.setOffsetY(tileOffsetPos.y + camOffsetY);
}
