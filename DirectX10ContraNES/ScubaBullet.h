#pragma once
#ifndef __GUNBOSSBULLET_H__
#define __GUNBOSSBULLET_H__

#include "Bullet.h"

class ScubaBullet :public Bullet {
public:

private:
	int bulletDirect;
public:
	ScubaBullet(int id, string name, string type, float x, float y, float speed, float angle, int bulletDirect = 0) : Bullet(id, name, type, x, y, speed, angle) {
		this->bulletDirect = bulletDirect;
		if (bulletDirect == 0)
			this->nx = 0;
		else if (bulletDirect == 1)
			this->nx = 1;
		else
			this->nx = -1;
		this->ny = 0.8;
		this->vx = speed;
		this->vy = speed;
	}
	void OnNoCollision(float dt)override {
		if (this->bulletDirect == 1 && this->nx > 0) {
			this->nx -= 0.01;
			if (this->nx <= 0)
				this->nx = 0;
		}
		if (this->bulletDirect == -1 && this->nx < 0) {
			this->nx += 0.01;
			if (this->nx >= 0)
				this->nx = 0;
		}
		this->ny -= 0.02;
		this->objectBound->x += vx * dt * this->nx;
		this->objectBound->y += vy * dt * this->ny;
	}
	void OnCollisionWith(CollisionEvent* e, float dt) override {
		if (dynamic_cast<Bullet*>(e->dest)) {
			return;
		}

	}
};

#endif // !__GUNBOSSBULLET_H__
