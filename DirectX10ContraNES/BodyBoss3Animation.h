#pragma once
#ifndef __BodyBoss3ANIMATION_H__
#define __BodyBoss3ANIMATION_H__

class BodyBoss3;

#include "GameAnimation.h"

class BodyBoss3Animation :public GameAnimation {
private:
	BodyBoss3* bodyBoss3;
public:
	BodyBoss3Animation(BodyBoss3* g) { this->bodyBoss3 = g; }
	void Update(float dt, GameObject* o = NULL, bool isDead = false);
};

#endif // !__BodyBoss3ANIMATION_H__
