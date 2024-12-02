#include "debug.h"
#include "../map/utils_map.h"
#include <random>
#include <iostream>
#include <raylib.h>
#include <intrin.h>
#include <string>

void DebugTools::drawFramerate()
{
    int framerate = GetFPS();
    char framerateText[7] = "FPS: ";
    std::string intString = std::to_string(framerate);
    strcat(framerateText, intString.c_str());
    DrawText(framerateText, 20, 20, 20, WHITE);
}