#include "Blazer.h"
#include "BlazerState.h"
#include "SceneManager.h"
void BlazerDefault::Enter() {
}
void BlazerDefault::Exit() {
	this->holdTime = 0;
}
void BlazerDefault::Update(float dt) {
}
void BlazerDefault::OnKeyDown(int keyCode) {
}
void BlazerDefault::OnKeyUp(int keyCode) {

}
string BlazerDefault::GetStateName() {
	return "BlazerDefault";
}

void BlazerRuin::Enter() {
}
void BlazerRuin::Exit() {
}
void BlazerRuin::Update(float dt) {
}
void BlazerRuin::OnKeyDown(int keyCode) {
}
void BlazerRuin::OnKeyUp(int keyCode) {

}
string BlazerRuin::GetStateName() {
	return "BlazerRuin";
}

void BlazerDead::Enter() {
	this->blazer->isDead = true;
	this->blazer->isCollidable = 0;
}
void BlazerDead::Exit() {
}
void BlazerDead::Update(float dt) {
}
void BlazerDead::OnKeyDown(int keyCode) {
}
void BlazerDead::OnKeyUp(int keyCode) {

}
string BlazerDead::GetStateName() {
	return "Dead";
}