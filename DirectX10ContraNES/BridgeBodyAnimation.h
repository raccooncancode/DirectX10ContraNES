#pragma once
#ifndef __BRIDGEBODYANIMATION_H__
#define __BRIDGEBODYANIMATION_H__

class BridgeBody;

#include "GameAnimation.h"

class BridgeBodyAnimation :public GameAnimation {
private:
	BridgeBody* bridgeBody;
public:
	BridgeBodyAnimation(BridgeBody* bH) { this->bridgeBody = bH; }
	void Update(float dt, GameObject* o = NULL, bool isDead = false);
};

#endif // !__BRIDGEBODYANIMATION_H__
