#pragma once
#ifndef __HeadBoss3ANIMATION_H__
#define __HeadBoss3ANIMATION_H__

class HeadBoss3;

#include "GameAnimation.h"

class HeadBoss3Animation :public GameAnimation {
private:
	HeadBoss3* headBoss3;
public:
	HeadBoss3Animation(HeadBoss3* g) { this->headBoss3 = g; }
	void Update(float dt, GameObject* o = NULL, bool isDead = false);
};

#endif // !__HeadBoss3ANIMATION_H__
