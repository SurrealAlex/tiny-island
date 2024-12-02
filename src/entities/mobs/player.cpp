#include "player.h"
#include "../../map/utils_map.h"
#include <string>
#include <string.h>
#include <iostream>
#include <math.h>
#include "../world-objects/tree.h"

Player::Player()
{
    name = "Player";
    width = tileSize / 2;
    height = tileSize / 2;
    screenX = (GetScreenWidth() / 2) - (width / 2);
    screenY = (GetScreenHeight() / 2) - (height / 2);
    zIndex = screenY - (12 * TILE_SCALE);
    centerPoint = {screenX + (width / 2), screenY + (height / 2)};
    hitBox = {screenX + (height / 3) + TILE_SCALE, screenY + (height / 3) + (TILE_SCALE * 3), width / 3 - (TILE_SCALE * 2), height / 3 - (TILE_SCALE)};

    speed = 5;
    sprintSpeed = 8;
    isMoving = false;
    willCollide = false;
    isFacing = Facing::South;
    spriteState = SpriteState::Idle;
    isStandingOn = TileState::Sand;
    spriteCounter = 0;
}

void Player::DEBUG_drawWorldCoords()
{
    char textX[10] = "X: ";
    char textY[10] = "Y: ";
    std::string xString = std::to_string(worldX);
    strcat(textX, xString.c_str());
    std::string yString = std::to_string(worldY);
    strcat(textY, yString.c_str());
    DrawText(textX, 20, 40, 20, WHITE);
    DrawText(textY, 20, 60, 20, WHITE);
}

void Player::DEBUG_drawCurrentTile(Map &map)
{
    char arr[5] = "";
    std::string stateStr;
    switch(isStandingOn)
    {
        case TileState::Grass:
            stateStr = "Grass";
            break;
        case TileState::Water:
            stateStr = "Water";
            break;
        case TileState::Sand:
            stateStr = "Sand";
            break;
        default:
            stateStr = "N/A";
            break;
    }
    strcat(arr, stateStr.c_str());
    DrawText(arr, 20, 80, 20, WHITE);
}

bool Player::checkWaterCollision(Map& map, int speed, Facing direction)
{
    int possiblePosX = worldX;
    int possiblePosY = worldY;
    switch(direction)
    {
        case Facing::North:
            possiblePosY -= speed;
            break;
        case Facing::South:
            possiblePosY += speed + (height / 2) - (speed / 2);
            break;
        case Facing::West:
            possiblePosX -= speed;
            break;
        case Facing::East:
            possiblePosX += speed;
            break;
        default:
            break;
    }

    if (MapUtils::getTileAtWorldCoords(map, {possiblePosX, possiblePosY}).state == TileState::Water) {
        return true;
    }
    else {
        return false;
    }
}

void Player::events(Map &map)
{
    float sprintDifference = 0;
    isMoving = false;

    if (IsKeyDown(KEY_LEFT_SHIFT)) {
        sprintDifference = sprintSpeed - speed;
    }

    float currentSpeed = speed + sprintDifference;

    if ((IsKeyDown(KEY_W) && IsKeyDown(KEY_A)) ||
        (IsKeyDown(KEY_W) && IsKeyDown(KEY_D)) ||
        (IsKeyDown(KEY_S) && IsKeyDown(KEY_A)) ||
        (IsKeyDown(KEY_S) && IsKeyDown(KEY_D))) {
            if (sprintDifference == 0) {
                currentSpeed = (currentSpeed / 5) + sqrt(2 * currentSpeed);
            } else {
                currentSpeed = (currentSpeed / 3) + sqrt(2 * currentSpeed);
            }
        }

    if (IsKeyDown(KEY_W)) {
        isFacing = Facing::North;
        if (!checkWaterCollision(map, currentSpeed, Facing::North) && !willCollide) {
            map.adjustOffsetY(currentSpeed);
            isMoving = true;
        }
    }
    if (IsKeyDown(KEY_A)) {
        isFacing = Facing::West;
        if (!checkWaterCollision(map, currentSpeed, Facing::West) && !willCollide) {
            map.adjustOffsetX(currentSpeed);
            isMoving = true;
        }
    }
    if (IsKeyDown(KEY_S)) {
        isFacing = Facing::South;
        if (!checkWaterCollision(map, currentSpeed, Facing::South) && !willCollide) {
            map.adjustOffsetY(-currentSpeed);
            isMoving = true;
        }
    }
    if (IsKeyDown(KEY_D)) {
        isFacing = Facing::East;
        if (!checkWaterCollision(map, currentSpeed, Facing::East) && !willCollide) {
            map.adjustOffsetX(-currentSpeed);
            isMoving = true;
        }
    }

    if (IsKeyPressed(KEY_SPACE)) {
        interact();
    }
}

void Player::update(Map &map)
{
    if (IsWindowResized()) {
        screenX = (GetScreenWidth() / 2) - (width / 2);
        screenY = (GetScreenHeight() / 2) - (height / 2);
        zIndex = screenY - (12 * TILE_SCALE);
        centerPoint = {screenX + (width / 2), screenY + (height / 2)};
    }
    worldX = -map.getOffsetX() + (GetScreenWidth() / 2);
    worldY = -map.getOffsetY() + (GetScreenHeight() / 2);
    isStandingOn = MapUtils::getTileAtWorldCoords(map, {worldX, worldY}).state;

    spriteCounter++;
    if (spriteCounter > 60) {spriteCounter = 0;}

    int spriteIntervals[4] = {15, 30, 45, 60};

    if (isMoving) {
        if (spriteCounter < spriteIntervals[0]) {spriteState = SpriteState::Idle;}
        else if (spriteCounter < spriteIntervals[1]) {spriteState = SpriteState::Walk1;}
        else if (spriteCounter < spriteIntervals[2]) {spriteState = SpriteState::Idle;}
        else {spriteState = SpriteState::Walk2;}
    }
    else {
        spriteState = SpriteState::Idle;
        hitBox = {screenX + (height / 3) + TILE_SCALE, screenY + (height / 3) + (TILE_SCALE * 3), width / 3 - (TILE_SCALE * 2), height / 3 - (TILE_SCALE)};
    }
}

void Player::draw(Map& map, Assets& assets)
{
    switch(isFacing)
    {
        case Facing::North:
            if (spriteState == SpriteState::Idle) {DrawTexture(*assets.get("uIdle"), screenX, screenY, WHITE);}
            if (spriteState == SpriteState::Walk1) {DrawTexture(*assets.get("uWalk1"), screenX, screenY, WHITE);}
            if (spriteState == SpriteState::Walk2) {DrawTexture(*assets.get("uWalk2"), screenX, screenY, WHITE);}
            break;
        case Facing::East:
            if (spriteState == SpriteState::Idle) {DrawTexture(*assets.get("rIdle"), screenX, screenY, WHITE);}
            if (spriteState == SpriteState::Walk1) {DrawTexture(*assets.get("rWalk1"), screenX, screenY, WHITE);}
            if (spriteState == SpriteState::Walk2) {DrawTexture(*assets.get("rWalk2"), screenX, screenY, WHITE);}
            break;
        case Facing::South:
            if (spriteState == SpriteState::Idle) {DrawTexture(*assets.get("dIdle"), screenX, screenY, WHITE);}
            if (spriteState == SpriteState::Walk1) {DrawTexture(*assets.get("dWalk1"), screenX, screenY, WHITE);}
            if (spriteState == SpriteState::Walk2) {DrawTexture(*assets.get("dWalk2"), screenX, screenY, WHITE);}
            break;
        case Facing::West:
            if (spriteState == SpriteState::Idle) {DrawTexture(*assets.get("lIdle"), screenX, screenY, WHITE);}
            if (spriteState == SpriteState::Walk1) {DrawTexture(*assets.get("lWalk1"), screenX, screenY, WHITE);}
            if (spriteState == SpriteState::Walk2) {DrawTexture(*assets.get("lWalk2"), screenX, screenY, WHITE);}
            break;
    }

    if (SHOW_HITBOXES) {
        DrawRectangle(hitBox.x, hitBox.y, hitBox.width, hitBox.height, GREEN);
    }
    if (SHOW_CENTER_POINTS) {
        DrawCircle(centerPoint.x, centerPoint.y, 5, YELLOW);
    }
}

void Player::interact()
{
    if (interactableEntity == nullptr) {
        return;
    }

    if (Tree* tree = dynamic_cast<Tree*>(interactableEntity))
    {
        if (tree->isBeingShaked) {
            return;
        }
        tree->shake();
    }
}
