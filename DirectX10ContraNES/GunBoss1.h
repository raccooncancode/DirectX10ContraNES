#pragma once
#ifndef __GunBoss1_H__
#define __GunBoss1_H__

class Boss1;

#include "Enemy.h"
#include "GunBoss1Animation.h"
#include "GunBoss1State.h"
#include <unordered_map>
#include "tinyxml2.h"
class GunBoss1 :public Enemy {
public:
	bool isInShootRange;
private:
	GunBoss1Animation* gunBoss1Animation;
	GunBoss1State* currentGunBoss1State;
	std::unordered_map<std::string, GunBoss1State*> stateDict;
	Boss1* parent;
	bool isRuined;
public:
	GunBoss1(int id, string name, string type,int hp,bool isRuined = false) :Enemy(id, name, type,hp) {
		this->nx = -1;
		this->ny = -1;
		this->SetSpeed(0.1, 0.1);
		this->angle = D3DX_PI + D3DX_PI / 4;
		this->isRuined = isRuined;
		this->isInShootRange = false;
		this->gunBoss1Animation = new GunBoss1Animation(this);
		this->currentGunBoss1State = new GunBoss1State(this);
		stateDict["GunBoss1Default"] = new GunBoss1Default(this);
		stateDict["GunBoss1Ruin"] = new GunBoss1Ruin(this);
		stateDict["Dead"] = new GunBoss1Dead(this);
		if (!this->isRuined) {
			this->SetState("GunBoss1Default", "GunBoss1Default");
		}
		else {
			this->SetState("GunBoss1Ruin", "GunBoss1Ruin");
			this->isCollidable = 0;
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
	void CreateBullet(float x, float y);
};

#endif // !__GunBoss1_H__
