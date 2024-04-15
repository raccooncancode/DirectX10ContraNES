#pragma once
#ifndef __CANNONANIMATION_H__
#define __CANNONANIMATION_H__

class Cannon;
#include "GameAnimation.h"

class CannonAnimation :public GameAnimation {
private:
	Cannon* cannon;
public:
	CannonAnimation(Cannon* c) { this->cannon = c; }
	void Update(float dt, GameObject* o = NULL, bool isDead = false);
};

#endif // !__CANNONANIMATION_H__
