#include "Map.h"
#include "Bill.h"
#include "TextureManager.h"
#include "SceneManager.h"
#include <corecrt.h>
#include <cmath>
#include <algorithm>
#include "Camera.h"
void Bill::SetState(std::string stateName, std::string animationName)
{
	if (this->billAnimation->GetAnimation() != animationName)
	{
		currentBillState->Exit();
		this->currentBillState = stateDict[stateName];
		this->currentBillState->Enter();
		this->billAnimation->SetAnimation(animationName);
	}
}

void Bill::OnKeyDown(int keyCode)
{
	if (keyCode == DIK_O) {
		SceneManager::GetInstance()->ChangeMap(3);
	}
	this->currentBillState->OnKeyDown(keyCode);
}

void Bill::OnKeyUp(int keyCode)
{
	this->currentBillState->OnKeyUp(keyCode);
}
void Bill::Update(float dt,vector<GameObject*>* objects)
{
	//DebugOut(L"\nRes Times: %d", respawnTimes);
	if (this->isDeleted == true) {
		if (this->respawnTimes >= 0) {
			this->isDeleted = false;
			this->isDead = false;
			this->ax = 1;
			this->ny = -1;
			int stage = Camera::GetInstance()->currentStage;
			float resX = Camera::GetInstance()->GetCameraBound()->x + 30;
			float resY = Camera::GetInstance()->GetCameraBound()->y + 30;
			if (stage == 1) {
				this->objectBound->UpdateBoundLocation(resX,200);
			}
			else {
				this->objectBound->UpdateBoundLocation(80,resY);
			}
			SetState("Falling0", Helper::aXToString(ax) + "Falling0");
		}
		else
		{
			//this is the place to switch to ending scene
			return;
		}
	}
	if (Camera::GetInstance()->GetTarget() == NULL) {
		Bound camBound = Camera::GetInstance()->GetCameraBound();
		if (Camera::GetInstance()->currentStage == 1) {
			if (this->objectBound->x >= camBound->x + camBound->w / 2 - 20) {
				Camera::GetInstance()->SetFollowTarget(this);
			}
		}
		else {
			if (this->objectBound->y >= camBound->y + camBound->h / 2 - 30) {
				Camera::GetInstance()->SetFollowTarget(this);
			}
		}
	}
	isOnGround = false;
	// only retrieve all bound in current object bound is in to process collision
	this->objects.clear();
	this->btree->Retrieve(btree->root,this->objects, this->objectBound);
	//DebugOut(L"\n Object size: %d", this->objects.size());
	//auto test = this->objects; 
	// check if lowest object retrieved 
	// then you're success that just check collision in only node or (2 nodes) you are in
	//Collision::GetInstance()->Proccess(this, &this->objects, dt);
	this->collision->Proccess(this, &this->objects, dt);
	if (this->boss == NULL) {

		for (GameObject* o : this->objects) {
			if (o->GetName() == "BodyBoss3" || o->GetName() == "GunBoss1") {
				this->boss = o;
				DebugOut(L"\nPlayer found boss");
				Camera::GetInstance()->SetFollowTarget(o);
			}
		}
	}
	this->billAnimation->Update(dt,this,this->isDead);
	this->currentBillState->Update(dt);
	ResetBulletType(dt);
	//DebugOut(L"\nBullet Type :%d", this->bulletType);
}

void Bill::OnNoCollision(float dt) {
	if (!isOnGround && !isJumping && !isSwimming) {
		SetState("Falling0", Helper::aXToString(ax) + "Falling0");
	}
	this->objectBound->x += vx * dt  * nx;
	this->objectBound->y += vy * dt  * ny;
}

void Bill::OnCollisionWith(CollisionEvent* e, float dt) {

	if (e->ny > 0) {
		if (dynamic_cast<Platform*>(e->dest)) {
			if (e->dest->GetType().compare("water") == 0 && !isSwimming) {
				if (!isSwimming) {
					SetState("Swimming", Helper::aXToString(ax) + "Swimming");
				}
			}
			else 
			{
				isOnGround = true;
			}
		}
		if (e->dest->GetType() == "Bridge") {
				isOnGround = true;

		}
	}
	if(e->nx != 0) {
		if (dynamic_cast<Bullet*>(e->dest)) {
			if (e->dest->GetType().compare("PlayerBullet")) {
				
			}
		}
		else
		{
			this->nx = 0;
		}
	}
	if (dynamic_cast<Enemy*>(e->dest)) {
		if(e->dest->GetName()!="BodyBoss1")
			SetState("Dead", Helper::aXToString(ax) + "Dead");
			Camera::GetInstance()->SetFollowTarget(NULL);
	}
	if (dynamic_cast<Bullet*>(e->dest)) {
		if (e->dest->GetType() == "EnemyBullet")
		{
			e->dest->isDeleted = true;
			SetState("Dead", Helper::aXToString(ax) + "Dead");
			Camera::GetInstance()->SetFollowTarget(NULL);
		}
	}
	if (e->dest->GetType() == "Item") {
		OnCollisionWithItem(e, dt);
	}
}

void Bill::OnCollisionWithItem(CollisionEvent* e, float dt) {
	/*string s = e->dest->GetName();
	wstring temp = wstring(s.begin(), s.end());
	LPCWSTR wideString = temp.c_str();
	DebugOut(L"\n");
	DebugOut(wideString);*/
	e->dest->isDeleted = true;
	this->timeBulletType = 0;
	if (e->dest->GetName() == "ItemM") {
		this->bulletType = 1;
	}
	else if (e->dest->GetName() == "ItemS") {
		this->bulletType = 2;
	}
	else {
		this->bulletType = 3;
	}
}

void Bill::Render()
{
	billAnimation->Render(this->objectBound->x +this->objectBound->w/2, this->objectBound->y+this->objectBound->h/2);
	
	//RenderBoundingBox();
}

void Bill::CreateBullet(float x,float y) {
	float bX, bY;
	
	float speed = this->bulletType != 3 ? 0.15 : 0.2;
	float angleSupport1 = this->angle - D3DX_PI / 12;
	float angleSupport2 = this->angle - D3DX_PI / 24;
	float angleSupport3 = this->angle + D3DX_PI / 12;
	float angleSupport4 = this->angle + D3DX_PI / 24;
	Bound bound = this->GetBound();
	bX = x;
	bY = y;
	auto currentMap = SceneManager::GetInstance()->GetCurrentScene();
	switch (this->bulletType)
	{
	case 0: //regular
		currentMap->AddMovingObject(new Bullet(-99, "BulletSmall", "PlayerBullet", bX, bY, speed, this->angle));
		break;
	case 1: //get M - bigger bullet
		currentMap->AddMovingObject(new Bullet(-98, "BulletBig", "PlayerBullet", bX, bY, speed, this->angle));
		break;
	case 2: //get S - 5 bullets
		 currentMap->AddMovingObject(new Bullet(-98, "BulletBig", "PlayerBullet", bX, bY, speed, this->angle));
		 currentMap->AddMovingObject(new Bullet(-98, "BulletBig", "PlayerBullet", bX, bY, speed, angleSupport1));
		 currentMap->AddMovingObject(new Bullet(-98, "BulletBig", "PlayerBullet", bX, bY, speed, angleSupport2));
		 currentMap->AddMovingObject(new Bullet(-98, "BulletBig", "PlayerBullet", bX, bY, speed, angleSupport3));
		 currentMap->AddMovingObject(new Bullet(-98, "BulletBig", "PlayerBullet", bX, bY, speed, angleSupport4));
		break;
	case 3: //get R - sped up bullet
		currentMap->AddMovingObject(new Bullet(-99, "BulletSmall", "PlayerBullet", bX, bY, speed, this->angle));
		break;
	default:
		break;
	}
}

void Bill::DecreaseHP() {
	this->respawnTimes--;
}

void Bill::ResetBulletType(float dt) {
	//after 5 second , reset bullet type to default
	if (this->bulletType != 0) {
		if (this->timeBulletType <= 10000) {
			this->timeBulletType += dt;
		}
		else {
			this->bulletType = 0;
			this->timeBulletType = 0;
		}
	}
}

void Bill::LoadAssets() {
	tinyxml2::XMLDocument xmlDoc;
	tinyxml2::XMLError eResult = xmlDoc.LoadFile("Textures\\Bill.xml");
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
	LPTEXTURE tex = TextureManager::GetInstance()->Get(id);

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
		this->billAnimation->AddAnimation(name, ani);
	}
	ani = new CAnimation(0, 0, false);//temp
	this->billAnimation->Update(0,this,this->isDead);
	//InitStateVariable();
	delete ani;
}