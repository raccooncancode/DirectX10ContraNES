#include "Stone.h"
#include "StoneState.h"
#include "SceneManager.h"
void StoneDefault::Enter() {
}
void StoneDefault::Exit() {
	this->holdTime = 0;
}
void StoneDefault::Update(float dt) {
}
void StoneDefault::OnKeyDown(int keyCode) {
}
void StoneDefault::OnKeyUp(int keyCode) {

}
string StoneDefault::GetStateName() {
	return "StoneDefault";
}

void StoneRuin::Enter() {
}
void StoneRuin::Exit() {
}
void StoneRuin::Update(float dt) {
}
void StoneRuin::OnKeyDown(int keyCode) {
}
void StoneRuin::OnKeyUp(int keyCode) {

}
string StoneRuin::GetStateName() {
	return "StoneRuin";
}

void StoneDead::Enter() {
	this->stone->isDead = true;
	this->stone->isCollidable = 0;
	this->stone->SetSpeed(0, 0);
}
void StoneDead::Exit() {
}
void StoneDead::Update(float dt) {
}
void StoneDead::OnKeyDown(int keyCode) {
}
void StoneDead::OnKeyUp(int keyCode) {

}
string StoneDead::GetStateName() {
	return "Dead";
}