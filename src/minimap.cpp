#include "minimap.h"

void Minimap::events()
{
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
    std::pair<int, int> playerLocation = map.getTileCoordsAtWorldCoords(player.worldX, player.worldY);

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

    int playerX = startingX + (playerLocation.first * MINIMAP_SCALE);
    int playerY = startingY + (playerLocation.second * MINIMAP_SCALE);
    DrawCircle(playerX, playerY, minimapPlayerRadius, RED);
}