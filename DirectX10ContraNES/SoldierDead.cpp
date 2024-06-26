#include "Soldier.h"
#include "SoldierState.h"
#include "SoundManager.h"
#include "SceneManager.h"
void SoldierDead::Enter() {
	this->soldier->isOnGround = false;
	this->soldier->isJumping = true;
	this->soldier->SetSpeed(0, 0);
	this->soldier->SetNx(0);
	this->soldier->isDead = true;
	this->maxYCanReach = this->soldier->GetBound()->y + 20;
	SceneManager::GetInstance()->scores += this->soldier->GetScore();
}
void SoldierDead::Exit() {
	this->maxYCanReach = 0;
}
void SoldierDead::Update(float dt) {
	
}
void SoldierDead::OnKeyDown(int keyCode) {
}
void SoldierDead::OnKeyUp(int keyCode) {

}
string SoldierDead::GetStateName() {
	return "Dead";
}
