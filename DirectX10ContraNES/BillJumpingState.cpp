#include "Bill.h"
#include "BillState.h"

void BillJumping0::Enter() {
	this->bill->isOnGround = false;
	this->bill->isJumping = true;
	this->maxYCanReach = this->bill->GetBound()->y + 60;
}
void BillJumping0::Exit() {
	this->bill->isJumping = false;
	this->maxYCanReach = 0;
}
void BillJumping0::OnKeyDown(int keyCode) {
	if (keyCode == DIK_LEFT) {
		this->bill->SetNx(-1);
		this->bill->ax = -1;
	}
	if (keyCode == DIK_RIGHT) {
		this->bill->SetNx(1);
		this->bill->ax = 1;
	}
	if (keyCode == DIK_A) {
		float angle = this->bill->ax == 1 ? 0 : D3DX_PI;
		this->bill->SetAngle(angle);
		Bound b = this->bill->GetBound();
		float bx, by;
		bx = this->bill->ax == 1 ? b->x + b->w + 3 : b->x - 3;
		by = b->y + b->h / 2 ;
		this->bill->CreateBullet(bx,by);
	}
}
void BillJumping0::Update(float dt) {
	if (this->bill->GetBound()->y >= maxYCanReach)
	{
		this->bill->SetNy(-1);
		this->bill->SetState("Falling0", Helper::aXToString(this->bill->ax) + "Falling0");
	}
}
void BillJumping0::OnKeyUp(int keyCode) {
	
}
string BillJumping0::GetStateName() {
	return "Jumping0";
}
