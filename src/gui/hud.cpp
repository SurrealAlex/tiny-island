#include "hud.h"

void Hud::events()
{
    itemTriangleSelection = ' ';
    if (IsKeyDown(KEY_I)) {
        itemTriangleSelection = 'i';
    }
    if (IsKeyDown(KEY_J)) {
        itemTriangleSelection = 'j';
    }
    if (IsKeyDown(KEY_K)) {
        itemTriangleSelection = 'k';
    }
    if (IsKeyDown(KEY_L)) {
        itemTriangleSelection = 'l';
    }
}

void Hud::update()
{
    if (IsWindowResized()) {
        itemTriangle[0] = {GetScreenWidth() - 216.0f, GetScreenHeight() - 216.0f, 100, 100}; //i slot
        itemTriangle[1] = {GetScreenWidth() - 324.0f, GetScreenHeight() - 108.0f, 100, 100}; //j slot
        itemTriangle[2] = {GetScreenWidth() - 216.0f, GetScreenHeight() - 108.0f, 100, 100}; //k slot
        itemTriangle[3] = {GetScreenWidth() - 108.0f, GetScreenHeight() - 108.0f, 100, 100}; //l slot
    }
}

void Hud::draw()
{
    DrawText("i", itemTriangle[0].x + 10, itemTriangle[0].y + 10, 25, WHITE);
    DrawText("j", itemTriangle[1].x + 10, itemTriangle[1].y + 10, 25, WHITE);
    DrawText("k", itemTriangle[2].x + 10, itemTriangle[2].y + 10, 25, WHITE);
    DrawText("l", itemTriangle[3].x + 10, itemTriangle[3].y + 10, 25, WHITE);
    for (Rectangle rect : itemTriangle) 
    {
        DrawRectangle(rect.x, rect.y, rect.width, rect.height, {25, 25, 25, 100});
    }

    switch(itemTriangleSelection)
    {
        case 'i':
            DrawRectangleLinesEx(itemTriangle[0], 3.0f, WHITE);
            break;
        case 'j':
            DrawRectangleLinesEx(itemTriangle[1], 3.0f, WHITE);
            break;
        case 'k':
            DrawRectangleLinesEx(itemTriangle[2], 3.0f, WHITE);
            break;
        case 'l':
            DrawRectangleLinesEx(itemTriangle[3], 3.0f, WHITE);
            break;
        default:
            break;
    }
}
