#include "Cannon.h"
#include "Bullet.h"
#include "SceneManager.h"
#include "AnimationAddOnManager.h"
void Cannon::SetState(std::string stateName, std::string animationName) {
	if (this->cannonAnimation->GetAnimation() != animationName && this->currentCannonState->GetStateName()!=stateName)
	{
		this->currentCannonState->Exit();
		this->currentCannonState = stateDict[stateName];
		this->currentCannonState->Enter();
		this->cannonAnimation->SetAnimation(animationName);
	}
}

void Cannon::Update(float dt, vector<GameObject*>* objects) {
	this->objects.clear();
	this->btree->Retrieve(this->btree->root, this->objects, this->objectBound);
	//Collision::GetInstance()->Proccess(this, &this->objects, dt);
	this->collision->Proccess(this, &this->objects, dt);
	if (this->target == NULL)
	{
		for (GameObject* gO : this->objects) {
			if (gO->GetType() == "Player") {
				SetTarget(gO);
				SetState("CannonShowing", "CannonShowing");
			}
		}
	}
	if (this->target != NULL) {
		if (this->target->GetBound()->x <= this->objectBound->x)
			this->nx = -1;
		else
			this->nx = 1;
		if (this->target->GetBound()->y <= this->objectBound->y)
			this->ny = -1;
		else
			this->ny = 1;
	}
	currentCannonState->Update(dt);
	this->cannonAnimation->Update(dt, this, this->isDead);
}



void Cannon::Render() {
	cannonAnimation->Render(this->objectBound->x + this->objectBound->w / 2, this->objectBound->y + this->objectBound->h / 2);
	//RenderBoundingBox();
}

void Cannon::CreateBullet(float x, float y) {
	float bX, bY;
	float speed = 0.1;
	bX = x;
	bY = y;
	auto currentMap = SceneManager::GetInstance()->GetCurrentScene();
	currentMap->AddMovingObject(new Bullet(-99, "BulletSmall", "EnemyBullet", bX, bY, speed, this->angle));
}

void Cannon::OnNoCollision(float dt) {
	/*if (!isOnGround && !isJumping && !isHiding && !isShooting) {
		SetState("Shooting0", Helper::aXToString(ax) + "Shooting0");
	}
	if (!isOnGround && !isJumping && isHiding) {
		SetState("HidingShooting0", Helper::aXToString(ax) + "HidingShooting0");
	}*/
	////this->objectBound->x += vx * dt * nx;
	//this->objectBound->y += vy * dt * ny;
}
void Cannon::OnCollisionWith(CollisionEvent* e, float dt) {
	if (dynamic_cast<Bullet*>(e->dest)) {
		OnCollisionWithBullet(e, dt);
	}
	//if (e->ny != 0) {
	//	if (e->ny > 0) {
	//		if (dynamic_cast<Platform*>(e->dest)) {
	//			isOnGround = true;
	//			//this->vy = 0;
	//		}
	//	}
	//}
	//if (e->nx != 0) {
	//	/*string s = e->dest->GetName();
	//	wstring temp = wstring(s.begin(), s.end());
	//	LPCWSTR wideString = temp.c_str();
	//	DebugOut(L"\n e nx dest: ");
	//	DebugOut(wideString);*/
	//}
}
void Cannon::OnCollisionWithPlayer(CollisionEvent* e, float dt) {
}
void Cannon::OnCollisionWithBullet(CollisionEvent* e, float dt) {
	if (e->dest->GetType() == "PlayerBullet")
	{
		DebugOut(L"\nCannon touch player bullet");
		e->dest->isDeleted = true;
		DecreaseHP(1);
	}
}

void Cannon::LoadAssets() {
	tinyxml2::XMLDocument xmlDoc;
	tinyxml2::XMLError eResult = xmlDoc.LoadFile("Textures\\Cannon.xml");
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
		this->cannonAnimation->AddAnimation(name, ani);
	}
	this->cannonAnimation->AddAnimation("Dead", AnimationAddOnManager::GetInstance()->GetAnimation("Explosion0"));
	ani = new CAnimation(0, 0, false);//temp
	this->cannonAnimation->Update(0, this, this->isDead);
	//InitStateVariable();
	delete ani;
}