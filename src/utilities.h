#pragma once
#include "map.h"

class Utilities {
    public:
        static void drawFramerate();
        static int getRandomInt(int min, int max);
        static int findLowestInt(int numbers[], int arrayLength);
        static bool tileWithinNthPerimeter(int cols, int rows, std::pair<int, int> coords, int n);
        static std::pair<int, int> getNeighborCoords(std::pair<int, int> coords, Direction direction);
        static std::pair<int, int> getRandomOrthogonalNeighborCoords(std::pair<int, int> coords);
        static int neighborsOfType(std::map<std::pair<int, int>, Tile>& tileMap, std::pair<int, int> coords, TileState stateToCheck);
        static std::pair<int, int> getTileOffsetPosition(std::pair<int, int> coords);
        static bool entityShouldRender(Map &map, int worldX, int worldY);
};