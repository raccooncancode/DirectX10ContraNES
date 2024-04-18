#pragma once
#ifndef __BOSS3_H__
#define __BOSS3_H__

#include "ArmJoint.h"

class Boss3 {
public:
	int rotateTime;
	int swingTime;
	ArmJoint* armRight;
	ArmJoint* armLeft;
	vector<ArmJoint*> jointsLeft;
	vector<ArmJoint*> jointsRight;
public:
	Boss3() {
		this->rotateTime = 0;
		this->swingTime = 0;
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
