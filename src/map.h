#pragma once
#include "settings.h"
#include "assets.h"
#include <raylib.h>
#include <map>

enum class TileState {Grass, Sand, Water, Lake, River};
enum class Direction {UpLeft, Up, UpRight, Right, DownRight, Down, DownLeft, Left};

struct Tile {
    TileState state;
    int elevation;
};

class Map {
    public:
        int cols, rows, size;
        int offsetX, offsetY;
        std::map<std::pair<int, int>, Tile> tileMap;
        Map();

        std::pair<int, int> selectLandingTile();
        void centerCameraOnTile(std::pair<int, int> coords);
        void generate();

        int getOffsetX();
        int getOffsetY();
        void setOffsetX(int x);
        void setOffsetY(int y);
        void adjustOffsetX(int x);
        void adjustOffsetY(int y);

        TileState getTileAtWorldCoords(int x, int y);
        std::pair<int, int> getTileCoordsAtWorldCoords(int x, int y);

        void draw(Assets &assets);
};