#include "Soldier.h"
#include "SoldierState.h"

void SoldierRunning::Enter() {
}
void SoldierRunning::Exit() {

}
void SoldierRunning::Update(float dt) {

}
void SoldierRunning::OnKeyDown(int keyCode) {
}
void SoldierRunning::OnKeyUp(int keyCode) {

}
string SoldierRunning::GetStateName() {
	return "Running";
}
