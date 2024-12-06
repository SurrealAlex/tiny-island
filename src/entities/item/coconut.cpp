#include "coconut.h"

Coconut::Coconut(int wrldX, int wrldY)
{
    name = "Coconut";
    timeSpawned = GetTime();
    width = tileSize / 4;
    height = tileSize / 4;
    worldX = wrldX;
    worldY = wrldY;
    screenX = -worldX;
    screenY = -worldY;
    centerPoint = {screenX + (width / 2), screenY + (height / 2)};

    isRested = false;
    spawnAnimationCounter = 0;
    speed = 6.0f;
}

void Coconut::events(Map &map)
{
    return;
}

void Coconut::update(Map &map)
{
    timeAlive = GetTime() - timeSpawned;
    if (!isRested) {
        worldY += speed;
        spawnAnimationCounter++;
        if (spawnAnimationCounter >= 25) {
            isRested = true;
        }
    }

    screenX = worldX + map.getOffsetX();
    screenY = worldY + map.getOffsetY();
    zIndex = screenY - (tileSize / 2);
    centerPoint = {screenX + (width / 2), screenY + (height / 2)};
}

void Coconut::draw(Map &map, Assets &assets)
{
    DrawTexture(*assets.get("Coconut"), screenX, screenY, WHITE);

    if (SHOW_CENTER_POINTS) {
        DrawCircle(centerPoint.x, centerPoint.y, 10.0f, YELLOW);
    }
}
