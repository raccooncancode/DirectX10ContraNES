#include "Stone.h"
#include "AnimationAddOnManager.h"
#include "Bill.h"
#include "GunBossBullet.h"
#include "SceneManager.h"
void Stone::Update(float dt, vector<GameObject*>* objects) {
	this->objects.clear();
	this->btree->Retrieve(this->btree->root, this->objects, this->objectBound);
	this->collision->Proccess(this, &this->objects, dt);
	if (this->target == NULL)
	{
		for (GameObject* gO : this->objects) {
			if (gO->GetType() == "Player") {
				SetTarget(gO);
				this->SetSpeed(0, 1.5);
			}
		}
	}
	this->currentStoneState->Update(dt);
	this->stoneAnimation->Update(dt, this, this->isDead);
}

void Stone::Render() {
	stoneAnimation->Render(this->objectBound->x + this->objectBound->w / 2, this->objectBound->y + this->objectBound->h / 2);
}


void Stone::SetState(std::string stateName, std::string animationName) {
	if (this->stoneAnimation->GetAnimation() != animationName && this->currentStoneState->GetStateName() != stateName)
	{
		this->currentStoneState->Exit();
		this->currentStoneState = stateDict[stateName];
		this->currentStoneState->Enter();
		this->stoneAnimation->SetAnimation(animationName);
	}
}

void Stone::LoadAssets() {
	tinyxml2::XMLDocument xmlDoc;
	tinyxml2::XMLError eResult = xmlDoc.LoadFile("Textures\\Stone.xml");
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
		this->stoneAnimation->AddAnimation(name, ani);
	}
	this->stoneAnimation->AddAnimation("Dead", AnimationAddOnManager::GetInstance()->GetAnimation("Explosion0"));
	ani = new CAnimation(0, 0, false);//temp
	this->stoneAnimation->Update(0, this, this->isDead);
	delete ani;
}
void Stone::CreateBullet(float x, float y) {
	float bX, bY;
	float speed = 0.01;
	bX = x;
	bY = y;
	auto currentMap = SceneManager::GetInstance()->GetCurrentScene();
}
void Stone::OnNoCollision(float dt) {
	this->objectBound->y += this->vy * this->ny;
}
void Stone::OnCollisionWith(CollisionEvent* e, float dt) {
	//if (dynamic_cast<Bill*>(e->dest)) {
	//	OnCollisionWithPlayer(e, dt);
	//}
}
void Stone::OnCollisionWithPlayer(CollisionEvent* e, float dt) {
	//SetState("Dead", "Dead");
}