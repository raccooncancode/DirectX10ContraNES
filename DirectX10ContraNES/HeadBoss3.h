#pragma once
#ifndef __HeadBoss3_H__
#define __HeadBoss3_H__

class Boss3;

#include "Enemy.h"
#include "HeadBoss3Animation.h"
#include "HeadBoss3State.h"
#include <unordered_map>
#include "tinyxml2.h"
class HeadBoss3 :public Enemy {
public:
	bool isInShootRange;
private:
	HeadBoss3Animation* headBoss3Animation;
	HeadBoss3State* currentHeadBoss3State;
	std::unordered_map<std::string, HeadBoss3State*> stateDict;
	bool isRuined;
	Boss3* parent;
public:
	HeadBoss3(int id, string name, string type, int hp, bool isRuined = false) :Enemy(id, name, type, hp) {
		this->nx = 0;
		this->ny = 0;
		this->SetSpeed(0.00, 0.00);
		this->angle = 0;
		this->isCollidable = 0;
		this->isRuined = isRuined;
		this->isInShootRange = false;
		this->headBoss3Animation = new HeadBoss3Animation(this);
		this->currentHeadBoss3State = new HeadBoss3State(this);
		stateDict["HeadBoss3Default"] = new HeadBoss3Default(this);
		stateDict["HeadBoss3Ruin"] = new HeadBoss3Ruin(this);
		stateDict["HeadBoss3Shooting"] = new HeadBoss3Shooting(this);
		stateDict["Dead"] = new HeadBoss3Dead(this);
		this->SetState("HeadBoss3Default", "HeadBoss3Default");
	}
	void Update(float dt, vector<GameObject*>* objects = NULL);
	void Render();
	void LoadAssets();
	int GetAx()override {
		return 0;
	}
	void SetState(std::string stateName, std::string animationName);
	void OnNoCollision(float dt) override;
	void SetParent(Boss3* p);
	Boss3* GetParent() { return this->parent; }
	void OnCollisionWith(CollisionEvent* e, float dt) override;
	void OnCollisionWithPlayer(CollisionEvent* e, float dt);
	void CreateBullet(float x, float y);
};

#endif // !__HeadBoss3_H__
