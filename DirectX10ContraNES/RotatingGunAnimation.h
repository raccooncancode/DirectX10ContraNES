#pragma once
#ifndef __ROTATINGGUNANIMATION_H__
#define __ROTATINGGUNANIMATION_H__

class RotatingGun;
#include "GameAnimation.h"

class RotatingGunAnimation :public GameAnimation {
private:
	RotatingGun* rotatingGun;
public:
	RotatingGunAnimation(RotatingGun* r) { this->rotatingGun = r; }
	void Update(float dt, GameObject* o = NULL, bool isDead = false);
};

#endif // !__RotingGunAnimation_H__
