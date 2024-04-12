#pragma once
#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "GameObject.h"

class Enemy :public GameObject {
protected:
	int hp;
public:
	Enemy(int id, string name, string type, int hp = 1) : GameObject(id, name, type) {
		this->hp = hp;
	}
	void DecreaseHP(float hp) {
		this->hp -= hp;
		if (this->hp <= 0) {
			this->hp = 0;
			this->isDead = true;
		}
	}
	virtual void Update(float dt, vector<GameObject*>* objects=NULL){}
	virtual void Render(){}
	virtual void OnNoCollision(float dt){}
	virtual void OnCollisionWith(CollisionEvent*e){}
};

#endif // !__ENEMY_H__
