#pragma once
#ifndef __BRIDGEHEADANIMATION_H__
#define __BRIDGEHEADANIMATION_H__

class BridgeHead;

#include "GameAnimation.h"

class BridgeHeadAnimation :public GameAnimation {
private:
	BridgeHead* bridgeHead;
public:
	BridgeHeadAnimation(BridgeHead* bH) { this->bridgeHead = bH; }
	void Update(float dt, GameObject* o = NULL, bool isDead = false);
};

#endif // !__BRIDGEHEADANIMATION_H__
