#include "tree.h"
#include "../../settings.h"
#include <raylib.h>
#include "../../map/map.h"

Tree::Tree(int wrldX, int wrldY)
{
    shakeDirection = false;
    isBeingShaked = false;
    shakeAnimationCounter = 0;
    shakeCounter = 0;
    shakeOffset = 0;
    generatingStick = false;
    stickDropChance = 2;

    name = "Tree";
    worldX = wrldX;
    worldY = wrldY;
    screenX = -worldX;
    screenY = -worldY;
    width = tileSize;
    height = tileSize;
    centerPoint = {screenX + (width / 2), screenY + (height / 2) + (TILE_SCALE * 6)};
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
    if (isBeingShaked) {
        shakeAnimationCounter++;
        if (!shakeDirection) {
            shakeOffset++;
            if (shakeOffset > 2) {shakeDirection = true;}
        }
        else if (shakeDirection) {
            shakeOffset--;
            if (shakeOffset < -2) {shakeDirection = false;}
        }
        if (shakeAnimationCounter >= 30) {
            shakeOffset = 0;
            shakeAnimationCounter = 0;
            isBeingShaked = false;
        }
    };
    screenX = worldX + map.getOffsetX() + shakeOffset;
    screenY = worldY + map.getOffsetY();
    zIndex = screenY;
    hitBox = {screenX + (tileSize / 3) + (TILE_SCALE * 2), screenY + (tileSize / 2) + (TILE_SCALE * 2), tileSize / 3 - (TILE_SCALE * 4), tileSize / 3};
    centerPoint = {screenX + (width / 2), screenY + (height / 2) + (TILE_SCALE * 6)};
}

void Tree::draw(Map& map, Assets& assets)
{
    DrawTexture(*assets.get("treeSprite"), screenX, screenY, WHITE);

    if (SHOW_HITBOXES) {
        DrawRectangle(hitBox.x, hitBox.y, hitBox.width, hitBox.height, RED);
    }
    if (SHOW_CENTER_POINTS) {
        DrawCircle(centerPoint.x, centerPoint.y, 5, YELLOW);
    }
}

void Tree::shake()
{
    isBeingShaked = true;
}
