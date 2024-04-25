#include "Sniper.h"
#include "SniperState.h"

void SniperDead::Enter() {
	DebugOut(L"\nHere Sniper Dead");
	this->sniper->isOnGround = false;
	this->sniper->isJumping = true;
	this->sniper->SetSpeed(0, 0);
	this->sniper->isDead = true;
	this->maxYCanReach = this->sniper->GetBound()->y + 20;
}
void SniperDead::Exit() {
	this->maxYCanReach = 0;
}
void SniperDead::Update(float dt) {

}
void SniperDead::OnKeyDown(int keyCode) {
}
void SniperDead::OnKeyUp(int keyCode) {

}
string SniperDead::GetStateName() {
	return "Dead";
}
