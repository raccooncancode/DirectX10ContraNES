#include "Item.h"
#include "AnimationAddOnManager.h"
#include "Bill.h"
void Item::Update(float dt, vector<GameObject*>* objects) {
	this->objects.clear();
	this->btree->Retrieve(this->btree->root, this->objects, this->objectBound);
	this->collision->Proccess(this, &this->objects, dt);
	if (this->bill == NULL) {
		for (GameObject* gO : this->objects) {
			if (gO->GetType() == "Player") {
				this->bill = gO;
			}
		}
	}
	if (this->bill != NULL) {
		if (this->bill->GetBound()->x <= this->objectBound->x && this->isDeleted==false) {
			this->nx = -1;
		}
		else
		{
			this->nx = 1;
		}
	}
	if (this->objectBound->y <= this->maxYCanReach && !this->isReachMaxY) {
		this->ny = 1;
	}
	else {
		this->isReachMaxY = true;
		this->ny = -1;
		this->SetSpeed(0.1, 1.5);
	}
	this->currentItemState->Update(dt);
	this->itemAnimation->Update(dt, this, this->isDead);
}

void Item::Render() {
	itemAnimation->Render(this->objectBound->x + this->objectBound->w / 2, this->objectBound->y + this->objectBound->h / 2);
}

void Item::SetState(std::string stateName, std::string animationName) {
	if (this->itemAnimation->GetAnimation() != animationName && this->currentItemState->GetStateName() != stateName)
	{
		this->currentItemState->Exit();
		this->currentItemState = stateDict[stateName];
		this->currentItemState->Enter();
		this->itemAnimation->SetAnimation(animationName);
	}
}

void Item::LoadAssets() {
	tinyxml2::XMLDocument xmlDoc;
	tinyxml2::XMLError eResult = xmlDoc.LoadFile("Textures\\Item.xml");
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
		this->itemAnimation->AddAnimation(name, ani);
	}
	this->itemAnimation->AddAnimation("Dead", AnimationAddOnManager::GetInstance()->GetAnimation("Explosion0"));
	ani = new CAnimation(0, 0, false);//temp
	this->itemAnimation->Update(0, this, this->isDead);
	delete ani;
}
void Item::InitItem() {
	this->maxYCanReach = this->objectBound->y + 10;
}
void Item::OnNoCollision(float dt) {
	this->objectBound->x += this->vx * nx;
	this->objectBound->y += this->vy * ny;
}
void Item::OnCollisionWith(CollisionEvent* e, float dt) {
	if (e->dest->GetType() == "Player") {
		OnCollisionWithPlayer(e, dt);
	}

}
void Item::OnCollisionWithPlayer(CollisionEvent* e, float dt) {
	//this->isDeleted = true;
}
void Item::OnCollisionWithPlayerBullet(CollisionEvent* e, float dt) {
}