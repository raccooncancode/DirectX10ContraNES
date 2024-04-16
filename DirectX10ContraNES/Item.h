#pragma once
#ifndef __Item_H__
#define __Item_H__

#include "ItemAnimation.h"
#include "ItemState.h"
#include "GameObject.h";
#include "tinyxml2.h"

class Item :public GameObject {
public:
	bool isShowing;
	bool isOnGround;
	float maxYCanReach;
	bool isReachMaxY;
private:
	ItemAnimation* itemAnimation;
	ItemState* currentItemState;
	std::unordered_map<std::string, ItemState*> stateDict;
	GameObject* bill;
	float crow;
public:
	Item(int id, string name, string type) :GameObject(id, name, type) {
		this->nx = 1;
		this->ny = 1;
		this->isShowing = false;
		this->isOnGround = false;
		this->isReachMaxY = false;
		this->bill = NULL;
		this->SetSpeed(0.3, 1.2);
		this->itemAnimation = new ItemAnimation(this);
		this->currentItemState = new ItemState(this);
		stateDict["ItemDefault"] = new ItemDefault(this);
		stateDict["ItemHiding"] = new ItemHiding(this);
		stateDict["Dead"] = new ItemDead(this);
		this->SetState("ItemDefault", "ItemDefault");
	}
	void InitItem();
	void Update(float dt, vector<GameObject*>* objects = NULL);
	void Render();
	void LoadAssets();
	void SetState(std::string stateName, std::string animationName);
	void OnNoCollision(float dt) override;
	void OnCollisionWith(CollisionEvent* e, float dt) override;
	void OnCollisionWithPlayer(CollisionEvent* e, float dt);
	void OnCollisionWithPlayerBullet(CollisionEvent* e, float dt);
};


#endif // !__Item_H__
