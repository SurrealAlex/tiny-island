#include "rock.h"

Rock::Rock(int wrldX, int wrldY)
{
    name = "Rock";
    worldX = wrldX;
    worldY = wrldY;
    screenX = -worldX;
    screenY = -worldY;
    width = tileSize;
    height = tileSize;
    centerPoint = {screenX + (width/2), screenY + (width/3) + (TILE_SCALE * 4)};
    hitBox = {screenX + (TILE_SCALE * 9),
              screenY + (tileSize / 3),
              tileSize / 2 - (TILE_SCALE * 2),
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
    zIndex = screenY - (6 * TILE_SCALE);
    hitBox = {screenX + (TILE_SCALE * 9),
              screenY + (tileSize / 3),
              tileSize / 2 - (TILE_SCALE * 2),
              tileSize / 2 - (TILE_SCALE * 4)};
    centerPoint = {screenX + (width/2), screenY + (width/3) + (TILE_SCALE * 4)};
}

void Rock::draw(Map& map, Assets& assets)
{
    DrawTexture(*assets.get("rockSprite"), screenX, screenY, WHITE);

    if (SHOW_HITBOXES) {
        DrawRectangle(hitBox.x, hitBox.y, hitBox.width, hitBox.height, RED);
    }
    if (SHOW_CENTER_POINTS) {
        DrawCircle(centerPoint.x, centerPoint.y, 5, YELLOW);
    }
}
