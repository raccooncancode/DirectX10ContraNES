#include "BodyBoss1.h"
#include "BodyBoss1Animation.h"

void BodyBoss1Animation::Update(float dt, GameObject* o, bool isDead) {
	float w, h;
	this->pAnimations[pCurrentAnimation]->Update(dt, o, isDead);
	this->pAnimations[pCurrentAnimation]->GetFrameResolution(w, h);
	this->bodyBoss1->GetBound()->UpdateBoundSize(w, h);
}