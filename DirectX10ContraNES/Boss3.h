#pragma once
#ifndef __BOSS3_H__
#define __BOSS3_H__

#include "ArmJoint.h"
#include "HeadBoss3.h"

class Boss3 {
public:
	int rotateTime;
	int swingTime;
	bool isSeeTarget;
	bool isMoveTo;
	bool isMoveAround;
	bool isDead;
	HeadBoss3* head;
	ArmJoint* armRight;
	ArmJoint* armLeft;
	vector<ArmJoint*> jointsLeft;
	vector<ArmJoint*> jointsRight;
public:
	Boss3() {
		this->isDead = false;
		this->isSeeTarget = false;
		this->isMoveAround = false;
		this->isMoveTo = false;
		this->rotateTime = 0;
		this->swingTime = 0;
	}
	bool IsDoneMoveTo() {
		for (ArmJoint* joint : jointsLeft) {
			if (!joint->isDoneMoveTo)
				return false;
		}
		for (ArmJoint* joint : jointsRight) {
			if (!joint->isDoneMoveTo)
				return false;
		}
		return true;
	}
	bool IsAllArmDestroyed() {
		for (ArmJoint* joint : jointsLeft) {
			if (!joint->isDeleted)
				return false;
		}
		for (ArmJoint* joint : jointsRight) {
			if (!joint->isDeleted)
				return false;
		}
		return true;
	}
	void AddHead(HeadBoss3* head) {
		this->head = head;
	}
	void AddArmLeft(ArmJoint* joint){
		this->armLeft = joint;
	}
	void AddArmRight(ArmJoint* joint) {
		this->armRight = joint;
	}
	void AddArmLeftJoint(ArmJoint* joint) {
		this->jointsLeft.push_back(joint);
	}
};

#endif // !__BOSS3_H__
