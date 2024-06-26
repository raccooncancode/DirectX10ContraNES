#include "BodyBoss3.h"
#include "AnimationAddOnManager.h"
#include "Bill.h"
#include "GunBossBullet.h"
#include "SceneManager.h"
#include "Camera.h"
void BodyBoss3::Update(float dt, vector<GameObject*>* objects) {
	this->objects.clear();
	this->btree->Retrieve(this->btree->root, this->objects, this->objectBound);
	this->collision->Proccess(this, &this->objects, dt);
	if (this->target == NULL)
	{
		for (GameObject* gO : this->objects) {
			if (gO->GetType() == "Player") {
				SetTarget(gO);
			}
		}
	}
	if (this->parent != NULL && this->target!=NULL && Camera::GetInstance()->IsReachedBossArea() == true) {
		this->parent->isSeeTarget = true;
		this->parent->isMoveTo = true;
	}
	if (this->parent->isDead) {
		this->SetState("Dead", "Dead");
	}
	this->currentBodyBoss3State->Update(dt);
	this->bodyBoss3Animation->Update(dt, this, this->isDead);
}

void BodyBoss3::Render() {
	bodyBoss3Animation->Render(this->objectBound->x + this->objectBound->w / 2, this->objectBound->y + this->objectBound->h / 2);
	//RenderBoundingBox();
}

void BodyBoss3::SetParent(Boss3* p) {
	this->parent = p;
}

void BodyBoss3::SetState(std::string stateName, std::string animationName) {
	if (this->bodyBoss3Animation->GetAnimation() != animationName && this->currentBodyBoss3State->GetStateName() != stateName)
	{
		this->currentBodyBoss3State->Exit();
		this->currentBodyBoss3State = stateDict[stateName];
		this->currentBodyBoss3State->Enter();
		this->bodyBoss3Animation->SetAnimation(animationName);
	}
}

void BodyBoss3::LoadAssets() {
	tinyxml2::XMLDocument xmlDoc;
	tinyxml2::XMLError eResult = xmlDoc.LoadFile("Textures\\BodyBoss3.xml");
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
		this->bodyBoss3Animation->AddAnimation(name, ani);
	}
	this->bodyBoss3Animation->AddAnimation("Dead", AnimationAddOnManager::GetInstance()->GetAnimation("Explosion1"));
	ani = new CAnimation(0, 0, false);//temp
	this->bodyBoss3Animation->Update(0, this, this->isDead);
	delete ani;
}
void BodyBoss3::CreateBullet(float x, float y) {
	float bX, bY;
	float speed = 0.01;
	bX = x;
	bY = y;
	auto currentMap = SceneManager::GetInstance()->GetCurrentScene();
}
void BodyBoss3::OnNoCollision(float dt) {
	this->objectBound->y += this->vy * this->ny;
}
void BodyBoss3::OnCollisionWith(CollisionEvent* e, float dt) {
	//if (dynamic_cast<Bill*>(e->dest)) {
	//	OnCollisionWithPlayer(e, dt);
	//}
}
void BodyBoss3::OnCollisionWithPlayer(CollisionEvent* e, float dt) {
	//SetState("Dead", "Dead");
}