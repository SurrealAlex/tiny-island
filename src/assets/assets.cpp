#include "assets.h"

Assets::Assets()
{
    //Load map tile assets
    _grassTile = LoadImage("res/sprites/tiles/grass.png");
    _sandTile = LoadImage("res/sprites/tiles/sand.png");
    _waterTile = LoadImage("res/sprites/tiles/water.png");
    ImageResizeNN(&_grassTile, tileSize, tileSize);
    ImageResizeNN(&_sandTile, tileSize, tileSize);
    ImageResizeNN(&_waterTile, tileSize, tileSize);
    grassTile = LoadTextureFromImage(_grassTile);
    sandTile = LoadTextureFromImage(_sandTile);
    waterTile = LoadTextureFromImage(_waterTile);
    assetList["grassTile"] = &grassTile;
    assetList["sandTile"] = &sandTile;
    assetList["waterTile"] = &waterTile;

    //Load player assets
    _dIdle = LoadImage("res/sprites/player/d_idle.png");
    _dWalk1 = LoadImage("res/sprites/player/d_walk1.png");
    _dWalk2 = LoadImage("res/sprites/player/d_walk2.png");
    _lIdle = LoadImage("res/sprites/player/l_idle.png");
    _lWalk1 = LoadImage("res/sprites/player/l_walk1.png");
    _lWalk2 = LoadImage("res/sprites/player/l_walk2.png");
    _rIdle = LoadImage("res/sprites/player/r_idle.png");
    _rWalk1 = LoadImage("res/sprites/player/r_walk1.png");
    _rWalk2 = LoadImage("res/sprites/player/r_walk2.png");
    _uIdle = LoadImage("res/sprites/player/u_idle.png");
    _uWalk1 = LoadImage("res/sprites/player/u_walk1.png");
    _uWalk2 = LoadImage("res/sprites/player/u_walk2.png");
    ImageResizeNN(&_dIdle, tileSize / 2, tileSize / 2);
    ImageResizeNN(&_dWalk1, tileSize / 2, tileSize / 2);
    ImageResizeNN(&_dWalk2, tileSize / 2, tileSize / 2);
    ImageResizeNN(&_lIdle, tileSize / 2, tileSize / 2);
    ImageResizeNN(&_lWalk1, tileSize / 2, tileSize / 2);
    ImageResizeNN(&_lWalk2, tileSize / 2, tileSize / 2);
    ImageResizeNN(&_rIdle, tileSize / 2, tileSize / 2);
    ImageResizeNN(&_rWalk1, tileSize / 2, tileSize / 2);
    ImageResizeNN(&_rWalk2, tileSize / 2, tileSize / 2);
    ImageResizeNN(&_uIdle, tileSize / 2, tileSize / 2);
    ImageResizeNN(&_uWalk1, tileSize / 2, tileSize / 2);
    ImageResizeNN(&_uWalk2, tileSize / 2, tileSize / 2);
    dIdle = LoadTextureFromImage(_dIdle);
    dWalk1 = LoadTextureFromImage(_dWalk1);
    dWalk2 = LoadTextureFromImage(_dWalk2);
    lIdle = LoadTextureFromImage(_lIdle);
    lWalk1 = LoadTextureFromImage(_lWalk1);
    lWalk2 = LoadTextureFromImage(_lWalk2);
    rIdle = LoadTextureFromImage(_rIdle);
    rWalk1 = LoadTextureFromImage(_rWalk1);
    rWalk2 = LoadTextureFromImage(_rWalk2);
    uIdle = LoadTextureFromImage(_uIdle);
    uWalk1 = LoadTextureFromImage(_uWalk1);
    uWalk2 = LoadTextureFromImage(_uWalk2);
    assetList["dIdle"] = &dIdle;
    assetList["dWalk1"] = &dWalk1;
    assetList["dWalk2"] = &dWalk2;
    assetList["uIdle"] = &uIdle;
    assetList["uWalk1"] = &uWalk1;
    assetList["uWalk2"] = &uWalk2;
    assetList["rIdle"] = &rIdle;
    assetList["rWalk1"] = &rWalk1;
    assetList["rWalk2"] = &rWalk2;
    assetList["lIdle"] = &lIdle;
    assetList["lWalk1"] = &lWalk1;
    assetList["lWalk2"] = &lWalk2;

    //Tree sprites
    _treeSprite = LoadImage("res/sprites/entity/tree.png");
    _palmSprite = LoadImage("res/sprites/entity/palm.png");
    ImageResizeNN(&_treeSprite, tileSize, tileSize);
    ImageResizeNN(&_palmSprite, tileSize, tileSize);
    treeSprite = LoadTextureFromImage(_treeSprite);
    palmSprite = LoadTextureFromImage(_palmSprite);
    assetList["treeSprite"] = &treeSprite;
    assetList["palmSprite"] = &palmSprite;

    //Rock sprites
    _rockSprite = LoadImage("res/sprites/entity/rock.png");
    ImageResizeNN(&_rockSprite, tileSize, tileSize);
    rockSprite = LoadTextureFromImage(_rockSprite);
    assetList["rockSprite"] = &rockSprite;

    //Items
    _stickItem = LoadImage("res/sprites/items/stick.png");
    _wormItem = LoadImage("res/sprites/items/worm.png");
    _wormItem2 = LoadImage("res/sprites/items/worm2.png");
    _coconutItem = LoadImage("res/sprites/items/coconut.png");
    ImageResizeNN(&_stickItem, tileSize / 4, tileSize / 4);
    ImageResizeNN(&_wormItem, tileSize / 4, tileSize / 4);
    ImageResizeNN(&_wormItem2, tileSize / 4, tileSize / 4);
    ImageResizeNN(&_coconutItem, tileSize / 6, tileSize / 6);
    stickItem = LoadTextureFromImage(_stickItem);
    wormItem = LoadTextureFromImage(_wormItem);
    coconutItem = LoadTextureFromImage(_coconutItem);
    wormItem2 = LoadTextureFromImage(_wormItem2);
    assetList["Stick"] = &stickItem;
    assetList["Worm"] = &wormItem;
    assetList["Worm2"] = &wormItem2;
    assetList["Coconut"] = &coconutItem;


    //Cleanup memory
    unloadImages();
}

void Assets::unloadImages()
{
    UnloadImage(_grassTile);
    UnloadImage(_sandTile);
    UnloadImage(_waterTile);
    UnloadImage(_dIdle);
    UnloadImage(_dWalk1);
    UnloadImage(_dWalk2);
    UnloadImage(_uIdle);
    UnloadImage(_uWalk1);
    UnloadImage(_uWalk2);
    UnloadImage(_lIdle);
    UnloadImage(_lWalk1);
    UnloadImage(_lWalk2);
    UnloadImage(_rIdle);
    UnloadImage(_rWalk1);
    UnloadImage(_rWalk2);
    UnloadImage(_treeSprite);
    UnloadImage(_palmSprite);
    UnloadImage(_rockSprite);
    UnloadImage(_stickItem);
    UnloadImage(_wormItem);
    UnloadImage(_wormItem2);
    UnloadImage(_coconutItem);
}

void Assets::unloadTextures()
{
    UnloadTexture(grassTile);
    UnloadTexture(sandTile);
    UnloadTexture(waterTile);
    UnloadTexture(dIdle);
    UnloadTexture(dWalk1);
    UnloadTexture(dWalk2);
    UnloadTexture(uIdle);
    UnloadTexture(uWalk1);
    UnloadTexture(uWalk2);
    UnloadTexture(lIdle);
    UnloadTexture(lWalk1);
    UnloadTexture(lWalk2);
    UnloadTexture(rIdle);
    UnloadTexture(rWalk1);
    UnloadTexture(rWalk2);
    UnloadTexture(treeSprite);
    UnloadTexture(palmSprite);
    UnloadTexture(rockSprite);
    UnloadTexture(stickItem);
    UnloadTexture(wormItem);
    UnloadTexture(wormItem2);
    UnloadTexture(coconutItem);
}

Texture2D* Assets::get(std::string assetName)
{
    auto it = assetList.find(assetName);
    if (it != assetList.end()) {
        return it->second;
    } else {
        return nullptr;
    }
}