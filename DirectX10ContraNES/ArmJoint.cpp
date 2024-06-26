#include "Boss3.h"
#include "ArmJoint.h"
#include "AnimationAddOnManager.h"
#include "Bill.h"
#include "GunBossBullet.h"
#include "SceneManager.h"
#include <algorithm>
void ArmJoint::Update(float dt, vector<GameObject*>* objects) {
	this->objects.clear();
	this->btree->Retrieve(this->btree->root, this->objects, this->objectBound);
	this->collision->Proccess(this, &this->objects, dt);
	if (this->parent != NULL) {
		if (this->parent->isSeeTarget && this->parent->IsDoneMoveTo() == false) {
			MoveTo(dt);
		}
		if (this->parent->IsDoneMoveTo()) {
			MoveAround(dt);
		}
	}
	this->currentArmJointState->Update(dt);
	this->armJointAnimation->Update(dt, this, this->isDead);
}

void ArmJoint::MoveTo(float dt) {
	
	this->ny = 1;
	this->nx = this->isLeftSide ? -1 : 1;
	if (this->isLeftSide) {
		if (this->objectBound->x != desX) {
			if (this->objectBound->x <= this->desX)
				this->objectBound->x = desX;
			else
				this->objectBound->x += this->nx * this->vx * dt;
		}
	}
	else {
		if (this->objectBound->x != desX) {
			if (this->objectBound->x >= this->desX)
				this->objectBound->x = desX;
			else
				this->objectBound->x += this->nx * this->vx * dt;
		}
	}
	if (this->objectBound->x == desX) {
		this->isDoneMoveTo = true;
	}
}

void ArmJoint::MoveAround(float dt) {
	if (this->angularSpeed != 0 && this->frontSibling != NULL) {
		this->nx = cos(angle);
		this->ny = sin(angle);
		if (isLeftSide)
			this->angle += this->angularSpeed;
		else
			this->angle -= this->angularSpeed;
		if (this->angle >= D3DX_PI * 2)
			this->angle = 0;
		float xNext, yNext;
		xNext = this->frontSibling->GetBound()->GetMiddleXOffset() + (cos(angle) * this->radius) - this->objectBound->w / 2;
		yNext = this->frontSibling->GetBound()->GetMiddleYOffset() + (sin(angle) * this->radius) - this->objectBound->h / 2;
		this->objectBound->x = xNext;
		this->objectBound->y = yNext;
		if (this->frontSibling->isDead) {
			this->isDead = true;
		}
		if (this->isTail) {
			if (this->shootingTime <= 2333) {
				this->shootingTime += dt;
			}
			else {
				this->shootingTime = 0;
				this->CreateBullet(this->objectBound->x, this->objectBound->y);
			}
		}

	}
}

void ArmJoint::Render() {
	armJointAnimation->Render(this->objectBound->x + this->objectBound->w / 2, this->objectBound->y + this->objectBound->h / 2);
}

void ArmJoint::SetFrontSibling(ArmJoint* joint) {
	this->frontSibling = joint;
}

void ArmJoint::SetParent(Boss3* b) {
	this->parent = b;
}

void ArmJoint::SetRadius(float radius) {
	this->radius = radius;
}

void ArmJoint::SetAngularSpeed(float speed) {
	this->angularSpeed = speed;
}

void ArmJoint::SetState(std::string stateName, std::string animationName) {
	if (this->armJointAnimation->GetAnimation() != animationName && this->currentArmJointState->GetStateName() != stateName)
	{
		this->currentArmJointState->Exit();
		this->currentArmJointState = stateDict[stateName];
		this->currentArmJointState->Enter();
		this->armJointAnimation->SetAnimation(animationName);
	}
}

void ArmJoint::LoadAssets() {
	tinyxml2::XMLDocument xmlDoc;
	tinyxml2::XMLError eResult;
	if(this->isTail==false)
		eResult = xmlDoc.LoadFile("Textures\\ArmJoint.xml");
	else
		eResult = xmlDoc.LoadFile("Textures\\ArmJoint1.xml");
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
		this->armJointAnimation->AddAnimation(name, ani);
	}
	this->armJointAnimation->AddAnimation("Dead", AnimationAddOnManager::GetInstance()->GetAnimation("Explosion1"));
	ani = new CAnimation(0, 0, false);//temp
	this->armJointAnimation->Update(0, this, this->isDead);
	delete ani;
}
void ArmJoint::CreateBullet(float x, float y) {
	float bX, bY;
	float minRange = this->isLeftSide ? (float)5 * D3DX_PI / 4 : (float)11 * D3DX_PI / 6;
	float maxRange = this->isLeftSide ? (float)11 * D3DX_PI / 6 : (float)7 * D3DX_PI / 4;
	float angle = ((float)rand() / RAND_MAX) * (maxRange - minRange) + minRange;
	float speed = 0.06;
	bX = x;
	bY = y;
	auto currentMap = SceneManager::GetInstance()->GetCurrentScene();
	currentMap->AddMovingObject(new Bullet(-96, "Boss3Bullet", "EnemyBullet", bX, bY, speed, angle));
}
void ArmJoint::OnNoCollision(float dt) {

}
void ArmJoint::OnCollisionWith(CollisionEvent* e, float dt) {
	//if (dynamic_cast<Bill*>(e->dest)) {
	//	OnCollisionWithPlayer(e, dt);
	//}
}
void ArmJoint::OnCollisionWithPlayer(CollisionEvent* e, float dt) {
	//SetState("Dead", "Dead");
}