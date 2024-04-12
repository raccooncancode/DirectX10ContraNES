#pragma once
#ifndef __SOLDIERANIMATION_H__
#define __SOLDIERANIMATION_H__

class Soldier;
#include "GameAnimation.h"


class SoldierAnimation : public GameAnimation {
private:
	Soldier* soldier;
public:
	SoldierAnimation(Soldier* s) { this->soldier = s; }
	void Update(float dt, GameObject* o = NULL, bool isDead = false);
};

#endif // !__SOLDIERANIMATION_H__
