#include "BodyBoss3.h"
#include "BodyBoss3State.h"
#include "SceneManager.h"
#include "SoundManager.h"
void BodyBoss3Default::Enter() {
}
void BodyBoss3Default::Exit() {
	this->holdTime = 0;
}
void BodyBoss3Default::Update(float dt) {
}
void BodyBoss3Default::OnKeyDown(int keyCode) {
}
void BodyBoss3Default::OnKeyUp(int keyCode) {

}
string BodyBoss3Default::GetStateName() {
	return "BodyBoss3Default";
}

void BodyBoss3Ruin::Enter() {
}
void BodyBoss3Ruin::Exit() {
}
void BodyBoss3Ruin::Update(float dt) {
}
void BodyBoss3Ruin::OnKeyDown(int keyCode) {
}
void BodyBoss3Ruin::OnKeyUp(int keyCode) {

}
string BodyBoss3Ruin::GetStateName() {
	return "BodyBoss3Ruin";
}

void BodyBoss3Dead::Enter() {
	SoundManager::GetInstance()->Play("destroy_bridge", false, 1);
	this->bodyBoss3->isDead = true;
	this->bodyBoss3->isCollidable = 0;
	this->bodyBoss3->SetSpeed(0, 0);
}
void BodyBoss3Dead::Exit() {
}
void BodyBoss3Dead::Update(float dt) {
}
void BodyBoss3Dead::OnKeyDown(int keyCode) {
}
void BodyBoss3Dead::OnKeyUp(int keyCode) {

}
string BodyBoss3Dead::GetStateName() {
	return "Dead";
}