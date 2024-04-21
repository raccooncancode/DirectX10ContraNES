#pragma once
#ifndef __BodyBoss3_H__
#define __BodyBoss3_H__

class Boss3;

#include "Enemy.h"
#include "BodyBoss3Animation.h"
#include "BodyBoss3State.h"
#include <unordered_map>
#include "tinyxml2.h"
class BodyBoss3 :public Enemy {
public:
	bool isInShootRange;
private:
	BodyBoss3Animation* bodyBoss3Animation;
	BodyBoss3State* currentBodyBoss3State;
	std::unordered_map<std::string, BodyBoss3State*> stateDict;
	bool isRuined;
	Boss3* parent;
public:
	BodyBoss3(int id, string name, string type, int hp, bool isRuined = false) :Enemy(id, name, type, hp) {
		this->nx = 0;
		this->ny = 0;
		this->SetSpeed(0.00, 0.00);
		this->angle = 0;
		this->isCollidable = 0;
		this->isRuined = isRuined;
		this->isInShootRange = false;
		this->bodyBoss3Animation = new BodyBoss3Animation(this);
		this->currentBodyBoss3State = new BodyBoss3State(this);
		stateDict["BodyBoss3Default"] = new BodyBoss3Default(this);
		stateDict["BodyBoss3Ruin"] = new BodyBoss3Ruin(this);
		stateDict["Dead"] = new BodyBoss3Dead(this);
		this->SetState("BodyBoss3Default", "BodyBoss3Default");
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
	void OnCollisionWith(CollisionEvent* e, float dt) override;
	void OnCollisionWithPlayer(CollisionEvent* e, float dt);
	void CreateBullet(float x, float y);
};

#endif // !__BodyBoss3_H__
