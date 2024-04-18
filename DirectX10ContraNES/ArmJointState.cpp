#include "ArmJoint.h"
#include "ArmJointState.h"
#include "SceneManager.h"
void ArmJointDefault::Enter() {
	this->holdTime = 0;
}
void ArmJointDefault::Exit() {
	this->holdTime = 0;
}
void ArmJointDefault::Update(float dt) {
	if (this->holdTime < 1000) {
		holdTime += dt;
	}
	else
	{
		float bx, by;
		Bound b = this->armJoint->GetBound();
		bx = b->x - 3;
		by = b->y + b->h / 2;
		if (this->armJoint->isInShootRange)
			this->armJoint->CreateBullet(bx, by);
		this->holdTime = 0;
	}
}
void ArmJointDefault::OnKeyDown(int keyCode) {
}
void ArmJointDefault::OnKeyUp(int keyCode) {

}
string ArmJointDefault::GetStateName() {
	return "ArmJointDefault";
}

void ArmJointRuin::Enter() {
}
void ArmJointRuin::Exit() {
}
void ArmJointRuin::Update(float dt) {
}
void ArmJointRuin::OnKeyDown(int keyCode) {
}
void ArmJointRuin::OnKeyUp(int keyCode) {

}
string ArmJointRuin::GetStateName() {
	return "ArmJointRuin";
}

void ArmJointDead::Enter() {
	this->armJoint->isDead = true;
	this->armJoint->isCollidable = 0;
	/*ArmJoint* gunRuined = new ArmJoint(13, "ArmJoint", "Enemy", 1000, true);
	gunRuined->LoadAssets();
	gunRuined->GetBound()->UpdateBoundLocation(this->ArmJoint->GetBound()->x, this->ArmJoint->GetBound()->y);
	auto currentMap = SceneManager::GetInstance()->GetCurrentScene();
	currentMap->AddMovingObject(gunRuined);*/
}
void ArmJointDead::Exit() {
}
void ArmJointDead::Update(float dt) {
}
void ArmJointDead::OnKeyDown(int keyCode) {
}
void ArmJointDead::OnKeyUp(int keyCode) {

}
string ArmJointDead::GetStateName() {
	return "Dead";
}