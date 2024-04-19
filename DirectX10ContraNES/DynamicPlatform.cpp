#include "DynamicPlatform.h"
#include "AnimationAddOnManager.h"
#include "Bill.h"
#include "GunBossBullet.h"
#include "SceneManager.h"
void DynamicPlatform::Update(float dt, vector<GameObject*>* objects) {
	this->objects.clear();
	this->btree->Retrieve(this->btree->root, this->objects, this->objectBound);
	this->collision->Proccess(this, &this->objects, dt);
	if (this->objectBound->x <= 10)
		this->nx = 1;
	if (this->objectBound->x >= 200)
		this->nx = -1;
	this->currentDynamicPlatformState->Update(dt);
	this->dynamicPlatformAnimation->Update(dt, this, this->isDead);
}

void DynamicPlatform::Render() {
	dynamicPlatformAnimation->Render(this->objectBound->x + this->objectBound->w / 2, this->objectBound->y + this->objectBound->h / 2);
	//RenderBoundingBox();
}


void DynamicPlatform::SetState(std::string stateName, std::string animationName) {
	if (this->dynamicPlatformAnimation->GetAnimation() != animationName && this->currentDynamicPlatformState->GetStateName() != stateName)
	{
		this->currentDynamicPlatformState->Exit();
		this->currentDynamicPlatformState = stateDict[stateName];
		this->currentDynamicPlatformState->Enter();
		this->dynamicPlatformAnimation->SetAnimation(animationName);
	}
}

void DynamicPlatform::LoadAssets() {
	tinyxml2::XMLDocument xmlDoc;
	tinyxml2::XMLError eResult = xmlDoc.LoadFile("Textures\\DynamicPlatform.xml");
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
		this->dynamicPlatformAnimation->AddAnimation(name, ani);
	}
	this->dynamicPlatformAnimation->AddAnimation("Dead", AnimationAddOnManager::GetInstance()->GetAnimation("Explosion0"));
	ani = new CAnimation(0, 0, false);//temp
	this->dynamicPlatformAnimation->Update(0, this, this->isDead);
	delete ani;
}
void DynamicPlatform::CreateBullet(float x, float y) {
	float bX, bY;
	float speed = 0.01;
	bX = x;
	bY = y;
	auto currentMap = SceneManager::GetInstance()->GetCurrentScene();
}
void DynamicPlatform::OnNoCollision(float dt) {
	this->objectBound->x += this->nx * this->vx *dt;
}
void DynamicPlatform::OnCollisionWith(CollisionEvent* e, float dt) {
	if (e->dest->GetName() == "Platform") {
			this->nx = -1 * this->nx;
	}
	this->objectBound->x += this->nx * this->vx *dt ; 
}
void DynamicPlatform::OnCollisionWithPlayer(CollisionEvent* e, float dt) {
}