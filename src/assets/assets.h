#pragma once

#include "../settings.h"

#include <raylib.h>
#include <string>
#include <map>

/*
*** Raw image files are prefixed with an underscore - "_grassTile"
*** Textures loaded from raw images are not prefixed - "grassTile"
*/

class Assets {
    public:
        //Map tile assets
        Image _grassTile, _sandTile, _waterTile;
        Texture2D grassTile, sandTile, waterTile;

        //Player assets
        Image _uIdle, _uWalk1, _uWalk2, _rIdle, _rWalk1, _rWalk2, _dIdle, _dWalk1, _dWalk2, _lIdle, _lWalk1, _lWalk2;
        Texture2D uIdle, uWalk1, uWalk2, rIdle, rWalk1, rWalk2, dIdle, dWalk1, dWalk2, lIdle, lWalk1, lWalk2;

        //Tree assets
        Image _treeSprite;
        Texture2D treeSprite;

        //Rock assets
        Image _rockSprite;
        Texture2D rockSprite;

        //Item assets
        Image _stickItem;
        Texture2D stickItem;

        //Asset map
        std::map<std::string, Texture2D*> assetList;

        //Functions
        Assets();
        void unloadImages();
        void unloadTextures();
        Texture2D* get(std::string assetName);
};