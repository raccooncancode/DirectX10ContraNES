#include "Blazer.h"
#include "BlazerAnimation.h"

void BlazerAnimation::Update(float dt, GameObject* o, bool isDead) {
	float w, h;
	this->pAnimations[pCurrentAnimation]->Update(dt, o, isDead);
	this->pAnimations[pCurrentAnimation]->GetFrameResolution(w, h);
	this->blazer->GetBound()->UpdateBoundSize(w, h);
}