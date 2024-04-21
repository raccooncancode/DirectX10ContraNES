#include "HeadBoss3.h"
#include "HeadBoss3Animation.h"

void HeadBoss3Animation::Update(float dt, GameObject* o, bool isDead) {
	float w, h;
	this->pAnimations[pCurrentAnimation]->Update(dt, o, isDead);
	this->pAnimations[pCurrentAnimation]->GetFrameResolution(w, h);
	this->headBoss3->GetBound()->UpdateBoundSize(w, h);
}