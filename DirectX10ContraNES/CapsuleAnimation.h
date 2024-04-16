#pragma once
#ifndef __CapsuleANIMATION_H__
#define __CapsuleANIMATION_H__

class Capsule;

#include "GameAnimation.h"

class CapsuleAnimation :public GameAnimation {
private:
	Capsule* capsule;
public:
	CapsuleAnimation(Capsule* c) { this->capsule = c; }
	void Update(float dt, GameObject* o = NULL, bool isDead = false);
};

#endif // !__CapsuleANIMATION_H__
