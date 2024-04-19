#pragma once
#ifndef __Scuba_H__
#define __Scuba_H__

#include "ScubaAnimation.h"
#include "ScubaState.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Helper.h"
#include "tinyxml2.h"
#include "Platform.h"

class Scuba :public Enemy {
public:
	int ax;
	bool isOnGround;
	bool isInShootRange;
	bool isJumping;
	bool isSwimming;
	bool isShooting;
	bool isOpened;
private:
	ScubaState* currentScubaState;
	std::unordered_map<string, ScubaState*>stateDict;
	ScubaAnimation* scubaAnimation;
public:
	Scuba(int id, string name, string type, int hp) :Enemy(id, name, type, hp) {
		this->nx = -1;
		this->ny = -1;
		this->ax = 0;
		this->isJumping = false;
		this->isSwimming = false;
		this->isOnGround = false;
		this->isOpened = false;
		this->SetSpeed(0.1, 0.1);
		this->scubaAnimation = new ScubaAnimation(this);
		this->currentScubaState = new ScubaState(this);
		stateDict["Dead"] = new ScubaDead(this);
		stateDict["ScubaHiding"] = new ScubaHiding(this);
		stateDict["ScubaShowing"] = new ScubaShowing(this);
		stateDict["ScubaShooting"] = new ScubaShooting(this);
		SetState("ScubaHiding", "ScubaHiding");
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

#endif // !__Scuba_H__
