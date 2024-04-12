#pragma once
#ifndef __MAP_H__
#define __MAP_H__

#include "GameObject.h"
#include "tinyxml2.h"
#include <vector>
#include <string>
#include "Tile.h"
#include "Platform.h"
#include "Bill.h"
#include "BTree.h"
class Map {
public:
	bool isFinish;
private:
	Bill* bill;
	int mapStage;
	int mapRows, mapColumns;
	int tileSize;
	std::vector<GameObject*> testObjects;
	std::unordered_map<int,GameObject*> platformsInCurrentMap; 
	std::unordered_map<int,GameObject*> objectsInCurrentMap; 
	std::unordered_map<int,GameObject*> objectsInCurrentCamera;
	std::vector<GameObject*> bulletsInCurrentCamera;
	std::vector<std::vector<int>>map2D;
	tinyxml2::XMLElement* xmlRoot;
	Tile* tile;
	Bound test;
	//BTree
	BTree* btree;
	bool isSplitVertical;
public:
	Map(int stage,bool isSplitVertical = true);
	~Map();
	void Update(float dt);
	void Render();//render rectangle which is overlapped or contain by camera bound
private:
	void ReadMapFile();
	void LoadMap2D(tinyxml2::XMLElement* e);
	void LoadObjects(tinyxml2::XMLElement* e);
};

#endif // !__MAP_H__

