#include "Soldier.h"
#include "SoldierState.h"

void SoldierFalling::Enter() {

}
void SoldierFalling::Exit() {

}
void SoldierFalling::Update(float dt) {
	if (this->soldier->isOnGround) {
		DebugOut(L"\nHERE FALLING");
		this->soldier->SetState("Running", Helper::aXToString(this->soldier->ax) + "Running");
	}
}
void SoldierFalling::OnKeyDown(int keyCode) {
}
void SoldierFalling::OnKeyUp(int keyCode) {

}
string SoldierFalling::GetStateName() {
	return "Falling";
}
