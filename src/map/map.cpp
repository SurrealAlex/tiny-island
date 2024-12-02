#include "map.h"
#include "utils_map.h"
#include "../utils/utils_general.h"
#include "../game/game.h"
#include <vector>
#include <iostream>
#include <intrin.h>
#include "../assets/assets.h"

Map::Map()
{
    cols = MAP_COLUMNS;
    rows = MAP_ROWS;
    size = cols * rows;
    offsetX = 0;
    offsetY = 0;
    currentWindowSize = std::make_pair(GetScreenWidth(), GetScreenHeight());
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

                if (MapUtils::tileWithinNthPerimeter(*this, {col, row}, 6)) {
                    continue;
                }

                TileCoords nextNeighborCoords = MapUtils::getRandomOrthogonalNeighborCoords({col, row});

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
        int possibleCol = GeneralUtils::getRandomInt(0, cols - 1);
        int possibleRow = GeneralUtils::getRandomInt(0, rows - 1);
        
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

                TileCoords nextNeighborCoords = MapUtils::getRandomOrthogonalNeighborCoords({col, row});
                
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

            if (MapUtils::neighborsOfType(*this, {col, row}, TileState::Water) > 0 ||
                MapUtils::neighborsOfType(*this, {col, row}, TileState::Lake) > 0) {
                tileMap[{col, row}].elevation = 1;
                continue;
            }

            tileMap[{col, row}].elevation = GeneralUtils::getRandomInt(2, 7);
        }
    }

    //Places river seeds on the island
    std::cout << "TINY_ISLAND: Initializing rivers...\n";
    int riverCount = 0;
    std::vector<TileCoords> riverSeedCoords;
    while (riverCount < NUM_OF_RIVERS)
    {
        int possibleCol = GeneralUtils::getRandomInt(0, cols - 1);
        int possibleRow = GeneralUtils::getRandomInt(0, cols - 1);

        if (tileMap[{possibleCol, possibleRow}].state != TileState::Grass) {
            continue;
        }

        if (MapUtils::neighborsOfType(*this, {possibleCol, possibleRow}, TileState::Grass) == 8) {
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
        TileCoords currentCoords = riverSeedCoords[riv];
        while (currentElevation > 0)
        {
            TileCoords neighborCoords[4] = {
                MapUtils::getNeighborCoords(currentCoords, Direction::North),
                MapUtils::getNeighborCoords(currentCoords, Direction::South),
                MapUtils::getNeighborCoords(currentCoords, Direction::West),
                MapUtils::getNeighborCoords(currentCoords, Direction::East)
            };

            int neighborElevations[4] = {
                tileMap[neighborCoords[0]].elevation,
                tileMap[neighborCoords[1]].elevation,
                tileMap[neighborCoords[2]].elevation,
                tileMap[neighborCoords[3]].elevation
            };

            currentElevation = GeneralUtils::findLowestInt(neighborElevations, 4);

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
                if (tileMap[{col, row}].state == TileState::Grass && MapUtils::neighborsOfType(*this, {col, row}, TileState::Water) > 5) {
                    tileMap[{col, row}].state = TileState::Water;
                }
                
                if (tileMap[{col, row}].state == TileState::Water && MapUtils::neighborsOfType(*this, {col, row}, TileState::Grass) > 6)
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

            if (MapUtils::neighborsOfType(*this, {col, row}, TileState::Water) > 0) {
                tileMap[{col, row}].state = TileState::Sand;
            }

        }
    }

    std::cout << "TINY_ISLAND: Map generated!\n";
    MapUtils::centerCameraOnTile(*this, MapUtils::selectLandingTile(*this));
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


void Map::update()
{
    if (IsWindowResized()) {
        std::cout << "OFFSET BEFORE: " << offsetX << ", " << offsetY << std::endl;
        offsetX += (GetScreenWidth() / 2) - (currentWindowSize.first / 2);
        offsetY += (GetScreenHeight() / 2) - (currentWindowSize.second / 2);
        currentWindowSize.first = GetScreenWidth();
        currentWindowSize.second = GetScreenHeight();
        std::cout << "OFFSET AFTER: " << offsetX << ", " << offsetY << std::endl;
    }
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
            WorldCoords tileOffsetPos = MapUtils::getTileWorldCoords({col, row});
            if (tileOffsetPos.x > offsetX + tileSize) {render = false;}
            if (tileOffsetPos.x < offsetX - GetScreenWidth()) {render = false;}
            if (tileOffsetPos.y > offsetY + tileSize) {render = false;}
            if (tileOffsetPos.y < offsetY - GetScreenHeight()) {render = false;}
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