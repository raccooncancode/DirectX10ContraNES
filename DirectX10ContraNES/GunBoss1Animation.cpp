#include "GunBoss1.h"
#include "GunBoss1Animation.h"

void GunBoss1Animation::Update(float dt, GameObject* o, bool isDead) {
	float w, h;
	this->pAnimations[pCurrentAnimation]->Update(dt, o, isDead);
	this->pAnimations[pCurrentAnimation]->GetFrameResolution(w, h);
	this->gunBoss1->GetBound()->UpdateBoundSize(w, h);
}