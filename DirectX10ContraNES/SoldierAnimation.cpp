#include "Soldier.h"
#include "SoldierAnimation.h"

void SoldierAnimation::Update(float dt, GameObject* o, bool isDead) {
	float w, h;
	this->pAnimations[pCurrentAnimation]->Update(dt, o, isDead);
	this->pAnimations[pCurrentAnimation]->GetFrameResolution(w, h);
	this->soldier->GetBound()->UpdateBoundSize(w, h);
}