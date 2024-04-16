#include "Capsule.h"
#include "CapsuleState.h"

void CapsuleDefault::Enter() {
}
void CapsuleDefault::Exit() {
}
void CapsuleDefault::Update(float dt) {
}
void CapsuleDefault::OnKeyDown(int keyCode) {
}
void CapsuleDefault::OnKeyUp(int keyCode) {

}
string CapsuleDefault::GetStateName() {
	return "CapsuleDefault";
}



void CapsuleHiding::Enter() {
}
void CapsuleHiding::Exit() {
	this->capsule->isShowing = true;
}
void CapsuleHiding::Update(float dt) {
}
void CapsuleHiding::OnKeyDown(int keyCode) {
}
void CapsuleHiding::OnKeyUp(int keyCode) {

}
string CapsuleHiding::GetStateName() {
	return "CapsuleHiding";
}


void CapsuleDead::Enter() {
	this->capsule->isDead = true;
}
void CapsuleDead::Exit() {
}
void CapsuleDead::Update(float dt) {
}
void CapsuleDead::OnKeyDown(int keyCode) {
}
void CapsuleDead::OnKeyUp(int keyCode) {

}
string CapsuleDead::GetStateName() {
	return "Dead";
}