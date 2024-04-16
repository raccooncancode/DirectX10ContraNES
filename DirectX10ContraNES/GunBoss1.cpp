#include "Boss1.h"
#include "GunBoss1.h"
#include "AnimationAddOnManager.h"
#include "Bill.h"
void GunBoss1::Update(float dt, vector<GameObject*>* objects) {
	this->objects.clear();
	this->btree->Retrieve(this->btree->root, this->objects, this->objectBound);
	if (this->isRuined)
		this->isCollidable = 0;
	this->collision->Proccess(this, &this->objects, dt);
	this->currentGunBoss1State->Update(dt);
	this->gunBoss1Animation->Update(dt, this, this->isDead);
}

void GunBoss1::Render() {
	gunBoss1Animation->Render(this->objectBound->x + this->objectBound->w / 2, this->objectBound->y + this->objectBound->h / 2);
}

void GunBoss1::SetParent(Boss1* b) {
	this->parent = b;
}

void GunBoss1::SetState(std::string stateName, std::string animationName) {
	if (this->gunBoss1Animation->GetAnimation() != animationName && this->currentGunBoss1State->GetStateName() != stateName)
	{
		this->currentGunBoss1State->Exit();
		this->currentGunBoss1State = stateDict[stateName];
		this->currentGunBoss1State->Enter();
		this->gunBoss1Animation->SetAnimation(animationName);
	}
}

void GunBoss1::LoadAssets() {
	tinyxml2::XMLDocument xmlDoc;
	tinyxml2::XMLError eResult = xmlDoc.LoadFile("Textures\\GunBoss1.xml");
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
		this->gunBoss1Animation->AddAnimation(name, ani);
	}
	this->gunBoss1Animation->AddAnimation("Dead", AnimationAddOnManager::GetInstance()->GetAnimation("Explosion0"));
	ani = new CAnimation(0, 0, false);//temp
	this->gunBoss1Animation->Update(0, this, this->isDead);
	delete ani;
}
void GunBoss1::OnNoCollision(float dt) {

}
void GunBoss1::OnCollisionWith(CollisionEvent* e, float dt) {
	//if (dynamic_cast<Bill*>(e->dest)) {
	//	OnCollisionWithPlayer(e, dt);
	//}
}
void GunBoss1::OnCollisionWithPlayer(CollisionEvent* e, float dt) {
	//SetState("Dead", "Dead");
}