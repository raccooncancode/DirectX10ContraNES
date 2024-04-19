#pragma once
#ifndef __BlazerANIMATION_H__
#define __BlazerANIMATION_H__

class Blazer;

#include "GameAnimation.h"

class BlazerAnimation :public GameAnimation {
private:
	Blazer* blazer;
public:
	BlazerAnimation(Blazer* g) { this->blazer = g; }
	void Update(float dt, GameObject* o = NULL, bool isDead = false);
};

#endif // !__BlazerANIMATION_H__
