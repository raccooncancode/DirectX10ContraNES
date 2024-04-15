#include "RotatingGun.h"
#include "RotatingGunAnimation.h"

void RotatingGunAnimation::Update(float dt, GameObject* o, bool isDead) {
	float w, h;
	this->pAnimations[pCurrentAnimation]->Update(dt, o, isDead);
	this->pAnimations[pCurrentAnimation]->GetFrameResolution(w, h);
	this->rotatingGun->GetBound()->UpdateBoundSize(w, h);
}