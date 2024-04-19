#include "Scuba.h"
#include "ScubaAnimation.h"

void ScubaAnimation::Update(float dt, GameObject* o, bool isDead) {
	float w, h;
	this->pAnimations[pCurrentAnimation]->Update(dt, o, isDead);
	this->pAnimations[pCurrentAnimation]->GetFrameResolution(w, h);
	this->scuba->GetBound()->UpdateBoundSize(w, h);
}