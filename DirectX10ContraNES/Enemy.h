#pragma once
#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "GameObject.h"
#include"Helper.h"
class Enemy :public GameObject {
protected:
	int hp;
	bool toDead;
	GameObject* target;
public:
	Enemy(int id, string name, string type, int hp = 1) : GameObject(id, name, type) {
		this->hp = hp;
		toDead = false;
		this->target = NULL;
	}
	void DecreaseHP(float hp) {
		this->hp -= hp;
		DebugOut(L"\nDecrease HP");
		if (this->hp <= 0) {
			this->hp = 0;
			SetState("Dead", Helper::aXToString(GetAx()) + "Dead");
		}
	}
	virtual void SetTarget(GameObject* o) { this->target = o; }
	virtual GameObject* GetTarget() { return this->target; }
	virtual void SetState(std::string stateName, std::string animationName) {
	}
	virtual int GetAx() { return -1; }
	virtual void Update(float dt, vector<GameObject*>* objects=NULL){}
	virtual void Render(){}
	virtual void OnNoCollision(float dt){}
	virtual void OnCollisionWith(CollisionEvent*e){}
};

#endif // !__ENEMY_H__
