#include "utilities.h"
#include "../map/utils_map.h"
#include <random>
#include <iostream>
#include <raylib.h>
#include <intrin.h>
#include <string>

void Utilities::drawFramerate()
{
    int framerate = GetFPS();
    char framerateText[7] = "FPS: ";
    std::string intString = std::to_string(framerate);
    strcat(framerateText, intString.c_str());
    DrawText(framerateText, 20, 20, 20, WHITE);
}

bool Utilities::entityShouldRender(Map& map, int screenX, int screenY)
{
    if (screenX > GetScreenWidth()) {return false;}
    if (screenX < 0 - tileSize) {return false;}
    if (screenY > GetScreenHeight()) {return false;}
    if (screenY < 0 - tileSize) {return false;}
    return true;
}