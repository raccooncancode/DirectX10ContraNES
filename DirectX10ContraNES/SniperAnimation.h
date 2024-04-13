#pragma once
#ifndef __SNIPERANIMATION_H__
#define __SNIPERANIMATION_H__

class Sniper;
#include "GameAnimation.h"

class SniperAnimation:public GameAnimation {
private:
	Sniper* sniper;
public:
	SniperAnimation(Sniper* s) { this->sniper = s; }
	void Update(float dt, GameObject* o = NULL, bool isDead = false);
};

#endif // !__SNIPERANIMATION_H__
