#pragma once
#ifndef __BOSS1_H__
#define __BOSS1_H__

#include "GameObject.h"
#include "GunBoss1.h"
#include "BodyBoss1.h"
#include <vector>

class Boss1 {
private:
	std::vector<GunBoss1*> guns;
public:
	void AddGun(GunBoss1* gun);
	bool IsAllGunsRuined();
};

#endif // !__BOSS1_H__
