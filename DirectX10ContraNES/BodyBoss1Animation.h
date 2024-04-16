#pragma once
#ifndef __BodyBoss1ANIMATION_H__
#define __BodyBoss1ANIMATION_H__

class BodyBoss1;

#include "GameAnimation.h"

class BodyBoss1Animation :public GameAnimation {
private:
	BodyBoss1* bodyBoss1;
public:
	BodyBoss1Animation(BodyBoss1* g) { this->bodyBoss1 = g; }
	void Update(float dt, GameObject* o = NULL, bool isDead = false);
};

#endif // !__BodyBoss1ANIMATION_H__
