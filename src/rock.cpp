#include "rock.h"

Rock::Rock(int wrldX, int wrldY)
{
    worldX = wrldX;
    worldY = wrldY;
    screenX = -worldX;
    screenY = -worldY;
    width = tileSize;
    height = tileSize;
    hitBox = {screenX + (TILE_SCALE * 5),
              screenY + (tileSize / 3) + (TILE_SCALE),
              tileSize / 2 + (TILE_SCALE * 5),
              tileSize / 2 - (TILE_SCALE * 4)};
}

void Rock::events(Map &map)
{
    return;
}

void Rock::update(Map &map)
{
    screenX = worldX + map.getOffsetX();
    screenY = worldY + map.getOffsetY();
    zIndex = screenY - (4 * TILE_SCALE);
    hitBox = {screenX + (TILE_SCALE * 5),
              screenY + (tileSize / 3) + (TILE_SCALE),
              tileSize / 2 + (TILE_SCALE * 5),
              tileSize / 2 - (TILE_SCALE * 4)};
}

void Rock::draw(Map& map, Assets& assets)
{
    DrawTexture(*assets.get("rockSprite"), screenX, screenY, WHITE);

    if (SHOW_HITBOXES) {
        DrawRectangle(hitBox.x, hitBox.y, hitBox.width, hitBox.height, RED);
    }
}