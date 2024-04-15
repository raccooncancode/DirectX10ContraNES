#include "Bridge.h"
#include "BridgeHead.h"
#include "AnimationAddOnManager.h"
#include "Bill.h"
void BridgeHead::Update(float dt, vector<GameObject*>* objects) {
	this->objects.clear();
	this->btree->Retrieve(this->btree->root, this->objects, this->objectBound);
	this->collision->Proccess(this, &this->objects, dt);
	if (this->bill == NULL) {

		for (GameObject* gO : this->objects) {
			if (gO->GetType() == "Player") {
				this->bill = gO;
			}
		}
	}
	if (!this->isDead && this->bill != NULL) {
		if (this->bill->GetBound()->x > this->objectBound->x) {
			SetState("Dead", "Dead");
		}
	}
	this->currentBridgeHeadState->Update(dt);
	this->bridgeHeadAnimation->Update(dt, this, this->isDead);
}

void BridgeHead::Render() {
	bridgeHeadAnimation->Render(this->objectBound->x + this->objectBound->w / 2, this->objectBound->y + this->objectBound->h / 2);
}

void BridgeHead::SetState(std::string stateName, std::string animationName) {
	if (this->bridgeHeadAnimation->GetAnimation() != animationName && this->currentBridgeHeadState->GetStateName() != stateName)
	{
		this->currentBridgeHeadState->Exit();
		this->currentBridgeHeadState = stateDict[stateName];
		this->currentBridgeHeadState->Enter();
		this->bridgeHeadAnimation->SetAnimation(animationName);
	}
}

void BridgeHead::LoadAssets() {
	tinyxml2::XMLDocument xmlDoc;
	tinyxml2::XMLError eResult = xmlDoc.LoadFile("Textures\\BridgeHead.xml");
	if (eResult != tinyxml2::XML_SUCCESS) {
		return;
	}
	tinyxml2::XMLElement* root = xmlDoc.FirstChildElement("Animations");
	if (root == nullptr) {
		return;
	}
	tinyxml2::XMLElement* animation = nullptr;
	tinyxml2::XMLElement* frame = nullptr;
	LPANIMATION ani;
	std::string name;
	int totalFrame = 0;
	bool isLoop;
	int duration = 0;
	float x, y, w, h;
	LPTEXTURE tex = TextureManager::GetInstance()->Get(this->id);

	for (animation = root->FirstChildElement(); animation != NULL; animation = animation->NextSiblingElement()) {
		animation->QueryIntAttribute("duration", &duration);
		animation->QueryIntAttribute("totalFrame", &totalFrame);
		animation->QueryBoolAttribute("isLoop", &isLoop);

		name = animation->Attribute("name");
		ani = new CAnimation(totalFrame, duration, isLoop);
		for (frame = animation->FirstChildElement(); frame != NULL; frame = frame->NextSiblingElement()) {
			frame->QueryFloatAttribute("x", &x);
			frame->QueryFloatAttribute("y", &y);
			frame->QueryFloatAttribute("w", &w);
			frame->QueryFloatAttribute("h", &h);
			ani->AddFrame(new CSprite(x, y, w, h, tex));
		}
		this->bridgeHeadAnimation->AddAnimation(name, ani);
	}
	this->bridgeHeadAnimation->AddAnimation("Dead", AnimationAddOnManager::GetInstance()->GetAnimation("Explosion1"));
	ani = new CAnimation(0, 0, false);//temp
	this->bridgeHeadAnimation->Update(0, this, this->isDead);
	delete ani;
}
void BridgeHead::OnNoCollision(float dt) {

}
void BridgeHead::OnCollisionWith(CollisionEvent* e, float dt) {
	//if (dynamic_cast<Bill*>(e->dest)) {
	//	OnCollisionWithPlayer(e,dt);
	//}
}
void BridgeHead::OnCollisionWithPlayer(CollisionEvent* e, float dt) {
	//SetState("Dead", "Dead");
}