#pragma once
#ifndef __GUNBOSSBULLET_H__
#define __GUNBOSSBULLET_H__

#include "Bullet.h"

class GunBoss1Bullet :public Bullet {
public:

private:
	float maxRange;
	float maxHigh;
	float minHigh;
	float minRange;
	float range;
	float high;
public:
	GunBoss1Bullet(int id, string name, string type, float x, float y, float speed, float angle) : Bullet(id, name, type, x, y, speed, angle) {
		maxRange = 0.4f * 16;
		maxHigh = 1.5f * 16;
		minHigh = 16.0f;
		minRange = 1.12f;
		range = std::rand() % (int)(maxRange - minRange) + minRange;
		high = std::rand() % (int)maxHigh + minHigh;
		float speedX = (float)range / 20;
		float speedY = (-0.5 * 0.2f * 5 * 5) / 5;
		this->nx = 1;
		this->ny = -1;
		this->vx = speed - speedX;
		this->vy = speed/2;
	}
	void OnNoCollision(float dt)override {
		this->vy += 0.02;
		this->objectBound->x += vx * dt * this->nx;
		this->objectBound->y += vy * dt * this->ny;
	}
	void OnCollisionWith(CollisionEvent* e, float dt) override{
		if (dynamic_cast<Bullet*>(e->dest)) {
			return;
		}
		
	}
};

#endif // !__GUNBOSSBULLET_H__
