#pragma once
#include <utility>
#include "map.h"

class MapUtils {
    public:
        static bool tileWithinNthPerimeter(Map& map, TileCoords coords, int n);
        static TileCoords getNeighborCoords(TileCoords coords, Direction direction);
        static TileCoords getRandomOrthogonalNeighborCoords(TileCoords coords);
        static int neighborsOfType(Map& map, TileCoords coords, TileState stateToCheck);
        static WorldCoords getTileWorldCoords(TileCoords coords);

        static TileCoords getTileCoordsAtWorldCoords(Map& map, WorldCoords coords);
        static Tile getTileAtWorldCoords(Map& map, WorldCoords coords);

        static TileCoords selectLandingTile(Map& map);
        static void centerCameraOnTile(Map& map, TileCoords coords);
};