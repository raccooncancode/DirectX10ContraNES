#pragma once
#ifndef __STATICWEAPON_H__
#define __STATICWEAPON_H__

#include "StaticWeaponAnimation.h"
#include "StaticWeaponState.h"
#include "GameObject.h";
#include "tinyxml2.h"

class StaticWeapon :public GameObject {
private:
	StaticWeaponAnimation* staticWeaponAnimation;
	StaticWeaponState* currentStaticWeaponState;
	std::unordered_map<std::string, StaticWeaponState*> stateDict;
	GameObject* bill;
public:
	StaticWeapon(int id, string name, string type) :GameObject(id, name, type) {
		this->nx = -1;
		this->ny = 1;
		this->SetSpeed(0.1, 0.1);
		this->staticWeaponAnimation = new StaticWeaponAnimation(this);
		this->currentStaticWeaponState = new StaticWeaponState(this);
		stateDict["StaticWeaponDefault"] = new StaticWeaponDefault(this);
		stateDict["Dead"] = new StaticWeaponDead(this);
		this->SetState("StaticWeaponDefault", "StaticWeaponDefault");
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


#endif // !__STATICWEAPON_H__
