#include "Stone.h"
#include "StoneAnimation.h"

void StoneAnimation::Update(float dt, GameObject* o, bool isDead) {
	float w, h;
	this->pAnimations[pCurrentAnimation]->Update(dt, o, isDead);
	this->pAnimations[pCurrentAnimation]->GetFrameResolution(w, h);
	this->stone->GetBound()->UpdateBoundSize(w, h);
}