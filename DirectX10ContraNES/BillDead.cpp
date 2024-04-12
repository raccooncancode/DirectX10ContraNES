#include "Bill.h"
#include "BillState.h"

void BillDead::Enter() {
}
void BillDead::Exit() {

}
void BillDead::OnKeyDown(int keyCode) {
}

void BillDead::OnKeyUp(int keyCode) {

}
string BillDead::GetStateName() {
	return "Dead";
}
