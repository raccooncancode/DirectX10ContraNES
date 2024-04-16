#include "Boss1.h"
#include "BodyBoss1.h"
#include "AnimationAddOnManager.h"
#include "Bill.h"
void BodyBoss1::Update(float dt, vector<GameObject*>* objects) {
	this->objects.clear();
	this->btree->Retrieve(this->btree->root, this->objects, this->objectBound);
	if (this->parent != NULL) {
		if (this->parent->IsAllGunsRuined()) {
			
			this->isCollidable = 1;
		}
		else {
			this->isCollidable = 0;
		}
	}
	if (this->target == NULL)
	{
		for (GameObject* gO : this->objects) {
			if (gO->GetType() == "Player") {
				SetTarget(gO);
			}
		}
	}
	/*if (this->target != NULL) {
		if (this->target->GetBound()->x <= this->objectBound->x)
			this->nx = -1;
		else
			this->nx = 1;
		if (this->target->GetBound()->y <= this->objectBound->y)
			this->ny = -1;
		else
			this->ny = 1;
	}*/
	this->collision->Proccess(this, &this->objects, dt);
	this->currentBodyBoss1State->Update(dt);
	this->bodyBoss1Animation->Update(dt, this, this->isDead);
}

void BodyBoss1::Render() {
	bodyBoss1Animation->Render(this->objectBound->x + this->objectBound->w / 2, this->objectBound->y + this->objectBound->h / 2);
	//RenderBoundingBox();
}

void BodyBoss1::SetParent(Boss1* b) {
	this->parent = b;
}

void BodyBoss1::SetState(std::string stateName, std::string animationName) {
	if (this->bodyBoss1Animation->GetAnimation() != animationName && this->currentBodyBoss1State->GetStateName() != stateName)
	{
		this->currentBodyBoss1State->Exit();
		this->currentBodyBoss1State = stateDict[stateName];
		this->currentBodyBoss1State->Enter();
		this->bodyBoss1Animation->SetAnimation(animationName);
	}
}

void BodyBoss1::LoadAssets() {
	tinyxml2::XMLDocument xmlDoc;
	tinyxml2::XMLError eResult = xmlDoc.LoadFile("Textures\\BodyBoss1.xml");
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
		this->bodyBoss1Animation->AddAnimation(name, ani);
	}
	this->bodyBoss1Animation->AddAnimation("Dead", AnimationAddOnManager::GetInstance()->GetAnimation("Explosion1"));
	ani = new CAnimation(0, 0, false);//temp
	this->bodyBoss1Animation->Update(0, this, this->isDead);
	delete ani;
}
void BodyBoss1::OnNoCollision(float dt) {

}
void BodyBoss1::OnCollisionWith(CollisionEvent* e, float dt) {
	//if (dynamic_cast<Bill*>(e->dest)) {
	//	OnCollisionWithPlayer(e, dt);
	//}
}
void BodyBoss1::OnCollisionWithPlayer(CollisionEvent* e, float dt) {
	//SetState("Dead", "Dead");
}