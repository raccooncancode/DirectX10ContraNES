#pragma once
#ifndef __ArmJoint_H__
#define __ArmJoint_H__

class Boss3;

#include "Enemy.h"
#include "ArmJointAnimation.h"
#include "ArmJointState.h"
#include <unordered_map>
#include "tinyxml2.h"
class ArmJoint :public Enemy {
public:
	bool isInShootRange;
	bool isMoveTo;
	bool isMoveAround;
	ArmJoint* frontSibling;
	bool isTail;
	bool isLeftSide;
	bool isDoneMoveTo;
	bool isDoneMoveAround;
	float angularSpeed;
	float radius;
private:
	ArmJointAnimation* armJointAnimation;
	ArmJointState* currentArmJointState;
	std::unordered_map<std::string, ArmJointState*> stateDict;
	Boss3* parent;
public:
	ArmJoint(int id, string name, string type, int hp,bool isLeftSide=false,bool isTail =false) :Enemy(id, name, type, hp) {
		this->nx = -1;
		this->ny = -1;
		this->SetSpeed(0.1, 0.1);
		this->angle = 0;
		this->radius = 0;
		this->isLeftSide = isLeftSide;
		this->frontSibling = NULL;
		this->angularSpeed = 0;
		this->isTail = isTail;
		this->isMoveAround = false;
		this->isMoveTo = false;
		this->isInShootRange = false;
		this->armJointAnimation = new ArmJointAnimation(this);
		this->currentArmJointState = new ArmJointState(this);
		stateDict["ArmJointDefault"] = new ArmJointDefault(this);
		stateDict["ArmJointRuin"] = new ArmJointRuin(this);
		stateDict["Dead"] = new ArmJointDead(this);
		this->SetState("ArmJointDefault", "ArmJointDefault");
	}
	void SetParent(Boss3* b);
	void Update(float dt, vector<GameObject*>* objects = NULL);
	void Render();
	void LoadAssets();
	int GetAx()override {
		return 0;
	}
	void SetAngularSpeed(float speed);
	void SetRadius(float radius);
	void SetFrontSibling(ArmJoint* joint);
	void SetState(std::string stateName, std::string animationName);
	void OnNoCollision(float dt) override;
	void OnCollisionWith(CollisionEvent* e, float dt) override;
	void OnCollisionWithPlayer(CollisionEvent* e, float dt);
	void CreateBullet(float x, float y);
};

#endif // !__ArmJoint_H__
