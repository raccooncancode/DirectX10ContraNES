#pragma once
#ifndef __StaticWeaponANIMATION_H__
#define __StaticWeaponANIMATION_H__

class StaticWeapon;

#include "GameAnimation.h"

class StaticWeaponAnimation :public GameAnimation {
private:
	StaticWeapon* staticWeapon;
public:
	StaticWeaponAnimation(StaticWeapon* sW) { this->staticWeapon = sW; }
	void Update(float dt, GameObject* o = NULL, bool isDead = false);
};

#endif // !__StaticWeaponANIMATION_H__
