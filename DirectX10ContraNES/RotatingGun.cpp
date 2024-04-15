#include "RotatingGun.h"
#include "Bullet.h"
#include "SceneManager.h"
#include "AnimationAddOnManager.h"
void RotatingGun::SetState(std::string stateName, std::string animationName) {
	if (this->rotatingGunAnimation->GetAnimation() != animationName)
	{
		this->currentRotatingGunState->Exit();
		this->currentRotatingGunState = stateDict[stateName];
		this->currentRotatingGunState->Enter();
		this->rotatingGunAnimation->SetAnimation(animationName);
	}
}

void RotatingGun::Update(float dt, vector<GameObject*>* objects) {
	this->objects.clear();
	this->btree->Retrieve(this->btree->root, this->objects, this->objectBound);
	//Collision::GetInstance()->Proccess(this, &this->objects, dt);
	this->collision->Proccess(this, &this->objects, dt);
	if (this->target == NULL)
	{
		for (GameObject* gO : this->objects) {
			if (gO->GetType() == "Player") {
				SetTarget(gO);
				SetState("GunOpen", "GunOpen");
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
	currentRotatingGunState->Update(dt);
	this->rotatingGunAnimation->Update(dt, this, this->isDead);
	Rotate();
}

void RotatingGun::Rotate() {
	if (this->isOpened && this->isInShootRange && !this->isDead) {
		if (this->target != NULL) {
			Bound b = this->target->GetBound();
			if (b->x < this->objectBound->x) {
				if (b->y > this->objectBound->y + this->objectBound->h) {
					//left up 45  = 135
					SetState("GunRotate135", "GunRotate135");
				}
				else if (b->y > this->objectBound->y && b->y < this->objectBound->y + this->objectBound->h + 3) {
					// left 180
					SetState("GunRotate180", "GunRotate180");
				}
				else {
					//left down 45
					SetState("GunRotate225", "GunRotate225");
				}
			}
			else if (b->x > this->objectBound->x  && b->x < this->objectBound->x + this->objectBound->w + 3) {
				if (b->y > this->objectBound->y + this->objectBound->h) {
					// up 90
					SetState("GunRotate90", "GunRotate90");
				}
				else
				{
					//down 90
					SetState("GunRotate270", "GunRotate270");
				}
			}
			else {
				if (b->y > this->objectBound->y + this->objectBound->h) {
					// right up 45
					SetState("GunRotate45", "GunRotate45");
				}
				else if (b->y > this->objectBound->y && b->y < this->objectBound->y + this->objectBound->h + 3) {
					// right 0
					SetState("GunRotate0", "GunRotate0");
				}
				else {
					//right down 315
					SetState("GunRotate315", "GunRotate315");
				}
			}
		}
	}
}

void RotatingGun::Render() {
	rotatingGunAnimation->Render(this->objectBound->x + this->objectBound->w / 2, this->objectBound->y + this->objectBound->h / 2);
	//RenderBoundingBox();
}

void RotatingGun::CreateBullet(float x, float y) {
	float bX, bY;
	float speed = 0.1;
	bX = x;
	bY = y;
	auto currentMap = SceneManager::GetInstance()->GetCurrentScene();
	currentMap->AddMovingObject(new Bullet(-99, "BulletSmall", "EnemyBullet", bX, bY, speed, this->angle));
}

void RotatingGun::OnNoCollision(float dt) {
	/*if (!isOnGround && !isJumping && !isHiding && !isShooting) {
		SetState("Shooting0", Helper::aXToString(ax) + "Shooting0");
	}
	if (!isOnGround && !isJumping && isHiding) {
		SetState("HidingShooting0", Helper::aXToString(ax) + "HidingShooting0");
	}*/
	////this->objectBound->x += vx * dt * nx;
	//this->objectBound->y += vy * dt * ny;
}
void RotatingGun::OnCollisionWith(CollisionEvent* e, float dt) {
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
void RotatingGun::OnCollisionWithPlayer(CollisionEvent* e, float dt) {
}
void RotatingGun::OnCollisionWithBullet(CollisionEvent* e, float dt) {
	if (e->dest->GetType() == "PlayerBullet")
	{
		DebugOut(L"\nRotatingGun touch player bullet");
		e->dest->isDeleted = true;
		DecreaseHP(1);
	}
}

void RotatingGun::LoadAssets() {
	tinyxml2::XMLDocument xmlDoc;
	tinyxml2::XMLError eResult = xmlDoc.LoadFile("Textures\\RotatingGun.xml");
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
		this->rotatingGunAnimation->AddAnimation(name, ani);
	}
	this->rotatingGunAnimation->AddAnimation("Dead", AnimationAddOnManager::GetInstance()->GetAnimation("Explosion0"));
	ani = new CAnimation(0, 0, false);//temp
	this->rotatingGunAnimation->Update(0, this, this->isDead);
	//InitStateVariable();
	delete ani;
}