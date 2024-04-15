#include "BridgeHead.h"
#include "BridgeHeadAnimation.h"

void BridgeHeadAnimation::Update(float dt, GameObject* o, bool isDead) {
	float w, h;
	this->pAnimations[pCurrentAnimation]->Update(dt, o, isDead);
	this->pAnimations[pCurrentAnimation]->GetFrameResolution(w, h);
	this->bridgeHead->GetBound()->UpdateBoundSize(w, h);
}