#include "Bill.h"
#include "BillAnimation.h"

void BillAnimation::Update(float dt,GameObject* o, bool isDead) {
		float w, h;
		this->pAnimations[pCurrentAnimation]->Update(dt, o, isDead);
		this->pAnimations[pCurrentAnimation]->GetFrameResolution(w, h);
		this->bill->GetBound()->UpdateBoundSize(w, h);
}