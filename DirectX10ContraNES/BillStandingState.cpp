#include "Bill.h"
#include "BillState.h"

void BillStanding0::Enter() {
	this->bill->SetNx(0);
}
void BillStanding0::Exit() {

}
void BillStanding0::OnKeyDown(int keyCode) {
	if (keyCode == DIK_LEFT) {
		this->bill->SetNx(-1);
		this->bill->ax = -1;
		this->bill->SetState("Running0", Helper::aXToString(this->bill->ax) + "Running0");
	}
	if (keyCode == DIK_RIGHT) {
		this->bill->SetNx(1);
		this->bill->ax = 1;
		this->bill->SetState("Running0", Helper::aXToString(this->bill->ax) + "Running0");
	}
	if (keyCode == DIK_DOWN) {
		if (this->bill->isOnGround) {
			this->bill->SetNx(0);
			this->bill->isLaying = true;
			this->bill->SetState("Laying0", Helper::aXToString(this->bill->ax) + "Laying0");
		}
	}
	if (keyCode == DIK_UP) {
		if (this->bill->isOnGround) {
			this->bill->SetNx(0);
			this->bill->SetState("Standing90", Helper::aXToString(this->bill->ax) + "Standing90");
		}
	}
	if (keyCode == DIK_S) {
		if (this->bill->isOnGround) {
			this->bill->SetNx(0);
			this->bill->SetNy(1);
			this->bill->SetState("Jumping0", Helper::aXToString(this->bill->ax) + "Jumping0");
		}
	}
	if (keyCode == DIK_A) {
		float angle = this->bill->ax == 1 ? 0 : D3DX_PI;
		this->bill->SetAngle(angle);
		Bound b = this->bill->GetBound();
		float bx, by;
		bx = this->bill->ax == 1 ? b->x + b->w  + 3 : b->x - 3;
		by = b->y + b->h / 2;
		this->bill->CreateBullet(bx,by);
	}
}
void BillStanding0::OnKeyUp(int keyCode) {

	}
string BillStanding0::GetStateName() {
	return "Standing0";
	}


void BillStanding90::Enter() {
}
void BillStanding90::Exit() {
}
void BillStanding90::OnKeyDown(int keyCode) {
	if (keyCode == DIK_A) {
		this->bill->SetAngle(D3DX_PI/2);
		Bound b = this->bill->GetBound();
		float bx, by;
		bx = this->bill->ax == 1 ? b->x + b->w / 2 + 3 : b->x + b->w / 2 - 3;
		by = b->y + b->h + 3;
		this->bill->CreateBullet(bx, by);
	}
}
void BillStanding90::OnKeyUp(int keyCode) {
	if (keyCode == DIK_UP) {
		this->bill->SetState("Standing0", Helper::aXToString(this->bill->ax) + "Standing0");
	}
}
string BillStanding90::GetStateName() {
	return "Standing90";
}