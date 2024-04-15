#include "Sniper.h"
#include "Bullet.h"
#include "SceneManager.h"
void Sniper::SetState(std::string stateName, std::string animationName) {
	if (this->sniperAnimation->GetAnimation() != animationName)
	{
		this->currentSniperState->Exit();
		this->currentSniperState = stateDict[stateName];
		this->currentSniperState->Enter();
		this->sniperAnimation->SetAnimation(animationName);
	}
}

void Sniper::Update(float dt, vector<GameObject*>* objects) {
	isOnGround = isHiding == false ? false : true;
	this->objects.clear();
	this->btree->Retrieve(this->btree->root, this->objects, this->objectBound);
	//Collision::GetInstance()->Proccess(this, &this->objects, dt);
	this->collision->Proccess(this, &this->objects, dt);
	if (this->target == NULL)
	{
		for (GameObject* gO : this->objects) {
			if (gO->GetType() == "Player") {
				DebugOut(L"\n Found Player");
				this->isInShootRange = true;
				SetTarget(gO);
			}
		}
	}
	currentSniperState->Update(dt);
	this->sniperAnimation->Update(dt, this, this->isDead);
}
void Sniper::Render() {
	sniperAnimation->Render(this->objectBound->x + this->objectBound->w / 2, this->objectBound->y + this->objectBound->h / 2);
	//RenderBoundingBox();
}

void Sniper::CreateBullet(float x, float y) {
	float bX, bY;
	float speed = 0.1;
	bX = x;
	bY = y;
	auto currentMap = SceneManager::GetInstance()->GetCurrentScene();
	currentMap->AddMovingObject(new Bullet(-99, "BulletSmall", "EnemyBullet", bX, bY, speed, this->angle));
}

void Sniper::OnNoCollision(float dt) {
	if (!isOnGround && !isJumping && !isHiding && !isShooting) {
		SetState("Shooting0", Helper::aXToString(ax) + "Shooting0");
	}
	if (!isOnGround && !isJumping && isHiding) {
		SetState("HidingShooting0", Helper::aXToString(ax) + "HidingShooting0");
	}
	if (this->isHiding) {
		if (this->ny > 0) {
			this->objectBound->y += vy * dt * ny;
		}
	}
	else
		this->objectBound->y += vy * dt * ny;
}
void Sniper::OnCollisionWith(CollisionEvent* e, float dt) {
	if (dynamic_cast<Bullet*>(e->dest)) {
		OnCollisionWithBullet(e, dt);
	}
	if (e->ny != 0) {
		if (e->ny > 0) {
			if (dynamic_cast<Platform*>(e->dest)) {
				isOnGround = true;
				//this->vy = 0;
			}
		}
	}
	if (e->nx != 0) {
		/*string s = e->dest->GetName();
		wstring temp = wstring(s.begin(), s.end());
		LPCWSTR wideString = temp.c_str();
		DebugOut(L"\n e nx dest: ");
		DebugOut(wideString);*/
	}
}
void Sniper::OnCollisionWithPlayer(CollisionEvent* e, float dt) {
}
void Sniper::OnCollisionWithBullet(CollisionEvent* e, float dt) {
	if (e->dest->GetType() == "PlayerBullet")
	{
		DebugOut(L"\nSniper touch player bullet");
		e->dest->isDeleted = true;
		DecreaseHP(1);
	}
}

void Sniper::LoadAssets() {
	tinyxml2::XMLDocument xmlDoc;
	tinyxml2::XMLError eResult = xmlDoc.LoadFile("Textures\\Sniper.xml");
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
		this->sniperAnimation->AddAnimation(name, ani);
	}
	ani = new CAnimation(0, 0, false);//temp
	this->sniperAnimation->Update(0, this, this->isDead);
	//InitStateVariable();
	delete ani;
}