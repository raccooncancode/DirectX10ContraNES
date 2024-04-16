#pragma once
#ifndef __Capsule_H__
#define __Capsule_H__

#include "CapsuleAnimation.h"
#include "CapsuleState.h"
#include "GameObject.h";
#include "tinyxml2.h"

class Capsule :public GameObject {
public:
	bool isShowing;
private:
	CapsuleAnimation* capsuleAnimation;
	CapsuleState* currentCapsuleState;
	std::unordered_map<std::string, CapsuleState*> stateDict;
	GameObject* bill;
	float crow;
public:
	Capsule(int id, string name, string type) :GameObject(id, name, type) {
		this->nx = 1;
		this->ny = 1;
		this->isShowing = false;
		this->bill = NULL;
		this->SetSpeed(1, 3.5);
		this->capsuleAnimation = new CapsuleAnimation(this);
		this->currentCapsuleState = new CapsuleState(this);
		stateDict["CapsuleDefault"] = new CapsuleDefault(this);
		stateDict["CapsuleHiding"] = new CapsuleHiding(this);
		stateDict["Dead"] = new CapsuleDead(this);
		this->SetState("CapsuleHiding", "CapsuleHiding");
	}
	void Update(float dt, vector<GameObject*>* objects = NULL);
	void Render();
	void LoadAssets();
	void SetState(std::string stateName, std::string animationName);
	void OnNoCollision(float dt) override;
	void OnCollisionWith(CollisionEvent* e, float dt) override;
	void OnCollisionWithPlayer(CollisionEvent* e, float dt);
	void OnCollisionWithPlayerBullet(CollisionEvent* e, float dt);
};


#endif // !__Capsule_H__
