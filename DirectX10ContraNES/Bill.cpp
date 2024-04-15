#include "Map.h"
#include "Bill.h"
#include "TextureManager.h"
#include "SceneManager.h"
#include <corecrt.h>
#include <cmath>
#include <algorithm>
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
			float cx, cy;
			cx = Camera::GetInstance()->GetCameraBound()->x;
			cy = Camera::GetInstance()->GetCameraBound()->y;

			this->objectBound->UpdateBoundLocation(cx + 50, cy + 200);
			SetState("Falling0", Helper::aXToString(ax) + "Falling0");
		}
		else
		{
			//this is the place to switch to ending scene
			return;
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
	this->billAnimation->Update(dt,this,this->isDead);
	this->currentBillState->Update(dt);
	
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
		SetState("Dead", Helper::aXToString(ax) + "Dead");
	}
	if (dynamic_cast<Bullet*>(e->dest)) {
		if (e->dest->GetType() == "EnemyBullet")
		{
			e->dest->isDeleted = true;
			SetState("Dead", Helper::aXToString(ax) + "Dead");
		}
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
	float angleSupport1 = this->angle - D3DX_PI / 6;
	float angleSupport2 = this->angle - D3DX_PI / 4;
	float angleSupport3 = this->angle + D3DX_PI / 4;
	float angleSupport4 = this->angle + D3DX_PI / 6;
	Bound bound = this->GetBound();
	bX = x;
	bY = y;
	auto currentMap = SceneManager::GetInstance()->GetCurrentScene();
	switch (bulletType)
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
	default:
		break;
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