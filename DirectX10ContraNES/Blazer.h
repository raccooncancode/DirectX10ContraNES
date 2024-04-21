#pragma once
#ifndef __Blazer_H__
#define __Blazer_H__


#include "Enemy.h"
#include "BlazerAnimation.h"
#include "BlazerState.h"
#include <unordered_map>
#include "tinyxml2.h"
class Blazer :public Enemy {
public:
	bool isInShootRange;
private:
	BlazerAnimation* blazerAnimation;
	BlazerState* currentBlazerState;
	std::unordered_map<std::string, BlazerState*> stateDict;
	bool isRuined;
public:
	Blazer(int id, string name, string type, int hp, bool isRuined = false) :Enemy(id, name, type, hp) {
		this->nx = -1;
		this->ny = -1;
		this->SetSpeed(0.02, 0.05);
		this->angle = 0;
		this->isRuined = isRuined;
		this->isInShootRange = false;
		this->blazerAnimation = new BlazerAnimation(this);
		this->currentBlazerState = new BlazerState(this);
		stateDict["BlazerDefault"] = new BlazerDefault(this);
		stateDict["BlazerRuin"] = new BlazerRuin(this);
		stateDict["Dead"] = new BlazerDead(this);
		this->SetState("BlazerDefault", "BlazerDefault");
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

#endif // !__Blazer_H__
