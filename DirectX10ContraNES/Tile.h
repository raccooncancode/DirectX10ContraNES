#pragma once
#ifndef __TILE_H__
#define __TILE_H__

#include "Animation.h"
#include <unordered_map>
#include <vector>
#include "tinyxml2.h"

class Tile {
private:
	int tileSize;
	LPTEXTURE tileTexture;
	std::vector<std::vector<int>> map2D;
	std::unordered_map<int, LPSPRITE> tiles;
	std::unordered_map<int, LPANIMATION> animationTiles;
public:
	void LoadTileSetTexture(LPTEXTURE tex);
	void LoadMap2D(std::vector<std::vector<int>>& data);
	void LoadTiles(int tileSizes);
	void LoadAnimationTiles(tinyxml2::XMLElement* e);
	void Update(float dt);
	void Render();
};

#endif // !__TILE_H__
