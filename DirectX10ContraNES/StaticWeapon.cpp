#include "StaticWeapon.h"
#include "AnimationAddOnManager.h"
#include "Bill.h"
void StaticWeapon::Update(float dt, vector<GameObject*>* objects) {
	this->objects.clear();
	this->btree->Retrieve(this->btree->root, this->objects, this->objectBound);
	this->collision->Proccess(this, &this->objects, dt);
	if (this->bill == NULL) {
		for (GameObject* gO : this->objects) {
			if (gO->GetType() == "Player") {
				this->bill = gO;
				//SetState("CapsuleDefault", "CapsuleDefault");
			}
		}
	}
	if (this->bill != NULL) {
		if (this->bill->GetBound()->x <= this->objectBound->x)
			this->nx = -1;
		else
			this->nx = 1;
		if (this->bill->GetBound()->y <= this->objectBound->y)
			this->ny = -1;
		else
			this->ny = 1;
	}
	this->currentStaticWeaponState->Update(dt);
	this->staticWeaponAnimation->Update(dt, this, this->isDead);
}

void StaticWeapon::Render() {
	staticWeaponAnimation->Render(this->objectBound->x + this->objectBound->w / 2, this->objectBound->y + this->objectBound->h / 2);
}

void StaticWeapon::SetState(std::string stateName, std::string animationName) {
	if (this->staticWeaponAnimation->GetAnimation() != animationName && this->currentStaticWeaponState->GetStateName() != stateName)
	{
		this->currentStaticWeaponState->Exit();
		this->currentStaticWeaponState = stateDict[stateName];
		this->currentStaticWeaponState->Enter();
		this->staticWeaponAnimation->SetAnimation(animationName);
	}
}

void StaticWeapon::LoadAssets() {
	tinyxml2::XMLDocument xmlDoc;
	tinyxml2::XMLError eResult = xmlDoc.LoadFile("Textures\\StaticWeapon.xml");
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
		this->staticWeaponAnimation->AddAnimation(name, ani);
	}
	this->staticWeaponAnimation->AddAnimation("Dead", AnimationAddOnManager::GetInstance()->GetAnimation("Explosion0"));
	ani = new CAnimation(0, 0, false);//temp
	this->staticWeaponAnimation->Update(0, this, this->isDead);
	delete ani;
}
void StaticWeapon::OnNoCollision(float dt) {

}
void StaticWeapon::OnCollisionWith(CollisionEvent* e, float dt) {
	if (e->dest->GetType() == "PlayerBullet") {
		OnCollisionWithPlayerBullet(e, dt);
	}
}
void StaticWeapon::OnCollisionWithPlayer(CollisionEvent* e, float dt) {
}
void StaticWeapon::OnCollisionWithPlayerBullet(CollisionEvent* e, float dt) {
	e->dest->isDeleted = true;
	SetState("Dead", "Dead");
	//Drop Item Here
}