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

#include "Soldier.h"
#include "Sniper.h"
#include "RotatingGun.h"
#include "Cannon.h"
#include "Bridge.h"
#include "StaticWeapon.h"

#include "Scene.h"
class Map :public Scene{
public:
	bool isFinish;
	std::vector<GameObject*> movingObjects;
	std::unordered_map<int, GameObject*> mObjects;
	std::unordered_map<int, GameObject*> sObjects;
	std::vector<GameObject*> staticObjects;
	std::vector<GameObject*> allObjects;
private:
	Bound mapBound;
	int mapStage;
	int mapRows, mapColumns;
	int tileSize;
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
	void AddMovingObject(GameObject* o); // to add bullets to btree
	void AddStaticObject(GameObject* o);
	void Update(float dt);
	void Render();//render rectangle which is overlapped or contain by camera bound
	void Clear();
private:
	void ReadMapFile();
	void LoadMap2D(tinyxml2::XMLElement* e);
	void LoadObjects(tinyxml2::XMLElement* e);
};

#endif // !__MAP_H__

