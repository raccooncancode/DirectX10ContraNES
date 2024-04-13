#include "Bill.h"
#include "BillState.h"

void BillDead::Enter() {
	this->bill->isDead = true;
	this->bill->isJumping = true;
	this->bill->isOnGround = false;
	this->bill->SetNy(1);
	
}
void BillDead::Exit() {

}

void BillDead::Update(float dt) {

}

void BillDead::OnKeyDown(int keyCode) {
}

void BillDead::OnKeyUp(int keyCode) {

}
string BillDead::GetStateName() {
	return "Dead";
}
