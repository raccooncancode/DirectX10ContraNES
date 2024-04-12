#include "Bill.h"
#include "BillState.h"

void BillLaying0::Enter() {
}
void BillLaying0::Exit() {
	this->bill->isLaying = false;
}
void BillLaying0::OnKeyDown(int keyCode) {
	if (keyCode == DIK_Z && this->bill->isOnGround) {
		this->bill->GetBound()->y -= 5;
	}
	if (keyCode == DIK_A) {
		float angle = this->bill->ax == 1 ? 0 : D3DX_PI;
		this->bill->SetAngle(angle);
		Bound b = this->bill->GetBound();
		float bx, by;
		bx = this->bill->ax == 1 ? b->x + b->w + 3 : b->x - 3;
		by = b->y + b->h / 2 - 5;
		this->bill->CreateBullet(bx,by);
	}
}
void BillLaying0::OnKeyUp(int keyCode) {
	if (keyCode == DIK_DOWN) {
		this->bill->SetState("Standing0", Helper::aXToString(this->bill->ax) + "Standing0");
	}
}
string BillLaying0::GetStateName() {
	return "Laying0";
}