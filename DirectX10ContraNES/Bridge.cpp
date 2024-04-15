#include "Bridge.h"
#include "SceneManager.h"

void Bridge::Init(float x, float y) {
	this->bH = new BridgeHead(5, "BridgeHead", "Bridge");
	bH->LoadAssets();
	bH->GetBound()->UpdateBoundLocation(x + 32 * 0, y);
	bH->GetBound()->UpdateBoundSize(32, 32);

	DebugOut(L"\nLoaded BridgeHead");

	bB1 = new BridgeBody(6, "BridgeBody", "Bridge");
	bB1->LoadAssets();
	bB1->GetBound()->UpdateBoundLocation(x + 32 * 1, y);
	bB1->GetBound()->UpdateBoundSize(32, 32);
	DebugOut(L"\nLoaded BridgeBody 1");
	
	bB2 = new BridgeBody(6, "BridgeBody", "Bridge");
	bB2->LoadAssets();
	bB2->GetBound()->UpdateBoundLocation(x + 32 * 2, y);
	bB2->GetBound()->UpdateBoundSize(32, 32);
	DebugOut(L"\nLoaded BridgeBody 2");
	
	bB3 = new BridgeBody(6, "BridgeBody", "Bridge");
	bB3->LoadAssets();
	bB3->GetBound()->UpdateBoundLocation(x + 32 * 3, y);
	bB3->GetBound()->UpdateBoundSize(32, 32);


	this->childs.push_back(bH);
	this->childs.push_back(bB1);
	this->childs.push_back(bB2);
	this->childs.push_back(bB3);
	bB1->SetParent(this);
	bB2->SetParent(this);
	bB3->SetParent(this);
	this->currentChild = bH;
	DebugOut(L"\nLoaded BridgeBody 3");
	//auto currentMap = SceneManager::GetInstance()->GetCurrentScene();
	//currentMap->AddMovingObject(bH);
	//currentMap->AddMovingObject(bB1);
	//currentMap->AddMovingObject(bB2);
	//currentMap->AddMovingObject(bB3);
}
void Bridge::Update(float dt, vector<GameObject*>* objects) {
	if (this->currentChildIndex < childs.size()) {
		if (this->childs[currentChildIndex]->isDeleted) {
			DebugOut(L"\nBridge Child Deleted");
			this->currentChildIndex++;
			if (this->currentChildIndex == childs.size()) {
				return;
			}
			this->currentChild = this->childs[this->currentChildIndex];
		}
	}
}
void Bridge::Render() {

}
void Bridge::LoadAssets() {

}