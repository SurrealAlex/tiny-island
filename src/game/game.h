#pragma once
#include "../map/map.h"
#include "../settings.h"
#include "../assets/assets.h"
#include "../map/map.h"
#include "../entities/mobs/player.h"
#include "../entities/entity_handler.h"
#include "../gui/minimap.h"
#include "../gui/hud.h"
#include "../gui/menu.h"

#include <iostream>
#include <raylib.h>

enum class GameState {MainMenu, Playing, Paused};

class Game {
    public:
        GameState gameState;
        void run();
};