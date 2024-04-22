#include "Capsule.h"
#include "CapsuleState.h"
#include "SceneManager.h"
#include "Item.h"
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
	auto currentMap = SceneManager::GetInstance()->GetCurrentScene();
	int itemId;
	std::string itemName;
	if (this->capsule->GetName() == "CapsuleWeaponM") {
		itemId = 10;
		itemName = "ItemM";
	}
	else if (this->capsule->GetName() == "CapsuleWeaponS") {
		itemId = 11;
		itemName = "ItemS";
	}
	else {
		itemId = 12;
		itemName = "ItemR";
	}
	this->capsule->SetSpeed(0, 0);
	auto item = new Item(itemId, itemName, "Item");
	item->LoadAssets();
	item->GetBound()->UpdateBoundLocation(this->capsule->GetBound()->x, this->capsule->GetBound()->y);
	item->InitItem();
	currentMap->AddMovingObject(item);
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