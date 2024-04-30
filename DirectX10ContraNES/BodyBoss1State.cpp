#include "BodyBoss1.h"
#include "BodyBoss1State.h"
#include "SceneManager.h"
#include "SoundManager.h"
void BodyBoss1Default::Enter() {
}
void BodyBoss1Default::Exit() {
}
void BodyBoss1Default::Update(float dt) {
}
void BodyBoss1Default::OnKeyDown(int keyCode) {
}
void BodyBoss1Default::OnKeyUp(int keyCode) {

}
string BodyBoss1Default::GetStateName() {
	return "BodyBoss1Default";
}

void BodyBoss1Ruin::Enter() {
}
void BodyBoss1Ruin::Exit() {
}
void BodyBoss1Ruin::Update(float dt) {
}
void BodyBoss1Ruin::OnKeyDown(int keyCode) {
}
void BodyBoss1Ruin::OnKeyUp(int keyCode) {

}
string BodyBoss1Ruin::GetStateName() {
	return "BodyBoss1Ruin";
}

void BodyBoss1Dead::Enter() {
	this->bodyBoss1->isDead = true;
	SoundManager::GetInstance()->Stop();
	SoundManager::GetInstance()->Play("destroy_bridge", false, 1);
	SoundManager::GetInstance()->Play("finish_stage", false, 1);
	this->bodyBoss1->isCollidable = 0;
	BodyBoss1* bodyRuined = new BodyBoss1(13, "BodyBoss1", "Enemy", 1000, true);
	bodyRuined->LoadAssets();
	bodyRuined->GetBound()->UpdateBoundLocation(this->bodyBoss1->GetBound()->x, this->bodyBoss1->GetBound()->y);
	auto currentMap = SceneManager::GetInstance()->GetCurrentScene();
	currentMap->AddMovingObject(bodyRuined);
}
void BodyBoss1Dead::Exit() {
}
void BodyBoss1Dead::Update(float dt) {
}
void BodyBoss1Dead::OnKeyDown(int keyCode) {
}
void BodyBoss1Dead::OnKeyUp(int keyCode) {

}
string BodyBoss1Dead::GetStateName() {
	return "Dead";
}