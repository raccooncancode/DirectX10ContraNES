#pragma once
#ifndef __SOLDIER_H__
#define __SOLDIER_H__

#include "Enemy.h"
#include "Bullet.h"
#include "SoldierAnimation.h"
#include "SoldierState.h"
#include "tinyxml2.h"
#include "Helper.h"
#include "Platform.h"
#include <unordered_map>
class Soldier : public Enemy{
public:
	int ax;
	bool isOnGround;
	bool isInShootRange;
	bool isJumping;
	bool isSwimming;
	vector<Bullet*> bullets;
private:
	SoldierState* currentSoldierState;
	std::unordered_map<std::string, SoldierState*> stateDict;
	SoldierAnimation* soldierAnimation;
public:
	Soldier(int id, string name, string type, int hp) :Enemy(id, name, type, hp) {
		this->nx = -1;
		this->ny = -1;
		this->ax = -1;
		this->isJumping = false;
		this->isSwimming = false;
		this->isOnGround = false;
		this->SetSpeed(0.01, 0.1);
		soldierAnimation = new SoldierAnimation(this);
		currentSoldierState = new SoldierState(this);
		stateDict["Running"] = new SoldierRunning(this);
		stateDict["Laying"] = new SoldierLaying(this);
		stateDict["Jumping"] = new SoldierJumping(this);
		stateDict["Shooting"] = new SoldierShooting(this);
		stateDict["Falling"] = new SoldierFalling(this);
		stateDict["Dead"] = new SoldierDead(this);
		SetState("Falling", Helper::aXToString(this->ax) + "Falling");
	}
	float GetNx() { return this->nx; }
	float GetVx() { return this->vx; }
	float GetVy() { return this->vy; }
	int GetAx() override { return this->ax; }
	void SetNx(int nx) { this->nx = nx; }
	void SetNy(int ny) { this->ny = ny; }
	void SetVy(float vy) { this->vy = vy; }
	void SetState(std::string stateName, std::string animationName)override;

	void Update(float dt, vector<GameObject*>* objects = NULL);
	void Render();
	void LoadAssets();

	void OnNoCollision(float dt) override;
	void OnCollisionWith(CollisionEvent* e, float dt) override;
	void OnCollisionWithPlayer(CollisionEvent* e, float dt);
	void OnCollisionWithBullet(CollisionEvent* e, float dt);
};

#endif // !__SOLDIER_H__
