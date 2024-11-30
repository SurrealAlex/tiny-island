#include "map.h"
#include "utilities.h"
#include "game.h"
#include <vector>
#include <iostream>
#include <intrin.h>
#include "assets.h"

Map::Map()
{
    cols = MAP_COLUMNS;
    rows = MAP_ROWS;
    size = cols * rows;
    offsetX = 0;
    offsetY = 0;
}

std::pair<int, int> Map::selectLandingTile()
{
    while (true)
    {
        for (int col = 0; col < cols; col++)
        {
            for (int row = 0; row < rows; row++)
            {
                if (tileMap[{col, row}].state != TileState::Sand) {continue;}
                if (Utilities::neighborsOfType(tileMap, {col, row}, TileState::Grass) < 3) {continue;}
                if (Utilities::getRandomInt(1, size) != size) {continue;}
                return {col, row};
            }
        }
    }
}

void Map::centerCameraOnTile(std::pair<int, int> coords)
{
    int cameraOffset = (tileSize * (CAMERA_COLUMNS / 2));
    std::pair<int, int> tileOffsetPos = Utilities::getTileOffsetPosition(coords);
    setOffsetX(tileOffsetPos.first + cameraOffset);
    setOffsetY(tileOffsetPos.second + cameraOffset);
}

void Map::generate() // Generates the tilemap
{
    // Initializes the tilemap by populating it with tiles
    std::cout << "TINY_ISLAND: Initializing map...\n";
    for (int col = 0; col < cols; col++) 
    {
        for (int row = 0; row < rows; row++) 
        {
            if ((col == cols / 2) && (row == rows / 2)) {
                tileMap[{col, row}] = {TileState::Grass, 1};
            }
            else {
                tileMap[{col, row}] = {TileState::Water, 0};
            }
        }
    }

    //Generates the island randomly from the center land tile
    std::cout << "TINY_ISLAND: Generating island...\n";
    int landCount = 1;
    int landSize = size * LAND_PERCENTAGE;
    while (landCount < landSize) 
    {
        for (int col = 0; col < cols; col++) 
        {
            for (int row = 0; row < rows; row++) 
            {
                if (tileMap[{col, row}].state != TileState::Grass) {
                    continue;
                }

                if (Utilities::tileWithinNthPerimeter(cols, rows, {col, row}, 3)) {
                    continue;
                }

                std::pair<int, int> nextNeighborCoords = Utilities::getRandomOrthogonalNeighborCoords({col, row});

                if (tileMap[nextNeighborCoords].state == TileState::Grass) {
                    continue;
                }

                tileMap[nextNeighborCoords].state = TileState::Grass;
                landCount++;
            }
        }
    }

    //Places lake seeds throughout the generated island
    std::cout << "TINY_ISLAND: Initializing lakes...\n";
    int lakeCount = 0;
    while (lakeCount < NUM_OF_LAKES)
    {
        int possibleCol = Utilities::getRandomInt(0, cols - 1);
        int possibleRow = Utilities::getRandomInt(0, rows - 1);
        
        if (tileMap[{possibleCol, possibleRow}].state == TileState::Grass)
        {
            tileMap[{possibleCol, possibleRow}].state = TileState::Lake;
            lakeCount++;
        }
    }

    //Generates the lakes from the seeds
    std::cout << "TINY_ISLAND: Generating lakes...\n";
    int lakeMax = landCount * LAKE_PERCENTAGE;
    while (lakeCount < lakeMax)
    {
        for (int col = 0; col < cols; col++)
        {
            for (int row = 0; row < rows; row++)
            {
                if (tileMap[{col, row}].state != TileState::Lake) {
                    continue;
                }

                std::pair<int, int> nextNeighborCoords = Utilities::getRandomOrthogonalNeighborCoords({col, row});
                
                if (tileMap[nextNeighborCoords].state == TileState::Lake || tileMap[nextNeighborCoords].state == TileState::Water) {
                    continue;
                }

                tileMap[nextNeighborCoords].state = TileState::Lake;
                lakeCount++;
            }
        }
    }

    //Generates heightmap by assiging elevation values to each tile
    std::cout << "TINY_ISLAND: Generating heightmap...\n";
    for (int col = 0; col < cols; col++)
    {
        for (int row = 0; row < rows; row++)
        {
            if (tileMap[{col, row}].state != TileState::Grass) {
                continue;
            }

            if (Utilities::neighborsOfType(tileMap, {col, row}, TileState::Water) > 0 ||
                Utilities::neighborsOfType(tileMap, {col, row}, TileState::Lake) > 0) {
                tileMap[{col, row}].elevation = 1;
                continue;
            }

            tileMap[{col, row}].elevation = Utilities::getRandomInt(2, 7);
        }
    }

    //Places river seeds on the island
    std::cout << "TINY_ISLAND: Initializing rivers...\n";
    int riverCount = 0;
    std::vector<std::pair<int, int>> riverSeedCoords;
    while (riverCount < NUM_OF_RIVERS)
    {
        int possibleCol = Utilities::getRandomInt(0, cols - 1);
        int possibleRow = Utilities::getRandomInt(0, cols - 1);

        if (tileMap[{possibleCol, possibleRow}].state != TileState::Grass) {
            continue;
        }

        if (Utilities::neighborsOfType(tileMap, {possibleCol, possibleRow}, TileState::Grass) == 8) {
            tileMap[{possibleCol, possibleRow}] = {TileState::River, 8};
            riverSeedCoords.push_back({possibleCol, possibleRow});
            riverCount++;
        }
    }

    //Generates rivers on the island
    std::cout << "TINY_ISLAND: Generating rivers...\n";
    for (int riv = 0; riv < (int)riverSeedCoords.size(); riv++)
    {
        int currentElevation = 8;
        std::pair<int, int> currentCoords = riverSeedCoords[riv];
        while (currentElevation > 0)
        {
            std::pair<int, int> neighborCoords[4] = {
                Utilities::getNeighborCoords(currentCoords, Direction::Up),
                Utilities::getNeighborCoords(currentCoords, Direction::Down),
                Utilities::getNeighborCoords(currentCoords, Direction::Left),
                Utilities::getNeighborCoords(currentCoords, Direction::Right)
            };

            int neighborElevations[4] = {
                tileMap[neighborCoords[0]].elevation,
                tileMap[neighborCoords[1]].elevation,
                tileMap[neighborCoords[2]].elevation,
                tileMap[neighborCoords[3]].elevation
            };

            currentElevation = Utilities::findLowestInt(neighborElevations, 4);

            for (int i = 0; i < 4; i++)
            {
                if (currentElevation == neighborElevations[i]) {
                    currentCoords = neighborCoords[i];
                    tileMap[currentCoords] = {TileState::River, 9};
                }
            }
        }
    }

    //Normalizes tiles (river/lake to water, reassign normal elevation)
    std::cout << "TINY_ISLAND: Normalizing tiles...\n";
    for (int col = 0; col < cols; col++)
    {
        for (int row = 0; row < rows; row++)
        {
            if (tileMap[{col, row}].state != TileState::Grass) {
                tileMap[{col, row}] = {TileState::Water, 0};
            }
            else {
                tileMap[{col, row}] = {TileState::Grass, 1};
            }
        }
    }

    //Cleans up shores and loose tiles
    std::cout << "TINY_ISLAND: Smoothing coastline...\n";
    for (int i = 0; i < CLEANUP_ITERATIONS; i++)
    {
        for (int col = 0; col < cols; col++)
        {
            for (int row = 0; row < rows; row++)
            {
                if (tileMap[{col, row}].state == TileState::Grass && Utilities::neighborsOfType(tileMap, {col, row}, TileState::Water) > 5) {
                    tileMap[{col, row}].state = TileState::Water;
                }
                
                if (tileMap[{col, row}].state == TileState::Water && Utilities::neighborsOfType(tileMap, {col, row}, TileState::Grass) > 6)
                {
                    tileMap[{col, row}].state = TileState::Grass;
                }
                
            }
        }
    }

    //Turns each tile that borders the ocean into a sand tile
    std::cout << "TINY_ISLAND: Generating beaches...\n";
    for (int col = 0; col < cols; col++)
    {
        for (int row = 0; row < rows; row++)
        {
            if (tileMap[{col, row}].state != TileState::Grass) {
                continue;
            }

            if (Utilities::neighborsOfType(tileMap, {col, row}, TileState::Water) > 0) {
                tileMap[{col, row}].state = TileState::Sand;
            }

        }
    }

    std::cout << "TINY_ISLAND: Map generated!\n";
    centerCameraOnTile(selectLandingTile());
}

int Map::getOffsetX()
{
    return offsetX;
}

int Map::getOffsetY()
{
    return offsetY;
}

void Map::setOffsetX(int x)
{
    offsetX = x;
}

void Map::setOffsetY(int y)
{
    offsetY = y;
}

void Map::adjustOffsetX(int x)
{
    offsetX += x;
}

void Map::adjustOffsetY(int y)
{
    offsetY += y;
}

TileState Map::getTileAtWorldCoords(int x, int y)
{
    int xApprox = x / tileSize;
    int yApprox = y / tileSize;

    return tileMap[{xApprox, yApprox}].state;
}

std::pair<int, int> Map::getTileCoordsAtWorldCoords(int x, int y)
{
    int xApprox = x / tileSize;
    int yApprox = y / tileSize;

    return std::make_pair(xApprox, yApprox);
}

void Map::draw(Assets &assets)
{
    int x = 0 + offsetX;
    int y = 0 + offsetY;

    for (int col = 0; col < cols; col++)
    {
        for (int row = 0; row < rows; row++)
        {
            x = col * tileSize + offsetX;
            y = row * tileSize + offsetY;

            bool render = true;
            std::pair<int, int> tileOffsetPos = Utilities::getTileOffsetPosition({col, row});
            if (tileOffsetPos.first > offsetX + tileSize) {render = false;}
            if (tileOffsetPos.first < offsetX - screenWidth) {render = false;}
            if (tileOffsetPos.second > offsetY + tileSize) {render = false;}
            if (tileOffsetPos.second < offsetY - screenHeight) {render = false;}
            if (!render) {continue;}

            switch(tileMap[{col, row}].state)
            {
                case TileState::Grass:
                    DrawTexture(*assets.get("grassTile"), x, y, WHITE);
                    break;
                case TileState::Sand:
                    DrawTexture(*assets.get("sandTile"), x, y, WHITE);
                    break;
                case TileState::Water:
                    DrawTexture(*assets.get("waterTile"), x, y, WHITE);
                    break;
                default:
                    std::cout << "UH OH" << std::endl;
                    break;
            }
        }
    }
}