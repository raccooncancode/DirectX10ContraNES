#include "HeadBoss3.h"
#include "AnimationAddOnManager.h"
#include "Bill.h"
#include "GunBossBullet.h"
#include "SceneManager.h"
void HeadBoss3::Update(float dt, vector<GameObject*>* objects) {
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
	if (this->parent != NULL) {
		if (this->parent->IsAllArmDestroyed()) {
			this->isCollidable = 1;
		}
	}
	this->currentHeadBoss3State->Update(dt);
	this->headBoss3Animation->Update(dt, this, this->isDead);
}

void HeadBoss3::Render() {
	headBoss3Animation->Render(this->objectBound->x + this->objectBound->w / 2, this->objectBound->y + this->objectBound->h / 2);
}

void HeadBoss3::SetParent(Boss3* p) {
	this->parent = p;
}

void HeadBoss3::SetState(std::string stateName, std::string animationName) {
	if (this->headBoss3Animation->GetAnimation() != animationName && this->currentHeadBoss3State->GetStateName() != stateName)
	{
		this->currentHeadBoss3State->Exit();
		this->currentHeadBoss3State = stateDict[stateName];
		this->currentHeadBoss3State->Enter();
		this->headBoss3Animation->SetAnimation(animationName);
	}
}

void HeadBoss3::LoadAssets() {
	tinyxml2::XMLDocument xmlDoc;
	tinyxml2::XMLError eResult = xmlDoc.LoadFile("Textures\\HeadBoss3.xml");
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
		this->headBoss3Animation->AddAnimation(name, ani);
	}
	this->headBoss3Animation->AddAnimation("Dead", AnimationAddOnManager::GetInstance()->GetAnimation("Explosion1"));
	ani = new CAnimation(0, 0, false);//temp
	this->headBoss3Animation->Update(0, this, this->isDead);
	delete ani;
}
void HeadBoss3::CreateBullet(float x, float y) {
	float bX, bY;
	float speed = 0.06;
	bX = x;
	bY = y;
	auto currentMap = SceneManager::GetInstance()->GetCurrentScene();
	currentMap->AddMovingObject(new Bullet(-96, "Boss3Bullet", "EnemyBullet", bX, bY, speed, (float) 3*D3DX_PI/2));
	currentMap->AddMovingObject(new Bullet(-96, "Boss3Bullet", "EnemyBullet", bX, bY, speed, (float)4* D3DX_PI / 3));
	currentMap->AddMovingObject(new Bullet(-96, "Boss3Bullet", "EnemyBullet", bX, bY, speed, (float)5* D3DX_PI / 3));
}
void HeadBoss3::OnNoCollision(float dt) {
	this->objectBound->y += this->vy * this->ny;
}
void HeadBoss3::OnCollisionWith(CollisionEvent* e, float dt) {
	//if (dynamic_cast<Bill*>(e->dest)) {
	//	OnCollisionWithPlayer(e, dt);
	//}
}
void HeadBoss3::OnCollisionWithPlayer(CollisionEvent* e, float dt) {
	//SetState("Dead", "Dead");
}