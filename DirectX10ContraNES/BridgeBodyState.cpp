#include "BridgeBody.h"
#include "BridgeBodyState.h"
#include "SoundManager.h"
void BridgeBodyDefault::Enter() {
}
void BridgeBodyDefault::Exit() {
}
void BridgeBodyDefault::Update(float dt) {
}
void BridgeBodyDefault::OnKeyDown(int keyCode) {
}
void BridgeBodyDefault::OnKeyUp(int keyCode) {

}
string BridgeBodyDefault::GetStateName() {
	return "BridgeBodyDefault";
}

void BridgeBodyDead::Enter() {
	SoundManager::GetInstance()->Play("destroy_bridge", false, 1);
	this->bridgeBody->isDead = true;
}
void BridgeBodyDead::Exit() {
}
void BridgeBodyDead::Update(float dt) {
}
void BridgeBodyDead::OnKeyDown(int keyCode) {
}
void BridgeBodyDead::OnKeyUp(int keyCode) {

}
string BridgeBodyDead::GetStateName() {
	return "Dead";
}