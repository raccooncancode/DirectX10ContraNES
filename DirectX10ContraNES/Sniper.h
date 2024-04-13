#pragma once
#ifndef __SNIPER_H__
#define __SNIPER_H__

#include "SniperAnimation.h"
#include "SniperState.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Helper.h"
#include "tinyxml2.h"
#include "Platform.h"
class Sniper:public Enemy {
public:
	int ax;
	bool isOnGround;
	bool isInShootRange;
	bool isJumping;
	bool isSwimming;
	bool isHiding;
	bool isShooting;
private:
	SniperState* currentSniperState;
	std::unordered_map<string, SniperState*>stateDict;
	SniperAnimation* sniperAnimation;
public:
	Sniper(int id, string name, string type, int hp,bool isHiding=false) : Enemy(id, name, type, hp) {
		this->nx = 0;
		this->ny = isHiding == false ? -1 : 0;
		this->ax = -1;
		this->isJumping = false;
		this->isSwimming = false;
		this->isOnGround = false;
		this->isHiding = isHiding;
		this->SetSpeed(0.0, 0.1);
		this->sniperAnimation = new SniperAnimation(this);
		this->currentSniperState = new SniperState(this);
		stateDict["Shooting0"] = new SniperShooting0(this);
		stateDict["Shooting45"] = new SniperShooting45(this);
		stateDict["Shooting315"] = new SniperShooting315(this);
		stateDict["HidingShooting0"] = new SniperHidingShooting0(this);
		stateDict["Dead"] = new SniperDead(this);
		if(!this->isHiding)
			SetState("Shooting0", Helper::aXToString(this->ax) + "Shooting0");
		else
			SetState("HidingShooting0", Helper::aXToString(this->ax) + "HidingShooting0");

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

#endif // !__SNIPER_H__
