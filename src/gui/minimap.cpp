#include "minimap.h"
#include "../map/utils_map.h"

void Minimap::events()
{
    if (IsWindowResized()) {
        startingX = GetScreenWidth() - (MAP_COLUMNS * MINIMAP_SCALE) + MINIMAP_OFFSET_X;
    }
    if (IsKeyPressed(KEY_M)) {
        if (showing) {showing = false;}
        else {showing = true;}
    }
}

void Minimap::draw(Map &map, Player& player)
{
    if (!showing) {
        return;
    }

    int x = startingX;
    int y = startingY;
    TileCoords playerLocation = MapUtils::getTileCoordsAtWorldCoords(map, {player.worldX, player.worldY});

    for (int col = 0; col < map.cols; col++)
    {
        for (int row = 0; row < map.rows; row++)
        {
            switch(map.tileMap[{col, row}].state)
            {
                case TileState::Grass:
                    DrawRectangle(x, y, MINIMAP_SCALE, MINIMAP_SCALE, GREEN);
                    break;
                case TileState::Water:
                    DrawRectangle(x, y, MINIMAP_SCALE, MINIMAP_SCALE, BLUE);
                    break;
                case TileState::Sand:
                    DrawRectangle(x, y, MINIMAP_SCALE, MINIMAP_SCALE, ORANGE);
                    break;
                default:
                    break;
            }

            y += MINIMAP_SCALE;
        }
        x += MINIMAP_SCALE;
        y = startingY;
    };

    int playerX = startingX + (playerLocation.col * MINIMAP_SCALE);
    int playerY = startingY + (playerLocation.row * MINIMAP_SCALE);
    DrawCircle(playerX, playerY, minimapPlayerRadius, RED);
}