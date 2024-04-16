#pragma once
#ifndef __CapsuleSTATE_H__
#define __CapsuleSTATE_H__

class Capsule;

#include <string>
#include "GameObject.h"
using namespace std;

class CapsuleState {
protected:
	Capsule* capsule;
	float holdTime;
	float maxYCanReach;
public:
	CapsuleState(Capsule* c) { this->capsule = c; }
	virtual void Enter() {};
	virtual void Exit() {};
	virtual void OnKeyDown(int keyCode) {};
	virtual void OnKeyUp(int keyCode) {};
	virtual void Update(float dt) {}
	virtual string GetStateName() { return ""; };
};

class CapsuleDefault :public CapsuleState {
private:
public:
	CapsuleDefault(Capsule* c) :CapsuleState(c) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

class CapsuleHiding :public CapsuleState {
private:
public:
	CapsuleHiding(Capsule* c) :CapsuleState(c) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

class CapsuleDead :public CapsuleState {
private:
public:
	CapsuleDead(Capsule* c) :CapsuleState(c) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

#endif // !__CapsuleSTATE_H__
