#include "Soldier.h"
#include "Bullet.h"
void Soldier::SetState(std::string stateName, std::string animationName) {
	if (this->soldierAnimation->GetAnimation() != animationName)
	{
		this->currentSoldierState->Exit();
		this->currentSoldierState = stateDict[stateName];
		this->currentSoldierState->Enter();
		this->soldierAnimation->SetAnimation(animationName);
	}
}
void Soldier::Update(float dt, vector<GameObject*>* objects){
	isOnGround = false;
	this->objects.clear();
	this->btree->Retrieve(this->btree->root, this->objects, this->objectBound);
	//Collision::GetInstance()->Proccess(this, &this->objects, dt);
	this->collision->Proccess(this, &this->objects, dt);
	if (this->target == NULL)
	{
		for (GameObject* gO : this->objects) {
			if (gO->GetType() == "Player") {
				//DebugOut(L"\nSoldier Found Player");
				SetTarget(gO);
				this->nx = gO->GetBound()->x < this->objectBound->x ? -1 : 1;
				this->ax = this->nx;
				SetState("Running", Helper::aXToString(ax) + "Running");
				this->isInShootRange = false;
				//this->isInShootRange = true;
			}
		}
	}
	currentSoldierState->Update(dt);
	this->soldierAnimation->Update(dt, this, this->isDead);
}
void Soldier::Render(){
	soldierAnimation->Render(this->objectBound->x + this->objectBound->w / 2, this->objectBound->y + this->objectBound->h / 2);
	//RenderBoundingBox();
}
void Soldier::OnNoCollision(float dt) {
	if (!isOnGround && !isJumping && !isSwimming) {
		SetState("Falling", Helper::aXToString(ax) + "Falling");
	}
	this->objectBound->y += vy * dt * ny;
}
void Soldier::OnCollisionWith(CollisionEvent* e, float dt) {
	if (dynamic_cast<Bullet*>(e->dest)) {
		OnCollisionWithBullet(e, dt);
	}
	if (dynamic_cast<Enemy*>(e->dest)) {
		return;
	}
	if (e->ny != 0) {
		if (e->ny > 0) {
			if (dynamic_cast<Platform*>(e->dest)) {
				if (e->dest->GetType() != "water")
				{

					isOnGround = true;
					if(isInShootRange == true)
						SetState("Shooting", Helper::aXToString(ax) + "Shooting");
					else
						SetState("Running", Helper::aXToString(ax) + "Running");

				}
				else
				{
					this->isDeleted = true;
				}
			}
		}
	}
	if (e->nx != 0) {
		//this->nx = 0;
	}
}
void Soldier::OnCollisionWithPlayer(CollisionEvent* e, float dt) {
}
void Soldier::OnCollisionWithBullet(CollisionEvent* e, float dt) {
	if (e->dest->GetType() == "PlayerBullet")
	{
		e->dest->isDeleted = true;
		DecreaseHP(1);
	}
}

void Soldier::LoadAssets(){
	tinyxml2::XMLDocument xmlDoc;
	tinyxml2::XMLError eResult = xmlDoc.LoadFile("Textures\\Soldier.xml");
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
	LPTEXTURE tex = TextureManager::GetInstance()->Get(1);

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
		this->soldierAnimation->AddAnimation(name, ani);
	}
	ani = new CAnimation(0, 0, false);//temp
	this->soldierAnimation->Update(0, this, this->isDead);
	//InitStateVariable();
	delete ani;
}