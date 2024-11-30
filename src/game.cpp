#include "game.h"
#include "settings.h"
#include "assets.h"
#include "map.h"
#include "player.h"
#include "entity_handler.h"
#include "minimap.h"
#include "utilities.h"
#include <iostream>
#include <raylib.h>

void Game::run()
{
    //Init window
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Tiny Island - Pre-Alpha Development");
    SetTargetFPS(TARGET_FPS);
    BeginDrawing();
    ClearBackground(BLACK);
    EndDrawing();

    //Init game objects
    gameState = GameState::Playing;
    Assets assets;
    Map map;
    EntityHandler eh;
    Minimap minimap;

    //Init game
    map.generate();
    eh.generateEntities(map);

    //Game loop
    while (!WindowShouldClose())
    {
        if (gameState == GameState::Playing)
        {
            //Listen for events
            eh.events(map);
            minimap.events();

            //Update objects
            eh.update(map);

            //Render
            BeginDrawing();
                ClearBackground(BLACK);
                map.draw(assets);
                eh.draw(map, assets);
            EndDrawing();
        }
    }

    //Cleanup
    assets.unloadTextures();
    CloseWindow();
}