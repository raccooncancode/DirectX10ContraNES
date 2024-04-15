#pragma once
#ifndef __CANNON_H__
#define __CANNON_H__

#include "CannonAnimation.h"
#include "CannonState.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Helper.h"
#include "tinyxml2.h"
#include "Platform.h"

class Cannon :public Enemy{
public:
	int ax;
	bool isOnGround;
	bool isInShootRange;
	bool isJumping;
	bool isSwimming;
	bool isShooting;
	bool isOpened;
private:
	CannonState* currentCannonState;
	std::unordered_map<string, CannonState*>stateDict;
	CannonAnimation* cannonAnimation;
public:
	Cannon(int id, string name, string type, int hp) :Enemy(id, name, type, hp) {
		this->nx = -1;
		this->ny = -1;
		this->ax = 0;
		this->isJumping = false;
		this->isSwimming = false;
		this->isOnGround = false;
		this->isOpened = false;
		this->SetSpeed(0.1, 0.1);
		this->cannonAnimation = new CannonAnimation(this);
		this->currentCannonState = new CannonState(this);
		stateDict["Dead"] = new CannonDead(this);
		stateDict["CannonHiding"] = new CannonHiding(this);
		stateDict["CannonShowing"] = new CannonShowing(this);
		stateDict["CannonShooting"] = new CannonShooting(this);
		SetState("CannonHiding", "CannonHiding");
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

	void CreateBullet(float x, float y);
	void OnNoCollision(float dt) override;
	void OnCollisionWith(CollisionEvent* e, float dt) override;
	void OnCollisionWithPlayer(CollisionEvent* e, float dt);
	void OnCollisionWithBullet(CollisionEvent* e, float dt);
};

#endif // !__CANNON_H__
