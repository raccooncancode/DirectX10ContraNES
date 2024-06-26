#pragma once
#ifndef __BILL_H__
#define __BILL_H__

#include "GameObject.h"
#include "IControlable.h"
#include "InputManager.h"
#include "BillAnimation.h"
#include "BillState.h"
#include <unordered_map>
#include <string>
#include "Helper.h"
#include "tinyxml2.h"
#include "Platform.h"
#include "Bullet.h"
class Map;

using namespace std;
class Bill:public GameObject, public IControlable {
public:
	bool isClearStage;
	int ax;
	bool isLaying;
	bool isOnGround;
	bool isJumping;
	bool isSwimming;
	int respawnTimes;
	int bulletType;
	float timeBulletType;
	Map* map;
	GameObject* boss;
private:
	unordered_map<string, BillState*> stateDict;
	BillState* currentBillState;
	BillAnimation* billAnimation;
	LPTEXTURE lifeTex;
	vector<LPSPRITE> lifeSprites;
public:
	Bill(int id, string name, string type) :GameObject(id, name, type) {
		isOnGround = false;
		isClearStage = false;
		isLaying = false;
		isJumping = false;
		isSwimming = false;
		respawnTimes = 5;
		timeBulletType = 0;
		this->ax = 1;
		this->bulletType = 0;
		SetSpeed(0.1, 0.1);
		billAnimation = new BillAnimation(this);
		currentBillState = new BillState(this);
		stateDict["Dead"] = new BillDead(this);
		stateDict["Running0"] = new BillRunning0(this);
		stateDict["Running45"] = new BillRunning45(this);
		stateDict["Running315"] = new BillRunning315(this);
		stateDict["RunningShooting0"] = new BillRunningShooting0(this);
		stateDict["Laying0"] = new BillLaying0(this);
		stateDict["Jumping0"] = new BillJumping0(this);
		stateDict["Falling0"] = new BillFalling0(this);
		stateDict["Standing0"] = new BillStanding0(this);
		stateDict["Standing90"] = new BillStanding90(this);
		stateDict["Swimming"] = new BillSwimming(this);
		stateDict["Swimming0"] = new BillSwimming0(this);
		stateDict["Swimming45"] = new BillSwimming45(this);
		stateDict["Swimming90"] = new BillSwimming90(this);
		SetNy(-1);
		SetNx(0);
		SetAngle(0);
		SetState("Falling0", Helper::aXToString(ax) + "Falling0");
		this->lifeTex = TextureManager::GetInstance()->Get(18);
		for (int i = 0; i < respawnTimes; i++) {
			auto lifeSprite = new CSprite(0, 0,12,16, lifeTex);
			lifeSprites.push_back(lifeSprite);
		}
		InputManager::GetInstance()->RegisterListener(this);
	}
	float GetNx() { return this->nx; }
	float GetVx() { return this->vx; }
	float GetVy() { return this->vy; }
	void SetNx(int nx) { this->nx = nx; }
	void SetNy(int ny) { this->ny = ny; }
	void SetVy(float vy) { this->vy = vy; }
	void SetState(std::string stateName, std::string animationName);
	void OnKeyDown(int keyCode) override;
	void OnKeyUp(int keyCode) override;

	void Update(float dt,vector<GameObject*>* objects=NULL);
	void Render();
	void LoadAssets();
	
	void CreateBullet(float x,float y);
	void OnNoCollision(float dt) override;
	void OnCollisionWith(CollisionEvent* e, float dt) override;
	void OnCollisionWithItem(CollisionEvent* e, float dt);
	void DecreaseHP();
	void ResetBulletType(float dt);
};

#endif // !__BILL_H__
