#pragma once
#ifndef __ROTATINGGUN_H__
#define __ROTATINGGUN_H__

#include "RotatingGunAnimation.h"
#include "RotatingGunState.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Helper.h"
#include "tinyxml2.h"
#include "Platform.h"

class RotatingGun:public Enemy {
public:
	int ax;
	bool isOnGround;
	bool isInShootRange;
	bool isJumping;
	bool isSwimming;
	bool isShooting;
	bool isOpened;
private:
	RotatingGunState* currentRotatingGunState;
	std::unordered_map<string, RotatingGunState*>stateDict;
	RotatingGunAnimation* rotatingGunAnimation;
public:
	RotatingGun(int id, string name, string type, int hp) :Enemy(id, name, type, hp) {
		this->nx = -1;
		this->ny = -1;
		this->ax = 0;
		this->isJumping = false;
		this->isSwimming = false;
		this->isOnGround = false;
		this->isOpened = false;
		this->SetSpeed(0.1, 0.1);
		this->rotatingGunAnimation = new RotatingGunAnimation(this);
		this->currentRotatingGunState = new RotatingGunState(this);
		stateDict["GunOpen"] = new RotatingGunOpen(this);
		stateDict["GunClose"] = new RotatingGunClose(this);
		stateDict["GunRotate0"] = new RotatingGun0(this);
		stateDict["GunRotate45"] = new RotatingGun45(this);
		stateDict["GunRotate90"] = new RotatingGun90(this);
		stateDict["GunRotate135"] = new RotatingGun135(this);
		stateDict["GunRotate180"] = new RotatingGun180(this);
		stateDict["GunRotate225"] = new RotatingGun225(this);
		stateDict["GunRotate270"] = new RotatingGun270(this);
		stateDict["GunRotate315"] = new RotatingGun315(this);
		stateDict["Dead"] = new RotatingGunDead(this);
		SetState("GunClose", "GunClose");
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
	void Rotate();
};

#endif // !__ROTATINGGUN_H__
