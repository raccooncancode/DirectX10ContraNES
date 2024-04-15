#pragma once
#ifndef __BRIDGE_H__
#define __BRIDGE_H__

#include "GameObject.h"
#include "BridgeHead.h"
#include "BridgeBody.h"
#include <vector>
class Bridge : public GameObject {
public:
	BridgeHead* bH;
	BridgeBody* bB1;
	BridgeBody* bB2;
	BridgeBody* bB3;
	GameObject* currentChild;
	int currentChildIndex = 0;
	std::vector<GameObject*> childs;
public:
	Bridge(int id, string name, string type,float x,float y) :GameObject(id,name,type) {
		//this->Init(x,y);
		//childs.push_back(new BridgeHead(5, "BridgeHead", "Bridge"));
	}
	void Init(float x,float y);
	void Update(float dt, vector<GameObject*>* objects = NULL);
	void Render();
	void LoadAssets();
};

#endif // !__BRIDGE_H__
