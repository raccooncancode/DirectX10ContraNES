#include "DynamicPlatform.h"
#include "DynamicPlatformAnimation.h"

void DynamicPlatformAnimation::Update(float dt, GameObject* o, bool isDead) {
	float w, h;
	this->pAnimations[pCurrentAnimation]->Update(dt, o, isDead);
	this->pAnimations[pCurrentAnimation]->GetFrameResolution(w, h);
	this->dynamicPlatform->GetBound()->UpdateBoundSize(w, h);
}