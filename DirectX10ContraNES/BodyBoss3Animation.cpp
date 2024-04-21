#include "BodyBoss3.h"
#include "BodyBoss3Animation.h"

void BodyBoss3Animation::Update(float dt, GameObject* o, bool isDead) {
	float w, h;
	this->pAnimations[pCurrentAnimation]->Update(dt, o, isDead);
	this->pAnimations[pCurrentAnimation]->GetFrameResolution(w, h);
	this->bodyBoss3->GetBound()->UpdateBoundSize(w, h);
}