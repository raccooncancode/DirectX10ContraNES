#include "Bill.h"
#include "BillState.h"

void BillDead::Enter() {
	this->bill->isDead = true;
	this->bill->isJumping = true;
	this->bill->isOnGround = false;
	this->bill->SetNy(1);
	this->maxYCanReach = this->bill->GetBound()->y + 35;
	this->bill->respawnTimes -= 1;
}
void BillDead::Exit() {

}

void BillDead::Update(float dt) {
	if (this->bill->GetBound()->y >= maxYCanReach)
	{
		this->bill->SetNy(-1);
		//this->bill->isDeleted = true;
	}
}

void BillDead::OnKeyDown(int keyCode) {
}

void BillDead::OnKeyUp(int keyCode) {

}
string BillDead::GetStateName() {
	return "Dead";
}
