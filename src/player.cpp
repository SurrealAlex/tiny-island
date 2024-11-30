#include "player.h"
#include <string>
#include <string.h>
#include <iostream>

Player::Player()
{
    width = tileSize / 2;
    height = tileSize / 2;
    screenX = (screenWidth / 2) - (width / 2);
    screenY = (screenHeight / 2) - (height / 2);
    zIndex = screenY - (12 * TILE_SCALE);
    hitBox = {screenX + (height / 3) + TILE_SCALE, screenY + (height / 3) + (TILE_SCALE * 3), width / 3 - (TILE_SCALE * 2), height / 3 - (TILE_SCALE)};

    speed = 5;
    sprintSpeed = 8;
    isMoving = false;
    willCollide = false;
    facing = Facing::Down;
    spriteState = SpriteState::Idle;
    standingOn = TileState::Sand;
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
    switch(standingOn)
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
        case Facing::Up:
            possiblePosY -= speed;
            break;
        case Facing::Down:
            possiblePosY += speed + (height / 2) - (speed / 2);
            break;
        case Facing::Left:
            possiblePosX -= speed;
            break;
        case Facing::Right:
            possiblePosX += speed;
            break;
        default:
            break;
    }

    if (map.getTileAtWorldCoords(possiblePosX, possiblePosY) == TileState::Water) {
        return true;
    }
    else {
        return false;
    }
}

void Player::events(Map &map)
{
    int sprintDifference = 0;
    isMoving = false;

    if (IsKeyDown(KEY_LEFT_SHIFT)) {
        sprintDifference = sprintSpeed - speed;
    }

    int currentSpeed = speed + sprintDifference;

    if (IsKeyDown(KEY_W)) {
        facing = Facing::Up;
        if (!checkWaterCollision(map, currentSpeed, Facing::Up) && !willCollide) {
            map.adjustOffsetY(currentSpeed);
            isMoving = true;
        }
    }
    if (IsKeyDown(KEY_A)) {
        facing = Facing::Left;
        if (!checkWaterCollision(map, currentSpeed, Facing::Left) && !willCollide) {
            map.adjustOffsetX(currentSpeed);
            isMoving = true;
        }
    }
    if (IsKeyDown(KEY_S)) {
        facing = Facing::Down;
        if (!checkWaterCollision(map, currentSpeed, Facing::Down) && !willCollide) {
            map.adjustOffsetY(-currentSpeed);
            isMoving = true;
        }
    }
    if (IsKeyDown(KEY_D)) {
        facing = Facing::Right;
        if (!checkWaterCollision(map, currentSpeed, Facing::Right) && !willCollide) {
            map.adjustOffsetX(-currentSpeed);
            isMoving = true;
        }
    }
}

void Player::update(Map &map)
{
    worldX = -map.getOffsetX() + (screenWidth / 2);
    worldY = -map.getOffsetY() + (screenHeight / 2);
    standingOn = map.getTileAtWorldCoords(worldX, worldY);

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
    switch(facing)
    {
        case Facing::Up:
            if (spriteState == SpriteState::Idle) {DrawTexture(*assets.get("uIdle"), screenX, screenY, WHITE);}
            if (spriteState == SpriteState::Walk1) {DrawTexture(*assets.get("uWalk1"), screenX, screenY, WHITE);}
            if (spriteState == SpriteState::Walk2) {DrawTexture(*assets.get("uWalk2"), screenX, screenY, WHITE);}
            break;
        case Facing::Right:
            if (spriteState == SpriteState::Idle) {DrawTexture(*assets.get("rIdle"), screenX, screenY, WHITE);}
            if (spriteState == SpriteState::Walk1) {DrawTexture(*assets.get("rWalk1"), screenX, screenY, WHITE);}
            if (spriteState == SpriteState::Walk2) {DrawTexture(*assets.get("rWalk2"), screenX, screenY, WHITE);}
            break;
        case Facing::Down:
            if (spriteState == SpriteState::Idle) {DrawTexture(*assets.get("dIdle"), screenX, screenY, WHITE);}
            if (spriteState == SpriteState::Walk1) {DrawTexture(*assets.get("dWalk1"), screenX, screenY, WHITE);}
            if (spriteState == SpriteState::Walk2) {DrawTexture(*assets.get("dWalk2"), screenX, screenY, WHITE);}
            break;
        case Facing::Left:
            if (spriteState == SpriteState::Idle) {DrawTexture(*assets.get("lIdle"), screenX, screenY, WHITE);}
            if (spriteState == SpriteState::Walk1) {DrawTexture(*assets.get("lWalk1"), screenX, screenY, WHITE);}
            if (spriteState == SpriteState::Walk2) {DrawTexture(*assets.get("lWalk2"), screenX, screenY, WHITE);}
            break;
    }
}