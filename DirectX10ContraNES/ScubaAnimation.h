#pragma once
#ifndef __ScubaANIMATION_H__
#define __ScubaANIMATION_H__

class Scuba;
#include "GameAnimation.h"

class ScubaAnimation :public GameAnimation {
private:
	Scuba* scuba;
public:
	ScubaAnimation(Scuba* c) { this->scuba = c; }
	void Update(float dt, GameObject* o = NULL, bool isDead = false);
};

#endif // !__ScubaANIMATION_H__
