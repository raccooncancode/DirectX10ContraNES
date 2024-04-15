#include "StaticWeapon.h"
#include "StaticWeaponAnimation.h"

void StaticWeaponAnimation::Update(float dt, GameObject* o, bool isDead) {
	float w, h;
	this->pAnimations[pCurrentAnimation]->Update(dt, o, isDead);
	this->pAnimations[pCurrentAnimation]->GetFrameResolution(w, h);
	this->staticWeapon->GetBound()->UpdateBoundSize(w, h);
}