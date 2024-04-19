#pragma once
#ifndef __Stone_H__
#define __Stone_H__


#include "Enemy.h"
#include "StoneAnimation.h"
#include "StoneState.h"
#include <unordered_map>
#include "tinyxml2.h"
class Stone :public Enemy {
public:
	bool isInShootRange;
private:
	StoneAnimation* stoneAnimation;
	StoneState* currentStoneState;
	std::unordered_map<std::string, StoneState*> stateDict;
	bool isRuined;
public:
	Stone(int id, string name, string type, int hp, bool isRuined = false) :Enemy(id, name, type, hp) {
		this->nx = 0;
		this->ny = -1;
		this->SetSpeed(0.00, 0.00);
		this->angle = 0;
		this->isRuined = isRuined;
		this->isInShootRange = false;
		this->stoneAnimation = new StoneAnimation(this);
		this->currentStoneState = new StoneState(this);
		stateDict["StoneDefault"] = new StoneDefault(this);
		stateDict["StoneRuin"] = new StoneRuin(this);
		stateDict["Dead"] = new StoneDead(this);
		this->SetState("StoneDefault", "StoneDefault");
	}
	void Update(float dt, vector<GameObject*>* objects = NULL);
	void Render();
	void LoadAssets();
	int GetAx()override {
		return 0;
	}
	void SetState(std::string stateName, std::string animationName);
	void OnNoCollision(float dt) override;
	void OnCollisionWith(CollisionEvent* e, float dt) override;
	void OnCollisionWithPlayer(CollisionEvent* e, float dt);
	void CreateBullet(float x, float y);
};

#endif // !__Stone_H__
