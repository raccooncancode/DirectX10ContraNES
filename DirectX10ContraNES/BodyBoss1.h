#pragma once
#ifndef __BodyBoss1_H__
#define __BodyBoss1_H__

class Boss1;

#include "Enemy.h"
#include "BodyBoss1Animation.h"
#include "BodyBoss1State.h"
#include <unordered_map>
#include "tinyxml2.h"
class BodyBoss1 :public Enemy {
private:
	BodyBoss1Animation* bodyBoss1Animation;
	BodyBoss1State* currentBodyBoss1State;
	std::unordered_map<std::string, BodyBoss1State*> stateDict;
	Boss1* parent;
	bool isRuined;
public:
	BodyBoss1(int id, string name, string type, int hp, bool isRuined = false) :Enemy(id, name, type, hp) {
		this->nx = 1;
		this->ny = -1;
		this->SetSpeed(0.4, 0.4);
		this->isRuined = isRuined;
		this->bodyBoss1Animation = new BodyBoss1Animation(this);
		this->currentBodyBoss1State = new BodyBoss1State(this);
		stateDict["BodyBoss1Default"] = new BodyBoss1Default(this);
		stateDict["BodyBoss1Ruin"] = new BodyBoss1Ruin(this);
		stateDict["Dead"] = new BodyBoss1Dead(this);
		if (!this->isRuined) {
			this->SetState("BodyBoss1Default", "BodyBoss1Default");
		}
		else {
			this->isCollidable = 0;
			this->SetState("BodyBoss1Ruin", "BodyBoss1Ruin");
		}
	}
	void SetParent(Boss1* b);
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
};

#endif // !__BodyBoss1_H__
