#pragma once
#ifndef __ArmJointANIMATION_H__
#define __ArmJointANIMATION_H__

class ArmJoint;

#include "GameAnimation.h"

class ArmJointAnimation :public GameAnimation {
private:
	ArmJoint* armJoint;
public:
	ArmJointAnimation(ArmJoint* g) { this->armJoint = g; }
	void Update(float dt, GameObject* o = NULL, bool isDead = false);
};

#endif // !__ArmJointANIMATION_H__
