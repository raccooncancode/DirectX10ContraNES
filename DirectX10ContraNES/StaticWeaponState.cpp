#include "StaticWeapon.h"
#include "StaticWeaponState.h"
#include "Item.h"
#include "SceneManager.h"
#include "SoundManager.h"
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
	auto currentMap = SceneManager::GetInstance()->GetCurrentScene();
	int itemId;
	std::string itemName;
	if (this->staticWeapon->GetName() == "StaticWeaponM") {
		itemId = 10;
		itemName = "ItemM";
	}
	else if (this->staticWeapon->GetName() == "StaticWeaponS") {
		itemId = 11;
		itemName = "ItemS";
	}
	else {
		itemId = 12;
		itemName = "ItemR";
	}
	auto item = new Item(itemId, itemName, "Item");
	SoundManager::GetInstance()->Play("destroy_bridge", false, 1);
	item->LoadAssets();
	item->GetBound()->UpdateBoundLocation(this->staticWeapon->GetBound()->x, this->staticWeapon->GetBound()->y);
	item->InitItem();
	currentMap->AddMovingObject(item);
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