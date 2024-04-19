#pragma once
#ifndef __DynamicPlatformANIMATION_H__
#define __DynamicPlatformANIMATION_H__

class DynamicPlatform;

#include "GameAnimation.h"

class DynamicPlatformAnimation :public GameAnimation {
private:
	DynamicPlatform* dynamicPlatform;
public:
	DynamicPlatformAnimation(DynamicPlatform* g) { this->dynamicPlatform = g; }
	void Update(float dt, GameObject* o = NULL, bool isDead = false);
};

#endif // !__DynamicPlatformANIMATION_H__
