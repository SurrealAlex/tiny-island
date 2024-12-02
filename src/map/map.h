#pragma once
#include "../settings.h"
#include "../assets/assets.h"
#include <raylib.h>
#include <map>

enum class TileState {Grass, Sand, Water, Lake, River};
enum class Direction {Northwest, North, Northeast, East, Southeast, South, Southwest, West};

struct TileCoords {
    int col, row;
    bool operator<(const TileCoords& other) const {
        if (col != other.col) {
            return col < other.col;
        }
        return row < other.row;
    }
};

struct WorldCoords {
    int x, y;
    bool operator<(const WorldCoords& other) const {
        if (x != other.x) {
            return x < other.x;
        }
        return y < other.y;
    }
};

struct Tile {
    TileState state;
    int elevation;
};

class Map {
    public:
        int cols, rows, size;
        int offsetX, offsetY;
        std::pair<int, int> currentWindowSize;
        std::map<TileCoords, Tile> tileMap;
        Map();

        void generate();

        int getOffsetX();
        int getOffsetY();
        void setOffsetX(int x);
        void setOffsetY(int y);
        void adjustOffsetX(int x);
        void adjustOffsetY(int y);

        void update();
        void draw(Assets &assets);
};