#include "GunBoss1.h"
#include "GunBoss1State.h"
#include "SceneManager.h"
void GunBoss1Default::Enter() {
	this->holdTime = 0;
}
void GunBoss1Default::Exit() {
	this->holdTime = 0;
}
void GunBoss1Default::Update(float dt) {
	if (this->holdTime < 1000) {
		holdTime += dt;
	}
	else
	{
		float bx, by;
		Bound b = this->gunBoss1->GetBound();
		bx = b->x - 3;
		by = b->y + b->h / 2;
		if (this->gunBoss1->isInShootRange)
			this->gunBoss1->CreateBullet(bx, by);
		this->holdTime = 0;
	}
}
void GunBoss1Default::OnKeyDown(int keyCode) {
}
void GunBoss1Default::OnKeyUp(int keyCode) {

}
string GunBoss1Default::GetStateName() {
	return "GunBoss1Default";
}

void GunBoss1Ruin::Enter() {
}
void GunBoss1Ruin::Exit() {
}
void GunBoss1Ruin::Update(float dt) {
}
void GunBoss1Ruin::OnKeyDown(int keyCode) {
}
void GunBoss1Ruin::OnKeyUp(int keyCode) {

}
string GunBoss1Ruin::GetStateName() {
	return "GunBoss1Ruin";
}

void GunBoss1Dead::Enter() {
	this->gunBoss1->isDead = true;
	this->gunBoss1->isCollidable = 0;
	GunBoss1* gunRuined = new GunBoss1(13, "GunBoss1", "Enemy", 1000, true);
	gunRuined->LoadAssets();
	gunRuined->GetBound()->UpdateBoundLocation(this->gunBoss1->GetBound()->x, this->gunBoss1->GetBound()->y);
	auto currentMap = SceneManager::GetInstance()->GetCurrentScene();
	currentMap->AddMovingObject(gunRuined);
}
void GunBoss1Dead::Exit() {
}
void GunBoss1Dead::Update(float dt) {
}
void GunBoss1Dead::OnKeyDown(int keyCode) {
}
void GunBoss1Dead::OnKeyUp(int keyCode) {

}
string GunBoss1Dead::GetStateName() {
	return "Dead";
}