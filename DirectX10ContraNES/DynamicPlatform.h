#pragma once
#ifndef __DynamicPlatform_H__
#define __DynamicPlatform_H__


#include "Platform.h"
#include "DynamicPlatformAnimation.h"
#include "DynamicPlatformState.h"
#include <unordered_map>
#include "tinyxml2.h"
class DynamicPlatform :public Platform {
public:
private:
	DynamicPlatformAnimation* dynamicPlatformAnimation;
	DynamicPlatformState* currentDynamicPlatformState;
	std::unordered_map<std::string, DynamicPlatformState*> stateDict;
	bool isRuined;
public:
	DynamicPlatform(int id, string name, string type) :Platform(id, name, type) {
		this->nx = -1;
		this->ny = 0;
		this->SetSpeed(0.05, 0.00);
		this->angle = 0;
		this->isRuined = isRuined;
		this->dynamicPlatformAnimation = new DynamicPlatformAnimation(this);
		this->currentDynamicPlatformState = new DynamicPlatformState(this);
		stateDict["DynamicPlatformDefault"] = new DynamicPlatformDefault(this);
		stateDict["DynamicPlatformRuin"] = new DynamicPlatformRuin(this);
		stateDict["Dead"] = new DynamicPlatformDead(this);
		this->SetState("DynamicPlatformDefault", "DynamicPlatformDefault");
	}
	void Update(float dt, vector<GameObject*>* objects = NULL);
	void Render();
	void LoadAssets();
	void SetState(std::string stateName, std::string animationName);
	void OnNoCollision(float dt) override;
	void OnCollisionWith(CollisionEvent* e, float dt) override;
	void OnCollisionWithPlayer(CollisionEvent* e, float dt);
	void CreateBullet(float x, float y);
};

#endif // !__DynamicPlatform_H__
