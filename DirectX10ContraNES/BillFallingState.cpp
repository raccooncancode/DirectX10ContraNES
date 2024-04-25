#include "Bill.h"
#include "BillState.h"
#include "SceneManager.h"
void BillFalling0::Enter() {
	
}
void BillFalling0::Exit() {

}
void BillFalling0::OnKeyDown(int keyCode) {
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
void BillFalling0::Update(float dt) {
	if (this->bill->isOnGround && this->bill->GetNx()==0) {
		this->bill->SetState("Standing0", Helper::aXToString(this->bill->ax) + "Standing0");
	}
	else if (this->bill->isOnGround && this->bill->GetNx() != 0) {
		this->bill->SetState("Running0", Helper::aXToString(this->bill->ax) + "Running0");
	}
}

void BillFalling0::OnKeyUp(int keyCode) {

}
string BillFalling0::GetStateName() {
	return "Falling0";
}
