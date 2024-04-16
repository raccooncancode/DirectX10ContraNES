#include "Item.h"
#include "ItemState.h"

void ItemDefault::Enter() {
}
void ItemDefault::Exit() {
}
void ItemDefault::Update(float dt) {
}
void ItemDefault::OnKeyDown(int keyCode) {
}
void ItemDefault::OnKeyUp(int keyCode) {

}
string ItemDefault::GetStateName() {
	return "ItemDefault";
}



void ItemHiding::Enter() {
}
void ItemHiding::Exit() {
	this->item->isShowing = true;
}
void ItemHiding::Update(float dt) {
}
void ItemHiding::OnKeyDown(int keyCode) {
}
void ItemHiding::OnKeyUp(int keyCode) {

}
string ItemHiding::GetStateName() {
	return "ItemHiding";
}


void ItemDead::Enter() {
	this->item->isDead = true;
}
void ItemDead::Exit() {
}
void ItemDead::Update(float dt) {
}
void ItemDead::OnKeyDown(int keyCode) {
}
void ItemDead::OnKeyUp(int keyCode) {

}
string ItemDead::GetStateName() {
	return "Dead";
}