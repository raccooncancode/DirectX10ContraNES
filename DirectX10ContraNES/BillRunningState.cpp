#include "Bill.h"
#include "BillState.h"

void BillRunning0::Enter() {

}
void BillRunning0::Exit() {

}
void BillRunning0::OnKeyDown(int keyCode) {
	if (keyCode == DIK_S) {
		if (this->bill->isOnGround) {
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
		by = b->y + b->h / 2;
		this->bill->CreateBullet(bx,by);
		this->bill->SetState("RunningShooting0", Helper::aXToString(this->bill->ax) + "RunningShooting0");
	}
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
	if (keyCode == DIK_UP) {
		this->bill->SetState("Running45", Helper::aXToString(this->bill->ax) + "Running45");
	}
	if (keyCode == DIK_DOWN) {
		this->bill->SetState("Running315", Helper::aXToString(this->bill->ax) + "Running315");
	}
}
void BillRunning0::OnKeyUp(int keyCode) {
	if (keyCode == DIK_LEFT && this->bill->ax == -1) {
		this->bill->SetNx(0);
		this->bill->SetState("Standing0", Helper::aXToString(this->bill->ax) + "Standing0");
	}
	if (keyCode == DIK_RIGHT && this->bill->ax == 1) {
		this->bill->SetNx(0);
		this->bill->SetState("Standing0", Helper::aXToString(this->bill->ax) + "Standing0");
	}
}
string BillRunning0::GetStateName() {
	return "Running0";
}

void BillRunningShooting0::Enter() {
	this->holdingTime = 0;
}
void BillRunningShooting0::Exit() {
	this->holdingTime = 0;
}
void BillRunningShooting0::OnKeyDown(int keyCode) {
	if (keyCode == DIK_A) {
		this->holdingTime = 0;
		float angle = this->bill->ax == 1 ? 0 : D3DX_PI;
		this->bill->SetAngle(angle);
		Bound b = this->bill->GetBound();
		float bx, by;
		bx = this->bill->ax == 1 ? b->x + b->w + 3 : b->x - 3;
		by = b->y + b->h / 2;
		this->bill->CreateBullet(bx,by);
	}
}
void BillRunningShooting0::Update(float dt) {
	if (this->holdingTime <= 500) {
		this->holdingTime += dt;
	}
	else{
		this->holdingTime -= 500;
		this->bill->SetState("Running0", Helper::aXToString(this->bill->ax) + "Running0");
	}
}
void BillRunningShooting0::OnKeyUp(int keyCode) {
	if (keyCode == DIK_RIGHT && this->bill->ax == 1) {
		this->bill->SetState("Running0", Helper::aXToString(this->bill->ax) + "Running0");
	}
	if (keyCode == DIK_LEFT && this->bill->ax == -1) {
		this->bill->SetState("Running0", Helper::aXToString(this->bill->ax) + "Running0");
	}
}
string BillRunningShooting0::GetStateName() {
	return "RunningShooting0";
}

void BillRunning45::Enter() {

}
void BillRunning45::Exit() {

}
void BillRunning45::OnKeyDown(int keyCode) {
	if (keyCode == DIK_A) {
		float angle = this->bill->ax == 1 ? D3DX_PI / 4 : D3DX_PI - D3DX_PI / 4;
		this->bill->SetAngle(angle);
		Bound b = this->bill->GetBound();
		float bx, by;
		bx = this->bill->ax == 1 ? b->x + b->w + 3 : b->x - 3;
		by = b->y + b->h / 2 + 13;
		this->bill->CreateBullet(bx,by);
	}
}
void BillRunning45::OnKeyUp(int keyCode) {
	if (keyCode == DIK_UP) {
		this->bill->SetState("Running0", Helper::aXToString(this->bill->ax) + "Running0");
	}
	if (keyCode == DIK_LEFT && this->bill->ax ==-1) {
		this->bill->SetNx(0);
		this->bill->SetState("Standing0", Helper::aXToString(this->bill->ax) + "Standing0");
	}
	if (keyCode == DIK_RIGHT && this->bill->ax == 1 ) {
		this->bill->SetNx(0);
		this->bill->SetState("Standing0", Helper::aXToString(this->bill->ax) + "Standing0");
	}

}
string BillRunning45::GetStateName() {
	return "Running45";
}


void BillRunning315::Enter() {

}
void BillRunning315::Exit() {

}
void BillRunning315::OnKeyDown(int keyCode) {
	if (keyCode == DIK_A) {
		float angle = this->bill->ax == 1 ? -D3DX_PI / 4 : -D3DX_PI + D3DX_PI / 4;
		this->bill->SetAngle(angle);
		Bound b = this->bill->GetBound();
		float bx, by;
		bx = this->bill->ax == 1 ? b->x + b->w + 3 : b->x - 3;
		by = b->y + b->h / 2 - 5;
		this->bill->CreateBullet(bx,by);
	}
}
void BillRunning315::OnKeyUp(int keyCode) {
	if (keyCode == DIK_DOWN) {
		this->bill->SetState("Running0", Helper::aXToString(this->bill->ax) + "Running0");
	}
	if (keyCode == DIK_LEFT && this->bill->ax == -1) {
		this->bill->SetNx(0);
		this->bill->SetState("Standing0", Helper::aXToString(this->bill->ax) + "Standing0");
	}
	if (keyCode == DIK_RIGHT && this->bill->ax == 1) {
		this->bill->SetNx(0);
		this->bill->SetState("Standing0", Helper::aXToString(this->bill->ax) + "Standing0");
	}
}
string BillRunning315::GetStateName() {
	return "Running315";
}