#include "BridgeBody.h"
#include "BridgeBodyAnimation.h"

void BridgeBodyAnimation::Update(float dt, GameObject* o, bool isDead) {
	float w, h;
	this->pAnimations[pCurrentAnimation]->Update(dt, o, isDead);
	this->pAnimations[pCurrentAnimation]->GetFrameResolution(w, h);
	this->bridgeBody->GetBound()->UpdateBoundSize(w, h);
}