#include "game.h"
#include "../settings.h"
#include "../assets/assets.h"
#include "../map/map.h"
#include "../entities/mobs/player.h"
#include "../entities/entity_handler.h"
#include "../gui/minimap.h"
#include "../gui/hud.h"
#include "../gui/menu.h"
#include "../utils/utilities.h"
#include <iostream>
#include <raylib.h>

void Game::run()
{
    //Init window
    Image icon = LoadImage("res/sprites/player/d_idle.png");
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Tiny Island - Pre-Alpha Development");
    SetWindowIcon(icon);
    UnloadImage(icon);
    SetTargetFPS(TARGET_FPS);
    BeginDrawing();
    ClearBackground(BLACK);
    EndDrawing();

    //Init game objects
    gameState = GameState::Playing;
    Assets assets;
    Map map;
    EntityHandler entities;
    Hud headsUpDisplay;

    //Init game
    map.generate();
    entities.generateEntities(map);

    //Game loop
    while (!WindowShouldClose())
    {
        if (gameState == GameState::Playing)
        {
            //Listen for events
            entities.events(map);
            headsUpDisplay.events();

            //Update objects
            map.update();
            entities.update(map);
            headsUpDisplay.update();

            //Render
            BeginDrawing();
                ClearBackground(BLACK);
                map.draw(assets);
                entities.draw(map, assets);
                headsUpDisplay.draw();
            EndDrawing();
        }
    }

    //Cleanup
    assets.unloadTextures();
    CloseWindow();
}
