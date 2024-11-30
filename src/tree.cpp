#include "tree.h"
#include "settings.h"
#include <raylib.h>
#include "map.h"
#include "utilities.h"

Tree::Tree(int wrldX, int wrldY)
{
    worldX = wrldX;
    worldY = wrldY;
    screenX = -worldX;
    screenY = -worldY;
    width = tileSize;
    height = tileSize;
    hitBox = {screenX + (tileSize / 3) + (TILE_SCALE * 2),
              screenY + (tileSize / 2) + (TILE_SCALE * 2),
              tileSize / 3 - (TILE_SCALE * 4),
              tileSize / 3};
}

void Tree::events(Map &map)
{
    return;
}

void Tree::update(Map &map)
{
    screenX = worldX + map.getOffsetX();
    screenY = worldY + map.getOffsetY();
    zIndex = screenY;
    hitBox = {screenX + (tileSize / 3) + (TILE_SCALE * 2), screenY + (tileSize / 2) + (TILE_SCALE * 2), tileSize / 3 - (TILE_SCALE * 4), tileSize / 3};
}

void Tree::draw(Map& map, Assets& assets)
{
    DrawTexture(*assets.get("treeSprite"), screenX, screenY, WHITE);

    if (SHOW_HITBOXES) {
        DrawRectangle(hitBox.x, hitBox.y, hitBox.width, hitBox.height, RED);
    }
}