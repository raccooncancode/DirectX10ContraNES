#include "Capsule.h"
#include "AnimationAddOnManager.h"
#include "Bill.h"
#include "Item.h"
#include "SceneManager.h"
void Capsule::Update(float dt, vector<GameObject*>* objects) {
	this->objects.clear();
	this->btree->Retrieve(this->btree->root, this->objects, this->objectBound);
	this->collision->Proccess(this, &this->objects, dt);
	
	this->currentCapsuleState->Update(dt);
	this->capsuleAnimation->Update(dt, this, this->isDead);
}

void Capsule::Render() {if (this->bill == NULL) {
		for (GameObject* gO : this->objects) {
			if (gO->GetType()=="Player") {
				this->bill = gO;
				//SetState("CapsuleDefault", "CapsuleDefault");
			}
		}
	}
	if (this->bill != NULL) {
		if (this->bill->GetBound()->x >= this->objectBound->x + 30) {
			SetState("CapsuleDefault", "CapsuleDefault");
			this->isShowing = true;
		}
	}
	capsuleAnimation->Render(this->objectBound->x + this->objectBound->w / 2, this->objectBound->y + this->objectBound->h / 2);
}

void Capsule::SetState(std::string stateName, std::string animationName) {
	if (this->capsuleAnimation->GetAnimation() != animationName && this->currentCapsuleState->GetStateName() != stateName)
	{
		this->currentCapsuleState->Exit();
		this->currentCapsuleState = stateDict[stateName];
		this->currentCapsuleState->Enter();
		this->capsuleAnimation->SetAnimation(animationName);
	}
}

void Capsule::LoadAssets() {
	tinyxml2::XMLDocument xmlDoc;
	tinyxml2::XMLError eResult = xmlDoc.LoadFile("Textures\\Capsule.xml");
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
		this->capsuleAnimation->AddAnimation(name, ani);
	}
	this->capsuleAnimation->AddAnimation("Dead", AnimationAddOnManager::GetInstance()->GetAnimation("Explosion0"));
	ani = new CAnimation(0, 0, false);//temp
	this->capsuleAnimation->Update(0, this, this->isDead);
	delete ani;
}
void Capsule::OnNoCollision(float dt) {
	if (this->isShowing) {

		crow += D3DX_PI / 60;
		if (crow == 2 * D3DX_PI)
		{
			crow = 0;
		}
		Map* currentMap = (Map*)SceneManager::GetInstance()->GetCurrentScene();
		if (currentMap->GetStage() == 1) {
			this->SetSpeed(1, 3.5);
			this->nx = 1;
			this->ny = sin(crow)*1.1f;
		}
		else {
			this->SetSpeed(3.5, 1);
			this->nx = cos(crow) * 1.1f;
			this->ny = 1;
		}
		this->objectBound->x += this->vx * nx;
		this->objectBound->y += this->vy * ny;
	}
}
void Capsule::OnCollisionWith(CollisionEvent* e, float dt) {
	if (this->isShowing) {

		if (e->dest->GetType() == "PlayerBullet") {
			OnCollisionWithPlayerBullet(e, dt);
		}
	}
}
void Capsule::OnCollisionWithPlayer(CollisionEvent* e, float dt) {
}
void Capsule::OnCollisionWithPlayerBullet(CollisionEvent* e, float dt) {
	this->SetSpeed(0, 0);
	e->dest->isDeleted = true;
	SetState("Dead", "Dead");
	//Drop Item Here
}