#include "Bridge.h"
#include "BridgeBody.h"
#include "AnimationAddOnManager.h"
#include "Bill.h"
void BridgeBody::Update(float dt, vector<GameObject*>* objects) {
	this->objects.clear();
	this->btree->Retrieve(this->btree->root, this->objects, this->objectBound);
	this->collision->Proccess(this, &this->objects, dt);
	if (this->parent != NULL) {
		auto child = this->parent->currentChild;
		if (child == this) {
			this->SetState("Dead", "Dead");
		}
	}
	this->currentBridgeBodyState->Update(dt);
	this->bridgeBodyAnimation->Update(dt, this, this->isDead);
}

void BridgeBody::Render() {
	bridgeBodyAnimation->Render(this->objectBound->x + this->objectBound->w / 2, this->objectBound->y + this->objectBound->h / 2);
}

void BridgeBody::SetParent(Bridge* b) {
	this->parent = b;
}

void BridgeBody::SetState(std::string stateName, std::string animationName) {
	if (this->bridgeBodyAnimation->GetAnimation() != animationName && this->currentBridgeBodyState->GetStateName() != stateName)
	{
		this->currentBridgeBodyState->Exit();
		this->currentBridgeBodyState = stateDict[stateName];
		this->currentBridgeBodyState->Enter();
		this->bridgeBodyAnimation->SetAnimation(animationName);
	}
}

void BridgeBody::LoadAssets() {
	tinyxml2::XMLDocument xmlDoc;
	tinyxml2::XMLError eResult = xmlDoc.LoadFile("Textures\\BridgeBody.xml");
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
		this->bridgeBodyAnimation->AddAnimation(name, ani);
	}
	this->bridgeBodyAnimation->AddAnimation("Dead", AnimationAddOnManager::GetInstance()->GetAnimation("Explosion1"));
	ani = new CAnimation(0, 0, false);//temp
	this->bridgeBodyAnimation->Update(0, this, this->isDead);
	delete ani;
}
void BridgeBody::OnNoCollision(float dt) {

}
void BridgeBody::OnCollisionWith(CollisionEvent* e, float dt) {
	//if (dynamic_cast<Bill*>(e->dest)) {
	//	OnCollisionWithPlayer(e, dt);
	//}
}
void BridgeBody::OnCollisionWithPlayer(CollisionEvent* e, float dt) {
	//SetState("Dead", "Dead");
}