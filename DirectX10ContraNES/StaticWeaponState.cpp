#include "StaticWeapon.h"
#include "StaticWeaponState.h"

void StaticWeaponDefault::Enter() {
}
void StaticWeaponDefault::Exit() {
}
void StaticWeaponDefault::Update(float dt) {
}
void StaticWeaponDefault::OnKeyDown(int keyCode) {
}
void StaticWeaponDefault::OnKeyUp(int keyCode) {

}
string StaticWeaponDefault::GetStateName() {
	return "StaticWeaponDefault";
}

void StaticWeaponDead::Enter() {
	this->staticWeapon->isDead = true;
}
void StaticWeaponDead::Exit() {
}
void StaticWeaponDead::Update(float dt) {
}
void StaticWeaponDead::OnKeyDown(int keyCode) {
}
void StaticWeaponDead::OnKeyUp(int keyCode) {

}
string StaticWeaponDead::GetStateName() {
	return "Dead";
}