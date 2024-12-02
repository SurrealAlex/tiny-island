#pragma once
#include "../map/map.h"

class Utilities {
    public:
        static void drawFramerate();
        static bool entityShouldRender(Map &map, int worldX, int worldY);
};