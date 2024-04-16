#include "Capsule.h"
#include "CapsuleAnimation.h"

void CapsuleAnimation::Update(float dt, GameObject* o, bool isDead) {
	float w, h;
	this->pAnimations[pCurrentAnimation]->Update(dt, o, isDead);
	this->pAnimations[pCurrentAnimation]->GetFrameResolution(w, h);
	this->capsule->GetBound()->UpdateBoundSize(w, h);
}