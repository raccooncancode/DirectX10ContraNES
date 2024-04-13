#include "Soldier.h"
#include "SoldierState.h"

void SoldierDead::Enter() {
	this->soldier->isOnGround = false;
	this->soldier->isJumping = true;
	this->soldier->SetNy(1);
	this->soldier->SetNx(0);
	this->maxYCanReach = this->soldier->GetBound()->y + 20;
}
void SoldierDead::Exit() {

}
void SoldierDead::Update(float dt) {
	if (this->soldier->GetBound()->y >= this->maxYCanReach)
	{
		this->soldier->isDeleted = true;
	}
}
void SoldierDead::OnKeyDown(int keyCode) {
}
void SoldierDead::OnKeyUp(int keyCode) {

}
string SoldierDead::GetStateName() {
	return "Dead";
}
