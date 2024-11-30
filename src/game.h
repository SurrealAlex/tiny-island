#pragma once
#include "map.h"

enum class GameState {MainMenu, Playing, Paused};

class Game {
    public:
        GameState gameState;
        void run();
};