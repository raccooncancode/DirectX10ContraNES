#pragma once
#ifndef __CANNONSTATE_H__
#define __CANNONSTATE_H__

class Cannon;

#include <string>
#include "GameObject.h"
using namespace std;

class CannonState {
protected:
	Cannon* cannon;
	float holdTime;
	float maxYCanReach;
public:
	CannonState(Cannon* c) { this->cannon = c; }
	virtual void Enter() {};
	virtual void Exit() {};
	virtual void OnKeyDown(int keyCode) {};
	virtual void OnKeyUp(int keyCode) {};
	virtual void Update(float dt) {}
	virtual string GetStateName() { return ""; };
};

class CannonHiding :public CannonState {
private:
public:
	CannonHiding(Cannon* c) :CannonState(c) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

class CannonShowing :public CannonState {
private:
public:
	CannonShowing(Cannon* c) :CannonState(c) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

class CannonShooting :public CannonState {
private:
public:
	CannonShooting(Cannon* c) :CannonState(c) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

class CannonDead :public CannonState {
private:
public:
	CannonDead(Cannon* c) :CannonState(c) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};
#endif //!__CANNONSTATE_H__