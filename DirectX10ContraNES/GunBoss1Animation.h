#pragma once
#ifndef __GunBoss1ANIMATION_H__
#define __GunBoss1ANIMATION_H__

class GunBoss1;

#include "GameAnimation.h"

class GunBoss1Animation :public GameAnimation {
private:
	GunBoss1* gunBoss1;
public:
	GunBoss1Animation(GunBoss1* g) { this->gunBoss1 = g; }
	void Update(float dt, GameObject* o = NULL, bool isDead = false);
};

#endif // !__GunBoss1ANIMATION_H__
