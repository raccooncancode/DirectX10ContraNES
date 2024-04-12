#include "Bill.h"
#include "BillState.h"

void BillSwimming::Enter() {
	this->bill->isSwimming = true;
}
void BillSwimming::Exit() {
	this->bill->isSwimming = false;
}
void BillSwimming::OnKeyDown(int keyCode) {
	if (keyCode == DIK_LEFT) {
		this->bill->SetNx(-1);
		this->bill->ax = -1;
		this->bill->SetState("Swimming0", Helper::aXToString(this->bill->ax) + "Swimming0");
		
	}
	if (keyCode == DIK_RIGHT) {
		this->bill->SetNx(1);
		this->bill->ax = 1;
		this->bill->SetState("Swimming0", Helper::aXToString(this->bill->ax) + "Swimming0");
	}
	if (keyCode == DIK_S) {
		if (this->bill->isOnGround || this->bill->isSwimming) {
			this->bill->SetNy(1);
			this->bill->SetState("Jumping0", Helper::aXToString(this->bill->ax) + "Jumping0");
		}
	}
	if (keyCode == DIK_UP) {
		this->bill->SetNx(0);
		this->bill->SetState("Swimming90", Helper::aXToString(this->bill->ax) + "Swimming90");
	}
}
void BillSwimming::OnKeyUp(int keyCode) {
}
string BillSwimming::GetStateName() {
	return "Swimming";
}




void BillSwimming0::Enter() {
	this->bill->isSwimming = true;
}
void BillSwimming0::Exit() {
	this->bill->isSwimming = false;

}
void BillSwimming0::OnKeyDown(int keyCode) {
	if (keyCode == DIK_UP) {
		this->bill->SetState("Swimming45", Helper::aXToString(this->bill->ax) + "Swimming45");
	}
	if (keyCode == DIK_LEFT) {
		this->bill->SetNx(-1);
		this->bill->ax = -1;
		this->bill->SetState("Swimming0", Helper::aXToString(this->bill->ax) + "Swimming0");
	}
	if (keyCode == DIK_RIGHT) {
		this->bill->SetNx(1);
		this->bill->ax = 1;
		this->bill->SetState("Swimming0", Helper::aXToString(this->bill->ax) + "Swimming0");
	}
	if (keyCode == DIK_S) {
		if (this->bill->isOnGround || this->bill->isSwimming) {
			this->bill->SetNy(1);
			this->bill->SetState("Jumping0", Helper::aXToString(this->bill->ax) + "Jumping0");
		}
	}
	if (keyCode == DIK_A) {
		float angle = this->bill->ax == 1 ? 0 : D3DX_PI;
		this->bill->SetAngle(angle);
		Bound b = this->bill->GetBound();
		float bx, by;
		bx = this->bill->ax == 1 ? b->x + b->w + 3 : b->x - 3;
		by = b->y + b->h / 2 -3;
		this->bill->CreateBullet(bx,by);
	}
}

void BillSwimming0::OnKeyUp(int keyCode) {
	if (keyCode == DIK_LEFT && this->bill->ax == -1) {
		this->bill->SetNx(0);
		this->bill->ax = -1;
		this->bill->SetState("Swimming", Helper::aXToString(this->bill->ax) + "Swimming");
	}
	if (keyCode == DIK_RIGHT && this->bill->ax == 1) {
		this->bill->SetNx(0);
		this->bill->ax = 1;
		this->bill->SetState("Swimming", Helper::aXToString(this->bill->ax) + "Swimming");
	}
}
string BillSwimming0::GetStateName() {
	return "Swimming0";
}


void BillSwimming90::Enter() {
	this->bill->isSwimming = true;
}
void BillSwimming90::Exit() {
	this->bill->isSwimming = false;
}
void BillSwimming90::OnKeyDown(int keyCode) {
	this->bill->SetAngle(D3DX_PI/2);
	Bound b = this->bill->GetBound();
	float bx, by;
	bx = this->bill->ax == 1 ? b->x + b->w / 2 + 3 : b->x + b->w/2 - 3;
	by = b->y + b->h + 3;
	this->bill->CreateBullet(bx,by);
}

void BillSwimming90::OnKeyUp(int keyCode) {
	if (keyCode == DIK_UP) {
		this->bill->SetState("Swimming", Helper::aXToString(this->bill->ax) + "Swimming");
	}
}
string BillSwimming90::GetStateName() {
	return "Swimming90";
}


void BillSwimming45::Enter() {
	this->bill->isSwimming = true;
}
void BillSwimming45::Exit() {
	this->bill->isSwimming = false;
}
void BillSwimming45::OnKeyDown(int keyCode) {
	if (keyCode == DIK_A) {
		float angle = this->bill->ax == 1 ? D3DX_PI/4 : D3DX_PI - D3DX_PI/4;
		this->bill->SetAngle(angle);
		Bound b = this->bill->GetBound();
		float bx, by;
		bx = this->bill->ax == 1 ? b->x + b->w + 3 : b->x - 3;
		by = b->y + b->h / 2 + 5;
		this->bill->CreateBullet(bx,by);
	}
}

void BillSwimming45::OnKeyUp(int keyCode) {
	if (keyCode == DIK_UP) {
		this->bill->SetState("Swimming0", Helper::aXToString(this->bill->ax) + "Swimming0");
	}
}
string BillSwimming45::GetStateName() {
	return "Swimming45";
}