#pragma once
#ifndef __SOLDIER_H__
#define __SOLDIER_H__

#include "Enemy.h"
#include "Bullet.h"
#include "SoldierAnimation.h"
class Soldier : public Enemy{
public:
	int ax;
	bool isOnGround;
	bool isJumping;
	bool isSwimming;
	vector<Bullet*> bullets;
private:
	SoldierAnimation* soldierAnimation;
public:
};

#endif // !__SOLDIER_H__
