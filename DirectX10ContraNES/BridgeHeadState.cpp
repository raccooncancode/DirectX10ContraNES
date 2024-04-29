#include "BridgeHead.h"
#include "BridgeHeadState.h"
#include "SoundManager.h"
void BridgeHeadDefault::Enter() {
}
void BridgeHeadDefault::Exit() {
}
void BridgeHeadDefault::Update(float dt) {
}
void BridgeHeadDefault::OnKeyDown(int keyCode) {
}
void BridgeHeadDefault::OnKeyUp(int keyCode) {

}
string BridgeHeadDefault::GetStateName() {
	return "BridgeHeadDefault";
}

void BridgeHeadDead::Enter() {
	SoundManager::GetInstance()->Play("destroy_bridge", false, 1);
	this->bridgeHead->isDead = true;
}
void BridgeHeadDead::Exit() {
}
void BridgeHeadDead::Update(float dt) {
}
void BridgeHeadDead::OnKeyDown(int keyCode) {
}
void BridgeHeadDead::OnKeyUp(int keyCode) {

}
string BridgeHeadDead::GetStateName() {
	return "Dead";
}