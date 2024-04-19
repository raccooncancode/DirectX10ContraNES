#pragma once
#ifndef __StoneANIMATION_H__
#define __StoneANIMATION_H__

class Stone;

#include "GameAnimation.h"

class StoneAnimation :public GameAnimation {
private:
	Stone* stone;
public:
	StoneAnimation(Stone* g) { this->stone = g; }
	void Update(float dt, GameObject* o = NULL, bool isDead = false);
};

#endif // !__StoneANIMATION_H__
