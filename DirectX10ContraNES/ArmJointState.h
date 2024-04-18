#pragma once
#ifndef __ArmJointSTATE_H__
#define __ArmJointSTATE_H__

class ArmJoint;

#include <string>
#include "GameObject.h"
using namespace std;

class ArmJointState {
protected:
	ArmJoint* armJoint;
	float holdTime;
	float maxYCanReach;
public:
	ArmJointState(ArmJoint* bH) { this->armJoint = bH; }
	virtual void Enter() {};
	virtual void Exit() {};
	virtual void OnKeyDown(int keyCode) {};
	virtual void OnKeyUp(int keyCode) {};
	virtual void Update(float dt) {}
	virtual string GetStateName() { return ""; };
};

class ArmJointDefault :public ArmJointState {
private:
public:
	ArmJointDefault(ArmJoint* bH) :ArmJointState(bH) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

class ArmJointRuin :public ArmJointState {
private:
public:
	ArmJointRuin(ArmJoint* bH) :ArmJointState(bH) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

class ArmJointDead :public ArmJointState {
private:
public:
	ArmJointDead(ArmJoint* bH) :ArmJointState(bH) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

#endif // !__ArmJointSTATE_H__
