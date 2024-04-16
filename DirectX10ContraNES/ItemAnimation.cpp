#include "Item.h"
#include "ItemAnimation.h"

void ItemAnimation::Update(float dt, GameObject* o, bool isDead) {
	float w, h;
	this->pAnimations[pCurrentAnimation]->Update(dt, o, isDead);
	this->pAnimations[pCurrentAnimation]->GetFrameResolution(w, h);
	this->item->GetBound()->UpdateBoundSize(w, h);
}