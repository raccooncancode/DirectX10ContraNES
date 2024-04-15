#include "Sniper.h"
#include "SniperState.h"

void SniperDead::Enter() {
	DebugOut(L"\nHere Sniper Dead");
	this->sniper->isOnGround = false;
	this->sniper->isJumping = true;
	this->sniper->SetNy(1);
	this->sniper->SetSpeed(0.1, 0.1);
;	this->sniper->SetNx(-1);
	this->maxYCanReach = this->sniper->GetBound()->y + 20;
}
void SniperDead::Exit() {
	this->maxYCanReach = 0;
}
void SniperDead::Update(float dt) {
	if (this->sniper->GetBound()->y >= this->maxYCanReach)
	{
		this->sniper->isDeleted = true;
	}
}
void SniperDead::OnKeyDown(int keyCode) {
}
void SniperDead::OnKeyUp(int keyCode) {

}
string SniperDead::GetStateName() {
	return "Dead";
}
