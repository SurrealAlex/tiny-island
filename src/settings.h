#pragma once

/* --- DEBUG --- */
constexpr bool SHOW_DEBUG_MENU = true; //Flag to display debug menu on screen
constexpr bool SHOW_HITBOXES = false; //Flag to draw entity hitboxes
constexpr bool SHOW_CENTER_POINTS = false; //Flag to draw entity center points

/* --- GRAPHICS --- */
constexpr int RAW_TILE_SIZE = 32; //Side length of raw tile sprite in pixels
constexpr float TILE_SCALE = 6.0f; //Scale multiplier for tile sprites
constexpr int CAMERA_COLUMNS = 7; //Total width of screen in tiles
constexpr int CAMERA_ROWS = 5; //Total height of screen in tiles
constexpr int TARGET_FPS = 60;

constexpr int tileSize = RAW_TILE_SIZE * TILE_SCALE; //Final size of rendered tiles in pixels
constexpr int screenWidth = tileSize * CAMERA_COLUMNS; //Width of screen in pixels
constexpr int screenHeight = tileSize * CAMERA_ROWS; //Height of screen in pixels

/* --- MAP GEN --- */
constexpr int MAP_COLUMNS = 99; //Total number of tile columns in the map
constexpr int MAP_ROWS = 99; //Total number of tile rows in the map
constexpr float LAND_PERCENTAGE = 0.57f; //Percentage of the map to be occupied by land, represented as a decimal
constexpr int NUM_OF_LAKES = 10; //Number of lake seeds to generate
constexpr float LAKE_PERCENTAGE = 0.37f; //Percentage of the map to be occupied by lakes, represented as a decimal
constexpr int NUM_OF_RIVERS = 4; //Number of river seeds to generate
constexpr int CLEANUP_ITERATIONS = 20; //Number of cycles to clean up shores

/* --- MINIMAP --- */
constexpr int MINIMAP_SCALE = 2; //Sidelength of tile as represented in minimap in pixels
constexpr int MINIMAP_OFFSET_X = -10; //Minimap offset from corner in X direction
constexpr int MINIMAP_OFFSET_Y = 10; //Minimap offset from corner in Y direction
constexpr int minimapPlayerRadius = MINIMAP_SCALE * 2;

/* --- ENTITY GEN --- */
constexpr int TREE_CHANCE = 12; //Chance a tree will spawn at an given tile, expressed as odds ("1 in _")
constexpr int TREE_MAX = 800; //Number of trees to generate
constexpr int ROCK_CHANCE = 25; //Chacne a rock will spawn at any given tile, expressed as odds ("1 in _")
constexpr int ROCK_MAX = 240; // Number of rocks to generate

/* --- PLAYER  --- */
constexpr int WALK_SPEED = 5; //Base player walking speed
constexpr int SPRINT_SPEED = 8; //Base player sprinting speed
constexpr int NDT = (tileSize / 3); //"Nearby Distance Threshold" - Minimum distance required between player and entity for player to interact with it

/* --- INVENTORY --- */
constexpr int INVENTORY_SIZE = 36; //Number of inventory storage slots