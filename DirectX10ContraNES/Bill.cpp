#include "Bill.h"
#include "TextureManager.h"
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
	this->currentBillState->OnKeyDown(keyCode);
}

void Bill::OnKeyUp(int keyCode)
{
	this->currentBillState->OnKeyUp(keyCode);
}
void Bill::Update(float dt,vector<GameObject*>* objects)
{
	isOnGround = false;
	Collision::GetInstance()->Proccess(this, objects, dt);
	this->billAnimation->Update(dt,this,this->isDead);
	this->currentBillState->Update(dt);
	for (Bullet* b : bullets) {
		b->Update(dt,objects);
	}
}

void Bill::OnNoCollision(float dt) {
	if (!isOnGround && !isJumping && !isSwimming) {
		SetState("Falling0", Helper::aXToString(ax) + "Falling0");
	}
	this->objectBound->x += vx * dt  * nx;
	this->objectBound->y += vy * dt  * ny;
}

void Bill::OnCollisionWith(CollisionEvent* e, float dt) {
	if (e->ny > 0 ) {
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
	if(e->nx != 0 ){
		this->nx = 0;
	}
}

void Bill::Render()
{
	billAnimation->Render(this->objectBound->x +this->objectBound->w/2, this->objectBound->y+this->objectBound->h/2);
	for (Bullet* b : bullets) {
		b->Render();
	}
	//RenderBoundingBox();
}

void Bill::CreateBullet(float x,float y) {
	float bX, bY;
	
	float speed = this->bulletType != 3 ? 0.15 : 0.25;
	float angleSupport1 = this->angle - D3DX_PI / 6;
	float angleSupport2 = this->angle - D3DX_PI / 4;
	float angleSupport3 = this->angle + D3DX_PI / 4;
	float angleSupport4 = this->angle + D3DX_PI / 6;
	Bound bound = this->GetBound();
	bX = x;
	bY = y;
	switch (bulletType)
	{
	case 0: //regular
		this->bullets.push_back(new Bullet(-99, "BulletSmall", "Bullet", bX, bY, speed, this->angle));
		break;
	case 1: //get M - bigger bullet
		this->bullets.push_back(new Bullet(-98, "BulletBig", "Bullet", bX, bY, speed, this->angle));
		break;
	case 2: //get S - 5 bullets
		this->bullets.push_back(new Bullet(-98, "BulletBig", "Bullet", bX, bY, speed, this->angle));
		this->bullets.push_back(new Bullet(-98, "BulletBig", "Bullet", bX, bY, speed, angleSupport1));
		this->bullets.push_back(new Bullet(-98, "BulletBig", "Bullet", bX, bY, speed, angleSupport2));
		this->bullets.push_back(new Bullet(-98, "BulletBig", "Bullet", bX, bY, speed, angleSupport3));
		this->bullets.push_back(new Bullet(-98, "BulletBig", "Bullet", bX, bY, speed, angleSupport4));
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