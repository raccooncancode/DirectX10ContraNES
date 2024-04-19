#include "DynamicPlatform.h"
#include "DynamicPlatformState.h"
#include "SceneManager.h"
void DynamicPlatformDefault::Enter() {
}
void DynamicPlatformDefault::Exit() {
	this->holdTime = 0;
}
void DynamicPlatformDefault::Update(float dt) {
}
void DynamicPlatformDefault::OnKeyDown(int keyCode) {
}
void DynamicPlatformDefault::OnKeyUp(int keyCode) {

}
string DynamicPlatformDefault::GetStateName() {
	return "DynamicPlatformDefault";
}

void DynamicPlatformRuin::Enter() {
}
void DynamicPlatformRuin::Exit() {
}
void DynamicPlatformRuin::Update(float dt) {
}
void DynamicPlatformRuin::OnKeyDown(int keyCode) {
}
void DynamicPlatformRuin::OnKeyUp(int keyCode) {

}
string DynamicPlatformRuin::GetStateName() {
	return "DynamicPlatformRuin";
}

void DynamicPlatformDead::Enter() {
}
void DynamicPlatformDead::Exit() {
}
void DynamicPlatformDead::Update(float dt) {
}
void DynamicPlatformDead::OnKeyDown(int keyCode) {
}
void DynamicPlatformDead::OnKeyUp(int keyCode) {

}
string DynamicPlatformDead::GetStateName() {
	return "Dead";
}